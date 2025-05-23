
set -e

WHODUN_ROOT=../whodun2
PROC_NAME=$($WHODUN_ROOT/scripts/arches/LinuxFigureArch.sh)
WHODUN_INC=$WHODUN_ROOT/builds/inc_$PROC_NAME''_darwin
WHODUN_BIN=$WHODUN_ROOT/builds/bin_$PROC_NAME''_darwin

# figure out the options (focus on baseline systems)

case "$PROC_NAME" in
	(x64)
		COMP_OPTS="-g -O0 -Wall -Wpedantic -std=c99 -pthread -fPIC"
		LINK_OPTS="-g -O0 -Wall -Wpedantic -std=c99 -pthread"
		;;
	(*)
		COMP_OPTS="-g -O0 -Wall -Wpedantic -pthread"
		LINK_OPTS="-g -O0 -Wall -Wpedantic -pthread"
		;;
esac
BASIC_PROG_LIBS="-ldl"

# make the folders

OBJDIR="builds/obj_$PROC_NAME""_darwin"
BINDIR="builds/bin_$PROC_NAME""_darwin"

rm -rf $OBJDIR
rm -rf $BINDIR

mkdir -p $OBJDIR
mkdir -p $BINDIR


# *******************************************************************
# main program

gcc $COMP_OPTS -I$WHODUN_INC -Isource -c -o $OBJDIR/main.o source/main.c
gcc $COMP_OPTS -I$WHODUN_INC -Isource -c -o $OBJDIR/spht.o source/spht.c
gcc $COMP_OPTS -I$WHODUN_INC -Isource -c -o $OBJDIR/flippy.o source/flippy.c
gcc $COMP_OPTS -I$WHODUN_INC -Isource -c -o $OBJDIR/plinko.o source/plinko.c
gcc $COMP_OPTS -I$WHODUN_INC -Isource -c -o $OBJDIR/drift.o source/drift.c

gcc $LINK_OPTS -o $BINDIR/spht $OBJDIR/*.o -L$WHODUN_BIN -lwhodun $BASIC_PROG_LIBS

