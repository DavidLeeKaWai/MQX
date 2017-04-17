//===========================================================================
//�ļ����ƣ�task_rf_recv.c
//���ܸ�Ҫ������RF��������֡����
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£��ɸ�����Ŀ��Ҫ�Ժ�������λ�ý��е���������command_proc()��������
//===========================================================================
#include "01_app_include.h"    //Ӧ�����񹫹�ͷ�ļ�

//��������
uint_8 FrameCheck(uint_8 *buff);
uint_8 FrameDataCheck(uint_8 *buff);
uint_8 flash_info_write(const TFlashStruct* const appinfo);
uint_8 ReadFlashInfo(uint_8 *buff);
uint_8 WriteFlashInfo(uint_8 *buff);
uint_8 RFTest();
uint_8 FlashRead();
uint_8 FlashWrite();
uint_8 FlashWritePic();
uint_8 LIGHTstate();
uint_8 command_proc();

//===========================================================================
//�������ƣ�task_rf_recv
//���ܸ�Ҫ���ж�RF�����¼�λEVENT_RF_RECV����һ�����FrameCheck()��
//         FrameDataCheck()����������֡����У�飬У��ɹ������command_proc()����
//         ��֡��������봦��������Ҫ�ط����ݵ�֡������֡����RF�����¼�λ��Ȼ��
//         ���RF�����¼�λ�������ȴ�RF�����¼�λ��һ��
//����˵����δʹ��
//===========================================================================
void task_rf_recv(uint32_t initial)
{
	//1. ��������ʹ�õı���
	//uint_8 offset;

	//2. ���йر�������ֵ

	//3. ��������ѭ����
	while(TRUE)
	{
		//���¼����û�����--------------------------------------------------------
		//1�� ���޵ȴ�RF�����¼�λ��һ
		_lwevent_wait_for(&lwevent_group, EVENT_RF_RECV, FALSE, NULL);
		g_rf_sentBufLength = 6;
		//2������֡֡��ʽ���ڵ���ϢУ��
		if(FrameCheck(g_rf_recvBuf) == 0)
		{
			if(g_rf_recvBuf[3] != 0){
				if(g_rf_recvBuf[3] == g_tinfo.node_number ){
					g_rf_sentBuf[0] = HEAD_TERMINAL;           //֡ͷ
					g_rf_sentBuf[1] = g_rf_sentBufLength - 3;  //��Ч���ݳ���
					g_rf_sentBuf[2] = g_rf_recvBuf[2];         //Ӳ����ַ
					g_rf_sentBuf[3] = 4;						//PCNode�ڵ��
					g_rf_sentBuf[4] = g_rf_recvBuf[4] + g_tinfo.node_number;  //���϶�Ӧ�����֣��ڵ�ţ�
					g_rf_sentBuf[g_rf_sentBufLength - 1] = END_TERMINAL;   //֡β
					//��RF�����¼�λ������RF��������
					_lwevent_set(&lwevent_group,EVENT_RF_SEND);
				}
			}
			else{
				g_tinfo.node_number = g_rf_recvBuf[4];
				flash_info_write(&g_tinfo);
				g_rf_sentBuf[0] = HEAD_TERMINAL;           //֡ͷ
				g_rf_sentBuf[1] = g_rf_sentBufLength - 3;  //��Ч���ݳ���
				g_rf_sentBuf[2] = g_rf_recvBuf[2];         //Ӳ����ַ
				g_rf_sentBuf[3] = 4;						//PCNode�ڵ��
				g_rf_sentBuf[4] = 0;
				g_rf_sentBuf[g_rf_sentBufLength - 1] = END_TERMINAL;   //֡β
				//��RF�����¼�λ������RF��������
				_lwevent_set(&lwevent_group,EVENT_RF_SEND);
			}
		}

		//3�����RF�����¼�λ
		_lwevent_clear(&lwevent_group, EVENT_RF_RECV);
	}//����ѭ����end_while
}


//============================================================================
//��������: FrameCheck
//���ܸ�Ҫ: ����֡֡��ʽУ��
//����˵��: ���飬���յ�������
//��������: ֡��ʽУ���������
//============================================================================
uint_8 FrameCheck(uint_8 *buff)
{
	uint_8 ret = 0;
	//֡ͷ
	if(buff[0] != HEAD_PC)
	{
		ret = 1;
		goto Exit_FrameCheck;
	}
	//����
	if(buff[1] > 61)
	{
		ret = 2;
		goto Exit_FrameCheck;
	}
	//Ӳ����ַ
	if(buff[2] != (uint_8)g_tinfo.hd_addr)
	{
		ret = 3;
		goto Exit_FrameCheck;
	}
	//֡β
	if(buff[2 + buff[1]] != END_PC)
	{
		ret = 4;
		goto Exit_FrameCheck;
	}

Exit_FrameCheck:
	return ret;
}


//============================================================================
//��������: flash_info_write
//���ܸ�Ҫ: �洢��¼��Ϣ
//����˵��: ��
//��������: д��FLASH��¼��Ϣ�Ĵ�������
//============================================================================
uint_8 flash_info_write(const TFlashStruct* const appinfo)
{
	DISABLE_INTERRUPTS;
	if(0 == flash_erase(APPINFO_FLASH_SECTOR))//�����ɹ�
    {
		if(0 == flash_write(APPINFO_FLASH_SECTOR, 0, sizeof(TFlashStruct),(uint_8*)appinfo))
		{
			return 0;//д��ɹ�
		}
    }
	ENABLE_INTERRUPTS;//���ж�

	return 1;//д��ʧ��
}




