//===========================================================================
//�ļ����ƣ�03_task_main.c������������
//���ܸ�Ҫ������MQXLite������������
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£��ɸ�����Ŀ��Ҫ�Ժ�������λ�ý��е���
//===========================================================================
#include "01_app_include.h"

__attribute__((section (".romsymbols"))) const uint_8 mydata[4] = {0x55, 0xAA, 0x43, 0x45};
//============================================================================
//��������: flash_info_read
//���ܸ�Ҫ: ��ȡ�洢��¼��Ϣ
//����˵��: ��
//��������: ��
//============================================================================
void flash_info_read(TFlashStruct* appinfo)
{
    uint_8* pbuf;
    uint_8* address =  (uint_8*)(APPINFO_FLASH_SECTOR * SIZE_FLASHPAGE);
    uint_8 i;
    pbuf = (uint_8*)(appinfo);
    for(i=0; i < sizeof(TFlashStruct);i++)
		pbuf[i] = address[i];
}

//===========================================================================
//�������ƣ�task_main
//���ܸ�Ҫ��MQX������������Ҫʵ�����������ʼ���������������񡢰�װ�û�ISR
//����˵����δʹ��
//===========================================================================
void task_main(uint32_t initial_data)
{
	//uint_8 i;
	
	//1. ����������ʹ�õı���
	//�����������¼���
	_lwevent_create(&lwevent_group,0);

    //2. �����ж�
    DISABLE_INTERRUPTS;

    //3. ��ʼ������ģ��
    uart_init(UART_0,MCGFLLCLK,115200);    //��ʼ��UART_0ģ��
    light_init(LIGHT_RUN_1,LIGHT_OFF);     //��ʼ���ڵ������ָʾ��1
    light_init(PORTB|(1),LIGHT_ON);     //��ʼ���ڵ������ָʾ��1

	 flash_init();                          //��ʼ��Flash



	//��FLASH�洢��Ϣ
	flash_info_read(&g_tinfo);
	//��¼��Ϣ����ȷ������Ĭ����Ϣ
	if(g_tinfo.hd_addr == 0xFFFF || g_tinfo.node_number == 0xFFFF)
	{
		g_tinfo.hd_addr = 0xFF;
		g_tinfo.node_number = 0;

	}

    RF_Init((uint_8)g_tinfo.hd_addr);		//RFģ���ʼ��

    //4. ���йر�������ֵ

    //5. ������������
    _task_create_at(0, TASK_LIGHT,   0, task_light_stack,   TASK_LIGHT_STACK_SIZE);
    _task_create_at(0, TASK_RF_RECV, 0, task_rf_recv_stack, TASK_RF_RECV_STACK_SIZE);
    _task_create_at(0, TASK_RF_SEND, 0, task_rf_send_stack, TASK_RF_SEND_STACK_SIZE);

    //6. ��װ�û�ISR
    _int_install_isr(INT_UART0,isr_uart0_re,NULL);//����0��ISR
    _int_install_isr(INT_PORTD,isr_gpio_cd,NULL); //PTC��PTD��ISR���˿�C��D����ͬһ�ж�����

    //7. ʹ��ģ���ж�
    uart_enable_re_int(UART_0);

	//8. �����ж�
	ENABLE_INTERRUPTS;

    //------------ִ����ϣ��������������̬----------------------------------------------
    _task_block();
}
