using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.IO;
using System.Management;

namespace SerialPort
{
    ///-----------------------------------------------------------------------------------
    ///FrmMain :KW01-A1工程的窗体                                                          
    ///目    的:
    ///日    期:                                             
    ///编 程 者:
    ///-----------------------------------------------------------------------------------
    public partial class FrmMain : Form
    {
        //1. 窗体类的临时变量区
        private System.IO.Ports.SerialPort UARTport;   //声明系统工具-串口对象的变量声明
        private Uart uart1;                          //声明一个自定义的Uart类型（串口操作）的变量
        private PCNode pcNode1;                      //声明一个自定义的PCNode类型的变量


      


        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// 名    称: FrmMain构造函数 
        /// 功    能: 启动窗体最先执行程序                                  
        /// </summary>                                                                                                               
        /// <returns>无</returns>                  
        /// ------------------------------------------------------------------------------
        /// 
        //2. 构造函数（启动窗体最先执行程序）
        public FrmMain()
        {
            //系统生成的构造函数（初始化窗体的元素）
            InitializeComponent();
            //禁止检测跨线程调用异常(
            CheckForIllegalCrossThreadCalls = false;
            //初始化窗体类临时变量
            UARTport = null;          //初始化“系统工具-串口对象”
            uart1 = null;             //初始化“Uart类型（串口操作）对象”
            pcNode1 = new PCNode();   //
        }
        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// 名    称: FrmMain_Load（加载窗体事件程序） 
        /// 功    能: 在构造函数之后执行的程序                                  
        /// </summary>                                                                                                               
        /// <returns>无</returns>                  
        /// ------------------------------------------------------------------------------
        //3. 加载窗体事件程序
        private void FrmMain_Load(object sender, EventArgs e)
        {
           
            string s1;
            this.tb_statue.Text = "运行状态：FrmMain_Load开始,调用PCNode类内部函数，寻找PCNode...";
            this.tb_statue.Refresh();

            if (uart1 != null && uart1.IsOpen) uart1.close();
            s1 = pcNode1.findPCNode();           //调用PCNode类内部函数，寻找PCNode
            uart1 = pcNode1.PCNode_Uart1;

            this.tb_statue.Text = "运行状态：找到" + s1;
            this.tb_statue.Refresh();

            lbl_PC_Node_State.Text = s1;

            //保留编程参考：绑定DataReceived事件(即串口接收中断处理函数）
            if (uart1 != null)
            {
                UARTport = uart1.port;
                UARTport.DataReceived += new System.IO.Ports. //添加串口对象变量的接收事件的响应函数
                         SerialDataReceivedEventHandler(this.UARTport_recvData);
            }
            //uart1.setReceInt(2);           //设置触发DataRecieved事件的字节数（目的是关闭该事件）
            //uart1.sendData(B1, B1.Length); //发送握手数据

        }

        //========================以下是本窗体的各个事件响应函数==========================
        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// 名    称: btnCheckPcNode_Click（单击“检测PC节点”按钮） 
        /// 功    能: 单击“检测PC节点”按钮，自动搜寻找到PCNode(PC节点）。                                 
        /// </summary>                                                                                                               
        /// <returns>无</returns>                  
        /// ------------------------------------------------------------------------------
        
        //------------------------单击“检测PC节点”按钮----------------------------------
        private void btnCheckPcNode_Click(object sender, EventArgs e)
        {

            //if (_port1.IsOpen) 

            this.tb_statue.Text = "运行状态：" + "单击“检测PC节点”按钮...";
            this.tb_statue.Refresh();

            FrmMain_Load(sender, e);

            this.tb_statue.Text = "运行状态：" + "单击“检测PC节点”按钮...退出";
        }

        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// 名    称: FrmMain_FormClosing（单击窗口关闭“X”按钮） 
        /// 功    能: 单击窗口关闭“X”按钮，关闭窗口。                                 
        /// </summary>                                                                                                               
        /// <returns>无</returns>                  
        /// ------------------------------------------------------------------------------
        //--------------------------单击窗口关闭“X”按钮---------------------------------
        private void FrmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (uart1 == null) return;
            //如果串口未关闭，则关闭
            if (uart1.IsOpen) uart1.close();
        }

        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// 名    称: UARTport_recvData（串口接收事件的响应函数） 
        /// 功    能: 串口接收事件的响应                               
        /// </summary>                                                                                                               
        /// <returns>无</returns>                  
        /// ------------------------------------------------------------------------------
        //-------------------------------串口接收事件的响应函数---------------------------
        private void UARTport_recvData(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            int i;
            //int tmp, brt;
            string s1 = string.Empty;

            Thread.Sleep(100);
            PublicVar.g_ReceiveByteArray = uart1.recvData();    //调用串口接收函数
            if (PublicVar.g_ReceiveByteArray == null) return;
            //if (PublicVar.g_ReceiveByteArray.Length > 0)
            //{
            //    this.Txt_recv2.Text = "Interrupt--- " + System.Text.Encoding.Default.GetString(PublicVar.g_ReceiveByteArray);
            //    if (PublicVar.g_ReceiveByteArray[2] == 'M') 
            //    {
            //        tmp = (int)(PublicVar.g_ReceiveByteArray[4] * 255 + PublicVar.g_ReceiveByteArray[3]);
            //        brt = (int)(PublicVar.g_ReceiveByteArray[6] * 255 + PublicVar.g_ReceiveByteArray[5]);

            //    }
            //}
            for (i = 0; i < PublicVar.g_ReceiveByteArray.Length; i++)
            {
                this.Txt_recv2.Text += "-" + PublicVar.g_ReceiveByteArray[i].ToString("D3") + " ";
            }

        }
        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// 名    称: btnVerifyRF_Click（单击“验证RF收发”按钮） 
        /// 功    能: 单击“验证RF收发”按钮 ，产生响应                              
        /// </summary>                                                                                                               
        /// <returns>无</returns>                  
        /// ------------------------------------------------------------------------------
        private void btnVerifyRF_Click(object sender, EventArgs e)
        {

            // 1. 临时变量声明
            byte n;             //测试数据字节数
            int i;
            //byte len;           //[命令+数据]字节数（总帧长度-1B帧头 - 1B len - 1B帧尾）
            string s1;
            byte hw_Addr;

            ////this.Txt_recv1.Text = "";
            //this.Txt_recv2.Text = "";

            //this.Txt_recv1.Refresh();
            //this.Txt_recv2.Refresh();
           

            btnVerifyRF.Enabled = false;

            // 2. 临时变量赋值
            //n = Convert.ToByte(tbTxtDataLen.Text);
            hw_Addr = Convert.ToByte(hwAddr.Text);

            //byte[] writeDataArray = System.Text.Encoding.Default.GetBytes(tbWriteData2.Text);

            //if (n > 50||n<1)
            //{
            //    this.tb_statue.Text = "发送字节数不合适，合理范围是1~50";
            //    return;
            //}

            //len = (byte)(n + 1);
            //len = (byte)(n + 1);    //增加一个是否检测能量场的字节

            byte[] SendByteArray = new byte[6];

            // 组帧
            try
            {
                SendByteArray[0] = (byte)'P';      //帧头

                SendByteArray[1] = (byte)3;            //帧长

                SendByteArray[2] = hw_Addr;        //被访问的硬件过滤地址

                //if(0 < int.Parse(tbWriteData2.Text) || int.Parse(tbWriteData2.Text)>255 )
                //{
                //    this.tb_statue.Text = "请输入0~255的数";
                //    this.tb_statue.Refresh();
                //    btnVerifyRF.Enabled = true;
                //    return;
                //}

                try
                {
                    SendByteArray[3] = byte.Parse(nodeSelect.Text);
                }
                catch
                {
                    this.tb_statue.Text = "请选择要发送的节点号";
                    this.tb_statue.Refresh();
                    btnVerifyRF.Enabled = true;
                    return;
                }

                try
                {
                    
                    SendByteArray[4] = byte.Parse(tbWriteData2.Text);
                }
                catch
                {
                    this.tb_statue.Text = "请输入0~255的数";
                    this.tb_statue.Refresh();
                    btnVerifyRF.Enabled = true;
                    return;
                }

               
                SendByteArray[5] = (byte)'C';      //帧尾

                //
                //发送、接收、显示
                //sendRecv(SendByteArray,1,5500);
                uart1.setReceInt(100);   //测试串口接收中断使用
                //uart1.sendData(SendByteArray, SendByteArray.Length);  // 通过串口发送数据
                sendRecv(SendByteArray, 2, 300);

                //System.Threading.Thread.Sleep(time);

                //s1 = s1 + "已经发送,Data 为"+ byte.Parse(tbWriteData2.Text) + ",等待接收中断...收到TargetNode回送信息！";
                //this.tb_statue.Text = s1;
                //this.tb_statue.Refresh();


                btnVerifyRF.Enabled = true;
            }
            catch
            {
                //this.Txt_recv1.Text = "有误:可能没串口！";
                this.tb_statue.Text = "发送消息失败，没有找到第" + nodeSelect.Text + "号TargetNode！";
                this.tb_statue.Refresh();
                btnVerifyRF.Enabled = true;
            }
          
        }

        //==========================================================================
        //函数名称：sendRecv,sendRecv2,sendRecv3
        //函数功能：通过串口发送数组帧数据，并接收返回的数据
        //参数说明：SendByteArray（待发送数组），cnt（发送次数），time(延迟时间)
        //========================================================================

        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// 名    称: sendRecv（数据收发） 
        /// 功    能: 温度采集，小灯控制数据帧的发送和接收模块
        ///           通过串口发送数组帧数据，并接收返回的数据 ，                                  
        /// </summary>                                                                                                               
        /// <returns>无</returns>                  
        /// ------------------------------------------------------------------------------

        //-------------数据帧的发送和接收------------------------
        private void sendRecv(byte[] SendByteArray, int cnt, int time)
        {
            byte[] recvData;
            String str = String.Empty;
            this.tb_statue.Text = "正在发送...";
            this.tb_statue.Refresh();
            recvData = pcNode1.PCNodeSendReturn(SendByteArray, cnt, time);
            if (recvData.Length <= 0)
            {

                if(SendByteArray[3] == (byte)0)
                {

                    this.tb_statue.Text = "设置节点号失败，没有找到TargetNode！";
                    this.tb_statue.Refresh();
                }
                else
                {
                    this.tb_statue.Text = "发送消息失败，没有找到第"+nodeSelect.Text+"号TargetNode！";
                    this.tb_statue.Refresh();
                }
            }
            else
            {

                //this.tb_statue.Text += "有数据从第";
                //this.tb_statue.Text += SendByteArray[3].ToString();
                //this.tb_statue.Text += "节点返回";
                //this.tb_statue.Refresh();
                if (SendByteArray[3] == (byte)0)
                {

                    this.tb_statue.Text = "设置节点号成功！TargetNode为第"+nodeNumber.Text+"号节点！";
                    this.tb_statue.Refresh();
                }
                else
                {
                    this.tb_statue.Text = "发送消息成功！收到第" + nodeSelect.Text + "号节点的消息！";
                    this.tb_statue.Refresh();
                }


                //this.Txt_recv2.Text = string.Empty;

                //sign = recvData[8];
                //for (i = 9; i < recvData.Length-1; i++)
                // this.Txt_recv.Text += "-" + recvData[i].ToString("D3").ToUpper() + " ";
                //this.Txt_recv2.Text += recvData[i].ToString("X2").ToUpper() + " ";
                //data[i - 9] = recvData[i];//有效数据字符数组
                //this.Txt_recv2.Text = System.Text.Encoding.Default.GetString(recvData);

                //str = Encoding.Default.GetString(data);//转换为字符串

                //if (sign == (byte)'R')
                //{
                if (recvData[3] == (byte)4 )
                {
                    if (recvData[4] != (byte)0) {
                        str = recvData[4].ToString();//转换为字符串
                        this.Txt_recv2.Text = string.Empty;
                        this.Txt_recv2.Text += "第"+ this.nodeSelect.Text + "节点:"+str;
                        this.Txt_recv2.Refresh();
                    }
                    else
                    {
                        this.Txt_recv2.Text = string.Empty;
                        this.Txt_recv2.Text += "第"+this.nodeNumber.Text+"节点设置成功！";
                        this.Txt_recv2.Refresh();
                    }
                }
                
                    //}
            }
        }
        

        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// 名    称: btnClear1_Click（单击“清空显示框”按钮） 
        /// 功    能: 单击“清空显示框”按钮 ，产生响应                              
        /// </summary>                                                                                                               
        /// <returns>无</returns>                  
        /// ------------------------------------------------------------------------------
        //---------------------------单击“清空显示框”按钮-------------------------------
        private void btnClear1_Click(object sender, EventArgs e)
        {
            this.tb_statue.Text = "运行状态：" + "单击“清空显示框”按钮。";
            this.tb_statue.Refresh();

            //this.Txt_recv1.Text = "";
            this.Txt_recv2.Text = "";
        }

        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// 名    称: btnClear1_Click（单击“清空显示框”按钮） 
        /// 功    能: 单击“清空显示框”按钮 ，产生响应                              
        /// </summary>                                                                                                               
        /// <returns>无</returns>                  
        /// ------------------------------------------------------------------------------
        //---------------------------单击“清空显示框”按钮-------------------------------

        private void setNodeNumber_Click(object sender, EventArgs e)
        {
            // 1. 临时变量声明
            byte n;             //测试数据字节数
            int i;
            //byte len;           //[命令+数据]字节数（总帧长度-1B帧头 - 1B len - 1B帧尾）
            string s1;
            byte hw_Addr;

            //this.Txt_recv1.Text = "";
            //this.Txt_recv2.Text = "";

            //this.Txt_recv1.Refresh();
            //this.Txt_recv2.Refresh();
            this.tb_statue.Refresh();

            setNodeNumber.Enabled = false;

            // 2. 临时变量赋值
            hw_Addr = Convert.ToByte(hwAddr.Text);

            //byte[] writeDataArray = System.Text.Encoding.Default.GetBytes(tbWriteData2.Text); //String转化为Byte[]


            //len = (byte)(n + 1);
            //len = (byte)(n + 1);    //增加一个是否检测能量场的字节

            byte[] SendByteArray = new byte[6];

            // 组帧
            try
            {
                SendByteArray[0] = (byte)'P';      //帧头

                SendByteArray[1] = (byte)(3);            //帧长

                SendByteArray[2] = hw_Addr;        //被访问的硬件过滤地址

                SendByteArray[3] = 0;
                try
                {
                    SendByteArray[4] = byte.Parse(nodeNumber.Text);
                }
                catch
                {
                    this.tb_statue.Text = "请择节点号！";
                    this.tb_statue.Refresh();
                    setNodeNumber.Enabled = true;
                    return;
                }
                SendByteArray[5] = (byte)'C';      //帧尾

                //
                //发送、接收、显示
                //sendRecv(SendByteArray,1,5500);
                uart1.setReceInt(100);   //测试串口接收中断使用
                //uart1.sendData(SendByteArray, SendByteArray.Length);  // 通过串口发送数据

                sendRecv(SendByteArray, 2, 300);

                //System.Threading.Thread.Sleep(time);

                
                


                setNodeNumber.Enabled = true;
            }
            catch
            {
                //this.Txt_recv1.Text = "有误:可能没串口！";
                this.tb_statue.Text = "设置节点号失败，没有找到TargetNode！";
                this.tb_statue.Refresh();
                setNodeNumber.Enabled = true;
            }
        }

        private void groupBox3_Enter(object sender, EventArgs e)
        {

        }
    }
}
