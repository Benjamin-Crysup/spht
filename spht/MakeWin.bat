
SET WHODUN_ROOT=..\whodun2

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

SET WHODUN_INC=%WHODUN_ROOT%\builds\inc_%PROC_NAME%_win32
SET WHODUN_BIN=%WHODUN_ROOT%\builds\bin_%PROC_NAME%_win32

REM ***************************************************************
REM Make a few folders.

SET OBJDIR=builds\obj_%PROC_NAME%_win32
SET BINDIR=builds\bin_%PROC_NAME%_win32

IF EXIST %OBJDIR% RMDIR /S /Q %OBJDIR%
IF EXIST %BINDIR% RMDIR /S /Q %BINDIR%

MKDIR %OBJDIR%
MKDIR %BINDIR%

REM ***************************************************************
REM Main program.

gcc %COMP_OPTS% -I%WHODUN_INC% -Isource -c -o %OBJDIR%\main.o source\main.c
gcc %COMP_OPTS% -I%WHODUN_INC% -Isource -c -o %OBJDIR%\spht.o source\spht.c
gcc %COMP_OPTS% -I%WHODUN_INC% -Isource -c -o %OBJDIR%\flippy.o source\flippy.c
gcc %COMP_OPTS% -I%WHODUN_INC% -Isource -c -o %OBJDIR%\plinko.o source\plinko.c
gcc %COMP_OPTS% -I%WHODUN_INC% -Isource -c -o %OBJDIR%\drift.o source\drift.c

gcc %LINK_OPTS% -o %BINDIR%\spht.exe %OBJDIR%\*.o -L%WHODUN_BIN% -lwhodun
