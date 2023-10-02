
/* Includes ******************************************************************/
#define __HDR_DEFS__
#include "Platform/RV32G/rmp_platform_rv32g.h"
#include "Kernel/rmp_kernel.h"
#undef __HDR_DEFS__

#define __HDR_STRUCTS__
#include "Platform/RV32G/rmp_platform_rv32g.h"
#include "Kernel/rmp_kernel.h"
#undef __HDR_STRUCTS__

/* Private include */
#include "Platform/RV32G/rmp_platform_rv32g.h"

#define __HDR_PUBLIC_MEMBERS__
#include "Kernel/rmp_kernel.h"
#undef __HDR_PUBLIC_MEMBERS__
/* End Includes **************************************************************/

/* Entry *********************************************************************/
/* This portion is completely GCC specific - if you need to move this to other
 * compilers, this needs to be changed. The linker script should also be changed
 * as well. */
/* Address of the data section */
extern rmp_ptr_t  __data_load_addr__;
/* Begin address for the .data section */
extern rmp_ptr_t __data_begin__;
/* End address for the .data section */
extern rmp_ptr_t __data_end__;
/* Begin address for the .bss section */
extern rmp_ptr_t __bss_begin__;
/* End address for the .bss section */
extern rmp_ptr_t __bss_end__;
/* The entry address */
extern int main(void);
void _start(void);
void __attribute__((weak)) _start(void)
{
    rmp_u8_t* Src;
    rmp_u8_t* Dst;

    Src=(rmp_u8_t*)&__data_load_addr__;
    Dst=(rmp_u8_t*)&__data_begin__;
    while((rmp_ptr_t)Dst<(rmp_ptr_t)&__data_end__)
        *Dst++=*Src++;

    Dst=(rmp_u8_t*)&__bss_begin__;
    while((rmp_ptr_t)Dst<(rmp_ptr_t)&__bss_end__)
        *Dst++=0;

    /* Call main function */
    main();
}
/* End Entry *****************************************************************/
