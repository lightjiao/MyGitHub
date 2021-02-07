using System;
using System.Collections.Generic;
using System.Net.Http;

namespace cSharpSolution
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            TestDelegate();
        }

        /// <summary>
        /// 测试委托的声明是何时初始化为一个object的
        /// </summary>
        private static void TestDelegate()
        {
            // 声明一个null的delegate 并没有获得一个对象
            Action<string> testPrint = null;
            var a = testPrint;

            // 只有第一次添加函数时才初始化这个委托对象
            testPrint += (x) => { Console.WriteLine($"Hello {x}"); };
            a += (x) => { Console.WriteLine($"Goodbye {x}"); };

            testPrint?.Invoke("rose");
            a?.Invoke("jack");
        }

        private static void TestDictionary()
        {
            var testMap = new Dictionary<int, HashSet<int>>();
            testMap[1] = new HashSet<int> { 1, 1, 1, 1 };

            Console.WriteLine(testMap[1]);

            /// 字典的 ?[index] 会报错
            /// System.Collections.Generic.HashSet`1[System.Int32]
            /// Unhandled exception. System.Collections.Generic.KeyNotFoundException: The given key '2' was not present in the dictionary.
            /// at System.Collections.Generic.Dictionary`2.get_Item(TKey key)
            /// at cSharpSolution.Program.Main(String[] args) in C:\develop\MyGitHub\cSharp\cSharpSolution\Program.cs:line 19
            //var c = testMap?[2];
            //Console.WriteLine(c);

            HashSet<int> ret = new HashSet<int>()
                ;
            var tryRet = testMap?.TryGetValue(1, out ret);
            Console.WriteLine(tryRet);

            tryRet = testMap?.TryGetValue(2, out ret);
            Console.WriteLine(tryRet);
        }

        private static async void TestAsync(string[] args)
        {
            // 用async/await代替上面的实现
            var s_httpClient = new HttpClient();
            string text = await s_httpClient.GetStringAsync("http://www.baidu.com");
            Console.WriteLine(text);
        }
    }
}