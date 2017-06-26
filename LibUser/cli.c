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
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>
#include "cli.h"
#include "type.h"
#include "../common.h"

char devname[20];

int usage (int argc, char* argv[])
{
    /*  cmd list help to be continued...  */
    printf("-tc -c ch -e ep -p pl -l lun -g page -b blk   \n");
    printf("-krnl_in -p ppa_addr                           \n");
    return OK;
}

int krnl_ioctl(int argc, char* argv[])
{
	int i, result, fd;
	int cmd = MY_IOCTL_DBG;
	//u32 val = 0x12fd3a;

	void *usr_mem = malloc(PAGE_SIZE * 2);
	if (usr_mem == NULL) {
		return -1;
	}

	for (i = 0; i < (PAGE_SIZE * 2) / sizeof(u32); i++) {
		*((u32 *)usr_mem + i) = i + 0x100;
	}

	fd = open(devname, O_RDWR);
	if (fd < 0) {
		printf("no such device:%s\n", devname);
		result = -1;
		goto free_mem;
	}
	
	result = ioctl(fd, cmd, (u64)usr_mem);
	if (result < 0) {
		printf("ioctl return:0x%x\n", result);
	}

	close(fd);
free_mem:
	free(usr_mem);
	return result;
}

int get_opt_example(int argc, char* argv[])
{
    struct physical_address ppa_addr;
    long para = 0;
    long para_num = 0;
    char* endptr;
    int opt = 0;
    char* optstring = "c:e:p:l:g:b:";

    while (ERROR != (opt = getopt(argc, argv, optstring))) 
    { 
        switch (opt) 
        {
            case 'c':
                para_num++;
                para = strtol(optarg, &endptr, 0);
                printf("CH: %d.\n", (u16)para);
                ppa_addr.nand.ch = (u16)para;
                break;

            case 'e':
                para_num++;
                para = strtol(optarg, &endptr, 0);		
                printf("EP: %d.\n", (u16)para);
                ppa_addr.nand.sec = (u16)para;
                break;

            case 'p':
                para_num++;
                para = strtol(optarg, &endptr, 0);
                printf("PL: %d.\n", (u16)para);
                ppa_addr.nand.pl = (u16)para;
                break;

            case 'l':
                para_num++;
                para = strtol(optarg, &endptr, 0);		
                printf("lun: %d.\n", (u16)para);
                ppa_addr.nand.lun = (u16)para;
                break;


            case 'g':
                para_num++;
                para = strtol(optarg, &endptr, 0);
                printf("PG: %d.\n", (u16)para);
                ppa_addr.nand.pg = (u16)para;
                break;

            case 'b':
                para_num++;
                para = strtol(optarg, &endptr, 0);		
                printf("BLK: %d.\n", (u16)para);
                ppa_addr.nand.blk = (u16)para;
                break;;
                
            default :
                printf("unexpected parameter of crtsq: %c.\n", opt);
                break;
        }
    }

    printf("PPA: 0x%x\n", ppa_addr.ppa);
    
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
struct cli_callback_fn g_cmd_func_list[] = 
{
	/* run in User space only*/
	{"-help", usage},
	{"-tc", get_opt_example},

	/* control sample dev, run from User to Kernel space*/
	{"-krnl_in", krnl_ioctl},
	{NULL, NULL},
};

const int cmd_func_list_size = ARRAY_SIZE(g_cmd_func_list);

int cli_main(int argc, char* argv[])
{
    int i = 0;
    int ret = ERROR;    

    snprintf(devname, 20, "%s", "dev/debugger_node");

    for (i = 0; i < cmd_func_list_size; i++) 
    {
        if ((NULL != g_cmd_func_list[i].cmd) && 
		(!strcmp(argv[1], g_cmd_func_list[i].cmd))) {
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

