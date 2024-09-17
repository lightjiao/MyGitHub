using System;
using System.Linq.Expressions;

namespace cSharpSolution
{
    public static class LearnExpressTree
    {
        public static void Run()
        {
            Expression<Func<int, bool>> exp = i => i > 0;
            Console.WriteLine(exp.Body);
            Console.WriteLine(exp.Body.GetType());
        }

        public static bool Greater(int i) // 不能直接被表达树引用，表达树只能用lambda
        {
            return i > 0;
        }
    }
}
