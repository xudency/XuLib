/********************************************************************
* FILE NAME: ktest_drv.c
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
*2014.6.27, dxu, initial coding.
*
****************************************************************/
#include <linux/pci.h>
#include <linux/spinlock.h>
#include <linux/list.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/stddef.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <asm/dma-mapping.h>
#include <linux/uaccess.h>
#include <linux/ptrace.h>
#include <linux/bitops.h>
#include <linux/time.h>
#include <linux/miscdevice.h>
#include <linux/kref.h>
#include <linux/bio.h>
#include "ktest_drv.h"
#include "ktest_ioctl.h"
#include "ktest_proc.h"
//#include "../include/libtype.h"


//u8 debug_level = PRINT_NOT;


/* global variable */
volatile s64 g_start = 0; /* this is the start timestamp for a testcase */

static struct tc_dev *tdev;



static int tc_dev_open(struct inode *inode, struct file *f)
{
    return 0;
}

static int tc_dev_release(struct inode *inode, struct file *f)
{
    return 0;
}

long tc_dev_ioctl(struct file *f, unsigned int cmd, unsigned long cmd_para)
{
	int i;
    //struct timespec ts;
    //ts = current_kernel_time();
    //g_start = timespec_to_ns(&ts);

	for (i = 0; i < gat_kernel_ioctl_array_size; i++)
	{
		if (cmd == gat_kernel_ioctl_array[i].cmd)
			return gat_kernel_ioctl_array[i].fn(cmd_para);
	}
	
	PRINTK( "cmd=0x%x is undefined", cmd);
	return -ENOTTY;

}

static const struct file_operations tc_dev_fops = {
    .owner             = THIS_MODULE,
    .open              = tc_dev_open,
    .release           = tc_dev_release,
    .unlocked_ioctl    = tc_dev_ioctl,
    .compat_ioctl      = tc_dev_ioctl,
};

static int __init ktest_init(void)
{
    int ret = 0;
    
    PRINTK("Ktest Version: %s\n", KTEST_VERSION);

    tdev = kzalloc(sizeof(*tdev), GFP_KERNEL);
    if (!tdev) {
		PRINTK("kzalloc fail !!!");
        return -ENOMEM;
    }

    tdev->scratch = 0;
    strcpy(tdev->name, KTEST_NAME); 
    tdev->miscdev.minor = MISC_DYNAMIC_MINOR;
    tdev->miscdev.name = tdev->name;
    tdev->miscdev.fops = &tc_dev_fops;
    ret = misc_register(&tdev->miscdev);
    if (ret < 0){
		PRINTK("misc char register failed");
        goto cleanup;
    }

    ktest_proc_init();

    PRINTK("misc device register success");


	//bbm_init();
	bbt_page = kzalloc(BBT_PAGE_SIZE, GFP_KERNEL);


        
    return 0;

cleanup:
    kfree(tdev);
    
    return ret;
}

static void __exit ktest_exit(void)
{
    PRINTK("ktest_exit");

	kfree(bbt_page);

    ktest_proc_exit();
    misc_deregister(&tdev->miscdev);

    kfree(tdev);	
    
    return ;
}



module_init(ktest_init);
module_exit(ktest_exit);

MODULE_AUTHOR("Dengcai Xu <dxu@cnexlabs.com>");
MODULE_LICENSE("GPL");
MODULE_VERSION(KTEST_VERSION);

