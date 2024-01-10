/*************************************************************************************************** 
                                   xxxx公司
  
                  

文件:   CookDrive.c 
作者:   龙川
说明:   炒菜机底层动作驱动，每代机器的都会不一样，所以这个驱动需要根据机器修改
		前面部分各种电机的找原点函数
		中间部分各种炒菜步骤的实现
		后面各种炒菜功能实现
***************************************************************************************************/
#include "PlatformManage.h"
#include "PlatformDrive.h"
#include "UserVars.h"
#include "OSVars.h"
#include "GPIO_Manager.h"
#include "motor.h"
#include "STM32Fxxx.h"
#include "Delay.h"

//这个是一个指向UserVars.Para.CookerSavePara的指针
SaveParaStruct *CookSavePara;

APP_FuncMboxMsgStruct MboxMsg_X_Motor;
APP_FuncMboxMsgStruct MboxMsg_Y_Motor;
 /**
 ****************************************************************************************
 @brief:	PanRiseFallPositionFound 升降电机位置寻找
 @Input：	NULL
 @Output：  NULL
 @Return	NULL
 @Warning:	NULL 
 @note: 	龙川2019-6-4
 ****************************************************************************************
  **/
uint32_t X_AxisPositionFound(void)
{
	int i;
	uint8_t foundFlag=0,iostate,cnt;//判断是否找到标志位
	uint16_t step[] = {6400,640,100};//三次步长设置
	for(i=0;i<3;i++)
	{
		foundFlag=0;
		cnt=0;
		while(1)
		{
            printf("i=%d\r\n",i);
			Motor_Enable(Enum_X_AxisMotor,Dir_Backward,6400,step[i]);
			while(PWM_Ctrl(X_AxisMotor, CMD_PWM_STATUS, 0))
			{

				Delay_ms(10);				
				iostate = IOFunction_Read(Limiter);
				cnt++;
				//if(cnt%500 == 0)
				{
					printf("iostate = %d\r\n",iostate);
				}
				if(iostate)
				{
					
					foundFlag=1;
					Delay_ms(100);
					Motor_Enable(Enum_X_AxisMotor,Dir_Foreward,6400,step[i]+10);
					break;
				}
			}
			if(foundFlag)
				break;

		}
	}
//	CookerFlag.PanRiseFallFind = 1;
	return ERR_TRUE;
}
/**
 ****************************************************************************************
 @brief: X_AxisPositionFoundStart 启动找电机
 @Input： NULL
 @Output：  NULL
 @Return NULL
 @Warning: NULL  
 @note:  
 ****************************************************************************************
  **/
void X_AxisPositionFoundStart(void)
{
	printf("%s\r\n",__func__);
	MboxMsg_X_Motor.ArgcNum=0;
	MboxMsg_X_Motor.FuncZeroArgc = X_AxisPositionFound;
	OSMboxPost(OSMboxX_Motor, (void *)&MboxMsg_X_Motor); // 释放访问权限
}
/**
 ****************************************************************************************
 @brief:	PanRiseFallDebugFunc 升锅电机调试
 @Input：	Dir方向
			speed 速度
			pul 脉冲个数
 @Output：  NULL
 @Return	NULL
 @Warning:	NULL  
 @note: 	龙川2019-6-4
 ****************************************************************************************
  **/
uint32_t X_AxisDebugFunc(uint32_t Dir, uint32_t speed,uint32_t pul)
{
	printf("%s,dir=%d,pul=%d\r\n",__func__,Dir,pul);
	Motor_Enable(Enum_X_AxisMotor,Dir,speed,pul);
	return ERR_TRUE;
}
/**
 ****************************************************************************************
 @brief:	PanRotatePositionFound 转锅电机找原点
 @Input：	NULL
 @Output：  NULL
 @Return	NULL
 @Warning:	NULL  
 @note: 	龙川2019-6-4
 ****************************************************************************************
  **/
uint32_t Y_AxisPositionFound(void)
{
	

	return ERR_TRUE;
}



 /**
 ****************************************************************************************
 @brief:	DriveInit 初始化
 @Input：	NULL
 @Output：  NULL
 @Return	NULL
 @Warning:	NULL  
 @note: 	龙川2019-5-8——这样做每代机器只需要修改下面这些函数的实现，顶层调用不用变
 ****************************************************************************************
**/
void DriveInit(void)
{

	memset(SysManage.MotorPosition,0,sizeof(SysManage.MotorPosition));
	memset(SysManage.LimitPul,0,32*sizeof(SysManage.LimitPul));

}
 /**
 ****************************************************************************************
 @brief:	Limit 限位防止机器跑过头了
 @Input：	NULL
 @Output：  NULL
 @Return	NULL
 @Warning:	NULL  
 @note: 	龙川2019-5-8
 ****************************************************************************************
**/
void Limit(void)
{
	
}

/**
 ****************************************************************************************
 @brief:	InterLocking 互锁
 @Input：	NULL
 @Output：  NULL
 @Return	NULL
 @Warning:	NULL  
 @note: 	龙川2019-5-8 机器动作的互锁功能实现：
			就是有的电机在动作时另外一个电机就不允许动作，否则会出问题
 ****************************************************************************************
**/
void InterLocking()
{
	//TODO:升降电机在动作时，转锅电机不能动作。
	
}

void MotorFlagHandle(void)
{
	if(ManageFlag.StartXFlag)
	{
		ManageFlag.StartXFlag = 0;
		X_AxisDebugFunc(ManageFlag.StartXDir,6400,640);
	}
//	else if(ManageFlag.StartXFlag==2)
//	{
//		ManageFlag.StartXFlag = 0;
//		X_AxisDebugFunc(ManageFlag.StartXDir,6400,640);
//	}
	
}



