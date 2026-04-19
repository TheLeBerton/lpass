# Workflow

## Commands

```sh
make          # build the binary → ./lpass
make test     # build and run all tests → ./test_runner
make re       # full rebuild
make clean    # remove object files
make fclean   # remove object files + binaries
```

## Git

### Branches

| Case | Branch |
|------|--------|
| Normal work | `master` directly |
| Non-trivial feature | `feature/name` → PR |
| Non-trivial refactor | `refactor/name` → PR |
| Experimental | `feat/name` |
| Hotfix | `master` directly |

### Commit messages

```
feat:     new feature
fix:      bug fix
refactor: change without new feature
test:     add or modify tests
docs:     documentation
chore:    makefile, dependencies, config
```

One commit per logical change — not per file.

### Pull Requests

Open a PR when working on a `feature/` or `refactor/` branch. Link the related issue in the PR description. Merge into `master` once done.

---

## GitHub Issues

### Labels

| Label | Usage |
|-------|-------|
| `feat` | New feature or functionality |
| `bug` | Something isn't working |
| `refactor` | Code restructure without behavior change |
| `test` | Adding or fixing tests |
| `docs` | Documentation improvements |
| `security` | Encryption, keys, or sensitive data |
| `design` | Architecture or API design discussion |
| `build` | Makefile, compilation, install |

### Milestones

| Milestone | Description |
|-----------|-------------|
| `MVP` | Minimum viable product — save and retrieve securely |
| `v1.0` | Full release — 6 commands working, installable, documented |

### Sub-issues

Parent issues describe a feature with acceptance criteria. Sub-issues (or prerequisite links) break it into smaller independent tasks assigned to the same milestone.

---

## Running Tests

Tests use [Criterion](https://criterion.readthedocs.io).

```sh
make test                                        # run all suites
./test_runner --filter entry_create/*            # run one suite
./test_runner --filter entry_create/copies_all_fields  # run one test
```
