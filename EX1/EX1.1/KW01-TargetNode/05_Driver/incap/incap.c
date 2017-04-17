//===========================================================================
//�ļ����ƣ�incap.c
//���ܸ�Ҫ��incap�ײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//��    ����V3.0(WYH),20140909
//===========================================================================
#include "incap.h"

//��ʱ��ģ��0,1,2��ַӳ��
static const TPM_MemMapPtr TPM_ARR2[]={TPM0_BASE_PTR,TPM1_BASE_PTR,TPM2_BASE_PTR};

//=========================================================================
//�������ƣ�incap_init                                                        
//���ܸ�Ҫ��incapģ���ʼ��                                        
//����˵����tpmModule:ģ��ţ�TPM0,TPM1,TPM2
//       channel:  ͨ���ţ�TPMCH0,TPMCH1,TPMCH2,TPMCH3,TPMCH4,TPMCH5
//       //int_us:  ����,��λΪ����,0.1ms=100usȡֵ100,��󲻳���20000,int_us/2�ж�һ��
//����˵����PTA12��(TPM0CH1)Ϊ��������,��������һ��Ҫ���������ڵ�1/2����
//=========================================================================
//void incap_init(uint_8 tpmModule,uint_8 channel,uint_32 int_us)
void incap_init(uint_8 tpmModule,uint_8 channel)
{
	//�������
    if(tpmModule > TPM2) tpmModule = TPM2;
    //������ڲ�����tpmModule-ģ��ţ�ִ�в�ͬ����
	if(TPM0 == tpmModule)
	{
		//��������
		if(channel > TPMCH5) channel = TPMCH5;
		//������ڲ�����channel-ͨ���ţ�ִ�в�ͬ����
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

	     //����ʱ��Ĭ��ѡ����PLL/2ʱ��Դ48MHz
	     SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);
	     SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	     //����SIMʱ����
	     BSET(SIM_SCGC6_TPM0_SHIFT+tpmModule,SIM_SCGC6);
//	     int_us = 24000*int_us/1000;
	     TPM_ARR2[tpmModule]->CNT = 0;
	     TPM_ARR2[tpmModule]->MOD = TPM0CH1MOD;

	     //�ж�ʹ�ܣ�ģʽѡ��
	     TPM_ARR2[tpmModule]->SC=TPM_SC_TOIE_MASK|TPM_SC_CMOD(1)|TPM_SC_PS(7);
	     TPM_ARR2[tpmModule]->SC=TPM_SC_CMOD(1)|TPM_SC_PS(7);
	     //�����������ز�׽
	     TPM_CnSC_REG(TPM_ARR2[tpmModule],channel)=TPM_CnSC_ELSA_MASK|TPM_CnSC_CHIE_MASK;
	     TPM_CnV_REG(TPM_ARR2[tpmModule],channel)=0;           //CnV�Ĵ�������ֵ�ڴ˴���Ч
	     //ʹ��NVIC�ж�
	     //enable_irq(TPM0_IRQ_NO+tpmModule);
}

//=========================================================================
//�������ƣ�incap_stop
//���ܸ�Ҫ���ر����벶׽ģ��
//����˵����tpmModule(ģ���)��TPM0,TPM1,TPM2
//�������أ���
//=========================================================================
void incap_stop(uint_8 tpmModule)
{
	if(tpmModule<=TPM2)
	    BCLR(SIM_SCGC6_TPM0_SHIFT + tpmModule,SIM_SCGC6);
}

//=========================================================================
//�������ƣ�incap_enable_int
//���ܸ�Ҫ��ʹ�����벶׽�ж�
//����˵����tpmModule(ģ���)��TPM0,TPM1,TPM2
//�������أ���
//=========================================================================
void incap_enable_int(uint_8 tpmModule)
{
	if(tpmModule<=TPM2) enable_irq(TPM0_IRQ_NO + tpmModule);
}

//=========================================================================
//�������ƣ�incap_disable_int
//���ܸ�Ҫ����ֹ���벶׽�ж�
//����˵����tpmModule(ģ���)��TPM0,TPM1,TPM2
//�������أ���
//=========================================================================
void incap_disable_int(uint_8 tpmModule)
{
	if(tpmModule<=TPM2) disable_irq(TPM0_IRQ_NO + tpmModule);
}

//=========================================================================
//�������ƣ�incap_disable_int
//���ܸ�Ҫ����ֹ���벶׽�ж�
//����˵����tpmModule(ģ���)��TPM0,TPM1,TPM2
//�������أ���
//=========================================================================
void incap_counter_clear(uint_8 tpmModule)
{
	TPM_ARR2[tpmModule]->CNT = 0;
}

