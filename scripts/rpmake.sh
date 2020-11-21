#!/bin/bash

DIR=$(dirname "$0")
. $DIR/env.sh

set -e

echo  🛠   $@ on $ADDR

ssh $ADDR  $(cat << EOF
	source /etc/profile; module load cuda-10.2 gcc-6.5.0 && \
	make -C ${HOSTREL} -i clean-nvprof && \
	make -C ${HOSTREL} $@
EOF
)

REPORTS=reports/${RELNAME}
mkdir -p $REPORTS
scp $ADDR:$HOSTREL/$1 ${REPORTS}
less ${REPORTS}/$1
