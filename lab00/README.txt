:attention please:
This content is only relevant for my fellow colleaques of the SEIS
master @ UNIBZ.


Probably out-of-date usage from ./src/benchmark:
```
./benchmark
error: no algorithm was specified

usage: ./benchmark <flags> <N>
note: at least one algo has to be specified

N: list of array sizes. Each n will be a separate measurement
-1 execute random sum algorithm
-2 execute sum prefix algorithm
-c: change ctx identifier (defaults to local)
-d turn on algorithmic specific debug prints
```

Measurements can be made by
1. Editing things in src/
2. Measuring performance on localhost
3. Measuring performance on remote

For the 2nd task the `mkbench-local.sh` script can be exploited. I
use it like this:
```
# src/ edit phase, then
% env CTX=mac+omppfor+opt N=10 ./mkbench-local.sh >> data.csv
```
Where:
- N is the number of times the same task is executed, and
- CTX will be the first column in the produced data.

For the 3rd tasks, the remote version of the script above is
available:
```
% env CTX=slurm+vec+opt N=10 ./mkbench-remote.sh >> data.csv
```

Checkout the scripts for configuring things, in particular
`remotesbatch.sh` for SSH access configuration to the cluster.

Last but not least, data is csv encoded, with header (not present)
```
context,algorithm,alloc() time, free() time, execution time
```
The .mkplot.R produces the `plot.pdf` file when fed with data
```
% ./mkplot.R < measurements/data.csv
```
Extra: `grep` data before feeding mkplot for filtering irrelevant experiments

