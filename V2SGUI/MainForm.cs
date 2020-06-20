using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace V2SGUI
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void fileChooseButton_Click(object sender, EventArgs e)
        {
            openFileDialog1.Title = "Choose .vox file";
            openFileDialog1.Filter = "Vox files (*.vox)|*.vox|All files (*.*)|*.*";
            openFileDialog1.RestoreDirectory = true;

            DialogResult result = openFileDialog1.ShowDialog(); // Show the dialog.
            if (result == DialogResult.OK) // Test result.
            {
                textBox1.Text = openFileDialog1.FileName;
            }
        }

        private void outputChooseButton_Click(object sender, EventArgs e)
        {
            folderBrowserDialog1.Description = "Choose output folder";
            DialogResult result = folderBrowserDialog1.ShowDialog(); // Show the dialog.
            if (result == DialogResult.OK) // Test result.
            {
                textBox2.Text = folderBrowserDialog1.SelectedPath;
            }
        }

        private void runButton_Click(object sender, EventArgs e)
        {
            Process proc = new Process();

            proc.StartInfo.FileName = ".\\V2S.exe";
            proc.StartInfo.CreateNoWindow = false;
            proc.StartInfo.Arguments = textBox1.Text + ' ' + textBox2.Text;
            proc.Start();
        }
    }
}
