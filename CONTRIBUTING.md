# Contributing

This document describes how our group works together on this repository.

## 1. Tasks are tracked as GitHub Issues
- Every piece of work (feature, bug fix, test, docs) starts as an Issue.
- Assign yourself to an Issue before starting it, so no two people work on the same thing.
- Use labels: `bug`, `feature`, `tests`, `build`, `ci`, `docs`.

## 2. One branch per Issue
- Never commit directly to `main` (it is protected).
- Create a branch from an up-to-date `main`:
      git checkout main
      git pull
      git checkout -b <type>/<issue-number>-<short-description>
- Branch name examples:
  - `feature/3-parse-board-win-check`
  - `fix/5-out-of-bounds-moves`
  - `test/7-diagonal-win-tests`
  - `ci/9-github-actions`
  - `docs/2-readme-rules`

## 3. Commit messages
- Make small commits that each do one thing.
- Format: `<type>: <what changed, in the imperative>`
  - `feat: implement row and column checks in parseBoard`
  - `fix: re-prompt player after an illegal move`
  - `test: add tests for both diagonal wins`
  - `build: add CMake target for test executable`
  - `docs: describe win conditions in README`
- Reference the Issue where relevant, e.g. `fix: bounds-check moves (#5)`.

## 4. Pull Requests
- Push your branch and open a PR into `main`.
- Write `Closes #<issue-number>` in the PR description, so the Issue closes automatically on merge.
- Each PR needs **at least one approving review from another group member** before merging.
- CI must pass (build + all tests green) before merging.
- The reviewer checks: the code builds, tests pass, the change matches the Issue, and the code is readable.
- Merge using **Squash and merge** or **Merge commit** (we agree to use: ________).
- Delete the branch after merging.

## 5. Keeping up to date
- Before opening a PR, update your branch with the latest `main`:
      git checkout main && git pull
      git checkout <your-branch> && git merge main
- Fix any merge conflicts locally, re-run the tests, then push.

## 6. Code style
- Build and run the tests locally before pushing (see README for build instructions).
- Every new function or bug fix should come with at least one test.
