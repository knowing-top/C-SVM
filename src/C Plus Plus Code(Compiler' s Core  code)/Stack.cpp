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
#include "Stack.h"

myStack::myStack()
{
   if(!(base=(int *)malloc(STACK_INIT_SIZE*sizeof(int)))) // �洢����ʧ��
   {
	   exit(1);
   }  
   top=base;
   stacksize=STACK_INIT_SIZE;
}

int myStack:: ClearStack()
 { // ��S��Ϊ��ջ
   top=base;
   return 1;  
 }

int myStack:: StackEmpty()
 { // ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE
   if(top==base)
     return 1;
   else
     return 0;
 }
int myStack:: GetTop(int &e)
 { // ��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
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
	int a;//��������亯����ʽ
	if(Pop(a))
	{
	  flag=Push(e);
	}
    return flag;

}
int myStack:: Push(int e)
 { // ����Ԫ��eΪ�µ�ջ��Ԫ��
   if(top-base>=stacksize) // ջ����׷�Ӵ洢�ռ�
   {
     base=(int *)realloc(base,(stacksize+STACKINCREMENT)*sizeof(int));
     if(!base)
	 {return 0;} // �洢����ʧ��
     top=base+stacksize;
     stacksize+=STACKINCREMENT;
   }
   *(top)++=e;
   return 1;
 }

int myStack:: Pop(int &e)
 { // ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
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