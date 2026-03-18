#!/usr/bin/env python3

import argparse
import json
import os
import re
import sys
from pathlib import Path
from openai import OpenAI

BASE_DIR = Path(__file__).resolve().parent
PROMPTS_DIR = BASE_DIR / "prompts"
CVES_DIR = BASE_DIR / "cves"
OUTPUTS_DIR = BASE_DIR / "outputs"
CONFIGS_DIR = BASE_DIR / "configs"
LOGS_DIR = BASE_DIR / "logs"

EXPLAIN1_TEMPLATE_PATH = PROMPTS_DIR / "prompt1.txt"
EXPLAIN2_TEMPLATE_PATH = PROMPTS_DIR / "prompt2.txt"
LLM_CONFIG_PATH = CONFIGS_DIR / "llm_config.json"
CHAT_HISTORY_PATH = LOGS_DIR / "chat_history.json"

class Client:
    def __init__(self):
        with open(LLM_CONFIG_PATH, "r", encoding="utf-8") as f:
            llm_config = json.load(f)

        self.model = llm_config['selected_model']
        api_key = llm_config['models'][self.model]['api_key']
        base_url = llm_config['models'][self.model]['base_url']
        self.client = OpenAI(api_key=api_key, base_url=base_url)
        self.messages = []
        self.usage = None
        self.log_file = str(CHAT_HISTORY_PATH)

        self.messages.append(
            {
                "role": "system",
                "content": "You are a precise security analysis assistant.",
            },
        )

    def chat(self, user_input: str) -> str:
        self.messages.append(
            {
                "role": "user",
                "content": user_input,
            }
        )

        resp = self.client.chat.completions.create(
            model=self.model,
            messages=self.messages,
        )

        self.usage = resp.usage

        reply = resp.choices[0].message.content

        self.messages.append(
            {
                "role": "assistant",
                "content": reply,
            }
        )

        return reply

    def __del__(self):
        try:
            with open(self.log_file, "w", encoding="utf-8") as f:
                print(f"[API usage] total tokens: {self.usage.total_tokens}")
                json.dump(self.messages, f, indent=2)
        except Exception as exc:
            print(f"Failed to write chat history to log file: {exc}", file=sys.stderr)


def read_file(path: str) -> str:
    with open(path, "r", encoding="utf-8") as f:
        return f.read()

def write_file(path: str, content: str) -> bool:
    try:
        with open(path, "w", encoding="utf-8") as f:
            f.write(content)
            if not content.endswith("\n"):
                f.write("\n")
        return True
    except OSError as exc:
        print(f"Failed to write file: {path} ({exc})", file=sys.stderr)
        return False


def load_prompt_template(path: Path) -> str | None:
    try:
        return path.read_text(encoding="utf-8")
    except OSError as exc:
        print(f"Failed to read prompt template: {path} ({exc})", file=sys.stderr)
        exit(1)

def load_cwe_prompt(cwe: str, location: str) -> str:
    with open(PROMPTS_DIR / "cwe-prompts.json", "r", encoding="utf-8") as f:
        cwe_prompts = json.load(f)
    m = re.match(r"CWE-(\d+)", cwe)
    if not m:
        print(f"Invalid CWE ID format: {cwe}", file=sys.stderr)
        exit(1)
    cwe_id = m.group(1)
    if cwe_id in cwe_prompts:
        cwe_prompt = cwe_prompts[cwe_id]
        return cwe_prompt.format(location=location)
    else:
        return ""

def parse_cve_file(content: str) -> tuple[str, str] | None:
    json.loads(content)
    keys = ["CVE-ID", "CWE-ID", "version", "patch", "location"]
    for key in keys:
        if key not in content:
            print(f"Missing key in CVE file: {key}", file=sys.stderr)
            print("Expected keys: 'CVE-ID', 'CWE-ID', 'version', 'patch', 'location'", file=sys.stderr)
            exit(1)
    cwe_id = json.loads(content)["CWE-ID"]
    vulnerability_location = json.loads(content)["location"]
    return cwe_id, vulnerability_location


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Run two-stage CVE workflow. The input directory must contain "
            "snippet.txt, context.txt, and cve.txt."
        )
    )
    parser.add_argument(
        "input_dir",
        help="Directory containing snippet.txt, context.txt, and cve.txt.",
    )
    return parser.parse_args()


def resolve_input_paths(input_dir: Path) -> tuple[Path, Path, Path] | None:
    if not input_dir.exists():
        print(f"Input directory does not exist: {input_dir}", file=sys.stderr)
        exit(1)
    if not input_dir.is_dir():
        print(f"Input path is not a directory: {input_dir}", file=sys.stderr)
        exit(1)

    cve_path = input_dir / "cve.json"
    snippet_path = input_dir / "snippet.txt"
    context_path = input_dir / "context.txt"

    missing: list[str] = []
    for path in (snippet_path, context_path, cve_path):
        if not path.is_file():
            missing.append(path.name)
    if missing:
        missing_display = ", ".join(missing)
        print(
            f"Input directory is missing required files: {missing_display}",
            file=sys.stderr,
        )
        exit(1)

    return snippet_path, context_path, cve_path


def main() -> int:
    args = parse_args()

    input_dir = CVES_DIR / args.input_dir
    resolved_inputs = resolve_input_paths(input_dir)
    snippet_path, context_path, cve_path = resolved_inputs

    output_dir = OUTPUTS_DIR / args.input_dir
    output_dir.mkdir(parents=True, exist_ok=True)
    LOGS_DIR.mkdir(parents=True, exist_ok=True)

    snippet = read_file(str(snippet_path)).strip()
    context = read_file(str(context_path)).strip()
    cve_file_content = read_file(str(cve_path))
    cwe_id, location = parse_cve_file(cve_file_content)

    explain1_template = load_prompt_template(EXPLAIN1_TEMPLATE_PATH)
    explain2_template = load_prompt_template(EXPLAIN2_TEMPLATE_PATH)
    cwe_prompt = load_cwe_prompt(cwe_id, location)

    explain1_prompt = explain1_template.format(
        cwe_id=cwe_id,
        location=location,
        snippet=snippet,
        cwe_prompt=cwe_prompt
    )

    explain2_prompt = explain2_template.format(
        context=context,
    )

    client = Client()

    explain1 = client.chat(explain1_prompt)
    explain2 = client.chat(explain2_prompt)

    write_file(str(output_dir / "explain1.txt"), explain1)
    write_file(str(output_dir / "explain2.txt"), explain2)

    return 0

if __name__ == "__main__":
    raise SystemExit(main())
