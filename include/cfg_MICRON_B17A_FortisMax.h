/****************************************************************************
* Copyright (c) 2018 - 2020 Store-Swift.
*	   All Rights Reserved
*
* Distribution of source code or binaries derived from this file is not
* permitted except as specifically allowed for in the Store-Swift.
* Software License agreement.  All copies of this source code
* modified or unmodified must retain this entire copyright notice and
* comment as is.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* Description: Micron 3D TLC NAND Flash B17A FortisMax Organization config
* we don't support Sixteen-Die Package with four CE# due to bit width restriction
* 
* $Revision: 0 $
* $Date:  $
* $Author: Dengcai Xu $
* Release $Name$
*
****************************************************************************/

#ifndef CFG_MICRON_B17A_FORTISMAX_H_
#define CFG_MICRON_B17A_FORTISMAX_H_

#define OF_BITS    		2
#define PL_BITS    		2
#define PG_BITS    		12
#define BLK_BITS   		9
#define FSQ_BITS		3
#define FSQ_CH_BITS		1
#define CE_BITS			1
#define CE_LUN_BITS		0

#define DIE_BITS		(FSQ_BITS+FSQ_CH_BITS+CE_BITS+CE_LUN_BITS)

// CFG_NAND_XX_NUM DON'T use 1<<BITS, e.g. blk 9bit but number is 504 rather than 2^9
#define CFG_NAND_OF_NUM    		4			// this is max offset when CRI is low
#define CFG_NAND_PL_NUM    		4
#define CFG_NAND_PG_NUM    		2304
#define CFG_NAND_BLK_NUM   		504

#define CFG_NAND_CE_NUM   		2 // 4
#define CFG_NAND_CE_LUN_NUM		1 // 2

#define CFG_NAND_OOB_SZ		2208
#define CFG_NAND_PG_SZ		16384

#define CFG_NAND_DIE_NVB	1912
#define CFG_NAND_BB_MARK	0x00

#endif /* CFG_MICRON_B17A_FORTISMAX_H_ */


