/*
 * task_lightctrl.c
 *
 *  Created on: 2016��3��28��
 *      Author: asus
 */
#include "01_app_include.h"    //Ӧ�����񹫹�ͷ�ļ�
//===========================================================================
//�������ƣ�task_lightctrl
//���ܸ�Ҫ����ȡPC�������Ŀ�����Ϣ���ı�С�Ƶ�״̬
//                ���������ȼ�Ϊ14
//����˵����δʹ��
//===========================================================================
void task_lightctrl(uint32_t initial_data)
{
		//1. ��������ʹ�õı���
		uint_8 state;//����PC������������ȷ��С��״̬
		//2. ���йر�������ֵ

		//3. ��������ѭ����
		while(TRUE)
		{
			//���¼����û�����--------------------------------------------------------
			//1������С��״̬
			_lwevent_wait_for(&lwevent_group, EVENT_LIGHTCTRL, FALSE, NULL);
			//�ȴ�С�ƿ����¼�λ

			if(light_temp==0)
			{
				state=0;
			}
			else
			{
				state=1;
			}
			light_control(LIGHT_ZR,state);      //�ı�����С��״̬

			_lwevent_clear(&lwevent_group, EVENT_LIGHTCTRL);
			//���С���¼�λ
		}

}







