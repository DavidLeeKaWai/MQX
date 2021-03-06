//===========================================================================
//文件名称：isr.c（ 中断底层驱动构件源文件）
//功能概要：中断服务例程存放处
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：根据实际情况更新
//===========================================================================
#include "01_app_include.h"

//===========================================================================
//ISR 名称：isr_uart0_re,UART_0（串口0）中断服务例程
//参数说明：user_isr_ptr：用户自定义参数，此处未用
//功能概要：每接收到一个字节，产生一次串口接收中断，执行本例程一次。
//         本例程对串口收到的数据，原样发送出去，实现串口数据回显功能。
//===========================================================================
void isr_uart0_re(pointer user_isr_ptr)
{
	uint_8 c;
	DISABLE_INTERRUPTS;           //关总中断
	//-----------------------------------------------------------------------
    uart_re1(UART_0, &c);         //收到的数据
    UART0_BASE_PTR->D = c;        //发送出去
    //-----------------------------------------------------------------------
	ENABLE_INTERRUPTS;            //开总中断
}

//===========================================================================
//ISR 名称：isr_gpio_cd,PTC、PTD端口中断服务例程
//参数说明：user_isr_ptr：用户自定义参数，此处未用
//功能概要：每接收到一帧64个字节的RF数据，产生一次本中断。
//         本例程对收到的数据，按照RF_ReceiveFrame函数对数据进行接收
//         组帧。接收成功后，置lwevent_group事件组的EVENT_RF_RECV事件
//         位（在"01_app_include.h"文件中声明的）。
//===========================================================================
void isr_gpio_cd(pointer user_isr_ptr)
{
	DISABLE_INTERRUPTS;                      //关总中断
	//-----------------------------------------------------------------------
    if((PORTC_PCR4 & PORT_PCR_ISF_MASK))     //DIO1中断
	{
    		//接收数据包成功，置事件位EVENT_RF_RECV，启动task_rf_recv()任务
		if(0 == RF_ReceiveFrame(g_rf_recvBuf,&g_rf_recvCount,g_tinfo.hd_addr))
		{
            _lwevent_set(&lwevent_group,EVENT_RF_RECV);
		}
		PORTC_PCR4 |= PORT_PCR_ISF_MASK; 	 //清标志位
	}
	//-----------------------------------------------------------------------
	UART0_S1|=0x1F;
    ENABLE_INTERRUPTS;                       //开总中断
}


