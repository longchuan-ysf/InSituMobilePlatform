/*************************************************************************************************** 
                                   xxxx公司
  
                  

文件:   timer.c 
作者:   龙川
说明:   电机控制定时器初始化
***************************************************************************************************/
#include "motor.h"
#include "GPIO_Manager.h"
#include "UserVars.h"	

/**
****************************************************************************************
@brief:    Motor_Enable
@Input：   Motor  需要控制的电机
		   Dir  电机的方向
		   Fre 电机频率
		   PUL 电机的脉冲个数
@Output：  NULL
@Return    NULL
@Warning:    
@note:     
****************************************************************************************
 **/

void Motor_Enable(MotorEnum Motor,uint8_t Dir,uint32_t Fre,uint32_t PUL)
{
	PWM_CTRL *pPara;
	TIM_CTRL TIMCtrl;
	uint8_t MotorID;
	if(Motor>=EnumMotorMax)
		return;
	switch(Motor)
	{
		case Enum_X_AxisMotor://X轴电机
		{
			
			//电机控制
			pPara=&UserVars.PWMPara[X_AxisMotor];
			while(PWM_Ctrl(X_AxisMotor, CMD_PWM_STATUS, 0) != 0); // 等待输出脉冲完成
			
			IO_Write(X_AxisMotorDir, Dir);//设置电机方向
			pPara->Mode = PWM_CTRL_FREQ_N; // 控制更改PWM频率输出, 并且输出N个脉冲后停止
            pPara->Freq = Fre;       // 设置默认频率
            pPara->Chx = PWM1CH_EN;        // 设置使能通道
			pPara->Num[0] = PUL;        // 设置每个通道输出脉冲个数__实际只用到通道1
			pPara->Num[1] = PUL;
			pPara->Num[2] = PUL;
			pPara->Num[3] = PUL;
			PWM_Ctrl(X_AxisMotor, CMD_PWM_FREQ, pPara);  // 按参数修改PWM输出频率   
			PWM_Ctrl(X_AxisMotor, CMD_PWM_ENA, pPara);  // 按参数设置使能PWM输出 
			
		}
		break;
		case Enum_Y_AxisMotor://Y轴电机
		{
			//限位判定
			
			//电机控制
			pPara=&UserVars.PWMPara[Y_AxisMotor];
			while(PWM_Ctrl(Y_AxisMotor, CMD_PWM_STATUS, 0) != 0); // 等待输出脉冲完成
			
			IO_Write(Y_AxisMotorDir, Dir);//设置电机方向
			pPara->Mode = PWM_CTRL_FREQ_N; // 控制更改PWM频率输出, 并且输出N个脉冲后停止
            pPara->Freq = Fre;       // 设置默认频率
            pPara->Chx = PWM2CH_EN;        // 设置使能通道
			pPara->Num[0] = PUL;        // 设置每个通道输出脉冲个数__实际只用到通道1
			pPara->Num[1] = PUL;
			pPara->Num[2] = PUL;
			pPara->Num[3] = PUL;
			PWM_Ctrl(Y_AxisMotor, CMD_PWM_FREQ, pPara);  // 按参数修改PWM输出频率   
			PWM_Ctrl(Y_AxisMotor, CMD_PWM_ENA, pPara);  // 按参数设置使能PWM输出 
		}
		break;
		default:
		break;
	}	
}
static uint8_t Motor_EnumToId(MotorEnum Motor)
{
	if(Motor == Enum_X_AxisMotor)
		return X_AxisMotor;
	else if(Motor == Enum_Y_AxisMotor)
		return Y_AxisMotor;
	return EnumMotorMax;
}
/**
****************************************************************************************
@brief:    Motor_Disable
@Input：   Motor  需要控制的电机
@Output：  NULL
@Return    NULL
@Warning:    
@note:     
****************************************************************************************
 **/

void Motor_Disable(MotorEnum Motor)
{
	TIM_CTRL TIMCtrl;
	uint8_t MotorId;
	if(Motor>=EnumMotorMax)
		return;
	MotorId = Motor_EnumToId(Motor);
	
	PWM_Ctrl(MotorId, CMD_PWM_DIS, 0);  // 按参数设置使能PWM输出 
	
}
/**
****************************************************************************************
@brief:    Motor_GetStatus
@Input：   Motor  需要控制的电机
@Output：  NULL
@Return    返回 ERR_TRUE, 操作成功
@Warning:    
@note:     根据测试发现这个函数返回的是定时器的使能Tim->CR的CEN位
****************************************************************************************
 **/
int32_t Motor_GetStatus(MotorEnum Motor)
{
	uint8_t MotorId;
	if(Motor>=EnumMotorMax)
		return ERR_FALSE;
	MotorId = Motor_EnumToId(Motor);
	
	return PWM_Ctrl(Motor, CMD_PWM_STATUS, 0);

}

/**
****************************************************************************************
@brief:    Motor_SetFrequency
@Input：   Motor  需要控制的电机  Frep频率
@Output：  NULL
@Return    返回ERR_TRUE, 操作成功
@Warning:    
@note:     
****************************************************************************************
 **/
int32_t Motor_SetFrequency(MotorEnum Motor,uint32_t Fre)
{
	PWM_CTRL Para;
	uint8_t MotorId;
	if(Motor>=EnumMotorMax)
		return ERR_FALSE;
	MotorId = Motor_EnumToId(Motor);
	Para.Freq = Fre;         // 设置频率
	return PWM_Ctrl(Motor, CMD_PWM_FREQ, &Para);  // 按参数修改PWM输出频率 ;
	
}
/**
****************************************************************************************
@brief:    Motor_GetPulse
@Input：   Motor  需要控制的电机 
@Output：  NULL 
@Return    已经发出的脉冲个数
@Warning:    
@note:     
****************************************************************************************
 **/
int32_t Motor_GetPulse(MotorEnum Motor)
{ 
	uint8_t MotorId;
	if(Motor>=EnumMotorMax)
		return ERR_FALSE;
	MotorId = Motor_EnumToId(Motor);
	
	return PWM_Ctrl(Motor, CMD_PWM_PULNUM, 0);  // 获取已发的脉冲个数
	
}
