/* Compile.cpp
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
#include "Vocable.h"
#include "Vocable.cpp"

#include "Syntax.h"
#include "Syntax.cpp"

#include "Semantic.h"
#include "Semantic.cpp"

#include "VirtualMachine.h"
#include "VirtualMachine.cpp"
void main(int argc,char *argv[])

{

	int flag=0;
	Scan exe(argv[1]);
	flag=exe.main_scan();   //���ʷ�����
    #ifdef DEBUG
	cout<<flag<<endl;
    #endif

	Syntax exe2;	
  	flag=exe2.Programme();//���﷨����  
    #ifdef DEBUG
	cout<<flag<<endl;
    #endif

	Semantic exe3;	
	if (flag==0)
	{
	  flag=exe3.ParseStarUp();//������������������������  
      #ifdef DEBUG
	  cout<<flag<<endl;
      #endif
	  if (flag==0)
	  {
		VirtualMachine exe4;	
		flag=exe4.Execute();    //��������� ,����ִ�г���
		#ifdef DEBUG
		cout<<flag<<endl;
		#endif
    	cout<<"Press any key to continue";
 	    getch();
	  }
	  if (flag==0)
	  {
		   fwrong<<"Successful!"<<endl;
	  }

	} 
	remove("vocable");



}