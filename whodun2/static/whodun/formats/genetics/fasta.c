#include "whodun/formats/genetics/fasta.h"

#include "whodun/ermac.h"
#include "whodun/string.h"

void whodun_fastaFileReaderInit_imp(struct whodun_FastaFileReader* toInit, struct whodun_InputStream* source, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err){
	whodun_lineFileReaderInit(&(toInit->source), source, useAl, usePool, err);
	if(WHODUN_WASERR(err)){ goto errorA; }
	toInit->lineN = 0;
	toInit->startLine = 1;
	toInit->sourceMore = 1;
	whodun_circleVectorInit(&(toInit->entries), sizeof(struct whodun_FastaEntry), useAl, err);
		if(WHODUN_WASERR(err)){ goto errorB; }
	toInit->usePool = usePool;
	if(!usePool){ return; }
	
	//TODO multithreading
	toInit->usePool = 0;
	toInit->extendo = 0;
	return;
	
	errorB:
		whodun_lineFileReaderFin(&(toInit->source));
	errorA:
		return;
}

#define FASTA_NWS 4
#define FASTA_WS " \r\t\n"

//square up past any leading junk
void whodun_fastaFileReader_readPastHead(struct whodun_FastaFileReader* toEdit, struct whodun_ErrorLog* err){
	while(toEdit->startLine){
		//if out of lines, read more
			if(toEdit->source.lines.len == 0){
				if(!(toEdit->sourceMore)){
					toEdit->startLine = 0;
					break;
				}
				toEdit->sourceMore = whodun_lineFileReaderReadMore(&(toEdit->source), err);
				if(WHODUN_WASERR(err)){ return; }
			}
		//skip any lines that are pure whitespace or that begin with a semicolon
			whodun_UInt numDrop = 0;
			while(numDrop < toEdit->source.lines.len){
				struct whodun_ByteArray* curLine = whodun_circleVectorGet(&(toEdit->source.lines), numDrop);
				if(curLine->len && (curLine->ptr[0] == '>')){
					toEdit->startLine = 0;
					break;
				}
				if((curLine->len != 0) && (curLine->ptr[0] != ';')){
					//must be all whitespace, check
					if(whodun_memspn(curLine->ptr, curLine->len, FASTA_WS, FASTA_NWS) != curLine->len){
						WHODUN_ERR_MARK_SIGNAL(FORMAT_FASTA_MALFORM, err)
						return;
					}
				}
				numDrop++;
			}
			whodun_lineFileReaderDropSome(&(toEdit->source), numDrop, err);
			if(WHODUN_WASERR(err)){ return; }
	}
}
whodun_Bool whodun_fastaFileReaderReadMore_imp(struct whodun_FastaFileReader* toEdit, struct whodun_ErrorLog* err){
	if(toEdit->sourceMore == 0){ return 0; }
	//load more data
		if(toEdit->startLine){
			whodun_fastaFileReader_readPastHead(toEdit, err);
			if(WHODUN_WASERR(err)){ return 0; }
		}
		else{
			toEdit->sourceMore = whodun_lineFileReaderReadMore(&(toEdit->source), err);
			if(WHODUN_WASERR(err)){ return 0; }
		}
	//chop up the lines
		//by construction, line0 begins with a > (if it exists)
		whodun_UInt line0 = toEdit->lineN;
		if(line0 >= toEdit->source.lines.len){ return toEdit->sourceMore; }
		whodun_UInt lineN = line0 + 1;
		whodun_UInt numBase = 0;
		while(lineN < toEdit->source.lines.len){
			struct whodun_ByteArray* curLine = whodun_circleVectorGet(&(toEdit->source.lines), lineN);
			if(curLine->len && (curLine->ptr[0] == '>')){
				//new entry
				struct whodun_FastaEntry* newEnt = whodun_circleVectorPushBack(&(toEdit->entries), 1, err);
				if(WHODUN_WASERR(err)){ return 0; }
				newEnt->nameLine = line0;
				newEnt->numLine = lineN - (line0 + 1);
				newEnt->numBase = numBase;
				line0 = lineN;
				numBase = 0;
			}
			else{
				//new set of base data
				if((curLine->len != 0) && (curLine->ptr[0] != ';')){
					//count the number of bases (non-whitespace) and check sanity
					const char* curP = curLine->ptr;
					whodun_UInt curL = curLine->len;
					while(curL){
						whodun_UInt numB = whodun_memcspn(curP, curL, FASTA_WS, FASTA_NWS);
							curP += numB;
							curL -= numB;
						whodun_UInt numW = whodun_memspn(curP, curL, FASTA_WS, FASTA_NWS);
							curP += numW;
							curL -= numW;
						numBase += numB;
					}
				}
			}
			lineN++;
		}
		toEdit->lineN = line0;
	//if end of file, add the final entry (must exist by this point in the code)
		if(toEdit->sourceMore == 0){
			struct whodun_FastaEntry* newEnt = whodun_circleVectorPushBack(&(toEdit->entries), 1, err);
			if(WHODUN_WASERR(err)){ return 0; }
			newEnt->nameLine = line0;
			newEnt->numLine = lineN - (line0 + 1);
			newEnt->numBase = numBase;
			toEdit->lineN = lineN;
		}
	return toEdit->sourceMore;
}
void whodun_fastaFileReaderDropSome_imp(struct whodun_FastaFileReader* toEdit, whodun_UInt numDrop, struct whodun_ErrorLog* err){
	whodun_UInt totLinePop = 0;
	for(whodun_UInt i = 0; i<numDrop; i++){
		struct whodun_FastaEntry* curEnt = whodun_circleVectorGet(&(toEdit->entries), i);
		totLinePop += (curEnt->numLine + 1);
	}
	whodun_circleVectorPopFront(&(toEdit->entries), numDrop);
	whodun_lineFileReaderDropSome(&(toEdit->source), totLinePop, err);
	if(WHODUN_WASERR(err)){ return; }
	//fix things
	toEdit->lineN -= totLinePop;
	for(whodun_UInt i = 0; i<toEdit->entries.len; i++){
		struct whodun_FastaEntry* curEnt = whodun_circleVectorGet(&(toEdit->entries), i);
		curEnt->nameLine -= totLinePop;
	}
}
struct whodun_ByteArray whodun_fastaFileEntryName_imp(struct whodun_FastaEntry* toGet, struct whodun_FastaFileReader* fromFile){
	struct whodun_ByteArray* curLine = whodun_circleVectorGet(&(fromFile->source.lines), toGet->nameLine);
	struct whodun_ByteArray curName = *curLine;
	//remove the leading >
		curName.len--;
		curName.ptr++;
	//skip leading whitespace
		whodun_UInt numW = whodun_memspn(curName.ptr, curName.len, FASTA_WS, FASTA_NWS);
		curName.len -= numW;
		curName.ptr += numW;
	//remove trailing whitespace
		while(curName.len && strchr(FASTA_WS, curName.ptr[curName.len-1])){
			curName.len--;
		}
	return curName;
}
void whodun_fastaFileEntryCopy_imp(struct whodun_FastaEntry* toGet, struct whodun_FastaFileReader* fromFile, char* toBuff){
	char* curTgt = toBuff;
	whodun_UInt line0 = toGet->nameLine + 1;
	for(whodun_UInt li = 0; li<toGet->numLine; li++){
		struct whodun_ByteArray* curLine = whodun_circleVectorGet(&(fromFile->source.lines), line0 + li);
		const char* curP = curLine->ptr;
		whodun_UInt curL = curLine->len;
		while(curL){
			whodun_UInt numB = whodun_memcspn(curP, curL, FASTA_WS, FASTA_NWS);
				memcpy(curTgt, curP, numB);
				curTgt += numB;
				curP += numB;
				curL -= numB;
			whodun_UInt numW = whodun_memspn(curP, curL, FASTA_WS, FASTA_NWS);
				curP += numW;
				curL -= numW;
		}
	}
}
void whodun_fastaFileEntryCopyLong_imp(struct whodun_FastaEntry* toGet, struct whodun_FastaFileReader* fromFile, char* toBuff, struct whodun_ErrorLog* err){
	whodun_fastaFileEntryCopy_imp(toGet, fromFile, toBuff);
}
void whodun_fastaFileReaderFin_imp(struct whodun_FastaFileReader* toKill){
	whodun_circleVectorFin(&(toKill->entries));
	whodun_lineFileReaderFin(&(toKill->source));
}

void (*whodun_fastaFileReaderInit)(struct whodun_FastaFileReader* toInit, struct whodun_InputStream* source, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err) = whodun_fastaFileReaderInit_imp;
whodun_Bool (*whodun_fastaFileReaderReadMore)(struct whodun_FastaFileReader* toEdit, struct whodun_ErrorLog* err) = whodun_fastaFileReaderReadMore_imp;
void (*whodun_fastaFileReaderDropSome)(struct whodun_FastaFileReader* toEdit, whodun_UInt numDrop, struct whodun_ErrorLog* err) = whodun_fastaFileReaderDropSome_imp;
struct whodun_ByteArray (*whodun_fastaFileEntryName)(struct whodun_FastaEntry* toGet, struct whodun_FastaFileReader* fromFile) = whodun_fastaFileEntryName_imp;
void (*whodun_fastaFileEntryCopy)(struct whodun_FastaEntry* toGet, struct whodun_FastaFileReader* fromFile, char* toBuff) = whodun_fastaFileEntryCopy_imp;
void (*whodun_fastaFileEntryCopyLong)(struct whodun_FastaEntry* toGet, struct whodun_FastaFileReader* fromFile, char* toBuff, struct whodun_ErrorLog* err) = whodun_fastaFileEntryCopyLong_imp;
void (*whodun_fastaFileReaderFin)(struct whodun_FastaFileReader* toKill) = whodun_fastaFileReaderFin_imp;


