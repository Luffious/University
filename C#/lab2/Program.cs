using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace __Сидоров__КС_20__2__22_
{
    class Program
    {
        static void Main(string[] args)
        {
            const double A0 = 0.68235;
            const double A1 = 1.20811e-2;
            const double A2 = 1.2379e-3;
            const double A3 = 3.7938e-6;
            const int N = 12;
            const int M = 4;
            double[,] a = new double[N, M]
            {
                { 0, 150, 160, 170 },
                { 86.68, 0, 0, 0 },
                { 88.28, 0, 0, 0 },
                { 89.58, 0, 0, 0 },
                { 90.63, 0, 0, 0 },
                { 92.97, 0, 0, 0 },
                { 93.82, 0, 0, 0 },
                { 94.38, 0, 0, 0 },
                { 97.48, 0, 0, 0 },
                { 98.66, 0, 0, 0 },
                { 100.93, 0, 0, 0 },
                { 101.60, 0, 0, 0 }
            };
            int i, j;
            for (i = 1; i < N; i++)
            {
                for (j = 1; j < M; j++)
                {
                    a[i, j] = A0 + A1 * a[i, 0] - (A2 - A3 * a[i, 0]) * a[0, j];
                }
            }
            Console.WriteLine("Вариант 2 - 23");
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < M; j++)
                {
                    if (i == 0 && j == 0)
                    {
                        Console.Write("\t");
                    }
                    else 
                    { 
                        Console.Write(Math.Round(a[i, j], 4) + "\t");
                    }
                }
                Console.WriteLine(); 
            }
            Console.ReadKey(true);
        }
    }
}
