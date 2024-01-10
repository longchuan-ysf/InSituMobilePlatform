
#ifndef __COOKMANAGE_H
#define __COOKMANAGE_H
#include "stdint.h"

#define BITCON(index,bit)             ((index<<5)+bit)//将数组位置和在字节中的位置转换成总偏移，如急停是第0个DWORD的第0个BIT index=0，bit=0
													//电磁炉通讯告警是第1个DWORD的第0个BIT，所以换算出来的结果是32 
//---------------------------------告警位偏移定义-------------------------------------------------//
#define Scram_Alarm_Offset                    BITCON(0,0)//急停
#define Screen_Alarm_Offset                   BITCON(0,1)//屏幕通讯异常



//---------------------------------告警码定义-------------------------------------------------//
//需要注意0是无告警——告警码和告警位的转换关系是 告警码是告警位在数组中的位索引+1 如急停是第0个DWORD的第0个BIT 0+1
//电磁炉通讯告警是第1个DWORD的第0个BIT，所以换算出来的结果是32+1 = 33
#define A_Scram                          (Scram_Alarm_Offset+1)//急停
#define A_Screen                         (Screen_Alarm_Offset+1)//屏幕通讯超时



//每位代表一种事件标志树立_____这些Flag是掉电丢失，上电全部初始化为0，
//掉电不丢失的Falg是UserVars.Para.Flag
typedef struct
{
	uint32_t StartXFlag:2;//X轴启动标志，0停止，1步进，2
	uint32_t StartXDir:1;//x轴方向
	
}FlagStruct;

typedef struct
{
	uint16_t Priority;//告警优先级——数字越小优先级越高
	uint16_t AlarmCode;//告警码
	uint16_t AlarmBit;//告警位或者称偏移
}AlarmStruct;
typedef struct
{
	int32_t MotorZhengLimit;//前限——前面 上面 左边 正转
	int32_t MotorFanLimit;//后限——后面 下面 右边 反转
}LimitPulStruct;

typedef struct
{
	
	uint8_t Alarm;//当前设备最高优先级的告警
	uint8_t RunStep;//当前正在执行的炒菜步骤
	
	//正数代表 ： 前面 上面 左边 正转
	//负数代表 ： 后面 下面 右边 反转
	//当前机器有几个定义几个-翻炒没有必要记录——这里0是原点位置 不是原点光电位置 原点光电位置+补偿 = 原点位置0
	//所有位置参考都是原点位置 而不是原点光电位置但回原点的原点位置依赖原点光电位置
	int32_t MotorPosition[4];
	LimitPulStruct LimitPul[4];//限位记录

}SysManageStruct;
extern uint32_t AlarmBitInfo[8];
extern FlagStruct ManageFlag;
extern SysManageStruct SysManage;

extern void  AlarmSet(uint32_t AlarmOffset);
extern uint8_t  AlarmGet(uint32_t AlarmOffset);
extern void  AlarmClear(uint32_t AlarmOffset);


extern void Motor_TaskCreate(void);
extern void Func_TaskCreate(void);
#endif



