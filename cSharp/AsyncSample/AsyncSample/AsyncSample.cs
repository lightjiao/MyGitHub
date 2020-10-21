using System;
using System.Threading;
using System.Threading.Tasks;

namespace AsyncSample
{
    internal class AsyncSample
    {
        public static async Task DoSomething(int num)
        {
            Console.WriteLine($"DoAsync {num} start");

            await SleepAsync();

            Console.WriteLine($"DoAsync {num} end");
        }

        private static async Task SleepAsync()
        {
            await Task.Run(() => { Thread.Sleep(2000); });
        }
    }
}