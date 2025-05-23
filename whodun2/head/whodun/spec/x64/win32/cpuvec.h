#ifndef WHODUN_CPUVEC_H
#define WHODUN_CPUVEC_H 1

/**
 * @file
 * @brief Vector ops for this x86-64 machine.
 */

#include "whodun/cpu.h"
#include "whodun/defs.h"

/** @cond PRIVATE_HELPERS */

#if WHODUN_X64_NOSSE
	#define whodun_vec_loadU_imp(fromP) (*(fromP))
	#define whodun_vec_storeU_imp(toP, toV) (*(fromP) = (toV))
	#define whodun_vec_loadI_imp(fromP) (*(fromP))
	#define whodun_vec_storeI_imp(toP, toV) (*(fromP) = (toV))
	#define whodun_vec_loadF_imp(fromP) (*(fromP))
	#define whodun_vec_storeF_imp(toP, toV) (*(fromP) = (toV))
	#define whodun_vec_loadP_imp(fromP) (*(fromP))
	#define whodun_vec_storeP_imp(toP, toV) (*(toP) = (toV))
	#define whodun_vec_loadB_imp(fromP) (*(unsigned char*)(fromP))
	#define whodun_vec_storeB_imp(toP, toV) (*(toP) = (toV))
	#define whodun_vec_gatherU_imp(fromA, atInds) ((fromA)[atInds])
	#define whodun_vec_gatherI_imp(fromA, atInds) ((fromA)[atInds])
	#define whodun_vec_gatherF_imp(fromA, atInds) ((fromA)[atInds])
	#define whodun_vec_gatherB_imp(fromA, atInds) ((whodun_UInt)(((unsigned char*)(fromA))[atInds]))
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
	#define whodun_vec_punU2I_imp(fromV) ((whodun_IntV)(fromV))
	#define whodun_vec_punU2F_imp(fromV) (whodun_unpackFlt(fromV))
	#define whodun_vec_punU2P_imp(fromV) ((void*)(fromV))
	#define whodun_vec_punI2U_imp(fromV) ((whodun_IntV)(fromV))
	#define whodun_vec_punI2F_imp(fromV) (whodun_unpackFlt(fromV))
	#define whodun_vec_punF2U_imp(fromV) (whodun_packFlt(fromV))
	#define whodun_vec_punF2I_imp(fromV) ((whodun_Int)(whodun_packFlt(fromV)))
	#define whodun_vec_punP2U_imp(fromV) ((whodun_UInt)(fromV))
	#define whodun_vec_bcU_imp(fromV) (fromV)
	#define whodun_vec_bcI_imp(fromV) (fromV)
	#define whodun_vec_bcF_imp(fromV) (fromV)
	#define whodun_vec_bcP_imp(fromV) (fromV)
	#define whodun_vec_ind_imp (0)
	#define whodun_vec_compEqU_imp(opA, opB) (((opA) == (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compNeU_imp(opA, opB) (((opA) != (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compLtU_imp(opA, opB) (((opA) < (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compGtU_imp(opA, opB) (((opA) > (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compLteU_imp(opA, opB) (((opA) <= (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compGteU_imp(opA, opB) (((opA) >= (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compEqI_imp(opA, opB) (((opA) == (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compNeI_imp(opA, opB) (((opA) != (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compLtI_imp(opA, opB) (((opA) < (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compGtI_imp(opA, opB) (((opA) > (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compLteI_imp(opA, opB) (((opA) <= (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compGteI_imp(opA, opB) (((opA) >= (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compEqF_imp(opA, opB) (((opA) == (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compNeF_imp(opA, opB) (((opA) != (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compLtF_imp(opA, opB) (((opA) < (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compGtF_imp(opA, opB) (((opA) > (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compLteF_imp(opA, opB) (((opA) <= (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_compGteF_imp(opA, opB) (((opA) >= (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)
	#define whodun_vec_andU_imp(opA, opB) ((opA) & (opB))
	#define whodun_vec_orU_imp(opA, opB) ((opA) | (opB))
	#define whodun_vec_xorU_imp(opA, opB) ((opA) ^ (opB))
	#define whodun_vec_notU_imp(opA) (~(opA))
	#define whodun_vec_lshU_imp(opA, opB) ((opA) << (opB))
	#define whodun_vec_rshU_imp(opA, opB) ((opA) >> (opB))
	#define whodun_vec_rshI_imp(opA, opB) ((opA) >> (opB))
	#define whodun_vec_addU_imp(opA, opB) ((opA) + (opB))
	#define whodun_vec_addI_imp(opA, opB) ((opA) + (opB))
	#define whodun_vec_addF_imp(opA, opB) ((opA) + (opB))
	#define whodun_vec_addP_imp(opA, opB) ((void*)((char*)(opA) + (opB)))
	#define whodun_vec_subU_imp(opA, opB) ((opA) - (opB))
	#define whodun_vec_subI_imp(opA, opB) ((opA) - (opB))
	#define whodun_vec_subF_imp(opA, opB) ((opA) - (opB))
	#define whodun_vec_negI_imp(opA) (-(opA))
	#define whodun_vec_negF_imp(opA) (-(opA))
	#define whodun_vec_mulU_imp(opA, opB) ((opA) * (opB))
	#define whodun_vec_mulI_imp(opA, opB) ((opA) * (opB))
	#define whodun_vec_mulF_imp(opA, opB) ((opA) * (opB))
	#define whodun_vec_divU_imp(opA, opB) ((opA) / (opB))
	#define whodun_vec_divI_imp(opA, opB) ((opA) / (opB))
	#define whodun_vec_divF_imp(opA, opB) ((opA) / (opB))
	#define whodun_vec_modU_imp(opA, opB) ((opA) % (opB))
	#define whodun_vec_modI_imp(opA, opB) ((opA) % (opB))
	#define whodun_vec_maxU_imp(opA, opB) (whodun_umax_imp((opA), (opB)))
	#define whodun_vec_maxI_imp(opA, opB) (whodun_max_imp((opA), (opB)))
	#define whodun_vec_maxF_imp(opA, opB) (whodun_fmax_imp((opA), (opB)))
	#define whodun_vec_minU_imp(opA, opB) (whodun_umin_imp((opA), (opB)))
	#define whodun_vec_minI_imp(opA, opB) (whodun_min_imp((opA), (opB)))
	#define whodun_vec_minF_imp(opA, opB) (whodun_fmin_imp((opA), (opB)))
	#define whodun_vec_convertI2F_imp(opA) ((whodun_Float)(opA))
	#define whodun_vec_convertF2I_imp(opA) ((whodun_Int)(opA))
	#define whodun_vec_handU_imp(opA) (opA)
	#define whodun_vec_horU_imp(opA) (opA)
	#define whodun_vec_hxorU_imp(opA) (opA)
	#define whodun_vec_haddU_imp(opA) (opA)
	#define whodun_vec_haddI_imp(opA) (opA)
	#define whodun_vec_haddF_imp(opA) (opA)
	#define whodun_vec_hmulU_imp(opA) (opA)
	#define whodun_vec_hmulI_imp(opA) (opA)
	#define whodun_vec_hmulF_imp(opA) (opA)
	#define whodun_vec_hmaxU_imp(opA) (opA)
	#define whodun_vec_hmaxI_imp(opA) (opA)
	#define whodun_vec_hmaxF_imp(opA) (opA)
	#define whodun_vec_hminU_imp(opA) (opA)
	#define whodun_vec_hminI_imp(opA) (opA)
	#define whodun_vec_hminF_imp(opA) (opA)
	#define WHODUN_VEC_LOOP_UNROLL_IMP(lvar, lcode) \
		{\
			lvar = 0;\
			{ lcode }\
		}
#elif WHODUN_X64_AVX
	#define whodun_vec_loadU_imp(fromP) (_mm256_loadu_si256((__m256i*)(fromP)))
	#define whodun_vec_storeU_imp(toP, toV) (_mm256_storeu_si256((__m256i*)(toP), (toV)))
	#define whodun_vec_loadI_imp(fromP) (_mm256_loadu_si256((__m256i*)(fromP)))
	#define whodun_vec_storeI_imp(toP, toV) (_mm256_storeu_si256((__m256i*)(toP), (toV)))
	#define whodun_vec_loadF_imp(fromP) (_mm256_loadu_pd(fromP))
	#define whodun_vec_storeF_imp(toP, toV) (_mm256_storeu_pd((toP), (toV)))
	#define whodun_vec_loadP_imp(fromP) (_mm256_loadu_si256((__m256i*)(fromP)))
	#define whodun_vec_storeP_imp(toP, toV) (_mm256_storeu_si256((__m256i*)(toP), (toV)))
	#define whodun_vec_loadB_imp(fromP) (whodun_vectorLoadB(fromP))
	#define whodun_vec_storeB_imp(toP, toV) (whodun_vectorStoreB((toP), (toV)))
	#define whodun_vec_gatherU_imp(fromA, atInds) (_mm256_i64gather_epi64((void*)(fromA), (atInds), 8))
	#define whodun_vec_gatherI_imp(fromA, atInds) (_mm256_i64gather_epi64((void*)(fromA), (atInds), 8))
	#define whodun_vec_gatherF_imp(fromA, atInds) (_mm256_i64gather_pd((fromA), (atInds), 8))
	#define whodun_vec_gatherB_imp(fromA, atInds) (whodun_vectorGatherB((fromA), (atInds)))
	#define whodun_vec_scatterU_imp(toA, atInds, toV) (whodun_vectorScatterU((toA), (atInds), (toV)))
	#define whodun_vec_scatterI_imp(toA, atInds, toV) (whodun_vectorScatterI((toA), (atInds), (toV)))
	#define whodun_vec_scatterF_imp(toA, atInds, toV) (whodun_vectorScatterF((toA), (atInds), (toV)))
	#define whodun_vec_scatterB_imp(toA, atInds, toV) (whodun_vectorScatterB((toA), (atInds), (toV)))
	#define whodun_vec_gatherPU_imp(fromA) (_mm256_i64gather_epi64(0, (fromA), 1))
	#define whodun_vec_gatherPI_imp(fromA) (_mm256_i64gather_epi64(0, (fromA), 1))
	#define whodun_vec_gatherPF_imp(fromA) (_mm256_i64gather_pd(0, (fromA), 1))
	#define whodun_vec_gatherPB_imp(fromA) (whodun_vectorAddrGatherB(fromA))
	#define whodun_vec_scatterPU_imp(toA, toV) (whodun_vectorAddrScatterU((toA), (toV)))
	#define whodun_vec_scatterPI_imp(toA, toV) (whodun_vectorAddrScatterI((toA), (toV)))
	#define whodun_vec_scatterPF_imp(toA, toV) (whodun_vectorAddrScatterF((toA), (toV)))
	#define whodun_vec_scatterPB_imp(toA, toV) (whodun_vectorAddrScatterB((toA), (toV)))
	#define whodun_vec_punU2I_imp(fromV) (fromV)
	#define whodun_vec_punU2F_imp(fromV) (_mm256_castsi256_pd(fromV))
	#define whodun_vec_punU2P_imp(fromV) (fromV)
	#define whodun_vec_punI2U_imp(fromV) (fromV)
	#define whodun_vec_punI2F_imp(fromV) (_mm256_castsi256_pd(fromV))
	#define whodun_vec_punF2U_imp(fromV) (_mm256_castpd_si256(fromV))
	#define whodun_vec_punF2I_imp(fromV) (_mm256_castpd_si256(fromV))
	#define whodun_vec_punP2U_imp(fromV) (fromV)
	#define whodun_vec_bcU_imp(fromV) (_mm256_set1_epi64x(fromV))
	#define whodun_vec_bcI_imp(fromV) (_mm256_set1_epi64x(fromV))
	#define whodun_vec_bcF_imp(fromV) (_mm256_set1_pd(fromV))
	#define whodun_vec_bcP_imp(fromV) (_mm256_set1_epi64x((whodun_UInt)(fromV)))
	#define whodun_vec_ind_imp (_mm256_set_epi64x(3,2,1,0))
	#define whodun_vec_compEqU_imp(opA, opB) (_mm256_cmpeq_epi64((opA), (opB)))
	#define whodun_vec_compNeU_imp(opA, opB) (_mm256_xor_si256(_mm256_cmpeq_epi64((opA), (opB)), _mm256_set1_epi64x(-1)))
	#define whodun_vec_compLtU_imp(opA, opB) (whodun_vectorCompareLtU((opA), (opB)))
	#define whodun_vec_compGtU_imp(opA, opB) (whodun_vectorCompareGtU((opA), (opB)))
	#define whodun_vec_compLteU_imp(opA, opB) (whodun_vectorCompareLteU((opA), (opB)))
	#define whodun_vec_compGteU_imp(opA, opB) (whodun_vectorCompareGteU((opA), (opB)))
	#define whodun_vec_compEqI_imp(opA, opB) (_mm256_cmpeq_epi64((opA), (opB)))
	#define whodun_vec_compNeI_imp(opA, opB) (_mm256_xor_si256(_mm256_cmpeq_epi64((opA), (opB)), _mm256_set1_epi64x(-1)))
	#define whodun_vec_compLtI_imp(opA, opB) (_mm256_cmpgt_epi64((opB), (opA)))
	#define whodun_vec_compGtI_imp(opA, opB) (_mm256_cmpgt_epi64((opA), (opB)))
	#define whodun_vec_compLteI_imp(opA, opB) (_mm256_xor_si256(_mm256_cmpgt_epi64((opA), (opB)), _mm256_set1_epi64x(-1)))
	#define whodun_vec_compGteI_imp(opA, opB) (_mm256_xor_si256(_mm256_cmpgt_epi64((opB), (opA)), _mm256_set1_epi64x(-1)))
	#define whodun_vec_compEqF_imp(opA, opB) (_mm256_castpd_si256(_mm256_cmp_pd((opA), (opB), 0)))
	#define whodun_vec_compNeF_imp(opA, opB) (_mm256_castpd_si256(_mm256_cmp_pd((opA), (opB), 4)))
	#define whodun_vec_compLtF_imp(opA, opB) (_mm256_castpd_si256(_mm256_cmp_pd((opA), (opB), 17)))
	#define whodun_vec_compGtF_imp(opA, opB) (_mm256_castpd_si256(_mm256_cmp_pd((opA), (opB), 30)))
	#define whodun_vec_compLteF_imp(opA, opB) (_mm256_castpd_si256(_mm256_cmp_pd((opA), (opB), 18)))
	#define whodun_vec_compGteF_imp(opA, opB) (_mm256_castpd_si256(_mm256_cmp_pd((opA), (opB), 29)))
	#define whodun_vec_andU_imp(opA, opB) (_mm256_and_si256((opA), (opB)))
	#define whodun_vec_orU_imp(opA, opB) (_mm256_or_si256((opA), (opB)))
	#define whodun_vec_xorU_imp(opA, opB) (_mm256_xor_si256((opA), (opB)))
	#define whodun_vec_notU_imp(opA) (_mm256_xor_si256((opA), _mm256_set1_epi64x(-1)))
	#define whodun_vec_lshU_imp(opA, opB) (_mm256_sllv_epi64((opA), (opB)))
	#define whodun_vec_rshU_imp(opA, opB) (_mm256_srlv_epi64((opA), (opB)))
	#define whodun_vec_rshI_imp(opA, opB) (whodun_vectorRshI((opA), (opB)))
	#define whodun_vec_addU_imp(opA, opB) (_mm256_add_epi64((opA), (opB)))
	#define whodun_vec_addI_imp(opA, opB) (_mm256_add_epi64((opA), (opB)))
	#define whodun_vec_addF_imp(opA, opB) (_mm256_add_pd((opA), (opB)))
	#define whodun_vec_addP_imp(opA, opB) (_mm256_add_epi64((opA), (opB)))
	#define whodun_vec_subU_imp(opA, opB) (_mm256_sub_epi64((opA), (opB)))
	#define whodun_vec_subI_imp(opA, opB) (_mm256_sub_epi64((opA), (opB)))
	#define whodun_vec_subF_imp(opA, opB) (_mm256_sub_pd((opA), (opB)))
	#define whodun_vec_negI_imp(opA) (_mm256_sub_epi64(_mm256_setzero_si256(), (opA)))
	#define whodun_vec_negF_imp(opA) (_mm256_sub_pd(_mm256_setzero_pd(), (opA)))
	#define whodun_vec_mulU_imp(opA, opB) (whodun_vectorMulU((opA), (opB)))
	#define whodun_vec_mulI_imp(opA, opB) (whodun_vectorMulI((opA), (opB)))
	#define whodun_vec_mulF_imp(opA, opB) (_mm256_mul_pd((opA), (opB)))
	#define whodun_vec_divU_imp(opA, opB) (whodun_vectorDivU((opA), (opB)))
	#define whodun_vec_divI_imp(opA, opB) (whodun_vectorDivU((opA), (opB)))
	#define whodun_vec_divF_imp(opA, opB) (_mm256_div_pd((opA), (opB)))
	#define whodun_vec_modU_imp(opA, opB) (whodun_vectorModU((opA), (opB)))
	#define whodun_vec_modI_imp(opA, opB) (whodun_vectorModI((opA), (opB)))
	#define whodun_vec_maxU_imp(opA, opB) (whodun_vectorMaxU((opA), (opB)))
	#define whodun_vec_maxI_imp(opA, opB) (whodun_vectorMaxI((opA), (opB)))
	#define whodun_vec_maxF_imp(opA, opB) (whodun_vectorMaxF((opA), (opB)))
	#define whodun_vec_minU_imp(opA, opB) (whodun_vectorMinU((opA), (opB)))
	#define whodun_vec_minI_imp(opA, opB) (whodun_vectorMinI((opA), (opB)))
	#define whodun_vec_minF_imp(opA, opB) (whodun_vectorMinF((opA), (opB)))
	#define whodun_vec_convertI2F_imp(opA) (whodun_vectorConvertI2F(opA))
	#define whodun_vec_convertF2I_imp(opA) (whodun_vectorConvertF2I(opA))
	#define whodun_vec_handU_imp(opA) (whodun_vectorHandU(opA))
	#define whodun_vec_horU_imp(opA) (whodun_vectorHorU(opA))
	#define whodun_vec_hxorU_imp(opA) (whodun_vectorHxorU(opA))
	#define whodun_vec_haddU_imp(opA) (whodun_vectorHaddU(opA))
	#define whodun_vec_haddI_imp(opA) (whodun_vectorHaddI(opA))
	#define whodun_vec_haddF_imp(opA) (whodun_vectorHaddF(opA))
	#define whodun_vec_hmulU_imp(opA) (whodun_vectorHmulU(opA))
	#define whodun_vec_hmulI_imp(opA) (whodun_vectorHmulI(opA))
	#define whodun_vec_hmulF_imp(opA) (whodun_vectorHmulF(opA))
	#define whodun_vec_hmaxU_imp(opA) (whodun_vectorHmaxU(opA))
	#define whodun_vec_hmaxI_imp(opA) (whodun_vectorHmaxI(opA))
	#define whodun_vec_hmaxF_imp(opA) (whodun_vectorHmaxF(opA))
	#define whodun_vec_hminU_imp(opA) (whodun_vectorHminU(opA))
	#define whodun_vec_hminI_imp(opA) (whodun_vectorHminI(opA))
	#define whodun_vec_hminF_imp(opA) (whodun_vectorHminF(opA))
	#define WHODUN_VEC_LOOP_UNROLL_IMP(lvar, lcode) \
		{\
			lvar = 0;\
			{ lcode }\
			lvar = 1;\
			{ lcode }\
			lvar = 2;\
			{ lcode }\
			lvar = 3;\
			{ lcode }\
		}
#else
	#define whodun_vec_loadU_imp(fromP) (_mm_loadu_si128((__m128i*)(fromP)))
	#define whodun_vec_storeU_imp(toP, toV) (_mm_storeu_si128((__m128i*)(toP), (toV)))
	#define whodun_vec_loadI_imp(fromP) (_mm_loadu_si128((__m128i*)(fromP)))
	#define whodun_vec_storeI_imp(toP, toV) (_mm_storeu_si128((__m128i*)(toP), (toV)))
	#define whodun_vec_loadF_imp(fromP) (_mm_loadu_pd(fromP))
	#define whodun_vec_storeF_imp(toP, toV) (_mm_storeu_pd((toP), (toV)))
	#define whodun_vec_loadP_imp(fromP) (_mm_loadu_si128((__m128i*)(fromP)))
	#define whodun_vec_storeP_imp(toP, toV) (_mm_storeu_si128((__m128i*)(toP), (toV)))
	#define whodun_vec_loadB_imp(fromP) (whodun_vectorLoadB(fromP))
	#define whodun_vec_storeB_imp(toP, toV) (whodun_vectorStoreB((toP), (toV)))
	#define whodun_vec_gatherU_imp(fromA, atInds) (whodun_vectorGatherU((fromA), (atInds)))
	#define whodun_vec_gatherI_imp(fromA, atInds) (whodun_vectorGatherI((fromA), (atInds)))
	#define whodun_vec_gatherF_imp(fromA, atInds) (whodun_vectorGatherF((fromA), (atInds)))
	#define whodun_vec_gatherB_imp(fromA, atInds) (whodun_vectorGatherB((fromA), (atInds)))
	#define whodun_vec_scatterU_imp(toA, atInds, toV) (whodun_vectorScatterU((toA), (atInds), (toV)))
	#define whodun_vec_scatterI_imp(toA, atInds, toV) (whodun_vectorScatterI((toA), (atInds), (toV)))
	#define whodun_vec_scatterF_imp(toA, atInds, toV) (whodun_vectorScatterF((toA), (atInds), (toV)))
	#define whodun_vec_scatterB_imp(toA, atInds, toV) (whodun_vectorScatterB((toA), (atInds), (toV)))
	#define whodun_vec_gatherPU_imp(fromA) (whodun_vectorAddrGatherU(fromA))
	#define whodun_vec_gatherPI_imp(fromA) (whodun_vectorAddrGatherI(fromA))
	#define whodun_vec_gatherPF_imp(fromA) (whodun_vectorAddrGatherF(fromA))
	#define whodun_vec_gatherPB_imp(fromA) (whodun_vectorAddrGatherB(fromA))
	#define whodun_vec_scatterPU_imp(toA, toV) (whodun_vectorAddrScatterU((toA), (toV)))
	#define whodun_vec_scatterPI_imp(toA, toV) (whodun_vectorAddrScatterI((toA), (toV)))
	#define whodun_vec_scatterPF_imp(toA, toV) (whodun_vectorAddrScatterF((toA), (toV)))
	#define whodun_vec_scatterPB_imp(toA, toV) (whodun_vectorAddrScatterB((toA), (toV)))
	#define whodun_vec_punU2I_imp(fromV) (fromV)
	#define whodun_vec_punU2F_imp(fromV) (_mm_castsi128_pd(fromV))
	#define whodun_vec_punU2P_imp(fromV) (fromV)
	#define whodun_vec_punI2U_imp(fromV) (fromV)
	#define whodun_vec_punI2F_imp(fromV) (_mm_castsi128_pd(fromV))
	#define whodun_vec_punF2U_imp(fromV) (_mm_castpd_si128(fromV))
	#define whodun_vec_punF2I_imp(fromV) (_mm_castpd_si128(fromV))
	#define whodun_vec_punP2U_imp(fromV) (fromV)
	#define whodun_vec_bcU_imp(fromV) (_mm_set1_epi64x(fromV))
	#define whodun_vec_bcI_imp(fromV) (_mm_set1_epi64x(fromV))
	#define whodun_vec_bcF_imp(fromV) (_mm_set1_pd(fromV))
	#define whodun_vec_bcP_imp(fromV) (_mm_set1_epi64x((whodun_UInt)(fromV)))
	#define whodun_vec_ind_imp (_mm_set_epi64x(1,0))
	#define whodun_vec_compEqU_imp(opA, opB) (whodun_vectorCompareEqU((opA), (opB)))
	#define whodun_vec_compNeU_imp(opA, opB) (whodun_vectorCompareNeU((opA), (opB)))
	#define whodun_vec_compLtU_imp(opA, opB) (whodun_vectorCompareLtU((opA), (opB)))
	#define whodun_vec_compGtU_imp(opA, opB) (whodun_vectorCompareGtU((opA), (opB)))
	#define whodun_vec_compLteU_imp(opA, opB) (whodun_vectorCompareLteU((opA), (opB)))
	#define whodun_vec_compGteU_imp(opA, opB) (whodun_vectorCompareGteU((opA), (opB)))
	#define whodun_vec_compEqI_imp(opA, opB) (whodun_vectorCompareEqI((opA), (opB)))
	#define whodun_vec_compNeI_imp(opA, opB) (whodun_vectorCompareNeI((opA), (opB)))
	#define whodun_vec_compLtI_imp(opA, opB) (whodun_vectorCompareLtI((opA), (opB)))
	#define whodun_vec_compGtI_imp(opA, opB) (whodun_vectorCompareGtI((opA), (opB)))
	#define whodun_vec_compLteI_imp(opA, opB) (whodun_vectorCompareLteI((opA), (opB)))
	#define whodun_vec_compGteI_imp(opA, opB) (whodun_vectorCompareGteI((opA), (opB)))
	#define whodun_vec_compEqF_imp(opA, opB) (_mm_castpd_si128(_mm_cmpeq_pd((opA), (opB))))
	#define whodun_vec_compNeF_imp(opA, opB) (_mm_castpd_si128(_mm_cmpneq_pd((opA), (opB))))
	#define whodun_vec_compLtF_imp(opA, opB) (_mm_castpd_si128(_mm_cmplt_pd((opA), (opB))))
	#define whodun_vec_compGtF_imp(opA, opB) (_mm_castpd_si128(_mm_cmpgt_pd((opA), (opB))))
	#define whodun_vec_compLteF_imp(opA, opB) (_mm_castpd_si128(_mm_cmple_pd((opA), (opB))))
	#define whodun_vec_compGteF_imp(opA, opB) (_mm_castpd_si128(_mm_cmpge_pd((opA), (opB))))
	#define whodun_vec_andU_imp(opA, opB) (_mm_and_si128((opA), (opB)))
	#define whodun_vec_orU_imp(opA, opB) (_mm_or_si128((opA), (opB)))
	#define whodun_vec_xorU_imp(opA, opB) (_mm_xor_si128((opA), (opB)))
	#define whodun_vec_notU_imp(opA) (_mm_xor_si128((opA), _mm_cmpeq_epi32(_mm_setzero_si128(),_mm_setzero_si128())))
	#define whodun_vec_lshU_imp(opA, opB) (whodun_vectorLshU((opA), (opB)))
	#define whodun_vec_rshU_imp(opA, opB) (whodun_vectorRshU((opA), (opB)))
	#define whodun_vec_rshI_imp(opA, opB) (whodun_vectorRshI((opA), (opB)))
	#define whodun_vec_addU_imp(opA, opB) (_mm_add_epi64((opA), (opB)))
	#define whodun_vec_addI_imp(opA, opB) (_mm_add_epi64((opA), (opB)))
	#define whodun_vec_addF_imp(opA, opB) (_mm_add_pd((opA), (opB)))
	#define whodun_vec_addP_imp(opA, opB) (_mm_add_epi64((opA), (opB)))
	#define whodun_vec_subU_imp(opA, opB) (_mm_sub_epi64((opA), (opB)))
	#define whodun_vec_subI_imp(opA, opB) (_mm_sub_epi64((opA), (opB)))
	#define whodun_vec_subF_imp(opA, opB) (_mm_sub_pd((opA), (opB)))
	#define whodun_vec_negI_imp(opA) (_mm_sub_epi64(_mm_setzero_si128(), (opA)))
	#define whodun_vec_negF_imp(opA) (_mm_sub_pd(_mm_setzero_pd(), (opA)))
	#define whodun_vec_mulU_imp(opA, opB) (whodun_vectorMulU((opA), (opB)))
	#define whodun_vec_mulI_imp(opA, opB) (whodun_vectorMulI((opA), (opB)))
	#define whodun_vec_mulF_imp(opA, opB) (_mm_mul_pd((opA), (opB)))
	#define whodun_vec_divU_imp(opA, opB) (whodun_vectorDivU((opA), (opB)))
	#define whodun_vec_divI_imp(opA, opB) (whodun_vectorDivU((opA), (opB)))
	#define whodun_vec_divF_imp(opA, opB) (_mm_div_pd((opA), (opB)))
	#define whodun_vec_modU_imp(opA, opB) (whodun_vectorModU((opA), (opB)))
	#define whodun_vec_modI_imp(opA, opB) (whodun_vectorModI((opA), (opB)))
	#define whodun_vec_maxU_imp(opA, opB) (whodun_vectorMaxU((opA), (opB)))
	#define whodun_vec_maxI_imp(opA, opB) (whodun_vectorMaxI((opA), (opB)))
	#define whodun_vec_maxF_imp(opA, opB) (whodun_vectorMaxF((opA), (opB)))
	#define whodun_vec_minU_imp(opA, opB) (whodun_vectorMinU((opA), (opB)))
	#define whodun_vec_minI_imp(opA, opB) (whodun_vectorMinI((opA), (opB)))
	#define whodun_vec_minF_imp(opA, opB) (whodun_vectorMinF((opA), (opB)))
	#define whodun_vec_convertI2F_imp(opA) (whodun_vectorConvertI2F(opA))
	#define whodun_vec_convertF2I_imp(opA) (whodun_vectorConvertF2I(opA))
	#define whodun_vec_handU_imp(opA) (whodun_vectorHandU(opA))
	#define whodun_vec_horU_imp(opA) (whodun_vectorHorU(opA))
	#define whodun_vec_hxorU_imp(opA) (whodun_vectorHxorU(opA))
	#define whodun_vec_haddU_imp(opA) (whodun_vectorHaddU(opA))
	#define whodun_vec_haddI_imp(opA) (whodun_vectorHaddI(opA))
	#define whodun_vec_haddF_imp(opA) (whodun_vectorHaddF(opA))
	#define whodun_vec_hmulU_imp(opA) (whodun_vectorHmulU(opA))
	#define whodun_vec_hmulI_imp(opA) (whodun_vectorHmulI(opA))
	#define whodun_vec_hmulF_imp(opA) (whodun_vectorHmulF(opA))
	#define whodun_vec_hmaxU_imp(opA) (whodun_vectorHmaxU(opA))
	#define whodun_vec_hmaxI_imp(opA) (whodun_vectorHmaxI(opA))
	#define whodun_vec_hmaxF_imp(opA) (whodun_vectorHmaxF(opA))
	#define whodun_vec_hminU_imp(opA) (whodun_vectorHminU(opA))
	#define whodun_vec_hminI_imp(opA) (whodun_vectorHminI(opA))
	#define whodun_vec_hminF_imp(opA) (whodun_vectorHminF(opA))
	#define WHODUN_VEC_LOOP_UNROLL_IMP(lvar, lcode) \
		{\
			lvar = 0;\
			{ lcode }\
			lvar = 1;\
			{ lcode }\
		}
#endif

/** @endcond */

/**
 * Load a vector of unsigned ints from a location.
 * @param fromP The place to load from.
 * @return The loaded vector.
 */
#define whodun_vec_loadU(fromP) (whodun_vec_loadU_imp(fromP))

/**
 * Store a vector of unsigned ints to a location.
 * @param toP The place to store to.
 * @param toV The values to set to.
 */
#define whodun_vec_storeU(toP, toV) (whodun_vec_storeU_imp((toP),(toV)))

/**
 * Load a vector of signed ints from a location.
 * @param fromP The place to load from.
 * @return The loaded vector.
 */
#define whodun_vec_loadI(fromP) (whodun_vec_loadI_imp(fromP))

/**
 * Store a vector of signed ints to a location.
 * @param toP The place to store to.
 * @param toV The values to set to.
 */
#define whodun_vec_storeI(toP, toV) (whodun_vec_storeI_imp((toP),(toV)))

/**
 * Load a vector of floats from a location.
 * @param fromP The place to load from.
 * @return The loaded vector.
 */
#define whodun_vec_loadF(fromP) (whodun_vec_loadF_imp(fromP))

/**
 * Store a vector of floats to a location.
 * @param toP The place to store to.
 * @param toV The values to set to.
 */
#define whodun_vec_storeF(toP, toV) (whodun_vec_storeF_imp((toP),(toV)))

/**
 * Load a vector of pointers from a location.
 * @param fromP The place to load from.
 * @return The loaded vector.
 */
#define whodun_vec_loadP(fromP) (whodun_vec_loadP_imp(fromP))

/**
 * Store a vector of pointers to a location.
 * @param toP The place to store to.
 * @param toV The values to set to.
 */
#define whodun_vec_storeP(toP, toV) (whodun_vec_storeP_imp((toP),(toV)))

/**
 * Load a vector of bytes from a location.
 * @param fromP The place to load from.
 * @return The loaded vector.
 */
#define whodun_vec_loadB(fromP) (whodun_vec_loadB_imp(fromP))

/**
 * Store a vector of bytes to a location.
 * @param toP The place to store to.
 * @param toV The values to set to.
 */
#define whodun_vec_storeB(toP, toV) (whodun_vec_storeB_imp((toP), (toV)))

/**
 * Load a vector from indices in an array of unsigned ints.
 * @param fromA The array to load from.
 * @param atInds The indices to load.
 * @return The loaded vector.
 */
#define whodun_vec_gatherU(fromA, atInds) (whodun_vec_gatherU_imp((fromA), (atInds)))

/**
 * Load a vector from indices in an array of signed ints.
 * @param fromA The array to load from.
 * @param atInds The indices to load.
 * @return The loaded vector.
 */
#define whodun_vec_gatherI(fromA, atInds) (whodun_vec_gatherI_imp((fromA), (atInds)))

/**
 * Load a vector from indices in an array of floats.
 * @param fromA The array to load from.
 * @param atInds The indices to load.
 * @return The loaded vector.
 */
#define whodun_vec_gatherF(fromA, atInds) (whodun_vec_gatherF_imp((fromA), (atInds)))

/**
 * Load a vector from indices in an array of bytes.
 * @param fromA The array to load from.
 * @param atInds The indices to load.
 * @return The loaded vector.
 */
#define whodun_vec_gatherB(fromA, atInds) (whodun_vec_gatherB_imp((fromA), (atInds)))

/**
 * Store a vector into indices in an array of unsigned ints.
 * @param toA The array to set into.
 * @param atInds The indices to set.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterU(toA, atInds, toV) (whodun_vec_scatterU_imp((toA), (atInds), (toV)))

/**
 * Store a vector into indices in an array of signed ints.
 * @param toA The array to set into.
 * @param atInds The indices to set.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterI(toA, atInds, toV) (whodun_vec_scatterI_imp((toA), (atInds), (toV)))

/**
 * Store a vector into indices in an array of floats.
 * @param toA The array to set into.
 * @param atInds The indices to set.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterF(toA, atInds, toV) (whodun_vec_scatterF_imp((toA), (atInds), (toV)))

/**
 * Store a vector into indices in an array of bytes.
 * @param toA The array to set into.
 * @param atInds The indices to set.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterB(toA, atInds, toV) (whodun_vec_scatterB_imp((toA), (atInds), (toV)))

/**
 * Load a vector from addresses to unsigned ints.
 * @param fromA The addresses to load from.
 * @return The loaded vector.
 */
#define whodun_vec_gatherPU(fromA) (whodun_vec_gatherPU_imp(fromA))

/**
 * Load a vector from addresses to signed ints.
 * @param fromA The addresses to load from.
 * @return The loaded vector.
 */
#define whodun_vec_gatherPI(fromA) (whodun_vec_gatherPI_imp(fromA))

/**
 * Load a vector from addresses to floats.
 * @param fromA The addresses to load from.
 * @return The loaded vector.
 */
#define whodun_vec_gatherPF(fromA) (whodun_vec_gatherPF_imp(fromA))

/**
 * Load a vector from addresses to bytes.
 * @param fromA The addresses to load from.
 * @return The loaded vector.
 */
#define whodun_vec_gatherPB(fromA) (whodun_vec_gatherPB_imp(fromA))

/**
 * Store a vector into addresses to unsigned ints.
 * @param toA The addresses to set into.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterPU(toA, toV) (whodun_vec_scatterPU_imp((toA), (toV)))

/**
 * Store a vector into addresses to signed ints.
 * @param toA The addresses to set into.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterPI(toA, toV) (whodun_vec_scatterPI_imp((toA), (toV)))

/**
 * Store a vector into addresses to floats.
 * @param toA The addresses to set into.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterPF(toA, toV) (whodun_vec_scatterPF_imp((toA), (toV)))

/**
 * Store a vector into addresses to bytes.
 * @param toA The addresses to set into.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterPB(toA, toV) (whodun_vec_scatterPB_imp((toA), (toV)))

/**
 * Pun an unsigned vector to signed.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punU2I(fromV) (whodun_vec_punU2I_imp(fromV))

/**
 * Pun an unsigned vector to float.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punU2F(fromV) (whodun_vec_punU2F_imp(fromV))

/**
 * Pun an unsigned vector to pointer.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punU2P(fromV) (whodun_vec_punU2P_imp(fromV))

/**
 * Pun a signed vector to unsigned.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punI2U(fromV) (whodun_vec_punI2U_imp(fromV))

/**
 * Pun a signed vector to float.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punI2F(fromV) (whodun_vec_punI2F_imp(fromV))

/**
 * Pun a float vector to unsigned ints.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punF2U(fromV) (whodun_vec_punF2U_imp(fromV))

/**
 * Pun a float vector to signed ints.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punF2I(fromV) (whodun_vec_punF2I_imp(fromV))

/**
 * Pun a pointer to unsigned vector.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punP2U(fromV) (whodun_vec_punP2U_imp(fromV))

/**
 * Broadcast a value to all lanes of a vector.
 * @param fromV The value to broadcast.
 * @return The new vector.
 */
#define whodun_vec_bcU(fromV) (whodun_vec_bcU_imp(fromV))

/**
 * Broadcast a value to all lanes of a vector.
 * @param fromV The value to broadcast.
 * @return The new vector.
 */
#define whodun_vec_bcI(fromV) (whodun_vec_bcI_imp(fromV))

/**
 * Broadcast a value to all lanes of a vector.
 * @param fromV The value to broadcast.
 * @return The new vector.
 */
#define whodun_vec_bcF(fromV) (whodun_vec_bcF_imp(fromV))

/**
 * Broadcast a value to all lanes of a vector.
 * @param fromV The value to broadcast.
 * @return The new vector.
 */
#define whodun_vec_bcP(fromV) (whodun_vec_bcP_imp(fromV))

/**
 * Set lanes of a vector to their index.
 * @return The new vector.
 */
#define whodun_vec_ind (whodun_vec_ind_imp)

/**
 * Compare vectors of unsigned integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compEqU(opA, opB) (whodun_vec_compEqU_imp((opA), (opB)))

/**
 * Compare vectors of unsigned integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compNeU(opA, opB) (whodun_vec_compNeU_imp((opA), (opB)))

/**
 * Compare vectors of unsigned integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compLtU(opA, opB) (whodun_vec_compLtU_imp((opA), (opB)))

/**
 * Compare vectors of unsigned integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compGtU(opA, opB) (whodun_vec_compGtU_imp((opA), (opB)))

/**
 * Compare vectors of unsigned integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compLteU(opA, opB) (whodun_vec_compLteU_imp((opA), (opB)))

/**
 * Compare vectors of unsigned integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compGteU(opA, opB) (whodun_vec_compGteU_imp((opA), (opB)))

/**
 * Compare vectors of signed integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compEqI(opA, opB) (whodun_vec_compEqI_imp((opA), (opB)))

/**
 * Compare vectors of signed integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compNeI(opA, opB) (whodun_vec_compNeI_imp((opA), (opB)))

/**
 * Compare vectors of signed integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compLtI(opA, opB) (whodun_vec_compLtI_imp((opA), (opB)))

/**
 * Compare vectors of signed integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compGtI(opA, opB) (whodun_vec_compGtI_imp((opA), (opB)))

/**
 * Compare vectors of signed integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compLteI(opA, opB) (whodun_vec_compLteI_imp((opA), (opB)))

/**
 * Compare vectors of signed integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compGteI(opA, opB) (whodun_vec_compGteI_imp((opA), (opB)))

/**
 * Compare vectors of floats
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compEqF(opA, opB) (whodun_vec_compEqF_imp((opA), (opB)))

/**
 * Compare vectors of floats
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compNeF(opA, opB) (whodun_vec_compNeF_imp((opA), (opB)))

/**
 * Compare vectors of floats
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compLtF(opA, opB) (whodun_vec_compLtF_imp((opA), (opB)))

/**
 * Compare vectors of floats
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compGtF(opA, opB) (whodun_vec_compGtF_imp((opA), (opB)))

/**
 * Compare vectors of floats
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compLteF(opA, opB) (whodun_vec_compLteF_imp((opA), (opB)))

/**
 * Compare vectors of floats
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compGteF(opA, opB) (whodun_vec_compGteF_imp((opA), (opB)))

/**
 * Bitwise and two vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_andU(opA, opB) (whodun_vec_andU_imp((opA), (opB)))

/**
 * Bitwise or two vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_orU(opA, opB) (whodun_vec_orU_imp((opA), (opB)))

/**
 * Bitwise xor two vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_xorU(opA, opB) (whodun_vec_xorU_imp((opA), (opB)))

/**
 * Bitwise not vectors of unsigned integers.
 * @param opA The first value.
 * @return The result.
 */
#define whodun_vec_notU(opA) (whodun_vec_notU_imp(opA))

/**
 * Left shift.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_lshU(opA, opB) (whodun_vec_lshU_imp((opA), (opB)))

/**
 * Unsigned right shift.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_rshU(opA, opB) (whodun_vec_rshU_imp((opA), (opB)))

/**
 * Signed right shift.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_rshI(opA, opB) (whodun_vec_rshI_imp((opA), (opB)))

/**
 * Add vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_addU(opA, opB) (whodun_vec_addU_imp((opA), (opB)))

/**
 * Add vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_addI(opA, opB) (whodun_vec_addI_imp((opA), (opB)))

/**
 * Add vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_addF(opA, opB) (whodun_vec_addF_imp((opA), (opB)))

/**
 * Advance vectors of pointers.
 * @param opA The pointers.
 * @param opB The offsets (in bytes).
 * @return The result.
 */
#define whodun_vec_addP(opA, opB) (whodun_vec_addP_imp((opA), (opB)))

/**
 * Subtract vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_subU(opA, opB) (whodun_vec_subU_imp((opA), (opB)))

/**
 * Subtract vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_subI(opA, opB) (whodun_vec_subI_imp((opA), (opB)))

/**
 * Subtract vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_subF(opA, opB) (whodun_vec_subF_imp((opA), (opB)))

/**
 * Negate vectors of signed integers.
 * @param opA The first value.
 * @return The result.
 */
#define whodun_vec_negI(opA) (whodun_vec_negI_imp(opA))

/**
 * Negate vectors of floats.
 * @param opA The first value.
 * @return The result.
 */
#define whodun_vec_negF(opA) (whodun_vec_negF_imp(opA))

/**
 * Multiply vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_mulU(opA, opB) (whodun_vec_mulU_imp((opA), (opB)))

/**
 * Multiply vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_mulI(opA, opB) (whodun_vec_mulI_imp((opA), (opB)))

/**
 * Multiply vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_mulF(opA, opB) (whodun_vec_mulF_imp((opA), (opB)))

/**
 * Divide vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_divU(opA, opB) (whodun_vec_divU_imp((opA), (opB)))

/**
 * Divide vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_divI(opA, opB) (whodun_vec_divI_imp((opA), (opB)))

/**
 * Divide vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_divF(opA, opB) (whodun_vec_divF_imp((opA), (opB)))

/**
 * Divide and take remainter of vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_modU(opA, opB) (whodun_vec_modU_imp((opA), (opB)))

/**
 * Divide and take remainter of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_modI(opA, opB) (whodun_vec_modI_imp((opA), (opB)))

/**
 * Take maximum of vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_maxU(opA, opB) (whodun_vec_maxU_imp((opA), (opB)))

/**
 * Take maximum of vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_maxI(opA, opB) (whodun_vec_maxI_imp((opA), (opB)))

/**
 * Take maximum of vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_maxF(opA, opB) (whodun_vec_maxF_imp((opA), (opB)))

/**
 * Take minimum of vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_minU(opA, opB) (whodun_vec_minU_imp((opA), (opB)))

/**
 * Take minimum of vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_minI(opA, opB) (whodun_vec_minI_imp((opA), (opB)))

/**
 * Take minimum of vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_minF(opA, opB) (whodun_vec_minF_imp((opA), (opB)))

/**
 * Convert a signed vector to float.
 * @param opA The value to convert.
 * @return The punned value.
 */
#define whodun_vec_convertI2F(opA) (whodun_vec_convertI2F_imp(opA))

/**
 * Convert a float to signed vector.
 * @param opA The value to convert.
 * @return The punned value.
 */
#define whodun_vec_convertF2I(opA) (whodun_vec_convertF2I_imp(opA))

/**
 * And all lanes of a vector.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_handU(opA) (whodun_vec_handU_imp(opA))

/**
 * Or all lanes of a vector.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_horU(opA) (whodun_vec_horU_imp(opA))

/**
 * Xor all lanes of a vector.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hxorU(opA) (whodun_vec_hxorU_imp(opA))

/**
 * Add all lanes of a vector of unsigned integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_haddU(opA) (whodun_vec_haddU_imp(opA))

/**
 * Add all lanes of a vector of signed integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_haddI(opA) (whodun_vec_haddI_imp(opA))

/**
 * Add all lanes of a vector of floats.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_haddF(opA) (whodun_vec_haddF_imp(opA))

/**
 * Multiply all lanes of a vector of unsigned integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hmulU(opA) (whodun_vec_hmulU_imp(opA))

/**
 * Multiply all lanes of a vector of signed integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hmulI(opA) (whodun_vec_hmulI_imp(opA))

/**
 * Multiply all lanes of a vector of floats.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hmulF(opA) (whodun_vec_hmulF_imp(opA))

/**
 * Take the maximum across all lanes of a vector of unsigned integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hmaxU(opA) (whodun_vec_hmaxU_imp(opA))

/**
 * Take the maximum across all lanes of a vector of signed integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hmaxI(opA) (whodun_vec_hmaxI_imp(opA))

/**
 * Take the maximum across all lanes of a vector of floats.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hmaxF(opA) (whodun_vec_hmaxF_imp(opA))

/**
 * Take the minimum across all lanes of a vector of unsigned integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hminU(opA) (whodun_vec_hminU_imp(opA))

/**
 * Take the minimum across all lanes of a vector of signed integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hminI(opA) (whodun_vec_hminI_imp(opA))

/**
 * Take the minimum across all lanes of a vector of floats.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hminF(opA) (whodun_vec_hminF_imp(opA))

/**
 * Unroll a loop along a vector.
 * @param lvar The variable for the iteration (some flavor of int).
 * @param lcode The code to repeat.
 */
#define WHODUN_VEC_LOOP_UNROLL(lvar, lcode) WHODUN_VEC_LOOP_UNROLL_IMP(lvar, lcode)

#endif

