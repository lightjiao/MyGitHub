using System;
using System.Net.Http;
using System.Threading.Tasks;

namespace cSharpSolution
{
    internal class Program
    {
        private static readonly HttpClient s_httpClient = new HttpClient();

        private static void Main(string[] args)
        {
            s_httpClient.GetStringAsync("http://www.baidu.com").ContinueWith(
                (downloadTask) =>
                {
                    Console.WriteLine(downloadTask.Result);
                }, TaskScheduler.FromCurrentSynchronizationContext());
        }

        private static async void Main2(string[] args)
        {
            // 用async/await代替上面的实现
            string text = await s_httpClient.GetStringAsync("http://www.baidu.com");
            Console.WriteLine(text);
        }
    }
}