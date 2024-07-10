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
#ifndef Vocable_H_


#include "Head.h"
#include "Const.h"

#define Vocable_H_
class Scan
{
private:
	char ch,token[40];//chΪÿ�ζ�����ַ���token���ڱ���ʶ����ĵ���
	int es,j,n;//es������룬0��ʾû�д���j,nΪ��ʱ������������ϵ���ʱ���±��
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



