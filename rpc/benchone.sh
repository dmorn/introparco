#!/bin/bash

# makes one benchmark. Stored stdout, stderr, and nvprof output inside a folder
# which can be downloaded later.  prints the location of the folder containing
# the data.

set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
. $DIR/../scripts/env.sh

function usage() {
	echo "usage: $0 [executable name] [array size]"
	exit 2
}

[ $# -ne 2 ] && usage
[ -z $1 ] && usage
[ $2 -lt 0 ] && {
	echo array size should be an integer greather than 0
	usage
}

TICKET=$(uuidgen)
REPORTS=reports/$1.$TICKET
REPORT=$REPORTS/report.nvprof
NARRAY=$2
EXEC=$HOSTREL/bin/$1
SRUN=$HOSTREL/scripts/srun.sh

ssh -T $ADDR << EOF
	# this is very tight to our system details.
	source /etc/profile
	module load cuda-10.2 gcc-6.5.0

	mkdir -p $REPORTS
	echo narray=$NARRAY > $REPORTS/setup.txt
	echo exec=$EXEC >> $REPORTS/setup.txt

	$SRUN nvprof -o $REPORT --cpu-profiling on $EXEC $NARRAY && \
	nvprof -i $REPORT --cpu-profiling-mode top-down --print-gpu-trace 2> $REPORTS/report.nvprof.txt
EOF

echo $REPORTS | pbcopy
echo 🎟 : $TICKET
echo download command:

DL="scp -r $ADDR:./$REPORTS/*.txt $REPORTS"
echo $DL
echo $DL | pbcopy
echo copied!

