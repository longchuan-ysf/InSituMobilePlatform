/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: sdio.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2019.11.22			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是sdio总线硬件驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S SDIO_Init(INT8U id, SDIO_PARA *pPara);
*          2. INT32S SDIO_Read(INT8U id, INT8U *p, INT32U len);
*          3. INT32S SDIO_Write(INT8U id, INT8U *p, INT32U len);
*          4. INT32S SDIO_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __SDIO_H 
#define __SDIO_H 
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// SPI初始化函数参数定义
/************************************************************************************/
// SPI索引定义
#define SDIO_ID		0 

/************************************************************************************************************************/
// 以下表是工控模块STM32F103VE, STM32F103ZE 管脚映射表, 是利用重映射方式定义
/************************************************************************************************************************/
// SDIO(管脚)功能重映射表
/*
|--------------------------------------------------------------------------------|
| 项目  |  重映射  | SDIO_CMD | SDIO_CK  | SDIO_D0 | SDIO_D1 | SDIO_D2 | SDIO_D3 |
|--------------------------------------------------------------------------------|
| SDIO  |   没有   |   PD2    |   PC12   |   PC8   |   PC9   |  PC10   |  PC11   |
|--------------------------------------------------------------------------------|
*/

/************************************************************************************************************************/
// 以下表是工控模块STM32F407VE/ZE/VG/ZG  管脚映射表, 是利用管脚复用寄存器定义
/************************************************************************************************************************/
// SDIO(管脚)功能映射表
/*
|--------------------------------------------------------------------------------|
| 项目  | 复用选择 | SDIO_CMD | SDIO_CK  | SDIO_D0 | SDIO_D1 | SDIO_D2 | SDIO_D3 |
|--------------------------------------------------------------------------------|
| SDIO  |   AF12   |   PD2    |   PC12   |   PC8   |   PC9   |  PC10   |  PC11   |
|--------------------------------------------------------------------------------|
*/

// SPI管脚参数结构 
typedef struct
{
    INT8U  CMD;       // SDIO_CMD管脚
    INT8U  CK;        // SDIO_CK管脚
    INT8U  D0;        // SDIO_D0管脚
    INT8U  D1;        // SDIO_D1管脚
    INT8U  D2;        // SDIO_D2管脚
    INT8U  D3;        // SDIO_D3管脚
}SDIO_PIN;

#define  SDIO_MODE_NORMAL    0   // 正常操作模式
#define  SDIO_MODE_DMA       1   // DMA操作模式 

// SDIO Initialization Frequency (400KHz max)
#define SDIO_INIT_CLK_DIV     ((INT8U)0x76)

// SDIO Data Transfer Frequency (25MHz max) 
#define SDIO_TRANSFER_CLK_DIV ((INT8U)0x02)

// SDIO总线宽度定义
#define SDIO_WIDBUS_1BIT      1
#define SDIO_WIDBUS_4BIT      4
#define SDIO_WIDBUS_8BIT      8

// SPI参数结构
typedef struct
{
    INT16U Flag;                // 参数标志
    INT8U  Mode;                // 工作模式：参考工作模式定义
    SDIO_PIN Pin;               // SDIO管脚 
    INT8U  ClkDiv;              // 时钟分频, 0-255, 0表示不分频   
    INT8U  WidBus;              // 总线宽度, 1或者4或者8   
}SDIO_PARA;


 
// SDMMC Data Control structure 
typedef struct
{
    INT32U DataTimeOut;         // Specifies the data timeout period in card bus clock periods.  
    INT32U DataLength;          // Specifies the number of data bytes to be transferred. 
    INT32U DataBlockSize;       // Specifies the data block size for block transfer.
                                // This parameter can be a value of @ref SDMMC_LL_Data_Block_Size
    INT32U TransferDir;         // Specifies the data transfer direction, whether the transfer
                                // is a read or write. This parameter can be a value of @ref SDMMC_LL_Transfer_Direction 
    INT32U TransferMode;        // Specifies whether data transfer is in stream or block mode.
                                // This parameter can be a value of @ref SDMMC_LL_Transfer_Type
    INT32U DPSM;                // Specifies whether SDMMC Data path state machine (DPSM)
                                // is enabled or disabled. This parameter can be a value of @ref SDMMC_LL_DPSM_State    
}SDIO_DataInitTypeDef;

/************************************************************************************/
// 命令控制函数参数定义
/************************************************************************************/
//// SPI时钟分频系数
//#define SPI_DIVCLK_2         ((INT16U)0x0000)   // 2分频
//#define SPI_DIVCLK_4         ((INT16U)0x0008)	// 4分频
//#define SPI_DIVCLK_8         ((INT16U)0x0010)	// 8分频
//#define SPI_DIVCLK_16        ((INT16U)0x0018)	// 16分频
//#define SPI_DIVCLK_32        ((INT16U)0x0020)	// 32分频
//#define SPI_DIVCLK_64        ((INT16U)0x0028)	// 64分频
//#define SPI_DIVCLK_128       ((INT16U)0x0030)	// 128分频
//#define SPI_DIVCLK_256       ((INT16U)0x0038)	// 256分频

//// 时钟相位模式
//#define SPI_CKMODE0  0	// CPOL = 0, CPHA = 0: 时钟空闲低电平, 数据采样从第一个时钟边沿开始(上升沿)  
//#define SPI_CKMODE1  1	// CPOL = 0, CPHA = 1：时钟空闲低电平, 数据采样从第二个时钟边沿开始(下降沿)  
//#define SPI_CKMODE2  2	// CPOL = 1, CPHA = 0：时钟空闲高电平, 数据采样从第一个时钟边沿开始(下降沿)  
//#define SPI_CKMODE3  3	// CPOL = 1, CPHA = 1：时钟空闲高电平, 数据采样从第二个时钟边沿开始(上升沿)   

//// SPI 控制命令定义
//#define CMD_SPI_ENA                    0  // 使能SPI外设
//#define CMD_SPI_DIS                    1  // 禁用SPI外设
//#define CMD_SPI_DIVCLK	               2  // 设置时钟分频系数
//#define CMD_SPI_CKMODE	               3  // 时钟相位模式，Para：可以为0,1,2,3
//#define CMD_SPI_RST                    4  // 复位SPI寄存器为初始状态
//#define CMD_SPI_CLOSE                  5  // 关闭SPI时钟,也就是关闭SPI功能,可以省电 


// SDMMC_LL_Exported_Constants SDMMC_LL Exported Constants
#define SDMMC_ERROR_NONE                     0x00000000U   // No error                                                      
#define SDMMC_ERROR_CMD_CRC_FAIL             0x00000001U   // Command response received (but CRC check failed)              
#define SDMMC_ERROR_DATA_CRC_FAIL            0x00000002U   // Data block sent/received (CRC check failed)                   
#define SDMMC_ERROR_CMD_RSP_TIMEOUT          0x00000004U   // Command response timeout                                      
#define SDMMC_ERROR_DATA_TIMEOUT             0x00000008U   // Data timeout                                                  
#define SDMMC_ERROR_TX_UNDERRUN              0x00000010U   // Transmit FIFO underrun                                        
#define SDMMC_ERROR_RX_OVERRUN               0x00000020U   // Receive FIFO overrun                                          
#define SDMMC_ERROR_ADDR_MISALIGNED          0x00000040U   // Misaligned address                                            
#define SDMMC_ERROR_BLOCK_LEN_ERR            0x00000080U   // Transferred block length is not allowed for the card or the 
                                                           // number of transferred bytes does not match the block length   
#define SDMMC_ERROR_ERASE_SEQ_ERR            0x00000100U   // An error in the sequence of erase command occurs              
#define SDMMC_ERROR_BAD_ERASE_PARAM          0x00000200U   // An invalid selection for erase groups                         
#define SDMMC_ERROR_WRITE_PROT_VIOLATION     0x00000400U   // Attempt to program a write protect block                      
#define SDMMC_ERROR_LOCK_UNLOCK_FAILED       0x00000800U   // Sequence or password error has been detected in unlock 
                                                           //   command or if there was an attempt to access a locked card    
#define SDMMC_ERROR_COM_CRC_FAILED           0x00001000U   // CRC check of the previous command failed                      
#define SDMMC_ERROR_ILLEGAL_CMD              0x00002000U   // Command is not legal for the card state                       
#define SDMMC_ERROR_CARD_ECC_FAILED          0x00004000U   // Card internal ECC was applied but failed to correct the data  
#define SDMMC_ERROR_CC_ERR                   0x00008000U   // Internal card controller error                                
#define SDMMC_ERROR_GENERAL_UNKNOWN_ERR      0x00010000U   // General or unknown error                                      
#define SDMMC_ERROR_STREAM_READ_UNDERRUN     0x00020000U   // The card could not sustain data reading in stream rmode       
#define SDMMC_ERROR_STREAM_WRITE_OVERRUN     0x00040000U   // The card could not sustain data programming in stream mode    
#define SDMMC_ERROR_CID_CSD_OVERWRITE        0x00080000U   // CID/CSD overwrite error                                       
#define SDMMC_ERROR_WP_ERASE_SKIP            0x00100000U   // Only partial address space was erased                         
#define SDMMC_ERROR_CARD_ECC_DISABLED        0x00200000U   // Command has been executed without using internal ECC          
#define SDMMC_ERROR_ERASE_RESET              0x00400000U   // Erase sequence was cleared before executing because an out 
                                                           // of erase sequence command was received                        
#define SDMMC_ERROR_AKE_SEQ_ERR              0x00800000U   // Error in sequence of authentication                           
#define SDMMC_ERROR_INVALID_VOLTRANGE        0x01000000U   // Error in case of invalid voltage range                        
#define SDMMC_ERROR_ADDR_OUT_OF_RANGE        0x02000000U   // Error when addressed block is out of range                    
#define SDMMC_ERROR_REQUEST_NOT_APPLICABLE   0x04000000U   // Error when command request is not applicable                  
#define SDMMC_ERROR_INVALID_PARAMETER        0x08000000U   // the used parameter is not valid                               
#define SDMMC_ERROR_UNSUPPORTED_FEATURE      0x10000000U   // Error when feature is not insupported                         
#define SDMMC_ERROR_BUSY                     0x20000000U   // Error when transfer process is busy                           
#define SDMMC_ERROR_DMA                      0x40000000U   // Error while DMA transfer                                      
#define SDMMC_ERROR_TIMEOUT                  0x80000000U   // Timeout error                                                 

// Masks for errors Card Status R1 (OCR Register) 
#define SDMMC_OCR_ADDR_OUT_OF_RANGE        0x80000000U
#define SDMMC_OCR_ADDR_MISALIGNED          0x40000000U
#define SDMMC_OCR_BLOCK_LEN_ERR            0x20000000U
#define SDMMC_OCR_ERASE_SEQ_ERR            0x10000000U
#define SDMMC_OCR_BAD_ERASE_PARAM          0x08000000U
#define SDMMC_OCR_WRITE_PROT_VIOLATION     0x04000000U
#define SDMMC_OCR_LOCK_UNLOCK_FAILED       0x01000000U
#define SDMMC_OCR_COM_CRC_FAILED           0x00800000U
#define SDMMC_OCR_ILLEGAL_CMD              0x00400000U
#define SDMMC_OCR_CARD_ECC_FAILED          0x00200000U
#define SDMMC_OCR_CC_ERROR                 0x00100000U
#define SDMMC_OCR_GENERAL_UNKNOWN_ERROR    0x00080000U
#define SDMMC_OCR_STREAM_READ_UNDERRUN     0x00040000U
#define SDMMC_OCR_STREAM_WRITE_OVERRUN     0x00020000U
#define SDMMC_OCR_CID_CSD_OVERWRITE        0x00010000U
#define SDMMC_OCR_WP_ERASE_SKIP            0x00008000U
#define SDMMC_OCR_CARD_ECC_DISABLED        0x00004000U
#define SDMMC_OCR_ERASE_RESET              0x00002000U
#define SDMMC_OCR_AKE_SEQ_ERROR            0x00000008U
#define SDMMC_OCR_ERRORBITS                0xFDFFE008U

//  Masks for R6 Response 
#define SDMMC_R6_GENERAL_UNKNOWN_ERROR     0x00002000U
#define SDMMC_R6_ILLEGAL_CMD               0x00004000U
#define SDMMC_R6_COM_CRC_FAILED            0x00008000U

#define SDMMC_VOLTAGE_WINDOW_SD            0x80100000U
#define SDMMC_HIGH_CAPACITY                0x40000000U
#define SDMMC_STD_CAPACITY                 0x00000000U
#define SDMMC_CHECK_PATTERN                0x000001AAU

#define SDMMC_MAX_VOLT_TRIAL               0x0000FFFFU
    
#define SDMMC_MAX_TRIAL                    0x0000FFFFU
    
#define SDMMC_ALLZERO                      0x00000000U

#define SDMMC_WIDE_BUS_SUPPORT             0x00040000U
#define SDMMC_SINGLE_BUS_SUPPORT           0x00010000U
#define SDMMC_CARD_LOCKED                  0x02000000U

#define SDMMC_DATATIMEOUT                  0xFFFFFFFFU//20000//0xFFFFFFFFU, Modify 2018.6.28

#define SDMMC_0TO7BITS                     0x000000FFU
#define SDMMC_8TO15BITS                    0x0000FF00U
#define SDMMC_16TO23BITS                   0x00FF0000U
#define SDMMC_24TO31BITS                   0xFF000000U
#define SDMMC_MAX_DATA_LENGTH              0x01FFFFFFU

#define SDMMC_HALFFIFO                     0x00000008U
#define SDMMC_HALFFIFOBYTES                0x00000020U

// Command Class supported
#define SDIO_CCCC_ERASE                   0x00000020U
#define SDIO_CMDTIMEOUT                   500000//5000U        // Command send and response timeout 
#define SDIO_MAXERASETIMEOUT              63000U       // Max erase Timeout 63 s            

// SDIO_LL_Response_Registers Response Register
#define SDIO_RESP1                          0x00000000U
#define SDIO_RESP2                          0x00000004U
#define SDIO_RESP3                          0x00000008U
#define SDIO_RESP4                          0x0000000CU

// SDIO_LL_Data_Block_Size  Data Block Size
#define SDIO_DATABLOCK_SIZE_1B               0x00000000U
#define SDIO_DATABLOCK_SIZE_2B               SDIO_DCTRL_DBLOCKSIZE_0
#define SDIO_DATABLOCK_SIZE_4B               SDIO_DCTRL_DBLOCKSIZE_1
#define SDIO_DATABLOCK_SIZE_8B               (SDIO_DCTRL_DBLOCKSIZE_0|SDIO_DCTRL_DBLOCKSIZE_1)
#define SDIO_DATABLOCK_SIZE_16B              SDIO_DCTRL_DBLOCKSIZE_2
#define SDIO_DATABLOCK_SIZE_32B              (SDIO_DCTRL_DBLOCKSIZE_0|SDIO_DCTRL_DBLOCKSIZE_2)
#define SDIO_DATABLOCK_SIZE_64B              (SDIO_DCTRL_DBLOCKSIZE_1|SDIO_DCTRL_DBLOCKSIZE_2)
#define SDIO_DATABLOCK_SIZE_128B             (SDIO_DCTRL_DBLOCKSIZE_0|SDIO_DCTRL_DBLOCKSIZE_1|SDIO_DCTRL_DBLOCKSIZE_2)
#define SDIO_DATABLOCK_SIZE_256B             SDIO_DCTRL_DBLOCKSIZE_3
#define SDIO_DATABLOCK_SIZE_512B             (SDIO_DCTRL_DBLOCKSIZE_0|SDIO_DCTRL_DBLOCKSIZE_3)
#define SDIO_DATABLOCK_SIZE_1024B            (SDIO_DCTRL_DBLOCKSIZE_1|SDIO_DCTRL_DBLOCKSIZE_3)
#define SDIO_DATABLOCK_SIZE_2048B            (SDIO_DCTRL_DBLOCKSIZE_0|SDIO_DCTRL_DBLOCKSIZE_1|SDIO_DCTRL_DBLOCKSIZE_3) 
#define SDIO_DATABLOCK_SIZE_4096B            (SDIO_DCTRL_DBLOCKSIZE_2|SDIO_DCTRL_DBLOCKSIZE_3)
#define SDIO_DATABLOCK_SIZE_8192B            (SDIO_DCTRL_DBLOCKSIZE_0|SDIO_DCTRL_DBLOCKSIZE_2|SDIO_DCTRL_DBLOCKSIZE_3)
#define SDIO_DATABLOCK_SIZE_16384B           (SDIO_DCTRL_DBLOCKSIZE_1|SDIO_DCTRL_DBLOCKSIZE_2|SDIO_DCTRL_DBLOCKSIZE_3)



// SDIO_LL_Transfer_Direction Transfer Direction
#define SDIO_TRANSFER_DIR_TO_CARD            0x00000000U
#define SDIO_TRANSFER_DIR_TO_SDIO            SDIO_DCTRL_DTDIR

// SDIO_LL_Transfer_Type Transfer Type
#define SDIO_TRANSFER_MODE_BLOCK             0x00000000U
#define SDIO_TRANSFER_MODE_STREAM            SDIO_DCTRL_DTMODE

// SDIO_LL_DPSM_State DPSM State
#define SDIO_DPSM_DISABLE                    0x00000000U
#define SDIO_DPSM_ENABLE                     SDIO_DCTRL_DTEN

  
// SDIO_LL_Read_Wait_Mode Read Wait Mode
#define SDIO_READ_WAIT_MODE_DATA2                0x00000000U
#define SDIO_READ_WAIT_MODE_CLK                  (SDIO_DCTRL_RWMOD)

// SDIO_LL_Interrupt_sources Interrupt Sources
#define SDIO_IT_CCRCFAIL                    SDIO_STA_CCRCFAIL
#define SDIO_IT_DCRCFAIL                    SDIO_STA_DCRCFAIL
#define SDIO_IT_CTIMEOUT                    SDIO_STA_CTIMEOUT
#define SDIO_IT_DTIMEOUT                    SDIO_STA_DTIMEOUT
#define SDIO_IT_TXUNDERR                    SDIO_STA_TXUNDERR
#define SDIO_IT_RXOVERR                     SDIO_STA_RXOVERR
#define SDIO_IT_CMDREND                     SDIO_STA_CMDREND
#define SDIO_IT_CMDSENT                     SDIO_STA_CMDSENT
#define SDIO_IT_DATAEND                     SDIO_STA_DATAEND
#define SDIO_IT_STBITERR                    SDIO_STA_STBITERR
#define SDIO_IT_DBCKEND                     SDIO_STA_DBCKEND
#define SDIO_IT_CMDACT                      SDIO_STA_CMDACT
#define SDIO_IT_TXACT                       SDIO_STA_TXACT
#define SDIO_IT_RXACT                       SDIO_STA_RXACT
#define SDIO_IT_TXFIFOHE                    SDIO_STA_TXFIFOHE
#define SDIO_IT_RXFIFOHF                    SDIO_STA_RXFIFOHF
#define SDIO_IT_TXFIFOF                     SDIO_STA_TXFIFOF
#define SDIO_IT_RXFIFOF                     SDIO_STA_RXFIFOF
#define SDIO_IT_TXFIFOE                     SDIO_STA_TXFIFOE
#define SDIO_IT_RXFIFOE                     SDIO_STA_RXFIFOE
#define SDIO_IT_TXDAVL                      SDIO_STA_TXDAVL
#define SDIO_IT_RXDAVL                      SDIO_STA_RXDAVL
#define SDIO_IT_SDIOIT                      SDIO_STA_SDIOIT
#define SDIO_IT_CEATAEND                    SDIO_STA_CEATAEND

// SDIO_LL_Flags Flags
#define SDIO_FLAG_CCRCFAIL                  SDIO_STA_CCRCFAIL
#define SDIO_FLAG_DCRCFAIL                  SDIO_STA_DCRCFAIL
#define SDIO_FLAG_CTIMEOUT                  SDIO_STA_CTIMEOUT
#define SDIO_FLAG_DTIMEOUT                  SDIO_STA_DTIMEOUT
#define SDIO_FLAG_TXUNDERR                  SDIO_STA_TXUNDERR
#define SDIO_FLAG_RXOVERR                   SDIO_STA_RXOVERR
#define SDIO_FLAG_CMDREND                   SDIO_STA_CMDREND
#define SDIO_FLAG_CMDSENT                   SDIO_STA_CMDSENT
#define SDIO_FLAG_DATAEND                   SDIO_STA_DATAEND
#define SDIO_FLAG_STBITERR                  SDIO_STA_STBITERR
#define SDIO_FLAG_DBCKEND                   SDIO_STA_DBCKEND
#define SDIO_FLAG_CMDACT                    SDIO_STA_CMDACT
#define SDIO_FLAG_TXACT                     SDIO_STA_TXACT
#define SDIO_FLAG_RXACT                     SDIO_STA_RXACT
#define SDIO_FLAG_TXFIFOHE                  SDIO_STA_TXFIFOHE
#define SDIO_FLAG_RXFIFOHF                  SDIO_STA_RXFIFOHF
#define SDIO_FLAG_TXFIFOF                   SDIO_STA_TXFIFOF
#define SDIO_FLAG_RXFIFOF                   SDIO_STA_RXFIFOF
#define SDIO_FLAG_TXFIFOE                   SDIO_STA_TXFIFOE
#define SDIO_FLAG_RXFIFOE                   SDIO_STA_RXFIFOE
#define SDIO_FLAG_TXDAVL                    SDIO_STA_TXDAVL
#define SDIO_FLAG_RXDAVL                    SDIO_STA_RXDAVL
#define SDIO_FLAG_SDIOIT                    SDIO_STA_SDIOIT
#define SDIO_FLAG_CEATAEND                  SDIO_STA_CEATAEND
#define SDIO_STATIC_FLAGS                   ((uint32_t)(SDIO_FLAG_CCRCFAIL | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_CTIMEOUT |\
                                                         SDIO_FLAG_DTIMEOUT | SDIO_FLAG_TXUNDERR | SDIO_FLAG_RXOVERR  |\
                                                         SDIO_FLAG_CMDREND  | SDIO_FLAG_CMDSENT  | SDIO_FLAG_DATAEND  |\
                                                         SDIO_FLAG_DBCKEND))  


// SDIO控制命令 
#define SDIO_CMD_CLKEN               ((INT8U)100)     // SDIO时钟控制: Para=0, 关闭时钟; Para=1, 使能时钟;                                                                
#define SDIO_CMD_PWREN               ((INT8U)101)     // SDIO电源控制: Para=0, 关闭电源, 卡的时钟关闭; Para=1, 上电状态, 卡的时钟开启;
#define SDIO_CMD_GET_RESP            ((INT8U)102)     // 读取RESP1(Para=0)或RESP2(Para=2)或RESP3(Para=3)或RESP4(Para=4)寄存器;
#define SDIO_CMD_GET_PWRSTA          ((INT8U)103)     // 读取SDIO电源状态: 返回: 0,Power OFF; 2,Power UP; 3,Power ON; 
#define SDIO_CMD_CLK_DIV             ((INT8U)104)     // SDIO时钟分频系数: 0-255, 0表示不分频 
#define SDIO_CMD_WIDBUS              ((INT8U)105)     // 设置SDIO总线宽度: 1或者4或者8 



// SDMMC Commands Index 
#define SDMMC_CMD_GO_IDLE_STATE                       ((INT8U)0)   // Resets the SD memory card.                                                               
#define SDMMC_CMD_SEND_OP_COND                        ((INT8U)1)   // Sends host capacity support information and activates the card's initialization process. 
#define SDMMC_CMD_ALL_SEND_CID                        ((INT8U)2)   // Asks any card connected to the host to send the CID numbers on the CMD line.             
#define SDMMC_CMD_SET_REL_ADDR                        ((INT8U)3)   // Asks the card to publish a new relative address (RCA).                                   
#define SDMMC_CMD_SET_DSR                             ((INT8U)4)   // Programs the DSR of all cards.                                                           
#define SDMMC_CMD_SDMMC_SEN_OP_COND                   ((INT8U)5)   // Sends host capacity support information (HCS) and asks the accessed card to send its 
                                                                   //    operating condition register (OCR) content in the response on the CMD line.                  
#define SDMMC_CMD_HS_SWITCH                           ((INT8U)6)   // Checks switchable function (mode 0) and switch card function (mode 1).                   
#define SDMMC_CMD_SEL_DESEL_CARD                      ((INT8U)7)   // Selects the card by its own relative address and gets deselected by any other address    
#define SDMMC_CMD_HS_SEND_EXT_CSD                     ((INT8U)8)   // Sends SD Memory Card interface condition, which includes host supply voltage information 
                                                                   //    and asks the card whether card supports voltage.                                             
#define SDMMC_CMD_SEND_CSD                            ((INT8U)9)   // Addressed card sends its card specific data (CSD) on the CMD line.                       
#define SDMMC_CMD_SEND_CID                            ((INT8U)10)  // Addressed card sends its card identification (CID) on the CMD line.                      
#define SDMMC_CMD_READ_DAT_UNTIL_STOP                 ((INT8U)11)  // SD card doesn't support it.                                                              
#define SDMMC_CMD_STOP_TRANSMISSION                   ((INT8U)12)  // Forces the card to stop transmission.                                                    
#define SDMMC_CMD_SEND_STATUS                         ((INT8U)13)  // Addressed card sends its status register.                                                
#define SDMMC_CMD_HS_BUSTEST_READ                     ((INT8U)14)  // Reserved                                                                                 
#define SDMMC_CMD_GO_INACTIVE_STATE                   ((INT8U)15)  // Sends an addressed card into the inactive state.                                         
#define SDMMC_CMD_SET_BLOCKLEN                        ((INT8U)16)  // Sets the block length (in bytes for SDSC) for all following block commands 
                                                                   //        (read, write, lock). Default block length is fixed to 512 Bytes. Not effective 
                                                                   //        for SDHS and SDXC.                                                                       
#define SDMMC_CMD_READ_SINGLE_BLOCK                   ((INT8U)17)  // Reads single block of size selected by SET_BLOCKLEN in case of SDSC, and a block of 
                                                                   //        fixed 512 bytes in case of SDHC and SDXC.                                                
#define SDMMC_CMD_READ_MULT_BLOCK                     ((INT8U)18)  // Continuously transfers data blocks from card to host until interrupted by 
                                                                   //        STOP_TRANSMISSION command.                                                               
#define SDMMC_CMD_HS_BUSTEST_WRITE                    ((INT8U)19)  // 64 bytes tuning pattern is sent for SDR50 and SDR104.                                    
#define SDMMC_CMD_WRITE_DAT_UNTIL_STOP                ((INT8U)20)  // Speed class control command.                                                             
#define SDMMC_CMD_SET_BLOCK_COUNT                     ((INT8U)23)  // Specify block count for CMD18 and CMD25.                                                 
#define SDMMC_CMD_WRITE_SINGLE_BLOCK                  ((INT8U)24)  // Writes single block of size selected by SET_BLOCKLEN in case of SDSC, and a block of 
                                                                   //        fixed 512 bytes in case of SDHC and SDXC.                                                
#define SDMMC_CMD_WRITE_MULT_BLOCK                    ((INT8U)25)  // Continuously writes blocks of data until a STOP_TRANSMISSION follows.                    
#define SDMMC_CMD_PROG_CID                            ((INT8U)26)  // Reserved for manufacturers.                                                              
#define SDMMC_CMD_PROG_CSD                            ((INT8U)27)  // Programming of the programmable bits of the CSD.                                         
#define SDMMC_CMD_SET_WRITE_PROT                      ((INT8U)28)  // Sets the write protection bit of the addressed group.                                    
#define SDMMC_CMD_CLR_WRITE_PROT                      ((INT8U)29)  // Clears the write protection bit of the addressed group.                                  
#define SDMMC_CMD_SEND_WRITE_PROT                     ((INT8U)30)  // Asks the card to send the status of the write protection bits.                           
#define SDMMC_CMD_SD_ERASE_GRP_START                  ((INT8U)32)  // Sets the address of the first write block to be erased. (For SD card only).              
#define SDMMC_CMD_SD_ERASE_GRP_END                    ((INT8U)33)  // Sets the address of the last write block of the continuous range to be erased.           
#define SDMMC_CMD_ERASE_GRP_START                     ((INT8U)35)  // Sets the address of the first write block to be erased. Reserved for each command 
                                                                   //        system set by switch function command (CMD6).                                            
#define SDMMC_CMD_ERASE_GRP_END                       ((INT8U)36)  // Sets the address of the last write block of the continuous range to be erased. 
                                                                   //        Reserved for each command system set by switch function command (CMD6).                  
#define SDMMC_CMD_ERASE                               ((INT8U)38)  // Reserved for SD security applications.                                                   
#define SDMMC_CMD_FAST_IO                             ((INT8U)39)  // SD card doesn't support it (Reserved).                                                   
#define SDMMC_CMD_GO_IRQ_STATE                        ((INT8U)40)  // SD card doesn't support it (Reserved).                                                   
#define SDMMC_CMD_LOCK_UNLOCK                         ((INT8U)42)  // Sets/resets the password or lock/unlock the card. The size of the data block is set by 
                                                                   //       the SET_BLOCK_LEN command.                                                               
#define SDMMC_CMD_APP_CMD                             ((INT8U)55)  // Indicates to the card that the next command is an application specific command rather 
                                                                   //        than a standard command.                                                                 
#define SDMMC_CMD_GEN_CMD                             ((INT8U)56)  // Used either to transfer a data block to the card or to get a data block from the card 
                                                                   //        for general purpose/application specific commands.                                       
#define SDMMC_CMD_NO_CMD                              ((INT8U)64)  // No command                                                                                

// Following commands are SD Card Specific commands.
// SDMMC_APP_CMD should be sent before sending these commands. 
#define SDMMC_CMD_APP_SD_SET_BUSWIDTH                 ((INT8U)6)   // (ACMD6) Defines the data bus width to be used for data transfer. The allowed data bus 
                                                                   //         widths are given in SCR register.                                                       
#define SDMMC_CMD_SD_APP_STATUS                       ((INT8U)13)  // (ACMD13) Sends the SD status.                                                            
#define SDMMC_CMD_SD_APP_SEND_NUM_WRITE_BLOCKS        ((INT8U)22)  // (ACMD22) Sends the number of the written (without errors) write blocks. Responds with 
                                                                   //        32bit+CRC data block.                                                                    
#define SDMMC_CMD_SD_APP_OP_COND                      ((INT8U)41)  // (ACMD41) Sends host capacity support information (HCS) and asks the accessed card to 
                                                                   //        send its operating condition register (OCR) content in the response on the CMD line.     
#define SDMMC_CMD_SD_APP_SET_CLR_CARD_DETECT          ((INT8U)42)  // (ACMD42) Connect/Disconnect the 50 KOhm pull-up resistor on CD/DAT3 (pin 1) of the card  
#define SDMMC_CMD_SD_APP_SEND_SCR                     ((INT8U)51)  // Reads the SD Configuration Register (SCR).                                               
#define SDMMC_CMD_SDMMC_RW_DIRECT                     ((INT8U)52)  // For SD I/O card only, reserved for security specification.                               
#define SDMMC_CMD_SDMMC_RW_EXTENDED                   ((INT8U)53)  // For SD I/O card only, reserved for security specification.                               

// Following commands are SD Card Specific security commands.
// SDMMC_CMD_APP_CMD should be sent before sending these commands. 
#define SDMMC_CMD_SD_APP_GET_MKB                      ((uint8_t)43)
#define SDMMC_CMD_SD_APP_GET_MID                      ((uint8_t)44)
#define SDMMC_CMD_SD_APP_SET_CER_RN1                  ((uint8_t)45)
#define SDMMC_CMD_SD_APP_GET_CER_RN2                  ((uint8_t)46)
#define SDMMC_CMD_SD_APP_SET_CER_RES2                 ((uint8_t)47)
#define SDMMC_CMD_SD_APP_GET_CER_RES1                 ((uint8_t)48)
#define SDMMC_CMD_SD_APP_SECURE_READ_MULTIPLE_BLOCK   ((uint8_t)18)
#define SDMMC_CMD_SD_APP_SECURE_WRITE_MULTIPLE_BLOCK  ((uint8_t)25)
#define SDMMC_CMD_SD_APP_SECURE_ERASE                 ((uint8_t)38)
#define SDMMC_CMD_SD_APP_CHANGE_SECURE_AREA           ((uint8_t)49)
#define SDMMC_CMD_SD_APP_SECURE_WRITE_MKB             ((uint8_t)48)
/*************************************************************************************/
//
// 				    SPI控制器硬件驱动函数定义
//
/*************************************************************************************/

/***********************************************************************************
* Function: SDIO_Init;
*
* Description: SDIO初始化函数;
* 
* Input:  id, SDIO识别号(SDIO_ID);
*         *pPara, SDIO初始化参数指针;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   初始化完成SDIO已经使能开始工作，无需调用SDIO_Ctrl再次使能;
************************************************************************************/
INT32S SDIO_Init(INT8U id, SDIO_PARA *pPara);

/***********************************************************************************
* Function: SDIO_Read;
*
* Description: SDIO总线读数据函数;
*              
* Input:  id, SDIO识别号(SDIO_ID);
*         *p, 读出数据存储的地址指针; 
*         len,要读出数据长度;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S SDIO_Read(INT8U id, INT8U *pData, INT32U BlockAdd, INT32U NumberOfBlocks, INT32U Timeout);

/***********************************************************************************
* Function: SDIO_Write;
*
* Description: SDIO总线写数据函数;
*              
* Input:  id, SDIO识别号(SDIO_ID);
*         *p, 写入数据的存储的地址指针; 
*         len,要写入数据长度;
*
* Output: none;
*
* Return: 只能返回ERR_TRUE;
*
* Note:   none;
************************************************************************************/
INT32S SDIO_Write(INT8U id, INT8U *pData, INT32U BlockAdd, INT32U NumberOfBlocks, INT32U Timeout);

///***********************************************************************************
//* Function: SPI_ReadWriteByte;
//*
//* Description: SPI总线读写一个字节数据函数;
//*              
//* Input:  id,SPI识别号(SPI1_ID,SPI2_ID,SPI3_ID);
//*         val, 写入的数据; 
//*
//* Output: none;
//*
//* Return: 返回读出的数据;
//*
//* Note:   none;
//************************************************************************************/


/***********************************************************************************
* Function: SDIO_Ctrl;
*
* Description: SDIO命令控制;
* 
* Input:  id, SDIO识别号(SDIO_ID);
*         Cmd,  SPI控制命令：
*               CMD_SDIO_ENA：   使能SPI外设, Para为0
*　　　　　　　 CMD_SDIO_DIS：   使能SPI外设, Para为0　　　　　　　　　　
*               CMD_SDIO_DIVCLK：设置时钟分频系数, Para为SPI_DIVCLK_2~SPI_DIVCLK_256
*               CMD_SDIO_CKMODE：时钟相位模式，Para为：SPI_CKMODE0~SPI_CKMODE3
*               CMD_SDIO_RST：   复位SPI寄存器为初始状态, Para为0
*               CMD_SDIO_CLOSE： 关闭SPI时钟,也就是关闭SPI功能,可以省电, Para为0 
*         Para, SPI命令控制参数;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S SDIO_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
  
#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/



