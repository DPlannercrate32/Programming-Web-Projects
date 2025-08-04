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

namespace WPCreater
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent(); //This function is needed to pretty much setup up the windows form application.
        }

/*Note to viewers: This function below creates the HTML and CSS files in the current directory by
 writing the information required for creating a HTML and CSS file, as well as utilizing user inputs to help customize it. The function begins
 once the button labled "Make" is clicked. 
*/
        private void button1_Click(object sender, EventArgs e)
        {
            StreamWriter File = new StreamWriter("./" + textBox4.Text + ".html"); //The File varible can hold a stream of whatever string that's written to it using the Write().
            File.Write("<!DOCTYPE html>\r\n");//These HTML tags "<>" are written to help create the HTML file.
            File.Write("<head>\r\n");
            File.Write("<title>");
            File.Write(textBox1.Text); //Text from the textboxes of the form is written into the File variable. 
            File.Write("</title>\r\n");
            File.Write("<link rel=\'stylesheet\' href=\'"+ textBox8.Text +".css\' type=\'text/css\'/>\r\n");
            File.Write("</head>");
            File.Write("<h1>");
            File.Write(textBox2.Text);
            File.Write("</h1>\r\n");
            File.Write("<body>\r\n");
            File.Write(textBox3.Text + "\r\n");
            File.Write("</body>\r\n");
            File.Write("</html>\r\n");
            File.Close();    //The file is closed denoting the HTML file is successfully made.

            StreamWriter File2 = new StreamWriter("./" + textBox8.Text + ".css"); //File2 variable is open for a stream of strings to be written into it for creating a CSS file.
            File2.Write("h1{\r\n color: " + textBox5.Text + ";\r\n}");
            File2.Write("\r\nbody{\n color: " + textBox6.Text + ";\r\nBackground-color: " + textBox7.Text + ";\r\n}");
            File2.Close();

            MessageBox.Show("Webpage Created! Your created html and css files are located in the same folder or location as the WPCreater.exe. You could also search for them using the windows search bar.");
            Close(); // The file is closed denoting the successful completion of the CSS file
        }      
    }
}
