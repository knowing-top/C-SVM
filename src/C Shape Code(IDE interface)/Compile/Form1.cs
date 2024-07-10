/* 
* Copyright 2007-2011, Shi shaofei (vivid.tju.dlut@gmail.com)

* This program is distributed in the hope that it will be useful
* for pepole who want to konw the  compiler's work,such as Lex-
* ical analysis,grammatical analysis,semantic analysis and stack 
* virtual machine's execution. 

* For education and personal research, you can free redistribute it 
* and/or modify it.The only requirement is that you must be marked
* my work and indicate the source of this software,to use this 
* program's codes,You'd better send a email to me.

* This file can't  be modify and must be include in program.

* Now,Enjoy the fun of the compiler world！
																											01.02.2011

* 本软件的目的是对那些对编译器词法分析、语法分析、语义分析以及栈
* 式虚拟机执行过程感兴趣的人提供帮助或者借鉴。

* 对于对于教育及个人研究者，你可以重新发布或修改本软件，唯一要求
* 提及我以及我的工作，并给出程序的来源

* 本文不可私自修改且必须包含于程序中。

* 现在享受编译世界的乐趣吧！

																											2011.01.02
*/
using System;
using System.Diagnostics; //开启运用程序
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;


namespace Compile
{
    public partial class Form1 : Form
    {
        private string CurrentFileName = ""; 
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CodeAera.Clear();
        }

        private void cutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CodeAera.Undo();
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void printToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFile();
        }

        private void helpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                Process ps = new Process();
                ps.StartInfo.FileName = @"Help\help.chm";
                ps.Start();
            }
            catch { MessageBox.Show("Fail to show the help files!"); }
           
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult res = MessageBox.Show("  Are you sure you want to exit?", "exit", MessageBoxButtons.OKCancel);
            if (res == DialogResult.OK)
                Application.Exit();
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutBox1 myAbout = new AboutBox1();
            myAbout.ShowDialog(); 
        }

        private void runToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ErrorInfo.Clear();
            if (CurrentFileName == "") { SaveAsFile(); }
            else
            {
                if (CodeAera.Modified)
                {
                    DialogResult res = MessageBox.Show("Sava the current context to file?", "Cancel", MessageBoxButtons.YesNoCancel);
                    if (res == DialogResult.Yes)
                    {//保存当前内容到文件
                        SaveFile();
                    }
                }

            }

            try
            {
                Process proc = Process.Start(@".\Execute\Compile.exe", CurrentFileName);
                if (proc != null)
                {
                    proc.WaitForExit();
                    ShowCompileResult();

                }
                string destinationFile = "vocable";

                if (File.Exists(destinationFile))
                {

                    FileInfo fi = new FileInfo(destinationFile);

                    if (fi.Attributes.ToString().IndexOf("ReadOnly") != -1)

                        fi.Attributes = FileAttributes.Normal;

                    File.Delete(destinationFile);

                }
            }
            catch (ArgumentException ex)
            {
                MessageBox.Show(ex.Message, this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void middleCodeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                using (StreamReader myStreamReader = File.OpenText("code"))
                {
                    CodeAera.Text = myStreamReader.ReadToEnd();
                    myStreamReader.Close();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(
              "Unable to open or read the file" + Environment.NewLine +
              "make sure the file name is correct," + "and you have the read authority."
              + Environment.NewLine + Environment.NewLine + "exception："
              + ex.Message
                );
            }
        }

        private void sourseToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                using (StreamReader myStreamReader = File.OpenText(CurrentFileName))
                {
                    CodeAera.Text = myStreamReader.ReadToEnd();
                    myStreamReader.Close();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(
              "Unable to open or read the file" + Environment.NewLine +
              "make sure the file name is correct," + "and you have the read authority."
              + Environment.NewLine + Environment.NewLine + "exception："
              + ex.Message
                );
            }
           
        }

        private void openToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            OpenFileDialog OpenFileDialog1 = new OpenFileDialog();
            openFileDialog1.RestoreDirectory = true;
            openFileDialog1.InitialDirectory = @".\Demos\";
            openFileDialog1.Filter = "MSCT Files (*.msct)|*.msct|Text Files (*.txt)|*.txt|All Files(*.*)|*.*";
            openFileDialog1.FilterIndex = 1;
            openFileDialog1.FileName = "";
      
            if(openFileDialog1.ShowDialog()==DialogResult.OK)
            {
                CurrentFileName = openFileDialog1.FileName;
                StreamReader myStreamReader = new StreamReader(openFileDialog1.FileName);
                try
                {
                    CodeAera.Text = myStreamReader.ReadToEnd();

                }
                catch (Exception ex)
                {
                    MessageBox.Show(
                  "Unable to open or read the file" + Environment.NewLine +
                  "make sure the file name is correct," + "and you have the read authority."
                  + Environment.NewLine + Environment.NewLine + "exception："
                  + ex.Message
                    );
                }
                myStreamReader.Close();
            }
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveAsFile();
        }

        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFile();
            CodeAera.Clear();

        }
        private void SaveAsFile()
        {
            SaveFileDialog saveFileDialog2 = new SaveFileDialog();
            saveFileDialog2.Filter = "MSCT Files (*.msct)|*.msct|Text Files (*.txt)|*.txt|All Files(*.*)|*.*";
            saveFileDialog2.FilterIndex = 1;
            saveFileDialog2.RestoreDirectory = true;
            if (saveFileDialog2.ShowDialog() == DialogResult.OK)
            {
                CurrentFileName = saveFileDialog2.FileName;
                StreamWriter savemessage = new StreamWriter(saveFileDialog2.OpenFile(), System.Text.Encoding.GetEncoding(-0));
                try
                {
                    savemessage.WriteLine(CodeAera.Text);
                }
                catch { MessageBox.Show("Fail to sava the file!"); }
                finally
                {
                    savemessage.Close();
                }
            }
        }
        private void SaveFile()
        {
             //保存当前内容到文件
                if (CurrentFileName == "") { SaveAsFile(); }
                else
                {
                    StreamWriter savemessage = new System.IO.StreamWriter(CurrentFileName);
                    try
                    {
                        savemessage.WriteLine(CodeAera.Text);
                    }
                    catch { MessageBox.Show("Fail to sava the file!"); }
                    finally
                    {
                        savemessage.Close();
                    }
                }
          
        }

        private void copyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CodeAera.Cut();
        }

        private void pasteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CodeAera.Copy();
        }

        private void pasteToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            CodeAera.Paste();
        }
        private void ShowCompileResult()
        {
            StreamReader myStreamReader = File.OpenText("error");
            try
            {
                ErrorInfo.Text = myStreamReader.ReadToEnd();

            }
            catch (Exception ex)
            {
                MessageBox.Show(
              "Unable to open or read the file" + Environment.NewLine +
              "make sure the file name is correct," + "and you have the read authority."
              + Environment.NewLine + Environment.NewLine + "exception："
              + ex.Message
                );
            }
            myStreamReader.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {

           ShowCompileResult();

        }
        private void cursorAction(object sender, EventArgs e)
        {
             int index = CodeAera.GetFirstCharIndexOfCurrentLine();//得到当前行第一个字符的索引!!
             int line  = CodeAera.GetLineFromCharIndex(index) + 1;
             label3.Text = line.ToString();
             label3.Update();
        }

        private void exitToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            DialogResult res = MessageBox.Show("Are you sure you want to exit?", "exit", MessageBoxButtons.OKCancel);
            if (res == DialogResult.OK)
                Application.Exit();
        }
    }
 

}
