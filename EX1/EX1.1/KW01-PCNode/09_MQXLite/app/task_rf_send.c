//===========================================================================
//文件名称：task_rf_send.c
//功能概要：放置RF发送数据帧任务
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：根据需要更新
//===========================================================================
#include "01_app_include.h"    //应用任务公共头文件

//===========================================================================
//任务名称：task_rf_send
//功能概要：判断RF发送事件位Event_RF_Send，调用RF_SendData()函数转发接收测试数据包；
//参数说明：未使用
//===========================================================================
void task_rf_send(uint32_t initial)
{	
	//1. 声明任务使用的变量
	uint_8 i;
	uint_8 rf_sentDataLen;

	//2. 给有关变量赋初值

	//3. 进入任务循环体
	while(TRUE) 
	{
		//以下加入用户程序--------------------------------------------------------
		//1）无限等待RF发送事件位置一
		_lwevent_wait_for(&lwevent_group, EVENT_RF_SEND, FALSE, NULL);

//		rf_sentDataLen = g_uart_recvBuf[1]-1;  //需要RF转发的字节数
//
//		for (i=0;i<rf_sentDataLen;i++) g_rf_sentBuf[i]=g_uart_recvBuf[i+3];
//
//		RFSendDataByCSMACA(rf_sentDataLen,&g_rf_sentBuf[0],0,g_rf_hdaddr);

		rf_sentDataLen = g_uart_recvBuf[1]+3;  //需要RF转发的字节数

		for (i=0;i<rf_sentDataLen;i++) g_rf_sentBuf[i]=g_uart_recvBuf[i];

		RFSendDataByCSMACA(rf_sentDataLen,&g_rf_sentBuf[0],0,g_rf_hdaddr);


		//清除RF发送事件位
		_lwevent_clear(&lwevent_group, EVENT_RF_SEND);

	}//任务循环体end_while
}
