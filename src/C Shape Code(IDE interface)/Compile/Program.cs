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

* Now,Enjoy the fun of the compiler world��
																											01.02.2011

* �������Ŀ���Ƕ���Щ�Ա������ʷ��������﷨��������������Լ�ջ
* ʽ�����ִ�й��̸���Ȥ�����ṩ�������߽����

* ���ڶ��ڽ����������о��ߣ���������·������޸ı������ΨһҪ��
* �ἰ���Լ��ҵĹ������������������Դ

* ���Ĳ���˽���޸��ұ�������ڳ����С�

* �������ܱ����������Ȥ�ɣ�

																											2011.01.02
*/
using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Media;
using System.IO;
namespace Compile
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            //try
            //{
            //    SoundPlayer simpleSound = new SoundPlayer(@"Music\Music.wav");
            //    simpleSound.Play();
            //}
            //catch { }
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());

            string destinationFile = "code";

            if (File.Exists(destinationFile))
            {

                FileInfo fi = new FileInfo(destinationFile);

                if (fi.Attributes.ToString().IndexOf("ReadOnly") != -1)

                    fi.Attributes = FileAttributes.Normal;

                File.Delete(destinationFile);

            }

            string destinationFile2 = "error";

            if (File.Exists(destinationFile2))
            {

                FileInfo fi = new FileInfo(destinationFile2);

                if (fi.Attributes.ToString().IndexOf("ReadOnly") != -1)

                    fi.Attributes = FileAttributes.Normal;

                File.Delete(destinationFile2);

            }


        }
    }
}