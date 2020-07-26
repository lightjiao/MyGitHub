using System;
using System.Collections.Generic;

namespace cSharpSolution
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            var list = new List<int> { 1, 1, 3, 3, 2, 2, 5, 5, 4, 4 };
            SortAlgorithm.QuickSort.Sort(list);
            var expect = new List<int> { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 };

            bool equal = true;
            for (int i = 0; i < list.Count; i++)
            {
                if (list[i] != expect[i])
                {
                    equal = false;
                    break;
                }
            }

            Console.WriteLine(equal);
            if (equal == false)
            {
                foreach (var item in list)
                {
                    Console.WriteLine(item);
                }
            }
        }
    }
}