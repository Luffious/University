using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using ZedGraph;

namespace _Сидоров__КС_20__9_10__CSharp_
{
    public partial class Form1 : Form
    {
        const double A = -20;
        const double B = 20;
        const int n = 30;
        const double h = (B - A) / n;
        double[] y1 = new double[n + 1];
        double[] y2 = new double[n + 1];
        string inputPath = "input.txt";
        PointPairList function1 = new PointPairList();
        PointPairList function2 = new PointPairList();
        LegendPos Legend = LegendPos.InsideTopLeft;
        string TitleX = "X";
        string TitleY = "Y";
        Color color1 = Color.LightBlue;
        Color color2 = Color.LightGreen;
        Size dataminimize = new Size(414, 163);
        Size datamaximize = new Size(908, 584);
        Point datamax = new Point(12, 12);
        Point datamin = new Point(506, 367);

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            StreamWriter sw = new StreamWriter(inputPath, false, System.Text.Encoding.Default);
            for (int i = 0; i < n + 1; i++)
            {
                double x = A + (h * i);
                y1[i] = Function1(x);
                sw.WriteLine(y1[i].ToString());
            }
            for (int i = 0; i < n + 1; i++)
            {
                double x = A + (h * i);
                y2[i] = Function2(x);
                sw.WriteLine(y2[i].ToString());
            }
            sw.Close();
            dataGridView1.Rows.Clear();
            dataGridView1.Columns.Clear();
            dataGridView1.RowHeadersVisible = false;
            dataGridView1.ColumnHeadersVisible = false;
            dataGridView1.ReadOnly = true;
            dataGridView1.Columns.Add(" ", " ");
            dataGridView1.Columns.Add(" ", " ");
            StreamReader sr = new StreamReader(File.Open(inputPath, FileMode.Open));
            for (int i = 0; i < n + 1; i++)
            {
                string temp = sr.ReadLine();
                bool res = double.TryParse(temp, out double y);
                dataGridView1.Rows.Add();
                if (res)
                {
                    dataGridView1[0, i].Value = A + (h * i);
                    dataGridView1[1, i].Value = double.Parse(temp);
                }
                else if (!res)
                {
                    dataGridView1[0, i].Value = " ";
                    dataGridView1[1, i].Value = " ";
                }
            }
            dataGridView1.Rows.Add("-------------------------", "-------------------------");
            for (int i = 0; i < n + 1; i++)
            {
                string temp = sr.ReadLine();
                bool res = double.TryParse(temp, out double y);
                dataGridView1.Rows.Add();
                if (res)
                {
                    dataGridView1[0, i + n + 2].Value = A + (h * i);
                    dataGridView1[1, i + n + 2].Value = double.Parse(temp);
                }
                else if (!res)
                {
                    dataGridView1[0, i + n + 2].Value = " ";
                    dataGridView1[1, i + n + 2].Value = " ";
                }
            }
            sr.Close();
            for (int i = 0; i < n + 1; i++)
            {
                function1.Add((double)dataGridView1[0, i].Value, (double)dataGridView1[1, i].Value);
            }
            for (int i = n + 3; i < n + n + 3; i++)
            {
                function2.Add((double)dataGridView1[0, i].Value, (double)dataGridView1[1, i].Value);
            }
            textBox1.Text = TitleX;
            textBox2.Text = TitleY;
            radioButton9.Checked = true;
            colorDialog1.FullOpen = true;
            colorDialog2.FullOpen = true;
        }

        static double Function1(double x)
        {
            //y = ((e^(x^2)+(e^(x^2)))/2e^(2(x^2))
            return (Math.Exp(Math.Pow(x, 2)) + Math.Exp(Math.Pow(x, 2))) / (2 * Math.Exp(2 * Math.Pow(x, 2)));
        }

        static double Function2(double x)
        {
            //y = sin(x)*cos(x)
            return Math.Sin(x) * Math.Cos(x);
        }

        private void DrawGraphs(bool number, Color firstLine, Color secondLine, SymbolType symbolType, bool lineShow, LegendPos legendPos)
        {
            GraphPane mainPane = zedGraphControl1.GraphPane;
            if (number)
            {
                if (radioButton1.Checked)
                    DrawGraph1(true, color1, color2, SymbolType.Circle, false, Legend);
                if (radioButton2.Checked)
                    DrawGraph1(true, color1, color2, SymbolType.None, true, Legend);
                if (radioButton3.Checked)
                    DrawGraph1(true, color1, color2, SymbolType.Diamond, true, Legend);
                if (radioButton4.Checked)
                    DrawGraph1(true, color1, color2, SymbolType.Plus, true, Legend);
            }
            if (!number)
            {
                if (radioButton5.Checked)
                    DrawGraph2(false, color1, color2, SymbolType.Circle, false, Legend);
                if (radioButton6.Checked)
                    DrawGraph2(false, color1, color2, SymbolType.None, true, Legend);
                if (radioButton7.Checked)
                    DrawGraph2(false, color1, color2, SymbolType.Diamond, true, Legend);
                if (radioButton8.Checked)
                    DrawGraph2(false, color1, color2, SymbolType.Plus, true, Legend);
            }
            if (legendPos != Legend)
            {
                legendPos = Legend;
            }
            mainPane.Legend.Position = legendPos;
            mainPane.Border.Color = Color.White;
            mainPane.Chart.Border.Color = Color.Red;
            mainPane.Chart.Fill.Type = FillType.Solid;
            mainPane.Chart.Fill.Color = Color.FromArgb(207, 125, 19);
            mainPane.XAxis.Title.Text = TitleX;
            mainPane.YAxis.Title.Text = TitleY;
            mainPane.Title.Text = "Лабораторная работа 9-10";
            zedGraphControl1.AxisChange();
            zedGraphControl1.Invalidate();
        }

        private void DrawGraph1(bool number, Color firstLine, Color secondLine, SymbolType symbolType, bool lineShow, LegendPos legendPos)
        {
            GraphPane mainPane = zedGraphControl1.GraphPane;
            LineItem firstFunction; 
            firstFunction = mainPane.AddCurve("y = (e^(x^2))+(e^(x^2))/2e^(2(x^2))", function1, firstLine, symbolType);
            if (!lineShow)
            {
                firstFunction.Line.IsVisible = false;
            }
        }

        private void DrawGraph2(bool number, Color firstLine, Color secondLine, SymbolType symbolType, bool lineShow, LegendPos legendPos)
        {
            GraphPane mainPane = zedGraphControl1.GraphPane;
            LineItem secondFunction;
            secondFunction = mainPane.AddCurve("y = sin(x)*cos(x)", function2, secondLine, symbolType);
            if (!lineShow)
            {
                secondFunction.Line.IsVisible = false;
            }
        }

        private void RadiobuttonsCheck()
        {
            if (zedGraphControl1.GraphPane.CurveList.Capacity > 2)
            {
                zedGraphControl1.GraphPane.CurveList.Clear();
            }
            if (radioButton1.Checked)
                DrawGraphs(true, color1, color2, SymbolType.Circle, false, Legend);
            if (radioButton2.Checked)
                DrawGraphs(true, color1, color2, SymbolType.None, true, Legend);
            if (radioButton3.Checked)
                DrawGraphs(true, color1, color2, SymbolType.Diamond, true, Legend);
            if (radioButton4.Checked)
                DrawGraphs(true, color1, color2, SymbolType.Plus, true, Legend);
            if (radioButton5.Checked)
                DrawGraphs(false, color1, color2, SymbolType.Circle, false, Legend);
            if (radioButton6.Checked)
                DrawGraphs(false, color1, color2, SymbolType.None, true, Legend);
            if (radioButton7.Checked)
                DrawGraphs(false, color1, color2, SymbolType.Diamond, true, Legend);
            if (radioButton8.Checked)
                DrawGraphs(false, color1, color2, SymbolType.Plus, true, Legend);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (colorDialog1.ShowDialog() == DialogResult.Cancel)
                return;
            color1 = colorDialog1.Color;
            RadiobuttonsCheck();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (colorDialog2.ShowDialog() == DialogResult.Cancel)
                return;
            color2 = colorDialog1.Color;
            RadiobuttonsCheck();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (zedGraphControl1.Visible)
            {
                zedGraphControl1.Visible = false;
                groupBox1.Visible = false;
                groupBox2.Visible = false;
                groupBox6.Visible = false;
                dataGridView1.Size = datamaximize;
                dataGridView1.Location = datamax;
                button3.Text = "Уменьшить таблицу точек функций";
            }
            else
            {
                zedGraphControl1.Visible = true;
                groupBox1.Visible = true;
                groupBox2.Visible = true;
                groupBox6.Visible = true;
                dataGridView1.Size = dataminimize;
                dataGridView1.Location = datamin;
                button3.Text = "Увеличить таблицу точек функций";
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            TitleX = textBox1.Text.ToString();
            TitleY = textBox2.Text.ToString();
            RadiobuttonsCheck();
        }

        private void radioButton9_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton9.Checked)
            {
                Legend = LegendPos.InsideTopLeft;
                RadiobuttonsCheck();
            }
        }

        private void radioButton10_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton10.Checked)
            {
                Legend = LegendPos.TopCenter;
                RadiobuttonsCheck();
            }
        }

        private void radioButton11_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton11.Checked)
            {
                Legend = LegendPos.InsideTopRight;
                RadiobuttonsCheck();
            }
        }

        private void radioButton12_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton12.Checked)
            {
                Legend = LegendPos.InsideBotLeft;
                RadiobuttonsCheck();
            }
        }

        private void radioButton13_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton13.Checked)
            {
                Legend = LegendPos.BottomCenter;
                RadiobuttonsCheck();
            }
        }

        private void radioButton14_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton14.Checked)
            {
                Legend = LegendPos.InsideBotRight;
                RadiobuttonsCheck();
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            RadiobuttonsCheck();
        }
    }
}
