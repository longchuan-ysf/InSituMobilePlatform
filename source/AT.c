/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: AT.c
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ�����ATָ���;
*
* Others: none;
*
* Function List:
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/

/************************************************************************************/
// ����˵��
/************************************************************************************/
/*
 
  
*/

/************************************************************************************/
// �����ⲿͷ�ļ�
#include "config.h"	 
#include "UserVars.h"
#include "STM32Fxxx.h"
#include "APP_Init.h"
#include "AT.h"			
/************************************************************************************/
#if (AT_EN > 0)
/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
// ֻ���豸��Ϣָ��
const INT8U AT_VER[] = {"AT+VER=?\r\n"};           //V, ��ȡATָ��汾
const INT8U AT_MODEL[] = {"AT+MODEL=?\r\n"};       //M, ��ȡ�豸�ͺ�
const INT8U AT_NAME[] = {"AT+NAME=?\r\n"};         //N, ��ȡ�豸����
const INT8U AT_HWVER[] = {"AT+HWVER=?\r\n"};       //H, ��ȡӲ���汾
const INT8U AT_SWVER[] = {"AT+SWVER=?\r\n"};       //S, ��ȡ����汾
const INT8U AT_LIBVER[] = {"AT+LIBVER=?\r\n"};     //L, ��ȡ������汾
const INT8U AT_BIN[] = {"AT+BIN=?\r\n"};         //B, ��ȡ�̼���Ϣ

// ����ָ��
const INT8U AT_RESET[] = {"AT+RESET\r\n"};        //R, ��λ�豸  
const INT8U AT_SAVE[] = {"AT+SAVE\r\n"};          //S, �洢����  
const INT8U AT_DEFAULT[] = {"AT+DEFAULT\r\n"};    //D, �ָ���������  
const INT8U AT_DEBUG_ON[] = {"AT+DEBUG=ON"};      //D, ʹ�ܵ�����Ϣ���
const INT8U AT_DEBUG_OFF[] = {"AT+DEBUG=OFF"};    //D, �رյ�����Ϣ���

const INT8U AT_IP[] = {"AT+IP="};          //A, ����IP����
const INT8U AT_PORT[] = {"AT+PORT="};      //P, ���ض˿�����
const INT8U AT_GWIP[] = {"AT+GWIP="};      //G, ����IP����
const INT8U AT_DSCIP[] = {"AT+DSCIP="};    //D, ������IP����
const INT8U AT_DSCPORT[] = {"AT+DSCPORT="};//D, �������˿�����
const INT8U AT_SUBMASK[] = {"AT+SUBMASK="};//S, ������������
const INT8U AT_MAC[] = {"AT+MAC="};        //M, MAC��ַ����
const INT8U AT_LINK[] = {"AT+LINK="};      //L, ���ӶϿ�����������
const INT8U AT_SERVER[] = {"AT+SERVER="};  //S, �����رշ���������

// ��д����ָ��
const INT8U AT_DI_M0[] = {"AT+DI=M0,"};        //D, DI����ָ��
const INT8U AT_DI_RM[] = {"AT+DI=M?\r\n"};    //D, ��ȡDI����ָ��

const INT8U AT_DI[] = {"AT+DI"};              //D, DI��ȡָ��
const INT8U AT_DI_ALL[] = {"AT+DI=?\r\n"};    //D, DI��ȡָ��

const INT8U AT_DO_M[] = {"AT+DO=M0,"};        //D, DO����ָ��
const INT8U AT_DO_RM[] = {"AT+DO=M?\r\n"};    //D, ��ȡDO����ָ��
const INT8U AT_DO[] = {"AT+DO"};              //D, DO����ָ��
const INT8U AT_DO_R_ALL[] = {"AT+DO=?\r\n"};  //D, DO����ָ��
const INT8U AT_DO_W_ALL[] = {"AT+DO="};  //D, DO����ָ��

const INT8U AT_AI_M[] = {"AT+AI=M0,"};        //A, AI����ָ��
const INT8U AT_AI_RM[] = {"AT+AI=M?\r\n"};    //A, ��ȡAI����ָ��
const INT8U AT_AI[] = {"AT+AI"};              //A, AI��ȡָ��
const INT8U AT_AI_ALL[] = {"AT+AI=?\r\n"};    //A, AI��ȡָ��

const INT8U AT_AO_M[] = {"AT+AO=M"};          //A, AO����ָ��
const INT8U AT_AO_RM[] = {"AT+AO=M?\r\n"};    //A, ��ȡAO����ָ��

const INT8U AT_AO_R_ALL[] = {"AT+AO=?\r\n"};  //A, AO����ָ��
const INT8U AT_AO1_R[] = {"AT+AO1=?\r\n"};    //A, AO����ָ��
const INT8U AT_AO2_R[] = {"AT+AO2=?\r\n"};    //A, AO����ָ��

const INT8U AT_AO_W[] = {"AT+AO=2,"};  //A, AO����ָ��
const INT8U AT_AO1_W[] = {"AT+AO1="};  //A, AO����ָ��
const INT8U AT_AO2_W[] = {"AT+AO2="};  //A, AO����ָ��

const INT8U AT_ALARM[] = {"AT+ALARM="};  //A, ALARM����ָ��

const INT8U AT_PWM_M[] = {"AT+PWM=M"};        //P, PWM����ָ��
const INT8U AT_PWM_RM[] = {"AT+PWM=M?\r\n"};  //P, ��ȡPWM����ָ��
const INT8U AT_PWM[] = {"AT+PWM"};            //P, PWM����ָ��

const INT8U AT_FCLK[] = {"AT+FCLK"};          //F, FCLK��ȡָ��

const INT8U AT_UART[] = {"AT+UART"};          //U, UART����ָ�� ?
const INT8U AT_CAN[] = {"AT+CAN"};            //C, CAN����ָ��  ?
const INT8U AT_NET[] = {"AT+NET="};            //N, NET����ָ��  ?
const INT8U AT_RTC_R[] = {"AT+RTC=?\r\n"};    //R, RTC����ָ��
const INT8U AT_RTC_W[] = {"AT+RTC=20"};       //R, RTC����ָ��

const INT8U AT_EEPROM[] = {"AT+EEPROM="};          //E, EEPROM����ָ��     ?
const INT8U AT_SPIFLASH[] = {"AT+SPIFLASH="};      //S, SPIFLASH����ָ��   ?
const INT8U AT_NFLASH[] = {"AT+NFLASH=?\r\n"};     //N, NAND FLASH״̬��ȡָ��
const INT8U AT_SRAM[] = {"AT+SRAM=?\r\n"};         //S, ��չSRAM״̬��ȡָ��
const INT8U AT_SD[] = {"AT+SD=?\r\n"};             //S, SD״̬��ȡָ��
const INT8U AT_UDISK[] = {"AT+UDISK=?\r\n"};       //U, U��״̬��ȡָ��
const INT8U AT_USB[] = {"AT+USB=?\r\n"};           //U, USB����״̬��ȡָ��
const INT8U AT_FILE[] = {"AT+FILE="};              //F, �ļ�����ָ��  ?
const INT8U AT_SW[] = {"AT+SW="};                  //S, ���뿪�ض�ȡָ��
  

INT32S AT_CmdProc(INT8U *pMEM, INT16U len)   
{
    INT32S flag, rst;
	INT16U m, n, i;
	INT8U *p, *pBuf, val, val1, val2, val3, id;
	INT8U cmd;
	INT32U baud, addr, k;
    RTC_TIME rtc;
    CAN_TX_MSG CanTx; // CAN��������
    
    rst = ERR_FALSE;
    flag = MatchStr(pMEM, (INT8U *)"AT+", 1, &n);
	if(flag==ERR_TRUE)
	{
		cmd = *(pMEM+n);
	    switch (cmd)
		{
            //----------��һ���ַ�: D--------------------------------------
			case 'D':
                // AT+DI=? 
                flag = MatchStr(pMEM, (INT8U *)AT_DI_ALL, 1, &n);
				if(flag==ERR_TRUE)
				{
					// ���´���ָ��
					printf("AT+DI=%d,", DI_NUM);   // ��ӡDIֵ
                    for(i=0; i<DI_NUM; i++)
                    {
                        if (UserVars.DI&(0x00000001<<i))
                        {    
                            printf("1"); 
                        }
                        else
                        {
                            printf("0"); 
                        }
                    }
                    printf("\r\n");
                    rst = ERR_TRUE;        
                    break; 
                }
                
            
				flag = MatchStr(pMEM, (INT8U *)AT_DI, 1, &n);
				if(flag==ERR_TRUE)
				{
                    m = len - n;
					p = pMEM + n;

					val1 = *(p+m-2);
					val2 = *(p+m-1);
                    val3 = *(p+m-3);
                    val = *(p+m-4);					
                    if ((val1=='\r')&&(val2=='\n')&&(val=='=')&&(val3 =='?'))
					{
                         p = pMEM + n;
                         val1 = *p;
					     val2 = *(p+1);
                         if ((val1>='0')&&(val1<='9')) 
                         {
                            k = val1 - '0';
                            if ((val2>='0')&&(val2<='9'))
                            {
                                k *= 10;
                                k += val2 - '0';
                            }
                            // ��ȡDIֵ                            
                            if (UserVars.DI_P&(0x00000001<<(k-1)))
                            {
                                printf("AT+DI%d=1\r\n", k);
                            }
                            else
                            {
                                printf("AT+DI%d=0\r\n", k);
                            }    
                            rst = ERR_TRUE;        
                            break; 
                         }
					}	
                }
                
                
                // DI����: AT+DI=M0,100,3000
                flag = MatchStr(pMEM, (INT8U *)AT_DI_M0, 1, &n);
				if(flag==ERR_TRUE)
				{
                    UserVars.Para.DI.Mode = 0;
                    m = len - n;
					p = pMEM + n;
                    val = *p++;
                    k=0;
                    while ((val>='0')&&(val<='9'))
                    {
                        k *= 10;
                        k += val - '0';
                        val = *p++;
                    }                        
                    if (val==',')
                    {
                        UserVars.Para.DI.t1 = k;
                        val = *p++;
                        k=0;
                        while ((val>='0')&&(val<='9'))
                        {
                            k *= 10;
                            k += val - '0';
                            val = *p++;
                        }                        
                        if (val=='\r')
                        {
                            UserVars.Para.DI.t2 = k;
                            if (UserVars.Para.DI.t2 > 0)
                            {    
                                UserVars.Para.ATFlag |= AT_DI_FLAG;
                            }
                            else
                            {
                                UserVars.Para.ATFlag &= ~AT_DI_FLAG;
                            }
                            printf("AT+DI=OK\r\n");
                            rst = ERR_TRUE;        
                            break; 
                        }
                    }
                    printf("AT+DI=ERROR\r\n");
                    rst = ERR_FALSE;
                    break;                    
                }
                
                // ��ȡDI����: AT+DI=M?
                flag = MatchStr(pMEM, (INT8U *)AT_DI_RM, 1, &n);
				if(flag==ERR_TRUE)
				{
                    printf("AT+DI=M0,%d,%d\r\n",UserVars.Para.DI.t1,UserVars.Para.DI.t2);
                    rst = ERR_TRUE;        
                    break;              
                } 
                // AT+DO=?
                flag = MatchStr(pMEM, (INT8U *)AT_DO_R_ALL, 1, &n);
				if(flag==ERR_TRUE)
				{
					// ��ȡ����DOֵ
                    printf("AT+DO=%d,", DO_NUM);   // ��ӡDOֵ
                    for(i=0; i<DO_NUM; i++)
                    {
                        if (UserVars.DO&(0x00000001<<i))
                        {    
                            printf("1"); 
                        }
                        else
                        {
                            printf("0"); 
                        }
                    }
                    printf("\r\n");
                    rst = ERR_TRUE;        
                    break; 
                }
                
                // AT+DO=8,01101111
                flag = MatchStr(pMEM, (INT8U *)AT_DO_W_ALL, 1, &n);
				if(flag==ERR_TRUE)
				{
					m = len - n;
					p = pMEM + n;

					val1 = *(p+m-2);
					val2 = *(p+m-1);
                    if ((val1=='\r')&&(val2=='\n'))
					{
                         p = pMEM + n;
                         val1 = *p;
					     val2 = *(p+1);
                         val3 = *(p+2);
                         if ((val1>='0')&&(val1<='9')) 
                         {
                            k = val1 - '0';
                            p++; 
                            if ((val2>='0')&&(val2<='9'))
                            {
                                k *= 10;
                                k += val2 - '0';
                                p++;
                            }                            
                            if (*p==',')
                            {
                                p++;
                                for (i=0; i<k; i++)
                                {
                                    val = *p++;
                                    if (val == '0')
                                    {
                                        UserVars.DO &= ~(0x00000001<<i);
                                    }
                                    else
                                    {
                                        UserVars.DO |= 0x00000001<<i;
                                    }                                        
                                }
                                //UserVars.Para.DO.Mode = AT_MODE_START; // ��������DO���
                                printf("AT+DO=OK\r\n");
                                rst = ERR_TRUE;        
                                break;      
                            }
                         }
					}
                 }
                
                // AT+DO2=? �� AT+DO2=1
                flag = MatchStr(pMEM, (INT8U *)AT_DO, 1, &n);
				if(flag==ERR_TRUE)
				{
                    m = len - n;
					p = pMEM + n;

					val1 = *(p+m-2);
					val2 = *(p+m-1);
                    val3 = *(p+m-3);
                    val = *(p+m-4);					
                    if ((val1=='\r')&&(val2=='\n')&&(val=='=')&&((val3 =='?')||(val3 =='0')||(val3 =='1'))) // AT+DO2=? �� AT+DO2=1
					{
                         //p = pMEM + n;
                         val1 = *p;
					     val2 = *(p+1);
                         if ((val1>='0')&&(val1<='9')) 
                         {
                            k = val1 - '0';
                            if ((val2>='0')&&(val2<='9'))
                            {
                                k *= 10;
                                k += val2 - '0';
                                
                            }                            
                            if (val3 =='?') // AT+DO2=?
                            {    
                                // ��ȡDOֵ
                               if (UserVars.DO&(0x00000001<<(k-1)))
                                {
                                    printf("AT+DO%d=1\r\n", k);
                                }
                                else
                                {
                                    printf("AT+DO%d=0\r\n", k);
                                }
                            }     
                            else // AT+DO2=1
                            {
                                if (val3 =='0')
                                {
                                    UserVars.DO &= ~(0x00000001<<(k-1));
                                }
                                else
                                {
                                    UserVars.DO |= 0x00000001<<(k-1);
                                }
                                //UserVars.Para.DO.Mode = AT_MODE_START; // ��������DO���
                                printf("AT+DO=OK\r\n");   
                            } 
                            
                            rst = ERR_TRUE;        
                            break; 
                         }
					}                    
                }
                
                // DO����: AT+DO=M0,100,3000
                flag = MatchStr(pMEM, (INT8U *)AT_DO_M, 1, &n);
				if(flag==ERR_TRUE)
				{
                    //m = len - n;
					p = pMEM + n;
                    val = *p++;
                    k=0;
                    while ((val>='0')&&(val<='9'))
                    {
                        k *= 10;
                        k += val - '0';
                        val = *p++;
                    }                        
                    if (val==',')
                    {
                        UserVars.Para.DO.t1 = k;
                        val = *p++;
                        k=0;
                        while ((val>='0')&&(val<='9'))
                        {
                            k *= 10;
                            k += val - '0';
                            val = *p++;
                        }                        
                        if (val=='\r')
                        {
                            UserVars.Para.DO.t2 = k;
                            if (UserVars.Para.DO.t2 > 0)
                            {    
                                UserVars.Para.ATFlag |= AT_DO_FLAG;
                            }
                            else
                            {
                                UserVars.Para.ATFlag &= ~AT_DO_FLAG;
                            }
                            printf("AT+DO=OK\r\n");
                            rst = ERR_TRUE;        
                            break; 
                        }
                    }
                    printf("AT+DO=ERROR\r\n");
                    rst = ERR_FALSE;
                    break;                    
                }
                
                // ��ȡDO����: AT+DO=M?
                flag = MatchStr(pMEM, (INT8U *)AT_DO_RM, 1, &n);
				if(flag==ERR_TRUE)
				{
                    printf("AT+DO=M0,%d,%d\r\n",UserVars.Para.DO.t1,UserVars.Para.DO.t2);
                    rst = ERR_TRUE;        
                    break;              
                }    
                
                // AT+DEFAULT
                flag = MatchStr(pMEM, (INT8U *)AT_DEFAULT, 1, &n);
				if(flag==ERR_TRUE)
				{
					// ���´���ָ��
                    APP_ParaInit((USER_VARS *)&UserVars.Flag);
                    printf("AT+DEFAULT=OK\r\n");
					rst = ERR_TRUE;        
                    break; 
				} 
                
                // AT+DEBUG=ON
                flag = MatchStr(pMEM, (INT8U *)AT_DEBUG_ON, 1, &n);
				if(flag==ERR_TRUE)
				{
					// ���´���ָ��
                    pMEM += n;
                    rst = ERR_TRUE;
                    if ((pMEM[0] == '\r')&&(pMEM[1] == '\n'))
                    {    
                        UserVars.Para.ATFlag = AT_ALL_FLAG;
                    }
                    else
                    {    
                        if (pMEM[0] == ',')
                        {    
                            if ((pMEM[1] == 'D')&&(pMEM[2] == 'I'))
                            {
                                UserVars.Para.ATFlag |= AT_DI_FLAG;
                            }                        
                            else if ((pMEM[1] == 'D')&&(pMEM[2] == 'O'))
                            {
                                UserVars.Para.ATFlag |= AT_DO_FLAG;
                            }  
                            else if ((pMEM[1] == 'A')&&(pMEM[2] == 'I'))
                            {
                                UserVars.Para.ATFlag |= AT_AI_FLAG;
                            }  
                            else if ((pMEM[1] == 'A')&&(pMEM[2] == 'O'))
                            {
                                UserVars.Para.ATFlag |= AT_AO_FLAG;
                            }  
                            else if ((pMEM[1] == 'P')&&(pMEM[2] == 'W')&&(pMEM[3] == 'M'))
                            {
                                UserVars.Para.ATFlag |= AT_PWM_FLAG;
                            } 
                            else if ((pMEM[1] == 'C')&&(pMEM[2] == 'A')&&(pMEM[3] == 'N'))
                            {
                                UserVars.Para.ATFlag |= AT_CAN_FLAG;
                            } 
                            else if ((pMEM[1] == 'R')&&(pMEM[2] == 'T')&&(pMEM[3] == 'C'))
                            {
                                UserVars.Para.ATFlag |= AT_RTC_FLAG;
                            } 
                            else if ((pMEM[1] == 'N')&&(pMEM[2] == 'E')&&(pMEM[3] == 'T'))
                            {
                                UserVars.Para.ATFlag |= AT_NET_FLAG;
                            } 
                            else if ((pMEM[1] == 'T')&&(pMEM[2] == 'I')&&(pMEM[3] == 'M'))
                            {
                                UserVars.Para.ATFlag |= AT_TIM_FLAG;
                            } 
                            else if ((pMEM[1] == 'U')&&(pMEM[2] == 'S')&&(pMEM[3] == 'B'))
                            {
                                UserVars.Para.ATFlag |= AT_USB_FLAG;
                            } 
                            else if ((pMEM[1] == 'F')&&(pMEM[2] == 'C')&&(pMEM[3] == 'L')&&(pMEM[4] == 'K'))
                            {
                                UserVars.Para.ATFlag |= AT_FCLK_FLAG;
                            } 
                            else if ((pMEM[1] == 'U')&&(pMEM[2] == 'A')&&(pMEM[3] == 'R')&&(pMEM[4] == 'T'))
                            {
                                UserVars.Para.ATFlag |= AT_UART_FLAG;
                            } 
                            else if ((pMEM[1] == 'I')&&(pMEM[2] == 'N')&&(pMEM[3] == 'F')&&(pMEM[4] == 'O'))
                            {
                                UserVars.Para.ATFlag |= AT_INFO_FLAG;
                            } 
                            else if ((pMEM[1] == 'F')&&(pMEM[2] == 'I')&&(pMEM[3] == 'L')&&(pMEM[4] == 'E'))
                            {
                                UserVars.Para.ATFlag |= AT_FILE_FLAG;
                            } 
                            else
                            {
                                rst = ERR_FALSE;
                            }                                
                        } 
                        else
                        {
                            rst = ERR_FALSE;
                        }                            
                    }
                    if (rst == ERR_TRUE)
                    {    
                        printf("AT+DEBUG=OK\r\n");
                    }
                    else
                    {    
                        printf("AT+DEBUG=ERROR\r\n");
                    } 
                    break;    
				}
                
                // AT+DEBUG=OFF
                flag = MatchStr(pMEM, (INT8U *)AT_DEBUG_OFF, 1, &n);
				if(flag==ERR_TRUE)
				{
					// ���´���ָ��
                    pMEM += n;
                    rst = ERR_TRUE;
                    if ((pMEM[0] == '\r')&&(pMEM[1] == '\n'))
                    {    
                        UserVars.Para.ATFlag = 0;
                    }
                    else
                    {    
                        if (pMEM[0] == ',')
                        {    
                            if ((pMEM[1] == 'D')&&(pMEM[2] == 'I'))
                            {
                                UserVars.Para.ATFlag &= ~AT_DI_FLAG;
                            }                        
                            else if ((pMEM[1] == 'D')&&(pMEM[2] == 'O'))
                            {
                                UserVars.Para.ATFlag &= ~AT_DO_FLAG;
                            }  
                            else if ((pMEM[1] == 'A')&&(pMEM[2] == 'I'))
                            {
                                UserVars.Para.ATFlag&= ~AT_AI_FLAG;
                            }  
                            else if ((pMEM[1] == 'A')&&(pMEM[2] == 'O'))
                            {
                                UserVars.Para.ATFlag &= ~AT_AO_FLAG;
                            }  
                            else if ((pMEM[1] == 'P')&&(pMEM[2] == 'W')&&(pMEM[3] == 'M'))
                            {
                                UserVars.Para.ATFlag &= ~AT_PWM_FLAG;
                            } 
                            else if ((pMEM[1] == 'C')&&(pMEM[2] == 'A')&&(pMEM[3] == 'N'))
                            {
                                UserVars.Para.ATFlag &= ~AT_CAN_FLAG;
                            } 
                            else if ((pMEM[1] == 'R')&&(pMEM[2] == 'T')&&(pMEM[3] == 'C'))
                            {
                                UserVars.Para.ATFlag &= ~AT_RTC_FLAG;
                            } 
                            else if ((pMEM[1] == 'N')&&(pMEM[2] == 'E')&&(pMEM[3] == 'T'))
                            {
                                UserVars.Para.ATFlag &= ~AT_NET_FLAG;
                            } 
                            else if ((pMEM[1] == 'T')&&(pMEM[2] == 'I')&&(pMEM[3] == 'M'))
                            {
                                UserVars.Para.ATFlag &= ~AT_TIM_FLAG;
                            } 
                            else if ((pMEM[1] == 'U')&&(pMEM[2] == 'S')&&(pMEM[3] == 'B'))
                            {
                                UserVars.Para.ATFlag = AT_USB_FLAG;
                            } 
                            else if ((pMEM[1] == 'F')&&(pMEM[2] == 'C')&&(pMEM[3] == 'L')&&(pMEM[4] == 'K'))
                            {
                                UserVars.Para.ATFlag &= ~AT_FCLK_FLAG;
                            } 
                            else if ((pMEM[1] == 'U')&&(pMEM[2] == 'A')&&(pMEM[3] == 'R')&&(pMEM[4] == 'T'))
                            {
                                UserVars.Para.ATFlag &= ~AT_UART_FLAG;
                            } 
                            else if ((pMEM[1] == 'I')&&(pMEM[2] == 'N')&&(pMEM[3] == 'F')&&(pMEM[4] == 'O'))
                            {
                                UserVars.Para.ATFlag &= ~AT_INFO_FLAG;
                            } 
                            else if ((pMEM[1] == 'F')&&(pMEM[2] == 'I')&&(pMEM[3] == 'L')&&(pMEM[4] == 'E'))
                            {
                                UserVars.Para.ATFlag &= ~AT_FILE_FLAG;
                            } 
                            else
                            {
                                rst = ERR_FALSE;
                            }                                
                        } 
                        else
                        {
                            rst = ERR_FALSE;
                        }                            
                    }
                    if (rst == ERR_TRUE)
                    {    
                        printf("AT+DEBUG=OK\r\n");
                    }
                    else
                    {    
                        printf("AT+DEBUG=ERROR\r\n");
                    } 
                    break;    
				}	
                
                // AT+DSCIP=192.168.1.10  ������IP����
                flag = MatchStr(pMEM, (INT8U *)AT_DSCIP, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val = *p;
                    if (val == '?')
                    {
                        p++;
                        val1 = *p++;
                        val2 = *p++;
                        if ((val1=='\r')&&(val2=='\n'))
                        {
                            printf("AT+DSCIP=%d.%d.%d.%d\r\n", UserVars.Para.DscIP[0], UserVars.Para.DscIP[1], UserVars.Para.DscIP[2], UserVars.Para.DscIP[3]);
                            rst = ERR_TRUE;                                    
                            break;
                        }                            
                    } 
                    else
                    {        
                        flag = StrToIP((INT8U *)&UserVars.Para.DscIP[0], p);
                        if (flag == ERR_TRUE)
                        {
                            printf("AT+DSCIP=OK\r\n");
                            rst = ERR_TRUE;        
                            break;
                        }
                    }
                    printf("AT+DSCIP=ERROR\r\n");
					rst = ERR_FALSE;        
                    break; 
				} 
                
                // AT+DSCPORT=6001  �������˿�����
                flag = MatchStr(pMEM, (INT8U *)AT_DSCPORT, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val = *p;
                    if (val == '?')
                    {
                        p++;
                        val1 = *p++;
                        val2 = *p++;
                        if ((val1=='\r')&&(val2=='\n'))
                        {
                            printf("AT+DSCPORT=%d\r\n", UserVars.Para.DscPort);
                            rst = ERR_TRUE;        
                            break;
                        }                            
                    } 
                    else
                    {        
                        UserVars.Para.DscPort = StrToInt(p);
                        printf("AT+DSCIP=%d\r\n", UserVars.Para.DscPort);
                        rst = ERR_TRUE;
                        break;    
                    }
                    printf("AT+DSCPORT=ERROR\r\n");
					rst = ERR_FALSE;        
                    break; 
				} 

                break;

//----------��һ���ַ�: S--------------------------------------
			case 'S':                 
                // AT+SAVE
                flag = MatchStr(pMEM, (INT8U *)AT_SAVE, 1, &n);
				if(flag==ERR_TRUE)
				{
					// ���´���ָ��
                    APP_ParaSave((USER_VARS *)&UserVars.Flag);   // �洢���µĲ���
                    
                    printf("AT+SAVE=OK\r\n");
					rst = ERR_TRUE;        
                    break; 
				} 
                
                // AT+SPIFLASH=
                flag = MatchStr(pMEM, (INT8U *)AT_SPIFLASH, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val1 = *p++;
                    val2 = *p++;
                    val3 = *p++;
                    if ((val1=='?')&&(val2=='\r')&&(val3=='\n'))  //��ѯ: AT+SPIFLASH=? 
                    {
                        // ���´���ָ��
                        if (UserVars.OKFlag&SPIFLASH_OK_FLAG)
                        {
                            printf("AT+SPIFLASH=OK\r\n");
                        }
                        else
                        {
                            printf("AT+SPIFLASH=ERROR\r\n");
                        }
                        rst = ERR_TRUE;        
                        break;                        
                    } 
                    else if ((val1=='E')&&(val2=='A')&&(val3==',')) // ��ȡ���� AT+SPIFLASH=EA,
                    {
                        val = *p++;
                        addr = 0;
                        while ((val>='0')&&(val<='9')) // ��ȡ��ʼ��ַ
                        {
                            addr *= 10;
                            addr += val - '0';
                            val = *p++;
                        }  
                        if (val == ',')  
                        {
                            val = *p++;
                            k = 0;
                            while ((val>='0')&&(val<='9'))  //��ȡ���ݳ���
                            {
                                k *= 10;
                                k += val - '0';
                                val = *p++;
                            }  
                            val1 = *p;
                            if ((val == '\r')&&(val1 == '\n'))
                            {    
                                #if (SPIFLASH_TYPE  == W25QXX)
                                for (i=0; i<k; i++)
                                {
                                    rst = W25QXX_Ctrl(CMD_W25QXX_SECTOR_ERASE, W25QXX_ZDY_STARTSECTOR+addr+i);
                                }
                                #endif
                                #if (SPIFLASH_TYPE  == AT45DBXX)
                                for (i=0; i<k; i++)
                                {
                                    rst = AT45DBXX_Ctrl(CMD_W25QXX_SECTOR_ERASE, CMD_AT45DBXX_PAGE_ERASE+addr+i);;
                                }
                                #endif
                                if (rst == ERR_TRUE)
                                {
                                    printf("AT+SPIFLASH=OK\r\n");
                                    break;                                    
                                } //if (rst == ERR_TRUE)  
                            } //if ((val == '\r')&&(val == '\n'))      
                        }     // if (val == ',')                      
                    }
                    else if ((val1=='R')&&((val2=='H')||(val2=='A'))&&(val3==',')) // ��ȡ���� AT+SPIFLASH=RH or RA
                    {
                        val = *p++;
                        addr = 0;
                        while ((val>='0')&&(val<='9')) // ��ȡ��ʼ��ַ
                        {
                            addr *= 10;
                            addr += val - '0';
                            val = *p++;
                        }  
                        if (val == ',')  
                        {
                            val = *p++;
                            k = 0;
                            while ((val>='0')&&(val<='9'))  //��ȡ���ݳ���
                            {
                                k *= 10;
                                k += val - '0';
                                val = *p++;
                            }  
                            val1 = *p;
                            if ((val == '\r')&&(val1 == '\n'))
                            {    
                                pBuf = (INT8U *)OSMalloc(k);   // �����ڴ�
                                if (pBuf == 0)
                                {
                                    return ERR_FALSE;
                                } 
                                
                                #if (SPIFLASH_TYPE  == W25QXX)
                                rst = W25QXX_Read(pBuf, (INT32U)W25QXX_ZDY_STARTSECTOR*W25QXX_SECTOR_SIZE+addr, k);
                                #endif
                                #if (SPIFLASH_TYPE  == AT45DBXX)
                                rst = AT45DBXX_Read(pBuf, (INT32U)AT45DBXX_ZDY_STARTPAGE*AT45DBXX_PAGE_SIZE + addr, k);
                                #endif
                                if (rst == ERR_TRUE)
                                {
                                    if (val2=='H') // д��HEX����
                                    {
                                        printf("AT+SPIFLASH=RH,%d,%d,", addr, k);
                                        for (i=0; i<k; i++)
                                        {
                                            if (i < (k-1))
                                            {    
                                                printf("%02X ", *(pBuf+i));
                                            }
                                            else
                                            {
                                                printf("%02X\r\n", *(pBuf+i));
                                            }
                                        }
                                    }
                                    else
                                    {
                                        printf("AT+SPIFLASH=RA,%d,%d,", addr, k);
                                        for (i=0; i<k; i++)
                                        {
                                            printf("%c", *(pBuf+i));
                                        }
                                        printf("\r\n");
                                    } 
                                    OSFree(pBuf);
                                    break;                                    
                                } //if (rst == ERR_TRUE)  
                                else
                                {
                                    OSFree(pBuf);
                                }                                    
                            } //if ((val == '\r')&&(val == '\n'))      
                        }     // if (val == ',')  
                    }         // else if ((val1=='R')&&((val2=='H')||(val2=='A'))&&(val3==','))                
                    else if ((val1=='W')&&((val2=='H')||(val2=='A'))&&(val3==',')) // д������ AT+SPIFLASH=WH or WA
                    {
                        val = *p++;
                        addr = 0;
                        while ((val>='0')&&(val<='9')) // ��ȡ��ʼ��ַ
                        {
                            addr *= 10;
                            addr += val - '0';
                            val = *p++;
                        }  
                        if (val == ',')  
                        {
                            val = *p++;
                            k = 0;
                            while ((val>='0')&&(val<='9'))  //��ȡ���ݳ���
                            {
                                k *= 10;
                                k += val - '0';
                                val = *p++;
                            }  
                            if (val == ',')
                            {    
                                pBuf = p;
                                if (val2=='H') // д��HEX����
                                {
                                    for (i=0; i<k; i++)
                                    {
                                        val = AsciiToHex(*p++)<<4;
                                        val += AsciiToHex(*p++);
                                        *(pBuf+i) = val;
                                        val = *p++;
                                        if (val != ' ')
                                        {
                                            val1 = *p++;
                                            if ((val=='\r')&&(val1=='\n'))
                                            {
                                                rst = ERR_TRUE; 
                                            }   
                                            else
                                            {
                                                rst = ERR_FALSE; 
                                            }
                                            break;    
                                        }   
                                    }
                                }
                                else  // д��ASCII��
                                {   
                                    val1 = *(p+k);
                                    val2 = *(p+k+1);
                                    if ((val1=='\r')&&(val2=='\n'))
                                    {
                                        rst = ERR_TRUE; 
                                    }   
                                    else
                                    {
                                        rst = ERR_FALSE; 
                                    }
                                }
                                if (rst == ERR_TRUE)
                                {
                                    // ����һ�����ݣ�pBuf, k
                                    #if (SPIFLASH_TYPE  == W25QXX)
                                    addr += (INT32U)W25QXX_ZDY_STARTSECTOR*W25QXX_SECTOR_SIZE;
                                    rst = W25QXX_Write(pBuf, addr, k);
                                    #endif
                                    #if (SPIFLASH_TYPE  == AT45DBXX)
                                    addr += (INT32U)AT45DBXX_ZDY_STARTPAGE*AT45DBXX_PAGE_SIZE;
                                    rst = AT45DBXX_Write(pBuf, addr, k);
                                    #endif
                                    if (rst == ERR_TRUE)
                                    {    
                                        printf("AT+SPIFLASH=OK\r\n");
                                        break;
                                    }   
                                } 
                            } // if (val == ',')        
                        }     // if (val == ',')  
                    }         // else if ((val1=='W')&&((val2=='H')||(val2=='A'))&&(val3==',')) // д������ AT+EEPROM=WH or WA
                
                    printf("AT+SPIFLASH=ERROR\r\n");
                    rst = ERR_FALSE; 
                }   // if(flag==ERR_TRUE)
 
                
                // AT+SD=?
                flag = MatchStr(pMEM, (INT8U *)AT_SD, 1, &n);
				if(flag==ERR_TRUE)
				{
					// ���´���ָ��
                    if (UserVars.OKFlag&SD_OK_FLAG)
                    {
                        printf("AT+SD=OK\r\n");
					}
                    else
                    {
                        printf("AT+SD=ERROR\r\n");
                    }
                    rst = ERR_TRUE;        
                    break; 
				}
                
                // AT+SWVER=?
                flag = MatchStr(pMEM, (INT8U *)AT_SWVER, 1, &n);
				if(flag==ERR_TRUE)
				{
					printf("AT+SWVER=%d.%d%d\r\n", SW_VERSION/100,(SW_VERSION%100)/10, SW_VERSION%10);
					rst = ERR_TRUE;        
                    break; 
				} 
                
                // AT+SW=?
                flag = MatchStr(pMEM, (INT8U *)AT_SW, 1, &n);
				if(flag==ERR_TRUE)
				{
					// ���´���ָ��
                    #ifdef SW_NUM
                    printf("AT+SW=");
                    for(i=0; i<SW_NUM; i++)
                    {
                        if (UserVars.SW&(0x0001<<i))
                        {    
                            printf("1"); 
                        }
                        else
                        {
                            printf("0"); 
                        }
                    }
                    printf("\r\n"); 
					rst = ERR_TRUE;        
                    break; 
                    #else
                    printf("AT+SW=ERROR\r\n"); 
					rst = ERR_FALSE; 
                    break;
                    #endif
				}       
                
                // AT+SRAM=?
                flag = MatchStr(pMEM, (INT8U *)AT_SRAM, 1, &n);
				if(flag==ERR_TRUE)
				{
					// ���´���ָ��
                    if (UserVars.OKFlag&SRAM_OK_FLAG)
                    {
                        printf("AT+SRAM=OK\r\n");
					}
                    else
                    {
                        printf("AT+SRAM=ERROR\r\n");
                    }
                    rst = ERR_TRUE;        
                    break; 
				}      


                // AT+SUBMASK=255.255.255.0  ������������
                flag = MatchStr(pMEM, (INT8U *)AT_SUBMASK, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val = *p;
                    if (val == '?')
                    {
                        p++;
                        val1 = *p++;
                        val2 = *p++;
                        if ((val1=='\r')&&(val2=='\n'))
                        {
                            printf("AT+SUBMASK=%d.%d.%d.%d\r\n", UserVars.Para.SubnetMask[0], UserVars.Para.SubnetMask[1], UserVars.Para.SubnetMask[2], UserVars.Para.SubnetMask[3]);
                            rst = ERR_TRUE;        
                            break;
                        }                            
                    } 
                    else
                    {        
                        flag = StrToIP((INT8U *)&UserVars.Para.SubnetMask[0], p);
                        if (flag == ERR_TRUE)
                        {
                            printf("AT+SUBMASK=OK\r\n");
                            rst = ERR_TRUE;        
                            break;
                        }
                    }
                    printf("AT+SUBMASK=ERROR\r\n");
					rst = ERR_FALSE;        
                    break; 
				}
                // AT+SERVER=    
                rst = MatchStr(pMEM, (INT8U *)AT_SERVER, 1, &n);
				if(rst==ERR_TRUE)
				{
                    p = pMEM + n;
                    val1 = *p++;
                    val2 = *p++;
                    val3 = *p++;
                    if ((val1 == '?')&&(val2 == '\r')&&(val3 == '\r'))
                    {
                        if (UserVars.OKFlag&NET_LINK_OK_FLAG)
                        {
                            printf("AT+SERVER=ON\r\n");
                        }
                        else
                        {
                            printf("AT+SERVER=OFF\r\n");
                        }
                    }
                    /*
                    else if ((val1 == 'O')&&(val2 == 'N')&&(val3 == '\r'))
                    {
                        // ִ���������Ӳ���
                        printf("AT+LINK=OK\r\n");
                    }                  
                    else if ((val1 == 'O')&&(val2 == 'F')&&(val3 == 'F'))
                    {
                        // ִ������Ͽ����Ӳ���
                        printf("AT+LINK=OK\r\n");
                    }                  
                    else if ((val1 == 'O')&&(val2 == 'F')&&(val3 == 'F'))
                    {
                        // ִ������Ͽ����Ӳ���
                        printf("AT+LINK=OK\r\n");
                    }*/                  
                    else
                    {
                        printf("AT+SERVER=ERROR\r\n");
                        rst = ERR_FALSE;
                    }
                    break; 
				} 
                
                break;
            
            //----------��һ���ַ�: A--------------------------------------
			case 'A':                 
                // AT+AI=?
                flag = MatchStr(pMEM, (INT8U *)AT_AI_ALL, 1, &n);
				if(flag==ERR_TRUE)
				{					
                    UserVars.Para.AI.Mode = AT_MODE_START;   // ����AI�ɼ���ʾ
                    rst = ERR_TRUE;        
                    break; 
				}        

                // AT+AI2=?
                flag = MatchStr(pMEM, (INT8U *)AT_AI, 1, &n);
				if(flag==ERR_TRUE)
				{					
                    m = len - n;
					p = pMEM + n;

					val1 = *(p+m-2);
					val2 = *(p+m-1);
					val3 = *(p+m-3);
                    val = *(p+m-4);
                    if ((val1=='\r')&&(val2=='\n')&&(val3=='?')&&(val=='='))
					{
                         p = pMEM + n;
                         val1 = *p;
					     val2 = *(p+1);
                         if ((val1>='0')&&(val1<='9')) 
                         {
                             k = val1 - '0';
                             if ((val2>='0')&&(val2<='9'))
                             {
                                 k *= 10;
                                 k += val2 - '0';
                             }
                             printf("AT+AI%d=%d\r\n", k, UserVars.ADC.buf[k-1]);
                             rst = ERR_TRUE;        
                             break; 
                         }
                     }          
                }
                
                // ��ȡAI����: AT+AI=M?
                flag = MatchStr(pMEM, (INT8U *)AT_AI_RM, 1, &n);
				if(flag==ERR_TRUE)
				{
                    printf("AT+AI=M0,%d,%d\r\n",UserVars.Para.AI.t1,UserVars.Para.AI.t2);
                    rst = ERR_TRUE;        
                    break;              
                }    
                
                // AI����: AT+AI=M0,100,3000
                flag = MatchStr(pMEM, (INT8U *)AT_AI_M, 1, &n);
				if(flag==ERR_TRUE)
				{
                    //m = len - n;
					p = pMEM + n;
                    val = *p++;
                    k=0;
                    while ((val>='0')&&(val<='9'))
                    {
                        k *= 10;
                        k += val - '0';
                        val = *p++;
                    }                        
                    if (val==',')
                    {
                        UserVars.Para.AI.t1 = k;
                        val = *p++;
                        k=0;
                        while ((val>='0')&&(val<='9'))
                        {
                            k *= 10;
                            k += val - '0';
                            val = *p++;
                        }                        
                        if (val=='\r')
                        {
                            UserVars.Para.AI.t2 = k;
                            /*
                            if (UserVars.Para.AI.t2 > 0)
                            {    
                                UserVars.Para.ATFlag |= AT_AI_FLAG;
                            }
                            else
                            {
                                UserVars.Para.ATFlag &= ~AT_AI_FLAG;
                            }*/
                            printf("AT+AI=OK\r\n");
                            rst = ERR_TRUE;        
                            break; 
                        }
                    }
                    printf("AT+AI=ERROR\r\n");
                    rst = ERR_FALSE;
                    break;                    
                }
                
                // AT+AO=?
                flag = MatchStr(pMEM, (INT8U *)AT_AO_R_ALL, 1, &n);
				if(flag==ERR_TRUE)
				{					
                    printf("AT+AO=2,%d,%d\r\n", (INT32U)UserVars.AO[0]*10000/4095, (INT32U)UserVars.AO[1]*10000/4095);
                    rst = ERR_TRUE;        
                    break; 
				}        

                // AT+AO1=?
                flag = MatchStr(pMEM, (INT8U *)AT_AO1_R, 1, &n);
				if(flag==ERR_TRUE)
				{					
                    printf("AT+AO1=%d\r\n", (INT32U)UserVars.AO[0]*10000/4095);
                    rst = ERR_TRUE;        
                    break; 
                }
                
                // AT+AO2=?
                flag = MatchStr(pMEM, (INT8U *)AT_AO2_R, 1, &n);
				if(flag==ERR_TRUE)
				{					
                    printf("AT+AO2=%d\r\n", (INT32U)UserVars.AO[1]*10000/4095);
                    rst = ERR_TRUE;        
                    break; 
                }
                // AT+AO1=500
                flag = MatchStr(pMEM, (INT8U *)AT_AO1_W, 1, &n);
				if(flag==ERR_TRUE)
				{					
                    p = pMEM + n;
                    val = *p++;
                    m = 0;
                    while((val>='0')&&(val<='9'))
                    {
                        m *= 10;
                        m += val-'0';
                        val = *p++;
                    }                        
                    val1 = *p;
                    if ((val=='\r')&&(val1=='\n'))
                    {
                        UserVars.AO[0] = (INT32U)m*4095/10000;
                        UserVars.Para.AO.Mode = AT_MODE_START;
                        printf("AT+AO1=OK\r\n");
                        rst = ERR_TRUE;        
                        break; 
                    }
                    printf("AT+AO1=ERROR\r\n");
                    break;
                }    
                
                // AT+AO2=500
                flag = MatchStr(pMEM, (INT8U *)AT_AO2_W, 1, &n);
				if(flag==ERR_TRUE)
				{					
                    p = pMEM + n;
                    val = *p++;
                    m = 0;
                    while((val>='0')&&(val<='9'))
                    {
                        m *= 10;
                        m += val-'0';
                        val = *p++;
                    }                        
                    val1 = *p;
                    if ((val=='\r')&&(val1=='\n'))
                    {
                        UserVars.AO[1] = (INT32U)m*4095/10000;
                        UserVars.Para.AO.Mode = AT_MODE_START;
                        printf("AT+AO2=OK\r\n");
                        rst = ERR_TRUE;        
                        break; 
                    }
                    printf("AT+AO2=ERROR\r\n");
                    break;
                }
                
                // AT+AO=2,500,1000
                flag = MatchStr(pMEM, (INT8U *)AT_AO_W, 1, &n);
				if(flag==ERR_TRUE)
				{					
                    p = pMEM + n;
                    val = *p++;
                    m = 0;
                    while((val>='0')&&(val<='9'))
                    {
                        m *= 10;
                        m += val-'0';
                        val = *p++;
                    }                        
                    if (val==',')
                    {
                        UserVars.AO[0] = (INT32U)m*4095/10000;                        
                        val = *p++;
                        m = 0;
                        while((val>='0')&&(val<='9'))
                        {
                            m *= 10;
                            m += val-'0';
                            val = *p++;
                        }                        
                        val1 = *p;
                        if ((val=='\r')&&(val1=='\n'))
                        {
                            UserVars.AO[1] = (INT32U)m*4095/10000;
                            UserVars.Para.AO.Mode = AT_MODE_START;
                            printf("AT+AO=OK\r\n");
                            rst = ERR_TRUE;        
                            break; 
                        }                        
                    }
                    
                    printf("AT+AO=ERROR\r\n");
                    break;
                }    
                
                // ��ȡAO����: AT+AO=M?
                flag = MatchStr(pMEM, (INT8U *)AT_AO_RM, 1, &n);
				if(flag==ERR_TRUE)
				{
                    printf("AT+AO=M%c,%d,%d\r\n",UserVars.Para.AO.Mode+'0',UserVars.Para.AO.val,UserVars.Para.AO.t);
                    rst = ERR_TRUE;        
                    break;              
                }    
                
                // AO����: AT+AO=M2,100,3
                flag = MatchStr(pMEM, (INT8U *)AT_AO_M, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val1 = *p++;
                    val2 = *p++;
                    if ((val1>='0')&&(val1<='9')&&(val2==','))
                    {
                        UserVars.Para.AO.Mode = val1 - '0';
                        val = *p++;
                        k=0;
                        while ((val>='0')&&(val<='9'))
                        {
                            k *= 10;
                            k += val - '0';
                            val = *p++;
                        }                        
                        if (val==',')
                        {
                            UserVars.Para.AO.val = k;
                            val = *p++;
                            k=0;
                            while ((val>='0')&&(val<='9'))
                            {
                                k *= 10;
                                k += val - '0';
                                val = *p++;
                            }                        
                            if (val=='\r')
                            {
                                UserVars.Para.AO.t = k;
                                /*
                                if (UserVars.Para.AO.t > 0)
                                {    
                                    UserVars.Para.ATFlag |= AT_AO_FLAG;
                                }
                                else
                                {
                                    UserVars.Para.ATFlag &= ~AT_AO_FLAG;
                                }
                                */
                                printf("AT+AO=OK\r\n");
                                rst = ERR_TRUE;        
                                break; 
                            }
                        }                        
                    } 
                    printf("AT+AO=ERROR\r\n");
                    rst = ERR_FALSE;
                    break;                      
                }
                
                // ALARM����: AT+ALARM=1,100
                flag = MatchStr(pMEM, (INT8U *)AT_ALARM, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val1 = *p++;
                    val2 = *p++;
                    
                    if ((val1=='0')&&(val2==','))
                    {
                        IO_Write(ALARM, 0);
                    } 
                    else
                    {
                        if ((val1=='1')&&(val2==','))
                        {
                            val = *p++;
                            k=0;
                            while ((val>='0')&&(val<='9'))
                            {
                                k *= 10;
                                k += val - '0';
                                val = *p++;
                            } 
                            if (k > 0)
                            {    
                                IO_Ctrl(ALARM, CMD_IO_ON_T, k); 
                            }
                            else
                            {
                                IO_Write(ALARM, 1);
                            }                                
                        }
                    }
                    printf("AT+ALARM=OK\r\n");
                    rst = ERR_TRUE;
                    break;                      
                }
                break;
            
            //----------��һ���ַ�: T--------------------------------------
//			case 'T':                 
//                //           
//                break;
            
            //----------��һ���ַ�: N--------------------------------------
			case 'N':                 
                // AT+NAME=?    
                flag = MatchStr(pMEM, (INT8U *)AT_NAME, 1, &n);
				if(flag==ERR_TRUE)
				{
                    printf("AT+NAME=%s\r\n", PRODUCT_NAME);
					rst = ERR_TRUE;        
                    break; 
				}               
                
                // AT+NFLASH=?
                flag = MatchStr(pMEM, (INT8U *)AT_NFLASH, 1, &n);
				if(flag==ERR_TRUE)
				{
					// ���´���ָ��
                    if (UserVars.OKFlag&NFLASH_OK_FLAG)
                    {
                        printf("AT+NFLASH=OK\r\n");
					}
                    else
                    {
                        printf("AT+NFLASH=ERROR\r\n");
                    }
                    rst = ERR_TRUE;        
                    break; 
				}        

                // AT+NET
                flag = MatchStr(pMEM, (INT8U *)AT_NET, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val1 = *p++;
                    val2 = *p++;
                    val3 = *p++;
                    if ((val1=='M')&&(val2=='0')&&(val3==','))  // ����: AT+NET=M0,0,0 
                    {
                        val1 = *p++;
                        val2 = *p++;
                        if ((val1>='0')&&(val1<='1')&&(val2==','))
                        {
                            val = val1 - '0';
                            val1 = *p++;
                            val2 = *p++;
                            val3 = *p++;
                            if ((val1>='0')&&(val1<='9')&&(val2=='\r')&&(val3=='\n'))
                            {
                                UserVars.Para.NetType = val;
                                UserVars.Para.NetMode = val1 - '0';
                                printf("AT+NET=OK\r\n");
                                rst = ERR_TRUE;        
                                break; 
                            }
                        }                            
                    }  
                    else if ((val1=='M')&&(val2=='0')&&(val3=='?'))  // ��ȡ����: AT+NET=M0,0,0 
                    {
                        val1 = *p++;
                        val2 = *p++;
                        if ((val1=='\r')&&(val2=='\n'))
                        {
                             printf("AT+NET=M0,%c,%c\r\n", UserVars.Para.NetType+'0', UserVars.Para.NetMode+'0');
                             rst = ERR_TRUE;        
                             break; 
                        }                            
                    }                       
                    else if ((val1=='W')&&((val2=='H')||(val2=='A'))&&(val3==',')) // NET�������� AT+NET=WH or WA
                    {
                        val = *p++;
                        k=0;
                        while ((val>='0')&&(val<='9'))
                        {
                            k *= 10;
                            k += val - '0';
                            val = *p++;
                        }  
                        if (val == ',')
                        {
                            pBuf = p;
                            if (val2=='H') // д��HEX����
                            {
                                for (i=0; i<k; i++)
                                {
                                    val = AsciiToHex(*p++)<<4;
                                    val += AsciiToHex(*p++);
                                    *(pBuf+i) = val;
                                    val = *p++;
                                    if (val != ' ')
                                    {
                                        val1 = *p++;
                                        if ((val=='\r')&&(val1=='\n'))
                                        {
                                            rst = ERR_TRUE; 
                                        }   
                                        else
                                        {
                                            rst = ERR_FALSE; 
                                        }
                                        break;    
                                    }   
                                }
                            }
                            else  // д��ASCII��
                            {   
                                val1 = *(p+k);
                                val2 = *(p+k+1);
                                if ((val1=='\r')&&(val2=='\n'))
                                {
                                    rst = ERR_TRUE; 
                                }   
                                else
                                {
                                    rst = ERR_FALSE; 
                                }
                            }
                            if (rst == ERR_TRUE)
                            {
                                // ����һ�����ݣ�pBuf, k
                                
                                printf("AT+NET=OK\r\n");
                                break;
                            }                                 
                        }
                    }  
                    printf("AT+NET=ERROR\r\n");
                    rst = ERR_FALSE;   
                    break;              
                }  
                break;
            
            //----------��һ���ַ�: H--------------------------------------
			case 'H':                 
                // AT+HWVER=?    
                flag = MatchStr(pMEM, (INT8U *)AT_HWVER, 1, &n);
				if(flag==ERR_TRUE)
				{
                    printf("AT+HWVER=%d.%d%d\r\n", HW_VERSION/100,(HW_VERSION%100)/10, HW_VERSION%10);
					rst = ERR_TRUE;        
                    break; 
				}               
                break;
                
            //----------��һ���ַ�: L--------------------------------------
			case 'L':                 
                // AT+LIBVER=?    
                flag = MatchStr(pMEM, (INT8U *)AT_LIBVER, 1, &n);
				if(flag==ERR_TRUE)
				{
                    val = SysLib_Ctrl(CMD_SYSLIB_READ_VERSION, 0);      // ��ȡ������汾
                    printf("AT+LIBVER=%d.%d%d\r\n", val/100,(val%100)/10, val%10);
					rst = ERR_TRUE;        
                    break; 
				} 
                
                // AT+LINK=    
                rst = MatchStr(pMEM, (INT8U *)AT_LINK, 1, &n);
				if(rst==ERR_TRUE)
				{
                    p = pMEM + n;
                    val1 = *p++;
                    val2 = *p++;
                    val3 = *p++;
                    if ((val1 == '?')&&(val2 == '\r')&&(val3 == '\r'))
                    {
                        if (UserVars.OKFlag&NET_LINK_OK_FLAG)
                        {
                            printf("AT+LINK=ON\r\n");
                        }
                        else
                        {
                            printf("AT+LINK=OFF\r\n");
                        }
                    }
                    /*
                    else if ((val1 == 'O')&&(val2 == 'N')&&(val3 == '\r'))
                    {
                        // ִ���������Ӳ���
                        printf("AT+LINK=OK\r\n");
                    }                  
                    else if ((val1 == 'O')&&(val2 == 'F')&&(val3 == 'F'))
                    {
                        // ִ������Ͽ����Ӳ���
                        printf("AT+LINK=OK\r\n");
                    }                  
                    else if ((val1 == 'O')&&(val2 == 'F')&&(val3 == 'F'))
                    {
                        // ִ������Ͽ����Ӳ���
                        printf("AT+LINK=OK\r\n");
                    }*/                  
                    else
                    {
                        printf("AT+LINK=ERROR\r\n");
                        rst = ERR_FALSE;
                    }
                    break; 
				} 
                
                break;
            
            //----------��һ���ַ�: B--------------------------------------
			case 'B':                 
                // AT+BIN=?    
                flag = MatchStr(pMEM, (INT8U *)AT_BIN, 1, &n);
				if(flag==ERR_TRUE)
				{
                    printf("AT+BIN=%s\r\n", BIN_NAME);
					rst = ERR_TRUE;        
                    break; 
				}              
                break;
            
            //----------��һ���ַ�: R--------------------------------------
			case 'R':                 
                // AT+RTC=?    
                flag = MatchStr(pMEM, (INT8U *)AT_RTC_R, 1, &n);
				if(flag==ERR_TRUE)
				{                    
                    flag = RTC_Read(&rtc); // ÿ��3��RTC��ʱ�����  
                    if (flag == ERR_TRUE)
                    {
                        printf("AT+RTC=%d.%d.%d,%d:%d:%d\r\n", rtc.year+2000,rtc.month,rtc.day,rtc.hour,rtc.minute,rtc.second);	
                    }
                    else
                    {
                        printf("AT+RTC=ERROR\r\n");
                    }      
					rst = ERR_TRUE;        
                    break; 
				}  

                // ����ʱ��: AT+RTC=2019.12.1,12:39:56    
                flag = MatchStr(pMEM, (INT8U *)AT_RTC_W, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM+n;
                    
                    val1 = *p++;
                    val2 = *p;                    
                    if ((val1>='0')&&(val1<='9')) 
                    {
                        rtc.year = val1 - '0';
                        if ((val2>='0')&&(val2<='9'))
                        {
                             rtc.year *= 10;
                             rtc.year += val2 - '0';
                             p++;
                        }
                        
                        val = *p++;
                        val1 = *p++;
                        val2 = *p;
                        if ((val1>='0')&&(val1<='9')&&(val=='.')) 
                        {
                            rtc.month = val1 - '0';
                            if ((val2>='0')&&(val2<='9'))
                            {
                                rtc.month *= 10;
                                rtc.month += val2 - '0';
                                p++;
                            }
                             
                            val = *p++;
                            val1 = *p++;
                            val2 = *p;
                            if ((val1>='0')&&(val1<='9')&&(val=='.')) 
                            {
                                rtc.day = val1 - '0';
                                if ((val2>='0')&&(val2<='9'))
                                {
                                    rtc.day *= 10;
                                    rtc.day += val2 - '0';
                                    p++;
                                    rst = ERR_TRUE;
                                    //goto RTC_TIME;
                                }
                                
                            } 
                        }
                    }

                    if (rst == ERR_TRUE)
                    {
                        rst = ERR_FALSE;
                        val = *p++;
                        val1 = *p++;
                        val2 = *p;                    
                        if ((val1>='0')&&(val1<='9')&&(val==',')) 
                        {
                            rtc.hour = val1 - '0';
                            if ((val2>='0')&&(val2<='9'))
                            {
                                 rtc.hour *= 10;
                                 rtc.hour += val2 - '0';
                                 p++;
                            }
                            
                            val = *p++;
                            val1 = *p++;
                            val2 = *p;
                            if ((val1>='0')&&(val1<='9')&&(val==':')) 
                            {
                                rtc.minute = val1 - '0';
                                if ((val2>='0')&&(val2<='9'))
                                {
                                    rtc.minute *= 10;
                                    rtc.minute += val2 - '0';
                                    p++;
                                }
                                 
                                val = *p++;
                                val1 = *p++;
                                val2 = *p;
                                if ((val1>='0')&&(val1<='9')&&(val==':')) 
                                {
                                    rtc.second = val1 - '0';
                                    if ((val2>='0')&&(val2<='9'))
                                    {
                                        rtc.second *= 10;
                                        rtc.second += val2 - '0';
                                        RTC_Write(&rtc);                                        
                                        printf("AT+RTC=OK\r\n");
                                        rst = ERR_TRUE;        
                                        break; 
                                    }
                                } 
                            }
                        }
                    }
                    printf("AT+RTC=ERROR\r\n");					
				}
                
                // ��λ�豸 AT_RESET
                flag = MatchStr(pMEM, (INT8U *)AT_RESET, 1, &n);
				if(flag==ERR_TRUE)
				{
                     // ִ�и�λǰ����
                     printf("AT+RESET=OK\r\n");
                     Delay_ms(100);   
                     SysLib_Ctrl(CMD_SYSLIB_RESET, 0); // �����λ
                }
                break;            
            
            //----------��һ���ַ�: P--------------------------------------
			case 'P':     
                // AT+PWM
                flag = MatchStr(pMEM, (INT8U *)AT_PWM, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val = *p++;
                    val1 = *p++;
                    val2 = *p++;
                    val3 = *p++;
                    if ((val>='1')&&(val<='9')&&(val1=='='))
                    {
                        id = val - '1' ; 
                        if (id >= PWM_NUM)
                        {
                            printf("AT+PWM%c=ERROR\r\n", id+'1');
                            break;
                        }                            
                        val1 = *p++;
                        if ((val2=='M')&&(val3=='?')) // ��ȡPWM����
                        {
                             printf("AT+PWM%c=M%c,%d,%d\r\n",id+'1', UserVars.Para.PWM[id].Mode+'0',UserVars.Para.PWM[id].t1,UserVars.Para.PWM[id].t2);
                             rst = ERR_TRUE;
                             break;
                        }
                        else if ((val2=='M')&&(val3>='0')&&(val3<='3')&&(val1==',')) // PWM��������
                        {
                            UserVars.Para.PWM[id].Mode = val3 - '0';
                            val = *p++;
                            k=0;
                            while ((val>='0')&&(val<='9'))
                            {
                                k *= 10;
                                k += val - '0';
                                val = *p++;
                            }                        
                            if (val==',')
                            {
                                UserVars.Para.PWM[id].t1 = k;
                                val = *p++;
                                k=0;
                                while ((val>='0')&&(val<='9'))
                                {
                                    k *= 10;
                                    k += val - '0';
                                    val = *p++;
                                }                        
                                if (val=='\r')
                                {
                                    UserVars.Para.PWM[id].t2 = k;
                                    printf("AT+PWM%c=OK\r\n",id+'0'+1);
                                    rst = ERR_TRUE;        
                                    break; 
                                }
                            }
                        }
                        else if ((val2=='?')&&(val3=='\r')&&(val1=='\n')) // PWM��ȡ
                        {
                            if (id<PWM_NUM)
                            { 
                                if (UserVars.Para.PWM[id].Mode==0) // ģʽ0, �����������
                                {
                                     printf("AT+PWM%c=%d\r\n", id+'0'+1, UserVars.PWMPara[id].Freq);
                                }
                                else if (UserVars.Para.PWM[id].Mode==1) // ģʽ1, ���N������
                                {
                                     printf("AT+PWM%c=%d,%d\r\n", id+'0'+1, UserVars.PWMPara[id].Freq, UserVars.PWMPara[id].Num[0]);
                                }
                                else if (UserVars.Para.PWM[id].Mode==2) // ģʽ2, ���ռ�ձȿɵ�����
                                {
                                     printf("AT+PWM%c=%d,%d\r\n", id+'0'+1, UserVars.PWMPara[id].Freq, UserVars.PWMPara[id].Rate[0]);
                                }         
                            }  
                            else
                            {
                                printf("AT+PWM%c=ERROR\r\n", id+'0'+1);
                            }                                       
                            rst = ERR_TRUE;
                            break;
                        }
                        else  // PWM�������
                        {
                            if (UserVars.Para.PWM[id].Mode==0) // ģʽ0, �����������
                            {
                                p = pMEM + n + 2;
                                val = *p++;
                                k=0;
                                while ((val>='0')&&(val<='9'))
                                {
                                    k *= 10;
                                    k += val - '0';
                                    val = *p++;
                                }             
                                UserVars.PWMPara[id].Freq = k;
                                printf("AT+PWM%c=OK\r\n", id+'0'+1);
                                rst = ERR_TRUE;
                                break;
                            }
                            else if (UserVars.Para.PWM[id].Mode==1) // ģʽ1, ���N������
                            {
                                p = pMEM + n + 2;
                                val = *p++;
                                k=0;
                                while ((val>='0')&&(val<='9'))
                                {
                                    k *= 10;
                                    k += val - '0';
                                    val = *p++;
                                }             
                                if (val == ',')
                                {
                                    UserVars.PWMPara[id].Freq = k;
                                    val = *p++;
                                    k=0;
                                    while ((val>='0')&&(val<='9'))
                                    {
                                        k *= 10;
                                        k += val - '0';
                                        val = *p++;
                                    }
                                    UserVars.PWMPara[id].Num[0] = k;
                                    printf("AT+PWM%c=OK\r\n", id+'0'+1);
                                    rst = ERR_TRUE;
                                    break;
                                }
                            }
                            else if (UserVars.Para.PWM[id].Mode==2) // ģʽ2, ���ռ�ձȿɵ�����
                            {
                                p = pMEM + n + 2;
                                val = *p++;
                                k=0;
                                while ((val>='0')&&(val<='9'))
                                {
                                    k *= 10;
                                    k += val - '0';
                                    val = *p++;
                                }             
                                if (val == ',')
                                {
                                    UserVars.PWMPara[id].Freq = k;
                                    val = *p++;
                                    k=0;
                                    while ((val>='0')&&(val<='9'))
                                    {
                                        k *= 10;
                                        k += val - '0';
                                        val = *p++;
                                    }
                                    UserVars.PWMPara[id].Rate[0] = k;
                                    printf("AT+PWM%c=OK\r\n", id+'0'+1);
                                    rst = ERR_TRUE;
                                    break;
                                } 
                            }                             
                        }
                    }                      
                    printf("AT+PWM=ERROR\r\n");
                    rst = ERR_FALSE;   
                    break;              
                }
                
                // AT+PORT=6001  ���ض˿�����
                flag = MatchStr(pMEM, (INT8U *)AT_PORT, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val = *p;
                    if (val == '?')
                    {
                        p++;
                        val1 = *p++;
                        val2 = *p++;
                        if ((val1=='\r')&&(val2=='\n'))
                        {
                            printf("AT+PORT=%d\r\n", UserVars.Para.LocalPort);
                            rst = ERR_TRUE;        
                            break;
                        }                            
                    } 
                    else
                    {        
                        UserVars.Para.LocalPort = StrToInt(p);
                        printf("AT+PORT=%d\r\n", UserVars.Para.LocalPort);
                        rst = ERR_TRUE;
                        break;    
                    }
                    printf("AT+PORT=ERROR\r\n");
					rst = ERR_FALSE;        
                    break; 
				} 
                
                break;
                        
            //----------��һ���ַ�: F--------------------------------------
			case 'F':                 
                // AT+FCLK
                flag = MatchStr(pMEM, (INT8U *)AT_FCLK, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val = *p++;
                    val1 = *p++;
                    val2 = *p++;
                    val3 = *p++;
                    if ((val>='1')&&(val<='9')&&(val1=='='))
                    {
                        id = val - '1'; 
                        if (id >= FCLK_NUM)
                        {
                            printf("AT+FCLK%c=ERROR\r\n", id+'1');
                            break;
                        }     
                        
                        val1 = *p++;
                        if ((val2=='M')&&(val3=='?')) // ��ȡFCLK����
                        {
                             printf("AT+FCLK%c=M%c,%d,%d\r\n",id+'1', UserVars.Para.FCLK[id].Mode+'0',UserVars.Para.FCLK[id].t1,UserVars.Para.FCLK[id].t2);
                             rst = ERR_TRUE;
                             break;
                        }
                        else if ((val2=='M')&&(val3>='0')&&(val3<='3')&&(val1==',')) // FCLK��������
                        {
                            UserVars.Para.PWM[id].Mode = val3 - '0';
                            val = *p++;
                            k=0;
                            while ((val>='0')&&(val<='9'))
                            {
                                k *= 10;
                                k += val - '0';
                                val = *p++;
                            }                        
                            if (val==',')
                            {
                                UserVars.Para.FCLK[id].t1 = k;
                                val = *p++;
                                k=0;
                                while ((val>='0')&&(val<='9'))
                                {
                                    k *= 10;
                                    k += val - '0';
                                    val = *p++;
                                }                        
                                if (val=='\r')
                                {
                                    UserVars.Para.FCLK[id].t2 = k;
                                    printf("AT+FCLK%c=OK\r\n", id+'1');
                                    rst = ERR_TRUE;        
                                    break; 
                                }
                            }
                        }
                        else if ((val2=='?')&&(val3=='\r')&&(val1=='\n')) // FCLK��ȡ
                        {
                            if (id<FCLK_NUM)
                            {    
                                if ((UserVars.Para.FCLK[id].Mode==FCLK_MODE_COUNT)||(UserVars.Para.FCLK[id].Mode==FCLK_MODE_DECODE)) // ģʽ0/1 
                                { 
                                     printf("AT+FCLK%c=N,%d\r\n", id+'0'+1, UserVars.FCLK[id].cnt);
                                }
                                else if (UserVars.Para.FCLK[id].Mode==FCLK_MODE_FREQ) // ģʽ2, ����Ƶ��
                                {
                                     printf("AT+FCLK%c=F,%d,%d,%d,%d\r\n", id+'0'+1, UserVars.FCLK[id].Freq[0]/100,UserVars.FCLK[id].Freq[1]/100,UserVars.FCLK[id].Freq[2]/100,UserVars.FCLK[id].Freq[3]/100);
                                }
                                else if (UserVars.Para.FCLK[id].Mode==FCLK_MODE_PWMRATE) // ģʽ3, ���ռ�ձȿɵ�����
                                {
                                     printf("AT+FCLK%c=D,%d.%d\r\n", id+'0'+1, UserVars.FCLK[id].Rate/100, (UserVars.FCLK[id].Rate%100)/10);
                                }
                            } 
                            else
                            {
                                printf("AT+FCLK%c=ERROR\r\n", id+'0'+1);
                            }                                
                            rst = ERR_TRUE;
                            break;
                        }
                    }    
                    printf("AT+FCLK%c=ERROR\r\n",id+'1');
                    rst = ERR_FALSE;   
                    break;              
                }              
                break;
            
            //----------��һ���ַ�: U--------------------------------------
			case 'U':      
                // AT+UART
                flag = MatchStr(pMEM, (INT8U *)AT_UART, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val = *p++;
                    val1 = *p++;
                    val2 = *p++;
                    val3 = *p++;
                    if ((val>='1')&&(val<='6')&&(val1=='=')) 
                    {
                        id = val - '1';
                        val1 = *p++;
                        if ((val2=='W')&&((val3=='H')||(val3=='A'))&&(val1==',')) // UART�������� AT+UART1=
                        {
                            val1 = *p++;
                            k=0;
                            while ((val1>='0')&&(val1<='9'))
                            {
                                k *= 10;
                                k += val1 - '0';
                                val1 = *p++;
                            }             
                            if (val1 == ',')
                            {
                                pBuf = (INT8U *)OSMalloc(k);   // �����ڴ�
                                if (pBuf == 0)
                                {
                                    return ERR_FALSE;
                                } 
                                
                                if (val3=='H') // д��HEX����
                                {
                                    for (i=0; i<k; i++)
                                    {
                                        val = AsciiToHex(*p++)<<4;
                                        val += AsciiToHex(*p++);
                                        *(pBuf+i) = val;
                                        if (i != (k-1)) // �жϲ������һ������
                                        {
                                            val1 = *p++;
                                            if (val1 != ' ')
                                            {
                                                break;
                                            }
                                        }        
                                    }
                                }
                                else  // д��ASCII��
                                {
                                    for (i=0; i<k; i++)
                                    {
                                        *(pBuf+i) = *p++;
                                    }
                                } 
                                val1 = *p++;
                                val2 = *p++;
                                if ((val1=='\r')&&(val2=='\n'))
                                {
                                    Uart_Write(id, pBuf, k); // ����һ������
                                    printf("AT+UART%c=OK\r\n", id+'1');
                                    OSFree(pBuf);         // �ͷ��ڴ�
                                    rst = ERR_TRUE;
                                    break;
                                }                                        
                                OSFree(pBuf);         // �ͷ��ڴ�                   
                             }
                             printf("AT+UART%c=OK\r\n", id+'1');
                             rst = ERR_FALSE;
                             break;
                        }           
                        else if ((val2=='?')&&(val3=='\r')&&(val1=='\n')) // ��ȡUART���� AT+UART1=?
                        {
                             printf("AT+UART%c=%d,%d,%d,%d\r\n", id+'1', UserVars.Para.Uart[id].Baud,UserVars.Para.Uart[id].bits, UserVars.Para.Uart[id].PS, UserVars.Para.Uart[id].Stop);
                             rst = ERR_TRUE;
                             break;
                        }
                        else if ((val2>='1')&&(val2<='9')&&(val3>='0')&&(val2<='9')&&(val1>='0')&&(val1<='9')) // ����UART���� AT+UART1=115200,8,0,
                        {
                            k = ((INT32U)val2-'0')*100 + ((INT32U)val3-'0')*10 + val1-'0';
                            val = *p++;
                            while ((val>='0')&&(val<='9'))
                            {
                                k *= 10;
                                k += val - '0';
                                val = *p++;
                            }             
                            if (val == ',')
                            {
                                UserVars.Para.Uart[id].Baud = k;
                                val = *p++;
                                val1 = *p++;
                                if ((val1 == ',')&&(val>='7')&&(val<='9'))                                
                                {
                                    UserVars.Para.Uart[id].bits = val - '0';
                                    val = *p++;
                                    val1 = *p++;
                                    if ((val1 == ',')&&(val>='0')&&(val<='2'))                                
                                    {
                                        UserVars.Para.Uart[id].PS = val - '0';
                                        val = *p++;
                                        val1 = *p++;
                                        val2 = *p++;
                                        if ((val1 == '\r')&&(val2 == '\n')&&(val>='1')&&(val<='2'))   
                                        {
                                            UserVars.Para.Uart[id].Stop = val - '0';
                                            printf("AT+UART%c=OK\r\n", id+'1');
                                            rst = ERR_TRUE;
                                            break;
                                        }                                            
                                    }
                                }
                            }
                            printf("AT+UART%c=ERROR\r\n", id+'1');
                            rst = ERR_TRUE;
                            break;
                        }          
                    }                      
                    printf("AT+UART=ERROR\r\n");
                    rst = ERR_FALSE;   
                    break;              
                }                        
                // AT+UDISK=?
                flag = MatchStr(pMEM, (INT8U *)AT_UDISK, 1, &n);
				if(flag==ERR_TRUE)
				{
					// ���´���ָ��
                    if (UserVars.OKFlag&UDISK_OK_FLAG)
                    {
                        printf("AT+UDISK=OK\r\n");
					}
                    else
                    {
                        printf("AT+UDISK=ERROR\r\n");
                    }
                    rst = ERR_TRUE;        
                    break; 
				}  
                // AT+USB=?
                flag = MatchStr(pMEM, (INT8U *)AT_USB, 1, &n);
				if(flag==ERR_TRUE)
				{
					// ���´���ָ��
                    if (UserVars.OKFlag&USB_OK_FLAG)
                    {
                        printf("AT+USB=OK\r\n");
					}
                    else
                    {
                        printf("AT+USB=ERROR\r\n");
                    }
                    rst = ERR_TRUE;        
                    break; 
				}     

               
                break;
            
            //----------��һ���ַ�: C--------------------------------------
			case 'C':                 
                // AT+CAN, 
                flag = MatchStr(pMEM, (INT8U *)AT_CAN, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val = *p++;
                    val1 = *p++;
                    val2 = *p++;
                    val3 = *p++;
                    if ((val>='1')&&(val<='2')&&(val1=='='))
                    {
                        id = val - '1';
                        val1 = *p++;
                        if ((val2=='W')&&((val3=='H')||(val3=='A'))&&(val1==',')) // CAN1����16�������� AT+CAN1=WH
                        {
                            val1 = *p++;
                            k=0;
                            while ((val1>='0')&&(val1<='9'))
                            {
                                k *= 10;
                                k += val1 - '0';
                                val1 = *p++;
                            }             
                            if (val1 == ',')
                            {
                                CanTx.ID = k;    // ��ֵCAN��ַ
                                CanTx.IDE = UserVars.Para.CAN[id].IDE;
                                CanTx.RTR = CAN_RTR_DATA;
                                
                                val1 = *p++;
                                k=0;
                                while ((val1>='0')&&(val1<='9'))
                                {
                                    k *= 10;
                                    k += val1 - '0';
                                    val1 = *p++;
                                }         
                                if (val1 == ',')
                                {
                                    CanTx.DLC = k;
                                    if (val3=='H') // д��HEX����
                                    {
                                        for (i=0; i<CanTx.DLC; i++)
                                        {
                                            CanTx.Data[i] = AsciiToHex(*p++)<<4;
                                            CanTx.Data[i] += AsciiToHex(*p++);
                                            if (i != (CanTx.DLC-1)) // �жϲ������һ������
                                            {
                                               val1 = *p++;
                                                if (val1 != ' ')
                                                {
                                                    break;
                                                }
                                            }        
                                        }
                                    }
                                    else  // д��ASCII��
                                    {
                                        for (i=0; i<CanTx.DLC; i++)
                                        {
                                            CanTx.Data[i] = *p++;
                                        }
                                    } 
                                    val1 = *p++;
                                    val2 = *p++;
                                    if ((val1=='\r')&&(val2=='\n'))
                                    {
                                        CAN_Write(id, (CAN_TX_MSG *)&CanTx.ID); // ����һ������
                                        printf("AT+CAN%c=OK\r\n", id+'1');
                                        rst = ERR_TRUE;
                                        break;
                                    }                                        
                                }                     
                             }
                             printf("AT+CAN%c=ERROR\r\n", id+'1');
                             rst = ERR_FALSE;
                             break;
                        }           
                        /*
                        else if ((val2=='W')&&(val3=='H')&&(val1==',')) // ��ȡCAN���� AT+CAN1=?
                        {
                             printf("AT+CAN%c=%d,%d\r\n", id+'1', UserVars.Para.CAN[id].IDE, UserVars.Para.CAN[id].Baud);
                             rst = ERR_TRUE;
                             break;
                        }*/    
                        else if ((val2=='?')&&(val3=='\r')&&(val1=='\n')) // ��ȡCAN���� AT+CAN1=?
                        {
                             printf("AT+CAN%c=%d,%d\r\n", id+'1', UserVars.Para.CAN[id].IDE, UserVars.Para.CAN[id].Baud);
                             rst = ERR_TRUE;
                             break;
                        }           
                        else if ((val2=='F')&&(val3=='?')&&(val1=='\r')) // ��ȡCAN �˲������� AT+CAN1=F?
                        {
                             printf("AT+CAN%c=F,14,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",id+'1', UserVars.Para.CAN[id].Filter[0],UserVars.Para.CAN[id].Filter[1], \
                                   UserVars.Para.CAN[id].Filter[2],UserVars.Para.CAN[id].Filter[3],UserVars.Para.CAN[id].Filter[4],UserVars.Para.CAN[id].Filter[5], \
                                   UserVars.Para.CAN[id].Filter[6],UserVars.Para.CAN[id].Filter[7],UserVars.Para.CAN[id].Filter[8],UserVars.Para.CAN[id].Filter[9], \
                                   UserVars.Para.CAN[id].Filter[10],UserVars.Para.CAN[id].Filter[11],UserVars.Para.CAN[id].Filter[12], UserVars.Para.CAN[id].Filter[13]);
                             rst = ERR_TRUE;
                             break;
                        }
                        else if (((val2=='0')||(val2=='1'))&&(val3==',')) // ����CAN���� AT+CAN1=1,50000
                        {
                            UserVars.Para.CAN[id].IDE = val2 - '0'; 
                            //val = *p++;
                            k=0;
                            while ((val1>='0')&&(val1<='9'))
                            {
                                k *= 10;
                                k += val1 - '0';
                                val1 = *p++;
                            }             
                            if (val1 == '\r')
                            {
                                UserVars.Para.CAN[id].Baud = k; 
                                printf("AT+CAN%c=OK\r\n", id+'1');
                                rst = ERR_TRUE;
                                break;
                            }                          
                        }
                        else if ((val2=='F')&&(val3==',')) // ����CAN �˲������� AT+CAN1=F,14,1,2,3,4,5,6,7,8,9,10,11,12,13,14
                        {
                            //val = *p++;
                            k=0;
                            while ((val1>='0')&&(val1<='9'))
                            {
                                k *= 10;
                                k += val1 - '0';
                                val1 = *p++;
                            }  
                            if (val1==',')
                            {        
                                n = k;  
                                rst = ERR_FALSE;                                
                                for (i=0;i<n;i++)
                                {
                                    k=0;
                                    val1 = *p++;
                                    while ((val1>='0')&&(val1<='9'))
                                    {
                                        k *= 10;
                                        k += val1 - '0';
                                        val1 = *p++;
                                    }
                                    UserVars.Para.CAN[id].Filter[i] = k;
                                    if (val1 == '\r')
                                    {  
                                        rst = ERR_TRUE;
                                        break;
                                    }                                        
                                }
                                if (rst == ERR_TRUE)
                                {
                                    printf("AT+CAN%c=OK\r\n", id+'1');
                                }
                                else
                                {
                                    printf("AT+CAN%c=ERROR\r\n", id+'1');
                                }                                    
                                break;
                            }                       
                        }                        
                    }                      
                    printf("AT+CAN=ERROR\r\n");
                    rst = ERR_FALSE;   
                    break;              
                }
                break;
             //----------��һ���ַ�: G--------------------------------------
			case 'G':                 
                // AT+GWIP=192.168.1.44  ����IP����
                flag = MatchStr(pMEM, (INT8U *)AT_GWIP, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val = *p;
                    if (val == '?')
                    {
                        p++;
                        val1 = *p++;
                        val2 = *p++;
                        if ((val1=='\r')&&(val2=='\n'))
                        {
                            printf("AT+GWIP=%d.%d.%d.%d\r\n", UserVars.Para.Gataway[0], UserVars.Para.Gataway[1], UserVars.Para.Gataway[2], UserVars.Para.Gataway[3]);
                            rst = ERR_TRUE;        
                            break;
                        }                            
                    } 
                    else
                    {        
                        flag = StrToIP((INT8U *)&UserVars.Para.Gataway[0], p);
                        if (flag == ERR_TRUE)
                        {
                            printf("AT+GWIP=OK\r\n");
                            rst = ERR_TRUE;        
                            break;
                        }
                    }
                    printf("AT+GWIP=ERROR\r\n");
					rst = ERR_FALSE;        
                    break; 
				} 
                break;
            //----------��һ���ַ�: I--------------------------------------
			case 'I':                 
                // AT+IP=192.168.1.44  ����IP����
                flag = MatchStr(pMEM, (INT8U *)AT_IP, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val = *p;
                    if (val == '?')
                    {
                        p++;
                        val1 = *p++;
                        val2 = *p++;
                        if ((val1=='\r')&&(val2=='\n'))
                        {
                            printf("AT+IP=%d.%d.%d.%d\r\n", UserVars.Para.LocalIP[0], UserVars.Para.LocalIP[1], UserVars.Para.LocalIP[2], UserVars.Para.LocalIP[3]);
                            rst = ERR_TRUE;        
                            break;
                        }                            
                    } 
                    else
                    {        
                        flag = StrToIP((INT8U *)&UserVars.Para.LocalIP[0], p);
                        if (flag == ERR_TRUE)
                        {
                            printf("AT+IP=OK\r\n");
                            rst = ERR_TRUE;        
                            break;
                        }
                    }
                    printf("AT+IP=ERROR\r\n");
					rst = ERR_FALSE;        
                    break; 
				} 
                break;
            //----------��һ���ַ�: E--------------------------------------
			case 'E': 
                // AT+EEPROM=
                flag = MatchStr(pMEM, (INT8U *)AT_EEPROM, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val1 = *p++;
                    val2 = *p++;
                    val3 = *p++;
                    if ((val1=='?')&&(val2=='\r')&&(val3=='\n'))  //��ѯ: AT+EEPROM=? 
                    {
                        // ���´���ָ��
                        if (UserVars.OKFlag&EEPROM_OK_FLAG)
                        {
                            printf("AT+EEPROM=OK\r\n");
                        }
                        else
                        {
                            printf("AT+EEPROM=ERROR\r\n");
                        }
                        rst = ERR_TRUE;        
                        break;                        
                    } 
                    else if ((val1=='R')&&((val2=='H')||(val2=='A'))&&(val3==',')) // ��ȡ���� AT+EEPROM=RH or RA
                    {
                        val = *p++;
                        addr = 0;
                        while ((val>='0')&&(val<='9')) // ��ȡ��ʼ��ַ
                        {
                            addr *= 10;
                            addr += val - '0';
                            val = *p++;
                        }  
                        if (val == ',')  
                        {
                            val = *p++;
                            k = 0;
                            while ((val>='0')&&(val<='9'))  //��ȡ���ݳ���
                            {
                                k *= 10;
                                k += val - '0';
                                val = *p++;
                            }  
                            val1 = *p;
                            if ((val == '\r')&&(val1 == '\n'))
                            {    
                                pBuf = (INT8U *)OSMalloc(k);   // �����ڴ�
                                if (pBuf == 0)
                                {
                                    return ERR_FALSE;
                                } 
                                rst = EEPROM_Read(addr, pBuf, k);
                                if (rst == ERR_TRUE)
                                {
                                    if (val2=='H') // д��HEX����
                                    {
                                        printf("AT+EEPROM=RH,%d,%d,", addr, k);
                                        for (i=0; i<k; i++)
                                        {
                                            if (i < (k-1))
                                            {    
                                                printf("%02X ", *(pBuf+i));
                                            }
                                            else
                                            {
                                                printf("%02X\r\n", *(pBuf+i));
                                            }
                                        }
                                    }
                                    else
                                    {
                                        printf("AT+EEPROM=RA,%d,%d,", addr, k);
                                        for (i=0; i<k; i++)
                                        {
                                            printf("%c", *(pBuf+i));
                                        }
                                        printf("\r\n");
                                    } 
                                    OSFree(pBuf);
                                    break;                                    
                                } //if (rst == ERR_TRUE)  
                                else
                                {
                                    OSFree(pBuf);
                                }                                    
                            } //if ((val == '\r')&&(val == '\n'))      
                        }     // if (val == ',')  
                    }         // else if ((val1=='R')&&((val2=='H')||(val2=='A'))&&(val3==','))                
                    else if ((val1=='W')&&((val2=='H')||(val2=='A'))&&(val3==',')) // д������ AT+EEPROM=WH or WA
                    {
                        val = *p++;
                        addr = 0;
                        while ((val>='0')&&(val<='9')) // ��ȡ��ʼ��ַ
                        {
                            addr *= 10;
                            addr += val - '0';
                            val = *p++;
                        }  
                        if (val == ',')  
                        {
                            val = *p++;
                            k = 0;
                            while ((val>='0')&&(val<='9'))  //��ȡ���ݳ���
                            {
                                k *= 10;
                                k += val - '0';
                                val = *p++;
                            }  
                            if (val == ',')
                            {    
                                pBuf = p;
                                if (val2=='H') // д��HEX����
                                {
                                    for (i=0; i<k; i++)
                                    {
                                        val = AsciiToHex(*p++)<<4;
                                        val += AsciiToHex(*p++);
                                        *(pBuf+i) = val;
                                        val = *p++;
                                        if (val != ' ')
                                        {
                                            val1 = *p++;
                                            if ((val=='\r')&&(val1=='\n'))
                                            {
                                                rst = ERR_TRUE; 
                                            }   
                                            else
                                            {
                                                rst = ERR_FALSE; 
                                            }
                                            break;    
                                        }   
                                    }
                                }
                                else  // д��ASCII��
                                {   
                                    val1 = *(p+k);
                                    val2 = *(p+k+1);
                                    if ((val1=='\r')&&(val2=='\n'))
                                    {
                                        rst = ERR_TRUE; 
                                    }   
                                    else
                                    {
                                        rst = ERR_FALSE; 
                                    }
                                }
                                if (rst == ERR_TRUE)
                                {
                                    // ����һ�����ݣ�pBuf, k
                                    rst = EEPROM_Write(addr, pBuf, k);
                                    if (rst == ERR_TRUE)
                                    {    
                                        printf("AT+EEPROM=OK\r\n");
                                        break;
                                    }   
                                } 
                            } // if (val == ',')        
                        }     // if (val == ',')  
                    }         // else if ((val1=='W')&&((val2=='H')||(val2=='A'))&&(val3==',')) // д������ AT+EEPROM=WH or WA
                
                    printf("AT+EEPROM=ERROR\r\n");
                    rst = ERR_FALSE; 
                }   // if(flag==ERR_TRUE)
                break;

            //----------��һ���ַ�: M--------------------------------------
			case 'M':                 
                // AT+MODEL=?    
                flag = MatchStr(pMEM, (INT8U *)AT_MODEL, 1, &n);
				if(flag==ERR_TRUE)
				{
                    printf("AT+MODEL=%s\r\n", PRODUCT_MODEL);
					return ERR_TRUE;
				}             
                
                // AT_MAC  ��дMAC��ַ
                flag = MatchStr(pMEM, (INT8U *)AT_MAC, 1, &n);
				if(flag==ERR_TRUE)
				{
                    p = pMEM + n;
                    val = *p;
                    if (val == '?')
                    {
                        p++;
                        val1 = *p++;
                        val2 = *p++;
                        if ((val1=='\r')&&(val2=='\n'))
                        {
                            printf("AT+MAC=%02X,%02X,%02X,%02X,%02X,%02X\r\n", UserVars.Para.MACAddr[0], UserVars.Para.MACAddr[1], UserVars.Para.MACAddr[2], \
                                    UserVars.Para.MACAddr[3],UserVars.Para.MACAddr[4],UserVars.Para.MACAddr[5]);
                            rst = ERR_TRUE;        
                            break;
                        }                            
                    } 
                    else
                    {   
                        for (i=0; i<6; i++)
                        {    
                            UserVars.Para.MACAddr[i] = AsciiToHex(*p++)<<4;
                            UserVars.Para.MACAddr[i] += AsciiToHex(*p++);
                            val = *p++;
                            if ((val!=',')&&(val!='\r'))
                            {
                                break;
                            }
                        } 
                        if ((val=='\r')&&(i==6))
                        {    
                            printf("AT+MAC=OK\r\n");
                            rst = ERR_TRUE;        
                            break;
                        }                        
                    }
                    printf("AT+MAC=ERROR\r\n");
					rst = ERR_FALSE;        
                    break; 
				} 
                
                break;
//             //----------��һ���ַ�: L--------------------------------------
//			case 'L':                 
//                // AT+LINK=?    
//                flag = MatchStr(pMEM, (INT8U *)AT_LINK, 1, &n);
//				if(flag==ERR_TRUE)
//				{
//                    p = pMEM + n;
//                    val = *p++;
//                    val1 = *p++;
//                    val2 = *p++;
//                    val3 = *p++;
//                    if ((val == '?')&&(val1 == '\r')&&(val1 == '\r'))
//                    {
//                        
//                    }
//                    
//                    printf("AT+VER=%d.%d%d\r\n", AT_VERSION/100,(AT_VERSION%100)/10, AT_VERSION%10);
//					rst = ERR_TRUE;        
//                    break; 
//				}               
//                break;        
            //----------��һ���ַ�: V--------------------------------------
			case 'V':                 
                // AT+VER=?    
                flag = MatchStr(pMEM, (INT8U *)AT_VER, 1, &n);
				if(flag==ERR_TRUE)
				{
                    printf("AT+VER=%d.%d%d\r\n", AT_VERSION/100,(AT_VERSION%100)/10, AT_VERSION%10);
					rst = ERR_TRUE;        
                    break; 
				}               
                break;   
                
            default:
                printf("AT+CMD=ERROR\r\n");
                return ERR_FALSE;
                break;
        }
        
        
    }    
}    

/***********************************************************************************
* Function: AT_Proc;
*
* Description: ATָ�����;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void AT_Proc(INT8U *p, INT16U len)
{
    INT32S flag;
	INT16U  n, i;
    INT8U *pMEM;    
    
    while(len>=6)
    {
        flag = MatchStr(p, "\r\n", 1, &n);
        if (flag==ERR_TRUE)
        {
             if (n>=6)
             {
                 pMEM = (INT8U *)OSMalloc(n+10); // �����ڴ�
                 for (i=0; i<n; i++)   // ��������
                 {
                     *(pMEM+i) = *p++;
                 }
                 *(pMEM+n) = 0;
                 AT_CmdProc(pMEM, n);  // AT�����
                 OSFree(pMEM);         // �ͷ��ڴ�
             }
             len -= n;               // ʣ���ֽڳ���
        }
        else
        {
             return;
        }            
    }
} 
#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
