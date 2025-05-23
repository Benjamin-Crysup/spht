
# Makefile is ONLY supported on Linux/unix.

# figure out what flavor of processor this is running on

PROC_NAME := $(shell scripts/arches/LinuxFigureArch.sh)

# figure out the options based on the above

COMP_OPTS := $(shell scripts/arches/LinuxCompOpts.sh $(PROC_NAME))
LINK_OPTS := $(shell scripts/arches/LinuxLinkOpts.sh $(PROC_NAME))

BASIC_PROG_LIBS = -ldl

INCDIR = builds/inc_$(PROC_NAME)_linux
OBJDIR = builds/obj_$(PROC_NAME)_linux
DOCDIR = builds/doc_$(PROC_NAME)_linux
BINDIR = builds/bin_$(PROC_NAME)_linux

# *******************************************************************
# super targets

all : $(BINDIR)/whodunh.tar $(BINDIR)/libwhodun.a $(BINDIR)/libwhodundyn.a $(BINDIR)/testwhodun

doc : $(BINDIR)/dochtml.tar.gz

clean : 
	rm -rf $(INCDIR)
	rm -rf $(OBJDIR)
	rm -rf $(DOCDIR)
	rm -rf $(BINDIR)

$(INCDIR) : 
	mkdir $(INCDIR)
$(OBJDIR) : 
	mkdir $(OBJDIR)
$(DOCDIR) : 
	mkdir $(DOCDIR)
$(BINDIR) : 
	mkdir $(BINDIR)

# *******************************************************************
# headers

$(INCDIR)/whodun : | $(INCDIR)
	mkdir $(INCDIR)/whodun
$(INCDIR)/whodun/bulk : | $(INCDIR)/whodun
	mkdir $(INCDIR)/whodun/bulk
$(INCDIR)/whodun/formats : | $(INCDIR)/whodun
	mkdir $(INCDIR)/whodun/formats
$(INCDIR)/whodun/formats/genetics : | $(INCDIR)/whodun/formats
	mkdir $(INCDIR)/whodun/formats/genetics
$(INCDIR)/whodun/formats/table : | $(INCDIR)/whodun/formats
	mkdir $(INCDIR)/whodun/formats/table
$(INCDIR)/whodun/parse : | $(INCDIR)/whodun
	mkdir $(INCDIR)/whodun/parse
$(INCDIR)/whodun/stats : | $(INCDIR)/whodun
	mkdir $(INCDIR)/whodun/stats

$(INCDIR)/whodun/alloc.h : head/whodun/alloc.h | $(INCDIR)/whodun
	cp head/whodun/alloc.h $(INCDIR)/whodun/alloc.h
$(INCDIR)/whodun/args.h : head/whodun/args.h | $(INCDIR)/whodun
	cp head/whodun/args.h $(INCDIR)/whodun/args.h
$(INCDIR)/whodun/array.h : head/whodun/array.h | $(INCDIR)/whodun
	cp head/whodun/array.h $(INCDIR)/whodun/array.h
$(INCDIR)/whodun/class.h : head/whodun/class.h | $(INCDIR)/whodun
	cp head/whodun/class.h $(INCDIR)/whodun/class.h
$(INCDIR)/whodun/complex.h : head/whodun/complex.h | $(INCDIR)/whodun
	cp head/whodun/complex.h $(INCDIR)/whodun/complex.h
$(INCDIR)/whodun/contain.h : head/whodun/contain.h | $(INCDIR)/whodun
	cp head/whodun/contain.h $(INCDIR)/whodun/contain.h
$(INCDIR)/whodun/cpu.h : head/whodun/cpu.h | $(INCDIR)/whodun
	cp head/whodun/cpu.h $(INCDIR)/whodun/cpu.h
$(INCDIR)/whodun/cpuvec.h : head/whodun/spec/$(PROC_NAME)/linux/cpuvec.h | $(INCDIR)/whodun
	cp head/whodun/spec/$(PROC_NAME)/linux/cpuvec.h $(INCDIR)/whodun/cpuvec.h
$(INCDIR)/whodun/cpuvecx.h : head/whodun/cpuvecx.h | $(INCDIR)/whodun
	cp head/whodun/cpuvecx.h $(INCDIR)/whodun/cpuvecx.h
$(INCDIR)/whodun/defs.h : head/whodun/spec/$(PROC_NAME)/linux/defs.h | $(INCDIR)/whodun
	cp head/whodun/spec/$(PROC_NAME)/linux/defs.h $(INCDIR)/whodun/defs.h
$(INCDIR)/whodun/ermac.h : head/whodun/ermac.h | $(INCDIR)/whodun
	cp head/whodun/ermac.h $(INCDIR)/whodun/ermac.h
$(INCDIR)/whodun/error.h : head/whodun/error.h | $(INCDIR)/whodun
	cp head/whodun/error.h $(INCDIR)/whodun/error.h
$(INCDIR)/whodun/internat.h : head/whodun/internat.h | $(INCDIR)/whodun
	cp head/whodun/internat.h $(INCDIR)/whodun/internat.h
$(INCDIR)/whodun/math.h : head/whodun/math.h | $(INCDIR)/whodun
	cp head/whodun/math.h $(INCDIR)/whodun/math.h
$(INCDIR)/whodun/memmap.h : head/whodun/memmap.h | $(INCDIR)/whodun
	cp head/whodun/memmap.h $(INCDIR)/whodun/memmap.h
$(INCDIR)/whodun/oshook.h : head/whodun/oshook.h | $(INCDIR)/whodun
	cp head/whodun/oshook.h $(INCDIR)/whodun/oshook.h
$(INCDIR)/whodun/stream.h : head/whodun/stream.h | $(INCDIR)/whodun
	cp head/whodun/stream.h $(INCDIR)/whodun/stream.h
$(INCDIR)/whodun/string.h : head/whodun/string.h | $(INCDIR)/whodun
	cp head/whodun/string.h $(INCDIR)/whodun/string.h
$(INCDIR)/whodun/test.h : head/whodun/test.h | $(INCDIR)/whodun
	cp head/whodun/test.h $(INCDIR)/whodun/test.h
$(INCDIR)/whodun/thread.h : head/whodun/thread.h | $(INCDIR)/whodun
	cp head/whodun/thread.h $(INCDIR)/whodun/thread.h
$(INCDIR)/whodun/bulk/mapred.h : head/whodun/bulk/mapred.h | $(INCDIR)/whodun/bulk
	cp head/whodun/bulk/mapred.h $(INCDIR)/whodun/bulk/mapred.h
$(INCDIR)/whodun/bulk/move.h : head/whodun/bulk/move.h | $(INCDIR)/whodun/bulk
	cp head/whodun/bulk/move.h $(INCDIR)/whodun/bulk/move.h
$(INCDIR)/whodun/bulk/sort.h : head/whodun/bulk/sort.h | $(INCDIR)/whodun/bulk
	cp head/whodun/bulk/sort.h $(INCDIR)/whodun/bulk/sort.h
$(INCDIR)/whodun/bulk/tensor.h : head/whodun/bulk/tensor.h | $(INCDIR)/whodun/bulk
	cp head/whodun/bulk/tensor.h $(INCDIR)/whodun/bulk/tensor.h
$(INCDIR)/whodun/formats/line.h : head/whodun/formats/line.h | $(INCDIR)/whodun/formats
	cp head/whodun/formats/line.h $(INCDIR)/whodun/formats/line.h
$(INCDIR)/whodun/formats/genetics/fasta.h : head/whodun/formats/genetics/fasta.h | $(INCDIR)/whodun/formats/genetics
	cp head/whodun/formats/genetics/fasta.h $(INCDIR)/whodun/formats/genetics/fasta.h
$(INCDIR)/whodun/formats/genetics/fastq.h : head/whodun/formats/genetics/fastq.h | $(INCDIR)/whodun/formats/genetics
	cp head/whodun/formats/genetics/fastq.h $(INCDIR)/whodun/formats/genetics/fastq.h
$(INCDIR)/whodun/formats/genetics/pileup.h : head/whodun/formats/genetics/pileup.h | $(INCDIR)/whodun/formats/genetics
	cp head/whodun/formats/genetics/pileup.h $(INCDIR)/whodun/formats/genetics/pileup.h
$(INCDIR)/whodun/formats/table/tsv.h : head/whodun/formats/table/tsv.h | $(INCDIR)/whodun/formats/table
	cp head/whodun/formats/table/tsv.h $(INCDIR)/whodun/formats/table/tsv.h
$(INCDIR)/whodun/parse/token.h : head/whodun/parse/token.h | $(INCDIR)/whodun/parse
	cp head/whodun/parse/token.h $(INCDIR)/whodun/parse/token.h
$(INCDIR)/whodun/stats/math.h : head/whodun/stats/math.h | $(INCDIR)/whodun/stats
	cp head/whodun/stats/math.h $(INCDIR)/whodun/stats/math.h
$(INCDIR)/whodun/stats/random.h : head/whodun/stats/random.h | $(INCDIR)/whodun/stats
	cp head/whodun/stats/random.h $(INCDIR)/whodun/stats/random.h

COMMON_HEADERS = \
	$(INCDIR)/whodun/alloc.h \
	$(INCDIR)/whodun/args.h \
	$(INCDIR)/whodun/array.h \
	$(INCDIR)/whodun/class.h \
	$(INCDIR)/whodun/complex.h \
	$(INCDIR)/whodun/contain.h \
	$(INCDIR)/whodun/cpu.h \
	$(INCDIR)/whodun/cpuvec.h \
	$(INCDIR)/whodun/cpuvecx.h \
	$(INCDIR)/whodun/defs.h \
	$(INCDIR)/whodun/ermac.h \
	$(INCDIR)/whodun/error.h \
	$(INCDIR)/whodun/internat.h \
	$(INCDIR)/whodun/math.h \
	$(INCDIR)/whodun/memmap.h \
	$(INCDIR)/whodun/oshook.h \
	$(INCDIR)/whodun/stream.h \
	$(INCDIR)/whodun/string.h \
	$(INCDIR)/whodun/test.h \
	$(INCDIR)/whodun/thread.h \
	$(INCDIR)/whodun/bulk/mapred.h \
	$(INCDIR)/whodun/bulk/move.h \
	$(INCDIR)/whodun/bulk/sort.h \
	$(INCDIR)/whodun/bulk/tensor.h \
	$(INCDIR)/whodun/formats/line.h \
	$(INCDIR)/whodun/formats/genetics/fasta.h \
	$(INCDIR)/whodun/formats/genetics/fastq.h \
	$(INCDIR)/whodun/formats/genetics/pileup.h \
	$(INCDIR)/whodun/formats/table/tsv.h \
	$(INCDIR)/whodun/parse/token.h \
	$(INCDIR)/whodun/stats/math.h \
	$(INCDIR)/whodun/stats/random.h

$(BINDIR)/whodunh.tar : \
		$(COMMON_HEADERS) \
		| $(BINDIR)
	tar cf $(BINDIR)/whodunh.tar --sort=name -C $(INCDIR)/ whodun

$(DOCDIR)/html/index.html : $(COMMON_HEADERS) | $(DOCDIR)
	rm -rf $(DOCDIR)/html
	( cat Doxyfile ; echo "OUTPUT_DIRECTORY=./builds/doc_"$(PROC_NAME)"_linux/" ; echo "STRIP_FROM_PATH=builds/inc_"$(PROC_NAME)"_linux" ; echo "INPUT=./builds/inc_"$(PROC_NAME)"_linux/" ) | doxygen -

$(BINDIR)/dochtml.tar.gz : $(DOCDIR)/html/index.html | $(BINDIR)
	tar czf $(BINDIR)/dochtml.tar.gz -C $(DOCDIR)/ html/


# *******************************************************************
# static sources

$(OBJDIR)/static : | $(OBJDIR)
	mkdir $(OBJDIR)/static
$(OBJDIR)/static/whodun : | $(OBJDIR)/static
	mkdir $(OBJDIR)/static/whodun
$(OBJDIR)/static/whodun/bulk : | $(OBJDIR)/static/whodun
	mkdir $(OBJDIR)/static/whodun/bulk
$(OBJDIR)/static/whodun/formats : | $(OBJDIR)/static/whodun
	mkdir $(OBJDIR)/static/whodun/formats
$(OBJDIR)/static/whodun/formats/genetics : | $(OBJDIR)/static/whodun/formats
	mkdir $(OBJDIR)/static/whodun/formats/genetics
$(OBJDIR)/static/whodun/formats/table : | $(OBJDIR)/static/whodun/formats
	mkdir $(OBJDIR)/static/whodun/formats/table
$(OBJDIR)/static/whodun/parse : | $(OBJDIR)/static/whodun
	mkdir $(OBJDIR)/static/whodun/parse
$(OBJDIR)/static/whodun/stats : | $(OBJDIR)/static/whodun
	mkdir $(OBJDIR)/static/whodun/stats

$(OBJDIR)/static/whodun/alloc.o : static/whodun/alloc.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/alloc.o static/whodun/alloc.c
$(OBJDIR)/static/whodun/args.o : static/whodun/args.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/args.o static/whodun/args.c
$(OBJDIR)/static/whodun/array.o : static/whodun/array.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/array.o static/whodun/array.c
$(OBJDIR)/static/whodun/class.o : static/whodun/class.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/class.o static/whodun/class.c
$(OBJDIR)/static/whodun/complex.o : static/whodun/complex.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/complex.o static/whodun/complex.c
$(OBJDIR)/static/whodun/contain.o : static/whodun/contain.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/contain.o static/whodun/contain.c
$(OBJDIR)/static/whodun/cpuc.o : static/whodun/spec/$(PROC_NAME)/linux/cpu.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/cpuc.o static/whodun/spec/$(PROC_NAME)/linux/cpu.c
$(OBJDIR)/static/whodun/cpus.o : static/whodun/spec/$(PROC_NAME)/linux/cpu.s | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -c -o $(OBJDIR)/static/whodun/cpus.o static/whodun/spec/$(PROC_NAME)/linux/cpu.s
$(OBJDIR)/static/whodun/error.o : static/whodun/error.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/error.o static/whodun/error.c
$(OBJDIR)/static/whodun/internat.o : static/whodun/internat.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/internat.o static/whodun/internat.c
$(OBJDIR)/static/whodun/math.o : static/whodun/math.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/math.o static/whodun/math.c
$(OBJDIR)/static/whodun/mathc.o : static/whodun/spec/$(PROC_NAME)/linux/math.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/mathc.o static/whodun/spec/$(PROC_NAME)/linux/math.c
$(OBJDIR)/static/whodun/maths.o : static/whodun/spec/$(PROC_NAME)/linux/math.s | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -c -o $(OBJDIR)/static/whodun/maths.o static/whodun/spec/$(PROC_NAME)/linux/math.s
$(OBJDIR)/static/whodun/memmap.o : static/whodun/memmap.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/memmap.o static/whodun/memmap.c
$(OBJDIR)/static/whodun/oshook.o : static/whodun/spec/any/linux/oshook.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/oshook.o static/whodun/spec/any/linux/oshook.c
$(OBJDIR)/static/whodun/oshfile.o : static/whodun/spec/any/linux/oshfile.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/oshfile.o static/whodun/spec/any/linux/oshfile.c
$(OBJDIR)/static/whodun/oshmem.o : static/whodun/spec/any/linux/oshmem.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/oshmem.o static/whodun/spec/any/linux/oshmem.c
$(OBJDIR)/static/whodun/oshmemi.o : static/whodun/spec/any/linux/oshmemi.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/oshmemi.o static/whodun/spec/any/linux/oshmemi.c
$(OBJDIR)/static/whodun/oshpanic.o : static/whodun/spec/any/linux/oshpanic.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/oshpanic.o static/whodun/spec/any/linux/oshpanic.c
$(OBJDIR)/static/whodun/oshstdio.o : static/whodun/spec/any/linux/oshstdio.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/oshstdio.o static/whodun/spec/any/linux/oshstdio.c
$(OBJDIR)/static/whodun/oshthred.o : static/whodun/spec/any/linux/oshthred.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/oshthred.o static/whodun/spec/any/linux/oshthred.c
$(OBJDIR)/static/whodun/stream.o : static/whodun/stream.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/stream.o static/whodun/stream.c
$(OBJDIR)/static/whodun/string.o : static/whodun/string.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/string.o static/whodun/string.c
$(OBJDIR)/static/whodun/stringc.o : static/whodun/spec/$(PROC_NAME)/linux/string.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/stringc.o static/whodun/spec/$(PROC_NAME)/linux/string.c
$(OBJDIR)/static/whodun/strings.o : static/whodun/spec/$(PROC_NAME)/linux/string.s | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -c -o $(OBJDIR)/static/whodun/strings.o static/whodun/spec/$(PROC_NAME)/linux/string.s
$(OBJDIR)/static/whodun/test.o : static/whodun/test.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/test.o static/whodun/test.c
$(OBJDIR)/static/whodun/thread.o : static/whodun/thread.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/thread.o static/whodun/thread.c
$(OBJDIR)/static/whodun/bulk/mapred.o : static/whodun/bulk/mapred.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun/bulk
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/bulk/mapred.o static/whodun/bulk/mapred.c
$(OBJDIR)/static/whodun/bulk/move.o : static/whodun/bulk/move.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun/bulk
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/bulk/move.o static/whodun/bulk/move.c
$(OBJDIR)/static/whodun/bulk/sort.o : static/whodun/bulk/sort.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun/bulk
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/bulk/sort.o static/whodun/bulk/sort.c
$(OBJDIR)/static/whodun/bulk/tensor.o : static/whodun/bulk/tensor.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun/bulk
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/bulk/tensor.o static/whodun/bulk/tensor.c
$(OBJDIR)/static/whodun/formats/line.o : static/whodun/formats/line.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun/formats
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/formats/line.o static/whodun/formats/line.c
$(OBJDIR)/static/whodun/formats/genetics/fasta.o : static/whodun/formats/genetics/fasta.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun/formats/genetics
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/formats/genetics/fasta.o static/whodun/formats/genetics/fasta.c
$(OBJDIR)/static/whodun/formats/genetics/fastq.o : static/whodun/formats/genetics/fastq.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun/formats/genetics
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/formats/genetics/fastq.o static/whodun/formats/genetics/fastq.c
$(OBJDIR)/static/whodun/formats/genetics/pileup.o : static/whodun/formats/genetics/pileup.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun/formats/genetics
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/formats/genetics/pileup.o static/whodun/formats/genetics/pileup.c
$(OBJDIR)/static/whodun/formats/table/tsv.o : static/whodun/formats/table/tsv.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun/formats/table
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/formats/table/tsv.o static/whodun/formats/table/tsv.c
$(OBJDIR)/static/whodun/parse/token.o : static/whodun/parse/token.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun/parse
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/parse/token.o static/whodun/parse/token.c
$(OBJDIR)/static/whodun/stats/math.o : static/whodun/stats/math.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun/stats
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/stats/math.o static/whodun/stats/math.c
$(OBJDIR)/static/whodun/stats/random.o : static/whodun/stats/random.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun/stats
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/stats/random.o static/whodun/stats/random.c
$(OBJDIR)/static/whodun/stats/randomc.o : static/whodun/spec/$(PROC_NAME)/linux/stats/random.c $(COMMON_HEADERS) | $(OBJDIR)/static/whodun/stats
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/static/whodun/stats/randomc.o static/whodun/spec/$(PROC_NAME)/linux/stats/random.c
$(OBJDIR)/static/whodun/stats/randoms.o : static/whodun/spec/$(PROC_NAME)/linux/stats/random.s | $(OBJDIR)/static/whodun/stats
	gcc $(COMP_OPTS) -c -o $(OBJDIR)/static/whodun/stats/randoms.o static/whodun/spec/$(PROC_NAME)/linux/stats/random.s

ifeq ($(PROC_NAME),oth)
STATICASSO = 
else
STATICASSO = \
	$(OBJDIR)/static/whodun/cpus.o \
	$(OBJDIR)/static/whodun/maths.o \
	$(OBJDIR)/static/whodun/strings.o \
	$(OBJDIR)/static/whodun/stats/randoms.o
endif

$(BINDIR)/libwhodun.a : \
		$(OBJDIR)/static/whodun/alloc.o \
		$(OBJDIR)/static/whodun/args.o \
		$(OBJDIR)/static/whodun/array.o \
		$(OBJDIR)/static/whodun/class.o \
		$(OBJDIR)/static/whodun/complex.o \
		$(OBJDIR)/static/whodun/contain.o \
		$(OBJDIR)/static/whodun/cpuc.o \
		$(OBJDIR)/static/whodun/error.o \
		$(OBJDIR)/static/whodun/internat.o \
		$(OBJDIR)/static/whodun/math.o \
		$(OBJDIR)/static/whodun/mathc.o \
		$(OBJDIR)/static/whodun/memmap.o \
		$(OBJDIR)/static/whodun/oshook.o \
		$(OBJDIR)/static/whodun/oshfile.o \
		$(OBJDIR)/static/whodun/oshmem.o \
		$(OBJDIR)/static/whodun/oshmemi.o \
		$(OBJDIR)/static/whodun/oshpanic.o \
		$(OBJDIR)/static/whodun/oshstdio.o \
		$(OBJDIR)/static/whodun/oshthred.o \
		$(OBJDIR)/static/whodun/stream.o \
		$(OBJDIR)/static/whodun/string.o \
		$(OBJDIR)/static/whodun/stringc.o \
		$(OBJDIR)/static/whodun/test.o \
		$(OBJDIR)/static/whodun/thread.o \
		$(OBJDIR)/static/whodun/bulk/mapred.o \
		$(OBJDIR)/static/whodun/bulk/move.o \
		$(OBJDIR)/static/whodun/bulk/sort.o \
		$(OBJDIR)/static/whodun/bulk/tensor.o \
		$(OBJDIR)/static/whodun/formats/line.o \
		$(OBJDIR)/static/whodun/formats/genetics/fasta.o \
		$(OBJDIR)/static/whodun/formats/genetics/fastq.o \
		$(OBJDIR)/static/whodun/formats/genetics/pileup.o \
		$(OBJDIR)/static/whodun/formats/table/tsv.o \
		$(OBJDIR)/static/whodun/parse/token.o \
		$(OBJDIR)/static/whodun/stats/math.o \
		$(OBJDIR)/static/whodun/stats/random.o \
		$(OBJDIR)/static/whodun/stats/randomc.o \
		$(STATICASSO) \
		| $(BINDIR)
	ar rcs $(BINDIR)/libwhodun.a \
			$(OBJDIR)/static/whodun/alloc.o \
			$(OBJDIR)/static/whodun/args.o \
			$(OBJDIR)/static/whodun/array.o \
			$(OBJDIR)/static/whodun/class.o \
			$(OBJDIR)/static/whodun/contain.o \
			$(OBJDIR)/static/whodun/complex.o \
			$(OBJDIR)/static/whodun/cpuc.o \
			$(OBJDIR)/static/whodun/error.o \
			$(OBJDIR)/static/whodun/internat.o \
			$(OBJDIR)/static/whodun/math.o \
			$(OBJDIR)/static/whodun/mathc.o \
			$(OBJDIR)/static/whodun/memmap.o \
			$(OBJDIR)/static/whodun/oshook.o \
			$(OBJDIR)/static/whodun/oshfile.o \
			$(OBJDIR)/static/whodun/oshmem.o \
			$(OBJDIR)/static/whodun/oshmemi.o \
			$(OBJDIR)/static/whodun/oshpanic.o \
			$(OBJDIR)/static/whodun/oshstdio.o \
			$(OBJDIR)/static/whodun/oshthred.o \
			$(OBJDIR)/static/whodun/stream.o \
			$(OBJDIR)/static/whodun/string.o \
			$(OBJDIR)/static/whodun/stringc.o \
			$(OBJDIR)/static/whodun/test.o \
			$(OBJDIR)/static/whodun/thread.o \
			$(OBJDIR)/static/whodun/bulk/mapred.o \
			$(OBJDIR)/static/whodun/bulk/move.o \
			$(OBJDIR)/static/whodun/bulk/sort.o \
			$(OBJDIR)/static/whodun/bulk/tensor.o \
			$(OBJDIR)/static/whodun/formats/line.o \
			$(OBJDIR)/static/whodun/formats/genetics/fasta.o \
			$(OBJDIR)/static/whodun/formats/genetics/fastq.o \
			$(OBJDIR)/static/whodun/formats/genetics/pileup.o \
			$(OBJDIR)/static/whodun/formats/table/tsv.o \
			$(OBJDIR)/static/whodun/parse/token.o \
			$(OBJDIR)/static/whodun/stats/math.o \
			$(OBJDIR)/static/whodun/stats/random.o \
			$(OBJDIR)/static/whodun/stats/randomc.o \
			$(STATICASSO)

# TODO

# *******************************************************************
# dynamic help

$(OBJDIR)/dynamic : | $(OBJDIR)
	mkdir $(OBJDIR)/dynamic
$(OBJDIR)/dynamic/whodun : | $(OBJDIR)/dynamic
	mkdir $(OBJDIR)/dynamic/whodun
$(OBJDIR)/dynamic/whodun/bulk : | $(OBJDIR)/dynamic/whodun
	mkdir $(OBJDIR)/dynamic/whodun/bulk
$(OBJDIR)/dynamic/whodun/formats : | $(OBJDIR)/dynamic/whodun
	mkdir $(OBJDIR)/dynamic/whodun/formats
$(OBJDIR)/dynamic/whodun/formats/genetics : | $(OBJDIR)/dynamic/whodun/formats
	mkdir $(OBJDIR)/dynamic/whodun/formats/genetics
$(OBJDIR)/dynamic/whodun/formats/table : | $(OBJDIR)/dynamic/whodun/formats
	mkdir $(OBJDIR)/dynamic/whodun/formats/table
$(OBJDIR)/dynamic/whodun/parse : | $(OBJDIR)/dynamic/whodun
	mkdir $(OBJDIR)/dynamic/whodun/parse
$(OBJDIR)/dynamic/whodun/stats : | $(OBJDIR)/dynamic/whodun
	mkdir $(OBJDIR)/dynamic/whodun/stats

$(OBJDIR)/dynamic/whodun/alloc.o : dynamic/whodun/alloc.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/alloc.o dynamic/whodun/alloc.c
$(OBJDIR)/dynamic/whodun/args.o : dynamic/whodun/args.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/args.o dynamic/whodun/args.c
$(OBJDIR)/dynamic/whodun/array.o : dynamic/whodun/array.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/array.o dynamic/whodun/array.c
$(OBJDIR)/dynamic/whodun/class.o : dynamic/whodun/class.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/class.o dynamic/whodun/class.c
$(OBJDIR)/dynamic/whodun/complex.o : dynamic/whodun/complex.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/complex.o dynamic/whodun/complex.c
$(OBJDIR)/dynamic/whodun/contain.o : dynamic/whodun/contain.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/contain.o dynamic/whodun/contain.c
$(OBJDIR)/dynamic/whodun/cpu.o : dynamic/whodun/cpu.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/cpu.o dynamic/whodun/cpu.c
$(OBJDIR)/dynamic/whodun/error.o : dynamic/whodun/error.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/error.o dynamic/whodun/error.c
$(OBJDIR)/dynamic/whodun/internat.o : dynamic/whodun/internat.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/internat.o dynamic/whodun/internat.c
$(OBJDIR)/dynamic/whodun/math.o : dynamic/whodun/math.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/math.o dynamic/whodun/math.c
$(OBJDIR)/dynamic/whodun/memmap.o : dynamic/whodun/memmap.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/memmap.o dynamic/whodun/memmap.c
$(OBJDIR)/dynamic/whodun/oshook.o : dynamic/whodun/oshook.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/oshook.o dynamic/whodun/oshook.c
$(OBJDIR)/dynamic/whodun/stream.o : dynamic/whodun/stream.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/stream.o dynamic/whodun/stream.c
$(OBJDIR)/dynamic/whodun/string.o : dynamic/whodun/string.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/string.o dynamic/whodun/string.c
$(OBJDIR)/dynamic/whodun/test.o : dynamic/whodun/test.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/test.o dynamic/whodun/test.c
$(OBJDIR)/dynamic/whodun/thread.o : dynamic/whodun/thread.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/thread.o dynamic/whodun/thread.c
$(OBJDIR)/dynamic/whodun/bulk/mapred.o : dynamic/whodun/bulk/mapred.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun/bulk
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/bulk/mapred.o dynamic/whodun/bulk/mapred.c
$(OBJDIR)/dynamic/whodun/bulk/move.o : dynamic/whodun/bulk/move.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun/bulk
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/bulk/move.o dynamic/whodun/bulk/move.c
$(OBJDIR)/dynamic/whodun/bulk/sort.o : dynamic/whodun/bulk/sort.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun/bulk
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/bulk/sort.o dynamic/whodun/bulk/sort.c
$(OBJDIR)/dynamic/whodun/bulk/tensor.o : dynamic/whodun/bulk/tensor.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun/bulk
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/bulk/tensor.o dynamic/whodun/bulk/tensor.c
$(OBJDIR)/dynamic/whodun/formats/line.o : dynamic/whodun/formats/line.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun/formats
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/formats/line.o dynamic/whodun/formats/line.c
$(OBJDIR)/dynamic/whodun/formats/genetics/fasta.o : dynamic/whodun/formats/genetics/fasta.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun/formats/genetics
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/formats/genetics/fasta.o dynamic/whodun/formats/genetics/fasta.c
$(OBJDIR)/dynamic/whodun/formats/genetics/fastq.o : dynamic/whodun/formats/genetics/fastq.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun/formats/genetics
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/formats/genetics/fastq.o dynamic/whodun/formats/genetics/fastq.c
$(OBJDIR)/dynamic/whodun/formats/genetics/pileup.o : dynamic/whodun/formats/genetics/pileup.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun/formats/genetics
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/formats/genetics/pileup.o dynamic/whodun/formats/genetics/pileup.c
$(OBJDIR)/dynamic/whodun/formats/table/tsv.o : dynamic/whodun/formats/table/tsv.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun/formats/table
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/formats/table/tsv.o dynamic/whodun/formats/table/tsv.c
$(OBJDIR)/dynamic/whodun/parse/token.o : dynamic/whodun/parse/token.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun/parse
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/parse/token.o dynamic/whodun/parse/token.c
$(OBJDIR)/dynamic/whodun/stats/math.o : dynamic/whodun/stats/math.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun/stats
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/stats/math.o dynamic/whodun/stats/math.c
$(OBJDIR)/dynamic/whodun/stats/random.o : dynamic/whodun/stats/random.c $(COMMON_HEADERS) | $(OBJDIR)/dynamic/whodun/stats
	gcc $(COMP_OPTS) -I$(INCDIR) -c -o $(OBJDIR)/dynamic/whodun/stats/random.o dynamic/whodun/stats/random.c

$(BINDIR)/libwhodundyn.a : \
		$(OBJDIR)/dynamic/whodun/alloc.o \
		$(OBJDIR)/dynamic/whodun/args.o \
		$(OBJDIR)/dynamic/whodun/array.o \
		$(OBJDIR)/dynamic/whodun/class.o \
		$(OBJDIR)/dynamic/whodun/complex.o \
		$(OBJDIR)/dynamic/whodun/contain.o \
		$(OBJDIR)/dynamic/whodun/cpu.o \
		$(OBJDIR)/dynamic/whodun/error.o \
		$(OBJDIR)/dynamic/whodun/internat.o \
		$(OBJDIR)/dynamic/whodun/math.o \
		$(OBJDIR)/dynamic/whodun/memmap.o \
		$(OBJDIR)/dynamic/whodun/oshook.o \
		$(OBJDIR)/dynamic/whodun/stream.o \
		$(OBJDIR)/dynamic/whodun/string.o \
		$(OBJDIR)/dynamic/whodun/test.o \
		$(OBJDIR)/dynamic/whodun/thread.o \
		$(OBJDIR)/dynamic/whodun/bulk/mapred.o \
		$(OBJDIR)/dynamic/whodun/bulk/move.o \
		$(OBJDIR)/dynamic/whodun/bulk/sort.o \
		$(OBJDIR)/dynamic/whodun/bulk/tensor.o \
		$(OBJDIR)/dynamic/whodun/formats/line.o \
		$(OBJDIR)/dynamic/whodun/formats/genetics/fasta.o \
		$(OBJDIR)/dynamic/whodun/formats/genetics/fastq.o \
		$(OBJDIR)/dynamic/whodun/formats/genetics/pileup.o \
		$(OBJDIR)/dynamic/whodun/formats/table/tsv.o \
		$(OBJDIR)/dynamic/whodun/parse/token.o \
		$(OBJDIR)/dynamic/whodun/stats/math.o \
		$(OBJDIR)/dynamic/whodun/stats/random.o \
		| $(BINDIR)
	ar rcs $(BINDIR)/libwhodundyn.a \
			$(OBJDIR)/dynamic/whodun/alloc.o \
			$(OBJDIR)/dynamic/whodun/args.o \
			$(OBJDIR)/dynamic/whodun/array.o \
			$(OBJDIR)/dynamic/whodun/class.o \
			$(OBJDIR)/dynamic/whodun/complex.o \
			$(OBJDIR)/dynamic/whodun/contain.o \
			$(OBJDIR)/dynamic/whodun/cpu.o \
			$(OBJDIR)/dynamic/whodun/error.o \
			$(OBJDIR)/dynamic/whodun/internat.o \
			$(OBJDIR)/dynamic/whodun/math.o \
			$(OBJDIR)/dynamic/whodun/memmap.o \
			$(OBJDIR)/dynamic/whodun/oshook.o \
			$(OBJDIR)/dynamic/whodun/stream.o \
			$(OBJDIR)/dynamic/whodun/string.o \
			$(OBJDIR)/dynamic/whodun/test.o \
			$(OBJDIR)/dynamic/whodun/thread.o \
			$(OBJDIR)/dynamic/whodun/bulk/mapred.o \
			$(OBJDIR)/dynamic/whodun/bulk/move.o \
			$(OBJDIR)/dynamic/whodun/bulk/sort.o \
			$(OBJDIR)/dynamic/whodun/bulk/tensor.o \
			$(OBJDIR)/dynamic/whodun/formats/line.o \
			$(OBJDIR)/dynamic/whodun/formats/genetics/fasta.o \
			$(OBJDIR)/dynamic/whodun/formats/genetics/fastq.o \
			$(OBJDIR)/dynamic/whodun/formats/genetics/pileup.o \
			$(OBJDIR)/dynamic/whodun/formats/table/tsv.o \
			$(OBJDIR)/dynamic/whodun/parse/token.o \
			$(OBJDIR)/dynamic/whodun/stats/math.o \
			$(OBJDIR)/dynamic/whodun/stats/random.o

# *******************************************************************
# unit testing

TEST_HEADERS = $(COMMON_HEADERS) \
	test/whodun/testmain.h

$(OBJDIR)/test : | $(OBJDIR)
	mkdir $(OBJDIR)/test

$(OBJDIR)/test/whodun : | $(OBJDIR)/test
	mkdir $(OBJDIR)/test/whodun

$(OBJDIR)/test/whodun/cpuvec.o : test/whodun/cpuvec.c $(TEST_HEADERS) | $(OBJDIR)/test/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -Itest -c -o $(OBJDIR)/test/whodun/cpuvec.o test/whodun/cpuvec.c
$(OBJDIR)/test/whodun/main.o : test/whodun/main.c $(TEST_HEADERS) | $(OBJDIR)/test/whodun
	gcc $(COMP_OPTS) -I$(INCDIR) -Itest -c -o $(OBJDIR)/test/whodun/main.o test/whodun/main.c

$(BINDIR)/testwhodun : \
		$(OBJDIR)/test/whodun/cpuvec.o \
		$(OBJDIR)/test/whodun/main.o \
		$(BINDIR)/libwhodun.a \
		| $(BINDIR)
	gcc $(LINK_OPTS) -o $(BINDIR)/testwhodun \
			$(OBJDIR)/test/whodun/cpuvec.o \
			$(OBJDIR)/test/whodun/main.o \
			-L$(BINDIR) -lwhodun $(BASIC_PROG_LIBS)

# TODO

