#!/bin/bash

USER=${USER:-dmorandini}
HOST=${HOST:-slurm-ctrl.inf.unibz.it}
ADDR=${USER}@${HOST}

REV=${REV:-$(git rev-parse --short HEAD)}
RELNAME=archive-${REV}
ARCHIVE=${RELNAME}.tgz

HOSTREL=./src/labs/${RELNAME}
