;/****************************************************************************/
;/* ajsm.asm - Customer Private Unlock Code                                  */
;/****************************************************************************/
;
; Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com 
; 
; 
;  Redistribution and use in source and binary forms, with or without 
;  modification, are permitted provided that the following conditions 
;  are met:
;
;    Redistributions of source code must retain the above copyright 
;    notice, this list of conditions and the following disclaimer.
;
;    Redistributions in binary form must reproduce the above copyright
;    notice, this list of conditions and the following disclaimer in the 
;    documentation and/or other materials provided with the   
;    distribution.
;
;    Neither the name of Texas Instruments Incorporated nor the names of
;    its contributors may be used to endorse or promote products derived
;    from this software without specific prior written permission.
;
;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
;  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
;  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
;  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
;  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
;  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
;  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
;  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;
;/****************************************************************************/
;
; File Description : ajsm.asm
;              This file is generated that contains the Customer or User 
; private AJSM unlock code which can be programmed to the dedicated 128bit OTP 
; memory region starting 0xF0000000. IMPORTANT NOTE: Corresponding ECC has to 
; programmed otherwise device might be permanently locked. 
;              
;              Please refer device datasheet for more info on AJSM support.   
;
; Steps to Add AJSM Support:
; -------------------------- 
; 1) Generate the Visible Unlock Code using HALCoGen AJSM Tab.
; 2) Make sure Save Key is pressed before Generating HALCoGen Code.
; 3) Add Memory Section in linker file to program the ""ajsm"" data section 
;    to address location 0xF0000000.
;   
;    	-------------------------------------
;    	Below example is for CCS Linker file
;    	-------------------------------------
;    	MEMORY
;    	{
;       	 - - - - - 
;        	 - - - - - 
;        	AJSM    : org = 0xF0000000   len = 0x00000010
;			AJSMECC : org = 0xF0040000   len = 0x00000002
;    	}
;
;    	SECTIONS
;    	{
;       	 - - - - - 
;        	 - - - - - 
;       	.ajsm    : {} > AJSM
;			.ajsmecc : {} > AJSMECC
;    	}
; 4) Build the project.
; 5) Make sure ECC is calculated and is part of the Image before programming
;    Note: If ECC locations are not programmed correctly device might be 
;    locked permanently.
; 6) Once device programmed correctly, after reset your JTAG will be locked.
; 7) Below SafeTI forum Link contains the user guide for using CCS as Unlock Tool.
;    https://e2eprivate.ti.com/safeti_functional_safety_support/m/hercules_ajsm_related_media/3575.aspx
; 
;    If you don’t have access then it will tell you the link is invalid.
;    Goto to www.ti.com/safetyanalysis to get access.
;   
; 8) Use the Scan pattern in the bottom of this file for JTAG unlock. 
;    This pattern is generated when AJSM "save key" button is pressed. 
;
;/****************************************************************************/

    .sect ".ajsm"
    .arm

AJSM0 .word  0xEFFDFFFFU
AJSM1 .word  0xFFFFFFFFU
AJSM2 .word  0xFFFDFFFEU
AJSM3 .word  0xFFEFFFFFU


    .sect ".ajsmecc"
    .arm

AJSMECC0 .byte  0xEDU
AJSMECC1 .byte  0xEDU

	
;/****************************************************************************/
;   
; For the above visible key selected, for unlocking scan pattern below 
; 
; dbgauth key : PATTERN_NOT_REQUIRED 
; CCS: 
; 		unlock key bits 31:00  = PATTERN_NOT_REQUIRED
; 		unlock key bits 63:32  = PATTERN_NOT_REQUIRED
; 		unlock key bits 95:64  = PATTERN_NOT_REQUIRED
; 		unlock key bits 127:96 = PATTERN_NOT_REQUIRED
;
;/****************************************************************************/
