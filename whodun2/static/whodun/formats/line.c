#include "whodun/formats/line.h"

#include <string.h>

void whodun_lineFileReaderInit_imp(struct whodun_LineFileReader* toInit, struct whodun_InputStream* source, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err){
	toInit->source = source;
	whodun_byteVectorInit(&(toInit->text), useAl, err);
		if(WHODUN_WASERR(err)){ goto errorA; }
	toInit->text0 = 0;
	toInit->textN = 0;
	whodun_circleVectorInit(&(toInit->lines), sizeof(struct whodun_ByteArray), useAl, err);
		if(WHODUN_WASERR(err)){ goto errorB; }
	toInit->line0 = 0;
	toInit->usePool = usePool;
	if(!usePool){ return; }
	
	//TODO multithreading
	toInit->usePool = 0;
	toInit->extendo = 0;
	return;
	
	//errorC:
	//	whodun_circleVectorFin(&(toInit->lines));
	errorB:
		whodun_byteVectorFin(&(toInit->text));
	errorA:
		return;
}

void whodun_lineFileReader_help_fixLines(struct whodun_LineFileReader* toEdit, char* oldBase, char* newBase, struct whodun_ErrorLog* err){
	whodun_UInt numFix = toEdit->lines.len;
	whodun_UInt curFix = 0;
	while(numFix){
		struct whodun_Array curChunk = whodun_circleVectorForwardSpan(&(toEdit->lines), curFix);
		struct whodun_ByteArray* curLine = curChunk.ptr;
		for(whodun_UInt i = 0; i<curChunk.len; i++){
			curLine[i].ptr = (curLine[i].ptr - oldBase) + newBase;
		}
		curFix += curChunk.len;
		numFix -= curChunk.len;
	}
}

whodun_Bool whodun_lineFileReaderReadMore_imp(struct whodun_LineFileReader* toEdit, struct whodun_ErrorLog* err){
	//if text0 is greater than half the allocation, compact
		if(toEdit->text0 > (toEdit->text.alloc / 2)){
			memmove(toEdit->text.view.ptr, toEdit->text.view.ptr + toEdit->text0, toEdit->text.view.len - toEdit->text0);
			whodun_lineFileReader_help_fixLines(toEdit, toEdit->text.view.ptr + toEdit->text0, toEdit->text.view.ptr, err);
			if(WHODUN_WASERR(err)){ return 0; }
			toEdit->text.view.len -= toEdit->text0;
			toEdit->textN -= toEdit->text0;
			toEdit->text0 = 0;
		}
	//if size is at allocation, change capacity
		if(toEdit->text.view.len == toEdit->text.alloc){
			whodun_UInt origLen = toEdit->text.view.len;
			char* oldBase = toEdit->text.view.ptr;
			whodun_byteVectorResize(&(toEdit->text), 2*origLen, err);
			if(WHODUN_WASERR(err)){ return 0; }
			toEdit->text.view.len = origLen;
			char* newBase = toEdit->text.view.ptr;
			whodun_lineFileReader_help_fixLines(toEdit, oldBase, newBase, err);
			if(WHODUN_WASERR(err)){ return 0; }
		}
	//read bytes to allocation
		whodun_UInt maxRead = toEdit->text.alloc - toEdit->text.view.len;
		whodun_UInt numRead = WHODUN_CFUN(whodun_InputStream, read, toEdit->source)(toEdit->source, toEdit->text.view.ptr + toEdit->text.view.len, maxRead, err);
		if(WHODUN_WASERR(err)){ return 0; }
		toEdit->text.view.len += numRead;
	//add any new lines to the thing
		whodun_UInt numBytes = toEdit->text.view.len;
		char* allBytes = toEdit->text.view.ptr;
		whodun_UInt textN = toEdit->textN;
		const char* foundL = memchr(allBytes + textN, '\n', numBytes - textN);
		while(foundL){
			struct whodun_ByteArray* newLine = whodun_circleVectorPushBack(&(toEdit->lines), 1, err);
			if(WHODUN_WASERR(err)){ return 0; }
			newLine->ptr = allBytes + textN;
			newLine->len = (foundL + 1) - newLine->ptr;
			textN += newLine->len;
			foundL = memchr(allBytes + textN, '\n', numBytes - textN);
		}
	//last line might not be terminated by a newline
		if((textN != numBytes) && (numRead != maxRead)){
			foundL = allBytes + numBytes;
			struct whodun_ByteArray* newLine = whodun_circleVectorPushBack(&(toEdit->lines), 1, err);
			if(WHODUN_WASERR(err)){ return 0; }
			newLine->ptr = allBytes + textN;
			newLine->len = foundL - newLine->ptr;
			textN += (newLine->len + 1);
		}
	return numRead == maxRead;
}

void whodun_lineFileReaderDropSome_imp(struct whodun_LineFileReader* toEdit, whodun_UInt numDrop, struct whodun_ErrorLog* err){
	whodun_UInt numLeft = numDrop;
	while(numLeft){
		whodun_UInt curNum = whodun_circleVectorPopFrontSpan(&(toEdit->lines));
		if(curNum > numLeft){ curNum = numLeft; }
		struct whodun_ByteArray* popLines = whodun_circleVectorPopFront(&(toEdit->lines), curNum);
		for(whodun_UInt i = 0; i<curNum; i++){
			toEdit->text0 += popLines[i].len;
		}
		numLeft -= curNum;
	}
	toEdit->line0 += numDrop;
}

void whodun_lineFileReaderFin_imp(struct whodun_LineFileReader* toKill){
	whodun_circleVectorFin(&(toKill->lines));
	whodun_byteVectorFin(&(toKill->text));
}

void (*whodun_lineFileReaderInit)(struct whodun_LineFileReader* toInit, struct whodun_InputStream* source, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err) = whodun_lineFileReaderInit_imp;
whodun_Bool (*whodun_lineFileReaderReadMore)(struct whodun_LineFileReader* toEdit, struct whodun_ErrorLog* err) = whodun_lineFileReaderReadMore_imp;
void (*whodun_lineFileReaderDropSome)(struct whodun_LineFileReader* toEdit, whodun_UInt numDrop, struct whodun_ErrorLog* err) = whodun_lineFileReaderDropSome_imp;
void (*whodun_lineFileReaderFin)(struct whodun_LineFileReader* toKill) = whodun_lineFileReaderFin_imp;

