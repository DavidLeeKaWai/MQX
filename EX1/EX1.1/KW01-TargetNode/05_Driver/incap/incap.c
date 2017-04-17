//===========================================================================
//文件名称：incap.c
//功能概要：incap底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版    本：V3.0(WYH),20140909
//===========================================================================
#include "incap.h"

//定时器模块0,1,2地址映射
static const TPM_MemMapPtr TPM_ARR2[]={TPM0_BASE_PTR,TPM1_BASE_PTR,TPM2_BASE_PTR};

//=========================================================================
//函数名称：incap_init                                                        
//功能概要：incap模块初始化                                        
//参数说明：tpmModule:模块号：TPM0,TPM1,TPM2
//       channel:  通道号：TPMCH0,TPMCH1,TPMCH2,TPMCH3,TPMCH4,TPMCH5
//       //int_us:  周期,单位为毫秒,0.1ms=100us取值100,最大不超过20000,int_us/2中断一次
//函数说明：PTA12口(TPM0CH1)为采样引脚,采样周期一定要是样本周期的1/2以下
//=========================================================================
//void incap_init(uint_8 tpmModule,uint_8 channel,uint_32 int_us)
void incap_init(uint_8 tpmModule,uint_8 channel)
{
	//参数检查
    if(tpmModule > TPM2) tpmModule = TPM2;
    //根据入口参数（tpmModule-模块号）执行不同程序
	if(TPM0 == tpmModule)
	{
		//参数防错
		if(channel > TPMCH5) channel = TPMCH5;
		//根据入口参数（channel-通道号）执行不同程序
		switch(channel)
		{
		case 0:
			PORTC_PCR1 = PORT_PCR_ISF_MASK |PORT_PCR_MUX(0x4);
			break;
		case 1:
            #if (TPM0_CH1_PIN == 1)
			PORTA_PCR4 = PORT_PCR_ISF_MASK |PORT_PCR_MUX(0x3);
            #endif

            #if (TPM0_CH1_PIN == 2)
			PORTC_PCR2 = PORT_PCR_ISF_MASK |PORT_PCR_MUX(0x4);
            #endif
			break;

		case 4:
			PORTD_PCR4 = PORT_PCR_ISF_MASK |PORT_PCR_MUX(0x4);
			break;

		case 5:
			PORTD_PCR5 = PORT_PCR_ISF_MASK |PORT_PCR_MUX(0x4);
			break;
		default:
			break;
		}
	}
	else if(TPM1 == tpmModule)
	{
		if(channel > TPMCH1)
			channel = TPMCH1;
		switch(channel)
		{
		case 0:
			PORTB_PCR0 = PORT_PCR_ISF_MASK |PORT_PCR_MUX(0x3)| PORT_PCR_DSE_MASK;
			break;
		case 1:
			PORTB_PCR1 = PORT_PCR_ISF_MASK |PORT_PCR_MUX(0x3)| PORT_PCR_DSE_MASK;
			break;
		default:
			break;
		}
	}
	else if(TPM2 == tpmModule)
	{
		if(channel > TPMCH1)
			channel = TPMCH1;
		switch(channel)
		{
		case 0:
            #if (TPM2_CH0_PIN == 1)
			PORTB_PCR2 = PORT_PCR_ISF_MASK |PORT_PCR_MUX(0x3);
            #endif

            #if (TPM2_CH0_PIN == 2)
			PORTA_PCR1 = PORT_PCR_ISF_MASK |PORT_PCR_MUX(0x3);
            #endif
			break;
		case 1:
			PORTA_PCR2 = PORT_PCR_ISF_MASK |PORT_PCR_MUX(0x3);
			break;

		default:
			break;
		 }
	}

	     //开启时钟默认选择用PLL/2时钟源48MHz
	     SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);
	     SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	     //开启SIM时钟门
	     BSET(SIM_SCGC6_TPM0_SHIFT+tpmModule,SIM_SCGC6);
//	     int_us = 24000*int_us/1000;
	     TPM_ARR2[tpmModule]->CNT = 0;
	     TPM_ARR2[tpmModule]->MOD = TPM0CH1MOD;

	     //中断使能，模式选择
	     TPM_ARR2[tpmModule]->SC=TPM_SC_TOIE_MASK|TPM_SC_CMOD(1)|TPM_SC_PS(7);
	     TPM_ARR2[tpmModule]->SC=TPM_SC_CMOD(1)|TPM_SC_PS(7);
	     //设置在上升沿捕捉
	     TPM_CnSC_REG(TPM_ARR2[tpmModule],channel)=TPM_CnSC_ELSA_MASK|TPM_CnSC_CHIE_MASK;
	     TPM_CnV_REG(TPM_ARR2[tpmModule],channel)=0;           //CnV寄存器啊的值在此处无效
	     //使能NVIC中断
	     //enable_irq(TPM0_IRQ_NO+tpmModule);
}

//=========================================================================
//函数名称：incap_stop
//功能概要：关闭输入捕捉模块
//参数说明：tpmModule(模块号)：TPM0,TPM1,TPM2
//函数返回：无
//=========================================================================
void incap_stop(uint_8 tpmModule)
{
	if(tpmModule<=TPM2)
	    BCLR(SIM_SCGC6_TPM0_SHIFT + tpmModule,SIM_SCGC6);
}

//=========================================================================
//函数名称：incap_enable_int
//功能概要：使能输入捕捉中断
//参数说明：tpmModule(模块号)：TPM0,TPM1,TPM2
//函数返回：无
//=========================================================================
void incap_enable_int(uint_8 tpmModule)
{
	if(tpmModule<=TPM2) enable_irq(TPM0_IRQ_NO + tpmModule);
}

//=========================================================================
//函数名称：incap_disable_int
//功能概要：禁止输入捕捉中断
//参数说明：tpmModule(模块号)：TPM0,TPM1,TPM2
//函数返回：无
//=========================================================================
void incap_disable_int(uint_8 tpmModule)
{
	if(tpmModule<=TPM2) disable_irq(TPM0_IRQ_NO + tpmModule);
}

//=========================================================================
//函数名称：incap_disable_int
//功能概要：禁止输入捕捉中断
//参数说明：tpmModule(模块号)：TPM0,TPM1,TPM2
//函数返回：无
//=========================================================================
void incap_counter_clear(uint_8 tpmModule)
{
	TPM_ARR2[tpmModule]->CNT = 0;
}

