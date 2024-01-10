
#ifndef __COOKMANAGE_H
#define __COOKMANAGE_H
#include "stdint.h"

#define BITCON(index,bit)             ((index<<5)+bit)//������λ�ú����ֽ��е�λ��ת������ƫ�ƣ��缱ͣ�ǵ�0��DWORD�ĵ�0��BIT index=0��bit=0
													//���¯ͨѶ�澯�ǵ�1��DWORD�ĵ�0��BIT�����Ի�������Ľ����32 
//---------------------------------�澯λƫ�ƶ���-------------------------------------------------//
#define Scram_Alarm_Offset                    BITCON(0,0)//��ͣ
#define Screen_Alarm_Offset                   BITCON(0,1)//��ĻͨѶ�쳣



//---------------------------------�澯�붨��-------------------------------------------------//
//��Ҫע��0���޸澯�����澯��͸澯λ��ת����ϵ�� �澯���Ǹ澯λ�������е�λ����+1 �缱ͣ�ǵ�0��DWORD�ĵ�0��BIT 0+1
//���¯ͨѶ�澯�ǵ�1��DWORD�ĵ�0��BIT�����Ի�������Ľ����32+1 = 33
#define A_Scram                          (Scram_Alarm_Offset+1)//��ͣ
#define A_Screen                         (Screen_Alarm_Offset+1)//��ĻͨѶ��ʱ



//ÿλ����һ���¼���־����_____��ЩFlag�ǵ��綪ʧ���ϵ�ȫ����ʼ��Ϊ0��
//���粻��ʧ��Falg��UserVars.Para.Flag
typedef struct
{
	uint32_t StartXFlag:2;//X��������־��0ֹͣ��1������2
	uint32_t StartXDir:1;//x�᷽��
	
}FlagStruct;

typedef struct
{
	uint16_t Priority;//�澯���ȼ���������ԽС���ȼ�Խ��
	uint16_t AlarmCode;//�澯��
	uint16_t AlarmBit;//�澯λ���߳�ƫ��
}AlarmStruct;
typedef struct
{
	int32_t MotorZhengLimit;//ǰ�ޡ���ǰ�� ���� ��� ��ת
	int32_t MotorFanLimit;//���ޡ������� ���� �ұ� ��ת
}LimitPulStruct;

typedef struct
{
	
	uint8_t Alarm;//��ǰ�豸������ȼ��ĸ澯
	uint8_t RunStep;//��ǰ����ִ�еĳ��˲���
	
	//�������� �� ǰ�� ���� ��� ��ת
	//�������� �� ���� ���� �ұ� ��ת
	//��ǰ�����м������弸��-����û�б�Ҫ��¼��������0��ԭ��λ�� ����ԭ����λ�� ԭ����λ��+���� = ԭ��λ��0
	//����λ�òο�����ԭ��λ�� ������ԭ����λ�õ���ԭ���ԭ��λ������ԭ����λ��
	int32_t MotorPosition[4];
	LimitPulStruct LimitPul[4];//��λ��¼

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



