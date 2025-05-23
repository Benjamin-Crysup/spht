#ifndef WHODUN_INTERNAT_H
#define WHODUN_INTERNAT_H 1

/**
 * @file
 * @brief Internationalization.
 */

#include "whodun/defs.h"
#include "whodun/alloc.h"
#include "whodun/array.h"
#include "whodun/class.h"
#include "whodun/error.h"
#include "whodun/contain.h"

#ifdef __cplusplus
extern "C" {
#endif

/**A map of internationalization data.*/
struct whodun_InternationalMap{
	/**Map from id to index.*/
	struct whodun_Trie indMap;
	/**Where each thing is.*/
	struct whodun_Vector curIndices;
	/**Information on things (including masked things).*/
	struct whodun_Vector allData;
};

/**The marker for a string (pointer to ByteArray).*/
extern void* whodun_internatTypeString;

/**
 * Set up an internationalization map.
 * @param toInit The map to set up.
 * @param useAl The allocator to use.
 * @param err The place to note errors.
 */
extern void (*whodun_internatMapInit)(struct whodun_InternationalMap* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);

/**
 * Get a thing out of an internationalization map.
 * @param map The map to get from.
 * @param intID The id of the thing to get.
 * @param saveType The place to put the type.
 * @param saveVal The place to put the value.
 * @return Whether that id was in the map.
 */
extern whodun_Bool (*whodun_internatMapGet)(struct whodun_InternationalMap* map, struct whodun_ByteArray intID, void** saveType, whodun_UInt* saveVal);

/**
 * Add a thing to an internationalization map.
 * @param map The map to add to.
 * @param intID The id of the thing to add.
 * @param source Where this thing came from.
 * @param type The type of thing this is.
 * @param val The value to associate.
 * @param err The place to note errors.
 */
extern void (*whodun_internatMapAdd)(struct whodun_InternationalMap* map, struct whodun_ByteArray intID, void* source, void* type, whodun_UInt val, struct whodun_ErrorLog* err);

/**
 * Drop all things from a given source from an internationalization map.
 * @param map The map to remove from.
 * @param source The source to remove.
 */
extern void (*whodun_internatMapDrop)(struct whodun_InternationalMap* map, void* source);

/**
 * Tear down an internationalization map.
 * @param toKill The map to tear down.
 */
extern void (*whodun_internatMapFin)(struct whodun_InternationalMap* toKill);

#ifdef __cplusplus
}
#endif

#endif

