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
	flag=exe.main_scan();   //调词法分析
    #ifdef DEBUG
	cout<<flag<<endl;
    #endif

	Syntax exe2;	
  	flag=exe2.Programme();//调语法分析  
    #ifdef DEBUG
	cout<<flag<<endl;
    #endif

	Semantic exe3;	
	if (flag==0)
	{
	  flag=exe3.ParseStarUp();//调语义分析，产生虚拟机代码  
      #ifdef DEBUG
	  cout<<flag<<endl;
      #endif
	  if (flag==0)
	  {
		VirtualMachine exe4;	
		flag=exe4.Execute();    //虚拟机代码 ,解释执行程序
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
