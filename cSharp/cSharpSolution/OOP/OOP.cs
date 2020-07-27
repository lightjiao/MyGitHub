using System;
using System.Collections.Generic;
using System.Text;

namespace cSharpSolution.OOP
{
    public class Base
    {
        public Base()
        {
            Console.WriteLine("Base print");
        }

        public virtual void Init()
        {
            Console.WriteLine("Base init");
        }
    }

    public class OOP : Base
    {
        public OOP() : base()
        {
            // 这里是先调用 base() 再调用 OOP()
            Console.WriteLine("OOP print");
        }

        public override void Init() // 普通函数没有 ` :xxx() `的写法
        {
            base.Init();
        }
    }
}
