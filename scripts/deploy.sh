#!/bin/sh

set -e

DIR=$(dirname "$0")
. $DIR/env.sh

(cd ${DIR}/.. && make -i clean && make ${ARCHIVE} && mv ${ARCHIVE} $DIR)
scp ${DIR}/${ARCHIVE} ${ADDR}:.
ssh ${ADDR} "rm -fr ${HOSTREL} 2>/dev/null"
ssh ${ADDR} "mkdir -p ${HOSTREL} 2>/dev/null"
ssh ${ADDR} "tar -zxf ${ARCHIVE} -C ${HOSTREL}"

rm ${DIR}/${ARCHIVE}
ssh ${ADDR} "rm ${ARCHIVE}"

echo 🚀 ${ADDR}:${HOSTREL}
