using System;
using System.Collections.Generic;
using System.Net.Http;

namespace cSharpSolution
{
    internal class Program
    {
        private static readonly HttpClient s_httpClient = new HttpClient();

        private static void Main(string[] args)
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

        private static async void Main2(string[] args)
        {
            // 用async/await代替上面的实现
            string text = await s_httpClient.GetStringAsync("http://www.baidu.com");
            Console.WriteLine(text);
        }
    }
}