
REM ***************************************************************
REM Figure out the processor architecture and any special arguments.

SET PROC_NAME=oth
IF %PROCESSOR_ARCHITECTURE% == AMD64 SET PROC_NAME=x64

IF %PROC_NAME% == x64 (
	SET COMP_OPTS=-g -O0 -Wall -Wpedantic -std=c99 -fPIC
	SET LINK_OPTS=-g -O0 -Wall -Wpedantic -std=c99
) ELSE (
	SET COMP_OPTS=-g -O0 -Wall -Wpedantic
	SET LINK_OPTS=-g -O0 -Wall -Wpedantic
)

REM ***************************************************************
REM Make a few folders.

SET INCDIR=builds\inc_%PROC_NAME%_win32
SET OBJDIR=builds\obj_%PROC_NAME%_win32
SET DOCDIR=builds\doc_%PROC_NAME%_win32
SET BINDIR=builds\bin_%PROC_NAME%_win32

IF EXIST %INCDIR% RMDIR /S /Q %INCDIR%
IF EXIST %OBJDIR% RMDIR /S /Q %OBJDIR%
IF EXIST %DOCDIR% RMDIR /S /Q %DOCDIR%
IF EXIST %BINDIR% RMDIR /S /Q %BINDIR%

MKDIR %INCDIR%
MKDIR %OBJDIR%
MKDIR %DOCDIR%
MKDIR %BINDIR%

REM ***************************************************************
REM Copy headers to where they belong.

MKDIR %INCDIR%\whodun
MKDIR %INCDIR%\whodun\bulk
MKDIR %INCDIR%\whodun\formats
MKDIR %INCDIR%\whodun\formats\genetics
MKDIR %INCDIR%\whodun\formats\table
MKDIR %INCDIR%\whodun\parse
MKDIR %INCDIR%\whodun\stats
COPY head\whodun\alloc.h %INCDIR%\whodun\
COPY head\whodun\args.h %INCDIR%\whodun\
COPY head\whodun\array.h %INCDIR%\whodun\
COPY head\whodun\class.h %INCDIR%\whodun\
COPY head\whodun\complex.h %INCDIR%\whodun\
COPY head\whodun\contain.h %INCDIR%\whodun\
COPY head\whodun\cpu.h %INCDIR%\whodun\
COPY head\whodun\spec\%PROC_NAME%\win32\cpuvec.h %INCDIR%\whodun\
COPY head\whodun\cpuvecx.h %INCDIR%\whodun\
COPY head\whodun\spec\%PROC_NAME%\win32\defs.h %INCDIR%\whodun\
COPY head\whodun\ermac.h %INCDIR%\whodun\
COPY head\whodun\error.h %INCDIR%\whodun\
COPY head\whodun\internat.h %INCDIR%\whodun\
COPY head\whodun\math.h %INCDIR%\whodun\
COPY head\whodun\memmap.h %INCDIR%\whodun\
COPY head\whodun\oshook.h %INCDIR%\whodun\
COPY head\whodun\stream.h %INCDIR%\whodun\
COPY head\whodun\string.h %INCDIR%\whodun\
COPY head\whodun\test.h %INCDIR%\whodun\
COPY head\whodun\thread.h %INCDIR%\whodun\
COPY head\whodun\bulk\mapred.h %INCDIR%\whodun\bulk\
COPY head\whodun\bulk\move.h %INCDIR%\whodun\bulk\
COPY head\whodun\bulk\sort.h %INCDIR%\whodun\bulk\
COPY head\whodun\bulk\tensor.h %INCDIR%\whodun\bulk\
COPY head\whodun\formats\line.h %INCDIR%\whodun\formats\
COPY head\whodun\formats\genetics\fasta.h %INCDIR%\whodun\formats\genetics\
COPY head\whodun\formats\genetics\fastq.h %INCDIR%\whodun\formats\genetics\
COPY head\whodun\formats\genetics\pileup.h %INCDIR%\whodun\formats\genetics\
COPY head\whodun\formats\table\tsv.h %INCDIR%\whodun\formats\table\
COPY head\whodun\parse\token.h %INCDIR%\whodun\parse\
COPY head\whodun\stats\math.h %INCDIR%\whodun\stats\
COPY head\whodun\stats\random.h %INCDIR%\whodun\stats\

tar cf %BINDIR%\whodunh.tar -C %INCDIR%\ whodun

REM Uncomment if you have doxygen installed.
REM COPY Doxyfile %DOCDIR%\usedoxy
REM ECHO OUTPUT_DIRECTORY=./builds/doc_%PROC_NAME%_win32/ >> %DOCDIR%\usedoxy
REM ECHO STRIP_FROM_PATH=builds/inc_%PROC_NAME%_win32 >> %DOCDIR%\usedoxy
REM ECHO INPUT=./builds/inc_%PROC_NAME%_win32/ >> %DOCDIR%\usedoxy
REM cat %DOCDIR%\usedoxy | doxygen -
REM DEL %DOCDIR%\usedoxy
REM tar czf %BINDIR%\dochtml.tar.gz -C %DOCDIR%\ html

REM ***************************************************************
REM Static sources

MKDIR %OBJDIR%\static
MKDIR %OBJDIR%\static\whodun
MKDIR %OBJDIR%\static\whodun\bulk
MKDIR %OBJDIR%\static\whodun\formats
MKDIR %OBJDIR%\static\whodun\formats\genetics
MKDIR %OBJDIR%\static\whodun\formats\table
MKDIR %OBJDIR%\static\whodun\parse
MKDIR %OBJDIR%\static\whodun\stats
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\alloc.o static\whodun\alloc.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\args.o static\whodun\args.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\array.o static\whodun\array.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\class.o static\whodun\class.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\complex.o static\whodun\complex.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\contain.o static\whodun\contain.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\cpuc.o static\whodun\spec\%PROC_NAME%\win32\cpu.c
IF NOT %PROC_NAME% == oth gcc %COMP_OPTS% -c -o %OBJDIR%\static\whodun\cpus.o static\whodun\spec\%PROC_NAME%\win32\cpu.s
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\error.o static\whodun\error.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\internat.o static\whodun\internat.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\math.o static\whodun\math.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\mathc.o static\whodun\spec\%PROC_NAME%\win32\math.c
IF NOT %PROC_NAME% == oth gcc %COMP_OPTS% -c -o %OBJDIR%\static\whodun\maths.o static\whodun\spec\%PROC_NAME%\win32\math.s
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\memmap.o static\whodun\memmap.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\oshook.o static\whodun\spec\any\win32\oshook.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\stream.o static\whodun\stream.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\string.o static\whodun\string.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\stringc.o static\whodun\spec\%PROC_NAME%\win32\string.c
IF NOT %PROC_NAME% == oth gcc %COMP_OPTS% -c -o %OBJDIR%\static\whodun\strings.o static\whodun\spec\%PROC_NAME%\win32\string.s
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\test.o static\whodun\test.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\thread.o static\whodun\thread.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\bulk\mapred.o static\whodun\bulk\mapred.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\bulk\move.o static\whodun\bulk\move.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\bulk\sort.o static\whodun\bulk\sort.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\bulk\tensor.o static\whodun\bulk\tensor.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\formats\line.o static\whodun\formats\line.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\formats\genetics\fasta.o static\whodun\formats\genetics\fasta.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\formats\genetics\fastq.o static\whodun\formats\genetics\fastq.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\formats\genetics\pileup.o static\whodun\formats\genetics\pileup.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\formats\table\tsv.o static\whodun\formats\table\tsv.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\parse\token.o static\whodun\parse\token.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\stats\math.o static\whodun\stats\math.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\stats\random.o static\whodun\stats\random.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\static\whodun\stats\randomc.o static\whodun\spec\%PROC_NAME%\win32\stats\random.c
IF NOT %PROC_NAME% == oth gcc %COMP_OPTS% -c -o %OBJDIR%\static\whodun\stats\randoms.o static\whodun\spec\%PROC_NAME%\win32\stats\random.s

ar rcs %BINDIR%\libwhodun.a ^
%OBJDIR%\static\whodun\*.o ^
%OBJDIR%\static\whodun\bulk\*.o ^
%OBJDIR%\static\whodun\formats\*.o ^
%OBJDIR%\static\whodun\formats\genetics\*.o ^
%OBJDIR%\static\whodun\formats\table\*.o ^
%OBJDIR%\static\whodun\parse\*.o ^
%OBJDIR%\static\whodun\stats\*.o

REM ***************************************************************
REM Dynamic help

MKDIR %OBJDIR%\dynamic
MKDIR %OBJDIR%\dynamic\whodun
MKDIR %OBJDIR%\dynamic\whodun\bulk
MKDIR %OBJDIR%\dynamic\whodun\formats
MKDIR %OBJDIR%\dynamic\whodun\formats\genetics
MKDIR %OBJDIR%\dynamic\whodun\formats\table
MKDIR %OBJDIR%\dynamic\whodun\parse
MKDIR %OBJDIR%\dynamic\whodun\stats
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\alloc.o dynamic\whodun\alloc.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\args.o dynamic\whodun\args.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\array.o dynamic\whodun\array.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\class.o dynamic\whodun\class.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\complex.o dynamic\whodun\complex.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\contain.o dynamic\whodun\contain.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\cpu.o dynamic\whodun\cpu.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\error.o dynamic\whodun\error.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\internat.o dynamic\whodun\internat.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\math.o dynamic\whodun\math.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\memmap.o dynamic\whodun\memmap.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\oshook.o dynamic\whodun\oshook.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\stream.o dynamic\whodun\stream.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\string.o dynamic\whodun\string.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\test.o dynamic\whodun\test.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\thread.o dynamic\whodun\thread.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\bulk\mapred.o dynamic\whodun\bulk\mapred.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\bulk\move.o dynamic\whodun\bulk\move.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\bulk\sort.o dynamic\whodun\bulk\sort.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\bulk\tensor.o dynamic\whodun\bulk\tensor.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\formats\line.o dynamic\whodun\formats\line.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\formats\genetics\fasta.o dynamic\whodun\formats\genetics\fasta.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\formats\genetics\fastq.o dynamic\whodun\formats\genetics\fastq.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\formats\genetics\pileup.o dynamic\whodun\formats\genetics\pileup.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\formats\table\tsv.o dynamic\whodun\formats\table\tsv.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\parse\token.o dynamic\whodun\parse\token.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\stats\math.o dynamic\whodun\stats\math.c
gcc %COMP_OPTS% -I%INCDIR% -c -o %OBJDIR%\dynamic\whodun\stats\random.o dynamic\whodun\stats\random.c

ar rcs %BINDIR%\libwhodundyn.a ^
%OBJDIR%\dynamic\whodun\*.o ^
%OBJDIR%\dynamic\whodun\bulk\*.o ^
%OBJDIR%\dynamic\whodun\formats\*.o ^
%OBJDIR%\dynamic\whodun\formats\genetics\*.o ^
%OBJDIR%\dynamic\whodun\formats\table\*.o ^
%OBJDIR%\dynamic\whodun\parse\*.o ^
%OBJDIR%\dynamic\whodun\stats\*.o

REM ***************************************************************
REM Unit testing

MKDIR %OBJDIR%\test
MKDIR %OBJDIR%\test\whodun
gcc %COMP_OPTS% -I%INCDIR% -Itest -c -o %OBJDIR%\test\whodun\cpuvec.o test\whodun\cpuvec.c
gcc %COMP_OPTS% -I%INCDIR% -Itest -c -o %OBJDIR%\test\whodun\main.o test\whodun\main.c

gcc %LINK_OPTS% -o %BINDIR%\testwhodun ^
%OBJDIR%\test\whodun\*.o ^
-L%BINDIR% -lwhodun




