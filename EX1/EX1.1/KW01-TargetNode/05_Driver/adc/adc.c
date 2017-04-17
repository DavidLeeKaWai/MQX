//===========================================================================
//文件名称：adc.c
//功能概要：ADC底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2013-4-7   V1.0
//===========================================================================
#include "adc.h"

//===========================================================================
//函数名称：adc_init
//功能概要：初始化adc模块
//参数说明：chnGroup通道选择配置：A通道MUXSEL_A，B通道MUXSEL_B
//         diff配置模式：单端输入SINGLE_END, 差分输入DIFFERENTIAL
//         accurary采样精度:单端8-12-10-16；差分9-13-11-16
//         HardwareAverage硬件滤波：sample4/sample8/sample16/sample32
//===========================================================================

void adc_init( uint_8 chnGroup,uint_8 diff,uint_8 accurary,uint_8 HDAve)
{
	uint_8 ADCCfg1;
//	uint_8 ADCCfg2=0;
	//1.打开ADC0模块时钟
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
    //2.配置CFG1寄存器:正常功耗，总线时钟4分频，总线时钟/2，常采样时间
	//2.1 根据采样精度确定ADC_CFG1_MODE位
	switch(accurary)
	{
	    case 8:case 9:
		    ADCCfg1 = ADC_CFG1_MODE(0);
		    break;
	    case 12:case 13:
		    ADCCfg1 = ADC_CFG1_MODE(1);
		    break;
	    case 10:case 11:
		    ADCCfg1 = ADC_CFG1_MODE(2);
		    break;
	    default:
		    ADCCfg1 = ADC_CFG1_MODE(3);
		    break;
 	}
	//2.2 继续计算配置值（正常功耗，总线时钟4分频，总线时钟/2，常采样时间）
	ADCCfg1 |=  (ADC_CFG1_ADIV(2) | ADC_CFG1_ADICLK(1) | ADC_CFG1_ADLSMP_MASK);
	//2.3 进行配置
	ADC0_CFG1 = ADCCfg1;
	//3.根据通道组，配置CFG2寄存器
	//3.1配置CFG2寄存器
	ADC0_CFG2&=~(ADC_CFG2_ADACKEN_MASK     //异步时钟输出禁止
               + ADC_CFG2_ADHSC_MASK       //普通转换
               + ADC_CFG2_ADLSTS_MASK);    //默认最长采样时间
	//3.2选择a通道或者b通道
	if(MUXSEL_A==chnGroup)
	{
    ADC0_CFG2 &=~(1<<ADC_CFG2_MUXSEL_SHIFT);        //选择a通道
	}
	else
	{
	ADC0_CFG2 |=(1<<ADC_CFG2_MUXSEL_SHIFT);        //选择b通道
	}
	//4.配置ADC0_SC2：软件触发，比较功能禁用；DMA禁用；默认外部参考电压 VREFH/VREFL
    ADC0_SC2 = 0;
    //5.ADC0_SC3寄存器硬件均值使能，配置硬件滤波次数
    ADC0_SC3 |= (ADC_SC3_ADCO_MASK | ADC_SC3_AVGE_MASK | ADC_SC3_AVGS((uint_8)HDAve));
    //选择差分输入或是单端输入
    (DIFFERENTIAL == diff)?(ADC0_SC1A |= (ADC_SC1_DIFF_MASK)):(ADC0_SC1A &= ~(ADC_SC1_DIFF_MASK ));
    //禁用ADC模块中断
    ADC0_SC1A &= ~(ADC_SC1_AIEN_MASK);
}

//============================================================================
//函数名称：adc_read
//功能概要：初始化adc模块                                                
//参数说明：channel：单端输入 通道范围 0~ 23
//               差分输入通道范围 0~ 3
//============================================================================

uint_16 adc_read(uint_8 channel)
{
	uint_16 ADCResult = 0;
	
	//设置SC1A寄存器通道号
	ADC0_SC1A = ADC_SC1_ADCH(channel);		
	
	//等待转换完成
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));

	//读取转换结果
	ADCResult = (uint_16)ADC0_RA;
	//清ADC转换完成标志
	ADC0_SC1A &= ~ADC_SC1_COCO_MASK;
	//返回读取结果
	return ADCResult;
}

//============================================================================
//函数名称：adc_cal
//功能概要：adc模块校正功能函数       
//说明：在校正之前，须正确配置ADC时钟、采样时间、模式、硬件滤波32次，详见KL25芯片手册28.4.6
//============================================================================
uint_8 adc_cal()
{
	uint_8 cal_var;
  
  ADC0_SC2 &=  ~ADC_SC2_ADTRG_MASK ; // 使能软件触发   
  ADC0_SC3 &= ( ~ADC_SC3_ADCO_MASK & ~ADC_SC3_AVGS_MASK ); //单次转换
  ADC0_SC3 |= ( ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(SAMPLE32) );  //硬件平均滤波32次  
  ADC0_SC3 |= ADC_SC3_CAL_MASK ;      //开始校验
  while (!(ADC0_SC1A & ADC_SC1_COCO_MASK)); // 等待转换完成
  	
  if (ADC0_SC3& ADC_SC3_CALF_MASK)
  {  
   return(1);    // 校正失败
  }
  
  // 计算正向输入校正
  cal_var = 0x00;
  cal_var =  ADC0_CLP0; 
  cal_var += ADC0_CLP1;
  cal_var += ADC0_CLP2;
  cal_var += ADC0_CLP3;
  cal_var += ADC0_CLP4;
  cal_var += ADC0_CLPS;

  cal_var = cal_var/2;
  cal_var |= 0x8000;   //Set MSB

  ADC0_PG = ADC_PG_PG(cal_var);
 
  // 计算负向输入校正
  cal_var = 0x00;
  cal_var =  ADC0_CLM0; 
  cal_var += ADC0_CLM1;
  cal_var += ADC0_CLM2;
  cal_var += ADC0_CLM3;
  cal_var += ADC0_CLM4;
  cal_var += ADC0_CLMS;

  cal_var = cal_var/2;

  cal_var |= 0x8000; // Set MSB

  ADC0_MG = ADC_MG_MG(cal_var); 
  
  ADC0_SC3 &= ~ADC_SC3_CAL_MASK ; //清CAL

  return(0);
}


//20150119
//adc_mid:1路A/D转换函数(中值滤波)------------------------------------------
//功能:获取通道channel中值滤波后的A/D转换结果
//参数:channel = 通道号
//返回:该通道中值滤波后的A/D转换结果
//内部调用:ADCValue
//-------------------------------------------------------------------------
uint_16 adc_mid(uint_8 channel)
{
    uint_16 i,j,k,tmp;

    //1.取三次A/D转换结果
    i = adc_read(channel);
    j = adc_read(channel);
    k = adc_read(channel);
    tmp = (i > j) ? i : j;
    tmp = (tmp > k) ? tmp : k;

    return tmp;
}

//adc_ave:1路A/D转换函数(均值滤波)------------------------------------------
//功能:通道channel进行n次中值滤波,求和再作均值,得出均值滤波结果
//参数:channel = 通道号,n = 中值滤波次数
//返回:该通道均值滤波后的A/D转换结果
//内部调用:adc_mid
//-------------------------------------------------------------------------
uint_16 adc_ave(uint_8 channel, uint_8 n)
{
    uint_16 i;
    uint_32 j;

    j = 0;
    for (i = 0; i < n; i++)
        j += adc_mid(channel);
    j = j/n;

    return (uint_16)j;
}

