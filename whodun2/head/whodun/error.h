#ifndef WHODUN_ERROR_H
#define WHODUN_ERROR_H 1

/**
 * @file
 * @brief How to mark errors.
 */

#include "whodun/defs.h"
#include "whodun/array.h"
#include "whodun/class.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
192-255 hard errors
128-191 exceptions (...)
64-127 weird execution (INFO through WARNING)
0-63 normal execution (NORMAL through DEBUG through PROGRESS)
*/

/**Something insane happened.*/
#define WHODUN_ERROR_SEVERITY_PANIC 255
/**An error happened.*/
#define WHODUN_ERROR_SEVERITY_ERROR 192

/**An unexpected kind of abnormal event happened.*/
#define WHODUN_ERROR_SEVERITY_SIGNAL 191
/**An expected and potentially recoverable kind of abnormal event happened.*/
#define WHODUN_ERROR_SEVERITY_EXCEPTION 128

/**Something technically legal happened.*/
#define WHODUN_ERROR_SEVERITY_WARNING 127
/**Something that might warrant later review happened.*/
#define WHODUN_ERROR_SEVERITY_INFO 64

/**Progress update for something expected to take a while.*/
#define WHODUN_ERROR_SEVERITY_PROGRESS 63
/**Normal execution, useful for debugging.*/
#define WHODUN_ERROR_SEVERITY_NORMAL 0

/**An error message.*/
#define WHODUN_ERROR_INFO_MESSAGE 1
/**A key-value pair.*/
#define WHODUN_ERROR_INFO_KEYVALUE 2
/**An internationalizable error message.*/
#define WHODUN_ERROR_INFO_MENSAJE 3

/**Information on an error.*/
struct whodun_ErrorInfo{
	/**The type of thing this is.*/
	int type;
	/**The data this carries.*/
	union{
		/**A message to pass for the error.*/
		struct whodun_ByteArray mess;
		/**A key-value pair belonging to the error.*/
		struct{
			/**The name of the key.*/
			struct whodun_ByteArray key;
			/**The name of the value.*/
			struct whodun_ByteArray val;
		} keyval;
		/**An internationalizable message to pass for the error.*/
		struct{
			/**An id for internationalization.*/
			struct whodun_ByteArray id;
			/**A default message to pass for the error.*/
			struct whodun_ByteArray mess;
		} mensaje;
	} data;
	/**The next piece of information in the chain, or null if none.*/
	struct whodun_ErrorInfo* next;
};


/**A place to log error information.*/
struct whodun_ErrorLog{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The maximum error severity since the last check.*/
	int maxErr;
};

/**The vtable layout for the ErrorLog class.*/
struct whodun_ErrorLog_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Note that something happened.
	 * @param self The instance.
	 * @param severity How severe was the thing.
	 * @param info The information chain on the error.
	 */
	void (*mark)(void* self, int severity, struct whodun_ErrorInfo* info);
};

/**
 * Get the vtable for the ErrorLog class.
 * @return The vtable for the ErrorLog class.
 */
extern struct whodun_ErrorLog_vtable_dec* (*whodun_ErrorLog_vtable)();


/**An error log that just eats all its input.*/
struct whodun_NullErrorLog{
	/**The super-class data.*/
	struct whodun_ErrorLog super;
};

/**The vtable layout for the NullErrorLog class.*/
struct whodun_NullErrorLog_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ErrorLog_vtable_dec super;
};

/**
 * Get the vtable for the NullErrorLog class.
 * @return The vtable for the NullErrorLog class.
 */
extern struct whodun_NullErrorLog_vtable_dec* (*whodun_NullErrorLog_vtable)();

/**An error log that simply wraps another.*/
struct whodun_PassErrorLog{
	/**The super-class data.*/
	struct whodun_ErrorLog super;
	/**The log to foward to, if any.*/
	struct whodun_ErrorLog* target;
};

/**The vtable layout for the PassErrorLog class.*/
struct whodun_PassErrorLog_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ErrorLog_vtable_dec super;
	/**
	 * Change where the log forwards to.
	 * @param self The instance.
	 * @param newTarget The new place to forward to.
	 */
	void (*retarget)(void* self, struct whodun_ErrorLog* newTarget);
};

/**
 * Get the vtable for the PassErrorLog class.
 * @return The vtable for the PassErrorLog class.
 */
extern struct whodun_PassErrorLog_vtable_dec* (*whodun_PassErrorLog_vtable)();

//error.h will always be included before stream.h
struct whodun_OutputStream;

/**An error log that posts to a stream.*/
struct whodun_StreamErrorLog{
	/**The super-class data.*/
	struct whodun_ErrorLog super;
	/**The stream it writes to, if any. Dropped on error.*/
	struct whodun_OutputStream* target;
	/**A log to use for writing to the stream, as well as to pass any errors to.*/
	struct whodun_PassErrorLog parrot;
};

/**The vtable layout for the StreamErrorLog class.*/
struct whodun_StreamErrorLog_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ErrorLog_vtable_dec super;
	/**
	 * Change where the log forwards to.
	 * @param self The instance.
	 * @param newTarget The new place to write to.
	 * @param newParrot The new place to forward to.
	 */
	void (*retarget)(void* self, struct whodun_OutputStream* newTarget, struct whodun_ErrorLog* newParrot);
};

/**
 * Get the vtable for the StreamErrorLog class.
 * @return The vtable for the StreamErrorLog class.
 */
extern struct whodun_StreamErrorLog_vtable_dec* (*whodun_StreamErrorLog_vtable)();

//Same for error.h and oshook.h
struct whodun_Mutex;

/**An error log that synchronizes marks.*/
struct whodun_SyncErrorLog{
	/**The super-class data.*/
	struct whodun_ErrorLog super;
	/**The lock for synchronization.*/
	struct whodun_Mutex* lock;
	/**The log to foward to, if any.*/
	struct whodun_ErrorLog* target;
};

/**The vtable layout for the SyncErrorLog class.*/
struct whodun_SyncErrorLog_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ErrorLog_vtable_dec super;
	/**
	 * Change where the log forwards to.
	 * @param self The instance.
	 * @param useLock The mutex to use for synchronizing.
	 * @param newTarget The new place to forward to.
	 */
	void (*retarget)(void* self, struct whodun_Mutex* useLock, struct whodun_ErrorLog* newTarget);
};

/**
 * Get the vtable for the SyncErrorLog class.
 * @return The vtable for the SyncErrorLog class.
 */
extern struct whodun_SyncErrorLog_vtable_dec* (*whodun_SyncErrorLog_vtable)();

/**
 * Test whether any errors have been reported to a log.
 * @param err The log to check.
 * @return Whether there have been any errors.
 */
#define WHODUN_WASERR(err) (*WHODUN_CVAR(whodun_ErrorLog, maxErr, err) >= WHODUN_ERROR_SEVERITY_EXCEPTION)

#ifdef __cplusplus
}
#endif

#endif

