namespace IR_Tool
{
    partial class AtlasForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AtlasForm));
            this.ImageList = new System.Windows.Forms.ListBox();
            this.Single_Img_Panel = new System.Windows.Forms.Panel();
            this.Load_File = new System.Windows.Forms.Button();
            this.Load_Folder = new System.Windows.Forms.Button();
            this.InfoGroupBox = new System.Windows.Forms.GroupBox();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.파일 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.MainMenuBar = new System.Windows.Forms.MenuStrip();
            this.ModeMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.애니메이션툴ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.이펙트툴ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.충돌및플래그설정툴ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MainMenuBar.SuspendLayout();
            this.SuspendLayout();
            // 
            // ImageList
            // 
            this.ImageList.FormattingEnabled = true;
            this.ImageList.ItemHeight = 12;
            this.ImageList.Location = new System.Drawing.Point(12, 269);
            this.ImageList.Name = "ImageList";
            this.ImageList.Size = new System.Drawing.Size(311, 400);
            this.ImageList.TabIndex = 0;
            // 
            // Single_Img_Panel
            // 
            this.Single_Img_Panel.Location = new System.Drawing.Point(12, 34);
            this.Single_Img_Panel.Name = "Single_Img_Panel";
            this.Single_Img_Panel.Size = new System.Drawing.Size(310, 229);
            this.Single_Img_Panel.TabIndex = 1;
            this.Single_Img_Panel.Paint += new System.Windows.Forms.PaintEventHandler(this.Render);
            // 
            // Load_File
            // 
            this.Load_File.Location = new System.Drawing.Point(329, 269);
            this.Load_File.Name = "Load_File";
            this.Load_File.Size = new System.Drawing.Size(121, 42);
            this.Load_File.TabIndex = 2;
            this.Load_File.Text = "파일 불러오기";
            this.Load_File.UseVisualStyleBackColor = true;
            // 
            // Load_Folder
            // 
            this.Load_Folder.Location = new System.Drawing.Point(329, 317);
            this.Load_Folder.Name = "Load_Folder";
            this.Load_Folder.Size = new System.Drawing.Size(121, 42);
            this.Load_Folder.TabIndex = 3;
            this.Load_Folder.Text = "폴더 불러오기";
            this.Load_Folder.UseVisualStyleBackColor = true;
            // 
            // InfoGroupBox
            // 
            this.InfoGroupBox.Location = new System.Drawing.Point(329, 28);
            this.InfoGroupBox.Name = "InfoGroupBox";
            this.InfoGroupBox.Size = new System.Drawing.Size(233, 235);
            this.InfoGroupBox.TabIndex = 4;
            this.InfoGroupBox.TabStop = false;
            this.InfoGroupBox.Text = "정보";
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(61, 4);
            // 
            // 파일
            // 
            this.파일.Name = "파일";
            this.파일.Size = new System.Drawing.Size(61, 4);
            // 
            // MainMenuBar
            // 
            this.MainMenuBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ModeMenu});
            this.MainMenuBar.Location = new System.Drawing.Point(0, 0);
            this.MainMenuBar.Name = "MainMenuBar";
            this.MainMenuBar.Size = new System.Drawing.Size(1264, 24);
            this.MainMenuBar.TabIndex = 5;
            this.MainMenuBar.Text = "menuStrip1";
            // 
            // ModeMenu
            // 
            this.ModeMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.애니메이션툴ToolStripMenuItem,
            this.이펙트툴ToolStripMenuItem,
            this.충돌및플래그설정툴ToolStripMenuItem});
            this.ModeMenu.Name = "ModeMenu";
            this.ModeMenu.Size = new System.Drawing.Size(59, 20);
            this.ModeMenu.Text = "기타 툴";
            // 
            // 애니메이션툴ToolStripMenuItem
            // 
            this.애니메이션툴ToolStripMenuItem.Name = "애니메이션툴ToolStripMenuItem";
            this.애니메이션툴ToolStripMenuItem.Size = new System.Drawing.Size(198, 22);
            this.애니메이션툴ToolStripMenuItem.Text = "애니메이션 툴";
            // 
            // 이펙트툴ToolStripMenuItem
            // 
            this.이펙트툴ToolStripMenuItem.Name = "이펙트툴ToolStripMenuItem";
            this.이펙트툴ToolStripMenuItem.Size = new System.Drawing.Size(198, 22);
            this.이펙트툴ToolStripMenuItem.Text = "이펙트 툴";
            // 
            // 충돌및플래그설정툴ToolStripMenuItem
            // 
            this.충돌및플래그설정툴ToolStripMenuItem.Name = "충돌및플래그설정툴ToolStripMenuItem";
            this.충돌및플래그설정툴ToolStripMenuItem.Size = new System.Drawing.Size(198, 22);
            this.충돌및플래그설정툴ToolStripMenuItem.Text = "충돌 및 플래그 설정 툴";
            // 
            // AtlasForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Window;
            this.ClientSize = new System.Drawing.Size(1264, 681);
            this.Controls.Add(this.MainMenuBar);
            this.Controls.Add(this.InfoGroupBox);
            this.Controls.Add(this.Load_Folder);
            this.Controls.Add(this.Load_File);
            this.Controls.Add(this.Single_Img_Panel);
            this.Controls.Add(this.ImageList);
            this.ForeColor = System.Drawing.SystemColors.WindowText;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.MainMenuBar;
            this.Name = "AtlasForm";
            this.Text = "Atlas Tool";
            this.Load += new System.EventHandler(this.Main_Load);
            this.MainMenuBar.ResumeLayout(false);
            this.MainMenuBar.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox ImageList;
        private System.Windows.Forms.Panel Single_Img_Panel;
        private System.Windows.Forms.Button Load_File;
        private System.Windows.Forms.Button Load_Folder;
        private System.Windows.Forms.GroupBox InfoGroupBox;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ContextMenuStrip 파일;
        private System.Windows.Forms.MenuStrip MainMenuBar;
        private System.Windows.Forms.ToolStripMenuItem ModeMenu;
        private System.Windows.Forms.ToolStripMenuItem 애니메이션툴ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 이펙트툴ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 충돌및플래그설정툴ToolStripMenuItem;
    }
}