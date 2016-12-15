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
#include "declare.h"
#include "../comm/ioctl_comm.h"


int kernel_dbg(int argc, char* argv[])
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

int setppa(int argc, char* argv[])
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


int getppa(int argc, char* argv[])
{
    struct physical_address ppa_addr;

    long para = 0;
    long para_num = 0;
    char* endptr;
    int opt = 0;
    char* optstring = "p:";

    while (ERROR != (opt = getopt(argc, argv, optstring))) 
    { 
        switch (opt) 
        {
            case 'p':
                para_num++;
                para = strtol(optarg, &endptr, 0);
                printf("ppa_addr: 0x%lx\n", para);
                ppa_addr.ppa = (u32)para;
                break;
                
            default :
                printf("unexpected parameter of crtsq: %c.\n", opt);
                break;
        }
    }

    printf("CH:%d\n", ppa_addr.nand.ch);
    
    printf("EP:%d\n", ppa_addr.nand.sec);
    printf("PL:%d\n", ppa_addr.nand.pl);
    printf("LUN:%d\n", ppa_addr.nand.lun);
    printf("PG:%d\n", ppa_addr.nand.pg);
    printf("BLK:%d\n", ppa_addr.nand.blk);

    return 0;
}

