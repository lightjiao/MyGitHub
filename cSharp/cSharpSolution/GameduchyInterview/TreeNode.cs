using System;

namespace cSharpSolution.GamedychyInterview
{
    public class TreeNode
    {
        public int value;
        public TreeNode[] childList;

        public void Print(TreeNode head)
        {
            // root
            // left
            // right
            Console.WriteLine(head.value);

            foreach (TreeNode child in head.childList)
            {
                Print(child);
            }
        }

        public override string ToString()
        {
            return value.ToString();
        }
    }
}