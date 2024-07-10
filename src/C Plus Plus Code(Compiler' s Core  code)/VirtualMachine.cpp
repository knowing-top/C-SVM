/* VirtualMachine.cpp
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
#include"VirtualMachine.h"

VirtualMachine::VirtualMachine()
{
   errorFlag=0;
   CommendLine.open("CommendLine.comm",ios::in|ios::out);
}
int VirtualMachine::Execute()
{
  int i=0;
  int StackTopValue;
  int content;
  int operator1;
  int operator2;
  while(i<CodeMaxLengrh)
  {
    switch(Code[i][0])
	{
	 case  0:content=varTable[Code[i][1]].address;
		     StackMachine.Push(content);
		     i++;
		     break;
     case  1:StackMachine.Push(Code[i][1]);
		     i++;
		     break;
	 case  2:StackMachine.GetTop(content);
             varTable[Code[i][1]].address=content;
		     i++;
		     break;
	 case  3:StackMachine.Pop(content);
		     varTable[Code[i][1]].address=content;
		     i++;
		     break;
	 case  4:StackMachine.Pop(operator1);
		     StackMachine.Pop(operator2);
			 StackMachine.Push(operator2+operator1);
			 i++;
		     break;
	 case  5:StackMachine.Pop(operator1);
             StackMachine.Pop(operator2);
			 StackMachine.Push(operator2-operator1);
			 i++;
		     break;
	 case  6:StackMachine.Pop(operator1);
             StackMachine.Pop(operator2);
			 StackMachine.Push(operator2*operator1);
			 i++;
		     break;
	 case  7:StackMachine.Pop(operator1);
             StackMachine.Pop(operator2);
			 StackMachine.Push(operator2/operator1);
			 i++;
		     break;
	 case  8:i=JmpPosition[Code[i][1]];
		     break;
	 case  9:StackMachine.Pop(StackTopValue);
		  //   StackMachine.GetTop(StackTopValue);
		     if (StackTopValue==0) 
			 {
				 i=JmpPosition[Code[i][1]];
			 }
			 else{i++;}
		     break;
	 case 10:StackMachine.Pop(operator1);
		     StackMachine.Pop(operator2);
//			 StackMachine.GetTop(operator1);
// 		     StackMachine.GetTop(operator2);
			 if (operator1==operator2)
			 {
				 StackMachine.Push(1);
			 }
			 else{StackMachine.Push(0);}
			 i++;
		     break;
	 case 11:StackMachine.Pop(operator1);
		     StackMachine.Pop(operator2);
//			 StackMachine.GetTop(operator1);
// 		     StackMachine.GetTop(operator2);
			 if (operator1==operator2)
			 {
				 StackMachine.Push(0);
			 }
			 else{StackMachine.Push(1);}
			 i++;
		     break;
	 case 12:StackMachine.Pop(operator1);
		     StackMachine.Pop(operator2);
//			 StackMachine.GetTop(operator1);
// 		     StackMachine.GetTop(operator2);
			 if (operator2>operator1)
			 {
				 StackMachine.Push(1);
			 }
			 else{StackMachine.Push(0);}
			 i++;
		     break;
	 case 13:StackMachine.Pop(operator1);
		     StackMachine.Pop(operator2);
//			 StackMachine.GetTop(operator1);
// 		     StackMachine.GetTop(operator2);
			 if (operator2<operator1)
			 {
				 StackMachine.Push(1);
			 }
			 else{StackMachine.Push(0);}
			 i++;
		     break;
	 case 14:StackMachine.Pop(operator1);
		     StackMachine.Pop(operator2);
//			 StackMachine.GetTop(operator1);
// 		     StackMachine.GetTop(operator2);
			 if (operator2>=operator1)
			 {
				 StackMachine.Push(1);
			 }
			 else{StackMachine.Push(0);}
			 i++;
		     break;
	 case 15:StackMachine.Pop(operator1);
		     StackMachine.Pop(operator2);
//			 StackMachine.GetTop(operator1);
// 		     StackMachine.GetTop(operator2);
			 if (operator2<=operator1)
			 {
				 StackMachine.Push(1);
			 }
			 else{StackMachine.Push(0);}
			 i++;
			 break;
	 case 16:StackMachine.Pop(operator1);
		     StackMachine.Pop(operator2);
//			 StackMachine.GetTop(operator1);
// 		     StackMachine.GetTop(operator2);
			 if (operator2&&operator1)
			 {
				 StackMachine.Push(1);
			 }
			 else{StackMachine.Push(0);}
			 i++;
		     break;
	 case 17:StackMachine.Pop(operator1);
		     StackMachine.Pop(operator2);
//			 StackMachine.GetTop(operator1);
// 		     StackMachine.GetTop(operator2);
			 if (operator2||operator1)
			 {
				 StackMachine.Push(1);
			 }
			 else{StackMachine.Push(0);}
			 i++;
			 break;
	 case 18:StackMachine.Pop(StackTopValue);
		     StackMachine.Push(!StackTopValue);
			 i++;
		     break;
	 case 19:cout<<"Please Input "<<varTable[Code[i][1]].name<<"'value:";
		     cin>>operator1;
			// StackMachine.Push(operator1);
			 StackMachine.SetTopValue(operator1);
             varTable[Code[i][1]].address=operator1;
			 i++;
		     break;
	 case 20:StackMachine.Pop(StackTopValue);
		     cout<<"The result is:"<<StackTopValue<<endl;;
			 i++;
		     break;
	 case 21:i=CodeMaxLengrh;
		     break;
	 default:i++;
		     break;
	}
  }
  return errorFlag;
}
