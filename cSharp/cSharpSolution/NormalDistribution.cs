using System;
using System.Linq;

public class NormalDistribution
{
    private static Random random = new Random();

    /// <summary>
    /// 理论上这个函数的返回值范围是 正无穷到负无穷，但
    /// 约99.7%的数据位于均值的三个标准差范围内 ( 即 mu ± 3sigma )。
    /// </summary>
    /// <param name="mu"></param>
    /// <param name="sigma"></param>
    /// <returns></returns>
    public static double NextGaussian(double mu = 0, double sigma = 1)
    {
        // Generate two uniform random variables
        double u1 = random.NextDouble(); // Uniform(0,1] random doubles
        double u2 = random.NextDouble();

        // Use Box-Muller transform to generate two independent standard normally distributed normal variables
        // See https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
        double R = Math.Sqrt(-2.0 * Math.Log(u1));
        double theta = 2.0 * Math.PI * u2;
        double z = R * Math.Cos(theta); // Random normal(0,1)

        // Scale and shift to get desired mean and standard deviation
        return z * sigma + mu;
    }

    /// <summary>
    /// clamp01, include 0 and 1
    /// </summary>
    /// <returns></returns>
    public static double NextGaussian01()
    {
        return Math.Clamp((NextGaussian() + 4) / 8, 0, 1);
    }

    public static void Test()
    {
        var maxNum = 100;
        var list = Enumerable.Repeat(0, maxNum).ToList();

        for (int i = 0; i < 1000000; i++)
        {
            //var normal = NextGaussian();
            //var key = (int)((normal + 4) * 10);
            //key = Math.Clamp(key, 0, maxNum);

            var normal = NextGaussian01();
            var key = (int)(normal * maxNum);

            if (key >= maxNum) continue;
            list[key]++;
        }

        foreach (var item in list)
        {
            for (int i = 0; i < item / 200; i++)
            {
                //if (i % 2 == 0)
                {
                    Console.Write("*");
                }
            }
            Console.WriteLine();
        }
    }
}