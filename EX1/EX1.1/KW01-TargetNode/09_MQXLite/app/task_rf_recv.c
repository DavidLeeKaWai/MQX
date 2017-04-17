//===========================================================================
//文件名称：task_rf_recv.c
//功能概要：放置RF接收数据帧任务
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：可根据项目需要对函数放置位置进行调整、增加command_proc()函数功能
//===========================================================================
#include "01_app_include.h"    //应用任务公共头文件

//函数声明
uint_8 FrameCheck(uint_8 *buff);
uint_8 FrameDataCheck(uint_8 *buff);
uint_8 flash_info_write(const TFlashStruct* const appinfo);
uint_8 ReadFlashInfo(uint_8 *buff);
uint_8 WriteFlashInfo(uint_8 *buff);
uint_8 RFTest();
uint_8 FlashRead();
uint_8 FlashWrite();
uint_8 FlashWritePic();
uint_8 LIGHTstate();
uint_8 command_proc();

//===========================================================================
//任务名称：task_rf_recv
//功能概要：判断RF接收事件位EVENT_RF_RECV，置一后调用FrameCheck()、
//         FrameDataCheck()函数对数据帧进行校验，校验成功后调用command_proc()函数
//         对帧命令解析与处理，并对需要回发数据的帧进行组帧、置RF发送事件位，然后
//         清除RF接收事件位，继续等待RF接收事件位置一。
//参数说明：未使用
//===========================================================================
void task_rf_recv(uint32_t initial)
{
	//1. 声明任务使用的变量
	//uint_8 offset;

	//2. 给有关变量赋初值

	//3. 进入任务循环体
	while(TRUE)
	{
		//以下加入用户程序--------------------------------------------------------
		//1） 无限等待RF接收事件位置一
		_lwevent_wait_for(&lwevent_group, EVENT_RF_RECV, FALSE, NULL);
		g_rf_sentBufLength = 6;
		//2）数据帧帧格式、节点信息校验
		if(FrameCheck(g_rf_recvBuf) == 0)
		{
			if(g_rf_recvBuf[3] != 0){
				if(g_rf_recvBuf[3] == g_tinfo.node_number ){
					g_rf_sentBuf[0] = HEAD_TERMINAL;           //帧头
					g_rf_sentBuf[1] = g_rf_sentBufLength - 3;  //有效数据长度
					g_rf_sentBuf[2] = g_rf_recvBuf[2];         //硬件地址
					g_rf_sentBuf[3] = 4;						//PCNode节点号
					g_rf_sentBuf[4] = g_rf_recvBuf[4] + g_tinfo.node_number;  //加上对应的数字（节点号）
					g_rf_sentBuf[g_rf_sentBufLength - 1] = END_TERMINAL;   //帧尾
					//置RF发送事件位，启动RF发送任务
					_lwevent_set(&lwevent_group,EVENT_RF_SEND);
				}
			}
			else{
				g_tinfo.node_number = g_rf_recvBuf[4];
				flash_info_write(&g_tinfo);
				g_rf_sentBuf[0] = HEAD_TERMINAL;           //帧头
				g_rf_sentBuf[1] = g_rf_sentBufLength - 3;  //有效数据长度
				g_rf_sentBuf[2] = g_rf_recvBuf[2];         //硬件地址
				g_rf_sentBuf[3] = 4;						//PCNode节点号
				g_rf_sentBuf[4] = 0;
				g_rf_sentBuf[g_rf_sentBufLength - 1] = END_TERMINAL;   //帧尾
				//置RF发送事件位，启动RF发送任务
				_lwevent_set(&lwevent_group,EVENT_RF_SEND);
			}
		}

		//3）清除RF接收事件位
		_lwevent_clear(&lwevent_group, EVENT_RF_RECV);
	}//任务循环体end_while
}


//============================================================================
//函数名称: FrameCheck
//功能概要: 数据帧帧格式校验
//参数说明: 数组，接收到的数据
//函数返回: 帧格式校验错误类型
//============================================================================
uint_8 FrameCheck(uint_8 *buff)
{
	uint_8 ret = 0;
	//帧头
	if(buff[0] != HEAD_PC)
	{
		ret = 1;
		goto Exit_FrameCheck;
	}
	//长度
	if(buff[1] > 61)
	{
		ret = 2;
		goto Exit_FrameCheck;
	}
	//硬件地址
	if(buff[2] != (uint_8)g_tinfo.hd_addr)
	{
		ret = 3;
		goto Exit_FrameCheck;
	}
	//帧尾
	if(buff[2 + buff[1]] != END_PC)
	{
		ret = 4;
		goto Exit_FrameCheck;
	}

Exit_FrameCheck:
	return ret;
}


//============================================================================
//函数名称: flash_info_write
//功能概要: 存储记录信息
//参数说明: 无
//函数返回: 写入FLASH记录信息的错误类型
//============================================================================
uint_8 flash_info_write(const TFlashStruct* const appinfo)
{
	DISABLE_INTERRUPTS;
	if(0 == flash_erase(APPINFO_FLASH_SECTOR))//擦出成功
    {
		if(0 == flash_write(APPINFO_FLASH_SECTOR, 0, sizeof(TFlashStruct),(uint_8*)appinfo))
		{
			return 0;//写入成功
		}
    }
	ENABLE_INTERRUPTS;//开中断

	return 1;//写入失败
}




