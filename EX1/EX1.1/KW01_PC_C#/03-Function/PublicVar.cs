namespace SerialPort
{
    /// --------------------------------------------------------------------*
    /// <summary>                                                           *
    /// 类功能:定义全局变量                                                 *
    /// </summary>                                                          *
    /// <remarks></remarks>                                                 *
    /// ------------------- ------------------------------------------------*
    public partial class PublicVar
    {
        //定义串口的全局变量,设置成静态的
        public static byte[] g_ReceiveByteArray = new byte[250];//存放接收的数据
        public static byte[] g_SendByteArray;                   //存放要发送的数据
        public static string g_SCIComNum;                       //存放选择的串口号
        public static int g_SCIBaudRate;                        //存放选择的波特率
        public static byte g_ReceiveByteArrayLen = 0;           //接收缓冲区字节数
    }
}