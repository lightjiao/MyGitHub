using System.Collections.Generic;

namespace cSharpSolution.SortAlgorithm
{
    public class QuickSort
    {
        public static void Sort(List<int> list)
        {
            quickSort(list, 0, list.Count - 1);
        }

        private static void quickSort(List<int> list, int l, int r)
        {
            if (l >= r) return;

            int pivot = list[l];

            int pos = l;
            while (list[pos] <= pivot && pos < r)
            {
                pos++;
            }

            for (int i = pos; i < r; i++)
            {
                if (list[i] < pivot)
                {
                    swap(list, i, pos);
                    pos++;
                }
            }
            swap(list, pos, l);

            quickSort(list, l, pos - 1);
            quickSort(list, pos + 1, r);
        }

        private static void swap(List<int> list, int a, int b)
        {
            int temp = list[a];
            list[a] = list[b];
            list[b] = temp;
        }
    }
}