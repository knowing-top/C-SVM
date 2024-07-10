/* Vocable.h
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
#ifndef Vocable_H_


#include "Head.h"
#include "Const.h"

#define Vocable_H_
class Scan
{
private:
	char ch,token[40];//ch为每次读入的字符，token用于保存识别出的单词
	int es,j,n;//es错误代码，0表示没有错误。j,n为临时变量，控制组合单词时的下标等
	int line;
	FILE *fin,*fout;
	char *myFileName;
public:
	Scan(char *FileName);
	void alphabet();//1
	void digit();//2
	void singleword_only();//3
	void doubleword_only();//4
	void comment();//5
	void error_dealwith();//6
	int contral_dealwith();
	int main_scan();		 
};

#endif



