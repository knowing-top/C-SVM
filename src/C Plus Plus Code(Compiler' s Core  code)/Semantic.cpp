/* Semantic.cpp
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
#include"Semantic.h"

Semantic::Semantic()
{
	line=1;
	labelp=0;
	fileadd=0;
	errorFlag=0;
	former=-1;
	curPosition=-1; 
	operateCodePosition=-1;
	leverTableTop=0;    
	varTable[0].link=-1;
    leverTable[leverTableTop].link=-1;
	for (int i=0;i<varTableLength;i++)//初始化符号表
	{
		varTable[i].name=" ";
		varTable[i].address=INT_MIN;
	}
	for (int i=0;i<CodeMaxLengrh;i++)
	{
      Code[i][0]=-1;
	  Code[i][1]=INT_MIN;
	}

	for (int i=0;i<JmpPositionMax;i++)
	{
		JmpPosition[i]=-1;
	}
	fin.open("vocable",ios_base::in);
	fout.open("code",ios_base::out);
}

int Semantic::ParseStarUp()
{
   if (!fin.is_open()) //判断输入文件名是否打开
   {
      # ifdef DEBUG
	   cout<<"\t\n打开词法分析结果文件出错!\n";
      # endif
	  return 4;//输入文件出错返回错误代码1
   } 
   if (!fout.is_open()) //判断输入文件名是否打开
   {
      # ifdef DEBUG
	   cout<<"\t\n创建虚拟机代码文件出错!\n";
      # endif
	  return 5;//输入文件出错返回错误代码1
   }
   	fin>>token>>token1>>line;
	if (token!="{")
	{
		errorFlag=1;
		fwrong<<line<<"\tunexpected star of file found,miss '{'!"<<endl;
        #ifdef DEBUG
        cout<<line<<"\tunexpected star of file found,miss '{'!"<<endl;
        #endif
	}
    fin>>token>>token1>>line;
	StatementList();
    if (fin.eof()&&token!="}")
    {
	  fwrong<<line<<"\tunexpected end of file found,miss '}'!"<<endl;
      #ifdef DEBUG
      cout<<line<<"\tunexpected end of file found,miss '}'!"<<endl;
      #endif
    }
   #ifdef DEBUG
   cout<<"\tSTOP"<<endl;	
   #endif
   fout<<"\tSTOP"<<endl;
   WriteCode(21);
   fin.close();
   return errorFlag;
}
void Semantic::StatementList()
{	
	while (token!="}")
	{
		Statement();
		if(fin.eof()){break;}
	}
}
void Semantic::Statement()
{
	if (token=="int")         VarDeclare();   //声明语句
	else if ( token=="if")    IfStat();       //<IF语句>
	else if (token=="while")  WhileStat();    //<while语句>
	else if (token=="for")    ForStat();      //<for语句>
	else if (token=="read")   ReadStat();     //<read语句>
	else if (token=="write")  WriteStat();    //<write语句>
	else if (token=="ID"||token=="NUM"||token=="(")  ExpressionStat();//<表达式语句>
	else 	return;
}

void Semantic::SentenceBody()
{
    int parentheses=0;
	if (token=="{")
	{
		parentheses=1;
		EnterLever();
		fin>>token>>token1>>line;
    	StatementList();
	}
	else {Statement();}
	if (parentheses==1)
	{       
		if (token!="}")
		{
			fwrong<<line<<"\tmiss '}'!"<<endl;
            #ifdef DEBUG
			cout<<line<<"\tmiss '}'!"<<endl;
            #endif
			fin>>token>>token1>>line;
		}
		else
		{
			QuitLever();
            fin>>token>>token1>>line;
		}
	}
}
void Semantic::VarDeclare()
{
	int fileadd=fin.tellg();//记住当前文件位置
	fin>>token>>token1>>line;//ID
	Insert(token1,1,0);//插入符号表
    fin>>token>>token1>>line;
	if (token=="=")
	{
       fin.seekg(fileadd);//若为'='则文件指针回到'ID'前的标识符 进行表达式处理
       fin>>token>>token1>>line;
	   Expression();
	}
	fin>>token>>token1>>line;	
}
void Semantic::IfStat()
{
	fin>>token>>token1>>line;//(

	fin>>token>>token1>>line;
	Expression();//)

	label1=labelp++;
	fout<<"\tJCXZ\t"<<label1<<endl;//输出条件为假时转移指令
	WriteCode(9,label1);
    #ifdef DEBUG
	cout<<"\tJCXZ\t"<<label1<<endl;
    #endif

	fin>>token>>token1>>line;
    SentenceBody();

	label2=labelp++;
	fout<<"\tJMP\t"<<label2<<endl;//无条件转移指令
	WriteCode(8,label2);
    #ifdef DEBUG
	cout<<"\tJMP\t"<<label2<<endl;
    #endif

	fout<<"LABEL "<<label1<<endl;//设置label1记住的标号
    AddJmp(label1);//记录label1记住的标号
    #ifdef DEBUG
	cout<<"LABEL "<<label1<<endl;
    #endif

	if (token=="else")//else部分处理
	{ 
		fin>>token>>token1>>line;
        SentenceBody();
	}
	fout<<"LABEL "<<label2<<endl;//设置label2记住的标号
	AddJmp(label2);//记录label2记住的标号
    #ifdef DEBUG
	cout<<"LABEL "<<label2<<endl;
    #endif
}
void Semantic::WhileStat()
{  
	label1=labelp++;
	fout<<"LABEL "<<label1<<endl;//设置label1记住的标号
	AddJmp(label1);//记录label1记住的标号
    #ifdef DEBUG
	cout<<"LABEL "<<label1<<endl;
    #endif

	fin>>token>>token1>>line;//(
	fin>>token>>token1>>line;
	Expression();
    label2=labelp++;
	fout<<"\tJCXZ\t"<<label2<<endl;//输出条件为假时转移指令
	WriteCode(9,label2);
    #ifdef DEBUG
	cout<<"\tJCXZ\t"<<label2<<endl;
    #endif
	fin>>token>>token1>>line;//
	SentenceBody();
	fout<<"\tJMP\t"<<label1<<endl;//无条件转移指令
	WriteCode(8,label1);
    #ifdef DEBUG
	cout<<"\tJMP\t"<<label1<<endl;
    #endif

	fout<<"LABEL "<<label2<<endl;//设置label2记住的标号
	AddJmp(label2);
    #ifdef DEBUG
	cout<<"LABEL "<<label2<<endl;
    #endif
}
void Semantic::ForStat()
{ 
	int label3,label4;
	fin>>token>>token1>>line;//(
	fin>>token>>token1>>line;
	if (token=="int")
	{
	 fin>>token>>token1>>line;//ID	 
	 Insert(token1,1,0); 
     Expression();
	}
	else{Expression();}

	label1=labelp++;
	fout<<"LABEL "<<label1<<endl;//设置label1记住的标号
	AddJmp(label1);
    #ifdef DEBUG
	cout<<"LABEL "<<label1<<endl;
    #endif

	fin>>token>>token1>>line;
	Expression();
    label2=labelp++;
	fout<<"\tJCXZ\t"<<label2<<endl;//输出条件为假时转移指令
	WriteCode(9,label2);
    #ifdef DEBUG
	cout<<"\tJCXZ\t"<<label2<<endl;
    #endif
	label3=labelp++;
	fout<<"\tJMP\t"<<label3<<endl;//无条件转移指令
	WriteCode(8,label3);
    #ifdef DEBUG
	cout<<"\tJMP\t"<<label3<<endl;
    #endif

	label4=labelp++;
	fout<<"LABEL "<<label4 <<endl;//设置label4记住的标号
	AddJmp(label4);
    #ifdef DEBUG
	cout<<"LABEL "<<label4 <<endl;
    #endif

	fin>>token>>token1>>line;
	Expression();
	fout<<"\tJMP\t"<<label1<<endl;//无条件转移指令
	WriteCode(8,label1);
    #ifdef DEBUG
	cout<<"\tJMP\t"<<label1<<endl;
    #endif
	fout<<"LABEL "<<label3 <<endl;//设置label3记住的标号
	AddJmp(label3);
    #ifdef DEBUG
	cout<<"LABEL "<<label3 <<endl;
    #endif

	fin>>token>>token1>>line;
	SentenceBody();
	fout<<"\tJMP\t"<<label4<<endl;//无条件转移指令
	WriteCode(8,label4);
    #ifdef DEBUG
	cout<<"\tJMP\t"<<label4<<endl;
    #endif
	fout<<"LABEL "<<label2 <<endl;//设置label2记住的标号
	AddJmp(label2);
    #ifdef DEBUG
	cout<<"LABEL "<<label2 <<endl;
    #endif
}

void Semantic::WriteStat()
{
	fin>>token>>token1>>line;
	Expression();

	fout<<"\tOUT"<<endl;//设置label2记住的标号
	WriteCode(20);
    #ifdef DEBUG
	cout<<"\tOUT"<<endl;
    #endif
	fin>>token>>token1>>line;
}
void Semantic::ReadStat()
{
	int position=-1;
	fin>>token>>token1>>line;
	Lookup(token1,0,position);
	fout<<"\tIN\t"<<position<<endl;
	WriteCode(19,position);
    #ifdef DEBUG
	cout<<"\tIN\t"<<position<<endl;
    #endif
	fin>>token>>token1>>line;//;
	fin>>token>>token1>>line;
}
void Semantic::ExpressionStat()
{
	if (token==";")
	{
		fin>>token>>token1>>line;
		return;
	}
	Expression();
	fin>>token>>token1>>line;
}
void Semantic::Expression()
{
	int fileadd,position=-1;
	string token2,token3;
	if (token=="ID")
	{   
        fileadd=fin.tellg();//记住当前文件位置
	    fin>>token2>>token3>>line;
		if (token2=="=")  //'='
		{
			Lookup(token1,0,position);
			fin>>token>>token1>>line;
			BoolExpr();
			fout<<"\tSTO\t"<<position<<endl;
			WriteCode(2,position);
            #ifdef DEBUG
			cout<<"\tSTO\t"<<position<<endl;
            #endif		
		} 
		else 
		{
			fin.seekg(fileadd);//若非'='则文件指针回到'='前的标识符
			BoolExpr();
		}
	}
	else 
	{
		BoolExpr();
	}	
}
void Semantic::BoolExpr()
{
	AdditiveExpr();
	if (token==">"|| token==">="||token=="<"||token=="<="||token=="=="||token=="!=")
	{
		string token2=token;//保存运算符
		fin>>token>>token1>>line;
		AdditiveExpr();
		if (token2==">")
		{
			fout<<"\tGT"<<endl;
			WriteCode(12);
            #ifdef DEBUG
			cout<<"\tGT"<<endl;
            #endif
		} 
		else if (token2==">=")
		{
			fout<<"\tGE"<<endl;
			WriteCode(14);
            #ifdef DEBUG
			cout<<"\tGE"<<endl;
            #endif
		}
		else if (token2=="<")
		{
			fout<<"\tLES"<<endl;
			WriteCode(13);
            #ifdef DEBUG
			cout<<"\tLES"<<endl;
            #endif
		}
		else if (token2=="<=")
		{
			fout<<"\tLE"<<endl;
			WriteCode(15);
            #ifdef DEBUG
			cout<<"\tLE"<<endl;
            #endif
		}
		else if (token2=="==")
		{
			fout<<"\tEQ"<<endl;
			WriteCode(10);
            #ifdef DEBUG
			cout<<"\tEQ"<<endl;
            #endif
		}
		else if (token2=="!=")
		{
			fout<<"\tNOTEQ"<<endl;
			WriteCode(11);
            #ifdef DEBUG
			cout<<"\tNOTEQ"<<endl;
            #endif
		}
	}
}
void Semantic::AdditiveExpr()
{
	Term();
	while (token=="+"||token=="-")
	{
		string token2=token;//保存运算符
		fin>>token>>token1>>line;
		Term();
		if (token2=="+")
		{
          fout<<"\tADD"<<endl;
		  WriteCode(4);
          #ifdef DEBUG
          cout<<"\tADD"<<endl;
          #endif
		} 
		else if (token2=="-")
		{
          fout<<"\tSUB"<<endl;
		  WriteCode(5);
          #ifdef DEBUG
          cout<<"\tSUB"<<endl;
          #endif
		} 

	}
}
void Semantic::Term()
{
	Factor();
	while (token=="*" ||token=="/")
	{
		string token2=token;	
		fin>>token>>token1>>line;
		Factor();
		if (token2=="*")
		{
          fout<<"\tMULT"<<endl;
		  WriteCode(6);
          #ifdef DEBUG
          cout<<"\tMULT"<<endl;
          #endif
		} 
		else if (token2=="/")
		{
          fout<<"\tDIV"<<endl;
		  WriteCode(7);
          #ifdef DEBUG
          cout<<"\tDIV"<<endl;
          #endif
		} 
	}
}

void Semantic::Factor()
{
	int position=-1;
	
	if (token=="(")  
	{
		fin>>token>>token1>>line;
		Expression();
		fin>>token>>token1>>line;
	} 
	else//token=="ID"||token=="NUM"
	{	 
		if(token=="ID")
		{
			Lookup(token1,0,position);
			fout<<"\tLOAD\t"<<position<<endl;	
			WriteCode(0,position);
            #ifdef DEBUG
			cout<<"\tLOAD\t"<<position<<endl;
            #endif
		}
		else
		{
			fout<<"\tLOADI\t"<<token1<<endl;

			WriteCode(1,StingToInt(token1));
            #ifdef DEBUG
			cout<<"\tLOADI\t"<<token1<<endl;
            #endif
		}
		fin>>token>>token1>>line;
	}
}

void Semantic::EnterLever()
{

	leverTable[leverTableTop].last=former;//填写上层最后一个元素位置
	leverTableTop++;
	leverTable[leverTableTop].link=curPosition;//填写新层开始位置
	former=curPosition;
}
void Semantic::QuitLever()
{
   leverTableTop--;
   former=leverTable[leverTableTop].last;
}
int Semantic::Insert(string name,int type,int obj)
{
    int endFlag;
	int i=curPosition;
    if (obj==0)
    {
		endFlag=leverTable[leverTableTop].link;//若是变量只需在本层不冲突
    }
	else endFlag=-1;//函数则查找全部
	while(i!=endFlag)
	{
		if (varTable[i].name==name&&varTable[i].obj==obj)
		{
            #ifdef DEBUG
			cout<<line<<"\t"<<"redefination '"<<name<<"'!"<<endl;
            #endif
			fwrong<<line<<"\t"<<"redefination '"<<name<<"'!"<<endl;
			return 1;//失败
		}
		else
		{
			i=varTable[i].link;
		}

	}//语法检查完毕

  curPosition++;
  varTable[curPosition].link=former;
  varTable[curPosition].name=name;
  varTable[curPosition].type=type;
  varTable[curPosition].obj=obj;
  former++;
return 0;//成功
}
int Semantic::Lookup(string name,int obj,int &idPosition)
{
    int i=curPosition;
    int endFlag=-1;//查找全部
	while(i!=endFlag)
	{
		if (varTable[i].name==name&&varTable[i].obj==obj)
		{
		    idPosition=i;
			return 0;//成功
		}
		else
		{
			i=varTable[i].link;
		}

	}
    #ifdef DEBUG
	cout<<line<<"\t"<<"Undefine ID '"<<token1<<"'!"<<endl;
    #endif
	fwrong<<line<<"\t"<<"Undefine ID '"<<token1<<"'!"<<endl;
	errorFlag=1;
    return 1;//失败
}
void Semantic::WriteCode(int operateCode,int operateNumber)//产生单操作数指令
{
  operateCodePosition++;
  Code[operateCodePosition][0]=operateCode;
  Code[operateCodePosition][1]=operateNumber;
}
void Semantic::WriteCode(int operateCode)//产生无操作数指令
{
  operateCodePosition++;
  Code[operateCodePosition][0]=operateCode;
}
void Semantic::AddJmp(int labelPositon)//用哈希函数存储跳转位置
{
  operateCodePosition++;
  JmpPosition[labelPositon]=operateCodePosition;
}
int Semantic::StingToInt(string source)
{
	int len=source.length();
	char *destination=new char[len+1];
	source.copy(destination,len,0);
	destination[len]=0;
	return atoi(destination);
 }