# figure out the compilation options
# requires the architecture name as an argument

PROC_NAME=$1

if [ "$PROC_NAME" = "x64" ]; then
	# need to determine the vector level on this machine
	AllFlags=$(cat /proc/cpuinfo | grep flags | grep fpu | head -n 1)
	CanAvx=0
	CanAvx512=0
	for flag in $AllFlags
	do
		if [ "$flag" = "avx2" ]; then
			CanAvx=1
		fi
		# TODO what's the actual flag?
#		if [ "$flag" = "avx512" ]; then
#			CanAvx=1
#		fi
	done
	SSEDEF=""
	if [ "$CanAvx512" = "1" ]; then
		SSEDEF="-DWHODUN_X64_AVX512=1"
	elif [ "$CanAvx" = "1" ]; then
		SSEDEF="-mavx2 -DWHODUN_X64_AVX=1"
	fi
	
	# output the options
	echo -g -O2 -Wall -Wpedantic -std=c99 -pthread -fPIC $SSEDEF
else
	echo -g -O0 -Wall -Wpedantic -pthread
fi



