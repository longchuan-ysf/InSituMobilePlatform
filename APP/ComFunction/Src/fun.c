/*************************************************************************************************** 
                                   xxxx��˾
  
                  

�ļ�:   fun.c 
����:   ����
˵��:   ����������ʵ��
***************************************************************************************************/
#include "fun.h"
#include "stdio.h"
#include "string.h"
 /**
****************************************************************************************
@brief:    printf_Hexbuffer 
@Input��   *data ��������Bufferָ��
		   Len  ��Ҫȡ�����ݳ���
@Output��  NULL
@Return    NULL
@Warning:  NULL
@note:     ����2019-4-15
****************************************************************************************
 **/
 
 void printf_Hexbuffer(uint8_t *buffer,uint32_t len)
 {
	uint32_t  i;
	uint8_t   data[16];
	for(i=0;i<len;i++)
	 {
		sprintf((char  *)&data,"0x%02x ",buffer[i]);
		printf("%s",data);
		if(((i+1)%16 == 0))
		{
			printf("\r\n");
		}
	 }
	 printf("\r\n");
 }

  /**
****************************************************************************************
@brief:    CheckSum ����У��� 
@Input��    *data ����
	       bufferLen  ���ݳ���
@Output��  NULL
@Return    NULL
@Warning:  NULL
@note:     ����2019-4-15
****************************************************************************************
 **/
 unsigned  char CheckSum(const unsigned  char *buffer,unsigned  int bufferLen)
{
	unsigned  int Sum;
	unsigned  int i;
	
	if(!buffer)
	{
		return 0;
	}
	Sum = 0;
	for(i=0; i<bufferLen; i++)
	{
		Sum = Sum + *buffer;
		buffer ++;
	}
	
	return Sum&0xff;
}



/**
****************************************************************************************
@brief:   StrFloatToInt
@Input��   *pSrc �ַ���ָ��
			FloatPoint ����λ��
@Output�� NULL
@Return   NULL
@Warning: NULL
@note:  ��Ļ�н�����С��ת�������� 
		���� 
		StrFloatToInt((uint8_t *)"1.23" ,2) = 123//��������λ����1 Ҫ�󸡵������ڸ���������
		StrFloatToInt((uint8_t *)"1.2345" ,2) = 123//��������λ����1 Ҫ�󸡵���С�ڸ���������
		StrFloatToInt((uint8_t *)"1.2" ,2) = 120//��������λ����1 Ҫ�󸡵��������ڸ���������

		StrFloatToInt((uint8_t *)"0.23" ,2) = 23//��������λС��1 Ҫ�󸡵������ڸ���������
		StrFloatToInt((uint8_t *)"0.2345" ,2) = 23
		StrFloatToInt((uint8_t *)"0.2" ,2) = 20

		StrFloatToInt((uint8_t *)"-1.23" ,2) = -123//����
		StrFloatToInt((uint8_t *)"-1.2345" ,2) = -123
		StrFloatToInt((uint8_t *)"-1.2" ,2) = -120
		
		StrFloatToInt((uint8_t *)"-0.23" ,2) = -23
		StrFloatToInt((uint8_t *)"-0.2345" ,2) = -23
		StrFloatToInt((uint8_t *)"-0.2" ,2) = -20
****************************************************************************************
 **/

int32_t StrFloatToInt(uint8_t *pSrc,uint8_t FloatPoint)
{
	int32_t ret,i,len,FloatCnt,neg,deci;
	ret = 0;
	len = strlen((char *)pSrc);
	FloatCnt = 0;//С��λ������
	neg = 0;//�������
	deci = 0;//С�����
	for(i=0; i<len; i++)
	{
		if((*pSrc>=0x30)&&(*pSrc<=0x39))
		{
			ret = ret*10;
			ret += (*pSrc-0x30);		
			if(deci)//��ʼ����С������
			{	
				FloatCnt++;				
				if(FloatCnt>=FloatPoint)//����ָ����С��λ�����˳������ܺ������
				{
					break;
				}
				
			}
			
		}
		else if(*pSrc == '.')//С����
		{
			if(!deci)
			{
				deci = 1;
				
			}
			else//�ַ����еڶ��γ���С���㣬ֱ���˳�
			{
				break;
			}
			//����������1..234   ���������100���漸��0ȡ����FloatPoint
		}
		else if((*pSrc == '-')&&(i==0))
		{
			neg = 1;
		}
		else
		{
				break;
		}
		pSrc++;
	}
	//�ַ�����С��λ����ָ����С��λ����0
	if(FloatCnt<FloatPoint)
	{
		for(i=0; i<FloatPoint-FloatCnt; i++)
		{
			ret=ret*10;
		}
	}
	if(neg)
		ret =-ret;
	return ret;
}












