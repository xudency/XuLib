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
#include "libtype.h"
#include "../include/flash_cfg.h"

char devname[20];

int usage (int argc, char* argv[])
{
    /*  cmd list help to be continued...  */
    printf("====================================================\n");
    printf("-tc -c ch -e ep -p pl -l lun -g page -b blk   \n");
    printf("-scanbb -t flash_type                           \n");
    printf("====================================================\n");
    return OK;
}


int optdemo_cli_parse(int argc, char* argv[])
{
    long para = 0;
    long para_num = 0;
    char* endptr;
    int opt = 0;
    char* optstring = "c:e:p:l:g:b:";

    fpa_t ppa_addr;
    ppa_addr.fpa_all = 0;

    while (ERROR != (opt = getopt(argc, argv, optstring))) 
    { 
        switch (opt) 
        {
            case 'd':
                para_num++;
                para = strtol(optarg, &endptr, 0);
                printf("DIE: %d.\n", (u16)para);
                ppa_addr.die = (u16)para;
                break;

            case 'o':
                para_num++;
                para = strtol(optarg, &endptr, 0);		
                printf("EP: %d.\n", (u16)para);
                ppa_addr.of = (u16)para;
                break;

            case 'p':
                para_num++;
                para = strtol(optarg, &endptr, 0);
                printf("PL: %d.\n", (u16)para);
                ppa_addr.pl = (u16)para;
                break;

            case 'g':
                para_num++;
                para = strtol(optarg, &endptr, 0);
                printf("PG: %d.\n", (u16)para);
                ppa_addr.pg = (u16)para;
                break;

            case 'b':
                para_num++;
                para = strtol(optarg, &endptr, 0);		
                printf("BLK: %d.\n", (u16)para);
                ppa_addr.blk = (u16)para;
                break;;
                
            default :
                printf("unexpected parameter of crtsq: %c.\n", opt);
                break;
        }
    }

    printf("PPA: 0x%x\n", ppa_addr.fpa_all);
    
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
struct cli_callback_fn gat_ucli_func_array[] = 
{
	/* run in User space only*/
	{"-help", usage},
	{"-demo", optdemo_cli_parse},

	/* control sample dev, run from User to Kernel space*/
	{"-scanbb", scan_bb_cli_parse},

	{"-readraw", scan_rdraw_cli_parse},

	{NULL, NULL},
};

const int gat_ucli_func_size = ARRAY_SIZE(gat_ucli_func_array);

int cli_main(int argc, char* argv[])
{
    int i = 0;
    int ret = ERROR;

    snprintf(devname, 20, "%s", "/dev/ksample0");

    for (i = 0; i < gat_ucli_func_size; i++) 
    {
        if ((NULL != gat_ucli_func_array[i].cmd) && 
		(!strcmp(argv[1], gat_ucli_func_array[i].cmd))) {

	    //PRINTU("%s", argv[1]);
            argc--;
            argv++;
            /* call the command routine */
            ret = gat_ucli_func_array[i].fn(argc, argv);
            break;
        } else {
            continue;
        }
    }
    
    if (gat_ucli_func_size == i){
        printf("Command is Invalid.\n");
        return ERROR;
    }
    
    return ret;
}

