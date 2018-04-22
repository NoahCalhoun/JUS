using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IR_Tool.DesignPattern
{
    public class Singleton<T> where T : class, new()
    {
        protected static object _instanceLock = new object();
        protected static volatile T _instance;
        public static T Instance
        {
            get
            {
                lock(_instanceLock)
                {
                    if (_instance == null)
                        _instance = new T();
                }
                return _instance;
            }
        }
    }
}
