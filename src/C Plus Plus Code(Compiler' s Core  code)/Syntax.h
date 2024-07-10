/* Syntax.h
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
#ifndef Syntax_H_
#define Syntax_H_

#include "Head.h"
#include "Const.h"

 class Syntax
{
public:
    Syntax();
    /************************************************************************
     * <����>��{<�������>} 
     * <Programme>��{<StatementList>}
     ************************************************************************/
	int  Programme();
private:
	int line;
	int former;	
	int fileadd;	
	int errorFlag;	
 	int curPosition;
	ifstream fin;
	string token,token1;	
	/************************************************************************
     <�������>��<�������><���>|<���>
     <StatementList>��<StatementList><Statement>|<Statement>
	*************************************************************************/
	void StatementList();  
	
	/************************************************************************
     <���>��<�������>|<if���>|<while���>|<for���>|<read���>
	         |<write���>|<���ʽ���>
     <Statement>��<VarDeclare> | <IfStat>|<WhileStat>|<ForStat>|<ReadStar>
	         |<WriteStar>|<ExpressionStat>
	************************************************************************/
	void Statement();   

	/************************************************************************
	 <�������>��int <����>|int<����>=<�޷�������>
     <VarDeclare>��int ID|int ID=NUM                                       
	************************************************************************/
	void VarDeclare();  
    
	/************************************************************************/
	/* 
	<IF ���>��if (<���ʽ>) <��� > [else <��� >]
	<IfStat>��if (<Expr>) <Statement > [else < Statement >]                 */
	/************************************************************************/
	void IfStat();          
	
	/************************************************************************/
	/* <while���>��while(<���ʽ>) <���>
       <WhileStat>��While (<Expr >) < Statement >                           */
	/************************************************************************/
	void WhileStat();       
	
	/************************************************************************/
	/*  <for���>��for(<���ʽ>;<���ʽ>;<���ʽ>) <��� >
        <ForStat>��For(<Expr>,<Expr>,<Expr>)<Statement>                     */
	/************************************************************************/
	void ForStat();        

	/************************************************************************/
	/* <write_���>��write <���ʽ>;
       <WriteStat>��Write <Expression>;                                     */
	/************************************************************************/
	void WriteStat();      
	
	/************************************************************************/
	/* <read_���>��read <����>;
       <ReadStat>��Read <ID>;                                               */
	/************************************************************************/
	void ReadStat();        
	void SentenceBody();
	/************************************************************************/
	/*  <���ʽ���>��<<���ʽ>;|;
        <ExpressionStat>��<Expression>;|;                                   */
	/************************************************************************/
	void ExpressionStat();  
	/************************************************************************/
	/*  <���ʽ>��<��ʶ��>=<�������ʽ>|<�������ʽ>
        <Expr>��ID=<BoolExpr>|<BoolExpr>                                    */
	/************************************************************************/	
	void Expression();      
	
	/************************************************************************/
	/* <�������ʽ>��<�������ʽ>|<�������ʽ>(>|<|>=|<=|==|!=)<�������ʽ>
       <BoolExpr>��<AdditiveExpr>|< AdditiveExpr >(>|<|>=|<=|==|!=)< AdditiveExpr >*/
	/************************************************************************/
	void BoolExpr();        

	/************************************************************************/
	/* <�������ʽ>��<��>{(+|-)<��>}
       <AdditiveExpr>��<Term>{(+|-)< Term >}                                */
	/************************************************************************/
	void AdditiveExpr();    
    
	/************************************************************************/
	/* <��>��<����>{(*|/)<����>}
       < Term >��<Factor>{(*| /)< Factor >}                                 */
	/************************************************************************/
	void Term();           

	/************************************************************************/
	/* <����>��(<�������ʽ>)|<��ʶ��>|<�޷�������>
       < Factor >��(<AdditiveExpr>)| ID|NUM                                 */
	/************************************************************************/
	void Factor();
	
	void EnterLever();
	void QuitLever();
	int  Insert(string name,int type,int obj);       //����ͻ0 ����ͻ1
 	int  Lookup(string name,int obj,int idPosition); //����0 ��û��1

};

#endif
