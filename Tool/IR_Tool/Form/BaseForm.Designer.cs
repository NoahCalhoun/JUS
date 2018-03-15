namespace IR_Tool
{
    partial class BaseForm
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BaseForm));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openXMLToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.bmpToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.pngToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.importToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveSILToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.spriteToolToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.animationDataEditToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.bMPToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pNGToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.bmpToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.pngToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.modeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.spriteToolModeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.dataEditModeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.button1 = new System.Windows.Forms.Button();
            this.TestListBox = new System.Windows.Forms.ListBox();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.viewToolStripMenuItem,
            this.modeToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1264, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openXMLToolStripMenuItem,
            this.openToolStripMenuItem,
            this.openToolStripMenuItem1,
            this.importToolStripMenuItem,
            this.saveSILToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            this.fileToolStripMenuItem.Click += new System.EventHandler(this.FileClick);
            // 
            // openXMLToolStripMenuItem
            // 
            this.openXMLToolStripMenuItem.Name = "openXMLToolStripMenuItem";
            this.openXMLToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.openXMLToolStripMenuItem.Text = "Import (.XML)";
            this.openXMLToolStripMenuItem.Click += new System.EventHandler(this.ImportXmlClick);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.openToolStripMenuItem.Text = "Export (.XML)";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.ExportXmlClick);
            // 
            // openToolStripMenuItem1
            // 
            this.openToolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.bmpToolStripMenuItem2,
            this.pngToolStripMenuItem2});
            this.openToolStripMenuItem1.Name = "openToolStripMenuItem1";
            this.openToolStripMenuItem1.Size = new System.Drawing.Size(180, 22);
            this.openToolStripMenuItem1.Text = "Add (Img)";
            this.openToolStripMenuItem1.Click += new System.EventHandler(this.AddImgClick);
            // 
            // bmpToolStripMenuItem2
            // 
            this.bmpToolStripMenuItem2.Name = "bmpToolStripMenuItem2";
            this.bmpToolStripMenuItem2.Size = new System.Drawing.Size(102, 22);
            this.bmpToolStripMenuItem2.Text = ".bmp";
            this.bmpToolStripMenuItem2.Click += new System.EventHandler(this.AddBmpImage);
            // 
            // pngToolStripMenuItem2
            // 
            this.pngToolStripMenuItem2.Name = "pngToolStripMenuItem2";
            this.pngToolStripMenuItem2.Size = new System.Drawing.Size(102, 22);
            this.pngToolStripMenuItem2.Text = ".png";
            this.pngToolStripMenuItem2.Click += new System.EventHandler(this.AddPngImage);
            // 
            // importToolStripMenuItem
            // 
            this.importToolStripMenuItem.Enabled = false;
            this.importToolStripMenuItem.Name = "importToolStripMenuItem";
            this.importToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.importToolStripMenuItem.Text = "Open (.SIL)";
            // 
            // saveSILToolStripMenuItem
            // 
            this.saveSILToolStripMenuItem.Enabled = false;
            this.saveSILToolStripMenuItem.Name = "saveSILToolStripMenuItem";
            this.saveSILToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.saveSILToolStripMenuItem.Text = "Save (.SIL)";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.FormExitClick);
            // 
            // spriteToolToolStripMenuItem
            // 
            this.spriteToolToolStripMenuItem.Name = "spriteToolToolStripMenuItem";
            this.spriteToolToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // animationDataEditToolStripMenuItem
            // 
            this.animationDataEditToolStripMenuItem.Name = "animationDataEditToolStripMenuItem";
            this.animationDataEditToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // bMPToolStripMenuItem
            // 
            this.bMPToolStripMenuItem.Name = "bMPToolStripMenuItem";
            this.bMPToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // pNGToolStripMenuItem
            // 
            this.pNGToolStripMenuItem.Name = "pNGToolStripMenuItem";
            this.pNGToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.BackgroundImage")));
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Location = new System.Drawing.Point(0, 27);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(485, 43);
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            // 
            // bmpToolStripMenuItem1
            // 
            this.bmpToolStripMenuItem1.Name = "bmpToolStripMenuItem1";
            this.bmpToolStripMenuItem1.Size = new System.Drawing.Size(180, 22);
            this.bmpToolStripMenuItem1.Text = ".bmp";
            // 
            // pngToolStripMenuItem1
            // 
            this.pngToolStripMenuItem1.Name = "pngToolStripMenuItem1";
            this.pngToolStripMenuItem1.Size = new System.Drawing.Size(180, 22);
            this.pngToolStripMenuItem1.Text = ",png";
            // 
            // viewToolStripMenuItem
            // 
            this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
            this.viewToolStripMenuItem.Size = new System.Drawing.Size(45, 20);
            this.viewToolStripMenuItem.Text = "View";
            this.viewToolStripMenuItem.Click += new System.EventHandler(this.ViewClick);
            // 
            // modeToolStripMenuItem
            // 
            this.modeToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.spriteToolModeToolStripMenuItem,
            this.dataEditModeToolStripMenuItem});
            this.modeToolStripMenuItem.Name = "modeToolStripMenuItem";
            this.modeToolStripMenuItem.Size = new System.Drawing.Size(50, 20);
            this.modeToolStripMenuItem.Text = "Mode";
            this.modeToolStripMenuItem.Click += new System.EventHandler(this.ModeClick);
            // 
            // spriteToolModeToolStripMenuItem
            // 
            this.spriteToolModeToolStripMenuItem.Checked = true;
            this.spriteToolModeToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.spriteToolModeToolStripMenuItem.Name = "spriteToolModeToolStripMenuItem";
            this.spriteToolModeToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.spriteToolModeToolStripMenuItem.Text = "Sprite Tool Mode";
            this.spriteToolModeToolStripMenuItem.Click += new System.EventHandler(this.SpriteToolModeClick);
            // 
            // dataEditModeToolStripMenuItem
            // 
            this.dataEditModeToolStripMenuItem.Name = "dataEditModeToolStripMenuItem";
            this.dataEditModeToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.dataEditModeToolStripMenuItem.Text = "Data Edit Mode";
            this.dataEditModeToolStripMenuItem.Click += new System.EventHandler(this.DataEditModeClick);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            this.helpToolStripMenuItem.Click += new System.EventHandler(this.HelpClick);
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.SystemColors.InactiveCaption;
            this.button1.Location = new System.Drawing.Point(491, 30);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(96, 39);
            this.button1.TabIndex = 2;
            this.button1.Text = "TestButton";
            this.button1.UseVisualStyleBackColor = false;
            // 
            // TestListBox
            // 
            this.TestListBox.BackColor = System.Drawing.SystemColors.InactiveCaption;
            this.TestListBox.FormattingEnabled = true;
            this.TestListBox.Location = new System.Drawing.Point(0, 76);
            this.TestListBox.Name = "TestListBox";
            this.TestListBox.Size = new System.Drawing.Size(485, 472);
            this.TestListBox.TabIndex = 3;
            // 
            // BaseForm
            // 
            this.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Window;
            this.ClientSize = new System.Drawing.Size(1264, 921);
            this.Controls.Add(this.TestListBox);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.menuStrip1);
            this.Cursor = System.Windows.Forms.Cursors.Default;
            this.DoubleBuffered = true;
            this.Font = new System.Drawing.Font("휴먼엑스포", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.ForeColor = System.Drawing.SystemColors.ControlText;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.MaximumSize = new System.Drawing.Size(1280, 960);
            this.MinimumSize = new System.Drawing.Size(1280, 960);
            this.Name = "BaseForm";
            this.Text = "IRT";
            this.TransparencyKey = System.Drawing.Color.DimGray;
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openXMLToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem bMPToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pNGToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem importToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveSILToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.ToolStripMenuItem spriteToolToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem animationDataEditToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem bmpToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem pngToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem bmpToolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem pngToolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem viewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem modeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem spriteToolModeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem dataEditModeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ListBox TestListBox;
    }
}

