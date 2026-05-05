You are analyzing a vulnerable C/C++ test case. You have normal text-search/code-reading tools and must use VAST DB location tools to identify or validate relevant code context.

CWE-ID:
{cwe_id}

Known vulnerable location:
{location_text}

Analyze the vulnerable code in this directory. Avoid guessing beyond what the code supports. Treat the known vulnerable location text as anchors, not as a guaranteed chronological source-to-sink ordering; inspect the code to determine the actual trigger order.

# Workflow

1. Use text search/read tools only enough to locate the known vulnerable anchors in source code.
2. Before writing VAST DB Cypher queries, load the `write-cypher` skill. Load the `understand-mlir-schema` skill when you need schema details to construct queries or interpret returned records.
3. Treat VAST DB as a code navigation tool. Starting from the current anchors, use VAST DB to find relevant symbol, caller, callee, def, or use locations.
4. Alternate between VAST DB and source reading: query VAST DB for the next interesting locations, inspect those source locations with text search/read tools, then use what you learned as anchors for the next VAST DB query.
5. Execute at least one `run_cypher` query. If a VAST DB query fails or returns no complete call-chain/data-flow path, try narrower VAST DB navigation queries before relying only on text search/read tools.

# Output Schema

Return only the final explanation in this exact structure:

## Root Cause

Write one concise paragraph explaining the vulnerability root cause. Mention the vulnerable object/value, why it becomes unsafe, and why the known vulnerable location can trigger the CWE.

## Trigger Path

List every function stack frame on the vulnerability trigger path, from external/top-level entry toward the vulnerable operation. Each frame must include file name, function name, and line number. For each frame, briefly explain how control or data flows to the next frame.

Use this format for each frame:

1. `file:line` `function_name`
   - Describe the relevant condition, argument, object state, or data/control transfer.

If you cannot prove a stack frame from either the code or VAST DB evidence, say so explicitly rather than inventing one. Do not output placeholder text such as `file:line` or `function_name`.
