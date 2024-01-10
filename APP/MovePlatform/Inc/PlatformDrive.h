/*************************************************************************************************** 
                                   xxxx公司
  
                  

文件:   cookdrive.h
作者:   龙川
说明:   炒菜底层动作驱动
***************************************************************************************************/
#ifndef __COOKDRIVE_H
#define __COOKDRIVE_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "ucos_ii.h"


#pragma pack (1)
//定义需要保存的参数结构体---为了做到向下兼容不允许修改现有的结构体成员位置，新增只能往后加,且只允许增加不允许删除现有的
typedef struct
{
	//一些电机特定位置定义
	uint16_t sysnc;
	int16_t RiseFallPosition_Finish ;//定义降落到倒菜的位置
	int16_t RiseFallPosition_cook ;//定义锅炒菜的位置	这两个一定要是正数因为原点就是最低端
	

	
	//调试时每个电机按一下的步进是多少
	uint16_t DebugDyestrippingStep;
	uint16_t DebugBlockFBStep;

	//原点偏移
	int16_t OrgBlockFBOffset;//挡盒偏移---在界面显示为挡盒待机位置
	int16_t OrgPanRotateOffset;//转锅偏移--在界面显示为转锅回正位置
	int16_t OrgDyestrippingOffset;//撕膜偏移---在界面显示为勾膜位置

	//电机的速度定义----单位频率而不是每分钟多少转

	
	//撕膜电机与挡盒电机的同步系数——保留小数点后两位，也就是撕膜电机转一圈（发一个脉冲），挡盒电机需要转几圈（几个脉冲）
	//比如同步系数1.9说明撕膜电机发一个脉冲，挡盒电机需要发1.9个脉冲



}SaveParaStruct;
#pragma pack ()
typedef enum
{
	EnumRiseFallPosition_Finish = 0,
	
	EnumRiseFallPosition_cook ,//定义锅炒菜的位置

	EnumDyestrippingPosition ,//定义撕膜位置————第一次调试的位置

	EnumADD_FOOD1_Dyestripping_Pulse,//放食材1撕膜光电需要检测多少个脉冲

	EnumADD_FOOD2_Dyestripping_Pulse ,//放食材2撕膜光电需要检测多少个脉冲

	EnumADD_FOOD3_Dyestripping_Pulse ,//放食材3撕膜光电需要检测多少个脉冲

	//原点偏移
	EnumOrgIntoDishOffset,
	
	EnumOrgPanRotateOffset,//正数往里面摆负数往外面摆
	
	EnumOrgSlideOffset,
	
	EnumRotateDishPosition ,//定义转锅倒菜位置
	
	EnumRotateWashPosition  ,//定义转锅倒水位置
	
	EnumIntoDishUpLimit,//入菜上限
	
	EnumWashWaterRate,//洗锅注水量
	
	EnumSlideOpen,//滑道升起量
	
}SaveParaEnum;








extern void MotorFlagHandle(void);


//油泵校准函数
extern void X_AxisPositionFoundStart(void);
extern void DriveInit(void);
extern void Limit(void);
extern void InterLocking(void);

#endif



