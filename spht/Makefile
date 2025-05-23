
WHODUN_ROOT = ../whodun2
PROC_NAME := $(shell $(WHODUN_ROOT)/scripts/arches/LinuxFigureArch.sh)
WHODUN_INC = $(WHODUN_ROOT)/builds/inc_$(PROC_NAME)_linux
WHODUN_BIN = $(WHODUN_ROOT)/builds/bin_$(PROC_NAME)_linux

# figure out the options based on the above

COMP_OPTS := $(shell $(WHODUN_ROOT)/scripts/arches/LinuxCompOpts.sh $(PROC_NAME))
LINK_OPTS := $(shell $(WHODUN_ROOT)/scripts/arches/LinuxLinkOpts.sh $(PROC_NAME))

BASIC_PROG_LIBS = -lm -ldl

OBJDIR = builds/obj_$(PROC_NAME)_linux
BINDIR = builds/bin_$(PROC_NAME)_linux

# *******************************************************************
# super targets

all : $(BINDIR)/spht

clean : 
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

$(OBJDIR) : 
	mkdir $(OBJDIR)
$(BINDIR) : 
	mkdir $(BINDIR)


# *******************************************************************
# main program

PROG_HEADERS = $(WHODUN_BIN)/whodunh.tar \
			source/progs.h \
			source/spht.h

$(OBJDIR)/main.o : source/main.c $(PROG_HEADERS) | $(OBJDIR)
	gcc $(COMP_OPTS) -I$(WHODUN_INC) -Isource -c -o $(OBJDIR)/main.o source/main.c
$(OBJDIR)/spht.o : source/spht.c $(PROG_HEADERS) | $(OBJDIR)
	gcc $(COMP_OPTS) -I$(WHODUN_INC) -Isource -c -o $(OBJDIR)/spht.o source/spht.c
$(OBJDIR)/flippy.o : source/flippy.c $(PROG_HEADERS) | $(OBJDIR)
	gcc $(COMP_OPTS) -I$(WHODUN_INC) -Isource -c -o $(OBJDIR)/flippy.o source/flippy.c
$(OBJDIR)/plinko.o : source/plinko.c $(PROG_HEADERS) | $(OBJDIR)
	gcc $(COMP_OPTS) -I$(WHODUN_INC) -Isource -c -o $(OBJDIR)/plinko.o source/plinko.c
$(OBJDIR)/drift.o : source/drift.c $(PROG_HEADERS) | $(OBJDIR)
	gcc $(COMP_OPTS) -I$(WHODUN_INC) -Isource -c -o $(OBJDIR)/drift.o source/drift.c

$(BINDIR)/spht : \
		$(OBJDIR)/main.o \
		$(OBJDIR)/spht.o \
		$(OBJDIR)/flippy.o \
		$(OBJDIR)/plinko.o \
		$(OBJDIR)/drift.o \
		$(WHODUN_BIN)/libwhodun.a \
		| $(BINDIR)
	gcc $(LINK_OPTS) -o $(BINDIR)/spht \
			$(OBJDIR)/main.o \
			$(OBJDIR)/spht.o \
			$(OBJDIR)/flippy.o \
			$(OBJDIR)/plinko.o \
			$(OBJDIR)/drift.o \
			-L$(WHODUN_BIN) -lwhodun $(BASIC_PROG_LIBS)





