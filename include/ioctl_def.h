/********************************************************************
* FILE NAME: ioctl_cmd.h
*
*
* PURPOSE: headerfile of this application. 
*
* 
* NOTES:
*
* 
* DEVELOPMENT HISTORY: 
* 
* Date Author Release  Description Of Change 
* ---- ----- ---------------------------- 
*2016.3.11, dxu, initial coding.
****************************************************************/
#ifndef _IOCTL_CMD_H
#define _IOCTL_CMD_H


struct cli_cmd {
	unsigned char opcode;
	unsigned char para1;
	unsigned char para2;
	unsigned char para3;
	unsigned char para4;
};


/* ppa sync*/
#define IOCTL_CODEID_BB_SCAN              _IOWR('E', 0x40, unsigned long long)
#define IOCTL_CODEID_BMI_TST              _IOWR('E', 0x41, unsigned long long)

#define IOCTL_CODEID_RDRAW                _IOWR('E', 0x42, unsigned long long)


#endif
