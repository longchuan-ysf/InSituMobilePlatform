/*************************************************************************************************** 
                                   xxxx公司
  
                  

文件:   GPIO_Manager.h
作者:   龙川
说明:   普通输入输出口的IO管理
***************************************************************************************************/
#ifndef __GPIO_MANAGER_H
#define __GPIO_MANAGER_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>
//输出控制IO口索引宏定义——一定要与数组的位置一一对应
typedef enum
{
	StirPUL = 0,//搅拌脉冲-----

	
	//电机方向枚举	
	CookerDOMax,
}cookerDO;
//输入检测口IO索引定义
typedef enum
{
	Limiter=0,//限位器
	Raster,
	CookerDIMax,
}cookerDI;

typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
} GPIO_PinState;

#define CHECK_STATE GPIO_PIN_SET
#define CHECK_STATE_N GPIO_PIN_RESET

#define NOT_CHECK_STATE  GPIO_PIN_RESET 
#define NOT_CHECK_STATE_N GPIO_PIN_SET

#define FORWARD_STATE  GPIO_PIN_SET//正转
#define BACKWARD_STATE  GPIO_PIN_RESET//反转


#define UP_STATE  GPIO_PIN_SET//上升
#define DOWN_STATE  GPIO_PIN_RESET//下降

#define OUTDISH_STATE  GPIO_PIN_RESET //倒菜
#define WASH_STATE   GPIO_PIN_SET//倒洗锅水

#define OPEN_STATE  GPIO_PIN_SET  //
#define CLOSE_STATE   GPIO_PIN_RESET//

#define ROLL_STATE  GPIO_PIN_SET  //卷膜
#define RELEASE_STATE   GPIO_PIN_RESET//释放膜

#define ENABLE_STATE  GPIO_PIN_SET
#define DISABLE_STATE  GPIO_PIN_RESET

#define ENABLE_STATE_N  GPIO_PIN_RESET
#define DISABLE_STATE_N  GPIO_PIN_SET
extern uint32_t IOFunction_Read(cookerDI IOx);

extern void IOFunction_Write(cookerDO IOx, uint16_t val);

extern int32_t IOFunction_Ctrl(cookerDO IOx, uint8_t Cmd, uint32_t Para);



typedef struct  
{
	uint16_t IOFunction;//IO的功能cookerDO 或者 cookerDI中的一种
	uint16_t IO;//底层库给的别称
} IOMapping_TypeDef;



extern uint32_t IOFunction_Read(cookerDI IOx);
extern uint32_t IOFunction_ReadDO(cookerDO IOx);

extern void IOFunction_Write(cookerDO IOx, uint16_t val);

extern int32_t IOFunction_Ctrl(cookerDO IOx, uint8_t Cmd, uint32_t Para);


#endif

