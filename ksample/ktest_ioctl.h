#ifndef _KTEST_CMD_H
#define _KTEST_CMD_H

#include <linux/types.h>
 
struct kernel_ioctl_routine
{
    unsigned int cmd;
    int (*fn)(unsigned long);
};

extern struct kernel_ioctl_routine gat_kernel_ioctl_array[];

extern const int gat_kernel_ioctl_array_size;


extern int ioctl_bb_scan(unsigned long);
extern int ioctl_bmi_tst(unsigned long);


#endif
