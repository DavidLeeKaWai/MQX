//===========================================================================
//�ļ����ƣ�adc.c
//���ܸ�Ҫ��ADC�ײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2013-4-7   V1.0
//===========================================================================
#include "adc.h"

//===========================================================================
//�������ƣ�adc_init
//���ܸ�Ҫ����ʼ��adcģ��
//����˵����chnGroupͨ��ѡ�����ã�Aͨ��MUXSEL_A��Bͨ��MUXSEL_B
//         diff����ģʽ����������SINGLE_END, �������DIFFERENTIAL
//         accurary��������:����8-12-10-16�����9-13-11-16
//         HardwareAverageӲ���˲���sample4/sample8/sample16/sample32
//===========================================================================

void adc_init( uint_8 chnGroup,uint_8 diff,uint_8 accurary,uint_8 HDAve)
{
	uint_8 ADCCfg1;
//	uint_8 ADCCfg2=0;
	//1.��ADC0ģ��ʱ��
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
    //2.����CFG1�Ĵ���:�������ģ�����ʱ��4��Ƶ������ʱ��/2��������ʱ��
	//2.1 ���ݲ�������ȷ��ADC_CFG1_MODEλ
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
	//2.2 ������������ֵ���������ģ�����ʱ��4��Ƶ������ʱ��/2��������ʱ�䣩
	ADCCfg1 |=  (ADC_CFG1_ADIV(2) | ADC_CFG1_ADICLK(1) | ADC_CFG1_ADLSMP_MASK);
	//2.3 ��������
	ADC0_CFG1 = ADCCfg1;
	//3.����ͨ���飬����CFG2�Ĵ���
	//3.1����CFG2�Ĵ���
	ADC0_CFG2&=~(ADC_CFG2_ADACKEN_MASK     //�첽ʱ�������ֹ
               + ADC_CFG2_ADHSC_MASK       //��ͨת��
               + ADC_CFG2_ADLSTS_MASK);    //Ĭ�������ʱ��
	//3.2ѡ��aͨ������bͨ��
	if(MUXSEL_A==chnGroup)
	{
    ADC0_CFG2 &=~(1<<ADC_CFG2_MUXSEL_SHIFT);        //ѡ��aͨ��
	}
	else
	{
	ADC0_CFG2 |=(1<<ADC_CFG2_MUXSEL_SHIFT);        //ѡ��bͨ��
	}
	//4.����ADC0_SC2������������ȽϹ��ܽ��ã�DMA���ã�Ĭ���ⲿ�ο���ѹ VREFH/VREFL
    ADC0_SC2 = 0;
    //5.ADC0_SC3�Ĵ���Ӳ����ֵʹ�ܣ�����Ӳ���˲�����
    ADC0_SC3 |= (ADC_SC3_ADCO_MASK | ADC_SC3_AVGE_MASK | ADC_SC3_AVGS((uint_8)HDAve));
    //ѡ����������ǵ�������
    (DIFFERENTIAL == diff)?(ADC0_SC1A |= (ADC_SC1_DIFF_MASK)):(ADC0_SC1A &= ~(ADC_SC1_DIFF_MASK ));
    //����ADCģ���ж�
    ADC0_SC1A &= ~(ADC_SC1_AIEN_MASK);
}

//============================================================================
//�������ƣ�adc_read
//���ܸ�Ҫ����ʼ��adcģ��                                                
//����˵����channel���������� ͨ����Χ 0~ 23
//               �������ͨ����Χ 0~ 3
//============================================================================

uint_16 adc_read(uint_8 channel)
{
	uint_16 ADCResult = 0;
	
	//����SC1A�Ĵ���ͨ����
	ADC0_SC1A = ADC_SC1_ADCH(channel);		
	
	//�ȴ�ת�����
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));

	//��ȡת�����
	ADCResult = (uint_16)ADC0_RA;
	//��ADCת����ɱ�־
	ADC0_SC1A &= ~ADC_SC1_COCO_MASK;
	//���ض�ȡ���
	return ADCResult;
}

//============================================================================
//�������ƣ�adc_cal
//���ܸ�Ҫ��adcģ��У�����ܺ���       
//˵������У��֮ǰ������ȷ����ADCʱ�ӡ�����ʱ�䡢ģʽ��Ӳ���˲�32�Σ����KL25оƬ�ֲ�28.4.6
//============================================================================
uint_8 adc_cal()
{
	uint_8 cal_var;
  
  ADC0_SC2 &=  ~ADC_SC2_ADTRG_MASK ; // ʹ���������   
  ADC0_SC3 &= ( ~ADC_SC3_ADCO_MASK & ~ADC_SC3_AVGS_MASK ); //����ת��
  ADC0_SC3 |= ( ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(SAMPLE32) );  //Ӳ��ƽ���˲�32��  
  ADC0_SC3 |= ADC_SC3_CAL_MASK ;      //��ʼУ��
  while (!(ADC0_SC1A & ADC_SC1_COCO_MASK)); // �ȴ�ת�����
  	
  if (ADC0_SC3& ADC_SC3_CALF_MASK)
  {  
   return(1);    // У��ʧ��
  }
  
  // ������������У��
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
 
  // ���㸺������У��
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
  
  ADC0_SC3 &= ~ADC_SC3_CAL_MASK ; //��CAL

  return(0);
}


//20150119
//adc_mid:1·A/Dת������(��ֵ�˲�)------------------------------------------
//����:��ȡͨ��channel��ֵ�˲����A/Dת�����
//����:channel = ͨ����
//����:��ͨ����ֵ�˲����A/Dת�����
//�ڲ�����:ADCValue
//-------------------------------------------------------------------------
uint_16 adc_mid(uint_8 channel)
{
    uint_16 i,j,k,tmp;

    //1.ȡ����A/Dת�����
    i = adc_read(channel);
    j = adc_read(channel);
    k = adc_read(channel);
    tmp = (i > j) ? i : j;
    tmp = (tmp > k) ? tmp : k;

    return tmp;
}

//adc_ave:1·A/Dת������(��ֵ�˲�)------------------------------------------
//����:ͨ��channel����n����ֵ�˲�,���������ֵ,�ó���ֵ�˲����
//����:channel = ͨ����,n = ��ֵ�˲�����
//����:��ͨ����ֵ�˲����A/Dת�����
//�ڲ�����:adc_mid
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

