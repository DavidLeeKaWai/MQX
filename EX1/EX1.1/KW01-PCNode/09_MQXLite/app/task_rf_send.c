//===========================================================================
//�ļ����ƣ�task_rf_send.c
//���ܸ�Ҫ������RF��������֡����
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£�������Ҫ����
//===========================================================================
#include "01_app_include.h"    //Ӧ�����񹫹�ͷ�ļ�

//===========================================================================
//�������ƣ�task_rf_send
//���ܸ�Ҫ���ж�RF�����¼�λEvent_RF_Send������RF_SendData()����ת�����ղ������ݰ���
//����˵����δʹ��
//===========================================================================
void task_rf_send(uint32_t initial)
{	
	//1. ��������ʹ�õı���
	uint_8 i;
	uint_8 rf_sentDataLen;

	//2. ���йر�������ֵ

	//3. ��������ѭ����
	while(TRUE) 
	{
		//���¼����û�����--------------------------------------------------------
		//1�����޵ȴ�RF�����¼�λ��һ
		_lwevent_wait_for(&lwevent_group, EVENT_RF_SEND, FALSE, NULL);

//		rf_sentDataLen = g_uart_recvBuf[1]-1;  //��ҪRFת�����ֽ���
//
//		for (i=0;i<rf_sentDataLen;i++) g_rf_sentBuf[i]=g_uart_recvBuf[i+3];
//
//		RFSendDataByCSMACA(rf_sentDataLen,&g_rf_sentBuf[0],0,g_rf_hdaddr);

		rf_sentDataLen = g_uart_recvBuf[1]+3;  //��ҪRFת�����ֽ���

		for (i=0;i<rf_sentDataLen;i++) g_rf_sentBuf[i]=g_uart_recvBuf[i];

		RFSendDataByCSMACA(rf_sentDataLen,&g_rf_sentBuf[0],0,g_rf_hdaddr);


		//���RF�����¼�λ
		_lwevent_clear(&lwevent_group, EVENT_RF_SEND);

	}//����ѭ����end_while
}
