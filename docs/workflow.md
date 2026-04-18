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
| Non-trivial refactor | `refactor/name` |
| Experimental feature | `feat/name` |
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

---

## Running Tests

Tests use [Criterion](https://criterion.readthedocs.io).

```sh
make test                                        # run all suites
./test_runner --filter entry_create/*            # run one suite
./test_runner --filter entry_create/copies_all_fields  # run one test
```
