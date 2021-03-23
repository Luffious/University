using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace _Сидоров__КС_20__7__16_
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            var rand = new Random();
            int i, j;
            int n = rand.Next(1, 4);
            int m = rand.Next(1, 4);
            for (i = 0; i < n; i++)
            {
                listBox1.Items.Add(rand.Next(-100, 100).ToString());
            }
            for (j = 0; j < m; j++)
            {
                listBox2.Items.Add(rand.Next(-100, 100).ToString());
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int i = listBox2.SelectedIndex;
            object a = listBox2.SelectedItem;
            if (i == -1) {
                MessageBox.Show("Для перемещения нужно выбрать элемент");
            }
            else
            {
                listBox2.Items.RemoveAt(i);
                listBox1.Items.Add(a);
                if (listBox1.Items.Count > 0)
                {
                    button2.Show();
                }
            }
            if (listBox2.Items.Count == 0)
            {
                button1.Hide();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int i = listBox1.SelectedIndex;
            object a = listBox1.SelectedItem;
            if (i == -1)
            {
                MessageBox.Show("Для перемещения нужно выбрать элемент");
            }
            else
            {
                listBox1.Items.RemoveAt(i);
                listBox2.Items.Add(a);
                if (listBox2.Items.Count > 0)
                {
                    button1.Show();
                }
            }
            if (listBox1.Items.Count == 0)
            {
                button2.Hide();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int i;
            string path = @"E:\Microsoft Visual Studio\source\repos\C#\[Сидоров][КС-20][7][16]\";
            StreamWriter output = new StreamWriter($"{path}output.txt", false);
            object[] a = new object[listBox1.Items.Count];
            object[] b = new object[listBox2.Items.Count];
            listBox1.Items.CopyTo(a, 0);
            listBox2.Items.CopyTo(b, 0);
            output.Write("Элементы первого ListBox: ");
            for (i = 0; i < listBox1.Items.Count; i++)
            {
                output.Write(a[i].ToString() + ' ');
            }
            output.Write("\nЭлементы второго ListBox: ");
            for (i = 0; i < listBox2.Items.Count; i++)
            {
                output.Write(b[i].ToString() + ' ');
            }
            output.Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
