/*************************************************************************************************** 
                                   xxxx��˾
  
                  

�ļ�:   timer.c 
����:   ����
˵��:   ������ƶ�ʱ����ʼ��
***************************************************************************************************/
#include "motor.h"
#include "GPIO_Manager.h"
#include "UserVars.h"	

/**
****************************************************************************************
@brief:    Motor_Enable
@Input��   Motor  ��Ҫ���Ƶĵ��
		   Dir  ����ķ���
		   Fre ���Ƶ��
		   PUL ������������
@Output��  NULL
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
		case Enum_X_AxisMotor://X����
		{
			
			//�������
			pPara=&UserVars.PWMPara[X_AxisMotor];
			while(PWM_Ctrl(X_AxisMotor, CMD_PWM_STATUS, 0) != 0); // �ȴ�����������
			
			IO_Write(X_AxisMotorDir, Dir);//���õ������
			pPara->Mode = PWM_CTRL_FREQ_N; // ���Ƹ���PWMƵ�����, �������N�������ֹͣ
            pPara->Freq = Fre;       // ����Ĭ��Ƶ��
            pPara->Chx = PWM1CH_EN;        // ����ʹ��ͨ��
			pPara->Num[0] = PUL;        // ����ÿ��ͨ������������__ʵ��ֻ�õ�ͨ��1
			pPara->Num[1] = PUL;
			pPara->Num[2] = PUL;
			pPara->Num[3] = PUL;
			PWM_Ctrl(X_AxisMotor, CMD_PWM_FREQ, pPara);  // �������޸�PWM���Ƶ��   
			PWM_Ctrl(X_AxisMotor, CMD_PWM_ENA, pPara);  // ����������ʹ��PWM��� 
			
		}
		break;
		case Enum_Y_AxisMotor://Y����
		{
			//��λ�ж�
			
			//�������
			pPara=&UserVars.PWMPara[Y_AxisMotor];
			while(PWM_Ctrl(Y_AxisMotor, CMD_PWM_STATUS, 0) != 0); // �ȴ�����������
			
			IO_Write(Y_AxisMotorDir, Dir);//���õ������
			pPara->Mode = PWM_CTRL_FREQ_N; // ���Ƹ���PWMƵ�����, �������N�������ֹͣ
            pPara->Freq = Fre;       // ����Ĭ��Ƶ��
            pPara->Chx = PWM2CH_EN;        // ����ʹ��ͨ��
			pPara->Num[0] = PUL;        // ����ÿ��ͨ������������__ʵ��ֻ�õ�ͨ��1
			pPara->Num[1] = PUL;
			pPara->Num[2] = PUL;
			pPara->Num[3] = PUL;
			PWM_Ctrl(Y_AxisMotor, CMD_PWM_FREQ, pPara);  // �������޸�PWM���Ƶ��   
			PWM_Ctrl(Y_AxisMotor, CMD_PWM_ENA, pPara);  // ����������ʹ��PWM��� 
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
@Input��   Motor  ��Ҫ���Ƶĵ��
@Output��  NULL
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
	
	PWM_Ctrl(MotorId, CMD_PWM_DIS, 0);  // ����������ʹ��PWM��� 
	
}
/**
****************************************************************************************
@brief:    Motor_GetStatus
@Input��   Motor  ��Ҫ���Ƶĵ��
@Output��  NULL
@Return    ���� ERR_TRUE, �����ɹ�
@Warning:    
@note:     ���ݲ��Է�������������ص��Ƕ�ʱ����ʹ��Tim->CR��CENλ
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
@Input��   Motor  ��Ҫ���Ƶĵ��  FrepƵ��
@Output��  NULL
@Return    ����ERR_TRUE, �����ɹ�
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
	Para.Freq = Fre;         // ����Ƶ��
	return PWM_Ctrl(Motor, CMD_PWM_FREQ, &Para);  // �������޸�PWM���Ƶ�� ;
	
}
/**
****************************************************************************************
@brief:    Motor_GetPulse
@Input��   Motor  ��Ҫ���Ƶĵ�� 
@Output��  NULL 
@Return    �Ѿ��������������
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
	
	return PWM_Ctrl(Motor, CMD_PWM_PULNUM, 0);  // ��ȡ�ѷ����������
	
}
