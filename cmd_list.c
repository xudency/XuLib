/********************************************************************
* FILE NAME: cmd.c
*
*
* PURPOSE: cmd and routing function define here.
*
* 
* NOTES:
*
* 
* DEVELOPMENT HISTORY: 
* 
* Date Author Release  Description Of Change 
* ---- ----- ---------------------------- 
*2016.11.27, dxu, initial coding.
*
****************************************************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "declare.h"
#include "../comm/ioctl_comm.h"

int usage (int argc, char* argv[])
{
    /*  cmd list help to be continued...  */
    printf("-setppa -c ch -e ep -p pl -l lun -g page -b blk   \n");
    printf("-getppa -p ppa_addr                           \n");
    return OK;
}

struct cmd_func_stru g_cmd_func_list[] = 
{
	/* run in User space only*/
	{"-help", usage},
	{"-setppa", setppa},
	{"-getppa", getppa},

	/* control sample dev, run from User to Kernel space*/
	{"-kdbg", kernel_dbg},
	{NULL, NULL},
};

const int cmd_func_list_size = sizeof(g_cmd_func_list)/sizeof(struct cmd_func_stru);

char devname[20];

int main(int argc, char* argv[])
{
    int i = 0;
    int ret = ERROR;    

    snprintf(devname, 20, "%s%s", "/dev/", CHARDEV_NAME);
    //printf("devname:%s\n", devname);

    /* search and compare the command */
    for (i = 0; i < cmd_func_list_size; i++) 
    {
        if ((NULL != g_cmd_func_list[i].cmd) && (!strcmp(argv[1], g_cmd_func_list[i].cmd))) {
            argc--;
            argv++;

            /* call the command routine */
            ret = g_cmd_func_list[i].fn(argc, argv);
            break;
        } else {
            continue;
        }
    }
    
    if (cmd_func_list_size == i){
        printf("Command error, adding \"-help\" cmd for help.\n");
        return ERROR;
    }
    
    return ret;
}

