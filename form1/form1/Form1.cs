using System;
using System.IO;
using System.Text;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace form1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        /*Note to viewers: This function below handles whatever text is dragged into the form by checking if the text is part of
         an URL before allowing it to be dragged into the form. Also test this program out by dragging any text from the internet browser and dropping it into this programs windows form.*/

        private void textBox1_DragEnter(object sender, DragEventArgs e)
        {
            e.Effect = DragDropEffects.All;
            string hold = null;
            hold += e.Data.GetData(DataFormats.Text).ToString(); //any data that gets dropped into the windows form is added to the hold string. 
            string temp = "";
            bool urlmode = false;

            for (int k = hold.Length - 1; k >= 0; k--) //looping through hold string in reverse to checking for top level domain such as ".com", "edu", or ".net" to find the end of a URL.
            {
                if ((hold[k] == 'm' && hold[k - 1] == 'o' && hold[k - 2] == 'c' && hold[k - 3] == '.') || (hold[k] == 'u' && hold[k - 1] == 'd' && hold[k - 2] == 'e' && hold[k - 3] == '.') || (hold[k] == 'v' && hold[k - 1] == 'o' && hold[k - 2] == 'g' && hold[k - 3] == '.') || (hold[k] == 't' && hold[k - 1] == 'e' && hold[k - 2] == 'n' && hold[k - 3] == '.'))
                {
                    urlmode = true; 
                }
                if (urlmode == false)
                    continue;

                if(urlmode == true)  // if true then start add characters to the temporary string. 
                {
                    temp += hold[k];
                    Console.WriteLine(temp); // testing to see if something is in temp. 
                }
                if(k <= 0 || hold[k] == ' ' || hold[k] == '\n') //if a space, a newline, or beginning of hold string is reached, then stop add characters to temp and transfer characters from temp to the textBox1.Text string a.k.a. the windows form. 
                {
                    urlmode = false;
                    for(int d = temp.Length - 1; d >= 0; d--)
                    {
                        textBox1.Text += temp[d];
                    }
                    textBox1.Text += ' '; // plus add a space after each URL statement
                    temp = null;          // emptying the temp variable. 
                }
            }
            hold = null; // clearing out the hold string to prepare for the next possible url string to fill it up. 
        }
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        private void openToolStripMenuItem_Click(object sender, EventArgs e) //This function starts the process of browsing which .txt file to open once the "Open" option is clicked in the file dropdown menu.
        {
            Stream str;
            OpenFileDialog fd = new OpenFileDialog();
            fd.Filter = "Texts Only | *.txt| All Files|*.*";
            fd.ShowDialog();
            if((str = fd.OpenFile()) != null)
            {
                string fn = fd.FileName;
                string filetext = File.ReadAllText(fn);
                textBox1.Text = filetext;
            }
        }

        private void quitToolStripMenuItem_Click(object sender, EventArgs e) // This function begins the "Quit" button is clicked in the file dropdown menu & it basically closes the application.
        {
            Close();
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)// This function starts after the "New" option is clicked in the file dropdown menu and it erases any text from the form. 
        {
            textBox1.Text = null;
        }
    }
}
