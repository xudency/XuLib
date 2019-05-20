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
* Description: NAND Flash geometry define
*			   each NAND Flash has its cfg file, we should include the cfg file here
* 
* $Revision: 0 $
* $Date:  $
* $Author: Dengcai Xu $
* Release $Name$
*
****************************************************************************/


#ifndef CFG_FLASH_CFG_H_
#define CFG_FLASH_CFG_H_

//#include "libtype.h"


#define BITS_WIDTH(width) 	 ((1 << (width)) - 1)			 // width: bit count, bit count 1-base



//#include "cfg_TSB_TH58TFG9DFK.h"
//#include "cfg_MICRON_MCL95B.h"
#include "cfg_MICRON_B17A_FortisMax.h"


#define DIE_BITS				(FSQ_BITS+FSQ_CH_BITS+CE_BITS+CE_LUN_BITS)
#define FPA_BITS 				(DIE_BITS+OF_BITS+PL_BITS+PG_BITS+BLK_BITS)

#if (FPA_BITS > 32)
#error "FPA total Bits exceed 32 Bit"
#else
#define RSVD_BITS				(32-FPA_BITS)
#endif

#define FPA_SZ 					0x1000  				// 4KB

#define BLK_SHIFT 				(OF_BITS+PL_BITS+PG_BITS)
#define CE_LUN_SHIFT 			(BLK_SHIFT+BLK_BITS)
#define CE_SHIFT 				(CE_LUN_SHIFT+CE_LUN_BITS)
#define FSQ_CH_SHIFT 			(CE_SHIFT+CE_BITS)
#define FSQ_SHIFT 				(FSQ_CH_SHIFT+FSQ_BITS)

#define CFG_NAND_FSQ_NUM   		2 //6, EMU only has FSQ0 and FSQ3
#define CFG_NAND_FSQ_CH_NUM   	2
#define CFG_NAND_DIE_NUM		(CFG_NAND_FSQ_NUM*CFG_NAND_FSQ_CH_NUM*CFG_NAND_CE_NUM*CFG_NAND_CE_LUN_NUM)

#define CFG_NAND_TOTAL_FPAS   	(CFG_NAND_OF_NUM*CFG_NAND_PL_NUM*CFG_NAND_DIE_NUM*CFG_NAND_PG_NUM*CFG_NAND_BLK_NUM)
#define CFG_NAND_PHY_BLKS     	(CFG_NAND_PL_NUM*CFG_NAND_DIE_NUM*CFG_NAND_BLK_NUM)
#define CFG_NAND_RPAGE_FPAS   	(CFG_NAND_OF_NUM*CFG_NAND_PL_NUM*CFG_NAND_DIE_NUM)

#define CFG_NAND_PG_RAW_SZ		(CFG_NAND_OOB_SZ+CFG_NAND_PG_SZ)

#define NPU_FPA_NUM			  	(CFG_NAND_OF_NUM*CFG_NAND_PL_NUM)
#define WCD_SNUM			  	NPU_FPA_NUM

#define NPU_SZ					(FPA_SZ*NPU_FPA_NUM)	// 16*4KB

#define FPA_META_SZ				(CFG_NAND_OOB_SZ/CFG_NAND_OF_NUM)		// Hmeta CRC ECC encode is all place here

#define DIE_RSVD_BITS  			(8-DIE_BITS)

// CAUTIOUS: die has no hole
typedef union
{
    struct 
	{
	#if (CE_LUN_BITS > 0)
      unsigned char lun: 		CE_LUN_BITS;
	#else
	  // 1 lun per target, LUN alway=0, not need show explicitly in FPA_T
	#endif
      unsigned char ce: 		CE_BITS;
      unsigned char fsq_ch: 	FSQ_CH_BITS;
      unsigned char fsq: 		FSQ_BITS;
	  
	#if (DIE_RSVD_BITS > 0)
      unsigned char rsvd0: 	DIE_RSVD_BITS;
	
	#endif
    };
	
    unsigned char die;
} fpa_die_t;


typedef union 
{
  struct {
	  unsigned int of		  : OF_BITS;	  // this is PAGE Offset
	  unsigned int pl		  : PL_BITS;	  
	  unsigned int pg		  : PG_BITS;
	  unsigned int blk		  : BLK_BITS;

	  unsigned int die		  : DIE_BITS;		  // FSQ FSQ_CH CE LUN

	#if (RSVD_BITS>0)
	  unsigned int rsvd		  : RSVD_BITS;
	#endif
  };
  unsigned int fpa_all;
} fpa_t;


typedef union 
{
  struct {
	  unsigned int eid		: 16;
	  unsigned int rid		: 4;
	  unsigned int scratch	: 5;
	  unsigned int pattern	: 7;  // 0x7f: slot_pattern
  };
  unsigned int slot_all;
} slot_t;

// The definition of FPA format
typedef union
{
	fpa_t fpa;
	slot_t slot;
} ftl_map_entry;

#define GET_FSQ_ID_FROM_FPA(fpa)		(((fpa)>>FSQ_SHIFT) & (BITS_WIDTH(FSQ_BITS)))
#define GET_FSQ_ID_FROM_DIE(die)		(((die)>>(FSQ_CH_BITS+CE_BITS+CE_LUN_BITS)) & (BITS_WIDTH(FSQ_BITS)))

#define CALC_DIE(fsq, fsq_ch, ce, lun) \
	((lun) | ((ce)<<CE_LUN_BITS) | ((fsq_ch)<<(CE_LUN_BITS+CE_BITS)) | ((fsq)<<(CE_LUN_BITS+CE_BITS+FSQ_CH_BITS)))


// FIF_GEN_REQ/FIF_GEN_RSP Operation Type
// op has 8 bit in QW0, so we can define 256 op at most
enum {
	FIF_GEN_OP_DNLD_MCODE = 0,
	FIF_GEN_OP_RD_FLASH_ID,
	FIF_GEN_OP_RESET_FLASH,
	FIF_GEN_OP_SET_FEATURE,
	FIF_GEN_OP_GET_FEATURE,
	FIF_GEN_OP_BB_DISCOVERY,
	FIF_GEN_OP_HALT_GCU,
	FIF_GEN_OP_FLUSH_GCU,
	FIF_GEN_OP_SET_FLASH_CFG,
	FIF_GEN_OP_GET_DEBUG_STATS,
	FIF_GEN_OP_PFAIL_FLUSH,
	FIF_GEN_OP_READ_STATUS,
	FIF_GEN_OP_SET_FLASH_TYPE,
	FIF_GEN_OP_RNA_CMD,
	FIF_GEN_OP_TFA_CMD,				// Transparent FPA Access
	FIF_GEN_OP_RESUME_ABORTED_DIE,
	FIF_GEN_OP_PASSTHRU_WCD,
	FIF_GEN_OP_PASSTHRU_RCD,
	FIF_GEN_OP_PASSTHRU_ERZ,
	FIF_GEN_OP_QOS_PG_THROTTLE,    // Out Standing RPage number limitted
	FIF_GEN_OP_ECP_LEN_CFG,
	
	FIF_GEN_OP_INVALID,
};


// ONFI spec
#define ONFI_FEATURE_ADDR_TIMING_MODE		0x1
#define ONFI_FEATURE_ADDR_NV_DDR_CFG		0x2
#define ONFI_FEATURE_ADDR_VPP_CFG			0x30
#define ONFI_FEATURE_ADDR_VOLUME_CFG		0x58



typedef union {
  struct {
    unsigned short lb_crc_en      : 1;		// 0 2B CRC disable
    unsigned short lb_meta_sz 	   : 6;		// 8B*(this_value)
    unsigned short lb_sz   	   : 2;		// 0-512B  1-4KB  2-16KB
    unsigned short cph_sz         : 2;		// 16B*(this_value)
    unsigned short lb_num_in_cp   : 5;		// 0-base
  };
  unsigned short all;
} cp_len_info;

// IO gadget Info
typedef union {
  struct {
    unsigned int plane_map  : 4;
    unsigned int dtype      : 4;
    unsigned int qos_die    : 8;
    unsigned int ldpc_en    : 1;
    unsigned int scrm_en    : 1;
    unsigned int cri_sel    : 1;
	unsigned int rsvd0	   : 5;
	unsigned int band	   : 8;
  };
  unsigned int reg;
} ioggi_t;



#endif /* CFG_FLASH_CFG_H_ */
