using System;

namespace cSharpSolution.GamedychyInterview
{
    public class NodeList
    {
        public class Node
        {
            public int value;
            public Node next;

            public Node(int value)
            {
                this.value = value;
            }
        }

        private Node dummy;
        private Node tail;
        private int length;

        public NodeList()
        {
            dummy = new Node(0);
            tail = dummy;
            length = 0;
        }

        public int Length { get => length; }

        public void Print()
        {
            Node n = dummy.next;
            Console.WriteLine("Start print:\n");
            while (n != null)
            {
                Console.WriteLine(n.value);
                n = n.next;
            }
        }

        public void Add(Node node)
        {
            tail.next = node;
            tail = node;

            length++;
        }

        public bool Delete(int index)
        {
            Node deleteOne = dummy.next;
            Node beforeOne = dummy;
            for (int i = 0; i < index; i++)
            {
                if (deleteOne == null) return false;
                beforeOne = beforeOne.next;
                deleteOne = deleteOne.next;
            }

            beforeOne.next = deleteOne.next;

            length--;

            return true;
        }

        public bool Modify(int index, int value)
        {
            Node findOne = dummy.next;
            for (int i = 0; i < index; i++)
            {
                if (findOne == null) return false;
                findOne = findOne.next;
            }
            findOne.value = value;

            return true;
        }
    }
}