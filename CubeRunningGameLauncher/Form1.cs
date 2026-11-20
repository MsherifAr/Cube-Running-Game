using System;
using System.Diagnostics;
using System.Windows.Forms;
using System.IO;
using Newtonsoft.Json.Linq;

namespace CubeRunningGameLauncher
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            // Loading the Json File
            try
            {
                string filePath = "settings.conf";
                string jsonString = File.ReadAllText(filePath);
                var options = JObject.Parse(jsonString);

                ConfigurationData = new User
                {
                    ScreenWidth = (int)options["ScreenWidth"],
                    ScreenHeight = (int)options["ScreenHeight"],
                    fullscreen = (bool)options["fullscreen"],
                    level = (int)options["level"],
                    maxLevel = (int)options["maxLevel"],
                    vsync = (bool)options["vsync"],
                    software = (bool)options["software"]
                };
            
            }
            catch (Exception ex)
            {
                ConfigurationData = new User
                {
                    ScreenWidth = 640,
                    ScreenHeight = 480,
                    fullscreen = false,
                    level = 1,
                    maxLevel = 1,
                    vsync = false,
                    software = false
                };
            }
            // Applying the data to our local Variables.
            ScreenWidth = ConfigurationData.ScreenWidth;
            ScreenHeight = ConfigurationData.ScreenHeight;
            fullscreen = ConfigurationData.fullscreen;
            level = ConfigurationData.level;
            maxLevel = ConfigurationData.maxLevel;
            vsync = ConfigurationData.vsync;
            software = ConfigurationData.software;
            
            WriteFile();

            // Applying the configuration to our form

            // Resolution Combo Box
            if (ScreenWidth == 1920 && ScreenHeight == 1080)
                comboBox1.SelectedIndex = 0;
            if (ScreenWidth == 1280 && ScreenHeight == 720)
                comboBox1.SelectedIndex = 1;
            if (ScreenWidth == 1366 && ScreenHeight == 768)
                comboBox1.SelectedIndex = 2;
            if (ScreenWidth == 1440 && ScreenHeight == 900)
                comboBox1.SelectedIndex = 3;
            if (ScreenWidth == 2560 && ScreenHeight == 1440)
                comboBox1.SelectedIndex = 4;
            if (ScreenWidth == 3840 && ScreenHeight == 2160)
                comboBox1.SelectedIndex = 5;
            if (ScreenWidth == 1024 && ScreenHeight == 768)
                comboBox1.SelectedIndex = 6;
            if (ScreenWidth == 800 && ScreenHeight == 600)
                comboBox1.SelectedIndex = 7;
            if (ScreenWidth == 640 && ScreenHeight == 480)
                comboBox1.SelectedIndex = 8;

            // Toggle boxes
            FullScreenCheckBox.Checked = fullscreen;
            VsyncCheckBox.Checked = vsync;
            softwareToggle.Checked = software;

            // Level selector

            for (int i = 1; i <= maxLevel; i++)
            {
                string text = "Level " + i.ToString();
                LevelSelector.Items.Add(text);
            }
            if(level > maxLevel)
            {
                level = maxLevel;
                ConfigurationData.level = maxLevel;
                WriteFile();
            }
            LevelSelector.SelectedIndex = level - 1;
        }

        User ConfigurationData;
        int ScreenWidth = 1280;
        int ScreenHeight = 720;
        bool fullscreen = false;
        int level = 1;
        int maxLevel = 1;
        bool vsync = false;
        bool software = false;

        void WriteFile()
        {
            string filePath = "settings.conf";
            string empty = "{}";
            JObject data = JObject.Parse(empty);
            /*var options = new JsonSerializerOptions
            {
                PropertyNameCaseInsensitive = true
            };
            string jsonString = JsonSerializer.Serialize(ConfigurationData, options);
            File.WriteAllText(filePath, jsonString);
            */
            data["ScreenWidth"] = ConfigurationData.ScreenWidth;
            data["ScreenHeight"] = ConfigurationData.ScreenHeight;
            data["level"] = ConfigurationData.level;
            data["maxLevel"] = ConfigurationData.maxLevel;
            data["fullscreen"] = ConfigurationData.fullscreen;
            data["vsync"] = ConfigurationData.vsync;
            data["software"] = ConfigurationData.software;

            File.WriteAllText(filePath, data.ToString());
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            int[,] Supportedwidths = {
                {1920,1080} ,
                {1280, 720} ,
                {1366, 768} ,
                {1440, 900} ,
                {2560, 1440} ,
                {3840, 2160} ,
                {1024, 768} ,
                {800, 600} ,
                {640, 480}
            };
            //Full HD (1920x1080)
            //HD(1280x720)
            //Standard(1366x768)
            //High Def(1440x900)
            //QHD / 2K(2560x1440)
            //UHD / 4K(3840x2160)
            //Standard(1024x768)
            //Vintage(800x600)
            //Legacy(640x480)

            ScreenWidth = Supportedwidths[comboBox1.SelectedIndex, 0];
            ScreenHeight = Supportedwidths[comboBox1.SelectedIndex, 1];
            ConfigurationData.ScreenWidth = ScreenWidth;
            ConfigurationData.ScreenHeight = ScreenHeight;
            WriteFile();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void FullScreenCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            fullscreen = FullScreenCheckBox.Checked;
            ConfigurationData.fullscreen = fullscreen;
            WriteFile();
        }

        private void VsyncCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            vsync = VsyncCheckBox.Checked;
            ConfigurationData.vsync = vsync;
            WriteFile();
        }

        private void LevelSelector_SelectedIndexChanged(object sender, EventArgs e)
        {
            level = LevelSelector.SelectedIndex + 1;
            ConfigurationData.level = level;
            WriteFile();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void QuitButton_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void PlayButton_Click(object sender, EventArgs e)
        {
            try
            {
                string binDirectory = "";
                if (software)
                {
                    binDirectory = "Software/engine.bin";
                }
                else
                {
                    binDirectory = "Hardware/engine.bin";
                }

                ProcessStartInfo startInfo = new ProcessStartInfo
                {
                    FileName = @binDirectory,
                    UseShellExecute = false
                };
                Process.Start(startInfo);
                Application.Exit();

            }
            catch (Exception ex)
            {
                // Prevents the form from closing if the binary fails to launch
                MessageBox.Show($"Failed to launch application: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void softwareToggle_CheckedChanged(object sender, EventArgs e)
        {
            software = softwareToggle.Checked;
            ConfigurationData.software = software;
            WriteFile();
        }
    }

    public class User
    {
        public int ScreenHeight { get; set; }
        public int ScreenWidth { get; set; }
        public bool fullscreen { get; set; }
        public bool vsync { get; set; }
        public int level { get; set; }
        public int maxLevel { get; set; }
        public bool software { get; set; }
    }

}
