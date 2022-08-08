using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;

namespace cSharpSolution
{
    internal partial class Program
    {
        private static async Task Main(string[] args)
        {
            await foreach (var _ in ProduceAsyncSumSequence(10))
            {

            }
        }

        private static void ConsoleWriteEx(string str = null)
        {
            Console.WriteLine($"(ThreadId: {Thread.CurrentThread.ManagedThreadId}): {str}");
        }

        private static async IAsyncEnumerable<int> ProduceAsyncSumSequence(int count)
        {
            ConsoleWriteEx("ProduceAsyncSumSequence start");

            var sum = 0;
            for (var i = 0; i < count; i++)
            {
                sum += i;
                await Task.Delay(TimeSpan.FromSeconds(1));

                ConsoleWriteEx($"ProduceAsyncSumSequence sum:{sum}");

                yield return sum;
            }
        }
    }
}