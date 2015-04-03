/***********************************************************************/
/*  This file is part of the ARM Toolchain package                     */
/*  Copyright (c) 2010 Keil - An ARM Company. All rights reserved.     */
/***********************************************************************/
/*                                                                     */
/*  FlashDev.C:  Device Description for New Device Flash               */
/*                                                                     */
/***********************************************************************/

#include "../FlashOS.H"        // FlashOS Structures
#include "spifi_rom_api.h"

struct FlashDevice const FlashDevice = {
   FLASH_DRV_VERS,             // Driver Version, do not modify!
   "SPIFI on ""LPC18xx/43xx @80000000",  // Device Name 
   EXTSPI,                     // Device Type
   0x80000000,                 // Device Start Address
   0x08000000,              // Device Size is 64MB max
   PROG_SIZE,                  // Programming Page Size
   0,                          // Reserved, must be 0
   0xFF,                       // Initial Content of Erased Memory
   500,                        // Program Page Timeout 100 mSec
   5000,                       // Erase Sector Timeout 3000 mSec

// Specify Size and Address of Sectors
   1024*256, 0,         		// sectors are 256 KB
   SECTOR_END
};
