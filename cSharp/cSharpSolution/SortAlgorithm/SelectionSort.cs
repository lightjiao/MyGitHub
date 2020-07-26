using System.Collections.Generic;

namespace cSharpSolution.SortAlgorithm
{
    public class SelectionSort
    {
        public static void Sort(List<int> list)
        {
            int length = list.Count;
            for (int i = 0; i < length; i++)
            {
                int minIndex = i;
                for (int j = i; j < length; j++)
                {
                    if (list[j] < list[minIndex])
                    {
                        minIndex = j;
                    }
                }

                // swap min and list[i]
                int temp = list[minIndex];
                list[minIndex] = list[i];
                list[i] = temp;
            }
        }
    }
}