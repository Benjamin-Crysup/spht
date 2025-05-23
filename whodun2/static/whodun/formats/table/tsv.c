#include "whodun/formats/table/tsv.h"

#include <string.h>

void whodun_tsvLineParserInit_imp(struct whodun_TsvLineParser* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	toInit->line.len = 0;
	toInit->line.ptr = 0;
	whodun_vectorInit(&(toInit->entries), sizeof(struct whodun_ByteArray), useAl, err);
	if(WHODUN_WASERR(err)){ goto errorA; }
	return;
	
	errorA:
		return;
}
void whodun_tsvLineParserSplit_imp(struct whodun_ByteArray line, struct whodun_TsvLineParser* toSave, struct whodun_ErrorLog* err){
	struct whodun_ByteArray curLine = line;
	//remove any ending newline (either CR-LF or LF)
		if(curLine.len && (curLine.ptr[curLine.len-1] == '\n')){
			curLine.len--;
			if(curLine.len && (curLine.ptr[curLine.len-1] == '\r')){
				curLine.len--;
			}
		}
	//empty line goes to zero entries
		toSave->entries.view.len = 0;
		if(curLine.len == 0){
			return;
		}
	//cut into delimitted entries
		whodun_UInt numEnts = 0;
		char* nextT = memchr(curLine.ptr, '\t', curLine.len);
		while(nextT){
			whodun_UInt curLen = nextT - curLine.ptr;
			whodun_vectorResize(&(toSave->entries), numEnts + 1, err);
			if(WHODUN_WASERR(err)){ return; }
			((struct whodun_ByteArray*)(toSave->entries.view.ptr))[numEnts] = whodun_byteArrayPack(curLen, curLine.ptr);
			curLine.ptr += (curLen + 1);
			curLine.len -= (curLen + 1);
			numEnts++;
			nextT = memchr(curLine.ptr, '\t', curLine.len);
		}
	//add the finale
		whodun_vectorResize(&(toSave->entries), numEnts + 1, err);
		if(WHODUN_WASERR(err)){ return; }
		((struct whodun_ByteArray*)(toSave->entries.view.ptr))[numEnts] = curLine;
}
struct whodun_ByteArray whodun_tsvParseEscapes_imp(struct whodun_ByteArray entry, char* toSave){
	char* nextSave = toSave;
	struct whodun_ByteArray curEnt = entry;
	while(curEnt.len){
		//eat up to the next backslash
			char* nextB = memchr(curEnt.ptr, '\\', curEnt.len);
			whodun_UInt curLen = nextB ? (nextB - curEnt.ptr) : curEnt.len;
			memcpy(nextSave, curEnt.ptr, curLen);
			nextSave += curLen;
			curEnt.ptr += curLen;
			curEnt.len -= curLen;
			if(!nextB){ continue; }
		//handle the escape (invalid escapes go to backslash)
			if(curEnt.len == 1){
				*nextSave = '\\';
				curLen = 1;
			}
			else{
				switch(nextB[1]){
					case '\\':
						*nextSave = '\\';
						curLen = 2;
						break;
					case 'r':
						*nextSave = '\r';
						curLen = 2;
						break;
					case 'n':
						*nextSave = '\n';
						curLen = 2;
						break;
					case 't':
						*nextSave = '\t';
						curLen = 2;
						break;
					default:
						*nextSave = '\\';
						curLen = 1;
						break;
				}
			}
			nextSave++;
			curEnt.ptr += curLen;
			curEnt.len -= curLen;
	}
	return whodun_byteArrayPack((nextSave - toSave), toSave);
}
void whodun_tsvLineParserFin_imp(struct whodun_TsvLineParser* toKill){
	whodun_vectorFin(&(toKill->entries));
}

void (*whodun_tsvLineParserInit)(struct whodun_TsvLineParser* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = whodun_tsvLineParserInit_imp;
void (*whodun_tsvLineParserSplit)(struct whodun_ByteArray line, struct whodun_TsvLineParser* toSave, struct whodun_ErrorLog* err) = whodun_tsvLineParserSplit_imp;
struct whodun_ByteArray (*whodun_tsvParseEscapes)(struct whodun_ByteArray entry, char* toSave) = whodun_tsvParseEscapes_imp;
void (*whodun_tsvLineParserFin)(struct whodun_TsvLineParser* toKill) = whodun_tsvLineParserFin_imp;

