using System.Collections.Generic;

namespace cSharpSolution.GamedychyInterview
{
    public class QuickSort
    {
        public void Sort(List<int> nums)
        {
            quickSort(nums, 0, nums.Count - 1);
        }

        private void quickSort(List<int> nums, int l, int r)
        {
            if (l >= r)
            {
                return;
            }

            // 选一个数字
            // 比数字大的，移动到右边
            // 比数字小的，移动到左边
            // 递归的调用左右
            int pivot = nums[r];

            int pos = l;
            while (pos < r && nums[pos] <= pivot)
            {
                pos++;
            }

            for (int i = pos; i < r; i++)
            {
                if (nums[i] < pivot)
                {
                    swapList(nums, i, pos);
                    pos++;
                }
            }
            swapList(nums, pos, r);

            quickSort(nums, l, pos - 1);
            quickSort(nums, pos + 1, r);
        }

        private void swapList(List<int> nums, int indexA, int indexB)
        {
            int temp = nums[indexA];
            nums[indexA] = nums[indexB];
            nums[indexB] = temp;
        }
    }
}