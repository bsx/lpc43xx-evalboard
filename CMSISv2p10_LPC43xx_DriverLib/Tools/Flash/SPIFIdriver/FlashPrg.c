/***********************************************************************/
/*  FlashPrg.c:  Flash Programming Functions adapted for SPIFI Flash   */
/*  Copyright (c) 2011 NXP Semiconductors. All rights reserved.        */
/***********************************************************************/

#include "../FlashOS.H"        // FlashOS Structures
#include "spifi_rom_api.h"
#include "lpc18xx.h"

static struct FlashDevice FlashDevice;

SPIFIobj obj;

SPIFIopers opers = {
	NULL, 0, NULL, -1,	// save and restore protection
	S_CALLER_ERASE		// Keil code handles erasing
};

/* Mandatory Flash Programming Functions (Called by FlashOS):
                int Init        (unsigned long adr,   // Initialize Flash
                                 unsigned long clk,
                                 unsigned long fnc);
                int UnInit      (unsigned long fnc);  // De-initialize Flash
                int EraseSector (unsigned long adr);  // Erase Sector Function
                int ProgramPage (unsigned long adr,   // Program Page Function
                                 unsigned long sz,
                                 unsigned char *buf);

   Optional  Flash Programming Functions (Called by FlashOS):
                int BlankCheck  (unsigned long adr,   // Blank Check
                                 unsigned long sz,
                                 unsigned char pat);
                int EraseChip   (void);               // Erase complete Device
      unsigned long Verify      (unsigned long adr,   // Verify Function
                                 unsigned long sz,
                                 unsigned char *buf);

       - BlankCheck   necessary if Flash space is not mapped into CPU memory space
       - Verify       necessary if Flash space is not mapped into CPU memory space
       - if EraseChip is not provided than EraseSector for all sectors is called */

/*  Initialize Flash Programming Functions
 *    Parameter:      adr:  Device Base Address
 *                    clk:  Clock Frequency (Hz)
 *                    fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed */

int Init (unsigned long adr, unsigned long clk, unsigned long fnc) {
	int i;
#ifdef USE_SPIFI_LIB
#else
    SPIFI_RTNS * pSpifi;
    pSpifi = (SPIFI_RTNS *)(SPIFI_ROM_TABLE);
	/* Call functions via spifi rom table */
    #define spifi_init pSpifi->spifi_init
#endif
  /* init SPIFI clock and pins */
	LPC_CGU->BASE_SPIFI0_CLK = 1<<24 | 1<<11; /* IRC 12 MHz is good enough for us */

	/* set up SPIFI I/O (undocumented bit 7 set as 1, Aug 2 2011) */
	LPC_SCU->SFSP3_3 = 0xF3; /* high drive for SCLK */
	/* IO pins */
	LPC_SCU->SFSP3_4=LPC_SCU->SFSP3_5=LPC_SCU->SFSP3_6=LPC_SCU->SFSP3_7 = 0xD3;
	LPC_SCU->SFSP3_8 = 0x13; /* CS doesn't need feedback */

	if (spifi_init(&obj, 3, S_RCVCLK | S_FULLCLK, 12)) return 1;

	/* transfer info from init to FlashDevice struct */
	FlashDevice.szDev = obj.memSize;
	if (obj.protEnts) {
		/* build a Keil-style sector table from our sector table */
		unsigned ssz=1, sects = obj.sectors;
		struct FlashSectors *fsp = FlashDevice.sectors, *fsp2, *fsp3, svfs;
		protEnt *p = obj.protEnts;
		while (sects) {
			if (p->log2 < 0) {
				fsp->szSector = ssz = 1<<(-p->log2);
				fsp->AddrSector = p->base - ssz*(p->rept - 1);
			} else {
				fsp->szSector = 1<<p->log2;
				fsp->AddrSector = p->base;
			} 
			sects -= p->rept;
			fsp++;
			p++;
		}
		/* triangular-sort the Keil table into ascending address order */
		svfs.szSector = 1;
		while (svfs.szSector) {
			svfs.szSector = 0;
			fsp--;
			for (fsp2 = FlashDevice.sectors; fsp2 < fsp; fsp2++) {
				fsp3 = fsp2+1; 
				if (fsp2->AddrSector > fsp3->AddrSector) {
					svfs = *fsp2;
					*fsp2 = *fsp3;
					*fsp3 = svfs;
		}	}	}
	} else {
		/* because Keil keeps a 2-word descriptor for each sector, 
		   we have to post the largest available sector size */
		for (i=3; i>=0; i--) {
			if (obj.erase_shifts[i]) break;
		}
		FlashDevice.sectors[0].szSector = 1 << obj.erase_shifts[i];
	 }

	return 0;                                  // Finished without Errors
}
/*	De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed */

int UnInit (unsigned long fnc) {

  /* Add your Code */
  return 0;                                  // Finished without Errors
}
/*	Erase complete Flash Memory
 *    Return Value:   0 - OK,  1 - Failed */

int EraseChip (void) {
#ifdef USE_SPIFI_LIB
    /* Use spifi function names directly */
#else
    SPIFI_RTNS * pSpifi;
    pSpifi = (SPIFI_RTNS *)(SPIFI_ROM_TABLE);
	/* Call functions via spifi rom table */
    #define spifi_erase pSpifi->spifi_erase
#endif

	opers.dest = 0;
	opers.length = obj.devSize;
	return spifi_erase(&obj, &opers) != 0;
}
/*	Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed */

int EraseSector (unsigned long adr) {
#ifdef USE_SPIFI_LIB
    /* Use spifi function names directly */
#else
    SPIFI_RTNS * pSpifi;
    pSpifi = (SPIFI_RTNS *)(SPIFI_ROM_PTR);
	/* Call functions via spifi rom table */
    #define spifi_erase pSpifi->spifi_erase
#endif

	opers.dest = (char *)adr;
	if(obj.devSize < 1024*256)
		opers.length = obj.devSize;
	else
		opers.length = 1024*256;
	return spifi_erase(&obj, &opers) != 0;
}
/*	Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed */

int ProgramPage (unsigned long adr, unsigned long sz, unsigned char *buf) {
#ifdef USE_SPIFI_LIB
    /* Use spifi function names directly */
#else
    SPIFI_RTNS * pSpifi;
    pSpifi = (SPIFI_RTNS *)(SPIFI_ROM_TABLE);
	/* Call functions via spifi rom table */
    #define spifi_program pSpifi->spifi_program
#endif

	opers.dest = (char *)adr;
	opers.length = sz;
	return spifi_program(&obj, (char *)buf, &opers) != 0;
}
