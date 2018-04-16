using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IR_Tool.DesignPattern;
using IR_Tool._99.Dev;

namespace IR_Tool.Management
{
    class SystemMgr : Singleton<SystemMgr>
    {
        private CDevice m_Device;
        
        public void Init(System.Windows.Forms.Control _RenderTarget)
        {
            m_Device = new CDevice();
            m_Device.Init(_RenderTarget);
        }

        public void Update()
        {

        }

        public void BeginRender()
        {
            m_Device.BeginRender();
        }

        public void EndRender()
        {
            m_Device.EndRender();
        }

        public CDevice GetCDevice()
        {
            return m_Device;
        }
    }
}
