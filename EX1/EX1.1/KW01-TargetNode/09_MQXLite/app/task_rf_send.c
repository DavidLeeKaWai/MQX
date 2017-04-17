//===========================================================================
//文件名称：task_rf_send.c
//功能概要：放置RF发送数据帧任务
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：无需更改
//===========================================================================
#include "01_app_include.h"    //应用任务公共头文件

//===========================================================================
//任务名称：task_rf_send
//功能概要：判断RF发送事件位EVENT_RF_SEND，
//                置一后调用RFSendDataByCSMACA()函数转发
//                接收数据包，然后清除RF发送事件位，继续等待RF发送事件位置一。
//参数说明：未使用
//===========================================================================
void task_rf_send(uint32_t initial)
{	
	//1. 声明任务使用的变量

	//2. 给有关变量赋初值

	//3. 进入任务循环体
	while(TRUE)
	{
		//以下加入用户程序--------------------------------------------------------
		//1）无限等待RF发送事件位置一
		_lwevent_wait_for(&lwevent_group, EVENT_RF_SEND, FALSE, NULL);

		// 保护数据发送
		DISABLE_INTERRUPTS;      //关总中断

		//2）调用RFSendDataByCSMACA()函数发送数据包
		RFSendDataByCSMACA(g_rf_sentBufLength,&g_rf_sentBuf[0],0,(uint_8)g_tinfo.hd_addr);

		ENABLE_INTERRUPTS;       //开总中断

		//3） 清除RF发送事件位
		_lwevent_clear(&lwevent_group, EVENT_RF_SEND);

	}// 任务循环体end_while
}
