#ifndef _KTEST_DRV_H
#define _KTEST_DRV_H

#include <linux/types.h>
#include <linux/miscdevice.h>
 
#define KTEST_VERSION    "KTEST20190517"

#define KTEST_NAME    "ksample0"


#define PRINTK(fmt, args...)  \
    printk("KERNEL[%s:%d]"fmt "\n", __FUNCTION__, __LINE__, ## args);

//#define MSECONDS                1000000
//#define USECONDS                1000


struct tc_dev {
    struct miscdevice miscdev;
	int scratch;
    char name[12];
};


extern volatile s64 g_start; // this is the start timestamp for a testcase


#endif
