
#include "whodun/defs.h"
#include "whodun/test.h"
#include "whodun/error.h"
#include "whodun/cpuvec.h"

#include "testmain.h"

void cpuvec_markfail(const char* errMess, struct whodun_ErrorLog* err){
	struct whodun_ErrorInfo info0;
		info0.type = WHODUN_ERROR_INFO_MESSAGE;
		info0.data.mess = whodun_byteArrayPackNull(errMess);
		info0.next = 0;
	WHODUN_CFUN(whodun_ErrorLog, mark, err)(err, WHODUN_ERROR_SEVERITY_PANIC, &info0);
}

void cpuvec_testFunLoadU1(struct whodun_ErrorLog* err){
	whodun_UInt srcV[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){ srcV[i] = i; }
	whodun_UInt dstV[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeU(dstV, whodun_vec_loadU(srcV));
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		if(dstV[i] != i){
			cpuvec_markfail("dstV != srcV", err);
			return;
		}
	}
}
struct whodun_UnitTest cpuvec_testLoadU1 = {
	"load/store U",
	cpuvec_testFunLoadU1,
	__FILE__,
	__LINE__
};

void cpuvec_testFunLoadI1(struct whodun_ErrorLog* err){
	whodun_Int srcV[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){ srcV[i] = -i; }
	whodun_Int dstV[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeI(dstV, whodun_vec_loadI(srcV));
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		if(dstV[i] != -i){
			cpuvec_markfail("dstV != srcV", err);
			return;
		}
	}
}
struct whodun_UnitTest cpuvec_testLoadI1 = {
	"load/store I",
	cpuvec_testFunLoadI1,
	__FILE__,
	__LINE__
};

void cpuvec_testFunLoadF1(struct whodun_ErrorLog* err){
	whodun_Float srcV[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){ srcV[i] = i/2.0; }
	whodun_Float dstV[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeF(dstV, whodun_vec_loadF(srcV));
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		if(dstV[i] != (i/2.0)){
			cpuvec_markfail("dstV != srcV", err);
			return;
		}
	}
}
struct whodun_UnitTest cpuvec_testLoadF1 = {
	"load/store F",
	cpuvec_testFunLoadF1,
	__FILE__,
	__LINE__
};

void cpuvec_testFunLoadP1(struct whodun_ErrorLog* err){
	const char* baseStr = "ABCDEFGH";
	void* srcV[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){ srcV[i] = (void*)(baseStr + (i % 8)); }
	void* dstV[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeP(dstV, whodun_vec_loadP(srcV));
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		if(*(char*)(dstV[i]) != ('A' + (i%8))){
			cpuvec_markfail("dstV != srcV", err);
			return;
		}
	}
}
struct whodun_UnitTest cpuvec_testLoadP1 = {
	"load/store P",
	cpuvec_testFunLoadP1,
	__FILE__,
	__LINE__
};

void cpuvec_testFunLoadB1(struct whodun_ErrorLog* err){
	char srcV[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){ srcV[i] = i; }
	char dstV[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeB(dstV, whodun_vec_loadB(srcV));
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		if((dstV[i] & 0x00FF) != (i & 0x00FF)){
			cpuvec_markfail("dstV != srcV", err);
			return;
		}
	}
}
struct whodun_UnitTest cpuvec_testLoadB1 = {
	"load/store B",
	cpuvec_testFunLoadB1,
	__FILE__,
	__LINE__
};

void cpuvec_testFunIndex(struct whodun_ErrorLog* err){
	whodun_UInt dstV[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeU(dstV, whodun_vec_ind);
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		if(dstV[i] != i){
			cpuvec_markfail("dstV != index", err);
			return;
		}
	}
}
struct whodun_UnitTest cpuvec_testIndex = {
	"index",
	cpuvec_testFunIndex,
	__FILE__,
	__LINE__
};

void cpuvec_testFunGatherU1(struct whodun_ErrorLog* err){
	whodun_UInt srcV[WHODUN_VECTOR_WIDTH];
	whodun_UInt indV[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		srcV[i] = i;
		indV[i] = WHODUN_VECTOR_WIDTH - (i+1);
	}
	whodun_UInt dstV[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeU(dstV, whodun_vec_gatherU(srcV, whodun_vec_loadU(indV)));
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		if(dstV[i] != (WHODUN_VECTOR_WIDTH - (i+1))){
			cpuvec_markfail("dstV[i] != srcV[W-i]", err);
			return;
		}
	}
}
struct whodun_UnitTest cpuvec_testGatherU1 = {
	"gather U",
	cpuvec_testFunGatherU1,
	__FILE__,
	__LINE__
};

void cpuvec_testFunGatherI1(struct whodun_ErrorLog* err){
	whodun_Int srcV[WHODUN_VECTOR_WIDTH];
	whodun_UInt indV[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		srcV[i] = i;
		indV[i] = WHODUN_VECTOR_WIDTH - (i+1);
	}
	whodun_Int dstV[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeI(dstV, whodun_vec_gatherI(srcV, whodun_vec_loadU(indV)));
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		if(dstV[i] != (WHODUN_VECTOR_WIDTH - (i+1))){
			cpuvec_markfail("dstV[i] != srcV[W-i]", err);
			return;
		}
	}
}
struct whodun_UnitTest cpuvec_testGatherI1 = {
	"gather I",
	cpuvec_testFunGatherI1,
	__FILE__,
	__LINE__
};

void cpuvec_testFunGatherF1(struct whodun_ErrorLog* err){
	whodun_Float srcV[WHODUN_VECTOR_WIDTH];
	whodun_UInt indV[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		srcV[i] = i/2.0;
		indV[i] = WHODUN_VECTOR_WIDTH - (i+1);
	}
	whodun_Float dstV[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeF(dstV, whodun_vec_gatherF(srcV, whodun_vec_loadU(indV)));
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		if(dstV[i] != (WHODUN_VECTOR_WIDTH - (i+1))/2.0){
			cpuvec_markfail("dstV[i] != srcV[W-i]", err);
			return;
		}
	}
}
struct whodun_UnitTest cpuvec_testGatherF1 = {
	"gather F",
	cpuvec_testFunGatherF1,
	__FILE__,
	__LINE__
};

void cpuvec_testFunGatherB1(struct whodun_ErrorLog* err){
	char srcV[WHODUN_VECTOR_WIDTH];
	whodun_UInt indV[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		srcV[i] = '0' + i;
		indV[i] = WHODUN_VECTOR_WIDTH - (i+1);
	}
	char dstV[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeB(dstV, whodun_vec_gatherB(srcV, whodun_vec_loadU(indV)));
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		if(dstV[i] != ('0' + (WHODUN_VECTOR_WIDTH - (i+1)))){
			cpuvec_markfail("dstV[i] != srcV[W-i]", err);
			return;
		}
	}
}
struct whodun_UnitTest cpuvec_testGatherB1 = {
	"gather B",
	cpuvec_testFunGatherB1,
	__FILE__,
	__LINE__
};

/*
TODO scatter
TODO gather P
TODO scatter P
TODO pun
TODO bc
TODO comp (== != < > <= >=)
TODO & | ^ ~
TODO + - * / % max min
TODO conv
TODO h & | ^ + * max min
TODO switch
	#define whodun_vec_scatterU_imp(toA, atInds, toV) ((fromA)[atInds] = (toV))
	#define whodun_vec_scatterI_imp(toA, atInds, toV) ((fromA)[atInds] = (toV))
	#define whodun_vec_scatterF_imp(toA, atInds, toV) ((fromA)[atInds] = (toV))
	#define whodun_vec_scatterB_imp(toA, atInds, toV) ((fromA)[atInds] = (toV))
	#define whodun_vec_gatherPU_imp(fromA) (*(whodun_UInt*)(fromA))
	#define whodun_vec_gatherPI_imp(fromA) (*(whodun_Int*)(fromA))
	#define whodun_vec_gatherPF_imp(fromA) (*(whodun_Float*)(fromA))
	#define whodun_vec_gatherPB_imp(fromA) ((whodun_UInt)(*(unsigned char*)(fromA)))
	#define whodun_vec_scatterPU_imp(toA, toV) (*(whodun_UInt*)(fromA) = (toV))
	#define whodun_vec_scatterPI_imp(toA, toV) (*(whodun_Int*)(fromA) = (toV))
	#define whodun_vec_scatterPF_imp(toA, toV) (*(whodun_Float*)(fromA) = (toV))
	#define whodun_vec_scatterPB_imp(toA, toV) (*(char*)(fromA) = (toV))
*/

//TODO

void cpuvec_setup(struct whodun_ErrorLog* err){
	//no setup
}

void cpuvec_teardown(struct whodun_ErrorLog* err){
	//no setup
}

#define NUM_TEST 10

struct whodun_UnitTest* cpuvec_allTests[] = {
	&cpuvec_testLoadU1,
	&cpuvec_testLoadI1,
	&cpuvec_testLoadF1,
	&cpuvec_testLoadP1,
	&cpuvec_testLoadB1,
	&cpuvec_testIndex,
	&cpuvec_testGatherU1,
	&cpuvec_testGatherI1,
	&cpuvec_testGatherF1,
	&cpuvec_testGatherB1
};

struct whodun_UnitTestSet testCpuvec = {
	"cpuvec",
	
	cpuvec_setup,
	__FILE__,
	__LINE__,
	
	NUM_TEST,
	cpuvec_allTests,
	
	cpuvec_teardown,
	__FILE__,
	__LINE__
};

