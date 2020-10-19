#!/bin/sh
N=$1
shift

for i in `seq $N`; do $@; done
