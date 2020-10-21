#!/bin/sh

export REV=$(git rev-parse --short HEAD)

CTX=${CTX:?"give some experiment context/short description to identify this experiment among the others"}
INPUTFILE=${INPUTFILE:-input}

make deploy >/dev/null

N=${N:-1}
THREADS=${THREADS:-4}

export ERR=std.err
export OUT=std.out

export JOB="#!/bin/bash

#SBATCH --output=${OUT}
#SBATCH --error=${ERR}

#SBATCH --partition training
#SBATCH --gres=gpu
#SBATCH --mem-per-cpu=4gb
#SBATCH --nodes 1
#SBATCH --time=00:01:00
#SBATCH --ntasks=1

export OMP_NUM_THREADS=${THREADS}
srun -N 1 ./benchmark-${REV} -12c ${CTX} $(cat ${INPUTFILE})
"

for i in $(seq $N); do
	./remotesbatch.sh
done
