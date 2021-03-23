using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _Сидоров__КС_20__5._1__18_
{
    public partial class Task1 : Form
    {
        public Task1()
        {
            InitializeComponent();
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar >= '0') && (e.KeyChar <= '9'))
            {
                return;
            }
            if (Char.IsControl(e.KeyChar))
            {
                if (e.KeyChar == (char)Keys.Enter)
                    button1.Focus();
                return;
            }
            e.Handled = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int digit;
            try
            {
                digit = Convert.ToInt16(textBox1.Text);
                if ((digit > 255) || (digit < 0))
                {
                    label1.Location = new Point(12, 123);
                    label1.Text = "Введеное число не подходит по формату";
                    DialogResult result = MessageBox.Show(
                        "Введеное число не подходит по формату!",
                        "Ошибка",
                        MessageBoxButtons.AbortRetryIgnore,
                        MessageBoxIcon.Warning,
                        MessageBoxDefaultButton.Button1,
                        MessageBoxOptions.DefaultDesktopOnly);
                    if (result == DialogResult.Abort)
                    {
                        Application.Exit();
                    }
                    if (result == DialogResult.Ignore)
                    {
                        Application.Exit();
                    }
                }
                else
                {
                    label1.Location = new Point(112, 123);
                    label1.Text = digit.ToString();
                }
            }
            catch
            {
                textBox1.Focus();
            }    
        }
    }
}
