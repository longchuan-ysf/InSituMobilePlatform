/*************************************************************************************************** 
                                   xxxx公司
  
                  

文件:   CookDriveTask.c 
作者:   龙川
说明:   炒菜机驱动任务，包括各个电机控制任务 ————————其实最开始规划错了应该是5个同步任务——不仅仅用来执行电机控制，其他都可以
		各个模组控制任务
		目前都是使用邮箱的方式传递函数然后再任务中执行函数
		电机用邮箱就够了（因为是邮箱所以一次只能处理一个动作--邮箱只保存最新的消息），正常电机也应该这样
		模组用消息队列，可以按入队的顺序执行命令
***************************************************************************************************/
#include "PlatformManage.h"
#include "PlatformDrive.h"
#include "UserVars.h"
#include "OSVars.h"


 /**
 ****************************************************************************************
 @brief:	Motor_PanRiseFallTask 升降电机
 @Input：	NULL
 @Output：  NULL
 @Return	NULL
 @Warning:	NULL  
 @note: 	龙川2019-6-4
 ****************************************************************************************
  **/
void Motor_PanRiseFallTask(void *p_arg)
{
	INT8U err;
	APP_FuncMboxMsgStruct  *pFuncMboxMsg;
	printf("Motor_PanRiseFallTask");
	
	while(1)
	{
		// 获取邮箱中的函数，然后执行这些函数可以是升降电机的原点找寻函数 升降电机的控制函数等等
		pFuncMboxMsg = OSMboxPend(OSMboxX_Motor, 0, &err);
		if (err==OS_ERR_NONE)
		{
			//下面这些代码后面几个电机都是相同的，但是不做成一个函数，因为做成函数要考虑共享资源的访问问题
			switch(pFuncMboxMsg->ArgcNum)
			{
				case 0:
				{
					pFuncMboxMsg->FuncZeroArgc();
				}
				break;
				case 1:
				{
					pFuncMboxMsg->FuncOneArgc(pFuncMboxMsg->FuncArgc1);
				}
				break;
				case 2:
				{
					pFuncMboxMsg->FuncTwoArgc(pFuncMboxMsg->FuncArgc1,pFuncMboxMsg->FuncArgc2);
				}
				break;
				case 3:
				{
					pFuncMboxMsg->FuncThreeArgc(pFuncMboxMsg->FuncArgc1,pFuncMboxMsg->FuncArgc2,pFuncMboxMsg->FuncArgc3);
				}
				break;
				case 4:
				{
					pFuncMboxMsg->FuncFourArgc(pFuncMboxMsg->FuncArgc1,pFuncMboxMsg->FuncArgc2,pFuncMboxMsg->FuncArgc3,pFuncMboxMsg->FuncArgc4);
				}
				break;
			}
		}
	}
}
/**
 ****************************************************************************************
 @brief:	Motor_PanRotateTask 转锅电机
 @Input：	NULL
 @Output：  NULL
 @Return	NULL
 @Warning:	NULL  
 @note: 	龙川2019-6-4
 ****************************************************************************************
  **/
void Motor_PanRotateTask(void *p_arg)
{
	APP_FuncMboxMsgStruct  *pFuncMboxMsg;
	INT8U err;
	while(1)
	{
		// 获取邮箱中的函数
		pFuncMboxMsg = OSMboxPend(OSMboxY_Motor, 0, &err);
		if (err==OS_ERR_NONE)
		{
			switch(pFuncMboxMsg->ArgcNum)
			{
				case 0:
				{
					pFuncMboxMsg->FuncZeroArgc();
				}
				break;
				case 1:
				{
					pFuncMboxMsg->FuncOneArgc(pFuncMboxMsg->FuncArgc1);
				}
				break;
				case 2:
				{
					pFuncMboxMsg->FuncTwoArgc(pFuncMboxMsg->FuncArgc1,pFuncMboxMsg->FuncArgc2);
				}
				break;
				case 3:
				{
					pFuncMboxMsg->FuncThreeArgc(pFuncMboxMsg->FuncArgc1,pFuncMboxMsg->FuncArgc2,pFuncMboxMsg->FuncArgc3);
				}
				break;
				case 4:
				{
					pFuncMboxMsg->FuncFourArgc(pFuncMboxMsg->FuncArgc1,pFuncMboxMsg->FuncArgc2,pFuncMboxMsg->FuncArgc3,pFuncMboxMsg->FuncArgc4);
				}
				break;
			}
		}
	}
}

/**
 ****************************************************************************************
 @brief:	Func_UniversalSynchTask 通用同步功能
 @Input：	NULL
 @Output：  NULL
 @Return	NULL
 @Warning:	NULL  
 @note: 	这个可以用来同步执行模块功能，也可以用来执行其他同步，
			只需要保证前后两个动作不是同时进行,因为任务中是顺序执行，任务之间通过
			时间片轮询的方式实现类似同步的效果
 ****************************************************************************************
  **/
void Func_UniversalSynchTask(void *p_arg)
{
	APP_FuncMboxMsgStruct  *pFuncMboxMsg;
	INT8U err;
	while(1)
	{
		// 获取邮箱中的函数
		pFuncMboxMsg = OSQPend(OSQUniversalSynchFun, 0, &err);
		if (err==OS_ERR_NONE)
		{
			switch(pFuncMboxMsg->ArgcNum)
			{
				case 0:
				{
					pFuncMboxMsg->FuncZeroArgc();
				}
				break;
				case 1:
				{
					pFuncMboxMsg->FuncOneArgc(pFuncMboxMsg->FuncArgc1);
				}
				break;
				case 2:
				{
					pFuncMboxMsg->FuncTwoArgc(pFuncMboxMsg->FuncArgc1,pFuncMboxMsg->FuncArgc2);
				}
				break;
				case 3:
				{
					pFuncMboxMsg->FuncThreeArgc(pFuncMboxMsg->FuncArgc1,pFuncMboxMsg->FuncArgc2,pFuncMboxMsg->FuncArgc3);
				}
				break;
				case 4:
				{
					pFuncMboxMsg->FuncFourArgc(pFuncMboxMsg->FuncArgc1,pFuncMboxMsg->FuncArgc2,pFuncMboxMsg->FuncArgc3,pFuncMboxMsg->FuncArgc4);
				}
				break;
			}
		}
	}
}