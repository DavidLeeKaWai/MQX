//===========================================================================
//文件名称：01_app_include.h
//功能概要：应用任务公共头文件（MQX中头文件及相关全局变量、任务参数的声明等）
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：根据需要更新
//===========================================================================

#ifndef __01_APP_INCLUDE_H_
#define __01_APP_INCLUDE_H_

//---------------------------------------------------------------------------
// 第一部分
// 包含头文件、宏定义常量、声明全局变量、声明轻量级事件组、定义事件位
//---------------------------------------------------------------------------
//1.1 包含头文件
#include "bsp.h"
#include "stdint.h"
#include "mqxlite.h"
#include "mqx_inc.h"
#include "light.h"
#include "lwevent.h"
#include "rf.h"
#include "lwmsgq.h"
#include "adc.h"
#include "pit.h"
#include "mutex.h"
#include "flash.h"
#include "incap.h"

//1.2 宏定义常量
#define HEAD_PC        'P'         //上位机发送帧帧头
#define END_PC         'C'         //上位机发送帧帧尾
#define HEAD_TERMINAL  'T'         //目标节点返回帧帧头
#define END_TERMINAL   'D'         //目标节点返回帧帧尾

#define DELAY_TIMES       200      //延时次数

#define APPINFO_FLASH_SECTOR  127  //节点FLASH信息存储页号，数据按照TFlashStruct结构体进行放置

//命令及回发命令类型，发送命令字与回发命令字相同，帧最大差异体现在帧头、帧尾
enum eAppCmd
{
	eAPPCMD_SYSPARAMREAD  = 0x00,       //0x00. 读取目标节点的系统参数（127页）
	eAPPCMD_SYSPARAMWRITE = 0x01,       //0x01. 写入目标节点的系统参数（127页）

	//增加命令
	eAPPCMD_RFTEST = 0x02,              // 验证RF收发
	eAPPCMD_LIGHTCTRL = 0x03,              //灯控命令字

	eAPPCMD_FLASHREAD  = 0x04,      //读取FLASH指定页内容
	eAPPCMD_FLASHWRITE = 0x05,      //写入FLASH指定页内容
	eAPPCMD_FLASHWRITEPICTURE = 0x06,      //写入FLASH图片

	eAPPCMD_MAX,
};



//1.3 宏定义变量
uint_8 g_rf_recvBuf[64];           //RF接收数据缓冲区
uint_8 g_rf_sentBuf[64];          //RF发送数据缓冲区
uint_8 g_rf_recvCount;            //有效帧长
uint_8 g_rf_sentBufLength;     //RF发送数据长度
uint_8 light_temp;                  //接收小灯状态命令
float  g_temperature;             //芯片温度
uint_8 Pic_Arr[4000];              //flash接收数据缓冲区

uint_8 PicZhenNum;              //图片帧数
//uint_16 PicByteCount;            //图片字节数
uint_8 RevZhenCount;            //收到的图片帧数

//1.4 声明轻量级事件组
LWEVENT_STRUCT  lwevent_group;

//1.5 宏定义事件位
#define EVENT_RF_RECV     ((1uL)<<(1))   //RF接收事件位
#define EVENT_RF_SEND     ((1uL)<<(2))   //RF发送事件位
#define EVENT_LIGHTCTRL     ((1uL)<<(3))   //灯控事件位
#define EVENT_WRITEPIC     ((1uL)<<(4))   //写图片事件位

typedef struct{
    uint_8  hd_addr;           //硬件地址
    uint_8 node_number;         //节点号
}TFlashStruct;

TFlashStruct g_tinfo;

//---------------------------------------------------------------------------
// 第二部分
// 新建任务的相关定义
//---------------------------------------------------------------------------
// 添加任务的步骤
// (1) 在02_task_templates.c中任务模板列表中添加任务模板 （任务编号,任务函数,任务栈大小,优先级,任务名,任务属性）
// (2) 在01_app_include.h中宏定义任务编号、宏定义任务栈大小、声明任务函数、声明任务栈
// (3) 在03_task_main.c的自启动任务中，创建任务_task_create
//---------------------------------------------------------------------------
//2.1 宏定义任务编号
#define TASK_MAIN          1
#define TASK_LIGHT         2
#define TASK_RF_RECV       3
#define TASK_RF_SEND       4
//2.2 宏定义任务栈大小
#define TASK_MAIN_STACK_SIZE       (sizeof(TD_STRUCT) + 1024 + PSP_STACK_ALIGNMENT + 1)
#define TASK_LIGHT_STACK_SIZE      (sizeof(TD_STRUCT) + 200 + PSP_STACK_ALIGNMENT + 1)
#define TASK_RF_RECV_STACK_SIZE    (sizeof(TD_STRUCT) + 1024 + PSP_STACK_ALIGNMENT + 1)
#define TASK_RF_SEND_STACK_SIZE    (sizeof(TD_STRUCT) + 512 + PSP_STACK_ALIGNMENT + 1)
//2.3 声明任务函数
void task_main(uint32_t initial_data);
void task_light(uint32_t initial_data);
void task_rf_recv(uint32_t initial_data);
void task_rf_send(uint32_t initial_data);
//2.4 声明任务栈
uint_8 task_main_stack[TASK_MAIN_STACK_SIZE];
uint_8 task_light_stack[TASK_LIGHT_STACK_SIZE];
uint_8 task_rf_recv_stack[TASK_RF_RECV_STACK_SIZE];
uint_8 task_rf_send_stack[TASK_RF_SEND_STACK_SIZE];

//---------------------------------------------------------------------------
#endif    //01_app_include.h

