/* Stack.h
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

* ��������Ŀ���Ƕ���Щ�Ա������ʷ��������﷨��������������Լ�ջ
* ʽ�����ִ�й��̸���Ȥ�����ṩ�������߽����

* ���ڶ��ڽ����������о��ߣ���������·������޸ı�������ΨһҪ��
* �ἰ���Լ��ҵĹ������������������Դ

* ���Ĳ���˽���޸��ұ�������ڳ����С�

* �������ܱ����������Ȥ�ɣ�

																											2011.01.02
*/
#ifndef Stack_H_
#define Stack_H_
#include "Const.h"
class myStack
{
private:
	int *base;// ��ջ����֮ǰ������֮��base��ֵΪNULL
    int *top; // ջ��ָ��
    int stacksize; // ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
public:
    myStack();
	int ClearStack();
	int StackEmpty();
	int GetTop(int &e);
	int SetTopValue(int e);
	int Push(int e);
	int Pop(int &e);
	~myStack();
};
#endif