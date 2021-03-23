using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace __Сидоров__КС_20__3__16_
{
    class Program
    {
        static void Main(string[] args)
        {
            var rand = new Random();
            const int K = 11;
            int i;
            double step;
            var x = new List<double>(K);
            var F = new List<double>();
            for (i = 0, step = -0.5; i < K; i++, step += 0.5)
            {   
                x.Add(step);
            }
            Console.WriteLine("16 Вариант");
            for (i = 0; i < K; i++)
            {   
                if (x[i] > 0)
                {
                    double a = Math.Log(x[i], 3);
                    double b = Math.Sinh(-1 * Math.Pow(4, x[i]));
                    if ((1 + (1 / Math.Pow(x[i], 3))) != 0)
                    {
                        double c = Math.Cos((Math.Abs(-1 * x[i])) / (1 + (1 / Math.Pow(x[i], 3))));
                        double d = a + b + c;
                        F.Add(d);
                        Console.WriteLine("F(" + x[i] + ") = F1(" + x[i] + ") + F2(" + x[i] + ") + F3(" + x[i] + ") = " + d);
                    }
                    else
                    {
                        Console.WriteLine("F(" + x[i] + ") не входит в область определения F3(" + x[i] + ")");
                        //F.Add(' ');
                        continue;
                    }
                }
                else
                {
                    Console.WriteLine("F(" + x[i] + ") не входит в область определения F1(" + x[i] + ")");
                    //F.Add(' ');
                    continue;
                }
            }
        }
    }
}
