
# Mac is so close to Linux it is PAINFUL.
# And of course it has its own name mangling for assembly.

set -e

PROC_NAME=$(scripts/arches/LinuxFigureArch.sh)

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

INCDIR="builds/inc_$PROC_NAME""_darwin"
OBJDIR="builds/obj_$PROC_NAME""_darwin"
DOCDIR="builds/doc_$PROC_NAME""_darwin"
BINDIR="builds/bin_$PROC_NAME""_darwin"

rm -rf $INCDIR
rm -rf $OBJDIR
rm -rf $DOCDIR
rm -rf $BINDIR

mkdir -p $INCDIR
mkdir -p $OBJDIR
mkdir -p $DOCDIR
mkdir -p $BINDIR

# *******************************************************************
# headers

mkdir $INCDIR/whodun
mkdir $INCDIR/whodun/bulk
mkdir $INCDIR/whodun/formats
mkdir $INCDIR/whodun/formats/genetics
mkdir $INCDIR/whodun/formats/table
mkdir $INCDIR/whodun/parse
mkdir $INCDIR/whodun/stats

cp head/whodun/alloc.h $INCDIR/whodun/alloc.h
cp head/whodun/args.h $INCDIR/whodun/args.h
cp head/whodun/array.h $INCDIR/whodun/array.h
cp head/whodun/class.h $INCDIR/whodun/class.h
cp head/whodun/complex.h $INCDIR/whodun/complex.h
cp head/whodun/contain.h $INCDIR/whodun/contain.h
cp head/whodun/cpu.h $INCDIR/whodun/cpu.h
cp head/whodun/spec/$PROC_NAME/linux/cpuvec.h $INCDIR/whodun/cpuvec.h
cp head/whodun/cpuvecx.h $INCDIR/whodun/cpuvecx.h
cp head/whodun/spec/$PROC_NAME/linux/defs.h $INCDIR/whodun/defs.h
cp head/whodun/ermac.h $INCDIR/whodun/ermac.h
cp head/whodun/error.h $INCDIR/whodun/error.h
cp head/whodun/internat.h $INCDIR/whodun/internat.h
cp head/whodun/math.h $INCDIR/whodun/math.h
cp head/whodun/memmap.h $INCDIR/whodun/memmap.h
cp head/whodun/oshook.h $INCDIR/whodun/oshook.h
cp head/whodun/stream.h $INCDIR/whodun/stream.h
cp head/whodun/string.h $INCDIR/whodun/string.h
cp head/whodun/test.h $INCDIR/whodun/test.h
cp head/whodun/thread.h $INCDIR/whodun/thread.h
cp head/whodun/bulk/mapred.h $INCDIR/whodun/bulk/mapred.h
cp head/whodun/bulk/move.h $INCDIR/whodun/bulk/move.h
cp head/whodun/bulk/sort.h $INCDIR/whodun/bulk/sort.h
cp head/whodun/bulk/tensor.h $INCDIR/whodun/bulk/tensor.h
cp head/whodun/formats/line.h $INCDIR/whodun/formats/line.h
cp head/whodun/formats/genetics/fasta.h $INCDIR/whodun/formats/genetics/fasta.h
cp head/whodun/formats/genetics/fastq.h $INCDIR/whodun/formats/genetics/fastq.h
cp head/whodun/formats/genetics/pileup.h $INCDIR/whodun/formats/genetics/pileup.h
cp head/whodun/formats/table/tsv.h $INCDIR/whodun/formats/table/tsv.h
cp head/whodun/parse/token.h $INCDIR/whodun/parse/token.h
cp head/whodun/stats/math.h $INCDIR/whodun/stats/math.h
cp head/whodun/stats/random.h $INCDIR/whodun/stats/random.h

tar cf $BINDIR/whodunh.tar -C $INCDIR/ whodun

# uncomment if you have doxygen installed
#rm -rf $DOCDIR/html
#( cat Doxyfile ; echo "OUTPUT_DIRECTORY=./builds/doc_"$PROC_NAME"_darwin/" ; echo "STRIP_FROM_PATH=builds/inc_"$PROC_NAME"_darwin" ; echo "INPUT=./builds/inc_"$PROC_NAME"_darwin/" ) | doxygen -
#tar czf $BINDIR/dochtml.tar.gz -C $DOCDIR/ html/


# *******************************************************************
# static sources

mkdir $OBJDIR/static
mkdir $OBJDIR/static/whodun
mkdir $OBJDIR/static/whodun/bulk
mkdir $OBJDIR/static/whodun/formats
mkdir $OBJDIR/static/whodun/formats/genetics
mkdir $OBJDIR/static/whodun/formats/table
mkdir $OBJDIR/static/whodun/parse
mkdir $OBJDIR/static/whodun/stats

gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/alloc.o static/whodun/alloc.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/args.o static/whodun/args.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/array.o static/whodun/array.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/class.o static/whodun/class.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/complex.o static/whodun/complex.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/contain.o static/whodun/contain.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/cpuc.o static/whodun/spec/$PROC_NAME/macos/cpu.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/error.o static/whodun/error.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/internat.o static/whodun/internat.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/math.o static/whodun/math.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/mathc.o static/whodun/spec/$PROC_NAME/macos/math.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/memmap.o static/whodun/memmap.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/oshook.o static/whodun/spec/any/macos/oshook.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/oshfile.o static/whodun/spec/any/linux/oshfile.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/oshmem.o static/whodun/spec/any/linux/oshmem.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/oshmemi.o static/whodun/spec/any/macos/oshmemi.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/oshpanic.o static/whodun/spec/any/linux/oshpanic.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/oshstdio.o static/whodun/spec/any/linux/oshstdio.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/oshthred.o static/whodun/spec/any/linux/oshthred.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/stream.o static/whodun/stream.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/string.o static/whodun/string.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/stringc.o static/whodun/spec/$PROC_NAME/macos/string.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/test.o static/whodun/test.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/thread.o static/whodun/thread.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/bulk/mapred.o static/whodun/bulk/mapred.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/bulk/move.o static/whodun/bulk/move.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/bulk/sort.o static/whodun/bulk/sort.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/bulk/tensor.o static/whodun/bulk/tensor.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/formats/line.o static/whodun/formats/line.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/formats/genetics/fasta.o static/whodun/formats/genetics/fasta.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/formats/genetics/fastq.o static/whodun/formats/genetics/fastq.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/formats/genetics/pileup.o static/whodun/formats/genetics/pileup.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/formats/table/tsv.o static/whodun/formats/table/tsv.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/parse/token.o static/whodun/parse/token.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/stats/math.o static/whodun/stats/math.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/stats/random.o static/whodun/stats/random.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/static/whodun/stats/randomc.o static/whodun/spec/$PROC_NAME/macos/stats/random.c

if [[ "$PROC_NAME" == "oth" ]]; then
	STATICASSO=""
else
	gcc $COMP_OPTS -c -o $OBJDIR/static/whodun/cpus.o static/whodun/spec/$PROC_NAME/macos/cpu.s
	gcc $COMP_OPTS -c -o $OBJDIR/static/whodun/maths.o static/whodun/spec/$PROC_NAME/macos/math.s
	gcc $COMP_OPTS -c -o $OBJDIR/static/whodun/strings.o static/whodun/spec/$PROC_NAME/macos/string.s
	gcc $COMP_OPTS -c -o $OBJDIR/static/whodun/stats/randoms.o static/whodun/spec/$PROC_NAME/macos/stats/random.s
	STATICASSO="$OBJDIR/static/whodun/cpus.o $OBJDIR/static/whodun/maths.o $OBJDIR/static/whodun/strings.o $OBJDIR/static/whodun/stats/randoms.o"
fi

ar rcs $BINDIR/libwhodun.a \
		$OBJDIR/static/whodun/*.o \
		$OBJDIR/static/whodun/bulk/*.o \
		$OBJDIR/static/whodun/formats/*.o \
		$OBJDIR/static/whodun/formats/genetics/*.o \
		$OBJDIR/static/whodun/formats/table/*.o \
		$OBJDIR/static/whodun/parse/*.o \
		$OBJDIR/static/whodun/stats/*.o

# *******************************************************************
# dynamic help

mkdir $OBJDIR/dynamic
mkdir $OBJDIR/dynamic/whodun
mkdir $OBJDIR/dynamic/whodun/bulk
mkdir $OBJDIR/dynamic/whodun/formats
mkdir $OBJDIR/dynamic/whodun/formats/genetics
mkdir $OBJDIR/dynamic/whodun/formats/table
mkdir $OBJDIR/dynamic/whodun/parse
mkdir $OBJDIR/dynamic/whodun/stats

gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/alloc.o dynamic/whodun/alloc.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/args.o dynamic/whodun/args.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/array.o dynamic/whodun/array.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/class.o dynamic/whodun/class.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/complex.o dynamic/whodun/complex.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/contain.o dynamic/whodun/contain.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/cpu.o dynamic/whodun/cpu.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/error.o dynamic/whodun/error.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/internat.o dynamic/whodun/internat.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/math.o dynamic/whodun/math.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/memmap.o dynamic/whodun/memmap.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/oshook.o dynamic/whodun/oshook.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/stream.o dynamic/whodun/stream.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/string.o dynamic/whodun/string.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/test.o dynamic/whodun/test.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/thread.o dynamic/whodun/thread.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/bulk/mapred.o dynamic/whodun/bulk/mapred.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/bulk/move.o dynamic/whodun/bulk/move.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/bulk/sort.o dynamic/whodun/bulk/sort.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/bulk/tensor.o dynamic/whodun/bulk/tensor.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/formats/line.o dynamic/whodun/formats/line.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/formats/genetics/fasta.o dynamic/whodun/formats/genetics/fasta.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/formats/genetics/fastq.o dynamic/whodun/formats/genetics/fastq.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/formats/genetics/pileup.o dynamic/whodun/formats/genetics/pileup.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/formats/table/tsv.o dynamic/whodun/formats/table/tsv.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/parse/token.o dynamic/whodun/parse/token.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/stats/math.o dynamic/whodun/stats/math.c
gcc $COMP_OPTS -I$INCDIR -c -o $OBJDIR/dynamic/whodun/stats/random.o dynamic/whodun/stats/random.c

ar rcs $BINDIR/libwhodundyn.a \
		$OBJDIR/dynamic/whodun/*.o \
		$OBJDIR/dynamic/whodun/bulk/*.o \
		$OBJDIR/dynamic/whodun/formats/*.o \
		$OBJDIR/dynamic/whodun/formats/genetics/*.o \
		$OBJDIR/dynamic/whodun/formats/table/*.o \
		$OBJDIR/dynamic/whodun/parse/*.o \
		$OBJDIR/dynamic/whodun/stats/*.o

# *******************************************************************
# unit testing

mkdir $OBJDIR/test
mkdir $OBJDIR/test/whodun

gcc $COMP_OPTS -I$INCDIR -Itest -c -o $OBJDIR/test/whodun/cpuvec.o test/whodun/cpuvec.c
gcc $COMP_OPTS -I$INCDIR -Itest -c -o $OBJDIR/test/whodun/main.o test/whodun/main.c

gcc $LINK_OPTS -o $BINDIR/testwhodun \
		$OBJDIR/test/whodun/*.o \
		-L$BINDIR -lwhodun $BASIC_PROG_LIBS


