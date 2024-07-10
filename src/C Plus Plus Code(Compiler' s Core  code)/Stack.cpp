/* Stack.cpp
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
#include "Stack.h"

myStack::myStack()
{
   if(!(base=(int *)malloc(STACK_INIT_SIZE*sizeof(int)))) // 存储分配失败
   {
	   exit(1);
   }  
   top=base;
   stacksize=STACK_INIT_SIZE;
}

int myStack:: ClearStack()
 { // 把S置为空栈
   top=base;
   return 1;  
 }

int myStack:: StackEmpty()
 { // 若栈S为空栈，则返回TRUE，否则返回FALSE
   if(top==base)
     return 1;
   else
     return 0;
 }
int myStack:: GetTop(int &e)
 { // 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
   if(top>base)
   {
     e=*(top-1);
     return 1;
   }
   else{return 0;}
 }
int myStack:: SetTopValue(int e)
{
	int flag=0;
	int a;//无意义填充函数格式
	if(Pop(a))
	{
	  flag=Push(e);
	}
    return flag;

}
int myStack:: Push(int e)
 { // 插入元素e为新的栈顶元素
   if(top-base>=stacksize) // 栈满，追加存储空间
   {
     base=(int *)realloc(base,(stacksize+STACKINCREMENT)*sizeof(int));
     if(!base)
	 {return 0;} // 存储分配失败
     top=base+stacksize;
     stacksize+=STACKINCREMENT;
   }
   *(top)++=e;
   return 1;
 }

int myStack:: Pop(int &e)
 { // 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
   if(top==base){ return 0;}
   else{e=*--top;return 1;}
 }
myStack::~myStack()
{
   free(base);
   base=NULL;
   top=NULL;
   stacksize=0;
}