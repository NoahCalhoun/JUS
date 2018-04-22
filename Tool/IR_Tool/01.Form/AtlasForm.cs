using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using IR_Tool.Management;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;


namespace IR_Tool
{
    
    public partial class AtlasForm : Form
    {
        public AtlasForm()
        {
            InitializeComponent();
        }

        private void Main_Load(object sender, EventArgs e)
        {
            SystemMgr.Instance.Init(this.Single_Img_Panel);
        }
        
        private void Render(object sender, PaintEventArgs e)
        {
            SystemMgr.Instance.BeginRender();
            SystemMgr.Instance.EndRender();
        }
    }
}
