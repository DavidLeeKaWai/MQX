//===========================================================================
//文件名称：03_task_main.c（主任务函数）
//功能概要：放置MQXLite的自启动任务
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：可根据项目需要对函数放置位置进行调整
//===========================================================================
#include "01_app_include.h"

__attribute__((section (".romsymbols"))) const uint_8 mydata[4] = {0x55, 0xAA, 0x43, 0x45};
//============================================================================
//函数名称: flash_info_read
//功能概要: 读取存储记录信息
//参数说明: 无
//函数返回: 无
//============================================================================
void flash_info_read(TFlashStruct* appinfo)
{
    uint_8* pbuf;
    uint_8* address =  (uint_8*)(APPINFO_FLASH_SECTOR * SIZE_FLASHPAGE);
    uint_8 i;
    pbuf = (uint_8*)(appinfo);
    for(i=0; i < sizeof(TFlashStruct);i++)
		pbuf[i] = address[i];
}

//===========================================================================
//任务名称：task_main
//功能概要：MQX自启动任务，主要实现任务变量初始化、创建其他任务、安装用户ISR
//参数说明：未使用
//===========================================================================
void task_main(uint32_t initial_data)
{
	//uint_8 i;
	
	//1. 声明主任务使用的变量
	//创建轻量级事件组
	_lwevent_create(&lwevent_group,0);

    //2. 关总中断
    DISABLE_INTERRUPTS;

    //3. 初始化外设模块
    uart_init(UART_0,MCGFLLCLK,115200);    //初始化UART_0模块
    light_init(LIGHT_RUN_1,LIGHT_OFF);     //初始化节点的运行指示灯1
    light_init(PORTB|(1),LIGHT_ON);     //初始化节点的运行指示灯1

	 flash_init();                          //初始化Flash



	//读FLASH存储信息
	flash_info_read(&g_tinfo);
	//记录信息不正确，采用默认信息
	if(g_tinfo.hd_addr == 0xFFFF || g_tinfo.node_number == 0xFFFF)
	{
		g_tinfo.hd_addr = 0xFF;
		g_tinfo.node_number = 0;

	}

    RF_Init((uint_8)g_tinfo.hd_addr);		//RF模块初始化

    //4. 给有关变量赋初值

    //5. 创建其他任务
    _task_create_at(0, TASK_LIGHT,   0, task_light_stack,   TASK_LIGHT_STACK_SIZE);
    _task_create_at(0, TASK_RF_RECV, 0, task_rf_recv_stack, TASK_RF_RECV_STACK_SIZE);
    _task_create_at(0, TASK_RF_SEND, 0, task_rf_send_stack, TASK_RF_SEND_STACK_SIZE);

    //6. 安装用户ISR
    _int_install_isr(INT_UART0,isr_uart0_re,NULL);//串口0的ISR
    _int_install_isr(INT_PORTD,isr_gpio_cd,NULL); //PTC、PTD的ISR，端口C和D共用同一中断向量

    //7. 使能模块中断
    uart_enable_re_int(UART_0);

	//8. 开总中断
	ENABLE_INTERRUPTS;

    //------------执行完毕，本任务进入阻塞态----------------------------------------------
    _task_block();
}
