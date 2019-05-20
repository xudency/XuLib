/*
 * ftl_cfg.h
 *
 *  Created on: 12/23/2018
 *      Author: dengcaixu
 */

#ifndef CFG_FTL_CFG_H_
#define CFG_FTL_CFG_H_

#include "flash_kick.h"
#include "utils.h"


#define NS_NUM				1

/*
#define HOST_STREAM_NUM		1
#define GC_STREAM_NUM		1

#define CPA_BAND_NUM		(HOST_STREAM_NUM + GC_STREAM_NUM)
#define TOTAL_BAND_NUM		(CPA_BAND_NUM + 3)		// ckpt + sys + boot
*/


#define CPA_BAND_NUM		1
#define TOTAL_BAND_NUM		1	// ckpt + sys + boot


#define OVER_PROVISION_CFG	OVER_PROVISION_CFG_28		 // Over-Provision space config


// if CP_SZ > LBA_SZ, runt 
#define LB_SZ 					(0x1000) 		//0x1000   // 512B, 4KB
#define CP_SZ 					(0x1000)   // Control Page Size 4KB or 16KB
#define CP_SZ_BITS              (12)

#define CPH_SZ					0x10
#define HMETA_SZ				0 //0x10
#define PHIF_CRC_SZ				0 // 2		// PHIF HDMA CRC16	

#define LB_NUM_IN_CP			(CP_SZ/LB_SZ)		// 8



/*
 * @LPDC Config
 * 
 */
#define LDPCEN_DATA_MAX_BLEN		2176			// HW resource restriction 

#define CP_IN_FP_BLEN		(CPH_SZ + (LB_SZ+HMETA_SZ+PHIF_CRC_SZ)*LB_NUM_IN_CP)    // not include SCRAMBLE+BCH parity

#define SCRAMBLE_SZ			(8)		// 4B seed + 4B CRC32,   pad_en=0


// LDPC encode data length require 16B align, this should not exceed Maximum User Bytes:2176
#define LDPCEN_DATA_BLEN			roundup((CP_IN_FP_BLEN + SCRAMBLE_SZ)/2, 16)

#if (LDPCEN_DATA_BLEN > LDPCEN_DATA_MAX_BLEN)
	#error "LDPC Encode data length has exceed 2176"
#endif


#define LDPCEN_DATA_LEN_OW_CNT			(LDPCEN_DATA_BLEN >> 4)		// OW: 16 Bytes align


#define LDPC_CRI_NUM		8	// Code Rate Index: 0-7


/**
 * @brief drive capacity information
 */
#define CAPACITY                     CAPACITY_GiB(4096)


#define CAPACITY_IN_GiB             (((CAPACITY  * 1) / 1) >> 30)
#define CAPACITY_IN_GB              (((CAPACITY  * 1) / 1)/(double)(1000*1000*1000))


#define GB_IN_BYTE_HEX(cap)        ((cap)*1024*1024*1024)
#define GB_IN_BYTE_DEC(cap)        ((cap)*1000*1000*1000)

/**
 * @brief this fomular is that given absoult logical capacity in decimal, then deduct the op
 */
#if (OVER_PROVISION_CFG == OVER_PROVISION_CFG_7)
    #define LOGICAL_CAPACITY_IN_GB     (u64)(CAPACITY_IN_GiB*0.9375)  // 7%
#elif (OVER_PROVISION_CFG == OVER_PROVISION_CFG_14)
    #define LOGICAL_CAPACITY_IN_GB     (u64)(CAPACITY_IN_GiB*0.8872)  // 14%
#elif (OVER_PROVISION_CFG == OVER_PROVISION_CFG_20)
    #define LOGICAL_CAPACITY_IN_GB     (u64)(CAPACITY_IN_GiB*0.8385)  // 21%
#elif (OVER_PROVISION_CFG == OVER_PROVISION_CFG_28)
    #define LOGICAL_CAPACITY_IN_GB     (u64)(CAPACITY_IN_GiB*0.7949)   // 28%
#endif




#define CAPACITY_OP                (double)(GB_IN_BYTE_DEC(CAPACITY_IN_GiB) - GB_IN_BYTE_DEC(LOGICAL_CAPACITY_IN_GB))/(double)(GB_IN_BYTE_DEC(LOGICAL_CAPACITY_IN_GB))




#if (ENABLE == RAM_DRIVE)
    //#define MAX_LBA         (0x3ffff)  // small lba size
	#define MAX_LBA			(127)		// EMU only has 16 MAP Entry
#else
    //Use JEDEC capacity calculation
    /**
     * @brief Use JEDEC capacity calculation, use lba size is 4k
     */    
    //#define MAX_LBA             (((((((u64)LOGICAL_CAPACITY_IN_GB - 50) * 1953504) + 97696368) >> 3) << 3) - 1)
    #define MAX_LBA             ((((((u64)LOGICAL_CAPACITY_IN_GB - 50) * 1953504) + 97696368) >> 3) - 1)

#endif


// MIN_CPA <= Valid_CPA <= MAX_CPA
#define MIN_CPA		0

#define MAX_CPA		  			((MAX_LBA+1)/LB_NUM_IN_CP - 1)  //((u32)(SSD_USER_CAPACITY/CP_SZ))



// total SSD capacity in Byte, inclue bb, sys-blocks, boot-blocks, etc.
#define SSD_RAW_CAPACITY ((u64)CFG_NAND_TOTAL_FPAS*FPA_SZ)

// visible capacity for host user, OP is reserved internal and invisibe for host
#define SSD_USER_CAPACITY ((u64)((MAX_CPA + 1)*CP_SZ))



/////////////////////////////////////////////////////RAIF releated Config
#define RAIF_DISABLE			0
#define RAIF1_ENABLE			1					// BEWARE: not change this value
#define RAIF2_ENABLE			2					// BEWARE: not change this value

#define RAIF_MODE				RAIF_DISABLE		//RAIF1_ENABLE/RAIF2_ENABLE/RAIF_DISABLE

#if (RAIF_MODE == RAIF_DISABLE)

	#define RAIF_STRIPE_WIDTH		192 		    //this must be CHANNEL*N, 12/24/48/96/192
	#define RAIF_GROUP_NUM			1	
	#define CFG_WPBQ_NUM			TOTAL_BAND_NUM
	
#elif ((RAIF_MODE == RAIF1_ENABLE) || (RAIF_MODE == RAIF2_ENABLE))

	#define RAIF_STRIPE_WIDTH		192     			//this must be CHANNEL*N, 12/24/48/96/192
	#define RAIF_GROUP_NUM			(CFG_NAND_DIE_NUM/RAIF_STRIPE_WIDTH)

	#define CFG_WPBQ_NUM			TOTAL_BAND_NUM*2
	
#else
	#error "RAIF Mode Invalid"
#endif


#define RPAGE_LIMITTED_THRD          1     // per band


///// HW Resource Config
#define CFG_WPBQ_DEPTH				16  	      // how many wpb entry in one wpb queue, support up to 16

#define CFG_WPBQ_LO_THRD			4

#define FTLA_LRU_SWAP_TRIGGER_THRD  0x7ff0

#define CFG_WFD_SLOT_NUM 		16//SZ_32K        // How many slots of WFD region, we support up to 32K
#define CFG_RRD_SLOT_NUM		16//96
#define CFG_WCD_SLOT_NUM		16//SZ_4K		  // 0 - 4K
#define CFG_RCD_SLOT_NUM		16//SZ_2K		  // 0 - 2K
#define CFG_RDCMD_NUM			16//SZ_1K		  // 0 - 1K
#define CFG_ERZCMD_NUM			16//SZ_256		  // 0 - 1K



#endif /* CFG_FTL_CFG_H_ */
