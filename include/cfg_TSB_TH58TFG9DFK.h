/*
 * cfg_TSB_TH58TFG9DFK.h
 *
 *  Created on: 2018Äê9ÔÂ17ÈÕ
 *      Author: dengcaixu
 */

#ifndef CFG_TSB_TH58TFG9DFK_H_
#define CFG_TSB_TH58TFG9DFK_H_


#define OF_BITS    		2
#define PL_BITS    		2
#define PG_BITS    		8
#define BLK_BITS   		11
#define FSQ_BITS		3
#define FSQ_CH_BITS		1
#define CE_BITS			2
#define CE_LUN_BITS		1

// CFG_NAND_XX_NUM DON'T use 1<<BITS, e.g. blk 9bit but number is 504 rather than 2^9
#define CFG_NAND_OF_NUM    		4
#define CFG_NAND_PL_NUM    		4
#define CFG_NAND_PG_NUM    		256
#define CFG_NAND_BLK_NUM   		1069
#define CFG_NAND_CE_NUM   		4
#define CFG_NAND_CE_LUN_NUM		2

#define CFG_NAND_OOB_SZ		2208
#define CFG_NAND_PG_SZ		16384


#endif /* CFG_CFG_MICRO_95B_2TB_H_ */
