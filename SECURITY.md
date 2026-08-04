# Security Policy

## 📦 About this repository

**BNU CS Archive** is a personal academic archive of coursework, notes, and student projects (e.g. `ClassSync AI`, `DailyKhata`, database and web-development lab exercises). It is **not a maintained software product or library**, and most of the code it contains was written for coursework, learning, and one-off assignments rather than production use.

Because of that, this policy is scoped narrower than a typical software project's security policy — it focuses on **data exposure** and **archive integrity** rather than ongoing vulnerability patching for every embedded project.

## ✅ Supported Scope

| Area | Coverage |
|---|---|
| Course materials (slides, PDFs, docs) | Not applicable — static reference content |
| Student-authored projects (e.g. ClassSync AI, DailyKhata) | Best-effort only — these are course/learning projects, not maintained software |
| Vendored/third-party code (e.g. `node_modules`, cloned cohort repos) | Not maintained here — please report upstream to the original project |

There is no guaranteed patch turnaround, as this repository is not under active security maintenance the way a production application would be.

## 🚨 Reporting a Concern

If you discover any of the following, please report it **privately** rather than through a public issue:

- 🔑 **Exposed credentials or secrets** (API keys, tokens, database connection strings, `.env`-style values) accidentally committed within a project folder
- 🧑 **Personal or sensitive information** that shouldn't be public (e.g. private contact details beyond what's expected in an academic report)
- ⚠️ **A genuine, exploitable vulnerability** in one of the student-built applications (e.g. `ClassSync AI`, the `mongo-express-test` CRUD app, or `DailyKhata` prototypes) that could affect someone running that code themselves

### How to report

- Open a **private security advisory** via this repository's GitHub Security tab (`Security` → `Report a vulnerability`), if enabled, **or**
- Open a regular issue with **minimal detail** (e.g. "Possible exposed credential in `<path>` — details sent privately") and avoid posting the sensitive value itself, so it can be triaged and removed from history if needed.

Please **do not** post secrets, tokens, or exploit details directly in a public issue or pull request.

## 🔍 What to expect

- Reports involving exposed secrets or personal data will be prioritized for removal/rotation as quickly as possible.
- Reports about vulnerabilities in course/learning projects will be reviewed on a best-effort basis, since these were built as academic exercises rather than production software and may not receive a formal fix.
- Third-party dependencies vendored inside project folders (e.g. `node_modules`) should be reported to their respective upstream maintainers, not here.

Thank you for helping keep this archive safe and accurate.
