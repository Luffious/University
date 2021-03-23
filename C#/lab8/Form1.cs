using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _Сидоров__КС_20__8__1_
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            int i;
            for (i = 0; i < 20; i++)
            {
                checkedListBox1.Items.Add(i + 1);
                checkedListBox2.Items.Add(i + 1);
            }
            dataGridView1.AllowUserToAddRows = false;
        }

        public void Arr()
        {
            double[,] A = new double[dataGridView1.Rows.Count, dataGridView1.Columns.Count];
            for (int i = 0; i < dataGridView1.Rows.Count; i++)
            {
                for (int j = 0; j < dataGridView1.Columns.Count; j++)
                {
                    A[i, j] = (10 * Math.Pow((-1), i + j)) + i + (j * 0.1);
                    dataGridView1[j, i].Value = A[i, j];
                }
            }
            if (dataGridView1.Rows.Count >= 8 && dataGridView1.Columns.Count >= 19)
            {
                dataGridView1[19, 8].Value = -0.1;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int i, j;
            if (checkedListBox1.SelectedIndex > -1 && checkedListBox2.SelectedIndex > -1)
            {
                double[,] A = new double[checkedListBox1.SelectedIndex + 1, checkedListBox2.SelectedIndex + 1];
                for (j = 0; j < checkedListBox2.SelectedIndex + 1; j++)
                {
                    var column = new DataGridViewColumn();
                    column.HeaderText = (j + 1).ToString();
                    column.Width = 30;
                    column.ReadOnly = true;
                    column.CellTemplate = new DataGridViewTextBoxCell();
                    dataGridView1.Columns.Add(column);
                }
                for (i = 0; i < checkedListBox1.SelectedIndex + 1; i++)
                {
                    var row = new DataGridViewRow();
                    row.ReadOnly = true;
                    dataGridView1.Rows.Add(row);
                }
                for (i = 0; i < dataGridView1.Rows.Count; i++)
                {
                    for (j = 0; j < dataGridView1.Columns.Count; j++)
                    {
                        A[i, j] = (10 * Math.Pow((-1), i + j)) + i + (j * 0.1);
                        dataGridView1[j, i].Value = A[i, j];
                    }
                }
                if (dataGridView1.Rows.Count >= 8 && dataGridView1.Columns.Count >= 19)
                {
                    dataGridView1[19, 8].Value = -0.1;
                }
                groupBox1.Visible = false;
                dataGridView1.Visible = true;
                groupBox2.Visible = true;
            }
            else
            {
                MessageBox.Show("Ошибка, попробуйте выбрать заново");
            }
        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (checkedListBox1.CheckedItems.Count > 1)
            {
                for (int i = 0; i < checkedListBox1.Items.Count; i++)
                    checkedListBox1.SetItemChecked(i, false);
                checkedListBox1.SetItemChecked(checkedListBox1.SelectedIndex, true);
            }
        }

        private void checkedListBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (checkedListBox2.CheckedItems.Count > 1)
            {
                for (int i = 0; i < checkedListBox2.Items.Count; i++)
                    checkedListBox2.SetItemChecked(i, false);
                checkedListBox2.SetItemChecked(checkedListBox2.SelectedIndex, true);
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Arr();
            for (int i = 0; i < checkedListBox3.Items.Count; i++)
                checkedListBox3.SetItemChecked(i, false);
            checkedListBox3.SelectedIndex = -1;
            for (int i = 0; i < checkedListBox4.Items.Count; i++)
                checkedListBox4.SetItemChecked(i, false);
            checkedListBox4.SelectedIndex = -1;
            checkedListBox5.SetItemChecked(0, false);
            checkedListBox5.SelectedIndex = -1;
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if (checkedListBox3.SelectedIndex == 0)
            {
                Arr();
                for (int i = 0; i < dataGridView1.Rows.Count; i++)
                {
                    for (int j = 0; j < dataGridView1.Columns.Count; j++)
                    {
                        if (Int32.TryParse(dataGridView1[j, i].Value.ToString(), out int res) == false)
                        {
                            dataGridView1[j, i].Value = ' ';
                        }
                        if (Int32.TryParse(dataGridView1[j, i].Value.ToString(), out res) == true)
                        {
                            if (checkedListBox4.SelectedIndex == 0)
                            {
                                if (checkedListBox5.SelectedIndex > -1)
                                {
                                    if (Int32.Parse(dataGridView1[j, i].Value.ToString()) < 0)
                                    {
                                        dataGridView1[j, i].Value = ' ';
                                    }
                                }
                                else
                                {
                                    if (Int32.Parse(dataGridView1[j, i].Value.ToString()) <= 0)
                                    {
                                        dataGridView1[j, i].Value = ' ';
                                    }
                                }
                            }
                            else if (checkedListBox4.SelectedIndex == 1)
                            {
                                if (checkedListBox5.SelectedIndex > -1)
                                {
                                    if (Int32.Parse(dataGridView1[j, i].Value.ToString()) > 0)
                                    {
                                        dataGridView1[j, i].Value = ' ';
                                    }
                                }
                                else
                                {
                                    if (Int32.Parse(dataGridView1[j, i].Value.ToString()) >= 0)
                                    {
                                        dataGridView1[j, i].Value = ' ';
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (checkedListBox3.SelectedIndex == 1)
            {
                Arr();
                for (int i = 0; i < dataGridView1.Rows.Count; i++)
                {
                    for (int j = 0; j < dataGridView1.Columns.Count; j++)
                    {
                        string b = dataGridView1[j, i].Value.ToString();
                        if (b.Contains(',') == false)
                        {
                            dataGridView1[j, i].Value = ' ';
                        }
                        if (b.Contains(',') == true)
                        {
                            if (checkedListBox4.SelectedIndex == 0)
                            {
                                if (Double.Parse(dataGridView1[j, i].Value.ToString()) <= 0)
                                {
                                    dataGridView1[j, i].Value = ' ';
                                }
                            }
                            else if (checkedListBox4.SelectedIndex == 1)
                            {
                                if (Double.Parse(dataGridView1[j, i].Value.ToString()) >= 0)
                                {
                                    dataGridView1[j, i].Value = ' ';
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                MessageBox.Show("Ошибка, вы не выбрали ни одного фильтра");
            }
            for (int i = 0; i < checkedListBox3.Items.Count; i++)
                checkedListBox3.SetItemChecked(i, false);
            checkedListBox3.SelectedIndex = -1;
            for (int i = 0; i < checkedListBox4.Items.Count; i++)
                checkedListBox4.SetItemChecked(i, false);
            checkedListBox4.SelectedIndex = -1;
            checkedListBox5.SetItemChecked(0, false);
            checkedListBox5.SelectedIndex = -1;
        }

        private void checkedListBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (checkedListBox3.CheckedItems.Count > 1)
            {
                for (int i = 0; i < checkedListBox3.Items.Count; i++)
                    checkedListBox3.SetItemChecked(i, false);
                checkedListBox3.SetItemChecked(checkedListBox3.SelectedIndex, true);
            }
            if (checkedListBox3.SelectedIndex == 0)
            {
                checkedListBox5.Enabled = true;
            }
            else if (checkedListBox3.SelectedIndex == 1)
            {
                checkedListBox5.Enabled = false;
                checkedListBox5.SetItemChecked(0, false);
                checkedListBox5.SelectedIndex = -1;
            }
        }

        private void checkedListBox4_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (checkedListBox4.CheckedItems.Count > 1)
            {
                for (int i = 0; i < checkedListBox4.Items.Count; i++)
                    checkedListBox4.SetItemChecked(i, false);
                checkedListBox4.SetItemChecked(checkedListBox4.SelectedIndex, true);
            }
        }
    }
}
