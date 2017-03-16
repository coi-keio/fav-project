using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using FavLibrary;

namespace FavLibraryApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            FavLibrary.FavLibrary a = new FavLibrary.FavLibrary();

            ColorBase cb = new ColorBase();
            cb.colorMode = ColorMode.None;
        }
    }
}
