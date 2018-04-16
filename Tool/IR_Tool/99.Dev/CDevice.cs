using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace IR_Tool._99.Dev
{
    class CDevice
    {
        private Device device = null;
        
        public void Init(System.Windows.Forms.Control _RenderTarget)
        {
            PresentParameters pp = new PresentParameters();

            pp.Windowed = true;
            pp.SwapEffect = SwapEffect.Discard;
            pp.EnableAutoDepthStencil = true;
            pp.AutoDepthStencilFormat = DepthFormat.D16;
            device = new Device(0, DeviceType.Hardware, _RenderTarget, CreateFlags.SoftwareVertexProcessing, pp);
        }

        public Device GetDevice()
        {
            if (device == null)
            {
                MessageBox.Show("GetDevice() Device NULL");
                return null;
            }
            return device;
        }

        public void BeginRender()
        {
            if (device == null)
            {
                MessageBox.Show("BeginRender() Device NULL");
                return;
            }

            device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.Blue, 1.0f, 0);
            device.BeginScene();
        }

        public void EndRender()
        {
            if (device == null)
            {
                MessageBox.Show("EndRender() Device NULL");
                return;
            }

            device.EndScene();
            device.Present();
        }
    }
}
