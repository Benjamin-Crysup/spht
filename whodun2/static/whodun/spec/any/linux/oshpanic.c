#include "whodun/oshook.h"

#include <stdlib.h>
#include <string.h>

#include "whodun/ermac.h"

void whodun_panic_imp(const char* reason, struct whodun_ErrorLog* err){
	if(err){
		struct whodun_ErrorInfo einf0;
		einf0.type = WHODUN_ERROR_INFO_MESSAGE;
		einf0.data.mess = whodun_byteArrayPackNull(reason);
		einf0.next = 0;
		WHODUN_CFUN(whodun_ErrorLog, mark, err)(err, WHODUN_ERROR_SEVERITY_PANIC, &einf0);
	}
	abort();
}

