/* Vocable.cpp
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
#include"Vocable.h"

Scan::Scan(char *FileName)
{
	es=0;
	line=1;
	myFileName=FileName;
};
int Scan:: main_scan()
{
    
   if ((fin=fopen(myFileName,"r"))==NULL) //�ж������ļ����Ƿ���ȷ
   {
      # ifdef DEBUG
	   cout<<"\n�򿪴ʷ����������ļ�����!\n";
      # endif
	  return 1;//�����ļ������ش������1
   }
   if ((fout=fopen("vocable","w"))==NULL) //�ж�����ļ����Ƿ���ȷ
   {
      # ifdef DEBUG
	    cout<<"\n�����ʷ���������ļ�����!\n";
      # endif
	  
	  return 2; //����ļ������ش������2
   }
   if (!fwrong.is_open()) //�ж�����ļ����Ƿ���ȷ
   {
      # ifdef DEBUG
	    cout<<"\n�򿪴�������ļ�����!\n";
      # endif
	  
	  return 3; //����ļ������ش������2
    }
   ch=getc(fin);
   while (ch!=EOF)
   {
	  while (ch==' '||ch=='\n'||ch=='\t')
	  {
		  if (ch=='\n') {line++;}
		  ch=getc(fin);
	  }
	  if (ch==EOF) break;
	  switch(contral_dealwith()) 
	   {
		case 1:    alphabet();
				   break;
		case 2:    digit();
				   break;
		case 3:    singleword_only();
				   break;
		case 4:    doubleword_only();
				   break;
		case 5:    comment();
				   break;
		default:   error_dealwith();			   

	   }
   }
   fclose(fin);//�ر���������ļ�
   fclose(fout);
   return(es);  //����������
           
}

int Scan:: contral_dealwith()
{
   if (isalpha(ch))                      return 1;
   else if(isdigit(ch))                  return 2;
   else if(strchr(singleword,ch)>0)      return 3;
   else if(strchr(doubleword,ch)>0)      return 4;
   else if(ch=='/')                      return 5;
   else                                  return 6;                        
}
void Scan:: alphabet()//1
{
	 token[0]=ch; j=1;
	 ch=getc(fin);
	 while(isalnum(ch))  //�������ĸ��������ϱ�ʶ��������������ʶ����Ͻ���
	 {
		token[j++]=ch;  //��ϵı�ʶ��������token��
		ch=getc(fin);  //����һ���ַ�
	 }
	 token[j]='\0';  //��ʶ����Ͻ���	 

	 //���������������������������鱣���֣���������������������
	 n=0;
	 while ((n<keywordSum) && strcmp(token,keyword[n])) n++;
	 if (n>=keywordSum)  //���Ǳ����֣������ʶ��
	 {
		 fprintf(fout,"%s\t%s\t%d\n","ID",token,line);  //�����ʶ������
	 }
	else//�Ǳ����֣����������
	{
		fprintf(fout,"%s\t%s\t%d\n",token,token,line);  //��������ַ���
	}
}
void Scan:: digit()//2
{
	 token[0]=ch; j=1;
	 ch=getc(fin);  //����һ���ַ�
	 while (isdigit(ch))  //�����������������������������������Ͻ���
	 {
		token[j++]=ch;  //�������������token��
		ch=getc(fin);  //����һ���ַ�
	 }
	 token[j]='\0';  //������Ͻ���		 
	 fprintf(fout,"%s\t%s\t%d\n","NUM",token,line);  //�����������
}
void Scan:: singleword_only()//3
{
	 token[0]=ch; token[1]='\0';
	 ch=getc(fin);//����һ�������Ա�ʶ����һ������
	 fprintf(fout,"%s\t%s\t%d\n",token,token,line);  //������ֽ������
}
void Scan:: doubleword_only()//4
{
	 token[0]=ch;
	 ch=getc(fin);  //����һ���ַ��ж��Ƿ�Ϊ˫�ֽ��
	 if (ch=='=')  //�����=�����˫�ֽ��
	 {
		token[1]=ch;token[2]='\0';  //���˫�ֽ������
		ch=getc(fin);  //����һ�������Ա�ʶ����һ������
	 } 
	 else//����=��Ϊ���ֽ��
	 token[1]='\0';
	 fprintf(fout,"%s\t%s\t%d\n",token,token,line);  //�������˫�ֽ������
}
void Scan:: comment()//5
{
   	 ch=getc(fin);  //����һ���ַ�
	 if (ch=='*')  //�����*����ʼ����ע��
	 {  
		char ch1;
		ch1=getc(fin);  //����һ���ַ�
		do{
			ch=ch1;
			if (ch1=='\n')
			{
				line++;
			}
			ch1=getc(fin);
		}while ((ch!='*' || ch1!='/')&&ch1!=EOF);  //ֱ������ע�ͽ�����*/���ļ�β +++//ɾ��ע��+++

		ch=getc(fin);//����һ�������Ա�ʶ����һ������
	 } 
	 else  //����*�����ֽ��/
	 {
		 token[0]='/'; token[1]='\0';
		 fprintf(fout,"%s\t%s\t%d\n",token,token,line);  //������ֽ��/
	 }
}
void Scan:: error_dealwith()//6
{
	 token[0]=ch;token[1]='\0';
	 ch=getc(fin);//����ռ�����ֽ�
	 ch=getc(fin);  //����һ�������Ա�ʶ����һ������

	 es=3;  //���ô������
	 fwrong<<line<<"\tUnkown character!"<<endl; //����������
     # ifdef DEBUG
	 cout<<line<<"\tUnkown character!"<<endl;
     # endif
}
