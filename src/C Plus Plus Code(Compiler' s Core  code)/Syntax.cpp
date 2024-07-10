/* Syntax.cpp
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
#include"Syntax.h"

Syntax::Syntax()
{
	line=1;
	fileadd=0;
	errorFlag=0;
	former=-1;
	curPosition=-1;   
	leverTableTop=0;    

	varTable[0].link=-1;
    leverTable[leverTableTop].link=-1;
	for (int i=0;i<varTableLength;i++)//��ʼ�����ű�
	{
		varTable[i].name=" ";
		varTable[i].address=INT_MIN;
	}
	fin.open("vocable",ios_base::in);
}

int Syntax::Programme()
{
   if (!fin.is_open()) //�ж������ļ����Ƿ��
   {
      # ifdef DEBUG
	   cout<<"\n�򿪴ʷ���������ļ�����!\n";
      # endif
	  return 4;//�����ļ������ش������1
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
   fin.close();
   return errorFlag;
}
void Syntax::StatementList()
{	
	while (token!="}")
	{
		Statement();
		if(fin.eof()){break;}
	}
}
void Syntax::Statement()
{
	if (token=="int")         VarDeclare();   //�������
	else if ( token=="if")    IfStat();       //<IF���>
	else if (token=="while")  WhileStat();    //<while���>
	else if (token=="for")    ForStat();      //<for���>
	else if (token=="read")   ReadStat();     //<read���>
	else if (token=="write")  WriteStat();    //<write���>
	else if (token=="ID"||token=="NUM"||token=="(")  ExpressionStat();//<���ʽ���>
	else 	return;
}

void Syntax::SentenceBody()
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
void Syntax::VarDeclare()
{
	int fileadd=fin.tellg();//��ס��ǰ�ļ�λ��
	fin>>token>>token1>>line;

	if (token!="ID")	 //���Ǳ�ʶ��
	{
		errorFlag=1;
        #ifdef DEBUG
		cout<<line<<"\tShort ID!"<<endl;
        #endif
		fwrong<<line<<"\tShort ID!"<<endl;
	}
	else 
	{
		Insert(token1,1,0);//������ű�
    	fin>>token>>token1>>line;
	}
	if (token=="=")
	{
       fin.seekg(fileadd);//��Ϊ'='���ļ�ָ��ص�'ID'ǰ�ı�ʶ�� ���б��ʽ����
       fin>>token>>token1>>line;
	   Expression();
	}
	if (token!=";")	 
	{
		errorFlag=1;
        #ifdef DEBUG
		cout<<line<<"\tmiss';'!"<<endl;
        #endif
		fwrong<<line<<"\tmiss';'!"<<endl;
	}
	else 
	{
		fin>>token>>token1>>line;
	}	
}
void Syntax::IfStat()
{
	fin>>token>>token1>>line;
	if (token!="(")	
	{
		errorFlag=1;
        #ifdef DEBUG
		cout<<line<<"\tmiss '('!"<<endl;
        #endif
		fwrong<<line<<"\tmiss '('!"<<endl;
	}
	else 
	{
		fin>>token>>token1>>line;
	}
	Expression();
	if (token!=")") 
	{
	 errorFlag=1;
     #ifdef DEBUG
	 cout<<line<<"\tmiss ')'!"<<endl;
     #endif
	 fwrong<<line<<"\tmiss ')'!"<<endl;
	}
	else
	{
		fin>>token>>token1>>line;
	}
    SentenceBody();
	if (token=="else")//else���ִ���
	{ 
		fin>>token>>token1>>line;
        SentenceBody();
	}
}
void Syntax::WhileStat()
{  
	fin>>token>>token1>>line;
	if (token!="(") //��������
	{
		errorFlag=1;
        #ifdef DEBUG
		cout<<line<<"\tmiss '('!"<<endl;
        #endif
		fwrong<<line<<"\tmiss '('!"<<endl;
	}
	else
	{
	 fin>>token>>token1>>line;
	}
	Expression();
	if (token!=")")  //��������
	{
		errorFlag=1;
        #ifdef DEBUG
		cout<<line<<"\tmiss ')'!"<<endl;
        #endif
		fwrong<<line<<"\tmiss ')'!"<<endl;
	}
	else
	{
		fin>>token>>token1>>line;
	}
	SentenceBody();
}
void Syntax::ForStat()
{ 
	fin>>token>>token1>>line;
	if (token!="(") //��������
	{
	  errorFlag=1;  
      #ifdef DEBUG
	  cout<<line<<"\tmiss '('!"<<endl;
      #endif
	  fwrong<<line<<"\tmiss '('!"<<endl;
	}
	else
	{
	 fin>>token>>token1>>line;
	}
	if (token=="int")
	{
	 fin>>token>>token1>>line;
	 if (token!="ID")
	 {
 	  errorFlag=1;  
      #ifdef DEBUG
	  cout<<line<<"\tmiss 'ID'!"<<endl;
      #endif
	  fwrong<<line<<"\tmiss 'ID'!"<<endl;      
	 }
	 else
	 {	 
		 Insert(token1,1,0); 
	 }
     Expression();
	}
	else{Expression();}
	if (token!=";")
	{ 
		errorFlag=1;
        #ifdef DEBUG
		cout<<line<<"\tmiss ';'!"<<endl;
        #endif
		fwrong<<line<<"\tmiss ';'!"<<endl;
	} //�ٷֺ�
	else
	{	
		fin>>token>>token1>>line;
	}
	Expression();
	if (token!=";")
	{
		errorFlag=1; 
        #ifdef DEBUG
		cout<<line<<"\tmiss ';'!"<<endl;
        #endif
		fwrong<<line<<"\tmiss ';'!"<<endl;
	} 
	else
	{
	 fin>>token>>token1>>line;
	}
	Expression();
	if (token!=")") 
	{ 
		errorFlag=1; 
        #ifdef DEBUG
		cout<<line<<"\tmiss ')'!"<<endl;
        #endif
		fwrong<<line<<"\tmiss ')'!"<<endl;
	}//��������
	else
	{
	 fin>>token>>token1>>line;
	}
	SentenceBody();
}

void Syntax::WriteStat()
{
	fin>>token>>token1>>line;
	Expression();
	if (token!=";") 
	{ 
		errorFlag=1;
        #ifdef DEBUG
		cout<<line<<"\tmiss';'!"<<endl;
        #endif
		fwrong<<line<<"\tmiss';'!"<<endl;
	}//�ٷֺ�
	else
	{
		fin>>token>>token1>>line;
	}
}
void Syntax::ReadStat()
{
	int position=-1;
	fin>>token>>token1>>line;
	Lookup(token1,0,position);
	if (token!="ID")
	{ 
		errorFlag=1;
        #ifdef DEBUG
		cout<<line<<"\tmiss 'ID'!"<<endl;
        #endif
		fwrong<<line<<"\tmiss 'ID'!"<<endl;
	} //�ٱ�ʶ��
	else
	{
		fin>>token>>token1>>line;
	}
	if (token!=";") 
	{ 
		errorFlag=1; 
        #ifdef DEBUG
		cout<<line<<"\tmiss';'!"<<endl;
        #endif
		fwrong<<line<<"\tmiss';'!"<<endl;
	}  //�ٷֺ�
	else
	{
		fin>>token>>token1>>line;
	}
}
void Syntax::ExpressionStat()
{
	if (token==";")
	{
		fin>>token>>token1>>line;
		return;
	}
	Expression();
	if ( token==";") 
	{
		fin>>token>>token1>>line;
	}

	else
	{
	    errorFlag=1;
        #ifdef DEBUG
		cout<<line<<"\tmiss';'!"<<endl;
        #endif
 		fwrong<<line<<"\tmiss';'!"<<endl;
	}
}
void Syntax::Expression()
{
	int fileadd,position=-1;
	string token2,token3;
	if (token=="ID")
	{   
        fileadd=fin.tellg();//��ס��ǰ�ļ�λ��
	    fin>>token2>>token3>>line;
		if (token2=="=")  //'='
		{
			Lookup(token1,0,position);
			fin>>token>>token1>>line;
			BoolExpr();
		} 
		else 
		{
			fin.seekg(fileadd);//����'='���ļ�ָ��ص�'='ǰ�ı�ʶ��
			BoolExpr();
		}
	}
	else 
	{
		BoolExpr();
	}	
}
void Syntax::BoolExpr()
{
	AdditiveExpr();
	if (token==">"|| token==">="||token=="<"||token=="<="||token=="=="||token=="!=")
	{
		fin>>token>>token1>>line;
		AdditiveExpr();
	}
}
void Syntax::AdditiveExpr()
{
	Term();
	while (token=="+"||token=="-")
	{
		fin>>token>>token1>>line;
		Term();
	}
}
void Syntax::Term()
{
	Factor();
	while (token=="*" ||token=="/")
	{
		fin>>token>>token1>>line;
		Factor();
	}
}

void Syntax::Factor()
{
	int position=-1;
	
	if (token=="(")  
	{
		fin>>token>>token1>>line;
		Expression();
		if (token!=")") 
		{ 
			errorFlag=1;
            #ifdef DEBUG
			cout<<line<<"\tmiss')'!"<<endl;
            #endif
			fwrong<<line<<"\tmiss')'!"<<endl;
		}
		else
		{
		 fin>>token>>token1>>line;
		}
	} 
	else
	{	
		if (token=="ID"||token=="NUM")
		{   
			if(token=="ID")
			{
				Lookup(token1,0,position);
			}
			fin>>token>>token1>>line;
		} 
		else
		{
            #ifdef DEBUG
			cout<<line<<"\tmiss operator number!"<<endl;
            #endif
			fwrong<<line<<"\tmiss operator number!"<<endl;
			errorFlag=1; 
		}
	}
}

void Syntax::EnterLever()
{

	leverTable[leverTableTop].last=former;//��д�ϲ����һ��Ԫ��λ��
	leverTableTop++;
	leverTable[leverTableTop].link=curPosition;//��д�²㿪ʼλ��
	former=curPosition;
}
void Syntax::QuitLever()
{
   leverTableTop--;
   former=leverTable[leverTableTop].last;
}
int Syntax::Insert(string name,int type,int obj)
{
    int endFlag;
	int i=curPosition;
    if (obj==0)
    {
		endFlag=leverTable[leverTableTop].link;//���Ǳ���ֻ���ڱ��㲻��ͻ
    }
	else endFlag=-1;//���������ȫ��
	while(i!=endFlag)
	{
		if (varTable[i].name==name&&varTable[i].obj==obj)
		{
            #ifdef DEBUG
			cout<<line<<"\t"<<"redefination '"<<name<<"'!"<<endl;
            #endif
			fwrong<<line<<"\t"<<"redefination '"<<name<<"'!"<<endl;
			errorFlag=1;
			return 1;//ʧ��
		}
		else
		{
			i=varTable[i].link;
		}

	}//�﷨������

  curPosition++;
  varTable[curPosition].link=former;
  varTable[curPosition].name=name;
  varTable[curPosition].type=type;
  varTable[curPosition].obj=obj;
  former++;
return 0;//�ɹ�
}
int Syntax::Lookup(string name,int obj,int idPosition)
{
    int i=curPosition;
    int endFlag=-1;//����ȫ��
	while(i!=endFlag)
	{
		if (varTable[i].name==name&&varTable[i].obj==obj)
		{
		    idPosition=i;
			return 0;//�ɹ�
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
    return 1;//ʧ��
}