#include "whodun/oshook.h"

#include "whodun/cpu.h"
#include "whodun/ermac.h"
#include "whodun/contain.h"

//MinGW, why do you do this to me?
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif

//I demand Vista, for the condition variables (and appdata)
#define _WIN32_WINNT 0x0600
#include <windows.h>

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

/****************************************************************************/
/*Memory*/

whodun_UInt whodun_installedRAM_imp(){
	MEMORYSTATUSEX checkMS;
	checkMS.dwLength = sizeof(MEMORYSTATUSEX);
	if(GlobalMemoryStatusEx(&checkMS) == 0){ return 0x01000000; } //minimum requirement for NT 4
	return checkMS.ullTotalPhys;
}

whodun_UInt whodun_availableRAM_imp(){
	MEMORYSTATUSEX checkMS;
	checkMS.dwLength = sizeof(MEMORYSTATUSEX);
	if(GlobalMemoryStatusEx(&checkMS) == 0){ return 0x00100000; }
	return checkMS.ullAvailPhys;
}

void whodun_OSAllocator_initialize_imp(void* self){
	//nothing to do here
}

void whodun_OSAllocator_finalize_imp(void* self){
	//nothing to do here
}

void* whodun_OSAllocator_alloc_imp(void* self, whodun_UInt size, struct whodun_ErrorLog* err){
	if(size == 0){ return 0; }
	void* toRet = malloc(size);
	if(toRet){ return toRet; }
	//problem
	WHODUN_ERR_MARK_SIGNAL(NOMEMORY, err)
	return 0;
}

void* whodun_OSAllocator_realloc_imp(void* self, void* prev, whodun_UInt newS, struct whodun_ErrorLog* err){
	if(newS == 0){ return prev; }
	if(prev == 0){
		return WHODUN_CFUN(whodun_Allocator, alloc, self)(self, newS, err);
	}
	void* toRet = realloc(prev, newS);
	if(toRet){ return toRet; }
	//problem
	WHODUN_ERR_MARK_SIGNAL(NOMEMORY, err)
	return prev;
}

void whodun_OSAllocator_free_imp(void* self, void* toK){
	free(toK);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_OSAllocator, whodun_Allocator)
	needInit->super.super.finalize = whodun_OSAllocator_finalize_imp;
	needInit->super.super.initialize = whodun_OSAllocator_initialize_imp;
	needInit->super.alloc = whodun_OSAllocator_alloc_imp;
	needInit->super.realloc = whodun_OSAllocator_realloc_imp;
	needInit->super.free = whodun_OSAllocator_free_imp;
WHODUN_CVTABLE_FUN_END(whodun_OSAllocator)

struct whodun_OSAllocator whodun_heap_imp;

/****************************************************************************/
/*Stdio*/

HANDLE whodun_oshelp_saveStdinHandle;
HANDLE whodun_oshelp_saveStdoutHandle;
HANDLE whodun_oshelp_saveStderrHandle;

void whodun_StdinInputStream_initialize_imp(void* self){
	//nothing to do here
}

void whodun_StdinInputStream_finalize_imp(void* self){
	//nothing to do here
}

void whodun_StdinInputStream_close_imp(void* self, struct whodun_ErrorLog* err){
	*WHODUN_CVAR(whodun_Stream, haveClose, self) = 1;
}

whodun_UInt whodun_StdinInputStream_read_imp(void* self, char* buff, whodun_UInt max, struct whodun_ErrorLog* err){
	if(*WHODUN_CVAR(whodun_Stream, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return 0;
	}
	if(whodun_oshelp_saveStdinHandle == INVALID_HANDLE_VALUE){
		WHODUN_ERR_MARK_SIGNAL(READSTDIN, err)
		return 0;
	}
	char* curR = buff;
	whodun_UInt numLeft = max;
	while(numLeft){
		DWORD curNumR = (numLeft > 0x10000000) ? 0x10000000 : numLeft;
		DWORD numGot;
		if(ReadFile(whodun_oshelp_saveStdinHandle, curR, curNumR, &numGot, 0) == 0){
			WHODUN_ERR_MARK_SIGNAL(READSTDIN, err)
			return 0;
		}
		if(numGot == 0){ break; }
		*WHODUN_CVAR(whodun_Stream, totalBytes, self) += numGot;
		curR += numGot;
		numLeft -= numGot;
	}
	return (max - numLeft);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_StdinInputStream, whodun_InputStream)
	needInit->super.super.super.finalize = whodun_StdinInputStream_finalize_imp;
	needInit->super.super.super.initialize = whodun_StdinInputStream_initialize_imp;
	needInit->super.super.close = whodun_StdinInputStream_close_imp;
	needInit->super.read = whodun_StdinInputStream_read_imp;
WHODUN_CVTABLE_FUN_END(whodun_StdinInputStream)

struct whodun_StdinInputStream whodun_stdin_imp;

void whodun_StdoutOutputStream_initialize_imp(void* self){
	//nothing to do here
}

void whodun_StdoutOutputStream_finalize_imp(void* self){
	//nothing to do here
}

void whodun_StdoutOutputStream_close_imp(void* self, struct whodun_ErrorLog* err){
	*WHODUN_CVAR(whodun_Stream, haveClose, self) = 1;
}

void whodun_StdoutOuttputStream_write_imp(void* self, const char* buff, whodun_UInt num, struct whodun_ErrorLog* err){
	if(*WHODUN_CVAR(whodun_Stream, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	if(whodun_oshelp_saveStdoutHandle == INVALID_HANDLE_VALUE){
		WHODUN_ERR_MARK_SIGNAL(WRITESTDOUT, err)
		return;
	}
	const char* curW = buff;
	whodun_UInt numLeft = num;
	while(numLeft){
		DWORD curNumR = (numLeft > 0x10000000) ? 0x10000000 : numLeft;
		DWORD numWritten;
		if(WriteFile(whodun_oshelp_saveStdoutHandle, curW, curNumR, &numWritten, 0)==0){
			WHODUN_ERR_MARK_SIGNAL(WRITESTDOUT, err)
			return;
		}
		*WHODUN_CVAR(whodun_Stream, totalBytes, self) += curNumR;
		curW += curNumR;
		numLeft -= curNumR;
	}
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_StdoutOutputStream, whodun_OutputStream)
	needInit->super.super.super.finalize = whodun_StdoutOutputStream_finalize_imp;
	needInit->super.super.super.initialize = whodun_StdoutOutputStream_initialize_imp;
	needInit->super.super.close = whodun_StdoutOutputStream_close_imp;
	needInit->super.write = whodun_StdoutOuttputStream_write_imp;
WHODUN_CVTABLE_FUN_END(whodun_StdoutOutputStream)

struct whodun_StdoutOutputStream whodun_stdout_imp;

void whodun_StderrOutputStream_initialize_imp(void* self){
	//nothing to do here
}

void whodun_StderrOutputStream_finalize_imp(void* self){
	//nothing to do here
}

void whodun_StderrOutputStream_close_imp(void* self, struct whodun_ErrorLog* err){
	*WHODUN_CVAR(whodun_Stream, haveClose, self) = 1;
}

void whodun_StderrOuttputStream_write_imp(void* self, const char* buff, whodun_UInt num, struct whodun_ErrorLog* err){
	if(*WHODUN_CVAR(whodun_Stream, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	if(whodun_oshelp_saveStderrHandle == INVALID_HANDLE_VALUE){
		WHODUN_ERR_MARK_SIGNAL(WRITESTDERR, err)
		return;
	}
	const char* curW = buff;
	whodun_UInt numLeft = num;
	while(numLeft){
		DWORD curNumR = (numLeft > 0x10000000) ? 0x10000000 : numLeft;
		DWORD numWritten;
		if(WriteFile(whodun_oshelp_saveStderrHandle, curW, curNumR, &numWritten, 0)==0){
			WHODUN_ERR_MARK_SIGNAL(WRITESTDOUT, err)
			return;
		}
		*WHODUN_CVAR(whodun_Stream, totalBytes, self) += curNumR;
		curW += curNumR;
		numLeft -= curNumR;
	}
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_StderrOutputStream, whodun_OutputStream)
	needInit->super.super.super.finalize = whodun_StderrOutputStream_finalize_imp;
	needInit->super.super.super.initialize = whodun_StderrOutputStream_initialize_imp;
	needInit->super.super.close = whodun_StderrOutputStream_close_imp;
	needInit->super.write = whodun_StderrOuttputStream_write_imp;
WHODUN_CVTABLE_FUN_END(whodun_StderrOutputStream)

struct whodun_StderrOutputStream whodun_stderr_imp;

/****************************************************************************/
/*Folders*/

/**The actual definition. On Windows, utf-16 paths.*/
struct whodun_Path{
	/**The number of CHARACTERS, excluding the null terminator.*/
	size_t len;
	/**The characters. Part of this allocation.*/
	wchar_t* ptr;
	/**Whether this path has to be a folder.*/
	int mustFold;
};

struct whodun_Path* whodun_pathRoot_imp(struct whodun_ErrorLog* err){
	struct whodun_Path* toRet = (struct whodun_Path*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, sizeof(struct whodun_Path) + sizeof(wchar_t), err));
	if(WHODUN_WASERR(err)){ return 0; }
	toRet->len = 0;
	toRet->ptr = (wchar_t*)(toRet + 1);
	toRet->mustFold = 1;
	toRet->ptr[0] = 0;
	return toRet;
}

struct whodun_Path* whodun_oshelp_pathNormalizeW(wchar_t* toNorm, struct whodun_ErrorLog* err){
	struct whodun_Path* toRet = 0;
	//get the size of the normalized name
		DWORD reqNormSize = GetFullPathNameW(toNorm, 0, 0, 0);
		if(reqNormSize == 0){ goto err_path; }
	//allocate with a little extra space
		toRet = (struct whodun_Path*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, sizeof(struct whodun_Path) + (reqNormSize + 1)*sizeof(wchar_t), err));
		if(WHODUN_WASERR(err)){ goto err_cleanup; }
	//convert
		toRet->ptr = (wchar_t*)(toRet + 1);
		toRet->mustFold = 0;
		DWORD endNormSize = GetFullPathNameW(toNorm, reqNormSize, toRet->ptr, 0);
		if(endNormSize == 0){ goto err_path; }
	//if the last character is a \, drop
		if(toRet->ptr[endNormSize-1] == '\\'){ endNormSize--; }
	//if there are no backslashes in the name, add one
		int anyBS = 0;
		for(DWORD i = 0; i<endNormSize; i++){
			if(toRet->ptr[i] == '\\'){ anyBS = 1; break; }
		}
		if(!anyBS){
			toRet->mustFold = 1;
			toRet->ptr[endNormSize] = '\\';
			endNormSize++;
		}
	//null terminate
		toRet->ptr[endNormSize] = 0;
		toRet->len = endNormSize;
	return toRet;
	
	err_path:
		WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
	err_cleanup:
		if(toRet){ WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, toRet); }
	return 0;
}

struct whodun_Path* whodun_pathNormalize_imp(struct whodun_ByteArray prov, struct whodun_ErrorLog* err){
	wchar_t* convProv = 0;
	//if empty, return root
		if(prov.len == 0){ return whodun_pathRoot_imp(err); }
	//convert to utf-16 and null terminate
		int reqConvSize = MultiByteToWideChar(CP_UTF8, 0, prov.ptr, prov.len, 0, 0);
		if(reqConvSize == 0){ goto err_path; }
		convProv = (wchar_t*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, (reqConvSize + 1)*sizeof(wchar_t), err));
		if(WHODUN_WASERR(err)){ goto err_cleanup; }
		int endConvSize = MultiByteToWideChar(CP_UTF8, 0, prov.ptr, prov.len, convProv, reqConvSize);
		if(endConvSize == 0){ goto err_path; }
		convProv[endConvSize] = 0;
	//and normalize
		struct whodun_Path* toRet = whodun_oshelp_pathNormalizeW(convProv, err);
	//clean up and return
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, convProv);
		return toRet;
	
	err_path:
		WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
	err_cleanup:
		if(convProv){ WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, convProv); }
	return 0;
}

struct whodun_Path* whodun_pathGetParent_imp(struct whodun_Path* ofPath, struct whodun_ErrorLog* err){
	size_t slen = ofPath->len;
	wchar_t* sptr = ofPath->ptr;
	//skip any ending backslash
		if(sptr[slen-1] == '\\'){ slen--; }
	//chew backwards to a backslash
		while(slen && (sptr[slen] != '\\')){ slen--; }
	//if nothing left, return root
		if(slen == 0){
			return whodun_pathRoot_imp(err);
		}
	//if the path has no other backslash, keep the ending backslash (drive letter)
		size_t tlen = slen;
		while(tlen){
			if(sptr[tlen-1] == '\\'){ break; }
			tlen--;
		}
		if(tlen == 0){ slen++; }
	//make a new thing
		struct whodun_Path* toRet = (struct whodun_Path*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, sizeof(struct whodun_Path) + (slen + 1)*sizeof(wchar_t), err));
		if(WHODUN_WASERR(err)){ return 0; }
		toRet->len = slen;
		toRet->ptr = (wchar_t*)(toRet + 1);
		toRet->mustFold = 1;
		memcpy(toRet->ptr, sptr, slen*sizeof(wchar_t));
		toRet->ptr[slen] = 0;
		return toRet;
}

struct whodun_Path* whodun_pathGetChild_imp(struct whodun_Path* ofPath, struct whodun_ByteArray name, struct whodun_ErrorLog* err){
	size_t slen = ofPath->len;
	wchar_t* sptr = ofPath->ptr;
	//figure out how long the conversion from utf-8 is
		int reqConvSize = MultiByteToWideChar(CP_UTF8, 0, name.ptr, name.len, 0, 0);
		if(reqConvSize == 0){
			WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
			return 0;
		}
	//if the path is root, adding a drive letter
		if(slen == 0){
			struct whodun_Path* toRet = (struct whodun_Path*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, sizeof(struct whodun_Path) + (reqConvSize + 2)*sizeof(wchar_t), err));
			if(WHODUN_WASERR(err)){ return 0; }
			toRet->ptr = (wchar_t*)(toRet + 1);
			toRet->mustFold = 1;
			int endConvSize = MultiByteToWideChar(CP_UTF8, 0, name.ptr, name.len, toRet->ptr, reqConvSize);
			if(endConvSize == 0){
				WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, toRet);
				WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
				return 0;
			}
			toRet->ptr[endConvSize] = '\\';
			toRet->ptr[endConvSize+1] = 0;
			toRet->len = endConvSize + 1;
			return toRet;
		}
	//drop any ending backslash
		if(sptr[slen-1] == '\\'){ slen--; }
	//make it
		struct whodun_Path* toRet = (struct whodun_Path*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, sizeof(struct whodun_Path) + (slen + 1 + reqConvSize + 1)*sizeof(wchar_t), err));
		if(WHODUN_WASERR(err)){ return 0; }
		toRet->ptr = (wchar_t*)(toRet + 1);
		toRet->mustFold = 0;
		memcpy(toRet->ptr, sptr, slen*sizeof(wchar_t));
		toRet->ptr[slen] = '\\';
		int endConvSize = MultiByteToWideChar(CP_UTF8, 0, name.ptr, name.len, toRet->ptr + slen + 1, reqConvSize);
		if(endConvSize == 0){
			WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, toRet);
			WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
			return 0;
		}
		toRet->len = slen + 1 + endConvSize;
		toRet->ptr[toRet->len] = 0;
		return toRet;
}

whodun_Bool whodun_pathIsRoot_imp(struct whodun_Path* test){
	return test->len == 0;
}

whodun_Bool whodun_pathCanFile_imp(struct whodun_Path* test){
	return test->mustFold == 0;
}

whodun_Bool whodun_pathCanFolder_imp(struct whodun_Path* test){
	return 1;
}

void whodun_pathFree_imp(struct whodun_Path* toK){
	WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, toK);
}

struct whodun_Path* whodun_pathGetCWD_imp(struct whodun_ErrorLog* err){
	//Get the name
		DWORD reqConvSize = GetCurrentDirectoryW(0,0);
		if(reqConvSize == 0){
			WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
			return 0;
		}
	//allocate space
		wchar_t* convProv = (wchar_t*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, (reqConvSize)*sizeof(wchar_t), err));
		if(WHODUN_WASERR(err)){ return 0; }
	//get the directory
		DWORD endConvSize = GetCurrentDirectoryW(reqConvSize, convProv);
		if(endConvSize == 0){
			WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, convProv);
			WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
			return 0;
		}
	//normalize
		struct whodun_Path* toRet = whodun_oshelp_pathNormalizeW(convProv, err);
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, convProv);
	return toRet;
}

struct whodun_Path* whodun_oshelp_getPathFromEnv(wchar_t* envName, struct whodun_ErrorLog* err){
	//get the required size
		DWORD reqConvSize = GetEnvironmentVariableW(envName, 0, 0);
		if(reqConvSize == 0){
			WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
			return 0;
		}
	//make space and get it
		wchar_t* convProv = (wchar_t*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, (reqConvSize)*sizeof(wchar_t), err));
		if(WHODUN_WASERR(err)){ return 0; }
		DWORD endConvSize = GetEnvironmentVariableW(envName, convProv, reqConvSize);
		if(endConvSize == 0){
			WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, convProv);
			WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
			return 0;
		}
	//normalize
		struct whodun_Path* toRet = whodun_oshelp_pathNormalizeW(convProv, err);
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, convProv);
	return toRet;
}

struct whodun_Path* whodun_pathGetTmp_imp(struct whodun_ErrorLog* err){
	return whodun_oshelp_getPathFromEnv(L"TEMP", err);
}

struct whodun_Path* whodun_pathGetHome_imp(struct whodun_ErrorLog* err){
	return whodun_oshelp_getPathFromEnv(L"USERPROFILE", err);
}

struct whodun_Path* whodun_pathGetDataRoam_imp(struct whodun_ErrorLog* err){
	return whodun_oshelp_getPathFromEnv(L"APPDATA", err);
}

struct whodun_Path* whodun_pathGetDataLocal_imp(struct whodun_ErrorLog* err){
	return whodun_oshelp_getPathFromEnv(L"LOCALAPPDATA", err);
}

whodun_Bool whodun_pathIsFile_imp(struct whodun_Path* test, struct whodun_ErrorLog* err){
	if(test->mustFold){ return 0; }
	DWORD fileType = GetFileAttributesW(test->ptr);
	if(fileType == INVALID_FILE_ATTRIBUTES){ return 0; }
	if(fileType & FILE_ATTRIBUTE_DIRECTORY){ return 0; }
	return 1;
}

void whodun_pathFileDelete_imp(struct whodun_Path* kill, struct whodun_ErrorLog* err){
	int delGood = DeleteFileW(kill->ptr);
	if(!delGood){
		struct whodun_ByteArray fileN = whodun_byteArrayPack(2*kill->len, (char*)kill->ptr);
		WHODUN_ERR_MARK_SIGNAL_FILENAME(WRITEFILE, fileN, err)
	}
}

whodun_MaxUInt whodun_pathFileSize_imp(struct whodun_Path* check, struct whodun_ErrorLog* err){
	if(check->len == 0){
		WHODUN_ERR_MARK_SIGNAL(READFILE, err)
		return 0;
	}
	WIN32_FILE_ATTRIBUTE_DATA fileDat;
	int infoGood = GetFileAttributesExW(check->ptr, GetFileExInfoStandard, &fileDat);
	if(infoGood){
		whodun_MaxUInt word0 = 0x00FFFF & fileDat.nFileSizeLow;
		whodun_MaxUInt word1 = 0x00FFFF & (fileDat.nFileSizeLow >> 16);
		whodun_MaxUInt word2 = 0x00FFFF & fileDat.nFileSizeHigh;
		whodun_MaxUInt word3 = 0x00FFFF & (fileDat.nFileSizeHigh >> 16);
		whodun_MaxUInt endS = word3;
			endS = (endS << 16) | word2;
			endS = (endS << 16) | word1;
			endS = (endS << 16) | word0;
		return endS;
	}
	else{
		struct whodun_ByteArray fileN = whodun_byteArrayPack(2*check->len, (char*)check->ptr);
		WHODUN_ERR_MARK_SIGNAL_FILENAME(WRITEFILE, fileN, err)
		return 0;
	}
}

whodun_Bool whodun_pathIsFold_imp(struct whodun_Path* test, struct whodun_ErrorLog* err){
	if(test->len == 0){ return 1; }
	DWORD fileType = GetFileAttributesW(test->ptr);
	if(fileType == INVALID_FILE_ATTRIBUTES){ return 0; }
	if(fileType & FILE_ATTRIBUTE_DIRECTORY){ return 1; }
	return 0;
}

void whodun_pathFoldCreate_imp(struct whodun_Path* llik, struct whodun_ErrorLog* err){
	int delGood = CreateDirectoryW(llik->ptr, 0);
	if(!delGood){
		struct whodun_ByteArray fileN = whodun_byteArrayPack(2*llik->len, (char*)llik->ptr);
		WHODUN_ERR_MARK_SIGNAL_FILENAME(WRITEFOLD, fileN, err)
	}
}

void whodun_pathFoldDelete_imp(struct whodun_Path* kill, struct whodun_ErrorLog* err){
	int delGood = RemoveDirectoryW(kill->ptr);
	if(!delGood){
		struct whodun_ByteArray fileN = whodun_byteArrayPack(2*kill->len, (char*)kill->ptr);
		WHODUN_ERR_MARK_SIGNAL_FILENAME(WRITEFOLD, fileN, err)
	}
}

//It was started, and something was found and is currently waiting.
#define DIR_ITER_FOLD_STATUS_HOT 2
//It was started and should move forward on next query
#define DIR_ITER_FOLD_STATUS_ACTIVE 1
//It was not started because the parent folder was empty.
#define DIR_ITER_FOLD_STATUS_DEAD 0

/**Iterate through a folder.*/
struct whodun_DirIter_Fold{
	/**The status of this iteration.*/
	int startStatus;
	/**Storage for find data.*/
	WIN32_FIND_DATAW findDat;
	/**The handle to the directory.*/
	HANDLE hFind;
};

/**Iterate through drives.*/
struct whodun_DirIter_Drive{
	/**The next drive to report. Double null terminated.*/
	wchar_t* curDrive;
	/**Enforce alignment requirements.*/
	wchar_t lineup;
};

#define DIR_ITER_TYPE_FOLDER 0
#define DIR_ITER_TYPE_DRIVE 1

/**An active directory iteration.*/
struct whodun_DirIter{
	/**The type of iteration this is.*/
	int iterType;
	/**Temporary storage.*/
	struct whodun_ByteVector tempStore;
	/**Different ways this can go down.*/
	union{
		/**Iterate through the contents of a folder.*/
		struct whodun_DirIter_Fold fold;
		/**Iterate through drive letters.*/
		struct whodun_DirIter_Drive drive;
	} p;
};

struct whodun_DirIter* whodun_pathFoldIterOpen_imp(struct whodun_Path* check, struct whodun_ErrorLog* err){
	if(check->len == 0){
		//iterate through drive letters
		//note how much space is necessary
			DWORD reqConvSize = GetLogicalDriveStringsW(0,0);
			if(reqConvSize == 0){
				struct whodun_ByteArray fileN = whodun_byteArrayPack(2*check->len, (char*)check->ptr);
				WHODUN_ERR_MARK_SIGNAL_FILENAME(READFOLD, fileN, err)
				return 0;
			}
		//allocate
			struct whodun_DirIter* toRet = (struct whodun_DirIter*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, sizeof(struct whodun_DirIter) + reqConvSize*sizeof(wchar_t), err));
			if(WHODUN_WASERR(err)){ return 0; }
			toRet->iterType = DIR_ITER_TYPE_DRIVE;
			toRet->p.drive.curDrive = 0;
		//get the things (insert an extra null at the start)
			toRet->p.drive.lineup = 0;
			DWORD endConvSize = GetLogicalDriveStringsW(reqConvSize, 1 + &(toRet->p.drive.lineup));
			if(endConvSize == 0){
				WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, toRet);
				struct whodun_ByteArray fileN = whodun_byteArrayPack(2*check->len, (char*)check->ptr);
				WHODUN_ERR_MARK_SIGNAL_FILENAME(READFOLD, fileN, err)
				return 0;
			}
		//make an array
			whodun_byteVectorInit(&(toRet->tempStore), whodun_heap, err);
			if(WHODUN_WASERR(err)){
				WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, toRet);
				return 0;
			}
		return toRet;
	}
	else{
		//actual iteration
		//allocate the iterator
			struct whodun_DirIter* toRet = (struct whodun_DirIter*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, sizeof(struct whodun_DirIter), err));
			if(WHODUN_WASERR(err)){ return 0; }
			toRet->iterType = DIR_ITER_TYPE_FOLDER;
		//and byte storage
			whodun_byteVectorInit(&(toRet->tempStore), whodun_heap, err);
			if(WHODUN_WASERR(err)){
				WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, toRet);
				return 0;
			}
		//create a search string
			whodun_byteVectorResize(&(toRet->tempStore), (check->len + 3)*sizeof(wchar_t), err);
			if(WHODUN_WASERR(err)){
				whodun_byteVectorFin(&(toRet->tempStore));
				WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, toRet);
				return 0;
			}
			wchar_t* tempSP = (wchar_t*)(toRet->tempStore.view.ptr);
			whodun_UInt bsInd = (check->ptr[check->len-1] == '\\') ? check->len-1 : check->len;
			memcpy(tempSP, check->ptr, check->len * sizeof(wchar_t));
			tempSP[bsInd] = '\\';
			tempSP[bsInd+1] = '*';
			tempSP[bsInd+2] = 0;
		//start the search
			toRet->p.fold.hFind = FindFirstFileW(tempSP, &(toRet->p.fold.findDat));
			if(toRet->p.fold.hFind == INVALID_HANDLE_VALUE){
				whodun_byteVectorFin(&(toRet->tempStore));
				WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, toRet);
				struct whodun_ByteArray fileN = whodun_byteArrayPack(2*check->len, (char*)check->ptr);
				WHODUN_ERR_MARK_SIGNAL_FILENAME(READFOLD, fileN, err)
				return 0;
			}
			else{
				toRet->p.fold.startStatus = DIR_ITER_FOLD_STATUS_HOT;
			}
		return toRet;
	}
}

whodun_Bool whodun_pathFoldIterNext_imp(struct whodun_DirIter* iter, struct whodun_ErrorLog* err){
	switch(iter->iterType){
		case DIR_ITER_TYPE_FOLDER:{
			if(iter->p.fold.startStatus == DIR_ITER_FOLD_STATUS_DEAD){ return 0; }
			//advance the iteration
			fix_it_again_tony:
				if(iter->p.fold.startStatus == DIR_ITER_FOLD_STATUS_HOT){
					iter->p.fold.startStatus = DIR_ITER_FOLD_STATUS_ACTIVE;
				}
				else{
					if(FindNextFileW(iter->p.fold.hFind, &(iter->p.fold.findDat)) == 0){
						if(GetLastError() != ERROR_NO_MORE_FILES){
							WHODUN_ERR_MARK_SIGNAL(READFOLD, err)
						}
						return 0;
					}
				}
			//if it is . or .., skip
				wchar_t* curFoc = iter->p.fold.findDat.cFileName;
				if(curFoc[0] == '.'){
					if(curFoc[1] == 0){ goto fix_it_again_tony; }
					if((curFoc[1] == '.') && (curFoc[2] == 0)){ goto fix_it_again_tony; }
				}
			//unpack the name
				int reqConvSize = WideCharToMultiByte(CP_UTF8, 0, curFoc, -1, 0, 0, 0, 0);
				if(reqConvSize == 0){
					WHODUN_ERR_MARK_SIGNAL(READFOLD, err)
					return 0;
				}
				whodun_byteVectorResize(&(iter->tempStore), reqConvSize, err);
				if(WHODUN_WASERR(err)){ return 0; }
				int endConvSize = WideCharToMultiByte(CP_UTF8, 0, curFoc, -1, iter->tempStore.view.ptr, reqConvSize, 0, 0);
				if(endConvSize == 0){
					WHODUN_ERR_MARK_SIGNAL(READFOLD, err)
					return 0;
				}
				iter->tempStore.view.len = endConvSize - 1;
			return 1;
		} break;
		case DIR_ITER_TYPE_DRIVE:{
			wchar_t* curFoc = iter->p.drive.curDrive ? iter->p.drive.curDrive : &(iter->p.drive.lineup);
			while(*curFoc){ curFoc++; }
			curFoc++;
			iter->p.drive.curDrive = curFoc;
			if(*curFoc){
				//figure out how to convert to utf-8
					int reqConvSize = WideCharToMultiByte(CP_UTF8, 0, curFoc, -1, 0, 0, 0, 0);
					if(reqConvSize == 0){
						WHODUN_ERR_MARK_SIGNAL(READFOLD, err)
						return 0;
					}
				//resize and do so
					whodun_byteVectorResize(&(iter->tempStore), reqConvSize, err);
					if(WHODUN_WASERR(err)){ return 0; }
					int endConvSize = WideCharToMultiByte(CP_UTF8, 0, curFoc, -1, iter->tempStore.view.ptr, reqConvSize, 0, 0);
					if(endConvSize == 0){
						WHODUN_ERR_MARK_SIGNAL(READFOLD, err)
						return 0;
					}
				//replace null with a colon
					iter->tempStore.view.len = endConvSize;
					iter->tempStore.view.ptr[endConvSize-1] = ':';
				return 1;
			}
			else{
				return 0;
			}
		} break;
		default:
			whodun_panic_imp("Illegal case.", err);
			return 0;
	};
}

struct whodun_ByteArray whodun_pathFoldIterName_imp(struct whodun_DirIter* iter){
	return iter->tempStore.view;
}

whodun_UInt whodun_pathFoldIterType_imp(struct whodun_DirIter* iter){
	switch(iter->iterType){
		case DIR_ITER_TYPE_FOLDER:{
			return (iter->p.fold.findDat.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? WHODUN_DIRITER_TYPE_FOLD : WHODUN_DIRITER_TYPE_FILE;
		} break;
		case DIR_ITER_TYPE_DRIVE:{
			return WHODUN_DIRITER_TYPE_FOLD;
		} break;
		default:
			whodun_panic_imp("Illegal case.", 0);
			return WHODUN_DIRITER_TYPE_ODD;
	};
}

void whodun_pathFoldIterClose_imp(struct whodun_DirIter* kill){
	switch(kill->iterType){
		case DIR_ITER_TYPE_FOLDER:{
			if(kill->p.fold.startStatus != DIR_ITER_FOLD_STATUS_DEAD){
				FindClose(kill->p.fold.hFind);
			}
		} break;
		case DIR_ITER_TYPE_DRIVE:{
			//nothing to do
		} break;
		default:
			whodun_panic_imp("Illegal case.", 0);
	};
	whodun_byteVectorFin(&(kill->tempStore));
	WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, kill);
}

/****************************************************************************/
/*Files*/

whodun_UInt whodun_os_help_readHandle(HANDLE baseHand, char* buff, whodun_UInt max, struct whodun_ByteArray* fileName, struct whodun_ErrorLog* err){
	char* nextB = buff;
	whodun_UInt leftC = max;
	while(leftC){
		DWORD curNum = (leftC > 0x01000000) ? 0x01000000 : leftC;
		DWORD actNum;
		if(ReadFile(baseHand, nextB, curNum, &actNum, 0) == 0){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(READFILE, *fileName, err);
			break;
		}
		nextB += actNum;
		leftC -= actNum;
		if(actNum != curNum){ break; }
	}
	return max - leftC;
}

void whodun_os_help_writeHandle(HANDLE baseHand, const char* buff, whodun_UInt num, struct whodun_ByteArray* fileName, struct whodun_ErrorLog* err){
	const char* nextB = buff;
	whodun_UInt leftC = num;
	while(leftC){
		DWORD curNum = (leftC > 0x01000000) ? 0x01000000 : leftC;
		DWORD actNum;
		if(WriteFile(baseHand, nextB, curNum, &actNum, 0) == 0){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(WRITEFILE, *fileName, err);
			break;
		}
		nextB += actNum;
		leftC -= actNum;
	}
}

void whodun_os_help_seekHandle(HANDLE baseHand, whodun_MaxUInt toOff, struct whodun_ByteArray* fileName, struct whodun_ErrorLog* err){
	LONG low32 = toOff;
	LONG hig32 = (toOff >> 16) >> 16;
	DWORD retOffset = SetFilePointer(baseHand, low32, &hig32, FILE_BEGIN);
	if((retOffset == INVALID_SET_FILE_POINTER) && (GetLastError() != NO_ERROR)){
		WHODUN_ERR_MARK_SIGNAL_FILENAME(READFILE, *fileName, err)
		return;
	}
}

void whodun_FileInputStream_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_FileInputStream, baseHandle, self) = (void*)0;
	*WHODUN_CVAR(whodun_FileInputStream, saveName, self) = whodun_byteArrayPack(0, 0);
}

void whodun_FileInputStream_finalize_imp(void* self){
	if(WHODUN_CVAR(whodun_FileInputStream, saveName, self)->len){
		free(WHODUN_CVAR(whodun_FileInputStream, saveName, self)->ptr);
	}
}

void whodun_FileInputStream_close_imp(void* self, struct whodun_ErrorLog* err){
	whodun_Bool* closeP = WHODUN_CVAR(whodun_Stream, haveClose, self);
	if(*closeP){ return; }
	*closeP = 1;
	HANDLE baseHand = (*WHODUN_CVAR(whodun_FileInputStream, baseHandle, self));
	if(baseHand){
		if(CloseHandle(baseHand) == 0){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(CLOSEFILE, *WHODUN_CVAR(whodun_FileOutputStream, saveName, self), err)
		}
	}
}

whodun_UInt whodun_FileInputStream_read_imp(void* self, char* buff, whodun_UInt max, struct whodun_ErrorLog* err){
	HANDLE baseHand = (*WHODUN_CVAR(whodun_FileInputStream, baseHandle, self));
	if(!baseHand || *WHODUN_CVAR(whodun_Stream, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return 0;
	}
	whodun_UInt actNum = whodun_os_help_readHandle(baseHand, buff, max, WHODUN_CVAR(whodun_FileInputStream, saveName, self), err);
	*WHODUN_CVAR(whodun_Stream, totalBytes, self) += actNum;
	return actNum;
}
/**Helper method for opening.*/
void whodun_FileInputStream_open_base(void* self, const wchar_t* path, struct whodun_ErrorLog* err){
	//idiot check
		void** baseHandP = WHODUN_CVAR(whodun_FileInputStream, baseHandle, self);
		if(*baseHandP){
			WHODUN_ERR_MARK_PANIC(ASSERT, err)
			return;
		}
	//make a working copy of the name
		size_t pathL = 0;
		while(path[pathL]){ pathL++; }
		pathL++;
		wchar_t* pathCpyAl = (wchar_t*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, pathL*sizeof(wchar_t), err));
		if(WHODUN_WASERR(err)){ return; }
		memcpy(pathCpyAl, path, pathL*sizeof(wchar_t));
		struct whodun_ByteArray pathCpyAr = whodun_byteArrayPack(pathL*sizeof(wchar_t),(char*)pathCpyAl);
	//open and check
		HANDLE hotHand = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
		if(hotHand == INVALID_HANDLE_VALUE){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(OPENFILE, pathCpyAr, err)
			WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, pathCpyAl);
			return;
		}
	*baseHandP = hotHand;
	*WHODUN_CVAR(whodun_FileInputStream, saveName, self) = pathCpyAr;
}
void whodun_FileInputStream_open_imp(void* self, struct whodun_Path* path, struct whodun_ErrorLog* err){
	whodun_FileInputStream_open_base(self, path->ptr, err);
}
void whodun_FileInputStream_openRaw_imp(void* self, struct whodun_ByteArray path, struct whodun_ErrorLog* err){
	wchar_t* convProv = 0;
	//convert to utf-16 and null terminate
		int reqConvSize = MultiByteToWideChar(CP_UTF8, 0, path.ptr, path.len, 0, 0);
		if(reqConvSize == 0){ goto err_path; }
		convProv = (wchar_t*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, (reqConvSize + 1)*sizeof(wchar_t), err));
		if(WHODUN_WASERR(err)){ goto err_cleanup; }
		int endConvSize = MultiByteToWideChar(CP_UTF8, 0, path.ptr, path.len, convProv, reqConvSize);
		if(endConvSize == 0){ goto err_path; }
		convProv[endConvSize] = 0;
	//do it
		whodun_FileInputStream_open_base(self, convProv, err);
	//clean up
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, convProv);
	return;
	
	err_path:
		WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
	err_cleanup:
		if(convProv){ WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, convProv); }
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_FileInputStream, whodun_InputStream)
	needInit->super.super.super.finalize = whodun_FileInputStream_finalize_imp;
	needInit->super.super.super.initialize = whodun_FileInputStream_initialize_imp;
	needInit->super.super.close = whodun_FileInputStream_close_imp;
	needInit->super.read = whodun_FileInputStream_read_imp;
	needInit->open = whodun_FileInputStream_open_imp;
	needInit->openRaw = whodun_FileInputStream_openRaw_imp;
WHODUN_CVTABLE_FUN_END(whodun_FileInputStream)

void whodun_FileOutputStream_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_FileOutputStream, baseHandle, self) = (void*)0;
	*WHODUN_CVAR(whodun_FileOutputStream, saveName, self) = whodun_byteArrayPack(0, 0);
}

void whodun_FileOutputStream_finalize_imp(void* self){
	if(WHODUN_CVAR(whodun_FileOutputStream, saveName, self)->len){
		free(WHODUN_CVAR(whodun_FileOutputStream, saveName, self)->ptr);
	}
}

void whodun_FileOutputStream_close_imp(void* self, struct whodun_ErrorLog* err){
	whodun_Bool* closeP = WHODUN_CVAR(whodun_Stream, haveClose, self);
	if(*closeP){ return; }
	*closeP = 1;
	HANDLE baseHand = (*WHODUN_CVAR(whodun_FileOutputStream, baseHandle, self));
	if(baseHand){
		if(CloseHandle(baseHand) == 0){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(CLOSEFILE, *WHODUN_CVAR(whodun_FileOutputStream, saveName, self), err)
		}
	}
}

void whodun_FileOutputStream_write_imp(void* self, const char* buff, whodun_UInt num, struct whodun_ErrorLog* err){
	HANDLE baseHand = (*WHODUN_CVAR(whodun_FileOutputStream, baseHandle, self));
	if(!baseHand || *WHODUN_CVAR(whodun_Stream, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	whodun_os_help_writeHandle(baseHand, buff, num, WHODUN_CVAR(whodun_FileOutputStream, saveName, self), err);
	if(WHODUN_WASERR(err)){ return; }
	*WHODUN_CVAR(whodun_Stream, totalBytes, self) += num;
}
/**Helper method for opening.*/
void whodun_FileOutputStream_open_base(void* self, const wchar_t* path, struct whodun_ErrorLog* err){
	//idiot check
		void** baseHandP = WHODUN_CVAR(whodun_FileOutputStream, baseHandle, self);
		if(*baseHandP){
			WHODUN_ERR_MARK_PANIC(ASSERT, err)
			return;
		}
	//make a working copy of the name
		size_t pathL = 0;
		while(path[pathL]){ pathL++; }
		pathL++;
		wchar_t* pathCpyAl = (wchar_t*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, pathL*sizeof(wchar_t), err));
		if(WHODUN_WASERR(err)){ return; }
		memcpy(pathCpyAl, path, pathL*sizeof(wchar_t));
		struct whodun_ByteArray pathCpyAr = whodun_byteArrayPack(pathL*sizeof(wchar_t),(char*)pathCpyAl);
	//open and check
		HANDLE hotHand = CreateFileW(path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
		if(hotHand == INVALID_HANDLE_VALUE){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(OPENFILE, pathCpyAr, err)
			WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, pathCpyAl);
			return;
		}
	*baseHandP = hotHand;
	*WHODUN_CVAR(whodun_FileOutputStream, saveName, self) = pathCpyAr;
}
void whodun_FileOutputStream_open_imp(void* self, struct whodun_Path* path, struct whodun_ErrorLog* err){
	whodun_FileOutputStream_open_base(self, path->ptr, err);
}
void whodun_FileOutputStream_openRaw_imp(void* self, struct whodun_ByteArray path, struct whodun_ErrorLog* err){
	wchar_t* convProv = 0;
	//convert to utf-16 and null terminate
		int reqConvSize = MultiByteToWideChar(CP_UTF8, 0, path.ptr, path.len, 0, 0);
		if(reqConvSize == 0){ goto err_path; }
		convProv = (wchar_t*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, (reqConvSize + 1)*sizeof(wchar_t), err));
		if(WHODUN_WASERR(err)){ goto err_cleanup; }
		int endConvSize = MultiByteToWideChar(CP_UTF8, 0, path.ptr, path.len, convProv, reqConvSize);
		if(endConvSize == 0){ goto err_path; }
		convProv[endConvSize] = 0;
	//do it
		whodun_FileOutputStream_open_base(self, convProv, err);
	//clean up
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, convProv);
	return;
	
	err_path:
		WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
	err_cleanup:
		if(convProv){ WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, convProv); }
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_FileOutputStream, whodun_OutputStream)
	needInit->super.super.super.finalize = whodun_FileOutputStream_finalize_imp;
	needInit->super.super.super.initialize = whodun_FileOutputStream_initialize_imp;
	needInit->super.super.close = whodun_FileOutputStream_close_imp;
	needInit->super.write = whodun_FileOutputStream_write_imp;
	needInit->open = whodun_FileOutputStream_open_imp;
	needInit->openRaw = whodun_FileOutputStream_openRaw_imp;
WHODUN_CVTABLE_FUN_END(whodun_FileOutputStream)


void whodun_FileReadExternalArray_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_FileReadExternalArray, baseHandle, self) = 0;
	*WHODUN_CVAR(whodun_FileReadExternalArray, saveName, self) = whodun_byteArrayPack(0, 0);
}

void whodun_FileReadExternalArray_finalize_imp(void* self){
	if(WHODUN_CVAR(whodun_FileReadExternalArray, saveName, self)->len){
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, WHODUN_CVAR(whodun_FileReadExternalArray, saveName, self)->ptr);
		whodun_byteVectorFin(WHODUN_CVAR(whodun_FileReadExternalArray, baseView, self));
	}
}

void whodun_FileReadExternalArray_close_imp(void* self, struct whodun_ErrorLog* err){
	whodun_Bool* closeP = WHODUN_CVAR(whodun_ExternalArray, haveClose, self);
	if(*closeP){ return; }
	*closeP = 1;
	HANDLE baseHand = *WHODUN_CVAR(whodun_FileReadExternalArray, baseHandle, self);
	if(baseHand){
		if(CloseHandle(baseHand) == 0){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(CLOSEFILE, *WHODUN_CVAR(whodun_FileReadExternalArray, saveName, self), err)
		}
	}
}
void whodun_FileReadExternalArray_moveView_imp(void* self, whodun_MaxUInt toOff, whodun_UInt reqSize, struct whodun_ErrorLog* err){
	HANDLE baseHand = *WHODUN_CVAR(whodun_FileReadExternalArray, baseHandle, self);
	if(!baseHand || *WHODUN_CVAR(whodun_ExternalArray, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	struct whodun_ByteVector* baseView = WHODUN_CVAR(whodun_FileReadExternalArray, baseView, self);
	whodun_byteVectorResize(baseView, reqSize, err);
	if(WHODUN_WASERR(err)){ return; }
	if(reqSize){
		whodun_os_help_seekHandle(baseHand, toOff, WHODUN_CVAR(whodun_FileReadExternalArray, saveName, self), err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_os_help_readHandle(baseHand, baseView->view.ptr, reqSize, WHODUN_CVAR(whodun_FileReadExternalArray, saveName, self), err);
		if(WHODUN_WASERR(err)){ return; }
	}
	*WHODUN_CVAR(whodun_ExternalArray, curOff, self) = toOff;
	*WHODUN_CVAR(whodun_ExternalArray, view, self) = baseView->view;
}
void whodun_FileReadExternalArray_readBulk_imp(void* self, whodun_MaxUInt fromOff, whodun_UInt numRead, char* buffer, struct whodun_ErrorLog* err){
	HANDLE baseHand = *WHODUN_CVAR(whodun_FileReadExternalArray, baseHandle, self);
	if(!baseHand || *WHODUN_CVAR(whodun_ExternalArray, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	//trash the view as an idiot guard
	*WHODUN_CVAR(whodun_ExternalArray, view, self) = whodun_byteArrayPack(0, 0);
	//just read directly
	if(numRead){
		whodun_os_help_seekHandle(baseHand, fromOff, WHODUN_CVAR(whodun_FileReadExternalArray, saveName, self), err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_os_help_readHandle(baseHand, buffer, numRead, WHODUN_CVAR(whodun_FileReadExternalArray, saveName, self), err);
		if(WHODUN_WASERR(err)){ return; }
	}
}
void whodun_FileReadExternalArray_open_base(void* self, const wchar_t* path, struct whodun_ErrorLog* err){
	//idiot check
		void** baseHandP = WHODUN_CVAR(whodun_FileReadExternalArray, baseHandle, self);
		if(*baseHandP){
			WHODUN_ERR_MARK_PANIC(ASSERT, err)
			return;
		}
	//make a working copy of the name
		size_t pathL = 0;
		while(path[pathL]){ pathL++; }
		pathL++;
		wchar_t* pathCpyAl = (wchar_t*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, pathL*sizeof(wchar_t), err));
		if(WHODUN_WASERR(err)){ return; }
		memcpy(pathCpyAl, path, pathL*sizeof(wchar_t));
		struct whodun_ByteArray pathCpyAr = whodun_byteArrayPack(pathL*sizeof(wchar_t),(char*)pathCpyAl);
	whodun_byteVectorInit(WHODUN_CVAR(whodun_FileReadExternalArray, baseView, self), whodun_heap, err);
		if(WHODUN_WASERR(err)){ goto cleanUpA; }
	HANDLE happyHand = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
		if(happyHand == INVALID_HANDLE_VALUE){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(OPENFILE, pathCpyAr, err)
			goto cleanUpB;
		}
	DWORD sizeH;
	DWORD sizeL = GetFileSize(happyHand, &sizeH);
	if((sizeL == INVALID_FILE_SIZE) && (GetLastError() != NO_ERROR)){
		WHODUN_ERR_MARK_SIGNAL_FILENAME(READFILE, whodun_byteArrayPack(pathL*sizeof(wchar_t),(char*)path), err)
		goto cleanUpC;
	}
	*baseHandP = happyHand;
	*WHODUN_CVAR(whodun_FileReadExternalArray, saveName, self) = pathCpyAr;
	*WHODUN_CVAR(whodun_ExternalArray, baseSize, self) = (((whodun_MaxUInt)sizeH) << 32) + sizeL;
	return;
	
	cleanUpC:
		CloseHandle(happyHand);
	cleanUpB:
		whodun_byteVectorFin(WHODUN_CVAR(whodun_FileReadExternalArray, baseView, self));
	cleanUpA:
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, pathCpyAl);
}
void whodun_FileReadExternalArray_open_imp(void* self, struct whodun_Path* path, struct whodun_ErrorLog* err){
	whodun_FileReadExternalArray_open_base(self, path->ptr, err);
}
void whodun_FileReadExternalArray_openRaw_imp(void* self, struct whodun_ByteArray path, struct whodun_ErrorLog* err){
	wchar_t* convProv = 0;
	//convert to utf-16 and null terminate
		int reqConvSize = MultiByteToWideChar(CP_UTF8, 0, path.ptr, path.len, 0, 0);
		if(reqConvSize == 0){ goto err_path; }
		convProv = (wchar_t*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, (reqConvSize + 1)*sizeof(wchar_t), err));
		if(WHODUN_WASERR(err)){ goto err_cleanup; }
		int endConvSize = MultiByteToWideChar(CP_UTF8, 0, path.ptr, path.len, convProv, reqConvSize);
		if(endConvSize == 0){ goto err_path; }
		convProv[endConvSize] = 0;
	//do it
		whodun_FileReadExternalArray_open_base(self, convProv, err);
	//clean up
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, convProv);
	return;
	
	err_path:
		WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
	err_cleanup:
		if(convProv){ WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, convProv); }
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_FileReadExternalArray, whodun_ExternalArray)
	needInit->super.super.finalize = whodun_FileReadExternalArray_finalize_imp;
	needInit->super.super.initialize = whodun_FileReadExternalArray_initialize_imp;
	needInit->super.close = whodun_FileReadExternalArray_close_imp;
	needInit->super.moveView = whodun_FileReadExternalArray_moveView_imp;
	needInit->super.readBulk = whodun_FileReadExternalArray_readBulk_imp;
	needInit->open = whodun_FileReadExternalArray_open_imp;
	needInit->openRaw = whodun_FileReadExternalArray_openRaw_imp;
WHODUN_CVTABLE_FUN_END(whodun_FileReadExternalArray)

void whodun_FileEditExternalArray_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self) = 0;
	*WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self) = whodun_byteArrayPack(0, 0);
	*WHODUN_CVAR(whodun_FileEditExternalArray, dirty, self) = 0;
}

void whodun_FileEditExternalArray_finalize_imp(void* self){
	if(WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self)->len){
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self)->ptr);
		whodun_byteVectorFin(WHODUN_CVAR(whodun_FileEditExternalArray, baseView, self));
	}
}

//push any dirty data back out
void whodun_FileEditExternalArray_clean(void* self, struct whodun_ErrorLog* err){
	whodun_Bool* dirtyP = WHODUN_CVAR(whodun_FileEditExternalArray, dirty, self);
	if(*dirtyP == 0){ return; }
	
	HANDLE baseHand = *WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self);
	struct whodun_ByteArray* viewP = WHODUN_CVAR(whodun_ExternalArray, view, self);
	if(viewP->len){
		whodun_os_help_seekHandle(baseHand, *WHODUN_CVAR(whodun_ExternalArray, curOff, self), WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_os_help_writeHandle(baseHand, viewP->ptr, viewP->len, WHODUN_CVAR(whodun_FileOutputStream, saveName, self), err);
		if(WHODUN_WASERR(err)){ return; }
	}
	*dirtyP = 0;
}

void whodun_FileEditExternalArray_close_imp(void* self, struct whodun_ErrorLog* err){
	whodun_Bool* closeP = WHODUN_CVAR(whodun_ExternalArray, haveClose, self);
	if(*closeP){ return; }
	*closeP = 1;
	
	HANDLE baseHand = *WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self);
	if(baseHand){
		whodun_FileEditExternalArray_clean(self, err);
		if(CloseHandle(baseHand) == 0){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(CLOSEFILE, *WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err)
		}
	}
}
void whodun_FileEditExternalArray_moveView_imp(void* self, whodun_MaxUInt toOff, whodun_UInt reqSize, struct whodun_ErrorLog* err){
	HANDLE baseHand = *WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self);
	if(!baseHand || *WHODUN_CVAR(whodun_ExternalArray, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	whodun_FileEditExternalArray_clean(self, err);
		if(WHODUN_WASERR(err)){ return; }
	struct whodun_ByteVector* baseView = WHODUN_CVAR(whodun_FileEditExternalArray, baseView, self);
	whodun_byteVectorResize(baseView, reqSize, err);
	if(WHODUN_WASERR(err)){ return; }
	if(reqSize){
		whodun_os_help_seekHandle(baseHand, toOff, WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_os_help_readHandle(baseHand, baseView->view.ptr, reqSize, WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err);
		if(WHODUN_WASERR(err)){ return; }
	}
	*WHODUN_CVAR(whodun_ExternalArray, curOff, self) = toOff;
	*WHODUN_CVAR(whodun_ExternalArray, view, self) = baseView->view;
}
void whodun_FileEditExternalArray_markDirty_imp(void* self, struct whodun_ErrorLog* err){
	*WHODUN_CVAR(whodun_FileEditExternalArray, dirty, self) = 1;
}
void whodun_FileEditExternalArray_resize_imp(void* self, whodun_MaxUInt newSize, struct whodun_ErrorLog* err){
	//get the handle
		HANDLE baseHand = *WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self);
		if(!baseHand || *WHODUN_CVAR(whodun_ExternalArray, haveClose, self)){
			WHODUN_ERR_MARK_PANIC(ASSERT, err)
			return;
		}
	//trash the view as an idiot guard
		whodun_FileEditExternalArray_clean(self, err);
			if(WHODUN_WASERR(err)){ return; }
		*WHODUN_CVAR(whodun_ExternalArray, view, self) = whodun_byteArrayPack(0, 0);
	//figure out whether to grow or shrink
		whodun_MaxUInt* fileSizeP = WHODUN_CVAR(whodun_ExternalArray, baseSize, self);
		if(newSize > *fileSizeP){
			whodun_os_help_seekHandle(baseHand, *fileSizeP, WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err);
			if(WHODUN_WASERR(err)){ goto mark_error; }
			whodun_MaxUInt numNeed = newSize - *fileSizeP;
			#define DUMP_SIZE 1024
			char dumpBuff[DUMP_SIZE];
			memset(dumpBuff, 0, DUMP_SIZE);
			while(numNeed){
				whodun_UInt curNum = (numNeed > DUMP_SIZE) ? DUMP_SIZE : numNeed;
				whodun_os_help_writeHandle(baseHand, dumpBuff, curNum, WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err);
				if(WHODUN_WASERR(err)){ return; }
				numNeed -= curNum;
			}
			*fileSizeP = newSize;
			return;
		}
		else if(newSize < *fileSizeP){
			whodun_os_help_seekHandle(baseHand, newSize, WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err);
			if(WHODUN_WASERR(err)){ goto mark_error; }
			if(SetEndOfFile(baseHand) == 0){ goto mark_error; }
			*fileSizeP = newSize;
			return;
		}
	mark_error:
	WHODUN_ERR_MARK_SIGNAL_FILENAME(WRITEFILE, *WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err)
	return;
}
void whodun_FileEditExternalArray_readBulk_imp(void* self, whodun_MaxUInt fromOff, whodun_UInt numRead, char* buffer, struct whodun_ErrorLog* err){
	HANDLE baseHand = *WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self);
	if(!baseHand || *WHODUN_CVAR(whodun_ExternalArray, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	//trash the view as an idiot guard
	whodun_FileEditExternalArray_clean(self, err);
		if(WHODUN_WASERR(err)){ return; }
	*WHODUN_CVAR(whodun_ExternalArray, view, self) = whodun_byteArrayPack(0, 0);
	//just read directly
	if(numRead){
		whodun_os_help_seekHandle(baseHand, fromOff, WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_os_help_readHandle(baseHand, buffer, numRead, WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err);
		if(WHODUN_WASERR(err)){ return; }
	}
}
void whodun_FileEditExternalArray_writeBulk_imp(void* self, whodun_MaxUInt fromOff, whodun_UInt numWrite, const char* buffer, struct whodun_ErrorLog* err){
	HANDLE baseHand = *WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self);
	if(!baseHand || *WHODUN_CVAR(whodun_ExternalArray, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	//trash the view as an idiot guard
	whodun_FileEditExternalArray_clean(self, err);
		if(WHODUN_WASERR(err)){ return; }
	*WHODUN_CVAR(whodun_ExternalArray, view, self) = whodun_byteArrayPack(0, 0);
	//just read directly
	if(numWrite){
		whodun_os_help_seekHandle(baseHand, fromOff, WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_os_help_writeHandle(baseHand, buffer, numWrite, WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err);
		if(WHODUN_WASERR(err)){ return; }
	}
}
void whodun_FileEditExternalArray_open_base(void* self, const wchar_t* path, struct whodun_ErrorLog* err){
	//idiot check
		void** baseHandP = WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self);
		if(*baseHandP){
			WHODUN_ERR_MARK_PANIC(ASSERT, err)
			return;
		}
	//make a working copy of the name
		size_t pathL = 0;
		while(path[pathL]){ pathL++; }
		pathL++;
		wchar_t* pathCpyAl = (wchar_t*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, pathL*sizeof(wchar_t), err));
		if(WHODUN_WASERR(err)){ return; }
		memcpy(pathCpyAl, path, pathL*sizeof(wchar_t));
		struct whodun_ByteArray pathCpyAr = whodun_byteArrayPack(pathL*sizeof(wchar_t),(char*)pathCpyAl);
	whodun_byteVectorInit(WHODUN_CVAR(whodun_FileEditExternalArray, baseView, self), whodun_heap, err);
		if(WHODUN_WASERR(err)){ goto cleanUpA; }
	HANDLE happyHand = CreateFileW(path, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
		if(happyHand == INVALID_HANDLE_VALUE){
			happyHand = CreateFileW(path, GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
		}
		if(happyHand == INVALID_HANDLE_VALUE){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(OPENFILE, pathCpyAr, err)
			goto cleanUpB;
		}
	DWORD sizeH;
	DWORD sizeL = GetFileSize(happyHand, &sizeH);
	if((sizeL == INVALID_FILE_SIZE) && (GetLastError() != NO_ERROR)){
		WHODUN_ERR_MARK_SIGNAL_FILENAME(READFILE, whodun_byteArrayPack(pathL*sizeof(wchar_t),(char*)path), err)
		goto cleanUpC;
	}
	*baseHandP = happyHand;
	*WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self) = pathCpyAr;
	*WHODUN_CVAR(whodun_ExternalArray, baseSize, self) = (((whodun_MaxUInt)sizeH) << 32) + sizeL;
	return;
	
	cleanUpC:
		CloseHandle(happyHand);
	cleanUpB:
		whodun_byteVectorFin(WHODUN_CVAR(whodun_FileEditExternalArray, baseView, self));
	cleanUpA:
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, pathCpyAl);
}
void whodun_FileEditExternalArray_open_imp(void* self, struct whodun_Path* path, struct whodun_ErrorLog* err){
	whodun_FileEditExternalArray_open_base(self, path->ptr, err);
}
void whodun_FileEditExternalArray_openRaw_imp(void* self, struct whodun_ByteArray path, struct whodun_ErrorLog* err){
	wchar_t* convProv = 0;
	//convert to utf-16 and null terminate
		int reqConvSize = MultiByteToWideChar(CP_UTF8, 0, path.ptr, path.len, 0, 0);
		if(reqConvSize == 0){ goto err_path; }
		convProv = (wchar_t*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, (reqConvSize + 1)*sizeof(wchar_t), err));
		if(WHODUN_WASERR(err)){ goto err_cleanup; }
		int endConvSize = MultiByteToWideChar(CP_UTF8, 0, path.ptr, path.len, convProv, reqConvSize);
		if(endConvSize == 0){ goto err_path; }
		convProv[endConvSize] = 0;
	//do it
		whodun_FileEditExternalArray_open_base(self, convProv, err);
	//clean up
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, convProv);
	return;
	
	err_path:
		WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
	err_cleanup:
		if(convProv){ WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, convProv); }
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_FileEditExternalArray, whodun_ExternalArray)
	needInit->super.super.finalize = whodun_FileEditExternalArray_finalize_imp;
	needInit->super.super.initialize = whodun_FileEditExternalArray_initialize_imp;
	needInit->super.close = whodun_FileEditExternalArray_close_imp;
	needInit->super.moveView = whodun_FileEditExternalArray_moveView_imp;
	needInit->super.markDirty = whodun_FileEditExternalArray_markDirty_imp;
	needInit->super.resize = whodun_FileEditExternalArray_resize_imp;
	needInit->super.readBulk = whodun_FileEditExternalArray_readBulk_imp;
	needInit->super.writeBulk = whodun_FileEditExternalArray_writeBulk_imp;
	needInit->open = whodun_FileEditExternalArray_open_imp;
	needInit->openRaw = whodun_FileEditExternalArray_openRaw_imp;
WHODUN_CVTABLE_FUN_END(whodun_FileEditExternalArray)

/****************************************************************************/
/*Threading*/

whodun_UInt whodun_installedCPUs_imp(){
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;
}

/**Simple mutex.*/
struct whodun_Mutex {
	/**The actual lock.*/
	CRITICAL_SECTION actual;
};

struct whodun_Mutex* whodun_mutexAlloc_imp(struct whodun_ErrorLog* err){
	struct whodun_Mutex* toRet = (struct whodun_Mutex*)malloc(sizeof(struct whodun_Mutex));
	if(toRet){
		if(InitializeCriticalSectionAndSpinCount(&(toRet->actual), 3) == 0){
			free(toRet);
			toRet = 0;
		}
	}
	if(!toRet){
		if(err){ WHODUN_ERR_MARK_SIGNAL(CANT_MUTEX, err) }
	}
	return toRet;
}

whodun_Bool whodun_mutexTry_imp(struct whodun_Mutex* toL){
	return TryEnterCriticalSection(&(toL->actual)) != 0;
}

void whodun_mutexLock_imp(struct whodun_Mutex* toL){
	EnterCriticalSection(&(toL->actual));
}

void whodun_mutexUnlock_imp(struct whodun_Mutex* toU){
	LeaveCriticalSection(&(toU->actual));
}

void whodun_mutexFree_imp(struct whodun_Mutex* toK){
	DeleteCriticalSection(&(toK->actual));
	free(toK);
}

/**Simple condition.*/
struct whodun_Condition {
	/**The actual condition.*/
	CONDITION_VARIABLE actual;
};

struct whodun_Condition* whodun_condAlloc_imp(struct whodun_Mutex* forLock, struct whodun_ErrorLog* err){
	struct whodun_Condition* toRet = (struct whodun_Condition*)malloc(sizeof(struct whodun_Condition));
	if(toRet){
		InitializeConditionVariable(&(toRet->actual));
	}
	if(!toRet){
		WHODUN_ERR_MARK_SIGNAL(CANT_COND, err)
	}
	return toRet;
}
void whodun_condWait_imp(struct whodun_Mutex* forLock, struct whodun_Condition* onCond){
	SleepConditionVariableCS(&(onCond->actual), &(forLock->actual), INFINITE);
}

void whodun_condSignal_imp(struct whodun_Mutex* forLock, struct whodun_Condition* onCond){
	WakeConditionVariable(&(onCond->actual));
}

void whodun_condBroadcast_imp(struct whodun_Mutex* forLock, struct whodun_Condition* onCond){
	WakeAllConditionVariable(&(onCond->actual));
}

void whodun_condFree_imp(struct whodun_Mutex* forLock, struct whodun_Condition* toKill){
	free(toKill);
}

/**Simple thread.*/
struct whodun_Thread {
	/**The actual thread.*/
	HANDLE actual;
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
DWORD WINAPI whodun_threadMain_imp(LPVOID myPtrV){
	struct whodun_Thread* myPtr = (struct whodun_Thread*)myPtrV;
	myPtr->callFunc(myPtr->callPass);
	return 0;
}

struct whodun_Thread* whodun_threadStart_imp(void(*callFunc)(void*), void* callPass, struct whodun_ErrorLog* err){
	struct whodun_Thread* toRet = (struct whodun_Thread*)malloc(sizeof(struct whodun_Thread));
	if(toRet){
		toRet->callFunc = callFunc;
		toRet->callPass = callPass;
		toRet->actual = CreateThread(NULL, 0, whodun_threadMain_imp, toRet, 0, 0);
		if(toRet->actual == 0){
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
	WaitForSingleObject(toWait->actual, INFINITE);
	CloseHandle(toWait->actual);
	free(toWait);
}

const char* whodun_initializeOS(int argc, char** argv){
	whodun_GIL = whodun_mutexAlloc_imp(0);
	if(!whodun_GIL){ return "Problem allocating primary lock."; }
	
	WHODUN_CINIT(whodun_OSAllocator, &whodun_heap_imp);
	whodun_heap = (struct whodun_Allocator*)&whodun_heap_imp;
	
	whodun_oshelp_saveStdinHandle = GetStdHandle(STD_INPUT_HANDLE);
	whodun_oshelp_saveStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	whodun_oshelp_saveStderrHandle = GetStdHandle(STD_ERROR_HANDLE);
	
	WHODUN_CINIT(whodun_StdinInputStream, &whodun_stdin_imp);
	whodun_stdin = (struct whodun_InputStream*)&whodun_stdin_imp;
	WHODUN_CINIT(whodun_StdoutOutputStream, &whodun_stdout_imp);
	whodun_stdout = (struct whodun_OutputStream*)&whodun_stdout_imp;
	WHODUN_CINIT(whodun_StderrOutputStream, &whodun_stderr_imp);
	whodun_stderr = (struct whodun_OutputStream*)&whodun_stderr_imp;
	
	//need to get unicode arguments, and convert from utf-16
	int argcAct;
	wchar_t** argvAct = CommandLineToArgvW(GetCommandLineW(), &argcAct);
	if(!argvAct){ return "Could not get command line arguments."; }
	whodun_cliNumArgs = argcAct;
	whodun_cliArgs = (struct whodun_ByteArray*)malloc(argcAct * sizeof(struct whodun_ByteArray));
	if(!whodun_cliArgs){ return "Problem allocating argument storage."; }
	for(int i = 0; i<argc; i++){
		int reqConvSize = WideCharToMultiByte(CP_UTF8, 0, argvAct[i], -1, 0, 0, 0, 0);
		if(reqConvSize == 0){ return "Problem converting argument to utf-8"; }
		char* argvi = (char*)malloc(reqConvSize);
		if(!argvi){ return "Problem allocating argument conversion storage."; }
		int endConvSize = WideCharToMultiByte(CP_UTF8, 0, argvAct[i], -1, argvi, reqConvSize, 0, 0);
		if(endConvSize == 0){ return "Problem converting argument to utf-8"; }
		whodun_cliArgs[i] = whodun_byteArrayPack(endConvSize - 1, argvi);
	}
	HeapFree(GetProcessHeap(), 0, argvAct);
	
	return 0;
}

void whodun_finalizeOS(){
	//make a dummy error log
		struct whodun_NullErrorLog nerr;
		WHODUN_CINIT(whodun_NullErrorLog, &nerr);
		struct whodun_ErrorLog* err = (struct whodun_ErrorLog*)&nerr;
	
	//"close" the streams, ignore errors
		WHODUN_CFUN(whodun_Stream, close, whodun_stderr)(whodun_stderr, err);
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, err) = WHODUN_ERROR_SEVERITY_NORMAL;
		WHODUN_CFUN(whodun_Stream, close, whodun_stdout)(whodun_stdout, err);
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, err) = WHODUN_ERROR_SEVERITY_NORMAL;
		WHODUN_CFUN(whodun_Stream, close, whodun_stdin)(whodun_stdin, err);
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, err) = WHODUN_ERROR_SEVERITY_NORMAL;
	
	for(whodun_UInt i = 0; i<whodun_cliNumArgs; i++){
		free(whodun_cliArgs[i].ptr);
	}
	free(whodun_cliArgs);
	WHODUN_CFIN(whodun_stderr);
	WHODUN_CFIN(whodun_stdout);
	WHODUN_CFIN(whodun_stdin);
	WHODUN_CFIN(whodun_heap);
	whodun_mutexFree_imp(whodun_GIL);
}

void (*whodun_panic)(const char* reason, struct whodun_ErrorLog* err) = whodun_panic_imp;

whodun_UInt (*whodun_installedRAM)() = whodun_installedRAM_imp;
whodun_UInt (*whodun_availableRAM)() = whodun_availableRAM_imp;
struct whodun_Allocator* whodun_heap = 0;

struct whodun_InputStream* whodun_stdin = 0;
struct whodun_OutputStream* whodun_stdout = 0;
struct whodun_OutputStream* whodun_stderr = 0;

struct whodun_Path* (*whodun_pathRoot)(struct whodun_ErrorLog* err) = whodun_pathRoot_imp;
struct whodun_Path* (*whodun_pathNormalize)(struct whodun_ByteArray prov, struct whodun_ErrorLog* err) = whodun_pathNormalize_imp;
struct whodun_Path* (*whodun_pathGetParent)(struct whodun_Path* ofPath, struct whodun_ErrorLog* err) = whodun_pathGetParent_imp;
struct whodun_Path* (*whodun_pathGetChild)(struct whodun_Path* ofPath, struct whodun_ByteArray name, struct whodun_ErrorLog* err) = whodun_pathGetChild_imp;
whodun_Bool (*whodun_pathIsRoot)(struct whodun_Path* test) = whodun_pathIsRoot_imp;
whodun_Bool (*whodun_pathCanFile)(struct whodun_Path* test) = whodun_pathCanFile_imp;
whodun_Bool (*whodun_pathCanFolder)(struct whodun_Path* test) = whodun_pathCanFolder_imp;
void (*whodun_pathFree)(struct whodun_Path* toK) = whodun_pathFree_imp;
struct whodun_Path* (*whodun_pathGetCWD)(struct whodun_ErrorLog* err) = whodun_pathGetCWD_imp;
struct whodun_Path* (*whodun_pathGetTmp)(struct whodun_ErrorLog* err) = whodun_pathGetTmp_imp;
struct whodun_Path* (*whodun_pathGetHome)(struct whodun_ErrorLog* err) = whodun_pathGetHome_imp;
struct whodun_Path* (*whodun_pathGetDataRoam)(struct whodun_ErrorLog* err) = whodun_pathGetDataRoam_imp;
struct whodun_Path* (*whodun_pathGetDataLocal)(struct whodun_ErrorLog* err) = whodun_pathGetDataLocal_imp;
whodun_Bool (*whodun_pathIsFile)(struct whodun_Path* test, struct whodun_ErrorLog* err) = whodun_pathIsFile_imp;
void (*whodun_pathFileDelete)(struct whodun_Path* kill, struct whodun_ErrorLog* err) = whodun_pathFileDelete_imp;
whodun_MaxUInt (*whodun_pathFileSize)(struct whodun_Path* check, struct whodun_ErrorLog* err) = whodun_pathFileSize_imp;
whodun_Bool (*whodun_pathIsFold)(struct whodun_Path* test, struct whodun_ErrorLog* err) = whodun_pathIsFold_imp;
void (*whodun_pathFoldCreate)(struct whodun_Path* llik, struct whodun_ErrorLog* err) = whodun_pathFoldCreate_imp;
void (*whodun_pathFoldDelete)(struct whodun_Path* kill, struct whodun_ErrorLog* err) = whodun_pathFoldDelete_imp;
struct whodun_DirIter* (*whodun_pathFoldIterOpen)(struct whodun_Path* check, struct whodun_ErrorLog* err) = whodun_pathFoldIterOpen_imp;
whodun_Bool (*whodun_pathFoldIterNext)(struct whodun_DirIter* iter, struct whodun_ErrorLog* err) = whodun_pathFoldIterNext_imp;
struct whodun_ByteArray (*whodun_pathFoldIterName)(struct whodun_DirIter* iter) = whodun_pathFoldIterName_imp;
whodun_UInt (*whodun_pathFoldIterType)(struct whodun_DirIter* iter) = whodun_pathFoldIterType_imp;
void (*whodun_pathFoldIterClose)(struct whodun_DirIter* kill) = whodun_pathFoldIterClose_imp;

whodun_UInt (*whodun_installedCPUs)() = whodun_installedCPUs_imp;
struct whodun_Mutex* (*whodun_mutexAlloc)(struct whodun_ErrorLog* err) = whodun_mutexAlloc_imp;
whodun_Bool (*whodun_mutexTry)(struct whodun_Mutex* toL) = whodun_mutexTry_imp;
void (*whodun_mutexLock)(struct whodun_Mutex* toL) = whodun_mutexLock_imp;
void (*whodun_mutexUnlock)(struct whodun_Mutex* toU) = whodun_mutexUnlock_imp;
void (*whodun_mutexFree)(struct whodun_Mutex* toK) = whodun_mutexFree_imp;
struct whodun_Mutex* whodun_GIL;
struct whodun_Condition* (*whodun_condAlloc)(struct whodun_Mutex* forLock, struct whodun_ErrorLog* err) = whodun_condAlloc_imp;
void (*whodun_condWait)(struct whodun_Mutex* forLock, struct whodun_Condition* onCond) = whodun_condWait_imp;
void (*whodun_condSignal)(struct whodun_Mutex* forLock, struct whodun_Condition* onCond) = whodun_condSignal_imp;
void (*whodun_condBroadcast)(struct whodun_Mutex* forLock, struct whodun_Condition* onCond) = whodun_condBroadcast_imp;
void (*whodun_condFree)(struct whodun_Mutex* forLock, struct whodun_Condition* toKill) = whodun_condFree_imp;
struct whodun_Thread* (*whodun_threadStart)(void(*callFunc)(void*), void* callPass, struct whodun_ErrorLog* err) = whodun_threadStart_imp;
void (*whodun_threadJoin)(struct whodun_Thread* toWait) = whodun_threadJoin_imp;

whodun_UInt whodun_cliNumArgs = 0;
struct whodun_ByteArray* whodun_cliArgs = 0;

