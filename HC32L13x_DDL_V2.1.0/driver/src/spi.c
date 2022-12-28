/******************************************************************************
* Copyright (C) 2016, Xiaohua Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Xiaohua Semiconductor Co.,Ltd ("XHSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with XHSC
* components. This software is licensed by XHSC to be adapted only
* for use in systems utilizing XHSC components. XHSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. XHSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* XHSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* XHSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with eaenCh copy of this software, whether used in part or whole,
* at all times.
*/
/*****************************************************************************/
/** \file spi.c
 **
 ** SPI driver API.
 ** @link Driver Group Some description @endlink
 **
 **   - 2018-05-17  1.0  Devi First version for Device Driver Library of
 **                      Module.
 **
 *****************************************************************************/

/******************************************************************************
 * Include files
 *****************************************************************************/
#include "spi.h"

/**
 ******************************************************************************
 ** \addtogroup SpiGroup
 *****************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 *****************************************************************************/

#define IS_VALID_STAT(x)            (   SpiIf == (x)||\
                                        SpiSserr == (x)||\
                                        SpiBusy == (x)||\
                                        SpiMdf == (x)||\
                                        SpiTxe == (x)||\
                                        SpiRxne == (x))


/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Local variable prototypes ('static')                                       */
/******************************************************************************/

/**
 ******************************************************************************
 ** \brief  SPI 请求状态获取
 **
 ** \param [in]SPIx 通道， enStatus 获取请求
 **
 ** \retval 请求状态
 ** 
 ******************************************************************************/
boolean_t Spi_GetStatus(M0P_SPI_TypeDef* SPIx, en_spi_status_t enStatus)
{    
    ASSERT(IS_VALID_STAT(enStatus));
    
    if(SPIx->STAT&enStatus)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
}
/**
 ******************************************************************************
 ** \brief  SPI中断清除
 **
 ** \param [in]SPIx 通道选择
 **
 ** \retval 请求状态
 ** 
 ******************************************************************************/
en_result_t Spi_ClearStatus(M0P_SPI_TypeDef* SPIx)
{    
    SPIx->ICLR = 0;
    
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  SPI 中断使能函数
 **
 ** \param [in] SPIx 通道
 **
 ** \retval Ok成功
 **
 ******************************************************************************/
en_result_t Spi_IrqEnable(M0P_SPI_TypeDef* SPIx)
{ 
    SPIx->CR2 |= 0x4u;
    
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  SPI 中断禁止函数
 **
 ** \param [in] enCh通道
 **
 ** \retval Ok成功
 **
 ******************************************************************************/
en_result_t Spi_IrqDisable(M0P_SPI_TypeDef* SPIx)
{ 
    SPIx->CR2 &= ~0x4u;
    
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  SPI 功能使能函数
 **
 ** \param [in] SPIx 通道，enFunc功能
 **
 ** \retval Ok初始化成功
 **
 ******************************************************************************/
en_result_t Spi_FuncEnable(M0P_SPI_TypeDef* SPIx, en_spi_func_t enFunc)
{    
    SPIx->CR2 |= enFunc;
    
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  SPI 功能禁止函数
 **
 ** \param [in] SPIx 通道，enFunc功能
 **
 ** \retval Ok初始化成功
 **
 ******************************************************************************/
en_result_t Spi_FuncDisable(M0P_SPI_TypeDef* SPIx, en_spi_func_t enFunc)
{    
    SPIx->CR2 &= ~(uint32_t)enFunc;
    
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  SPI 总体初始化函数
 **
 ** \param [in] SPIx 通道
 ** \param [in] pstcSpiCfg 初始化结构
 **
 ** \retval Ok初始化成功
 ** \retval ErrorInvalidParameter 初始化错误
 ******************************************************************************/
en_result_t Spi_Init(M0P_SPI_TypeDef* SPIx, stc_spi_cfg_t *pstcSpiCfg)
{
    ASSERT(NULL != pstcSpiCfg);

    SPIx->CR = 0;
    SPIx->CR =  (uint32_t)pstcSpiCfg->enSpiMode |
                (uint32_t)pstcSpiCfg->enPclkDiv |
                (uint32_t)pstcSpiCfg->enCPOL    |
                (uint32_t)pstcSpiCfg->enCPHA    |
                (uint32_t)0x40;
    
    SPIx->STAT = 0x00;

    return Ok;
}

/**
 ******************************************************************************
 ** \brief  SPI 配置主发送的电平
 **
 ** \param [in] SPIx 通道选择，bFlag高低电平
 **
 ** \retval 无
 ** 
 ******************************************************************************/
void Spi_SetCS(M0P_SPI_TypeDef* SPIx, boolean_t bFlag) 
{    
    SPIx->SSN = bFlag;    
} 
/**
 ******************************************************************************
 ** \brief  SPI 发送一字节函数
 **
 ** \param [in] SPIx 通道选择，u8Data发送字节
 **
 ** \retval Ok发送成功
 ** 
 ******************************************************************************/
en_result_t Spi_SendData(M0P_SPI_TypeDef* SPIx, uint8_t u8Data)
{  
    SPIx->DATA = u8Data;
   
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  SPI 接收一字节函数
 **
 ** \param [in] SPIx接收通道
 **
 ** \retval 接收一字节数据
 ** 
 ******************************************************************************/
uint8_t Spi_ReceiveData(M0P_SPI_TypeDef* SPIx)
{
    return SPIx->DATA;
}

//@} // SpiGroup
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

