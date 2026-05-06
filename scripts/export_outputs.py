#!/usr/bin/env python3
"""Copy outputs and keep only compact per-testcase result artifacts."""

from __future__ import annotations

import argparse
import shutil
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_SOURCE = ROOT / "outputs"
DEFAULT_DEST = ROOT / "outputs-export"
REMOVE_RELATIVE_PATHS = (
    Path("bad"),
    Path("good"),
    Path("cve.json"),
    Path("results/run"),
)
KEEP_RESULT_FILENAMES = {"log.json", "output.txt"}
KEEP_RESULT_RELATIVE_PATHS = {Path("judge/output.json")}


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Copy vastdb-eval outputs to a new directory, then remove bad/, "
            "good/, cve.json, and results/run from every CWD "
            "testcase directory in the copy. Remaining results subdirectories "
            "keep only log.json, output.txt, and results/judge/output.json."
        )
    )
    parser.add_argument(
        "--source",
        type=Path,
        default=DEFAULT_SOURCE,
        help=f"source outputs directory (default: {DEFAULT_SOURCE})",
    )
    parser.add_argument(
        "--dest",
        type=Path,
        default=DEFAULT_DEST,
        help=f"destination directory for the pruned copy (default: {DEFAULT_DEST})",
    )
    parser.add_argument(
        "--force",
        action="store_true",
        help="replace the destination directory if it already exists",
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="show what would be removed without copying or deleting anything",
    )
    return parser.parse_args()


def is_relative_to(path: Path, parent: Path) -> bool:
    try:
        path.relative_to(parent)
    except ValueError:
        return False
    return True


def is_testcase_dir(path: Path) -> bool:
    parts = path.name.split("-")
    if len(parts) != 3 or parts[0] != "CWD":
        return False
    expected_parent = "-".join(parts[:2])
    return path.parent.name == expected_parent


def testcase_dirs(root: Path) -> list[Path]:
    return sorted(
        path for path in root.rglob("CWD-*") if path.is_dir() and is_testcase_dir(path)
    )


def validate_force_dest(source: Path, dest: Path) -> None:
    protected = {
        Path("/").resolve(),
        Path.home().resolve(),
        ROOT,
        ROOT.parent,
        source,
        source.parent,
    }
    if dest in protected:
        raise SystemExit(f"refusing to replace protected directory: {dest}")


def remove_path(path: Path) -> bool:
    if not path.exists() and not path.is_symlink():
        return False

    if path.is_dir() and not path.is_symlink():
        shutil.rmtree(path)
    else:
        path.unlink()
    return True


def plan_removals(root: Path) -> tuple[list[Path], int]:
    cases = testcase_dirs(root)
    removals: list[Path] = []
    for case in cases:
        for relative_path in REMOVE_RELATIVE_PATHS:
            path = case / relative_path
            if path.exists() or path.is_symlink():
                removals.append(path)

        results_dir = case / "results"
        if results_dir.is_dir():
            for path in sorted(results_dir.rglob("*")):
                if any(parent in removals for parent in path.parents):
                    continue
                if path.is_file() or path.is_symlink():
                    relative_path = path.relative_to(results_dir)
                    if (
                        path.name not in KEEP_RESULT_FILENAMES
                        and relative_path not in KEEP_RESULT_RELATIVE_PATHS
                    ):
                        removals.append(path)
    return removals, len(cases)


def copy_outputs(source: Path, dest: Path, force: bool) -> None:
    if dest.exists():
        if not force:
            raise SystemExit(f"destination already exists: {dest}\nUse --force to replace it.")
        validate_force_dest(source, dest)
        shutil.rmtree(dest)

    shutil.copytree(source, dest, symlinks=True)


def main() -> int:
    args = parse_args()
    source = args.source.expanduser().resolve()
    dest = args.dest.expanduser().resolve()

    if not source.is_dir():
        raise SystemExit(f"source is not a directory: {source}")
    if source == dest:
        raise SystemExit("destination must be different from source")
    if is_relative_to(dest, source):
        raise SystemExit("destination must not be inside source")

    root_for_plan = source if args.dry_run else dest
    if args.dry_run:
        removals, case_count = plan_removals(source)
        print(f"Would copy: {source} -> {dest}")
        print(f"Found {case_count} testcase directories.")
        print(f"Would remove {len(removals)} paths from the copy.")
        for path in removals:
            print(path.relative_to(source))
        return 0

    copy_outputs(source, dest, args.force)
    removals, case_count = plan_removals(root_for_plan)
    removed = 0
    for path in removals:
        removed += int(remove_path(path))

    print(f"Copied: {source} -> {dest}")
    print(f"Found {case_count} testcase directories.")
    print(f"Removed {removed} paths from the copy.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
