#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
. $DIR/env.sh

set -e

ssh $ADDR  $(cat << EOF
	source /etc/profile; module load cuda-10.2 gcc-6.5.0 && \
	make -C ${HOSTREL} -i clean-nvprof >&2 && \
	make -C ${HOSTREL} $@ >&2 && \
	cat $HOSTREL/$1
EOF
)
