namespace SerialPort
{
    partial class FrmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmMain));
            this.btnCheckPcNode = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.lbl_PC_Node_State = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.hwAddr = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.Txt_recv2 = new System.Windows.Forms.TextBox();
            this.btnClear1 = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.nodeSelect = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.btnVerifyRF = new System.Windows.Forms.Button();
            this.tbWriteData2 = new System.Windows.Forms.TextBox();
            this.nodeNumber = new System.Windows.Forms.ComboBox();
            this.setNodeNumber = new System.Windows.Forms.Button();
            this.tb_statue = new System.Windows.Forms.TextBox();
            this.设置节点号 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.设置节点号.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnCheckPcNode
            // 
            this.btnCheckPcNode.Location = new System.Drawing.Point(208, 22);
            this.btnCheckPcNode.Name = "btnCheckPcNode";
            this.btnCheckPcNode.Size = new System.Drawing.Size(136, 36);
            this.btnCheckPcNode.TabIndex = 0;
            this.btnCheckPcNode.Text = "检测PC节点";
            this.btnCheckPcNode.UseVisualStyleBackColor = true;
            this.btnCheckPcNode.Click += new System.EventHandler(this.btnCheckPcNode_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.groupBox1.BackColor = System.Drawing.Color.White;
            this.groupBox1.Controls.Add(this.lbl_PC_Node_State);
            this.groupBox1.Controls.Add(this.btnCheckPcNode);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.hwAddr);
            this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.groupBox1.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox1.ForeColor = System.Drawing.Color.Tomato;
            this.groupBox1.Location = new System.Drawing.Point(4, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(376, 118);
            this.groupBox1.TabIndex = 20;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "PC节点状态";
            // 
            // lbl_PC_Node_State
            // 
            this.lbl_PC_Node_State.AutoSize = true;
            this.lbl_PC_Node_State.Font = new System.Drawing.Font("宋体", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_PC_Node_State.ForeColor = System.Drawing.Color.Blue;
            this.lbl_PC_Node_State.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.lbl_PC_Node_State.Location = new System.Drawing.Point(2, 30);
            this.lbl_PC_Node_State.Name = "lbl_PC_Node_State";
            this.lbl_PC_Node_State.Size = new System.Drawing.Size(196, 20);
            this.lbl_PC_Node_State.TabIndex = 1;
            this.lbl_PC_Node_State.Text = "lbl_PC_Node_State";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.label1.Location = new System.Drawing.Point(8, 82);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(164, 21);
            this.label1.TabIndex = 23;
            this.label1.Text = "硬件过滤地址：";
            // 
            // hwAddr
            // 
            this.hwAddr.Location = new System.Drawing.Point(208, 72);
            this.hwAddr.Name = "hwAddr";
            this.hwAddr.ReadOnly = true;
            this.hwAddr.Size = new System.Drawing.Size(53, 31);
            this.hwAddr.TabIndex = 24;
            this.hwAddr.Text = "255";
            // 
            // timer1
            // 
            this.timer1.Interval = 3000;
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.textBox2);
            this.groupBox7.Controls.Add(this.Txt_recv2);
            this.groupBox7.Controls.Add(this.btnClear1);
            this.groupBox7.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox7.ForeColor = System.Drawing.SystemColors.Highlight;
            this.groupBox7.Location = new System.Drawing.Point(4, 200);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(547, 103);
            this.groupBox7.TabIndex = 27;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "串口接收信息";
            // 
            // textBox2
            // 
            this.textBox2.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.textBox2.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox2.ForeColor = System.Drawing.Color.AliceBlue;
            this.textBox2.Location = new System.Drawing.Point(-7, 198);
            this.textBox2.Multiline = true;
            this.textBox2.Name = "textBox2";
            this.textBox2.ReadOnly = true;
            this.textBox2.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox2.Size = new System.Drawing.Size(720, 26);
            this.textBox2.TabIndex = 25;
            this.textBox2.Text = "KW01无线收发测试软件B1功能：\r\n\r\n单击按钮，自动搜寻找到KW01的PC_NODE，显示相关信息。";
            // 
            // Txt_recv2
            // 
            this.Txt_recv2.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.Txt_recv2.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Txt_recv2.ForeColor = System.Drawing.Color.Blue;
            this.Txt_recv2.Location = new System.Drawing.Point(6, 20);
            this.Txt_recv2.Multiline = true;
            this.Txt_recv2.Name = "Txt_recv2";
            this.Txt_recv2.ReadOnly = true;
            this.Txt_recv2.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.Txt_recv2.Size = new System.Drawing.Size(437, 69);
            this.Txt_recv2.TabIndex = 24;
            // 
            // btnClear1
            // 
            this.btnClear1.Location = new System.Drawing.Point(449, 60);
            this.btnClear1.Name = "btnClear1";
            this.btnClear1.Size = new System.Drawing.Size(92, 29);
            this.btnClear1.TabIndex = 21;
            this.btnClear1.Text = "清空显示框";
            this.btnClear1.UseVisualStyleBackColor = true;
            this.btnClear1.Click += new System.EventHandler(this.btnClear1_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.nodeSelect);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.textBox3);
            this.groupBox2.Controls.Add(this.btnVerifyRF);
            this.groupBox2.Controls.Add(this.tbWriteData2);
            this.groupBox2.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox2.ForeColor = System.Drawing.SystemColors.Highlight;
            this.groupBox2.Location = new System.Drawing.Point(4, 136);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(547, 58);
            this.groupBox2.TabIndex = 33;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "数字发送";
            // 
            // nodeSelect
            // 
            this.nodeSelect.AutoCompleteCustomSource.AddRange(new string[] {
            "1",
            "2",
            "3"});
            this.nodeSelect.FormattingEnabled = true;
            this.nodeSelect.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.nodeSelect.Items.AddRange(new object[] {
            "1",
            "2",
            "3"});
            this.nodeSelect.Location = new System.Drawing.Point(248, 20);
            this.nodeSelect.Name = "nodeSelect";
            this.nodeSelect.Size = new System.Drawing.Size(121, 25);
            this.nodeSelect.TabIndex = 29;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 25);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(44, 17);
            this.label2.TabIndex = 26;
            this.label2.Text = "数字：";
            // 
            // textBox3
            // 
            this.textBox3.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.textBox3.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox3.ForeColor = System.Drawing.Color.AliceBlue;
            this.textBox3.Location = new System.Drawing.Point(6, 159);
            this.textBox3.Multiline = true;
            this.textBox3.Name = "textBox3";
            this.textBox3.ReadOnly = true;
            this.textBox3.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox3.Size = new System.Drawing.Size(648, 123);
            this.textBox3.TabIndex = 20;
            this.textBox3.Text = "KW01无线收发测试软件B1功能：\r\n\r\n单击按钮，自动搜寻找到KW01的PC_NODE，显示相关信息。";
            // 
            // btnVerifyRF
            // 
            this.btnVerifyRF.Location = new System.Drawing.Point(382, 20);
            this.btnVerifyRF.Name = "btnVerifyRF";
            this.btnVerifyRF.Size = new System.Drawing.Size(135, 26);
            this.btnVerifyRF.TabIndex = 22;
            this.btnVerifyRF.Text = "发送";
            this.btnVerifyRF.UseVisualStyleBackColor = true;
            this.btnVerifyRF.Click += new System.EventHandler(this.btnVerifyRF_Click);
            // 
            // tbWriteData2
            // 
            this.tbWriteData2.Location = new System.Drawing.Point(56, 22);
            this.tbWriteData2.Name = "tbWriteData2";
            this.tbWriteData2.Size = new System.Drawing.Size(124, 23);
            this.tbWriteData2.TabIndex = 24;
            // 
            // nodeNumber
            // 
            this.nodeNumber.FormattingEnabled = true;
            this.nodeNumber.Items.AddRange(new object[] {
            "1",
            "2",
            "3"});
            this.nodeNumber.Location = new System.Drawing.Point(6, 30);
            this.nodeNumber.Name = "nodeNumber";
            this.nodeNumber.Size = new System.Drawing.Size(121, 29);
            this.nodeNumber.TabIndex = 27;
            // 
            // setNodeNumber
            // 
            this.setNodeNumber.ForeColor = System.Drawing.Color.Blue;
            this.setNodeNumber.Location = new System.Drawing.Point(6, 65);
            this.setNodeNumber.Name = "setNodeNumber";
            this.setNodeNumber.Size = new System.Drawing.Size(112, 33);
            this.setNodeNumber.TabIndex = 28;
            this.setNodeNumber.Text = "设置节点号";
            this.setNodeNumber.UseVisualStyleBackColor = true;
            this.setNodeNumber.Click += new System.EventHandler(this.setNodeNumber_Click);
            // 
            // tb_statue
            // 
            this.tb_statue.Location = new System.Drawing.Point(4, 309);
            this.tb_statue.Name = "tb_statue";
            this.tb_statue.Size = new System.Drawing.Size(547, 21);
            this.tb_statue.TabIndex = 26;
            // 
            // 设置节点号
            // 
            this.设置节点号.Controls.Add(this.nodeNumber);
            this.设置节点号.Controls.Add(this.setNodeNumber);
            this.设置节点号.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.设置节点号.ForeColor = System.Drawing.Color.Tomato;
            this.设置节点号.Location = new System.Drawing.Point(386, 12);
            this.设置节点号.Name = "设置节点号";
            this.设置节点号.Size = new System.Drawing.Size(165, 118);
            this.设置节点号.TabIndex = 34;
            this.设置节点号.TabStop = false;
            this.设置节点号.Text = "设置节点号";
            this.设置节点号.Enter += new System.EventHandler(this.groupBox3_Enter);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(186, 25);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(56, 17);
            this.label3.TabIndex = 30;
            this.label3.Text = "节点号：";
            // 
            // FrmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.ClientSize = new System.Drawing.Size(559, 338);
            this.Controls.Add(this.设置节点号);
            this.Controls.Add(this.groupBox7);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.tb_statue);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FrmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "KW01节点加法-李嘉维";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FrmMain_FormClosing);
            this.Load += new System.EventHandler(this.FrmMain_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.设置节点号.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnCheckPcNode;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label lbl_PC_Node_State;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox hwAddr;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox Txt_recv2;
        private System.Windows.Forms.Button btnClear1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.ComboBox nodeSelect;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Button btnVerifyRF;
        private System.Windows.Forms.TextBox tbWriteData2;
        private System.Windows.Forms.ComboBox nodeNumber;
        private System.Windows.Forms.Button setNodeNumber;
        private System.Windows.Forms.TextBox tb_statue;
        private System.Windows.Forms.GroupBox 设置节点号;
        private System.Windows.Forms.Label label3;
    }
}

