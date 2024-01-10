/*************************************************************************************************** 
                                   xxxx��˾
  
                  

�ļ�:   cookdrive.h
����:   ����
˵��:   ���˵ײ㶯������
***************************************************************************************************/
#ifndef __COOKDRIVE_H
#define __COOKDRIVE_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "ucos_ii.h"


#pragma pack (1)
//������Ҫ����Ĳ����ṹ��---Ϊ���������¼��ݲ������޸����еĽṹ���Աλ�ã�����ֻ�������,��ֻ�������Ӳ�����ɾ�����е�
typedef struct
{
	//һЩ����ض�λ�ö���
	uint16_t sysnc;
	int16_t RiseFallPosition_Finish ;//���彵�䵽���˵�λ��
	int16_t RiseFallPosition_cook ;//��������˵�λ��	������һ��Ҫ��������Ϊԭ�������Ͷ�
	

	
	//����ʱÿ�������һ�µĲ����Ƕ���
	uint16_t DebugDyestrippingStep;
	uint16_t DebugBlockFBStep;

	//ԭ��ƫ��
	int16_t OrgBlockFBOffset;//����ƫ��---�ڽ�����ʾΪ���д���λ��
	int16_t OrgPanRotateOffset;//ת��ƫ��--�ڽ�����ʾΪת������λ��
	int16_t OrgDyestrippingOffset;//˺Ĥƫ��---�ڽ�����ʾΪ��Ĥλ��

	//������ٶȶ���----��λƵ�ʶ�����ÿ���Ӷ���ת

	
	//˺Ĥ����뵲�е����ͬ��ϵ����������С�������λ��Ҳ����˺Ĥ���תһȦ����һ�����壩�����е����Ҫת��Ȧ���������壩
	//����ͬ��ϵ��1.9˵��˺Ĥ�����һ�����壬���е����Ҫ��1.9������



}SaveParaStruct;
#pragma pack ()
typedef enum
{
	EnumRiseFallPosition_Finish = 0,
	
	EnumRiseFallPosition_cook ,//��������˵�λ��

	EnumDyestrippingPosition ,//����˺Ĥλ�á���������һ�ε��Ե�λ��

	EnumADD_FOOD1_Dyestripping_Pulse,//��ʳ��1˺Ĥ�����Ҫ�����ٸ�����

	EnumADD_FOOD2_Dyestripping_Pulse ,//��ʳ��2˺Ĥ�����Ҫ�����ٸ�����

	EnumADD_FOOD3_Dyestripping_Pulse ,//��ʳ��3˺Ĥ�����Ҫ�����ٸ�����

	//ԭ��ƫ��
	EnumOrgIntoDishOffset,
	
	EnumOrgPanRotateOffset,//����������ڸ����������
	
	EnumOrgSlideOffset,
	
	EnumRotateDishPosition ,//����ת������λ��
	
	EnumRotateWashPosition  ,//����ת����ˮλ��
	
	EnumIntoDishUpLimit,//�������
	
	EnumWashWaterRate,//ϴ��עˮ��
	
	EnumSlideOpen,//����������
	
}SaveParaEnum;








extern void MotorFlagHandle(void);


//�ͱ�У׼����
extern void X_AxisPositionFoundStart(void);
extern void DriveInit(void);
extern void Limit(void);
extern void InterLocking(void);

#endif



