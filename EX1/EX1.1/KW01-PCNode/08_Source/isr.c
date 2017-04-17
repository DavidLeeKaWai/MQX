//===========================================================================
//�ļ����ƣ�isr.c�� �жϵײ���������Դ�ļ���
//���ܸ�Ҫ���жϷ������̴�Ŵ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼������ʵ���������
//
//===========================================================================
#include "includes.h"
#include "01_app_include.h"

//�ڲ���������
uint8_t CreateFrame(uint_8 Data,uint_8 * buffer);

//===========================================================================
//ISR ���ƣ�isr_uart0_re,UART_0������0���жϷ�������
//����˵����user_isr_ptr���û��Զ���������˴�δ��
//���ܸ�Ҫ��ÿ���յ�һ���ֽڣ�����һ�δ��ڽ����жϣ�ִ�б�����һ�Ρ�
//          �����̶Դ����յ������ݣ����ձ��ļ���CreateFrame����ͷ������Э��
//          ��֡����֡�ɹ�����lwevent_group�¼����EVENT_UART0_RE�¼�
//          λ����"01_app_include.h"�ļ��������ģ���
//===========================================================================
void isr_uart0_re(pointer user_isr_ptr)
{
    uint_8 c;
    DISABLE_INTERRUPTS;               //�����ж�
    //-----------------------------------------------------------------------
    uart_re1(UART_0, &c);             //����һ���ֽ�
    //�����ڲ�����CreateFrame������֡
    if(CreateFrame(c,g_uart_recvBuf)!=0)    //��֡�ɹ�
    {
        _lwevent_set(&lwevent_group,EVENT_UART0_RE);
    }
    //-----------------------------------------------------------------------
	ENABLE_INTERRUPTS;                //�����ж�
}


//===========================================================================
//ISR ���ƣ�gpio_CD_ISR,PTC��PTD�˿��жϷ�������
//����˵����user_isr_ptr���û��Զ���������˴�δ��
//���ܸ�Ҫ��ÿ���յ�һ֡64���ֽڵ�RF���ݣ�����һ�α��жϡ�
//         �����̶��յ������ݣ�����RF_ReceiveFrame���������ݽ��н���
//         ��֡�����ճɹ�����lwevent_group�¼����EVENT_RF_RECV�¼�
//         λ����"01_app_include.h"�ļ��������ģ���
//===========================================================================
void gpio_CD_ISR(pointer user_isr_ptr)
{
	DISABLE_INTERRUPTS;           //�����ж�
	//-----------------------------------------------------------------------
	if((PORTC_PCR4 & PORT_PCR_ISF_MASK)) 	//DIO1�ж�
	{
        //�������ݰ��ɹ������¼�λEVENT_RF_RECV������task_rf_recv()����
	    if(0 == RF_ReceiveFrame(g_rf_recvBuf,&g_rf_recvCount,g_rf_hdaddr))
	    {
            //��RF�����¼�λ������RF��������
            _lwevent_set(&lwevent_group,EVENT_RF_RECV); 
	    }
        PORTC_PCR4 |= PORT_PCR_ISF_MASK; 	//���־λ
	}
	//-----------------------------------------------------------------------
	UART0_S1|=0x1F;
    ENABLE_INTERRUPTS;                      //�����ж�
}

//�ڲ����ú���

//===========================================================================
//�������ƣ�CreateFrame
//���ܸ�Ҫ���齨����֡��������֡���ݼ��뵽����֡��
//����˵����Data��                   ����֡����
//          buffer:        ����֡����
//�������أ���֡״̬    0-��֡δ�ɹ���1-��֡�ɹ�
//��ע��ʮ����������֡��ʽ
//               ֡ͷ        + ���ݳ���         + ��Ч����    +  ֡β
//           FrameHead   +   len       + ��Ч����    + FrameTail
//===========================================================================

#define FrameHead    (0x50)       //֡ͷ     ASCII���ӦP
#define FrameTail    (0x43)       //֡β     ASCII���ӦC

uint8_t CreateFrame(uint_8 Data,uint_8 * buffer)
{
    static uint_8 frameLen=0;    //֡�ļ�����
    uint_8 frameFlag;            //��֡״̬

    frameFlag=0;            //��֡״̬��ʼ��
    //���ݾ�̬����frameCount��֡
    switch(frameLen)
    {
        case 0:    //��һ������
        {
            if (Data==FrameHead)    //�յ�������֡ͷFrameHead
            {
                buffer[0]=Data;
                frameLen++;
                frameFlag=0;        //��֡��ʼ
            }
            break;
        }
        case 1:    //�ڶ������ݣ��������������յ����ݸ���
        {
            buffer[1]=Data;
            frameLen++;
            break;
        }
        default:    //�������
        {
            //�ڶ�λ��������Ч���ݳ���,�������������µ�����ֱ��֡βǰһλ
            if(frameLen>=2 && frameLen<=(buffer[1] + 1))
            {
                buffer[frameLen]=Data;
                frameLen++;
                break;
            }

            //����ĩβ������ִ��
            if(frameLen>=(buffer[1]+2))
            {
                if (Data==FrameTail)    //����֡β
                {
                    buffer[frameLen]=Data;     //��֡β���뻺����
                    frameFlag=1;    //��֡�ɹ�
                }
                frameLen=0;     //������0��׼��������֡
                break;
            }
        }
    }     //switch_END
    return frameFlag;                 //������֡״̬
}
