/* Vocable.cpp
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
#include"Vocable.h"

Scan::Scan(char *FileName)
{
	es=0;
	line=1;
	myFileName=FileName;
};
int Scan:: main_scan()
{
    
   if ((fin=fopen(myFileName,"r"))==NULL) //判断输入文件名是否正确
   {
      # ifdef DEBUG
	   cout<<"\n打开词法分析输入文件出错!\n";
      # endif
	  return 1;//输入文件出错返回错误代码1
   }
   if ((fout=fopen("vocable","w"))==NULL) //判断输出文件名是否正确
   {
      # ifdef DEBUG
	    cout<<"\n创建词法分析输出文件出错!\n";
      # endif
	  
	  return 2; //输出文件出错返回错误代码2
   }
   if (!fwrong.is_open()) //判断输出文件名是否正确
   {
      # ifdef DEBUG
	    cout<<"\n打开错误输出文件出错!\n";
      # endif
	  
	  return 3; //输出文件出错返回错误代码2
    }
   ch=getc(fin);
   while (ch!=EOF)
   {
	  while (ch==' '||ch=='\n'||ch=='\t')
	  {
		  if (ch=='\n') {line++;}
		  ch=getc(fin);
	  }
	  if (ch==EOF) break;
	  switch(contral_dealwith()) 
	   {
		case 1:    alphabet();
				   break;
		case 2:    digit();
				   break;
		case 3:    singleword_only();
				   break;
		case 4:    doubleword_only();
				   break;
		case 5:    comment();
				   break;
		default:   error_dealwith();			   

	   }
   }
   fclose(fin);//关闭输入输出文件
   fclose(fout);
   return(es);  //返回主程序
           
}

int Scan:: contral_dealwith()
{
   if (isalpha(ch))                      return 1;
   else if(isdigit(ch))                  return 2;
   else if(strchr(singleword,ch)>0)      return 3;
   else if(strchr(doubleword,ch)>0)      return 4;
   else if(ch=='/')                      return 5;
   else                                  return 6;                        
}
void Scan:: alphabet()//1
{
	 token[0]=ch; j=1;
	 ch=getc(fin);
	 while(isalnum(ch))  //如果是字母数字则组合标识符；如果不是则标识符组合结束
	 {
		token[j++]=ch;  //组合的标识符保存在token中
		ch=getc(fin);  //读下一个字符
	 }
	 token[j]='\0';  //标识符组合结束	 

	 //＝＝＝＝＝＝＝＝＝＝＝＝＝查保留字＝＝＝＝＝＝＝＝＝＝＝
	 n=0;
	 while ((n<keywordSum) && strcmp(token,keyword[n])) n++;
	 if (n>=keywordSum)  //不是保留字，输出标识符
	 {
		 fprintf(fout,"%s\t%s\t%d\n","ID",token,line);  //输出标识符符号
	 }
	else//是保留字，输出保留字
	{
		fprintf(fout,"%s\t%s\t%d\n",token,token,line);  //输出保留字符号
	}
}
void Scan:: digit()//2
{
	 token[0]=ch; j=1;
	 ch=getc(fin);  //读下一个字符
	 while (isdigit(ch))  //如果是数字则组合整数；如果不是则整数组合结束
	 {
		token[j++]=ch;  //组合整数保存在token中
		ch=getc(fin);  //读下一个字符
	 }
	 token[j]='\0';  //整数组合结束		 
	 fprintf(fout,"%s\t%s\t%d\n","NUM",token,line);  //输出整数符号
}
void Scan:: singleword_only()//3
{
	 token[0]=ch; token[1]='\0';
	 ch=getc(fin);//读下一个符号以便识别下一个单词
	 fprintf(fout,"%s\t%s\t%d\n",token,token,line);  //输出单分界符符号
}
void Scan:: doubleword_only()//4
{
	 token[0]=ch;
	 ch=getc(fin);  //读下一个字符判断是否为双分界符
	 if (ch=='=')  //如果是=，组合双分界符
	 {
		token[1]=ch;token[2]='\0';  //组合双分界符结束
		ch=getc(fin);  //读下一个符号以便识别下一个单词
	 } 
	 else//不是=则为单分界符
	 token[1]='\0';
	 fprintf(fout,"%s\t%s\t%d\n",token,token,line);  //输出单或双分界符符号
}
void Scan:: comment()//5
{
   	 ch=getc(fin);  //读下一个字符
	 if (ch=='*')  //如果是*，则开始处理注释
	 {  
		char ch1;
		ch1=getc(fin);  //读下一个字符
		do{
			ch=ch1;
			if (ch1=='\n')
			{
				line++;
			}
			ch1=getc(fin);
		}while ((ch!='*' || ch1!='/')&&ch1!=EOF);  //直到遇到注释结束符*/或文件尾 +++//删除注释+++

		ch=getc(fin);//读下一个符号以便识别下一个单词
	 } 
	 else  //不是*则处理单分界符/
	 {
		 token[0]='/'; token[1]='\0';
		 fprintf(fout,"%s\t%s\t%d\n",token,token,line);  //输出单分界符/
	 }
}
void Scan:: error_dealwith()//6
{
	 token[0]=ch;token[1]='\0';
	 ch=getc(fin);//汉字占两个字节
	 ch=getc(fin);  //读下一个符号以便识别下一个单词

	 es=3;  //设置错误代码
	 fwrong<<line<<"\tUnkown character!"<<endl; //输出错误符号
     # ifdef DEBUG
	 cout<<line<<"\tUnkown character!"<<endl;
     # endif
}
