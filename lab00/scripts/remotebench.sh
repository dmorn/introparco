#!/bin/sh

# SSH configuration. Authentication should be made with keys.

USER=dmorandini
HOST=slurm-ctrl.inf.unibz.it
ADDR=${USER}@${HOST}

# Write here your slurm task. Do not change output & error variables.
ERR=std.err
OUT=std.out

PLATFORM=${PLATFORM:=""}
CTX=${CTX:?"variable must be set to a suitable experiment name (usually some short platform id, hw used ecc..)"}
REV=${REV:?"variable must be set to a deployed benchmark revision"}

MIN=1000
MAX=100000
STEP=2000

JOB="#!/bin/bash

#SBATCH --output=${OUT}
#SBATCH --error=${ERR}

#SBATCH --partition training
#SBATCH --gres=gpu
#SBATCH --mem-per-cpu=4gb
#SBATCH --nodes 1
#SBATCH --time=00:01:00
#SBATCH --ntasks=1

srun -N 1 ./benchmark-${REV} -12c ${CTX} $(seq -s ' ' $MIN $STEP $MAX)
"

TMPFILE=$(mktemp)
echo "$JOB" > $TMPFILE
chmod +x $TMPFILE


# Execute the script remotely, waiting for it to complete.
JOBNAME=$(basename ${TMPFILE})
scp $TMPFILE ${ADDR}:. 1>&2
ssh ${ADDR} "sbatch -W ${JOBNAME}" 1>&2
ssh ${ADDR} "rm ${JOBNAME}" 1>&2

# Copy error and output files to the stdout and stderr of this script.
scp ${ADDR}:${ERR} $TMPFILE 1>&2
ssh ${ADDR} "rm ${ERR}" 1>&2
cat $TMPFILE >&2

scp ${ADDR}:${OUT} $TMPFILE 1>&2
ssh ${ADDR} "rm ${OUT}" 1>&2
cat $TMPFILE >&1

rm $TMPFILE
