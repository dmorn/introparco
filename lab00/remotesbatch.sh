#!/bin/sh

# SSH configuration. Authentication should be made with keys.

USER=dmorandini
HOST=slurm-ctrl.inf.unibz.it
ADDR=${USER}@${HOST}

ERR=${ERR:?"choose a filename for stderr file. Random is OK"}
OUT=${OUT:?"choose a filename for stdout file. Random is OK"}
JOB=${JOB:?"must hold a valid sbatch job"}

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
