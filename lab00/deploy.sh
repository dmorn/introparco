#!/bin/sh

USER=dmorandini
HOST=slurm-ctrl.inf.unibz.it
ADDR=${USER}@${HOST}

export CMD=benchmark

export REV=${REV:-$(git rev-parse --short HEAD)}
export RELNAME=release-${REV}
export RELARCHIVE=${RELNAME}.tar.gz

SRC=src
EXEC=${CMD}-${REV}

HOSTDIST=dist-$(basename $(pwd))
HOSTREL=${HOSTDIST}/${RELNAME}

(cd ${SRC} && make release)

ssh ${ADDR} "rm -r ${HOSTREL}; mkdir -p ${HOSTREL}"
scp ${SRC}/${RELARCHIVE} ${ADDR}:.
ssh ${ADDR} "tar -zxf ${RELARCHIVE} -C ${HOSTREL}; rm ${RELARCHIVE}"
ssh ${ADDR} "cd ${HOSTREL}; make && mv ${CMD} ../../${EXEC}"
echo ${EXEC} deployed!
