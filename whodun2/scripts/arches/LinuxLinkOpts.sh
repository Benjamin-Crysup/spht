# figure out options for the linker
# requires the architecture name as an argument

PROC_NAME=$1

if [ "$PROC_NAME" = "x64" ]; then
	echo -g -O0 -Wall -Wpedantic -std=c99 -pthread -z noexecstack
else
	echo -g -O0 -Wall -Wpedantic -pthread
fi

