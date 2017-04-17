//===========================================================================
//�ļ����ƣ�isr.c�� �жϵײ���������Դ�ļ���
//���ܸ�Ҫ���жϷ������̴�Ŵ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼������ʵ���������
//===========================================================================
#include "01_app_include.h"

//===========================================================================
//ISR ���ƣ�isr_uart0_re,UART_0������0���жϷ�������
//����˵����user_isr_ptr���û��Զ���������˴�δ��
//���ܸ�Ҫ��ÿ���յ�һ���ֽڣ�����һ�δ��ڽ����жϣ�ִ�б�����һ�Ρ�
//         �����̶Դ����յ������ݣ�ԭ�����ͳ�ȥ��ʵ�ִ������ݻ��Թ��ܡ�
//===========================================================================
void isr_uart0_re(pointer user_isr_ptr)
{
	uint_8 c;
	DISABLE_INTERRUPTS;           //�����ж�
	//-----------------------------------------------------------------------
    uart_re1(UART_0, &c);         //�յ�������
    UART0_BASE_PTR->D = c;        //���ͳ�ȥ
    //-----------------------------------------------------------------------
	ENABLE_INTERRUPTS;            //�����ж�
}

//===========================================================================
//ISR ���ƣ�isr_gpio_cd,PTC��PTD�˿��жϷ�������
//����˵����user_isr_ptr���û��Զ���������˴�δ��
//���ܸ�Ҫ��ÿ���յ�һ֡64���ֽڵ�RF���ݣ�����һ�α��жϡ�
//         �����̶��յ������ݣ�����RF_ReceiveFrame���������ݽ��н���
//         ��֡�����ճɹ�����lwevent_group�¼����EVENT_RF_RECV�¼�
//         λ����"01_app_include.h"�ļ��������ģ���
//===========================================================================
void isr_gpio_cd(pointer user_isr_ptr)
{
	DISABLE_INTERRUPTS;                      //�����ж�
	//-----------------------------------------------------------------------
    if((PORTC_PCR4 & PORT_PCR_ISF_MASK))     //DIO1�ж�
	{
    		//�������ݰ��ɹ������¼�λEVENT_RF_RECV������task_rf_recv()����
		if(0 == RF_ReceiveFrame(g_rf_recvBuf,&g_rf_recvCount,g_tinfo.hd_addr))
		{
            _lwevent_set(&lwevent_group,EVENT_RF_RECV);
		}
		PORTC_PCR4 |= PORT_PCR_ISF_MASK; 	 //���־λ
	}
	//-----------------------------------------------------------------------
	UART0_S1|=0x1F;
    ENABLE_INTERRUPTS;                       //�����ж�
}

