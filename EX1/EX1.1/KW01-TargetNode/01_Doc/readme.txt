1. PC节点透传
判断握手命令还是转发命令依据：硬件地址
	硬件地址   = 0   --握手命令
	硬件地址 != 0   --转发命令
2. 数据帧格式
/**********************************************上位机发送帧格式*********************************************************************
帧头（1B 'P'）+ 帧长（1B） + 硬件地址（1B）+ 软件地址（4B[网络地址2B）+网内地址（2B）]）+命令（1B）+ 子命令（可选） + 帧尾（1B 'C'）

/*********************************************节点返回帧格式************************************************************************
帧头（1B 'T') + 帧长（1B） + 硬件地址（1B）+ 软件地址（4B[网络地址2B）+网内地址（2B）]）+命令（1B）+ 子命令（可选） + 节点返回数据（nB) + 帧尾（1B 'D') 

命令 ：
     （1）0x00：读目标节点FLASH127页的系统参数
     （2）0x01：写目标节点FLASH127页的系统参数
     （3）0x02：验证RF收发
     （4）0x03：灯控命令字
     （5）0x04：读取FLASH指定页内容
     （6）0x05：写入FLASH指定页内容
     （7）0x06：写入FLASH图片
    
    具体各个模块帧命令见PC端doc里面的工程说明文件。
 
3. 硬件接线
    （1）运行指示灯（LIGHT_RUN_1）：D口7脚，在“06_App_Component\light\light.h"文件中定义；
            低电平点亮，也在该文件中定义。
    （2）串口通讯引脚：串口0模块的发送引脚为PTA0，接收引脚为PTA1，
            在“05_Driver\uart\uart.h"文件中定义；
            对应底板上的RX0，TX0，串口通讯使用RX、TX、GND三根线；5V可以用于给板子供电。
      TX对应接白线，RX接绿线，GND接黑线，5V接红线。

4. 其他说明
实现功能：
1）PC节点检测及RF收发功能
单击“检测PC节点”按钮，自动搜寻找到PCNode(PC节点）。
单击“验证RF收发”按钮，能收到由TargetNode回送的数据。
2）数据收发：输入测试数据内容，点击“验证RF收发”按钮，下框中会收到Target节点回送的测试信息，即可验证通信良好。
3）温度采集
单击“开始采集”，Target节点每隔3秒自动采集一次，通过RF发送到PC节点，PC节点再传到PC端。
4）小灯控制
小灯接在PORTB|（1）的gpio口，程序一开始运行，小灯默认打开，当点击C#端的“打开小灯”，则小灯打开，并且target端会传回数据，表明小灯操作执行
5）flash读写测试：设置扇区号，偏移量和读写字节数，点击“target Flash读测试”，可以读到对应扇区、对应偏移位置的数据，数据量为输入的读写字节数；设置扇区号、偏移量和写入数据，点击“target Flash写测试”，可以将所输入的数据写入到指定位置；
6）图片读写：点击“打开图片”，选取要发送的图片，左侧图片框和文本框会显示待发送的图片、图片转为字符的结果和图片大小（即索要发送的字节数）。注：所选图片大小不超过5000字节。点击“发送图片”即可将图片发送至terget节点并存入flash；点击“读取图片”，可以从target端的flash中将图片字符串数据读回，显示在右侧文本框，点击“还原图片”，可以将字符串转换成为图片显示出来。


5.工程要素
中断：
1）isr_uart0_re,UART_0（串口0）中断服务例程
参数说明：user_isr_ptr：用户自定义参数，此处未用
功能概要：每接收到一个字节，产生一次串口接收中断，执行本例程一次。
         本例程对串口收到的数据，原样发送出去，实现串口数据回显功能。
2）isr_gpio_cd,PTC、PTD端口中断服务例程
参数说明：user_isr_ptr：用户自定义参数，此处未用
功能概要：每接收到一帧64个字节的RF数据，产生一次本中断。
         本例程对收到的数据，按照RF_ReceiveFrame函数对数据进行接收
         组帧。接收成功后，置lwevent_group事件组的EVENT_RF_RECV事件
         位（在"01_app_include.h"文件中声明的）。

任务：
1）task_adc
功能概要：读取26通道的温度物理量，计算出温度值，
                该任务优先级为14
task_light
功能概要：控制运行指示灯每隔1s闪烁，该任务优先级为14
task_lightctrl
功能概要：获取PC机传来的控制信息，改变小灯的状态
                该任务优先级为14
task_picwrite
功能概要：等待flash图片写入事件位，将图片写入到99开始的扇区对应位置。
				  通过图片缓冲区Pic_Arr的前两位计算出所需要存储的字节数，
              从而计算出所需要擦除的扇区数。然后擦除对应扇区，
               将表示图片字节数的两个字节写入第99扇区的偏移量为1000开始的两个字节。
               之后，Pic_Arr每1000字节写入到99扇区开始的偏移量为0开始的1000个字节位置。
               写入完毕，清除图片写入事件位。
               该任务优先级为9
task_rf_recv
功能概要：判断RF接收事件位EVENT_RF_RECV，置一后调用FrameCheck()、
         FrameDataCheck()函数对数据帧进行校验，校验成功后调用command_proc()函数
         对帧命令解析与处理，并对需要回发数据的帧进行组帧、置RF发送事件位，然后
         清除RF接收事件位，继续等待RF接收事件位置一。
task_rf_send
功能概要：判断RF发送事件位EVENT_RF_SEND，
                置一后调用RFSendDataByCSMACA()函数转发
                接收数据包，然后清除RF发送事件位，继续等待RF发送事件位置一。


=============================================================================
声明：
（1）我们开发的源代码，在本中心提供的硬件系统测试通过，真诚奉献给社会，
     不足之处，欢迎指正。
（2）对于使用非本中心硬件系统的用户，移植代码时，请仔细根据自己的硬件匹配。

苏州大学飞思卡尔嵌入式中心
技术咨询：http://sumcu.suda.edu.cn;0512-65214835

