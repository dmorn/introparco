#!/bin/sh

CTX=${CTX:?"give some experiment context/short description to identify this experiment among the others"}
INPUTFILE=${INPUTFILE:-benchinput.dat}

./benchmark -12c ${CTX} $(cat ${INPUTFILE})
