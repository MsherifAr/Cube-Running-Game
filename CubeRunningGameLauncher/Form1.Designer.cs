
namespace CubeRunningGameLauncher
{
    partial class Form1
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.FullScreenCheckBox = new System.Windows.Forms.CheckBox();
            this.VsyncCheckBox = new System.Windows.Forms.CheckBox();
            this.LevelSelector = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.QuitButton = new System.Windows.Forms.Button();
            this.PlayButton = new System.Windows.Forms.Button();
            this.softwareToggle = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // comboBox1
            // 
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "Full HD (1920x1080)",
            "HD (1280x720)",
            "Standard (1366x768)",
            "High Def (1440x900)",
            "QHD / 2K (2560x1440)",
            "UHD / 4K (3840x2160)",
            "Standard (1024x768)",
            "Vintage (800x600)",
            "Legacy (640x480)"});
            this.comboBox1.Location = new System.Drawing.Point(12, 281);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(196, 21);
            this.comboBox1.TabIndex = 0;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // pictureBox1
            // 
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(12, 25);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(428, 237);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(101, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Cube Runner Game";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 265);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(90, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Graphics Settings";
            // 
            // FullScreenCheckBox
            // 
            this.FullScreenCheckBox.AutoSize = true;
            this.FullScreenCheckBox.Location = new System.Drawing.Point(12, 331);
            this.FullScreenCheckBox.Name = "FullScreenCheckBox";
            this.FullScreenCheckBox.Size = new System.Drawing.Size(79, 17);
            this.FullScreenCheckBox.TabIndex = 4;
            this.FullScreenCheckBox.Text = "Full Screen";
            this.FullScreenCheckBox.UseVisualStyleBackColor = true;
            this.FullScreenCheckBox.CheckedChanged += new System.EventHandler(this.FullScreenCheckBox_CheckedChanged);
            // 
            // VsyncCheckBox
            // 
            this.VsyncCheckBox.AutoSize = true;
            this.VsyncCheckBox.Location = new System.Drawing.Point(12, 354);
            this.VsyncCheckBox.Name = "VsyncCheckBox";
            this.VsyncCheckBox.Size = new System.Drawing.Size(55, 17);
            this.VsyncCheckBox.TabIndex = 5;
            this.VsyncCheckBox.Text = "Vsync";
            this.VsyncCheckBox.UseVisualStyleBackColor = true;
            this.VsyncCheckBox.CheckedChanged += new System.EventHandler(this.VsyncCheckBox_CheckedChanged);
            // 
            // LevelSelector
            // 
            this.LevelSelector.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.LevelSelector.FormattingEnabled = true;
            this.LevelSelector.Location = new System.Drawing.Point(272, 281);
            this.LevelSelector.Name = "LevelSelector";
            this.LevelSelector.Size = new System.Drawing.Size(168, 21);
            this.LevelSelector.TabIndex = 6;
            this.LevelSelector.SelectedIndexChanged += new System.EventHandler(this.LevelSelector_SelectedIndexChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(269, 265);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(73, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Level selector";
            // 
            // QuitButton
            // 
            this.QuitButton.Location = new System.Drawing.Point(272, 374);
            this.QuitButton.Name = "QuitButton";
            this.QuitButton.Size = new System.Drawing.Size(75, 23);
            this.QuitButton.TabIndex = 8;
            this.QuitButton.Text = "Quit";
            this.QuitButton.UseVisualStyleBackColor = true;
            this.QuitButton.Click += new System.EventHandler(this.QuitButton_Click);
            // 
            // PlayButton
            // 
            this.PlayButton.Location = new System.Drawing.Point(366, 374);
            this.PlayButton.Name = "PlayButton";
            this.PlayButton.Size = new System.Drawing.Size(75, 23);
            this.PlayButton.TabIndex = 9;
            this.PlayButton.Text = "Play";
            this.PlayButton.UseVisualStyleBackColor = true;
            this.PlayButton.Click += new System.EventHandler(this.PlayButton_Click);
            // 
            // softwareToggle
            // 
            this.softwareToggle.AutoSize = true;
            this.softwareToggle.Location = new System.Drawing.Point(12, 308);
            this.softwareToggle.Name = "softwareToggle";
            this.softwareToggle.Size = new System.Drawing.Size(234, 17);
            this.softwareToggle.TabIndex = 10;
            this.softwareToggle.Text = "CPU Rendering (Slower, better compatibility)";
            this.softwareToggle.UseVisualStyleBackColor = true;
            this.softwareToggle.CheckedChanged += new System.EventHandler(this.softwareToggle_CheckedChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(453, 409);
            this.Controls.Add(this.softwareToggle);
            this.Controls.Add(this.PlayButton);
            this.Controls.Add(this.QuitButton);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.LevelSelector);
            this.Controls.Add(this.VsyncCheckBox);
            this.Controls.Add(this.FullScreenCheckBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.comboBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Cube Runner Game Launcher";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox FullScreenCheckBox;
        private System.Windows.Forms.CheckBox VsyncCheckBox;
        private System.Windows.Forms.ComboBox LevelSelector;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button QuitButton;
        private System.Windows.Forms.Button PlayButton;
        private System.Windows.Forms.CheckBox softwareToggle;
    }
}

