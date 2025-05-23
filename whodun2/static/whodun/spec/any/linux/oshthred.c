#include "whodun/oshook.h"

#include <pthread.h>

#include "whodun/ermac.h"

/**Simple pthread mutex.*/
struct whodun_Mutex {
	/**The actual lock.*/
	pthread_mutex_t actual;
};

whodun_UInt whodun_installedCPUs_imp(){
	#ifndef _SC_NPROCESSORS_ONLN
		return 1;
	#else
		long npro = sysconf(_SC_NPROCESSORS_ONLN);
		if(npro <= 0){ npro = 1; }
		return npro;
	#endif
}

struct whodun_Mutex* whodun_mutexAlloc_imp(struct whodun_ErrorLog* err){
	struct whodun_Mutex* toRet = (struct whodun_Mutex*)malloc(sizeof(struct whodun_Mutex));
	if(toRet){
		if(pthread_mutex_init(&(toRet->actual), 0)){
			free(toRet);
			toRet = 0;
		}
	}
	if(!toRet){
		//guarding because os initialize uses this
		if(err){ WHODUN_ERR_MARK_SIGNAL(CANT_MUTEX, err) }
	}
	return toRet;
}

whodun_Bool whodun_mutexTry_imp(struct whodun_Mutex* toL){
	return pthread_mutex_trylock(&(toL->actual)) == 0;
}

void whodun_mutexLock_imp(struct whodun_Mutex* toL){
	pthread_mutex_lock(&(toL->actual));
}

void whodun_mutexUnlock_imp(struct whodun_Mutex* toU){
	pthread_mutex_unlock(&(toU->actual));
}

void whodun_mutexFree_imp(struct whodun_Mutex* toK){
	pthread_mutex_destroy(&(toK->actual));
	free(toK);
}

/**Simple pthread condition.*/
struct whodun_Condition {
	/**The actual condition.*/
	pthread_cond_t actual;
};

struct whodun_Condition* whodun_condAlloc_imp(struct whodun_Mutex* forLock, struct whodun_ErrorLog* err){
	struct whodun_Condition* toRet = (struct whodun_Condition*)malloc(sizeof(struct whodun_Condition));
	if(toRet){
		if(pthread_cond_init(&(toRet->actual), 0)){
			free(toRet);
			toRet = 0;
		}
	}
	if(!toRet){
		WHODUN_ERR_MARK_SIGNAL(CANT_COND, err)
	}
	return toRet;
}

void whodun_condWait_imp(struct whodun_Mutex* forLock, struct whodun_Condition* onCond){
	pthread_cond_wait(&(onCond->actual), &(forLock->actual));
}

void whodun_condSignal_imp(struct whodun_Mutex* forLock, struct whodun_Condition* onCond){
	pthread_cond_signal(&(onCond->actual));
}

void whodun_condBroadcast_imp(struct whodun_Mutex* forLock, struct whodun_Condition* onCond){
	pthread_cond_broadcast(&(onCond->actual));
}

void whodun_condFree_imp(struct whodun_Mutex* forLock, struct whodun_Condition* toKill){
	pthread_cond_destroy(&(toKill->actual));
	free(toKill);
}

/**Simple pthread.*/
struct whodun_Thread {
	/**The actual thread.*/
	pthread_t actual;
	/**The function to call.*/
	void(*callFunc)(void*);
	/**The value passed to the function.*/
	void* callPass;
};

/**
 * The main function to pass to pthreads.
 * @param myPtrV The pointer to the relevant whodun_Thread.
 * @return null
 */
void* whodun_threadMain_imp(void* myPtrV){
	struct whodun_Thread* myPtr = (struct whodun_Thread*)myPtrV;
	myPtr->callFunc(myPtr->callPass);
	return 0;
}

struct whodun_Thread* whodun_threadStart_imp(void(*callFunc)(void*), void* callPass, struct whodun_ErrorLog* err){
	struct whodun_Thread* toRet = (struct whodun_Thread*)malloc(sizeof(struct whodun_Thread));
	if(toRet){
		toRet->callFunc = callFunc;
		toRet->callPass = callPass;
		if(pthread_create(&(toRet->actual), 0, whodun_threadMain_imp, toRet)){
			free(toRet);
			toRet = 0;
		}
	}
	if(!toRet){
		WHODUN_ERR_MARK_SIGNAL(CANT_THREAD, err)
	}
	return toRet;
}

void whodun_threadJoin_imp(struct whodun_Thread* toWait){
	pthread_join(toWait->actual, 0);
	free(toWait);
}


