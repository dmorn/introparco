#!/bin/bash

DIR=$(dirname "$0")
. $DIR/env.sh

set -e

echo making $@ on $ADDR
ssh $ADDR "source /etc/profile; module load cuda-10.2 gcc-6.5.0 && make -C ${HOSTREL} $@"
scp $ADDR:$HOSTREL/$1 .
