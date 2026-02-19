# Coverage report notes (genhtml / lcov)

The L1 pipeline generates an lcov/genhtml HTML report even if some tests fail.

## Where the report is
- Main entry: `entservices-appgateway-34/coverage/index.html`

## How to interpret per-file coverage %
`genhtml` presents coverage in a few places:

1. **Overall totals (project-level)**  
   Open `coverage/index.html`. Near the top/bottom it shows totals like:
   - **Lines**
   - **Functions**
   - **Branches**

2. **Per-directory / per-file table**
   On the same `coverage/index.html`, there is a table listing directories/files.  
   The columns typically include:
   - Lines (hit/total + %)
   - Functions (hit/total + %)
   - Branches (hit/total + %)

   The **percentage shown per row** is the per-file (or per-directory) coverage for that metric.

3. **Inside a single file view**
   Click a file from the table. At the top of the file’s page, genhtml shows that file’s:
   - line coverage %
   - function coverage %
   - branch coverage %

## Common gotchas
- A low per-file % can be caused by:
  - template-heavy headers, inline functions, or generated code being included in the capture
  - tests not executing certain paths (early returns / error handling)
- If tests fail, the report may still be usable, but it represents coverage up to the point tests executed.
  Failures can reduce coverage because later tests/cases did not run.
