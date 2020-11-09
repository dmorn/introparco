#!/bin/sh

USER=dmorandini
HOST=slurm-ctrl.inf.unibz.it
ADDR=${USER}@${HOST}

export CMD=benchmark

export REV=${REV:-$(git rev-parse --short HEAD)}
export RELNAME=release-${REV}
export RELARCHIVE=${RELNAME}.tar.gz

SRC=src
HOSTREL=./${RELNAME}

(cd ${SRC} && make release && mv ${RELARCHIVE} ..)
scp ${RELARCHIVE} ${ADDR}:.
ssh ${ADDR} "rm -r ${HOSTREL} 2>/dev/null"
ssh ${ADDR} "mkdir -p ${HOSTREL} 2>/dev/null"
ssh ${ADDR} "tar -zxf ${RELARCHIVE} -C ${HOSTREL}"
ssh ${ADDR} "rm ${RELARCHIVE}"

echo 🚀 ${ADDR}:${HOSTREL}
