/* Struct.h
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
#ifndef  Struct_H_
#define  Struct_H_
#include "Head.h"

struct Table
{//������ű�ṹ
	 string name; 
	 int  link;//ָ����һ��ID
	 int  type;//1:int, 0:void
	 int  obj;//0������,1:����
     int  address;//�����ĵ�ַ��ʾ��ֵ��
	              //�﷨�����к����ĵ�ַ��ʾ��������������ʱ��ʾ������ڵ�ַ
};
struct Lever
{
	int link;//�ò㿪ʼ
	int last;//�ò����һ��
};


#endif