#include "whodun/oshook.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

#include "whodun/cpu.h"
#include "whodun/ermac.h"
#include "whodun/contain.h"

/**The length of the current working directory.*/
size_t whodun_helpOS_savecwdL;
/**Cache the current working directory.*/
char* whodun_helpOS_savecwd;

/**The actual definition. On Unix, utf-8 paths.*/
struct whodun_Path{
	/**The number of bytes, excluding the null terminator.*/
	size_t len;
	/**The bytes. Part of this allocation.*/
	char* ptr;
	/**Whether this path has to be a folder.*/
	int mustFold;
};

struct whodun_Path* whodun_pathRoot_imp(struct whodun_ErrorLog* err){
	struct whodun_Path* toRet = (struct whodun_Path*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, sizeof(struct whodun_Path) + 2, err));
	if(WHODUN_WASERR(err)){ return 0; }
	toRet->len = 1;
	toRet->ptr = (char*)(toRet + 1);
	toRet->mustFold = 1;
	toRet->ptr[0] = '/';
	toRet->ptr[1] = 0;
	return toRet;
}

struct whodun_Path* whodun_pathNormalize_imp(struct whodun_ByteArray prov, struct whodun_ErrorLog* err){
	//provided path must have SOMETHING in it
		if(prov.len == 0){
			WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
			return 0;
		}
	//technically, two slashes at the start is a problem, but I'm choosing to ignore it
	//make space and prepare for copying
		size_t provL = prov.len;
		char* provP = prov.ptr;
		struct whodun_Path* toRet;
		char* retP;
		if(*provP == '/'){
			toRet = (struct whodun_Path*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, sizeof(struct whodun_Path) + provL + 1, err));
			if(WHODUN_WASERR(err)){ return 0; }
			toRet->ptr = (char*)(toRet + 1);
			retP = toRet->ptr;
		}
		else{
			if(!whodun_helpOS_savecwd){
				WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
				return 0;
			}
			toRet = (struct whodun_Path*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, sizeof(struct whodun_Path) + whodun_helpOS_savecwdL + 1 + provL + 1, err));
			if(WHODUN_WASERR(err)){ return 0; }
			toRet->ptr = (char*)(toRet + 1);
			memcpy(toRet->ptr, whodun_helpOS_savecwd, whodun_helpOS_savecwdL);
			retP = toRet->ptr + whodun_helpOS_savecwdL;
		}
	//note if it must be a folder
		if(provP[provL-1] == '/'){
			provL--;
			toRet->mustFold = 1;
		}
		else{
			toRet->mustFold = 0;
		}
	//add crap
		while(provL){
			//ignore any slashes
				if(*provP == '/'){ provP++; provL--; continue; }
			//figure out the current element to add
				char* nextSlash = (char*)memchr(provP, '/', provL);
				size_t elemL;
				char* elemP = provP;
				if(nextSlash){
					elemL = nextSlash - elemP;
					provL = provL - (elemL + 1);
					provP = nextSlash + 1;
				}
				else{
					elemL = provL;
					provP += provL;
					provL = 0;
				}
			//if just a dot, skip
				if((elemL == 1) && (elemP[0] == '.')){ continue; }
			//if dot dot, remove to either the previous slash or empty
				if((elemL == 2) && (elemP[0] == '.') && (elemP[1] == '.')){
					size_t maxRem = retP - toRet->ptr;
					while(maxRem){
						retP--;
						if(*retP == '/'){ break; }
						maxRem--;
					}
					continue;
				}
			//add a slash and the element
				*retP = '/';
				memcpy(retP + 1, elemP, elemL);
				retP = retP + 1 + elemL;
		}
	//note the final length
		toRet->len = retP - toRet->ptr;
		*retP = 0;
	//if length is 0, add a slash for root
		if(toRet->len == 0){
			toRet->len = 1;
			toRet->ptr[0] = '/';
			toRet->ptr[1] = 0;
		}
	return toRet;
}

struct whodun_Path* whodun_pathGetParent_imp(struct whodun_Path* ofPath, struct whodun_ErrorLog* err){
	size_t slen = ofPath->len;
	char* sptr = ofPath->ptr;
	//chew backwards to a slash
		slen--;
		while(sptr[slen] != '/'){ slen--; }
	//if only one character left, return root
		if(slen == 0){
			return whodun_pathRoot_imp(err);
		}
	//make a new thing
		struct whodun_Path* toRet = (struct whodun_Path*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, sizeof(struct whodun_Path) + slen + 1, err));
		if(WHODUN_WASERR(err)){ return 0; }
		toRet->len = slen;
		toRet->ptr = (char*)(toRet + 1);
		toRet->mustFold = 1;
		memcpy(toRet->ptr, sptr, slen);
		toRet->ptr[slen] = 0;
		return toRet;
}

struct whodun_Path* whodun_pathGetChild_imp(struct whodun_Path* ofPath, struct whodun_ByteArray name, struct whodun_ErrorLog* err){
	size_t slen = ofPath->len;
	char* sptr = ofPath->ptr;
	//back off one character if root
		if(slen == 1){ slen = 0; }
	//make it
		struct whodun_Path* toRet = (struct whodun_Path*)(WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, sizeof(struct whodun_Path) + slen + 1 + name.len + 1, err));
		if(WHODUN_WASERR(err)){ return 0; }
		toRet->len = slen + 1 + name.len;
		toRet->ptr = (char*)(toRet + 1);
		toRet->mustFold = 0;
		memcpy(toRet->ptr, sptr, slen);
		toRet->ptr[slen] = '/';
		memcpy(toRet->ptr + slen + 1, name.ptr, name.len);
		toRet->ptr[slen + 1 + name.len] = 0;
		return toRet;
}

whodun_Bool whodun_pathIsRoot_imp(struct whodun_Path* test){
	return test->len == 1;
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
	if(!whodun_helpOS_savecwd){
		WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
		return 0;
	}
	return whodun_pathNormalize_imp(whodun_byteArrayPack(whodun_helpOS_savecwdL, whodun_helpOS_savecwd), err);
}

struct whodun_Path* whodun_pathGetTmp_imp(struct whodun_ErrorLog* err){
	//might need to guard this with a mutex (getenv)
	char* hotPath = getenv("TMPDIR");
	if(hotPath){
		return whodun_pathNormalize_imp(whodun_byteArrayPack(strlen(hotPath), hotPath), err);
	}
	else{
		WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
		return 0;
	}
}

struct whodun_Path* whodun_pathGetHome_imp(struct whodun_ErrorLog* err){
	//might need to guard this with a mutex (getenv)
	char* hotPath = getenv("HOME");
	if(hotPath){
		return whodun_pathNormalize_imp(whodun_byteArrayPack(strlen(hotPath), hotPath), err);
	}
	else{
		WHODUN_ERR_MARK_SIGNAL(PATHPROB, err)
		return 0;
	}
}

struct whodun_Path* whodun_pathGetDataRoam_imp(struct whodun_ErrorLog* err){
	//no moral equivalent on unix
	return whodun_pathGetHome(err);
}

struct whodun_Path* whodun_pathGetDataLocal_imp(struct whodun_ErrorLog* err){
	//no moral equivalent on unix
	return whodun_pathGetHome(err);
}

whodun_Bool whodun_pathIsFile_imp(struct whodun_Path* test, struct whodun_ErrorLog* err){
	if(test->mustFold){ return 0; }
	struct stat dirFo;
	if((stat(test->ptr, &dirFo)==0) && (S_ISREG(dirFo.st_mode))){
		return 1;
	}
	return 0;
}

void whodun_pathFileDelete_imp(struct whodun_Path* kill, struct whodun_ErrorLog* err){
	if(kill->mustFold || unlink(kill->ptr)){
		struct whodun_ByteArray fileN = whodun_byteArrayPack(kill->len, kill->ptr);
		WHODUN_ERR_MARK_SIGNAL_FILENAME(WRITEFILE, fileN, err)
	}
}

whodun_MaxUInt whodun_pathFileSize_imp(struct whodun_Path* check, struct whodun_ErrorLog* err){
	struct stat fdatBuff;
	if(check->mustFold || stat(check->ptr, &fdatBuff)){
		struct whodun_ByteArray fileN = whodun_byteArrayPack(check->len, check->ptr);
		WHODUN_ERR_MARK_SIGNAL_FILENAME(READFILE, fileN, err)
		return 0;
	}
	return fdatBuff.st_size;
}

whodun_Bool whodun_pathIsFold_imp(struct whodun_Path* test, struct whodun_ErrorLog* err){
	struct stat dirFo;
	if((stat(test->ptr, &dirFo)==0) && (S_ISDIR(dirFo.st_mode))){
		return 1;
	}
	return 0;
}

void whodun_pathFoldCreate_imp(struct whodun_Path* llik, struct whodun_ErrorLog* err){
	if(mkdir(llik->ptr, 0777)){
		struct whodun_ByteArray fileN = whodun_byteArrayPack(llik->len, llik->ptr);
		WHODUN_ERR_MARK_SIGNAL_FILENAME(WRITEFOLD, fileN, err)
	}
}

void whodun_pathFoldDelete_imp(struct whodun_Path* kill, struct whodun_ErrorLog* err){
	if(rmdir(kill->ptr)){
		struct whodun_ByteArray fileN = whodun_byteArrayPack(kill->len, kill->ptr);
		WHODUN_ERR_MARK_SIGNAL_FILENAME(WRITEFOLD, fileN, err)
	}
}

/**An active directory iteration.*/
struct whodun_DirIter{
	/**The open directory.*/
	DIR* baseIt;
	/**The last read structure.*/
	struct dirent* curDFo;
	/**Get information on a file.*/
	struct stat dirSt;
	/**Build a temporary path.*/
	struct whodun_ByteVector tempPath;
};

struct whodun_DirIter* whodun_pathFoldIterOpen_imp(struct whodun_Path* check, struct whodun_ErrorLog* err){
	struct whodun_DirIter* toRet = (struct whodun_DirIter*)malloc(sizeof(struct whodun_DirIter));
	if(toRet){
		whodun_byteVectorInit(&(toRet->tempPath), whodun_heap, err);
			if(WHODUN_WASERR(err)){
				free(toRet);
				return 0;
			}
		whodun_byteVectorResize(&(toRet->tempPath), check->len + 16, err);
			if(WHODUN_WASERR(err)){
				whodun_byteVectorFin(&(toRet->tempPath));
				free(toRet);
				return 0;
			}
		char* savePath = toRet->tempPath.view.ptr;
		memcpy(savePath, check->ptr, check->len);
			if(check->ptr[check->len - 1] == '/'){
				savePath[check->len] = 0;
				toRet->tempPath.view.len = check->len;
			}
			else{
				savePath[check->len] = '/';
				savePath[check->len+1] = 0;
				toRet->tempPath.view.len = check->len + 1;
			}
		toRet->baseIt = opendir(check->ptr);
		if(toRet->baseIt == 0){
			whodun_byteVectorFin(&(toRet->tempPath));
			free(toRet);
			toRet = 0;
		}
	}
	if(!toRet){
		struct whodun_ByteArray fileN = whodun_byteArrayPack(check->len, check->ptr);
		WHODUN_ERR_MARK_SIGNAL_FILENAME(READFOLD, fileN, err)
	}
	return toRet;
}

whodun_Bool whodun_pathFoldIterNext_imp(struct whodun_DirIter* iter, struct whodun_ErrorLog* err){
	fix_it_again_tony:
	
	errno = 0;
	iter->curDFo = readdir(iter->baseIt);
	if(iter->curDFo){
		//skip . and ..
			if(strcmp(iter->curDFo->d_name,"..") == 0){ goto fix_it_again_tony; }
			if(strcmp(iter->curDFo->d_name,".") == 0){ goto fix_it_again_tony; }
		//build the full path
			whodun_UInt oldLen = iter->tempPath.view.len;
			whodun_byteVectorResize(&(iter->tempPath), oldLen + strlen(iter->curDFo->d_name) + 1, err);
			if(WHODUN_WASERR(err)){ return 0; }
			strcpy(iter->tempPath.view.ptr + oldLen, iter->curDFo->d_name);
		//load its information
			int statRet = stat(iter->tempPath.view.ptr, &(iter->dirSt));
			iter->tempPath.view.len = oldLen;
			if(statRet){
				struct whodun_ByteArray fileN = whodun_byteArrayPack(iter->tempPath.view.len, iter->tempPath.view.ptr);
				WHODUN_ERR_MARK_SIGNAL_FILENAME(READFOLD, fileN, err)
				return 0;
			}
		return 1;
	}
	//check for error
	if(errno){
		struct whodun_ByteArray fileN = whodun_byteArrayPack(iter->tempPath.view.len, iter->tempPath.view.ptr);
		WHODUN_ERR_MARK_SIGNAL_FILENAME(READFOLD, fileN, err)
	}
	return 0;
}

struct whodun_ByteArray whodun_pathFoldIterName_imp(struct whodun_DirIter* iter){
	return whodun_byteArrayPack(strlen(iter->curDFo->d_name), iter->curDFo->d_name);
}

whodun_UInt whodun_pathFoldIterType_imp(struct whodun_DirIter* iter){
	if(S_ISREG(iter->dirSt.st_mode)){ return WHODUN_DIRITER_TYPE_FILE; }
	if(S_ISDIR(iter->dirSt.st_mode)){ return WHODUN_DIRITER_TYPE_FOLD; }
	return WHODUN_DIRITER_TYPE_ODD;
}

void whodun_pathFoldIterClose_imp(struct whodun_DirIter* kill){
	closedir(kill->baseIt);
	whodun_byteVectorFin(&(kill->tempPath));
	free(kill);
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
	FILE* baseHand = (FILE*)(*WHODUN_CVAR(whodun_FileInputStream, baseHandle, self));
	if(baseHand){
		int probClose = fclose(baseHand);
		if(probClose){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(CLOSEFILE, *WHODUN_CVAR(whodun_FileInputStream, saveName, self), err)
		}
	}
}

whodun_UInt whodun_FileInputStream_read_imp(void* self, char* buff, whodun_UInt max, struct whodun_ErrorLog* err){
	FILE* baseHand = (FILE*)(*WHODUN_CVAR(whodun_FileInputStream, baseHandle, self));
	if(!baseHand || *WHODUN_CVAR(whodun_Stream, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return 0;
	}
	whodun_UInt numR = fread(buff, 1, max, baseHand);
	*WHODUN_CVAR(whodun_Stream, totalBytes, self) += numR;
	if(numR == max){ return numR; }
	if(feof(baseHand)){ return numR; }
	if(ferror(baseHand)){
		WHODUN_ERR_MARK_SIGNAL_FILENAME(READFILE, *WHODUN_CVAR(whodun_FileInputStream, saveName, self), err)
	}
	return numR;
}

/**Helper method for opening.*/
void whodun_FileInputStream_open_base(void* self, const char* path, struct whodun_ErrorLog* err){
	void** baseHandP = WHODUN_CVAR(whodun_FileInputStream, baseHandle, self);
	if(*baseHandP){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	size_t pathL = strlen(path);
	char* pathCpyAl = (char*)malloc(pathL + 1);
		if(!pathCpyAl){
			WHODUN_ERR_MARK_SIGNAL(NOMEMORY, err)
			return;
		}
		strcpy(pathCpyAl, path);
	FILE* happyHand;
		happyHand = fopen(path, "rb");
		if(happyHand == 0){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(OPENFILE, whodun_byteArrayPack(pathL,path), err)
			free(pathCpyAl);
			return;
		}
	*baseHandP = happyHand;
	*WHODUN_CVAR(whodun_FileInputStream, saveName, self) = whodun_byteArrayPack(pathL, pathCpyAl);
}
void whodun_FileInputStream_open_imp(void* self, struct whodun_Path* path, struct whodun_ErrorLog* err){
	whodun_FileInputStream_open_base(self, path->ptr, err);
}
void whodun_FileInputStream_openRaw_imp(void* self, struct whodun_ByteArray path, struct whodun_ErrorLog* err){
	char* tmpAl = (char*)malloc(path.len + 1);
	if(tmpAl == 0){
		WHODUN_ERR_MARK_SIGNAL(NOMEMORY, err)
		return;
	}
	memcpy(tmpAl, path.ptr, path.len);
	tmpAl[path.len] = 0;
	whodun_FileInputStream_open_base(self, tmpAl, err);
	free(tmpAl);
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
	FILE* baseHand = (FILE*)(*WHODUN_CVAR(whodun_FileOutputStream, baseHandle, self));
	if(baseHand){
		int probClose = fclose(baseHand);
		if(probClose){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(CLOSEFILE, *WHODUN_CVAR(whodun_FileOutputStream, saveName, self), err)
		}
	}
}

void whodun_FileOutputStream_write_imp(void* self, const char* buff, whodun_UInt num, struct whodun_ErrorLog* err){
	FILE* baseHand = (FILE*)(*WHODUN_CVAR(whodun_FileOutputStream, baseHandle, self));
	if(!baseHand || *WHODUN_CVAR(whodun_Stream, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	size_t actN = fwrite(buff, 1, num, baseHand);
	*WHODUN_CVAR(whodun_Stream, totalBytes, self) += actN;
	if(actN != num){
		WHODUN_ERR_MARK_SIGNAL_FILENAME(WRITEFILE, *WHODUN_CVAR(whodun_FileOutputStream, saveName, self), err)
	}
}

/**Helper method for opening.*/
void whodun_FileOutputStream_open_base(void* self, int append, const char* path, struct whodun_ErrorLog* err){
	void** baseHandP = WHODUN_CVAR(whodun_FileOutputStream, baseHandle, self);
	if(*baseHandP){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	size_t pathL = strlen(path);
	char* pathCpyAl = (char*)malloc(pathL + 1);
		if(!pathCpyAl){
			WHODUN_ERR_MARK_SIGNAL(NOMEMORY, err)
			return;
		}
		strcpy(pathCpyAl, path);
	FILE* happyHand;
		if(append){
			happyHand = fopen(path, "ab");
		}
		else{
			happyHand = fopen(path, "wb");
		}
		if(happyHand == 0){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(OPENFILE, whodun_byteArrayPack(pathL,path), err)
			free(pathCpyAl);
			return;
		}
	*baseHandP = happyHand;
	*WHODUN_CVAR(whodun_FileOutputStream, saveName, self) = whodun_byteArrayPack(pathL, pathCpyAl);
}
void whodun_FileOutputStream_open_imp(void* self, struct whodun_Path* path, struct whodun_ErrorLog* err){
	whodun_FileOutputStream_open_base(self, 0, path->ptr, err);
}
void whodun_FileOutputStream_openRaw_imp(void* self, struct whodun_ByteArray path, struct whodun_ErrorLog* err){
	char* tmpAl = (char*)malloc(path.len + 1);
	if(tmpAl == 0){
		WHODUN_ERR_MARK_SIGNAL(NOMEMORY, err)
		return;
	}
	memcpy(tmpAl, path.ptr, path.len);
	tmpAl[path.len] = 0;
	whodun_FileOutputStream_open_base(self, 0, tmpAl, err);
	free(tmpAl);
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
		free(WHODUN_CVAR(whodun_FileReadExternalArray, saveName, self)->ptr);
		whodun_byteVectorFin(WHODUN_CVAR(whodun_FileReadExternalArray, baseView, self));
	}
}

void whodun_FileReadExternalArray_close_imp(void* self, struct whodun_ErrorLog* err){
	whodun_Bool* closeP = WHODUN_CVAR(whodun_ExternalArray, haveClose, self);
	if(*closeP){ return; }
	*closeP = 1;
	FILE* baseHand = (FILE*)(*WHODUN_CVAR(whodun_FileReadExternalArray, baseHandle, self));
	if(baseHand){
		int probClose = fclose(baseHand);
		if(probClose){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(CLOSEFILE, *WHODUN_CVAR(whodun_FileReadExternalArray, saveName, self), err)
		}
	}
}
void whodun_FileReadExternalArray_moveView_imp(void* self, whodun_MaxUInt toOff, whodun_UInt reqSize, struct whodun_ErrorLog* err){
	FILE* baseHand = (FILE*)(*WHODUN_CVAR(whodun_FileReadExternalArray, baseHandle, self));
	if(!baseHand || *WHODUN_CVAR(whodun_ExternalArray, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	struct whodun_ByteVector* baseView = WHODUN_CVAR(whodun_FileReadExternalArray, baseView, self);
	whodun_byteVectorResize(baseView, reqSize, err);
	if(WHODUN_WASERR(err)){ return; }
	if(reqSize){
		//limited to 2GB on systems with 32-bit long
		//sucks to be you
		int moveSuc = fseek(baseHand, toOff, SEEK_SET);
		if(moveSuc){ goto mark_error; }
		whodun_UInt numR = fread(baseView->view.ptr, 1, reqSize, baseHand);
		if(numR != reqSize){ goto mark_error; }
		goto update_view;
		
		mark_error:
		WHODUN_ERR_MARK_SIGNAL_FILENAME(READFILE, *WHODUN_CVAR(whodun_FileReadExternalArray, saveName, self), err)
		return;
	}
	update_view:
	*WHODUN_CVAR(whodun_ExternalArray, curOff, self) = toOff;
	*WHODUN_CVAR(whodun_ExternalArray, view, self) = baseView->view;
}
void whodun_FileReadExternalArray_readBulk_imp(void* self, whodun_MaxUInt fromOff, whodun_UInt numRead, char* buffer, struct whodun_ErrorLog* err){
	FILE* baseHand = (FILE*)(*WHODUN_CVAR(whodun_FileReadExternalArray, baseHandle, self));
	if(!baseHand || *WHODUN_CVAR(whodun_ExternalArray, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	//trash the view as an idiot guard
	*WHODUN_CVAR(whodun_ExternalArray, view, self) = whodun_byteArrayPack(0, 0);
	//just read directly
	if(numRead){
		int moveSuc = fseek(baseHand, fromOff, SEEK_SET);
		if(moveSuc){ goto mark_error; }
		whodun_UInt numR = fread(buffer, 1, numRead, baseHand);
		if(numR != numRead){ goto mark_error; }
		return;
		
		mark_error:
		WHODUN_ERR_MARK_SIGNAL_FILENAME(READFILE, *WHODUN_CVAR(whodun_FileReadExternalArray, saveName, self), err)
		return;
	}
}
void whodun_FileReadExternalArray_open_base(void* self, const char* path, struct whodun_ErrorLog* err){
	void** baseHandP = WHODUN_CVAR(whodun_FileReadExternalArray, baseHandle, self);
	if(*baseHandP){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	size_t pathL = strlen(path);
	char* pathCpyAl = (char*)malloc(pathL + 1);
		if(!pathCpyAl){
			WHODUN_ERR_MARK_SIGNAL(NOMEMORY, err)
			return;
		}
		strcpy(pathCpyAl, path);
	whodun_byteVectorInit(WHODUN_CVAR(whodun_FileReadExternalArray, baseView, self), whodun_heap, err);
		if(WHODUN_WASERR(err)){ goto cleanUpA; }
	FILE* happyHand;
		happyHand = fopen(path, "rb");
		if(happyHand == 0){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(OPENFILE, whodun_byteArrayPack(pathL,path), err)
			goto cleanUpB;
		}
	struct stat fdatBuff;
		if(fstat(fileno(happyHand), &fdatBuff)){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(READFILE, whodun_byteArrayPack(pathL,path), err)
			goto cleanUpC;
		}
	*baseHandP = happyHand;
	*WHODUN_CVAR(whodun_FileReadExternalArray, saveName, self) = whodun_byteArrayPack(pathL, pathCpyAl);
	*WHODUN_CVAR(whodun_ExternalArray, baseSize, self) = fdatBuff.st_size;
	return;
	
	cleanUpC:
		fclose(happyHand);
	cleanUpB:
		whodun_byteVectorFin(WHODUN_CVAR(whodun_FileReadExternalArray, baseView, self));
	cleanUpA:
		free(pathCpyAl);
}
void whodun_FileReadExternalArray_open_imp(void* self, struct whodun_Path* path, struct whodun_ErrorLog* err){
	whodun_FileReadExternalArray_open_base(self, path->ptr, err);
}
void whodun_FileReadExternalArray_openRaw_imp(void* self, struct whodun_ByteArray path, struct whodun_ErrorLog* err){
	char* tmpAl = (char*)malloc(path.len + 1);
	if(tmpAl == 0){
		WHODUN_ERR_MARK_SIGNAL(NOMEMORY, err)
		return;
	}
	memcpy(tmpAl, path.ptr, path.len);
	tmpAl[path.len] = 0;
	whodun_FileReadExternalArray_open_base(self, tmpAl, err);
	free(tmpAl);
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
		free(WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self)->ptr);
		whodun_byteVectorFin(WHODUN_CVAR(whodun_FileEditExternalArray, baseView, self));
	}
}

//push any dirty data back out
void whodun_FileEditExternalArray_clean(void* self, struct whodun_ErrorLog* err){
	whodun_Bool* dirtyP = WHODUN_CVAR(whodun_FileEditExternalArray, dirty, self);
	if(*dirtyP == 0){ return; }
	
	FILE* baseHand = (FILE*)(*WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self));
	struct whodun_ByteArray* viewP = WHODUN_CVAR(whodun_ExternalArray, view, self);
	if(viewP->len){
		int moveSuc = fseek(baseHand, *WHODUN_CVAR(whodun_ExternalArray, curOff, self), SEEK_SET);
		if(moveSuc){ goto mark_error; }
		size_t actN = fwrite(viewP->ptr, 1, viewP->len, baseHand);
		if(actN != viewP->len){ goto mark_error; }
		goto update_dirty;
		
		mark_error:
		WHODUN_ERR_MARK_SIGNAL_FILENAME(READFILE, *WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err)
		return;
	}
	update_dirty:
	*dirtyP = 0;
}

void whodun_FileEditExternalArray_close_imp(void* self, struct whodun_ErrorLog* err){
	whodun_Bool* closeP = WHODUN_CVAR(whodun_ExternalArray, haveClose, self);
	if(*closeP){ return; }
	*closeP = 1;
	
	FILE* baseHand = (FILE*)(*WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self));
	if(baseHand){
		whodun_FileEditExternalArray_clean(self, err);
		int probClose = fclose(baseHand);
		if(probClose){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(CLOSEFILE, *WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err)
		}
	}
}
void whodun_FileEditExternalArray_moveView_imp(void* self, whodun_MaxUInt toOff, whodun_UInt reqSize, struct whodun_ErrorLog* err){
	FILE* baseHand = (FILE*)(*WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self));
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
		int moveSuc = fseek(baseHand, toOff, SEEK_SET);
		if(moveSuc){ goto mark_error; }
		whodun_UInt numR = fread(baseView->view.ptr, 1, reqSize, baseHand);
		if(numR != reqSize){ goto mark_error; }
		goto update_view;
		
		mark_error:
		WHODUN_ERR_MARK_SIGNAL_FILENAME(READFILE, *WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err)
		return;
	}
	update_view:
	*WHODUN_CVAR(whodun_ExternalArray, curOff, self) = toOff;
	*WHODUN_CVAR(whodun_ExternalArray, view, self) = baseView->view;
}
void whodun_FileEditExternalArray_markDirty_imp(void* self, struct whodun_ErrorLog* err){
	*WHODUN_CVAR(whodun_FileEditExternalArray, dirty, self) = 1;
}
void whodun_FileEditExternalArray_resize_imp(void* self, whodun_MaxUInt newSize, struct whodun_ErrorLog* err){
	//get the handle
		FILE* baseHand = (FILE*)(*WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self));
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
			int moveSuc = fseek(baseHand, *fileSizeP, SEEK_SET);
			if(moveSuc){ goto mark_error; }
			whodun_MaxUInt numNeed = newSize - *fileSizeP;
			#define DUMP_SIZE 1024
			char dumpBuff[DUMP_SIZE];
			memset(dumpBuff, 0, DUMP_SIZE);
			while(numNeed > DUMP_SIZE){
				size_t actN = fwrite(dumpBuff, 1, DUMP_SIZE, baseHand);
				if(actN != DUMP_SIZE){ goto mark_error; }
				numNeed -= DUMP_SIZE;
			}
			size_t actN = fwrite(dumpBuff, 1, numNeed, baseHand);
			if(actN != DUMP_SIZE){ goto mark_error; }
			*fileSizeP = newSize;
			return;
		}
		else if(newSize < *fileSizeP){
			//...check this
			if(fflush(baseHand)){ goto mark_error; }
			if(ftruncate(fileno(baseHand), newSize)){ goto mark_error; }
			*fileSizeP = newSize;
			return;
		}
	mark_error:
	WHODUN_ERR_MARK_SIGNAL_FILENAME(WRITEFILE, *WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err)
	return;
}
void whodun_FileEditExternalArray_readBulk_imp(void* self, whodun_MaxUInt fromOff, whodun_UInt numRead, char* buffer, struct whodun_ErrorLog* err){
	//get the handle
		FILE* baseHand = (FILE*)(*WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self));
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
			int moveSuc = fseek(baseHand, fromOff, SEEK_SET);
			if(moveSuc){ goto mark_error; }
			whodun_UInt numR = fread(buffer, 1, numRead, baseHand);
			if(numR != numRead){ goto mark_error; }
			return;
			
			mark_error:
			WHODUN_ERR_MARK_SIGNAL_FILENAME(READFILE, *WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err)
			return;
		}
}
void whodun_FileEditExternalArray_writeBulk_imp(void* self, whodun_MaxUInt fromOff, whodun_UInt numWrite, const char* buffer, struct whodun_ErrorLog* err){
	//get the handle
		FILE* baseHand = (FILE*)(*WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self));
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
			int moveSuc = fseek(baseHand, fromOff, SEEK_SET);
			if(moveSuc){ goto mark_error; }
			size_t actN = fwrite(buffer, 1, numWrite, baseHand);
			if(actN != numWrite){ goto mark_error; }
			return;
			
			mark_error:
			WHODUN_ERR_MARK_SIGNAL_FILENAME(READFILE, *WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self), err)
			return;
		}
}
void whodun_FileEditExternalArray_open_base(void* self, const char* path, struct whodun_ErrorLog* err){
	void** baseHandP = WHODUN_CVAR(whodun_FileEditExternalArray, baseHandle, self);
	if(*baseHandP){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	size_t pathL = strlen(path);
	char* pathCpyAl = (char*)malloc(pathL + 1);
		if(!pathCpyAl){
			WHODUN_ERR_MARK_SIGNAL(NOMEMORY, err)
			return;
		}
		strcpy(pathCpyAl, path);
	whodun_byteVectorInit(WHODUN_CVAR(whodun_FileEditExternalArray, baseView, self), whodun_heap, err);
		if(WHODUN_WASERR(err)){ goto cleanUpA; }
	FILE* happyHand;
		happyHand = fopen(path, "r+b");
		if(happyHand == 0){
			happyHand = fopen(path, "w+b");
		}
		if(happyHand == 0){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(OPENFILE, whodun_byteArrayPack(pathL,path), err)
			goto cleanUpB;
		}
	struct stat fdatBuff;
		if(fstat(fileno(happyHand), &fdatBuff)){
			WHODUN_ERR_MARK_SIGNAL_FILENAME(READFILE, whodun_byteArrayPack(pathL,path), err)
			goto cleanUpC;
		}
	*baseHandP = happyHand;
	*WHODUN_CVAR(whodun_FileEditExternalArray, saveName, self) = whodun_byteArrayPack(pathL, pathCpyAl);
	*WHODUN_CVAR(whodun_ExternalArray, baseSize, self) = fdatBuff.st_size;
	return;
	
	cleanUpC:
		fclose(happyHand);
	cleanUpB:
		whodun_byteVectorFin(WHODUN_CVAR(whodun_FileEditExternalArray, baseView, self));
	cleanUpA:
		free(pathCpyAl);
}
void whodun_FileEditExternalArray_open_imp(void* self, struct whodun_Path* path, struct whodun_ErrorLog* err){
	whodun_FileEditExternalArray_open_base(self, path->ptr, err);
}
void whodun_FileEditExternalArray_openRaw_imp(void* self, struct whodun_ByteArray path, struct whodun_ErrorLog* err){
	char* tmpAl = (char*)malloc(path.len + 1);
	if(tmpAl == 0){
		WHODUN_ERR_MARK_SIGNAL(NOMEMORY, err)
		return;
	}
	memcpy(tmpAl, path.ptr, path.len);
	tmpAl[path.len] = 0;
	whodun_FileEditExternalArray_open_base(self, tmpAl, err);
	free(tmpAl);
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




