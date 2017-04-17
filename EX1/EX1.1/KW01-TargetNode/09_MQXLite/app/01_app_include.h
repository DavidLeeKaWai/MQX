//===========================================================================
//�ļ����ƣ�01_app_include.h
//���ܸ�Ҫ��Ӧ�����񹫹�ͷ�ļ���MQX��ͷ�ļ������ȫ�ֱ�������������������ȣ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£�������Ҫ����
//===========================================================================

#ifndef __01_APP_INCLUDE_H_
#define __01_APP_INCLUDE_H_

//---------------------------------------------------------------------------
// ��һ����
// ����ͷ�ļ����궨�峣��������ȫ�ֱ����������������¼��顢�����¼�λ
//---------------------------------------------------------------------------
//1.1 ����ͷ�ļ�
#include "bsp.h"
#include "stdint.h"
#include "mqxlite.h"
#include "mqx_inc.h"
#include "light.h"
#include "lwevent.h"
#include "rf.h"
#include "lwmsgq.h"
#include "adc.h"
#include "pit.h"
#include "mutex.h"
#include "flash.h"
#include "incap.h"

//1.2 �궨�峣��
#define HEAD_PC        'P'         //��λ������֡֡ͷ
#define END_PC         'C'         //��λ������֡֡β
#define HEAD_TERMINAL  'T'         //Ŀ��ڵ㷵��֡֡ͷ
#define END_TERMINAL   'D'         //Ŀ��ڵ㷵��֡֡β

#define DELAY_TIMES       200      //��ʱ����

#define APPINFO_FLASH_SECTOR  127  //�ڵ�FLASH��Ϣ�洢ҳ�ţ����ݰ���TFlashStruct�ṹ����з���

//����ط��������ͣ�������������ط���������ͬ��֡������������֡ͷ��֡β
enum eAppCmd
{
	eAPPCMD_SYSPARAMREAD  = 0x00,       //0x00. ��ȡĿ��ڵ��ϵͳ������127ҳ��
	eAPPCMD_SYSPARAMWRITE = 0x01,       //0x01. д��Ŀ��ڵ��ϵͳ������127ҳ��

	//��������
	eAPPCMD_RFTEST = 0x02,              // ��֤RF�շ�
	eAPPCMD_LIGHTCTRL = 0x03,              //�ƿ�������

	eAPPCMD_FLASHREAD  = 0x04,      //��ȡFLASHָ��ҳ����
	eAPPCMD_FLASHWRITE = 0x05,      //д��FLASHָ��ҳ����
	eAPPCMD_FLASHWRITEPICTURE = 0x06,      //д��FLASHͼƬ

	eAPPCMD_MAX,
};



//1.3 �궨�����
uint_8 g_rf_recvBuf[64];           //RF�������ݻ�����
uint_8 g_rf_sentBuf[64];          //RF�������ݻ�����
uint_8 g_rf_recvCount;            //��Ч֡��
uint_8 g_rf_sentBufLength;     //RF�������ݳ���
uint_8 light_temp;                  //����С��״̬����
float  g_temperature;             //оƬ�¶�
uint_8 Pic_Arr[4000];              //flash�������ݻ�����

uint_8 PicZhenNum;              //ͼƬ֡��
//uint_16 PicByteCount;            //ͼƬ�ֽ���
uint_8 RevZhenCount;            //�յ���ͼƬ֡��

//1.4 �����������¼���
LWEVENT_STRUCT  lwevent_group;

//1.5 �궨���¼�λ
#define EVENT_RF_RECV     ((1uL)<<(1))   //RF�����¼�λ
#define EVENT_RF_SEND     ((1uL)<<(2))   //RF�����¼�λ
#define EVENT_LIGHTCTRL     ((1uL)<<(3))   //�ƿ��¼�λ
#define EVENT_WRITEPIC     ((1uL)<<(4))   //дͼƬ�¼�λ

typedef struct{
    uint_8  hd_addr;           //Ӳ����ַ
    uint_8 node_number;         //�ڵ��
}TFlashStruct;

TFlashStruct g_tinfo;

//---------------------------------------------------------------------------
// �ڶ�����
// �½��������ض���
//---------------------------------------------------------------------------
// �������Ĳ���
// (1) ��02_task_templates.c������ģ���б����������ģ�� ��������,������,����ջ��С,���ȼ�,������,�������ԣ�
// (2) ��01_app_include.h�к궨�������š��궨������ջ��С����������������������ջ
// (3) ��03_task_main.c�������������У���������_task_create
//---------------------------------------------------------------------------
//2.1 �궨��������
#define TASK_MAIN          1
#define TASK_LIGHT         2
#define TASK_RF_RECV       3
#define TASK_RF_SEND       4
//2.2 �궨������ջ��С
#define TASK_MAIN_STACK_SIZE       (sizeof(TD_STRUCT) + 1024 + PSP_STACK_ALIGNMENT + 1)
#define TASK_LIGHT_STACK_SIZE      (sizeof(TD_STRUCT) + 200 + PSP_STACK_ALIGNMENT + 1)
#define TASK_RF_RECV_STACK_SIZE    (sizeof(TD_STRUCT) + 1024 + PSP_STACK_ALIGNMENT + 1)
#define TASK_RF_SEND_STACK_SIZE    (sizeof(TD_STRUCT) + 512 + PSP_STACK_ALIGNMENT + 1)
//2.3 ����������
void task_main(uint32_t initial_data);
void task_light(uint32_t initial_data);
void task_rf_recv(uint32_t initial_data);
void task_rf_send(uint32_t initial_data);
//2.4 ��������ջ
uint_8 task_main_stack[TASK_MAIN_STACK_SIZE];
uint_8 task_light_stack[TASK_LIGHT_STACK_SIZE];
uint_8 task_rf_recv_stack[TASK_RF_RECV_STACK_SIZE];
uint_8 task_rf_send_stack[TASK_RF_SEND_STACK_SIZE];

//---------------------------------------------------------------------------
#endif    //01_app_include.h

