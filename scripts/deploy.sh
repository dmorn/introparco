#!/bin/sh

#set -e

USER=${USER:-dmorandini}
HOST=${HOST:-slurm-ctrl.inf.unibz.it}
ADDR=${USER}@${HOST}

export REV=${REV:-$(git rev-parse --short HEAD)}
export RELNAME=release-${REV}
export RELARCHIVE=${RELNAME}.tar.gz

DIR=$(dirname "$0")
HOSTREL=./src/labs/${RELNAME}

(cd ${DIR}/.. && make -i clean && make archive mv ${RELARCHIVE} $DIR)
scp ${DIR}/${RELARCHIVE} ${ADDR}:.
ssh ${ADDR} "rm -r ${HOSTREL} 2>/dev/null"
ssh ${ADDR} "mkdir -p ${HOSTREL} 2>/dev/null"
ssh ${ADDR} "tar -zxf ${RELARCHIVE} -C ${HOSTREL}"

rm ${DIR}/${RELARCHIVE}
ssh ${ADDR} "rm ${RELARCHIVE}"

echo 🚀 ${ADDR}:${HOSTREL}
