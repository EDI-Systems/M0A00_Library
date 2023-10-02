/******************************************************************************
Filename    : rmp_fe310g000.s
Author      : pry
Date        : 10/04/2012
Description : The assembly part of the RMP RTOS. This is for RV32IMAC (FE310).
******************************************************************************/

/* Begin Header **************************************************************/
    .section            .reset_entry,"ax", @progbits
    .align              2
/* End Header ****************************************************************/

/* Startup & Init ************************************************************/
    .global             _Reset_Entry
_Reset_Entry:
    .option             push
    /* Ensure the instruction is not optimized, since gp is not yet set. GP
     * will be supplied by the linker to provide the position of global variables */
    .option             norelax
    /* Load global pointer */
    LA                  gp,__global_pointer$
    .option             pop
    /* Load stack pointer */
    LA                  sp,__stack
    /* Go into C to continue our initialization of .data and .bss */
    J                   _start
/* End Startup & Init ********************************************************/
