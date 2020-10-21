#!/bin/sh

CTX=${CTX:?"give some experiment context/short description to identify this experiment among the others"}
INPUTFILE=${INPUTFILE:-input}
N=${N:-1}
THREADS=${THREADS:-4}

export OMP_NUM_THREADS=${THREADS}

cd src; make clean >/dev/null
make >/dev/null
cd ..

for i in $(seq $N); do
	./src/benchmark -12 -c ${CTX} $(cat ${INPUTFILE})
done
