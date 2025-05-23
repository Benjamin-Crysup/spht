#ifndef WHODUN_ERMAC_H
#define WHODUN_ERMAC_H 1

/**
 * @file
 * @brief All the error messages used in this library.
 */

#include "whodun/error.h"

/**Assertion failure.*/
#define WHODUN_ERR_ID_ASSERT "whodun.assert"
/**Assertion failure.*/
#define WHODUN_ERR_MESS_ASSERT "Critical problem detected."

/**No more memory.*/
#define WHODUN_ERR_ID_NOMEMORY "whodun.nomem"
/**No more memory.*/
#define WHODUN_ERR_MESS_NOMEMORY "Problem allocating memory."

/**Problem reading standard stream.*/
#define WHODUN_ERR_ID_READSTDIN "whodun.std.in.read"
/**Problem reading standard stream.*/
#define WHODUN_ERR_MESS_READSTDIN "Problem reading standard input."

/**Problem writing standard stream.*/
#define WHODUN_ERR_ID_WRITESTDOUT "whodun.std.out.write"
/**Problem writing standard stream.*/
#define WHODUN_ERR_MESS_WRITESTDOUT "Problem reading standard output."

/**Problem writing standard stream.*/
#define WHODUN_ERR_ID_WRITESTDERR "whodun.std.err.write"
/**Problem writing standard stream.*/
#define WHODUN_ERR_MESS_WRITESTDERR "Problem reading standard error."

/**Problem getting a path.*/
#define WHODUN_ERR_ID_PATHPROB "whodun.path.bad"
/**Problem getting a path.*/
#define WHODUN_ERR_MESS_PATHPROB "Problem with provided path."

/**Problem fixing arguments.*/
#define WHODUN_ERR_ID_ARGSPROB "whodun.args.normal"
/**Problem fixing arguments.*/
#define WHODUN_ERR_MESS_ARGSPROB "Problem normalizing arguments."

/**Problem closing a file.*/
#define WHODUN_ERR_ID_CLOSEFILE "whodun.file.close"
/**Problem closing a file.*/
#define WHODUN_ERR_MESS_CLOSEFILE "Problem closing file."

/**Problem reading a file.*/
#define WHODUN_ERR_ID_READFILE "whodun.file.read"
/**Problem reading a file.*/
#define WHODUN_ERR_MESS_READFILE "Problem reading file."

/**Problem writing a file.*/
#define WHODUN_ERR_ID_WRITEFILE "whodun.file.write"
/**Problem writing a file.*/
#define WHODUN_ERR_MESS_WRITEFILE "Problem writing file."

/**Problem opening a file.*/
#define WHODUN_ERR_ID_OPENFILE "whodun.file.open"
/**Problem opening a file.*/
#define WHODUN_ERR_MESS_OPENFILE "Problem opening file."

/**Problem reading a folder.*/
#define WHODUN_ERR_ID_READFOLD "whodun.file.folder"
/**Problem reading a folder.*/
#define WHODUN_ERR_MESS_READFOLD "Problem reading folder."

/**Problem writing a folder.*/
#define WHODUN_ERR_ID_WRITEFOLD "whodun.file.folder"
/**Problem writing a folder.*/
#define WHODUN_ERR_MESS_WRITEFOLD "Problem writing folder."

/**Problem making a mutex.*/
#define WHODUN_ERR_ID_CANT_MUTEX "whodun.mutex.make"
/**Problem making a mutex.*/
#define WHODUN_ERR_MESS_CANT_MUTEX "Problem allocating mutex."

/**Problem making a condition variable.*/
#define WHODUN_ERR_ID_CANT_COND "whodun.cond.make"
/**Problem making a condition variable.*/
#define WHODUN_ERR_MESS_CANT_COND "Problem allocating condition variable."

/**Problem starting a thread.*/
#define WHODUN_ERR_ID_CANT_THREAD "whodun.thread.make"
/**Problem starting a thread.*/
#define WHODUN_ERR_MESS_CANT_THREAD "Problem starting thread."

/**Unknown command line argument.*/
#define WHODUN_ERR_ID_CLI_UNKNOWN "whodun.cli.unkarg"
/**Unknown command line argument.*/
#define WHODUN_ERR_MESS_CLI_UNKNOWN "Unknown command line argument."

/**Missing value for command line argument.*/
#define WHODUN_ERR_ID_CLI_MISSING "whodun.cli.missval"
/**Missing value for command line argument.*/
#define WHODUN_ERR_MESS_CLI_MISSING "Command line argument missing value."

/**Invalid integer for command line argument.*/
#define WHODUN_ERR_ID_CLI_BADINT "whodun.cli.badint"
/**Invalid integer for command line argument.*/
#define WHODUN_ERR_MESS_CLI_BADINT "Command line argument provided invalid integer."

/**Trying to write to read-only external array.*/
#define WHODUN_ERR_ID_EXTARR_READONLY "whodun.extarr.readonly"
/**Trying to write to read-only external array.*/
#define WHODUN_ERR_MESS_EXTARR_READONLY "External array is read only."

/**Trying to change size of fixed size external array.*/
#define WHODUN_ERR_ID_EXTARR_FIXSIZE "whodun.extarr.fixsize"
/**Trying to change size of fixed size external array.*/
#define WHODUN_ERR_MESS_EXTARR_FIXSIZE "External array cannot be resized."

/**Malformed fasta file.*/
#define WHODUN_ERR_ID_FORMAT_FASTA_MALFORM "whodun.format.fasta.bad"
/**Malformed fasta file.*/
#define WHODUN_ERR_MESS_FORMAT_FASTA_MALFORM "Fasta file malformed."

/**Malformed fastq file.*/
#define WHODUN_ERR_ID_FORMAT_FASTQ_MALFORM "whodun.format.fastq.bad"
/**Malformed fastq file.*/
#define WHODUN_ERR_MESS_FORMAT_FASTQ_MALFORM "Fastq file malformed."

/**Malformed pileup file.*/
#define WHODUN_ERR_ID_FORMAT_PILEUP_MALFORM "whodun.format.pileup.bad"
/**Malformed pileup file.*/
#define WHODUN_ERR_MESS_FORMAT_PILEUP_MALFORM "Pileup file malformed."


//TODO

/**
 * Convenience to mark a signal-level error.
 * @param name The name to use from the other macros in this file.
 * @param err The value of the error log pointer.
 */
#define WHODUN_ERR_MARK_SIGNAL(name, err) \
	{\
		struct whodun_ErrorInfo einf0;\
		einf0.type = WHODUN_ERROR_INFO_MENSAJE;\
		einf0.data.mensaje.id = whodun_byteArrayPackNull(WHODUN_ERR_ID_ ## name);\
		einf0.data.mensaje.mess = whodun_byteArrayPackNull(WHODUN_ERR_MESS_ ## name);\
		einf0.next = 0;\
		WHODUN_CFUN(whodun_ErrorLog, mark, (err))((err), WHODUN_ERROR_SEVERITY_SIGNAL, &einf0);\
	}

/**
 * Convenience to mark a signal-level error with an attached file name.
 * @param name The name to use from the other macros in this file.
 * @param fname The name of the problematic file, as a whodun_ByteArray.
 * @param err The value of the error log pointer.
 */
#define WHODUN_ERR_MARK_SIGNAL_FILENAME(name, fname, err) \
	{\
		struct whodun_ErrorInfo einf1;\
		einf1.type = WHODUN_ERROR_INFO_KEYVALUE;\
		einf1.data.keyval.key = whodun_byteArrayPackNull("FILE");\
		einf1.data.keyval.val = (fname);\
		struct whodun_ErrorInfo einf0;\
		einf0.type = WHODUN_ERROR_INFO_MENSAJE;\
		einf0.data.mensaje.id = whodun_byteArrayPackNull(WHODUN_ERR_ID_ ## name);\
		einf0.data.mensaje.mess = whodun_byteArrayPackNull(WHODUN_ERR_MESS_ ## name);\
		einf0.next = &einf1;\
		WHODUN_CFUN(whodun_ErrorLog, mark, (err))((err), WHODUN_ERROR_SEVERITY_SIGNAL, &einf0);\
	}

/**
 * Convenience to mark a panic-level error.
 * @param name The name to use from the other macros in this file.
 * @param err The value of the error log pointer.
 */
#define WHODUN_ERR_MARK_PANIC(name, err) \
	{\
		struct whodun_ErrorInfo einf0;\
		einf0.type = WHODUN_ERROR_INFO_MENSAJE;\
		einf0.data.mensaje.id = whodun_byteArrayPackNull(WHODUN_ERR_ID_ ## name);\
		einf0.data.mensaje.mess = whodun_byteArrayPackNull(WHODUN_ERR_MESS_ ## name);\
		einf0.next = 0;\
		WHODUN_CFUN(whodun_ErrorLog, mark, (err))((err), WHODUN_ERROR_SEVERITY_PANIC, &einf0);\
	}

#endif

