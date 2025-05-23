#include "whodun/stats/math.h"

#include <math.h>

#include "whodun/math.h"
#include "whodun/cpuvec.h"
#include "whodun/cpuvecx.h"

whodun_Float whodun_log1mexp_imp(whodun_Float forVal){
	if(forVal > -0.693){
		return log(-expm1(forVal));
	}
	else{
		return log1p(-exp(forVal));
	}
}

whodun_FloatV whodun_log1mexpV_imp(whodun_FloatV forVal){
#if WHODUN_VECTOR_WIDTH == 1
	return whodun_log1mexp_imp(forVal);
#else
	whodun_UIntV bigP = whodun_vec_compGtF(forVal, whodun_vec_bcF(-0.693));
	whodun_FloatV valBig = whodun_logV(whodun_vec_negF(whodun_expm1V(forVal)));
	whodun_FloatV valLow = whodun_log1pV(whodun_vec_negF(whodun_expV(forVal)));
	return whodun_vec_switch2F(bigP, valBig, whodun_vec_notU(bigP), valLow);
#endif
}

whodun_Float whodun_logSumExp_short_nonempty(whodun_UInt num, whodun_Float* toSum){
	//get the max (don't need to be careful about max here)
		whodun_Float maxV = toSum[0];
		for(whodun_UInt i = 1; i<num; i++){
			maxV = (toSum[i] > maxV) ? toSum[i] : maxV;
		}
	//infinite and NaN short circuit
		if((maxV - maxV) != 0.0){ return maxV; }
	//get the sum
		whodun_Float sumV = 0.0;
		for(whodun_UInt i = 0; i<num; i++){
			sumV += exp(toSum[i] - maxV);
		}
	//mix together
		return maxV + log(sumV);
}

whodun_Float whodun_logSumExp_imp(whodun_UInt num, whodun_Float* toSum){
	//sum over empty is zero
		if(num == 0){ return -1.0 / 0.0; }
	//if large (and vectors meaningfully in play), do log-sum-exp in parallel, then mix at end
#if WHODUN_VECTOR_WIDTH > 1
		if(num > WHODUN_VECTOR_WIDTH){
			whodun_UInt left;
			whodun_Float* next;
			//hunt the maximum
				whodun_FloatV maxV = whodun_vec_loadF(toSum);
				left = num - WHODUN_VECTOR_WIDTH;
				next = toSum + WHODUN_VECTOR_WIDTH;
				while(left >= WHODUN_VECTOR_WIDTH){
					whodun_FloatV altV = whodun_vec_loadF(next);
					whodun_UIntV newWin = whodun_vec_compGtF(altV, maxV);
					maxV = whodun_vec_switch2F(newWin, altV, whodun_vec_notU(newWin), maxV);
					left -= WHODUN_VECTOR_WIDTH;
					next += WHODUN_VECTOR_WIDTH;
				}
				//leave the tail for later
			//note whether the maximum is nan or inf
			//calculate log-sum-exp for each piece
				whodun_FloatV sumV = whodun_expV(whodun_vec_subF(whodun_vec_loadF(toSum), maxV));
				left = num - WHODUN_VECTOR_WIDTH;
				next = toSum + WHODUN_VECTOR_WIDTH;
				while(left >= WHODUN_VECTOR_WIDTH){
					sumV = whodun_vec_addF(sumV, whodun_expV(whodun_vec_subF(whodun_vec_loadF(next), maxV)));
					left -= WHODUN_VECTOR_WIDTH;
					next += WHODUN_VECTOR_WIDTH;
				}
			//fix up the main pieces
				whodun_FloatV mainV = whodun_vec_addF(maxV, whodun_logV(sumV));
				whodun_UIntV maxCanMath = whodun_vec_compEqF(whodun_vec_subF(maxV, maxV), whodun_vec_bcF(0.0));
				mainV = whodun_vec_switch2F(maxCanMath, mainV, whodun_vec_notU(maxCanMath), maxV);
			//do a short sum across the lanes (and any tails)
				whodun_Float mainA[WHODUN_VECTOR_WIDTH + 1];
				whodun_vec_storeF(mainA, mainV);
				mainA[WHODUN_VECTOR_WIDTH] = (left ? whodun_logSumExp_short_nonempty(left, next) : (-1.0/0.0));
				return whodun_logSumExp_short_nonempty(WHODUN_VECTOR_WIDTH+1, mainA);
		}
#endif
	return whodun_logSumExp_short_nonempty(num, toSum);
}

whodun_Float (*whodun_log1mexp)(whodun_Float forVal) = whodun_log1mexp_imp;
whodun_FloatV (*whodun_log1mexpV)(whodun_FloatV forVal) = whodun_log1mexpV_imp;
whodun_Float (*whodun_logSumExp)(whodun_UInt numCalc, whodun_Float* calcFrom) = whodun_logSumExp_imp;


