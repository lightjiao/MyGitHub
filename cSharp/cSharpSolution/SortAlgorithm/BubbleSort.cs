using System.Collections.Generic;

namespace cSharpSolution.SortAlgorithm
{
    public class BubbleSort
    {
        public static void Sort(List<int> list)
        {
            int length = list.Count;
            for (int i = length; i >= 0; i--)
            {
                for (int j = 0; j < i; j++)
                {
                    if (j < length - 1 && list[j] > list[j + 1])
                    {
                        var temp = list[j];
                        list[j] = list[j + 1];
                        list[j + 1] = temp;
                    }
                }
            }
        }
    }
}