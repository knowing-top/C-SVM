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
#ifndef Const_H_
#define Const_H_
#include "Head.h"
#include "Struct.h"

const int STACK_INIT_SIZE=10; // �洢�ռ��ʼ������
const int STACKINCREMENT=2; // �洢�ռ��������



const int  keywordSum=9;//�ؼ��ֵ���Ŀ
const char *keyword[keywordSum]={ "if","else","for","while", "main","int","read","write","return"};
const char singleword[50]="+-*(){};,:";
const char doubleword[10]="><=!";
const int  maxLever=7;
const int  varTableLength=1000;//������ű������
const int  CodeMaxLengrh=1000;//����������󳤶�
const int  JmpPositionMax=100;

Lever leverTable[maxLever];//��α�
int leverTableTop=0;


Table varTable[varTableLength];//���ű�

int  Code[CodeMaxLengrh][2];//0 ������� 1������� 
int  JmpPosition[JmpPositionMax];//ת��λ�ò�ѯ��

ofstream fwrong("error",ios::out);//��������ļ�


#endif 

