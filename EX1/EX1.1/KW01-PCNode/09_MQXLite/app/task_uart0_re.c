//===========================================================================
//�ļ����ƣ�task_uart0_re.c
//���ܸ�Ҫ������Uart0��������֡�Ľ�֡����
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£�������Ҫ����
//===========================================================================
#include "01_app_include.h"    //Ӧ�����񹫹�ͷ�ļ�

extern uint_8 HW_ADR;
//===========================================================================
//�������ƣ�task_uart0_re
//���ܸ�Ҫ���жϴ��н����¼�λEvent_Uart0_Re���������н�������֡����������֡���ݾ�����1���������źţ�
//       2ֱ�Ӵ��ڻ��ͽ�����Ϣ��3����RF�����������¼�λEvent_RF_Send������RF��������task_rf_send()��
//����˵����δʹ��
//===========================================================================
void task_uart0_re(uint32_t initial)
{	
	//1. ��������ʹ�õı���

	//2. ���йر�������ֵ

	//3. ��������ѭ����
	while(TRUE) 
	{
		//���¼����û�����--------------------------------------------------------
		//1�����޵ȴ�������0������������֡�¼�λ��
		_lwevent_wait_for(&lwevent_group, EVENT_UART0_RE, FALSE, NULL);

		DISABLE_INTERRUPTS;
		// ����Ӳ�����˵�ַ���ж�֡���ͣ�����֡����ת��֡��
		if(g_uart_recvBuf[2] == 0)    //��������
		{
			g_uart_sentBuf[0]=(uint_8)HEAD_MASTER;     //
			g_uart_sentBuf[1]=7;               //
			g_uart_sentBuf[2]  = (uint_8)0;    //��������ط���ַ��Ϊ�㡣
			g_uart_sentBuf[3]  = (uint_8)'P';  //"PCNode"
			g_uart_sentBuf[4]  = (uint_8)'C';
			g_uart_sentBuf[5]  = (uint_8)'N';
			g_uart_sentBuf[6]  = (uint_8)'o';
			g_uart_sentBuf[7]  = (uint_8)'d';
			g_uart_sentBuf[8]  = (uint_8)'e';
			g_uart_sentBuf[9]  = (uint_8)END_MASTER;   //
			uart_sendN(UART_0,10,&g_uart_sentBuf[0]);
		}
		else      // ����ת��
		{
			g_rf_hdaddr=g_uart_recvBuf[2];   //g_rf_hdaddrΪȫ�ֱ�����Ӳ����ַ
			RF_Init(g_rf_hdaddr);		     //RFģ���ʼ��
			//��RF�����¼�λ��EVENT_RF_SEND��������task_rf_send����
			_lwevent_set(&lwevent_group,EVENT_RF_SEND);
		}
		ENABLE_INTERRUPTS;

        //3��Uart0�����¼�λ����
		_lwevent_clear(&lwevent_group, EVENT_UART0_RE);
	}//����ѭ����end_while
}
