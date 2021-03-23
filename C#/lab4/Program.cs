using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace __Сидоров__КС_20__4__19_
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("19 Вариант");
            int x = 0;
            string a = @"C:\Users\segas\Desktop\important.txt";
            string b = @"E:\AIDA64 Extreme\aida64.exe";
            string c = @"D:\DOOM\DOOM Eternal Deluxe Edition\DOOMEternalx64vk.exe";
            string d = @"C:\Users\segas\Desktop\ИНФА\МВМ\Lab3_Appr.txt";
            string e = @"D:\Music\Dr.Dre - Mortified.mp3";
            string f = @"C:\Users\segas\Desktop\finalPath";
            DirectoryInfo finalPath = new DirectoryInfo(f);
            var paths = new List<FileInfo>(5);
            var txt = new List<FileInfo>();
            var exe = new List<FileInfo>();
            var mp3 = new List<FileInfo>();
            FileInfo path1 = new FileInfo(a);
            FileInfo path2 = new FileInfo(b);
            FileInfo path3 = new FileInfo(c);
            FileInfo path4 = new FileInfo(d);
            FileInfo path5 = new FileInfo(e);
            paths.Add(path1);
            paths.Add(path2);
            paths.Add(path3);
            paths.Add(path4);
            paths.Add(path5);
            foreach (FileInfo i in paths)
            {
                if ((i.Extension == ".txt") & (x == 0))
                {
                    txt.Add(i);
                    finalPath.CreateSubdirectory(i.Extension);
                    x++;
                    i.CopyTo(finalPath + "\\" + i.Extension + "\\" + i.Name, true);
                }
                else if ((i.Extension == ".txt") & (x != 0))
                {
                    txt.Add(i);
                    i.CopyTo(finalPath + "\\" + i.Extension + "\\" + i.Name, true);
                }
                else if ((i.Extension == ".exe") & (x == 0))
                {
                    exe.Add(i);
                    finalPath.CreateSubdirectory(i.Extension);
                    x++;
                    i.CopyTo(finalPath + "\\" + i.Extension + "\\" + i.Name, true);
                }
                else if ((i.Extension == ".exe") & (x != 0))
                {
                    exe.Add(i);
                    i.CopyTo(finalPath + "\\" + i.Extension + "\\" + i.Name, true);
                }
                else if ((i.Extension == ".mp3") & (x == 0))
                {
                    mp3.Add(i);
                    finalPath.CreateSubdirectory(i.Extension);
                    x++;
                    i.CopyTo(finalPath + "\\" + i.Extension + "\\" + i.Name, true);
                }
                else if ((i.Extension == ".mp3") & (x != 0))
                {
                    mp3.Add(i);
                    i.CopyTo(finalPath + "\\" + i.Extension + "\\" + i.Name, true);
                }
                x = 0;
            }
        }
    }
}
