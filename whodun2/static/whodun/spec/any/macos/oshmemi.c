#include "whodun/oshook.h"

#include <string.h>

#include <sys/sysctl.h>

#include "whodun/cpu.h"
#include "whodun/ermac.h"

//...friggin mac
//https://stackoverflow.com/questions/8782228/retrieve-ram-info-on-a-mac

whodun_UInt whodun_installedRAM_imp(){
	int mib[] = {CTL_HW, HW_MEMSIZE};
	int64_t value;
	size_t length = sizeof(int64_t);
	if(sysctl(mib, 2, &value, &length, 0, 0) == -1){
		//cheetah required 128MB
		return 0x08000000;
	}
	return value;
}

whodun_UInt whodun_availableRAM_imp(){
	/*
	mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
	vm_statistics_data_t vmstat;
	if(host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmstat, &count) != KERN_SUCCESS){
		//say you can use a megabyte
		return 0x00100000;
	}
	long pageS = sysconf(_SC_PAGESIZE);
	//... I'll let errors in this break wildly
	return vmstat.free_count * pageS;
	*/
	//OH MY HOLY FUCKING STUPID CRAP APPLES DOCUMENTATION IS DOGSHIT
	//HOW HARD IS IT TO LIST A FUCKING HEADER FILE
	//you get a megabyte, I'm not dealing with this
	return 0x00100000;
}



