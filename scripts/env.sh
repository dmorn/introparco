#!/bin/bash

USER=${USER:-dmorandini}
HOST=${HOST:-slurm-ctrl.inf.unibz.it}
ADDR=${USER}@${HOST}

export REV=${REV:-$(git rev-parse --short HEAD)}
export RELNAME=archive-${REV}
export ARCHIVE=${RELNAME}.tgz

HOSTREL=./src/labs/${RELNAME}
