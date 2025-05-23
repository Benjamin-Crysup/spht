#ifndef WHODUN_CPUVECX_H
#define WHODUN_CPUVECX_H 1

/**
 * @file
 * @brief Higher-order vector ops.
 */

#include "whodun/cpu.h"
#include "whodun/defs.h"
#include "whodun/cpuvec.h"

/**
 * Load a vector of unsigned ints from a structure.
 * @param type The type being loaded from.
 * @param vname The name of the variable being targeted.
 * @param fromP The places to load from.
 * @return The loaded vector.
 */
#define whodun_vec_structGatherPU(type, vname, fromP) (whodun_vec_gatherPU(whodun_vec_addP((fromP), whodun_vec_bcU(offsetof(type, vname)))))

/**
 * Store a vector of unsigned ints into a structure.
 * @param type The type being stored to.
 * @param vname The name of the variable being targeted.
 * @param toP The places to store to.
 * @param toV The values to set to.
 */
#define whodun_vec_structScatterPU(type, vname, toP, toV) (whodun_vec_scatterPU(whodun_vec_addP((toP), whodun_vec_bcU(offsetof(type, vname))), (toV)));

/**
 * Load a vector of signed ints from a structure.
 * @param type The type being loaded from.
 * @param vname The name of the variable being targeted.
 * @param fromP The places to load from.
 * @return The loaded vector.
 */
#define whodun_vec_structGatherPI(type, vname, fromP) (whodun_vec_gatherPI(whodun_vec_addP((fromP), whodun_vec_bcU(offsetof(type, vname)))))

/**
 * Store a vector of signed ints into a structure.
 * @param type The type being stored to.
 * @param vname The name of the variable being targeted.
 * @param toP The places to store to.
 * @param toV The values to set to.
 */
#define whodun_vec_structScatterPI(type, vname, toP, toV) (whodun_vec_scatterPI(whodun_vec_addP((toP), whodun_vec_bcU(offsetof(type, vname))), (toV)));

/**
 * Load a vector of floats from a structure.
 * @param type The type being loaded from.
 * @param vname The name of the variable being targeted.
 * @param fromP The places to load from.
 * @return The loaded vector.
 */
#define whodun_vec_structGatherPF(type, vname, fromP) (whodun_vec_gatherPF(whodun_vec_addP((fromP), whodun_vec_bcU(offsetof(type, vname)))))

/**
 * Store a vector of floats into a structure.
 * @param type The type being stored to.
 * @param vname The name of the variable being targeted.
 * @param toP The places to store to.
 * @param toV The values to set to.
 */
#define whodun_vec_structScatterPF(type, vname, toP, toV) (whodun_vec_scatterPF(whodun_vec_addP((toP), whodun_vec_bcU(offsetof(type, vname))), (toV)));

/**
 * Select a value by a case mask, or zero if no case mask. The m4 preprocessor is Turing complete, why not C's?
 * @param c0 The condition mask for the first value.
 * @param v0 The first value.
 */
#define whodun_vec_switch1U(c0, v0) (whodun_vec_andU((c0), (v0)))

/**
 * Select a value by a case mask, or zero if no case mask. The m4 preprocessor is Turing complete, why not C's?
 * @param c0 The condition mask for the first value.
 * @param v0 The first value.
 */
#define whodun_vec_switch1I(c0, v0) (whodun_vec_punU2I(whodun_vec_andU((c0), whodun_vec_punI2U(v0))))

/**
 * Select a value by a case mask, or zero if no case mask. The m4 preprocessor is Turing complete, why not C's?
 * @param c0 The condition mask for the first value.
 * @param v0 The first value.
 */
#define whodun_vec_switch1F(c0, v0) (whodun_vec_punU2F(whodun_vec_andU((c0), whodun_vec_punF2U(v0))))

/**
 * Select a value by a case mask, or zero if no case mask. The m4 preprocessor is Turing complete, why not C's?
 * @param c0 The condition mask for the first value.
 * @param v0 The first value.
 */
#define whodun_vec_switch1P(c0, v0) (whodun_vec_punU2P(whodun_vec_andU((c0), whodun_vec_punP2U(v0))))

/**
 * Select a value by a case mask, or zero if no case mask. The m4 preprocessor is Turing complete, why not C's?
 * @param c0 The condition mask for the first value.
 * @param v0 The first value.
 * @param c1 The condition mask for the second value.
 * @param v1 The second value.
 */
#define whodun_vec_switch2U(c0, v0, c1, v1) (whodun_vec_orU(whodun_vec_andU((c0), (v0)), whodun_vec_andU((c1), (v1))))

/**
 * Select a value by a case mask, or zero if no case mask. The m4 preprocessor is Turing complete, why not C's?
 * @param c0 The condition mask for the first value.
 * @param v0 The first value.
 * @param c1 The condition mask for the second value.
 * @param v1 The second value.
 */
#define whodun_vec_switch2I(c0, v0, c1, v1) (whodun_vec_punU2I(whodun_vec_orU(whodun_vec_andU((c0), whodun_vec_punI2U(v0)), whodun_vec_andU((c1), whodun_vec_punI2U(v1)))))

/**
 * Select a value by a case mask, or zero if no case mask. The m4 preprocessor is Turing complete, why not C's?
 * @param c0 The condition mask for the first value.
 * @param v0 The first value.
 * @param c1 The condition mask for the second value.
 * @param v1 The second value.
 */
#define whodun_vec_switch2F(c0, v0, c1, v1) (whodun_vec_punU2F(whodun_vec_orU(whodun_vec_andU((c0), whodun_vec_punF2U(v0)), whodun_vec_andU((c1), whodun_vec_punF2U(v1)))))

/**
 * Select a value by a case mask, or zero if no case mask. The m4 preprocessor is Turing complete, why not C's?
 * @param c0 The condition mask for the first value.
 * @param v0 The first value.
 * @param c1 The condition mask for the second value.
 * @param v1 The second value.
 */
#define whodun_vec_switch2P(c0, v0, c1, v1) (whodun_vec_punU2P(whodun_vec_orU(whodun_vec_andU((c0), whodun_vec_punP2U(v0)), whodun_vec_andU((c1), whodun_vec_punP2U(v1)))))

/**
 * Select a value by a case mask, or zero if no case mask. The m4 preprocessor is Turing complete, why not C's?
 * @param c0 The condition mask for the first value.
 * @param v0 The first value.
 * @param c1 The condition mask for the second value.
 * @param v1 The second value.
 * @param c2 The condition mask for the third value.
 * @param v2 The third value.
 */
#define whodun_vec_switch3U(c0, v0, c1, v1, c2, v2) (whodun_vec_orU(whodun_vec_orU(whodun_vec_andU((c0), (v0)), whodun_vec_andU((c1), (v1))), whodun_vec_andU((c2), (v2))))

/**
 * Select a value by a case mask, or zero if no case mask. The m4 preprocessor is Turing complete, why not C's?
 * @param c0 The condition mask for the first value.
 * @param v0 The first value.
 * @param c1 The condition mask for the second value.
 * @param v1 The second value.
 * @param c2 The condition mask for the third value.
 * @param v2 The third value.
 */
#define whodun_vec_switch3I(c0, v0, c1, v1, c2, v2) (whodun_vec_punU2I(whodun_vec_orU(whodun_vec_orU(whodun_vec_andU((c0), whodun_vec_punI2U(v0)), whodun_vec_andU((c1), whodun_vec_punI2U(v1))), whodun_vec_andU((c2), whodun_vec_punI2U(v2)))))

/**
 * Select a value by a case mask, or zero if no case mask. The m4 preprocessor is Turing complete, why not C's?
 * @param c0 The condition mask for the first value.
 * @param v0 The first value.
 * @param c1 The condition mask for the second value.
 * @param v1 The second value.
 * @param c2 The condition mask for the third value.
 * @param v2 The third value.
 */
#define whodun_vec_switch3F(c0, v0, c1, v1, c2, v2) (whodun_vec_punU2F(whodun_vec_orU(whodun_vec_orU(whodun_vec_andU((c0), whodun_vec_punF2U(v0)), whodun_vec_andU((c1), whodun_vec_punF2U(v1))), whodun_vec_andU((c2), whodun_vec_punF2U(v2)))))

/**
 * Select a value by a case mask, or zero if no case mask. The m4 preprocessor is Turing complete, why not C's?
 * @param c0 The condition mask for the first value.
 * @param v0 The first value.
 * @param c1 The condition mask for the second value.
 * @param v1 The second value.
 * @param c2 The condition mask for the third value.
 * @param v2 The third value.
 */
#define whodun_vec_switch3P(c0, v0, c1, v1, c2, v2) (whodun_vec_punU2P(whodun_vec_orU(whodun_vec_orU(whodun_vec_andU((c0), whodun_vec_punP2U(v0)), whodun_vec_andU((c1), whodun_vec_punP2U(v1))), whodun_vec_andU((c2), whodun_vec_punP2U(v2)))))


#endif

