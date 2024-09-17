using System;
using System.Net.Http;
using System.Threading.Tasks;

namespace cSharpSolution
{
    public class AsyncSample
    {
        private static HttpClient m_HttpClient = new HttpClient();

        public static async Task Test()
        {
            await GetStringAsyncWithLog("aaa");
        }

        private static async Task PrintWeb(string url)
        {
            Console.WriteLine($"BeginSample: {DateTime.Now}");

            await m_HttpClient.GetStringAsync(url);

            Console.WriteLine($"EndSample: {DateTime.Now}");
        }

        static Task<string> GetStringAsyncWithLog(string url)
        {
            Console.WriteLine($"[{DateTime.UtcNow}] url: {url}");

            return m_HttpClient.GetStringAsync(url);
        }
    }
}
