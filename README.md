## 项目简介

本项目提供了一组用于评估大模型漏洞解释能力的测试集。每个测试用例对应一个上下文长度适中的 CVE 实例，旨在对比大模型在“无上下文”和“有上下文”两种条件下对漏洞的理解与解释能力。

在测试过程中，大模型可以通过 VAST DB 获取与漏洞相关的上下文信息，从而生成更加完整和准确的漏洞分析结果。

---

## 项目结构

项目目录结构如下：

- `cves/`：测试用例集合，每个子目录对应一个 CVE
  - `snippet.txt`：漏洞相关的原始代码片段
  - `context.txt`：通过数据库检索得到的漏洞上下文信息
  - `cve.json`：漏洞元信息，包括：
    - CVE-ID  
    - CWE-ID  
    - 所属项目  
    - 受影响版本  
    - patch  
    - 漏洞位置等  
  - `query.txt`：用于从数据库中获取漏洞上下文的参考查询语句

- `test.py`：测试脚本  
  用于调用大模型，在以下两种条件下生成漏洞解释：
  1. 无上下文信息  
  2. 使用 VAST DB 提供的上下文信息  

- `configs/`：模型配置文件，用于指定测试时所使用的大模型

- `outputs-example/`：参考实验结果
  -  `explain1.txt`：无上下文条件下的漏洞解释  
  -  `explain2.txt`：带上下文条件下的漏洞解释  

---

## 使用说明

1. 按照示例配置文件完成配置：
    ```bash
   cp configs/llm_config.json.example configs/llm_config.json
    ```
2. 运行测试脚本：
   ```bash
   python test.py <CVE-ID>
   ```
   例如：
   ```bash
   python test.py 2026-28688
   ```
3. 在 `outputs/` 目录中查看生成结果