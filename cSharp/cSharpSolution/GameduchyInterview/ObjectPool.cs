using System;
using System.Collections.Generic;

namespace cSharpSolution.GamedychyInterview
{
    public class ObjectPool<T> where T : new()
    {
        private class PoolObject
        {
            public T obj;
            public bool isValid = true;
        }

        private int count;
        private List<PoolObject> pool;

        public ObjectPool()
        {
            pool = new List<PoolObject>(3);
            for (int i = 0; i < 3; i++)
            {
                var obj = new T();
                Add(obj);
            }
        }

        public void Print()
        {
            foreach (var item in pool)
            {
                Console.WriteLine(item.obj + ": " + item.isValid);
            }
        }

        // set the object free
        public bool SetFree(T a)
        {
            for (int i = 0; i < pool.Count; i++)
            {
                if (object.ReferenceEquals(a, pool[i].obj))
                {
                    pool[i].isValid = true;
                    return true;
                }
            }

            return false;
        }

        public void Add(T obj)
        {
            var poolObj = new PoolObject();
            poolObj.isValid = true;
            poolObj.obj = obj;
            pool.Add(poolObj);

            count++;
        }

        public T GetOne()
        {
            for (int i = 0; i < count; i++)
            {
                if (pool[i].isValid)
                {
                    pool[i].isValid = false;

                    return pool[i].obj;
                }
            }

            ReSize(count * 2);

            return GetOne();
        }

        public void ReSize(int size)
        {
            if (size > count)
            {
                for (int i = 0; i < size - count; i++)
                {
                    var obj = new T();
                    Add(obj);
                }
            }
            if (size < count)
            {
                pool.RemoveRange(size, count - size);
            }

            count = size;
        }
    }
}