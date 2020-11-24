#!/bin/sh

# tars the project and scp's it to a remote system, untars, makes
# everything and cleans up archives.

set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
. $DIR/../scripts/env.sh

make -C $DIR/.. -i clean 1>/dev/null
make -C $DIR/.. ${ARCHIVE}
function cleanup() {
	rm -rf ${DIR}/../${ARCHIVE}
}
trap cleanup EXIT

scp ${DIR}/../${ARCHIVE} ${ADDR}:.

ssh -T $ADDR << EOF
	# this is very tight to our system details.
	source /etc/profile
	module load cuda-10.2 gcc-6.5.0

	rm -rf ${HOSTREL}
	mkdir -p ${HOSTREL}
	tar -zxf ${ARCHIVE} -C ${HOSTREL}
	make -C ${HOSTREL} all
	rm -rf ${ARCHIVE}
EOF

echo 🚀 : ${ADDR}:${HOSTREL}
