/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: subfun.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是常用子函数头文件;
*
* Others: none;
*
* Function List: 
*          1. INT16U GetStringLength(INT8U *p);
*          2. INT32S MatchStr(INT8U *pSrc, INT8U *pDst, INT8U m, INT16U *n);
*          3. INT32S StringComp(INT8U *str1,INT8U *str2, INT16U len);
*          4. void IntToStr(INT8U *pDst, INT32U val);
*          5. INT32U StrToInt(INT8U *pSrc);
*          6. INT8U AsciiToHex(INT8U val);
*          7. void IPToStr(INT8U *pDst, INT8U ip[]);
*          8. INT32S StrToIP(INT8U ip[], INT8U *pSrc);
*          9. void HexToStr(INT8U val, INT8U *pDst);
*          10. void StrCopy(INT8U *pDst, INT8U *pSrc);
*          11. void StrCopy2(INT8U *pDst, INT8U *pSrc1, INT8U *pSrc2);
*          12. void StrCopy3(INT8U *pDst, INT8U *pSrc1, INT8U *pSrc2, INT8U *pSrc3);
*          13. void StrCopy4(INT8U *pDst, INT8U *pSrc1, INT8U *pSrc2, INT8U *pSrc3, INT8U *pSrc4);
*          14. void StrCopy5(INT8U *pDst, INT8U *pSrc1, INT8U *pSrc2, INT8U *pSrc3, INT8U *pSrc4, INT8U *pSrc5);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h" 

/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/

/************************************************************************************
//
//                 常用函数子程序
//
*************************************************************************************/

/***********************************************************************************
* Function: GetStringLength;
*
* Description: 取得字符串长度;
*              
* Input:  *p: 字符串指针	 
*
* Return: 目标串长度;
*
* Note:   none;
************************************************************************************/
INT16U GetStringLength(INT8U *p);

/***********************************************************************************
* Function: MatchStr;
*
* Description: 字符串匹配搜索;
*              
* Input:  *pSrc: 源字符串指针
*         *pDst: 要搜索的目标字符串指针
*          m:    要搜索的第几个字符串
*         *n:    返回要搜索字符串下一个字符位置  	 
*
* Return: ERR_TRUE:成功;  ERR_FALSE:失败;
*
* Note:   none;
************************************************************************************/
INT32S MatchStr(INT8U *pSrc, INT8U *pDst, INT8U m, INT16U *n);

/***********************************************************************************
* Function: StringComp;
*
* Description: 字符串对比;
*              
* Input:  *str1: 对比字符串1指针
*         *str2: 对比字符串2指针
*          len:  字符串长度 
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S StringComp(INT8U *str1,INT8U *str2, INT16U len);

/***********************************************************************************
* Function: IntToStr;
*
* Description: 32位整型数转换为字符串(十进制);
*              
* Input:  *pDst: 目标字符串指针
*          val:  整型数
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void IntToStr(INT8U *pDst, INT32U val);

/***********************************************************************************
* Function: StrToInt;
*
* Description: 将字符串转换为32位整型数;
*              
* Input:  *pSrc: 源字符串指针
*
* Return: 32位整型数;
*
* Note:   直到遇到不是'0'-'9'的字符，就认为转换完成;
*         比如：字符串"1234A",转换结果就是返回：1234 
*************************************************************************************/
INT32U StrToInt(INT8U *pSrc);

/***********************************************************************************
* Function: AsciiToHex;
*
* Description: 将ASCII码转换为16进制数;
*              
* Input:  val: ASCII码
*
* Return: 8位16进制数;
*
* Note:   返回值是0, 则转换失败;
************************************************************************************/
INT8U AsciiToHex(INT8U val);

/***********************************************************************************
* Function: IPToStr;
*
* Description: 将4字节IP转换为点间隔的IP字符串
*              
* Input:  pDst: 目标IP字符串
*         ip[]: 四字节IP
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void IPToStr(INT8U *pDst, INT8U ip[]);

/***********************************************************************************
* Function: StrToIP;
*
* Description: 将点间隔的IP字符串转换为4字节IP
*              
* Input:  pSrc: 源IP字符串
*         ip[]: 四字节IP
*
* Return: ERR_TRUE:成功;  ERR_FALSE:失败;
*
* Note:   none;
************************************************************************************/
INT32S StrToIP(INT8U ip[], INT8U *pSrc);

/***********************************************************************************
* Function: HexToStr;
*
* Description: 将HEX数转换为2个字符串
*              
* Input:  val: HEX数
*         *pDst: 目标字符串
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void HexToStr(INT8U val, INT8U *pDst);

/***********************************************************************************
* Function: StrCopy;
*
* Description: 单字符串拷贝函数
*              
* Input:  *pDst: 目标目标字符串指针
*         *pSrc: 源字符串指针
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void StrCopy(INT8U *pDst, INT8U *pSrc);

/***********************************************************************************
* Function: StrCopy2;
*
* Description: 2字符串拷贝函数
*              
* Input:  *pDst: 目标目标字符串指针
*         *pSrc1: 源字符串1指针
*         *pSrc2: 源字符串2指针
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void StrCopy2(INT8U *pDst, INT8U *pSrc1, INT8U *pSrc2);

/***********************************************************************************
* Function: StrCopy3;
*
* Description: 3字符串拷贝函数
*              
* Input:  *pDst: 目标目标字符串指针
*         *pSrc1: 源字符串1指针
*         *pSrc2: 源字符串2指针
*         *pSrc3: 源字符串3指针
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void StrCopy3(INT8U *pDst, INT8U *pSrc1, INT8U *pSrc2, INT8U *pSrc3);

/***********************************************************************************
* Function: StrCopy4;
*
* Description: 4字符串拷贝函数
*              
* Input:  *pDst: 目标目标字符串指针
*         *pSrc1: 源字符串1指针
*         *pSrc2: 源字符串2指针
*         *pSrc3: 源字符串3指针
*         *pSrc4: 源字符串4指针
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void StrCopy4(INT8U *pDst, INT8U *pSrc1, INT8U *pSrc2, INT8U *pSrc3, INT8U *pSrc4);

/***********************************************************************************
* Function: StrCopy5;
*
* Description: 5字符串拷贝函数
*              
* Input:  *pDst: 目标目标字符串指针
*         *pSrc1: 源字符串1指针
*         *pSrc2: 源字符串2指针
*         *pSrc3: 源字符串3指针
*         *pSrc4: 源字符串4指针
*         *pSrc5: 源字符串5指针
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void StrCopy5(INT8U *pDst, INT8U *pSrc1, INT8U *pSrc2, INT8U *pSrc3, INT8U *pSrc4, INT8U *pSrc5);

/***********************************************************************************/
// 文件结束
/***********************************************************************************/
