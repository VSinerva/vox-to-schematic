namespace V2SGUI
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.fileChooseButton = new System.Windows.Forms.Button();
            this.outputChooseButton = new System.Windows.Forms.Button();
            this.runButton = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(12, 12);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(387, 20);
            this.textBox1.TabIndex = 0;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(12, 38);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(387, 20);
            this.textBox2.TabIndex = 1;
            // 
            // fileChooseButton
            // 
            this.fileChooseButton.Location = new System.Drawing.Point(405, 11);
            this.fileChooseButton.Name = "fileChooseButton";
            this.fileChooseButton.Size = new System.Drawing.Size(140, 22);
            this.fileChooseButton.TabIndex = 2;
            this.fileChooseButton.Text = "Choose a .vox file";
            this.fileChooseButton.UseVisualStyleBackColor = true;
            this.fileChooseButton.Click += new System.EventHandler(this.fileChooseButton_Click);
            // 
            // outputChooseButton
            // 
            this.outputChooseButton.Location = new System.Drawing.Point(405, 38);
            this.outputChooseButton.Name = "outputChooseButton";
            this.outputChooseButton.Size = new System.Drawing.Size(140, 22);
            this.outputChooseButton.TabIndex = 3;
            this.outputChooseButton.Text = "Choose an output folder";
            this.outputChooseButton.UseVisualStyleBackColor = true;
            this.outputChooseButton.Click += new System.EventHandler(this.outputChooseButton_Click);
            // 
            // runButton
            // 
            this.runButton.Location = new System.Drawing.Point(12, 64);
            this.runButton.Name = "runButton";
            this.runButton.Size = new System.Drawing.Size(75, 22);
            this.runButton.TabIndex = 4;
            this.runButton.Text = "Convert";
            this.runButton.UseVisualStyleBackColor = true;
            this.runButton.Click += new System.EventHandler(this.runButton_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.runButton);
            this.Controls.Add(this.outputChooseButton);
            this.Controls.Add(this.fileChooseButton);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.Padding = new System.Windows.Forms.Padding(6);
            this.ShowIcon = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "Vox to schematic";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Button fileChooseButton;
        private System.Windows.Forms.Button outputChooseButton;
        private System.Windows.Forms.Button runButton;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
    }
}

