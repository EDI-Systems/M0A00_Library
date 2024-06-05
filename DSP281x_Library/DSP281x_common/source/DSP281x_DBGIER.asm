;// TI File $Revision: /main/2 $
;// Checkin $Date: April 29, 2005   11:10:54 $
;//###########################################################################
;//
;// FILE:  DSP281x_DBGIER.asm
;//
;// TITLE: Set the DBGIER register
;//
;// DESCRIPTION:
;//  
;//  Function to set the DBGIER register (for realtime emulation).
;//  Function Prototype: void SetDBGIER(Uint16)
;//  Useage: SetDBGIER(value);
;//  Input Parameters: Uint16 value = value to put in DBGIER register. 
;//  Return Value: none          
;//
;//###########################################################################
;// $TI Release: DSP281x C/C++ Header Files V1.20 $
;// $Release Date: July 27, 2009 $
;//###########################################################################
		.global _SetDBGIER
		.text
		
_SetDBGIER:
		MOV 	*SP++,AL
		POP 	DBGIER
		LRETR
		
