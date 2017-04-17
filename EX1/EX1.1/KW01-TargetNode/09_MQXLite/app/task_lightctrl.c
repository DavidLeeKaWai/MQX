/*
 * task_lightctrl.c
 *
 *  Created on: 2016年3月28日
 *      Author: asus
 */
#include "01_app_include.h"    //应用任务公共头文件
//===========================================================================
//任务名称：task_lightctrl
//功能概要：获取PC机传来的控制信息，改变小灯的状态
//                该任务优先级为14
//参数说明：未使用
//===========================================================================
void task_lightctrl(uint32_t initial_data)
{
		//1. 声明任务使用的变量
		uint_8 state;//根据PC机传来的命令确定小灯状态
		//2. 给有关变量赋初值

		//3. 进入任务循环体
		while(TRUE)
		{
			//以下加入用户程序--------------------------------------------------------
			//1）控制小灯状态
			_lwevent_wait_for(&lwevent_group, EVENT_LIGHTCTRL, FALSE, NULL);
			//等待小灯控制事件位

			if(light_temp==0)
			{
				state=0;
			}
			else
			{
				state=1;
			}
			light_control(LIGHT_ZR,state);      //改变运行小灯状态

			_lwevent_clear(&lwevent_group, EVENT_LIGHTCTRL);
			//清楚小灯事件位
		}

}







