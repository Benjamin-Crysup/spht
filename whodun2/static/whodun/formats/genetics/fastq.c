#include "whodun/formats/genetics/fastq.h"

#include <math.h>

#include "whodun/defs.h"
#include "whodun/math.h"
#include "whodun/ermac.h"
#include "whodun/string.h"
#include "whodun/cpuvec.h"
#include "whodun/cpuvecx.h"

#define FASTQ_NWS 4
#define FASTQ_WS " \r\t\n"

struct whodun_ByteArray whodun_fastq_help_trim(struct whodun_ByteArray toTrim){
	struct whodun_ByteArray curName = toTrim;
	//skip leading whitespace
		whodun_UInt numW = whodun_memspn(curName.ptr, curName.len, FASTQ_WS, FASTQ_NWS);
		curName.len -= numW;
		curName.ptr += numW;
	//remove trailing whitespace
		while(curName.len && strchr(FASTQ_WS, curName.ptr[curName.len-1])){
			curName.len--;
		}
	return curName;
}

void whodun_fastqFileReaderInit_imp(struct whodun_FastqFileReader* toInit, struct whodun_InputStream* source, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err){
	whodun_lineFileReaderInit(&(toInit->source), source, useAl, usePool, err);
	if(WHODUN_WASERR(err)){ goto errorA; }
	toInit->lineN = 0;
	toInit->sourceMore = 1;
	whodun_circleVectorInit(&(toInit->entries), sizeof(struct whodun_FastqEntry), useAl, err);
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
whodun_Bool whodun_fastqFileReaderReadMore_imp(struct whodun_FastqFileReader* toEdit, struct whodun_ErrorLog* err){
	if(toEdit->sourceMore == 0){ return 0; }
	//load more data
		toEdit->sourceMore = whodun_lineFileReaderReadMore(&(toEdit->source), err);
		if(WHODUN_WASERR(err)){ return 0; }
	//chop it up
		whodun_UInt lineN = toEdit->lineN;
		whodun_UInt nLine = toEdit->source.lines.len;
		while((nLine - lineN) >= 4){
			struct whodun_ByteArray* curLine = whodun_circleVectorGet(&(toEdit->source.lines), lineN);
			if((curLine->len == 0) || (curLine->ptr[0] != '@')){
				struct whodun_ByteArray trimLine = whodun_fastq_help_trim(*curLine);
				if(trimLine.len != 0){
					WHODUN_ERR_MARK_SIGNAL(FORMAT_FASTQ_MALFORM, err)
					return 0;
				}
				lineN++;
				continue;
			}
			//I don't care about the name contents
			//idiot check sequence (no leading whitespace)
				struct whodun_ByteArray* baseLine = whodun_circleVectorGet(&(toEdit->source.lines), lineN + 1);
				struct whodun_ByteArray baseTrim = whodun_fastq_help_trim(*baseLine);
				if(baseTrim.ptr != baseLine->ptr){
					WHODUN_ERR_MARK_SIGNAL(FORMAT_FASTQ_MALFORM, err)
					return 0;
				}
			//make sure the separator is there (ignore the repeat)
				struct whodun_ByteArray* sepLine = whodun_circleVectorGet(&(toEdit->source.lines), lineN + 2);
				if((sepLine->len == 0) || (sepLine->ptr[0] != '+')){
					WHODUN_ERR_MARK_SIGNAL(FORMAT_FASTQ_MALFORM, err)
					return 0;
				}
			//check the quality (in valid range, no leading whitespace)
				struct whodun_ByteArray* qualLine = whodun_circleVectorGet(&(toEdit->source.lines), lineN + 3);
				struct whodun_ByteArray qualTrim = whodun_fastq_help_trim(*qualLine);
				if((qualTrim.ptr != qualLine->ptr) || (qualTrim.len != baseTrim.len)){
					WHODUN_ERR_MARK_SIGNAL(FORMAT_FASTQ_MALFORM, err)
					return 0;
				}
				for(whodun_UInt i = 0; i<qualTrim.len; i++){
					int curQ = 0x00FF & qualTrim.ptr[i];
					if((curQ < 33) || (curQ > 126)){
						WHODUN_ERR_MARK_SIGNAL(FORMAT_FASTQ_MALFORM, err)
						return 0;
					}
				}
			//make the entry
				struct whodun_FastqEntry* newEnt = whodun_circleVectorPushBack(&(toEdit->entries), 1, err);
				if(WHODUN_WASERR(err)){ return 0; }
				newEnt->nameLine = lineN;
			//advance
				lineN += 4;
				toEdit->lineN = lineN;
		}
	//complain if end on a tear
		if((toEdit->sourceMore == 0) && (lineN != nLine)){
			WHODUN_ERR_MARK_SIGNAL(FORMAT_FASTQ_MALFORM, err)
			return 0;
		}
	return toEdit->sourceMore;
}
void whodun_fastqFileReaderDropSome_imp(struct whodun_FastqFileReader* toEdit, whodun_UInt numDrop, struct whodun_ErrorLog* err){
	if(numDrop == 0){ return; }
	//do the drop
		struct whodun_FastqEntry* curEnt = whodun_circleVectorGet(&(toEdit->entries), numDrop - 1);
		whodun_UInt totLinePop = curEnt->nameLine + 4;
		whodun_circleVectorPopFront(&(toEdit->entries), numDrop);
		whodun_lineFileReaderDropSome(&(toEdit->source), totLinePop, err);
		if(WHODUN_WASERR(err)){ return; }
	//fix things
		toEdit->lineN -= totLinePop;
		for(whodun_UInt i = 0; i<toEdit->entries.len; i++){
			curEnt = whodun_circleVectorGet(&(toEdit->entries), i);
			curEnt->nameLine -= totLinePop;
		}
}
struct whodun_ByteArray whodun_fastqFileEntryName_imp(struct whodun_FastqEntry* toGet, struct whodun_FastqFileReader* fromFile){
	struct whodun_ByteArray* curLine = whodun_circleVectorGet(&(fromFile->source.lines), toGet->nameLine);
	struct whodun_ByteArray curName = *curLine;
	//remove the leading @
		curName.len--;
		curName.ptr++;
	return whodun_fastq_help_trim(curName);
}
struct whodun_ByteArray whodun_fastqFileEntrySeq_imp(struct whodun_FastqEntry* toGet, struct whodun_FastqFileReader* fromFile){
	struct whodun_ByteArray* curLine = whodun_circleVectorGet(&(fromFile->source.lines), toGet->nameLine + 1);
	struct whodun_ByteArray curBase = *curLine;
	//trim from end is necessary (CR LF)
	//trim from front... meh
	return whodun_fastq_help_trim(curBase);
}
struct whodun_ByteArray whodun_fastqFileEntryQual_imp(struct whodun_FastqEntry* toGet, struct whodun_FastqFileReader* fromFile){
	struct whodun_ByteArray* curLine = whodun_circleVectorGet(&(fromFile->source.lines), toGet->nameLine + 3);
	struct whodun_ByteArray curQual = *curLine;
	return whodun_fastq_help_trim(curQual);
}
void whodun_fastqFileReaderFin_imp(struct whodun_FastqFileReader* toKill){
	whodun_circleVectorFin(&(toKill->entries));
	whodun_lineFileReaderFin(&(toKill->source));
}
void whodun_fastqQualToProb_imp(whodun_UInt numBase, char* bqual, whodun_Float* bprob){
	whodun_Float lconvRat = -10.0 * log10(WHODUN_E);
	whodun_UInt numLeft = numBase;
	char* nqual = bqual;
	whodun_Float* nprob = bprob;
#if WHODUN_VECTOR_WIDTH > 1
	while(numLeft >= WHODUN_VECTOR_WIDTH){
		whodun_UIntV fpEst = whodun_vec_subI(whodun_vec_punU2I(whodun_vec_loadB(nqual)), whodun_vec_bcI(33));
		whodun_FloatV lnPro = whodun_vec_divF(whodun_vec_convertI2F(fpEst), whodun_vec_bcF(lconvRat));
		whodun_vec_storeF(nprob, whodun_expV(lnPro));
		numLeft -= WHODUN_VECTOR_WIDTH;
		nqual += WHODUN_VECTOR_WIDTH;
		nprob += WHODUN_VECTOR_WIDTH;
	}
#endif
	while(numLeft){
		*nprob = exp((*nqual - 33) / lconvRat);
		numLeft--;
		nqual++;
		nprob++;
	}
}
void whodun_fastqProbToQual_imp(whodun_UInt numBase, whodun_Float* bprob, char* bqual){
	whodun_Float lconvRat = -10.0 / log(10.0);
	whodun_UInt numLeft = numBase;
	char* nqual = bqual;
	whodun_Float* nprob = bprob;
#if WHODUN_VECTOR_WIDTH > 1
	while(numLeft >= WHODUN_VECTOR_WIDTH){
		whodun_FloatV logPro = whodun_vec_mulF(whodun_logV(whodun_vec_loadF(nprob)), whodun_vec_bcF(lconvRat));
			whodun_UIntV tooBig = whodun_vec_compGtF(logPro, whodun_vec_bcF(93.0));
			whodun_UIntV notNan = whodun_vec_andU(whodun_vec_notU(tooBig), whodun_vec_compGtF(logPro, whodun_vec_bcF(0.0)));
			//taking advantage of 0 being 0 to clamp nan and weirds to 0
			logPro = whodun_vec_switch2F(tooBig, whodun_vec_bcF(93.0), notNan, logPro);
		whodun_UIntV endQs = whodun_vec_addU(whodun_vec_punI2U(whodun_vec_convertF2I(logPro)), whodun_vec_bcU(33));
		whodun_vec_storeB(nqual, endQs);
		numLeft -= WHODUN_VECTOR_WIDTH;
		nqual += WHODUN_VECTOR_WIDTH;
		nprob += WHODUN_VECTOR_WIDTH;
	}
#endif
	while(numLeft){
		double logPro = *nprob * lconvRat;
			logPro = logPro > 93.0 ? 93.0 : logPro;
			logPro = logPro > 0.0 ? logPro : 0.0;
		*nqual = 33 + (int)logPro;
		numLeft--;
		nqual++;
		nprob++;
	}
}

void (*whodun_fastqFileReaderInit)(struct whodun_FastqFileReader* toInit, struct whodun_InputStream* source, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err) = whodun_fastqFileReaderInit_imp;
whodun_Bool (*whodun_fastqFileReaderReadMore)(struct whodun_FastqFileReader* toEdit, struct whodun_ErrorLog* err) = whodun_fastqFileReaderReadMore_imp;
void (*whodun_fastqFileReaderDropSome)(struct whodun_FastqFileReader* toEdit, whodun_UInt numDrop, struct whodun_ErrorLog* err) = whodun_fastqFileReaderDropSome_imp;
struct whodun_ByteArray (*whodun_fastqFileEntryName)(struct whodun_FastqEntry* toGet, struct whodun_FastqFileReader* fromFile) = whodun_fastqFileEntryName_imp;
struct whodun_ByteArray (*whodun_fastqFileEntrySeq)(struct whodun_FastqEntry* toGet, struct whodun_FastqFileReader* fromFile) = whodun_fastqFileEntrySeq_imp;
struct whodun_ByteArray (*whodun_fastqFileEntryQual)(struct whodun_FastqEntry* toGet, struct whodun_FastqFileReader* fromFile) = whodun_fastqFileEntryQual_imp;
void (*whodun_fastqFileReaderFin)(struct whodun_FastqFileReader* toKill) = whodun_fastqFileReaderFin_imp;
void (*whodun_fastqQualToProb)(whodun_UInt numBase, char* bqual, whodun_Float* bprob) = whodun_fastqQualToProb_imp;
void (*whodun_fastqProbToQual)(whodun_UInt numBase, whodun_Float* bprob, char* bqual) = whodun_fastqProbToQual_imp;

