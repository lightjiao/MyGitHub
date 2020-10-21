using System.Threading.Tasks;

namespace AsyncSample
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            Task.WaitAll(AsyncSample.DoSomething(1));
        }
    }
}