#ifndef WHODUN_CLASS_H
#define WHODUN_CLASS_H 1

/**
 * @file
 * @brief Standard interface stuff for classes.
 */

#include <stddef.h>

#include "whodun/defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**The data layout of the base class.*/
struct whodun_Object{
	/**The v-table for this object.*/
	void* vtable;
};

/**The vtable layout for the Object class.*/
struct whodun_Object_vtable_dec{
	/**The pointer to the parent vtable.*/
	void* parent;
	/**The number of bytes in an instance of this class.*/
	whodun_UInt instanceSize;
	/**The number of bytes in the vtable.*/
	whodun_UInt vtableSize;
	/**
	 * A function to finalize an instance of this class.
	 * @param self The Object instance.
	 */
	void (*finalize)(void* self);
	/**
	 * A function to initialize an instance of this class.
	 * @param self The Object instance.
	 */
	void (*initialize)(void* self);
};

/**
 * Get the vtable for the base Object class.
 * @return The vtable for the base Object class.
 */
extern struct whodun_Object_vtable_dec* (*whodun_Object_vtable)();

/**
 * Test if an Object is an instance of a given class.
 * @param toTest The instance to test.
 * @param vtable The vtable of the class in question.
 * @return Whether toTest is an instance. Null is always an instance.
 */
extern whodun_Bool (*whodun_classIsInstanceOf)(struct whodun_Object* toTest, void* vtable);

/**
 * A function to call for abstract methods that have not been filled in.
 */
extern void (*whodun_classAbstractCrash)();

/**
 * Check the sizes and panic if things have changed.
 * @param vtable The vtable to check.
 * @param instSize The expected size of an instance.
 * @param vtabSize The expected size of the vtable.
 */
extern void (*whodun_classCheckSizes)(void* vtable, whodun_UInt instSize, whodun_UInt vtabSize);

/**
 * Helper function to set a vtable and initialize a thing.
 * @param inst The instance to initialize.
 * @param vtable The vtable.
 * @return inst
 */
extern void* (*whodun_classInitialize)(void* inst, void* vtable);

/**
 * Helper function to finalize a thing.
 * @param inst The instance to finalize.
 * @return inst
 */
extern void (*whodun_classFinalize)(void* inst);

/**
 * Get the address of a variable out of a class instance.
 * @param cnsname The namespace and name of the class in question.
 * @param vname The name of the variable in question.
 * @param inst The instance to get the variable out of.
 * @return The address of the variable in the given instance.
 */
#define WHODUN_CVAR(cnsname, vname, inst) (&(((struct cnsname*)(inst))->vname))

/**
 * Get the relevant method for an instace of the given class.
 * @param cnsname The namespace and name of the class in question.
 * @param mname The name of the method in question.
 * @param inst The instance to get the method out of.
 */
#define WHODUN_CFUN(cnsname, mname, inst) (((struct cnsname ## _vtable_dec*)(((struct whodun_Object*)(inst))->vtable))->mname)

/**
 * Get the vtable of a class.
 * @param cnsname The namespace and name of the class in question.
 * @return The vtable.
 */
#define WHODUN_CVTABLE(cnsname) (cnsname ## _vtable())

/**
 * Initialize an object.
 * @param cnsname The namespace and name of the class in question.
 * @param inst The instance to initialize.
 */
#define WHODUN_CINIT(cnsname, inst) (whodun_classInitialize((inst), WHODUN_CVTABLE(cnsname)))

/**
 * Finalize an object.
 * @param inst The instance to finalize.
 */
#define WHODUN_CFIN(inst) (whodun_classFinalize(inst))

/**
 * Code generator to help in making the vtable retrieval function.
 * The code between this and WHODUN_CVTABLE_FUN_END will be run if the vtable has not yet been initialized.
 * Set entries in a pointer variable called needInit.
 * @param cnsname The namespace and name of the class in question.
 * @param supercns The namespace and name of the super-class.
 */
#define WHODUN_CVTABLE_FUN_BEGIN(cnsname, supercns) \
whodun_Lock cnsname ## _vtable_varLock = WHODUN_LOCK_INIT;\
whodun_UInt cnsname ## _vtable_varHaveInit = 0;\
struct cnsname ## _vtable_dec cnsname ## _vtable_var;\
struct cnsname ## _vtable_dec* cnsname ## _vtable_imp(){\
	if(whodun_atomGet(& cnsname ## _vtable_varHaveInit, & cnsname ## _vtable_varLock) == 0){\
		struct cnsname ## _vtable_dec* needInit = & cnsname ## _vtable_var;\
		struct supercns ## _vtable_dec* super = WHODUN_CVTABLE(supercns);\
		whodun_mutexLock(whodun_GIL);\
		if(whodun_atomGet(& cnsname ## _vtable_varHaveInit, & cnsname ## _vtable_varLock) == 0){\
			whodun_classCheckSizes(super, sizeof(struct supercns), sizeof(struct supercns ## _vtable_dec));\
			memcpy(needInit, super, sizeof(struct supercns ## _vtable_dec));\
			((struct whodun_Object_vtable_dec*)needInit)->parent = super;

/**
 * Companion code generator to help in making the vtable retrieval function.
 * @param cnsname The namespace and name of the class in question.
 */
#define WHODUN_CVTABLE_FUN_END(cnsname) \
			((struct whodun_Object_vtable_dec*)needInit)->instanceSize = sizeof(struct cnsname);\
			((struct whodun_Object_vtable_dec*)needInit)->vtableSize = sizeof(struct cnsname ## _vtable_dec);\
			whodun_atomicSet(& cnsname ## _vtable_varHaveInit, 1, & cnsname ## _vtable_varLock);\
		}\
		whodun_mutexUnlock(whodun_GIL);\
	}\
	return & cnsname ## _vtable_var;\
}\
struct cnsname ## _vtable_dec* (* cnsname ## _vtable)() = cnsname ## _vtable_imp ;

#ifdef __cplusplus
}
#endif
			


#endif

