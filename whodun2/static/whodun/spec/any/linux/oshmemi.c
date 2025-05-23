#include "whodun/oshook.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/ermac.h"

#include <sys/sysinfo.h>

whodun_UInt whodun_installedRAM_imp(){
	struct sysinfo infoStore;
	if(sysinfo(&infoStore)){ return 0x800000; } //Damn Small Linux requires 8MB as a minimum
	return ((uintptr_t)infoStore.totalram) * infoStore.mem_unit;
}

whodun_UInt whodun_availableRAM_imp(){
	struct sysinfo infoStore;
	if(sysinfo(&infoStore)){ return 0x200000; }
	return ((uintptr_t)infoStore.freeram) * infoStore.mem_unit;
}

