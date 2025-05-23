#ifndef WHODUN_MATH_H
#define WHODUN_MATH_H 1

/**
 * @file
 * @brief Basic mathematical functions.
 */

#include "whodun/defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**The ratio of the circumference of a circle to its diameter.*/
#define WHODUN_PI 3.14159265358979
/**Euler's number. The natural growth factor under continuously compounding interest.*/
#define WHODUN_E 2.718281828459045235360287471352
/**The Euler-Mascheroni constant.*/
#define WHODUN_EULERMASCHERONI 0.5772156649015328606065120900824024310421
/**Not-a-number.*/
#define WHODUN_NAN (0.0/0.0)
/**A floating point infinity.*/
#define WHODUN_INF (1.0/0.0)

/**
 * Calculate the inverse error function.
 * @param forVal The value to calculate for.
 * @return The inverse error function.
 */
extern whodun_Float (*whodun_erfinv)(whodun_Float forVal);

/**
 * Compute cos across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_cosV)(whodun_FloatV x);

/**
 * Compute sin across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_sinV)(whodun_FloatV x);

/**
 * Compute tan across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_tanV)(whodun_FloatV x);

/**
 * Compute acos across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_acosV)(whodun_FloatV x);

/**
 * Compute asin across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_asinV)(whodun_FloatV x);

/**
 * Compute atan across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_atanV)(whodun_FloatV x);

/**
 * Compute atan2 across all lanes of a vector.
 * @param y The value.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_atan2V)(whodun_FloatV y, whodun_FloatV x);

/**
 * Compute cosh across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_coshV)(whodun_FloatV x);

/**
 * Compute sinh across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_sinhV)(whodun_FloatV x);

/**
 * Compute tanh across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_tanhV)(whodun_FloatV x);

/**
 * Compute acosh across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_acoshV)(whodun_FloatV x);

/**
 * Compute asinh across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_asinhV)(whodun_FloatV x);

/**
 * Compute atanh across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_atanhV)(whodun_FloatV x);

/**
 * Compute exp across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_expV)(whodun_FloatV x);

/**
 * Compute ln across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_logV)(whodun_FloatV x);

/**
 * Compute pow across all lanes of a vector.
 * @param b The value.
 * @param e The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_powV)(whodun_FloatV b, whodun_FloatV e);

/**
 * Compute sqrt across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_sqrtV)(whodun_FloatV x);

/**
 * Compute erf across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_erfV)(whodun_FloatV x);

/**
 * Compute lgamma across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_lgammaV)(whodun_FloatV x);

/**
 * Compute ceil across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_ceilV)(whodun_FloatV x);

/**
 * Compute floor across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_floorV)(whodun_FloatV x);

/**
 * Compute trunc across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_truncV)(whodun_FloatV x);

/**
 * Compute round across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_roundV)(whodun_FloatV x);

/**
 * Compute expm1 across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_expm1V)(whodun_FloatV x);

/**
 * Compute log1p across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_log1pV)(whodun_FloatV x);

/**
 * Compute erfinv across all lanes of a vector.
 * @param x The value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_erfinvV)(whodun_FloatV x);

#ifdef __cplusplus
}
#endif

#endif
 
