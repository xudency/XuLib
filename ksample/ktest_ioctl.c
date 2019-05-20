/********************************************************************
* FILE NAME: ktest_cmd.c
*
*
* PURPOSE:
*
*
* DEVELOPMENT HISTORY: 
*
* 
* Date Author Release  Description Of Change 
* ---- ----- ---------------------------- 
*2016.2.1, dxu, initial coding.
*
****************************************************************/

#include "ktest_drv.h"
#include "ktest_ioctl.h"
#include "../include/ioctl_def.h"
#include "../include/flash_cfg.h"


int ioctl_rdraw(unsigned long para)
{
	PRINTK("rdraw");

	return 0;
}



int ioctl_bmi_tst(unsigned long para)
{
	PRINTK("bmi test");

	return 0;
}


int ioctl_bb_scan(unsigned long para)
{
	fpa_t fpa;
	fpa.fpa_all = para;
	

	PRINTK("fpa:0x%x", fpa.fpa_all);

	return 0;
}


 struct kernel_ioctl_routine gat_kernel_ioctl_array[] = 
{
	{IOCTL_CODEID_BB_SCAN, ioctl_bb_scan},
	{IOCTL_CODEID_BMI_TST, ioctl_bmi_tst},

	{IOCTL_CODEID_RDRAW, ioctl_rdraw},

};
 
const int gat_kernel_ioctl_array_size = sizeof(gat_kernel_ioctl_array)/sizeof(struct kernel_ioctl_routine);

