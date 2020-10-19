:attention please:
This content is only relevant for my fellow colleaques of the SEIS
master @ UNIBZ.

Legenda:
`line`              -> code
``` ...lines... ``` -> multi-line code

---
Local testing:
```
	cd src
	make
	./benchmark -12
```
Notes:
 - run `./benchmark` for usage help
 - `./benchmark > file.csv` can be used to pipe the results to file.csv
 - `./benchmark -c <name>` can be used to change the context column,
   I use it to identify experiments (i.e. mac+opt, slurmctl+opt+vec,...)

---
Remote testing:
```
	# compiles a copy of benchmark in the server. If you need to
	# change compilation related things, edit src/makefile.
	make deploy

	# Read the revision from previous command's output, or
	# run `git rev-parse --short HEAD`
	env REV=<revision> CTX=<passed as argument to benchmark -c> ./scripts/remotebench.sh
```

---
Utils:
./scripts/repeat.sh can be used to repeat a measurement (or any command actually). Use it like:
```
	./scripts/repeat.sh 5 "env CTX=slurmctl+vec+ivdep+opt REV=183c82c ./scripts/remotebench.sh" >> R/datasets/data.csv
```

