/* Const.h
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
#ifndef Const_H_
#define Const_H_
#include "Head.h"
#include "Struct.h"

const int STACK_INIT_SIZE=10; // 存储空间初始分配量
const int STACKINCREMENT=2; // 存储空间分配增量



const int  keywordSum=9;//关键字的数目
const char *keyword[keywordSum]={ "if","else","for","while", "main","int","read","write","return"};
const char singleword[50]="+-*(){};,:";
const char doubleword[10]="><=!";
const int  maxLever=7;
const int  varTableLength=1000;//定义符号表的容量
const int  CodeMaxLengrh=1000;//代码数组最大长度
const int  JmpPositionMax=100;

Lever leverTable[maxLever];//层次表
int leverTableTop=0;


Table varTable[varTableLength];//符号表

int  Code[CodeMaxLengrh][2];//0 存操作码 1存操作数 
int  JmpPosition[JmpPositionMax];//转移位置查询表

ofstream fwrong("error",ios::out);//错误输出文件


#endif 

