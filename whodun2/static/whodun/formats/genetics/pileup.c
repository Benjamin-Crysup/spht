#include "whodun/formats/genetics/pileup.h"

#include "whodun/ermac.h"
#include "whodun/string.h"

void whodun_samtoolsPileupNextRead_imp(struct whodun_SamtoolsPileupRead* toFill, struct whodun_ByteArray* toParse, struct whodun_ErrorLog* err){
	whodun_UInt numC = toParse->len;
	char* curP = toParse->ptr;
	//get the first character
		char firstB = *curP;
		numC--; curP++;
	//see if it is the first character of a read
		if(firstB == '^'){
			if(!numC){ goto error_truncate; }
			toFill->first = 1;
			toFill->mapQ = * curP;
			numC--; curP++;
			if(!numC){ goto error_truncate; }
			firstB = *curP;
			numC--; curP++;
		}
		else{
			toFill->first = 0;
			toFill->mapQ = 0;
		}
	//save the base
		if(strchr(".,ACGTNacgtn<>*#", firstB) == 0){ goto error_insane; }
		toFill->base = firstB;
	//see if insertion data follows
		if(numC && (*curP == '+')){
			numC--; curP++;
			whodun_UInt numDig = whodun_memspn(curP, numC, "0123456789", 10);
			if(numDig == 0){ goto error_insane; }
			struct whodun_ByteArray digs = whodun_byteArrayPack(numDig, curP);
			whodun_UInt numIB = whodun_asciiToInt(&digs);
			numC -= numDig; curP += numDig;
			if(numC < numIB){ goto error_truncate; }
			toFill->inserted.ptr = curP;
			toFill->inserted.len = numIB;
			numC -= numIB; curP += numIB;
		}
		else{
			toFill->inserted.len = 0;
		}
	//see if deletion data follows
		if(numC && (*curP == '-')){
			numC--; curP++;
			whodun_UInt numDig = whodun_memspn(curP, numC, "0123456789", 10);
			if(numDig == 0){ goto error_insane; }
			struct whodun_ByteArray digs = whodun_byteArrayPack(numDig, curP);
			whodun_UInt numIB = whodun_asciiToInt(&digs);
			numC -= numDig; curP += numDig;
			if(numC < numIB){ goto error_truncate; }
			toFill->deleted.ptr = curP;
			toFill->deleted.len = numIB;
			numC -= numIB; curP += numIB;
		}
		else{
			toFill->deleted.len = 0;
		}
	//see if it is the end
		if(numC && (*curP == '$')){
			toFill->last = 1;
			numC--; curP++;
		}
		else{
			toFill->last = 0;
		}
	//fix up the data
		toParse->len = numC;
		toParse->ptr = curP;
	return;
	
	error_insane:
	error_truncate:
		WHODUN_ERR_MARK_SIGNAL(FORMAT_PILEUP_MALFORM, err);
}

void (*whodun_samtoolsPileupNextRead)(struct whodun_SamtoolsPileupRead* toFill, struct whodun_ByteArray* toParse, struct whodun_ErrorLog* err) = whodun_samtoolsPileupNextRead_imp;


