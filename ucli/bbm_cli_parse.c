/********************************************************************
* FILE NAME: bad block management.c
*
*
* PURPOSE: parsing for each cmd name.
*
* 
* NOTES:
*
* 
* DEVELOPMENT HISTORY: 
* 
* Date Author Release  Description Of Change 
* ---- ----- ---------------------------- 
*2019.3.27, dxu, initial coding.
*
********************************************************************/ 
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

#include "../include/flash_cfg.h"
#include "../include/ioctl_def.h"
#include "libtype.h"
#include "cli.h"

int scan_bb_cli_parse(int argc, char* argv[])
{
	int result, fd;

	long para = 0;
    long para_num = 0;
    char* endptr;
    int opt = 0;
    char* optstring = "d:e:p:l:g:b:";
	
	fpa_t fpa_addr;
	fpa_addr.fpa_all = 0;

    while (ERROR != (opt = getopt(argc, argv, optstring))) 
    { 
        switch (opt) 
        {
            case 'd':
                para_num++;
                para = strtol(optarg, &endptr, 0);
                printf("die: %d.\n", (u16)para);
                fpa_addr.die = (u16)para;
                break;

            case 'b':
                para_num++;
                para = strtol(optarg, &endptr, 0);		
                printf("blk: %d.\n", (u16)para);
                fpa_addr.blk = (u16)para;
                break;

            case 'p':
                para_num++;
                para = strtol(optarg, &endptr, 0);
                printf("PL: %d.\n", (u16)para);
                fpa_addr.pl = (u16)para;
                break;
                
            default :
                printf("unexpected parameter of scan bb: %c.\n", opt);
                break;
        }
    }

    PRINTU("FPA: 0x%x", fpa_addr.fpa_all);
	
	fd = open(devname, O_RDWR);
	if (fd < 0) {
		printf("no such device:%s\n", devname);
		return -1;
	}
	
	result = ioctl(fd, IOCTL_CODEID_BB_SCAN, fpa_addr);
	if (result < 0) {
		printf("ioctl return:0x%x\n", result);
	}

	
    return 0;
}



int scan_rdraw_cli_parse(int argc, char* argv[])
{
	int result, fd;

	long para = 0;
    long para_num = 0;
    char* endptr;
    int opt = 0;
    char* optstring = "d:e:p:l:g:b:";
	
	fpa_t fpa_addr;
	fpa_addr.fpa_all = 0;

    while (ERROR != (opt = getopt(argc, argv, optstring))) 
    { 
        switch (opt) 
        {
            case 'd':
                para_num++;
                para = strtol(optarg, &endptr, 0);
                printf("die: %d.\n", (u16)para);
                fpa_addr.die = (u16)para;
                break;

            case 'b':
                para_num++;
                para = strtol(optarg, &endptr, 0);		
                printf("blk: %d.\n", (u16)para);
                fpa_addr.blk = (u16)para;
                break;

            case 'p':
                para_num++;
                para = strtol(optarg, &endptr, 0);
                printf("PL: %d.\n", (u16)para);
                fpa_addr.pl = (u16)para;
                break;
                
            default :
                printf("unexpected parameter of scan bb: %c.\n", opt);
                break;
        }
    }

    PRINTU("FPA: 0x%x", fpa_addr.fpa_all);
	
	fd = open(devname, O_RDWR);
	if (fd < 0) {
		printf("no such device:%s\n", devname);
		return -1;
	}
	
	result = ioctl(fd, IOCTL_CODEID_RDRAW, fpa_addr);
	if (result < 0) {
		printf("ioctl return:0x%x\n", result);
	}

	
    return 0;
}

