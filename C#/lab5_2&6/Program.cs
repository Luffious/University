using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace _Сидоров__КС_20__5._2_6__18_
{
    class Program
    {
        static void Main(string[] args)
        {
            int n;
            string path = @"E:\Microsoft Visual Studio\source\repos\C#\[Сидоров][КС-20][5.2][18]\";
            StreamWriter MyErrors = new StreamWriter($"{path}myErrors.log", false);
            MyErrors.Write("");
            MyErrors.Close();
            Inputs();
            Console.ReadLine();
        }
        static void G(double[] x, double[] y, int m)
        {
            string path = @"E:\Microsoft Visual Studio\source\repos\C#\[Сидоров][КС-20][5.2][18]\";
            int n = y.Length;
            int i, j, count = 0;
            double[,] G = new double[n + 1, n + 1];
            string temp;
            StreamWriter Gdat = new StreamWriter($"{path}" + "G" + m + ".dat", false, Encoding.Default);
            StreamWriter MyErrors = new StreamWriter($"{path}myErrors.log", true, Encoding.Default);
            Gdat.WriteLine("Рассчитываемая функция: y * 10^(ln(x)+1)\nКоличество пар точек (x, y): " + n);
            MyErrors.WriteLine("G" + m + ".dat");
            for (i = 0; i < n + 1; i++)
            {
                for (j = 0; j < n + 1; j++)
                {
                    if ((i == 0) && (j == 0))
                    {
                        Gdat.Write("       y" + "\\" + "x" + "       \t\t");
                    }
                    else if ((i == 0) && (j != 0) && (j < x.Length + 1))
                    {
                        Gdat.Write(x[j - 1] + " \t\t");
                    }
                    else if ((i != 0) && (j == 0) && (i < y.Length + 1))
                    {
                        Gdat.Write(y[i - 1] + " \t\t");
                    }
                    else if ((j < x.Length + 1) && (i < y.Length + 1))
                    {
                        G[i, j] = y[i - 1] * Math.Pow(10, Math.Log(x[j - 1]) + 1);
                        if (Double.IsNaN(G[i, j]) == true)
                        {
                            count++;
                            MyErrors.WriteLine("ERROR! Значение под натуральным логарифмом не может быть меньше 0");
                            Gdat.Write("       NaN       " + "\t\t");
                        }
                        else
                        {
                            Gdat.Write(G[i, j] + " \t\t");
                        }
                    }
                }
                Gdat.WriteLine();
            }
            MyErrors.WriteLine("Количество неопределённых значений функции: " + count);
            Gdat.Close();
            StreamReader Gdatt = new StreamReader($"{path}" + "G" + m + ".dat", Encoding.Default);
            temp = Gdatt.ReadToEnd();
            Gdatt.Close();
            StreamWriter Grez = new StreamWriter($"{path}G" + m + ".rez", false, Encoding.Default);
            Grez.Write(temp);
            Grez.WriteLine("Исходные данные (x, y):");
            for (i = 0; i < n; i++)
            {
                Grez.WriteLine(x[i] + "\t" + y[i]);
            }
            Grez.Close();
            MyErrors.Close();
            Console.WriteLine();
        }
        static void Inputs()
        {
            DateTime begin = DateTime.Now;
            string path = @"E:\Microsoft Visual Studio\source\repos\C#\[Сидоров][КС-20][5.2][18]\";
            StreamWriter MyProgram = new StreamWriter($"{path}myProgram.log", false, Encoding.Default);
            const double A = 100;
            const double B = -100;
            var rand = new Random();
            int i, j;
            string temp;
            retry1:
            Console.WriteLine("Введите количество наборов (x, y):");
            temp = Console.ReadLine();
            if (Int32.TryParse(temp, out int m))
            {
                m = Convert.ToInt32(temp);
                Console.WriteLine("Количество наборов (x, y): " + m);
                for (i = 0; i < m; i++)
                {
                    retry2:
                    Console.WriteLine("Введите количество элементов в наборе:");
                    temp = Console.ReadLine();
                    if (Int32.TryParse(temp, out int n))
                    {
                        n = Convert.ToInt32(temp);
                        Console.WriteLine("Количество элементов в наборе: " + n);
                        double[] y = new double[n];
                        double[] x = new double[n];
                        for (j = 0; j < n; j++)
                        {
                            x[j] = rand.NextDouble() * (A - B) + B;
                            y[j] = rand.NextDouble() * (A - B) + B;
                        }
                        G(x, y, i + 1);
                    }
                    else
                    {
                        Console.WriteLine("Некорректное значение!!!");
                        goto retry2;
                    }
                }
            }
            else
            {
                Console.WriteLine("Некорректное значение!!!");
                goto retry1;
            }
            MyProgram.WriteLine("Лабораторная работа 5 часть 2\n18 вариант\nВремя начала работы программы: " + begin);
            MyProgram.WriteLine("Рассчитываемая функция: y * 10^(ln(x)+1)");
            MyProgram.WriteLine("Названия рассчётных файлов: ");
            for (i = 1; i < m + 1; i++)
            {
                MyProgram.Write("G" + i + ".dat ");
            }
            MyProgram.Close();
        }
    }
}
