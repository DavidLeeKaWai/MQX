//===========================================================================
//�ļ����ƣ�task_light.c
//���ܸ�Ҫ����������ָʾ����˸
//��Ȩ���У����ݴ�ѧǶ��ʽ����(sumcu.suda.edu.cn)
//�汾���£�������Ҫ����
//��    ע��20151201��WYH
//===========================================================================
#include "01_app_include.h"    //Ӧ�����񹫹�ͷ�ļ�

//===========================================================================
//�������ƣ�task_light
//���ܸ�Ҫ����������ָʾ����˸�����������ȼ�Ϊ14��������task_adc
//����˵����δʹ��
//===========================================================================
void task_light(uint_32 initial)
{	
    //��������ѭ����
    while(TRUE) 
    {
        //���¼����û�����---------------------------------------------------
        
        //��1����������ָʾ����˸
        light_change(LIGHT_RUN_1);      
        //��2��������ʱ200�δ�ÿ���δ�tick����Ӧ5ms����ʱ200*5ms=1s
	    _time_delay_ticks(200);
	
     } //����ѭ����end_while
}