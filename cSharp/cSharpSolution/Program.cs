﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;

namespace cSharpSolution
{
    internal class Program
    {
        private static async Task Main(string[] args)
        {
            var sd = new SortedDictionary<int, string>();
            sd[3] = "3333";
            sd[1] = "1111";
            sd[2] = "2222";
            foreach (var item in sd)
            {
                Console.WriteLine(item);
            }
        }

        [Flags]
        public enum StateFlag
        {
            None = 0,

            //---
            Squat = 0x1,
            Stand = 0x2,

            //---
            NotFight = 0x10,
            Fight = 0x20,
        }

        private static void TestEnumFlagV2()
        {
            bool StateCheck(StateFlag state, StateFlag check)
            {
                return (state & check) == check;
            }

            var state = StateFlag.Stand | StateFlag.NotFight;

            Console.WriteLine($"Should true: {StateCheck(state, StateFlag.Stand)}");
            Console.WriteLine($"Should true: {StateCheck(state, StateFlag.NotFight)}");
            Console.WriteLine($"Should false: {StateCheck(state, StateFlag.Squat)}");
            Console.WriteLine($"Should false: {StateCheck(state, StateFlag.Fight)}");

            state = StateFlag.Stand | StateFlag.Fight;
            Console.WriteLine($"Should true: {StateCheck(state, StateFlag.Stand)}");
            Console.WriteLine($"Should false: {StateCheck(state, StateFlag.NotFight)}");
            Console.WriteLine($"Should false: {StateCheck(state, StateFlag.Squat)}");
            Console.WriteLine($"Should true: {StateCheck(state, StateFlag.Fight)}");
        }




        private static void TestRefKeyword()
        {
            // 注意这两行写法的不同
            // var refInt = GetRefIntValue(1); // 这种写法就还是和普通的写法没区别，只是将变量copy一份
            // ref var refInt = ref GetRefIntValue(1); // 这种写法才会使得变量的ref生效
            ref var refInt = ref IntList[1]; // var refInt = IntList[1]; // 这种写法不行
            Console.WriteLine($"IntValue: {IntList[1]}, refInt {refInt}");
            refInt = 100;
            Console.WriteLine($"IntValue: {IntList[1]}, refInt {refInt}");

            // 如果是一个reference类型，ref keyword 就没那么有必要了，因为class本身就是reference类型
            var c = new TestRefKeywordClass { Value = 1 };
            ValueList = new[] { c };

            var anotherC = ValueList[0];
            Console.WriteLine($"IntValue: {ValueList[0].Value}, refInt {anotherC.Value}");
            anotherC.Value = 99;
            Console.WriteLine($"IntValue: {ValueList[0].Value}, refInt {anotherC.Value}");

            ref var refC = ref ValueList[0];
            refC.Value = 101;
            Console.WriteLine($"IntValue: {ValueList[0].Value}, refInt {refC.Value}");
        }

        private static ref int GetRefIntValue(int idx)
        {
            return ref IntList[idx];
        }

        private static readonly int[] IntList = new[] { 1, 2, 3 };
        private static TestRefKeywordClass[] ValueList;

        private class TestRefKeywordClass
        {
            public int Value = 10;
        }


        private static void TestByteOperator()
        {
            var intMax = int.MaxValue;
            var midIntMax = int.MaxValue >> 1;

            Console.WriteLine(intMax);
            Console.WriteLine(midIntMax);

            Console.WriteLine(midIntMax + midIntMax);

            var a = midIntMax + 100;

            Console.WriteLine(midIntMax - 101 > int.MaxValue - a);
            Console.WriteLine(midIntMax + a);
        }

        #region 测试delegate关键字写法

        private static void TestDelegateOperator()
        {
            Mapper((x) => { Console.WriteLine($"hello {x}"); }, 1);
            Mapper((x) => { Console.WriteLine($"hello"); }, 1);
            Mapper(delegate { Console.WriteLine("hello"); }, 1);
        }

        private static void Mapper(Action<int> func, int a)
        {
            func(a);
        }

        #endregion 测试delegate关键字写法

        /// <summary>
        /// 输出结果
        /// main Thread id: 1
        /// ConfigureAwait(true) :await thread 1
        /// ConfigureAwait(false) :await thread 4
        /// </summary>
        /// <returns></returns>
        private static async Task ConfigureAwait()
        {
            // Task.WaitAll(ConfigureAwait()); // run this line in Main()

            Console.WriteLine($"main Thread id: {Thread.CurrentThread.ManagedThreadId}");
            await PrintAsync("ConfigureAwait(true)").ConfigureAwait(true);
            await PrintAsync("ConfigureAwait(false)").ConfigureAwait(false);


            TaskScheduler.FromCurrentSynchronizationContext();
        }

        private static async Task PrintAsync(string str)
        {
            Console.WriteLine($"{str} :await thread {Thread.CurrentThread.ManagedThreadId}");

            // 有一个空的await，才会让编译器认为这个函数真的是一个异步函数，会使得ConfigureAwait的设置生效
            // 如果没有空的await，那么整个异步调用会被编译器优化为同步调用函数，ConfigureAwait的设置当然不论怎么设置都不会生效
            await Task.Run(() => { });
        }

        /// <summary>
        /// 结论是哪怕skip超出了上限，也不会造成exception ( 因为结果是一个IEnumerate呀 )
        /// </summary>
        private static void TestLinqSkipTake()
        {
            var acc = Enumerable.Range(1, 5).Skip(100).Take(1);
            foreach (var item in acc)
            {
                Console.WriteLine(item);
            }
        }

        /// <summary>
        /// 只能返回与元素类型相同的数据类型
        /// </summary>
        private static void TestLinqAggregate()
        {
            var acc = Enumerable.Range(1, 10).Aggregate(0, (acc, x) =>
            {
                if (acc > x) return acc;
                else return x;
            });
            Console.WriteLine(acc);
        }

        # region 测试位运算

        [Flags]
        private enum TestFlag
        {
            A = 1,
            B = 1 << 1,
            C = 1 << 2,
            D = 1 << 3,
        }

        /// <summary>
        /// 测试Enum的位运算
        /// </summary>
        /// <remarks>
        ///
        /// 枚举叠加
        /// 0001 | 0010 --> 0011
        ///
        /// 判断是否包含
        /// 0011 & 0001 --> 0001 != 0 包含
        /// 0011 & 0010 --> 0010 != 0 包含
        /// 0011 & 0100 --> 0000 == 0 不包含
        ///
        /// </remarks>
        private static void TestEnumFlag()
        {
            PrintTestFlag(TestFlag.A);
            PrintTestFlag(TestFlag.B);
            //PrintTestFlag(TestFlag.C);
            //PrintTestFlag(TestFlag.D);

            var x = TestFlag.A | TestFlag.B;
            PrintTestFlag(x);
            Console.WriteLine(x & TestFlag.A);
        }

        private static void PrintTestFlag(TestFlag flag)
        {
            Console.Write(flag);
            Console.Write(": ");
            //var bytes = BitConverter.GetBytes((int)flag);
            //if (BitConverter.IsLittleEndian) Array.Reverse(bytes);
            //var bytes = ((int)flag).ToString();
            var bytes = Convert.ToString((int)flag, 2);
            for (int i = 0; i < bytes.Length; i++)
            {
                Console.Write(bytes[i]);
            }

            Console.WriteLine();
        }

        # endregion 测试位运算

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