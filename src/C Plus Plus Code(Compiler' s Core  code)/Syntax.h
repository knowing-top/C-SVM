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
#ifndef Syntax_H_
#define Syntax_H_

#include "Head.h"
#include "Const.h"

 class Syntax
{
public:
    Syntax();
    /************************************************************************
     * <程序>→{<语句序列>} 
     * <Programme>→{<StatementList>}
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
     <语句序列>→<语句序列><语句>|<语句>
     <StatementList>→<StatementList><Statement>|<Statement>
	*************************************************************************/
	void StatementList();  
	
	/************************************************************************
     <语句>→<声明语句>|<if语句>|<while语句>|<for语句>|<read语句>
	         |<write语句>|<表达式语句>
     <Statement>→<VarDeclare> | <IfStat>|<WhileStat>|<ForStat>|<ReadStar>
	         |<WriteStar>|<ExpressionStat>
	************************************************************************/
	void Statement();   

	/************************************************************************
	 <声明语句>→int <变量>|int<变量>=<无符号整数>
     <VarDeclare>→int ID|int ID=NUM                                       
	************************************************************************/
	void VarDeclare();  
    
	/************************************************************************/
	/* 
	<IF 语句>→if (<表达式>) <语句 > [else <语句 >]
	<IfStat>→if (<Expr>) <Statement > [else < Statement >]                 */
	/************************************************************************/
	void IfStat();          
	
	/************************************************************************/
	/* <while语句>→while(<表达式>) <语句>
       <WhileStat>→While (<Expr >) < Statement >                           */
	/************************************************************************/
	void WhileStat();       
	
	/************************************************************************/
	/*  <for语句>→for(<表达式>;<表达式>;<表达式>) <语句 >
        <ForStat>→For(<Expr>,<Expr>,<Expr>)<Statement>                     */
	/************************************************************************/
	void ForStat();        

	/************************************************************************/
	/* <write_语句>→write <表达式>;
       <WriteStat>→Write <Expression>;                                     */
	/************************************************************************/
	void WriteStat();      
	
	/************************************************************************/
	/* <read_语句>→read <变量>;
       <ReadStat>→Read <ID>;                                               */
	/************************************************************************/
	void ReadStat();        
	void SentenceBody();
	/************************************************************************/
	/*  <表达式语句>→<<表达式>;|;
        <ExpressionStat>→<Expression>;|;                                   */
	/************************************************************************/
	void ExpressionStat();  
	/************************************************************************/
	/*  <表达式>→<标识符>=<布尔表达式>|<布尔表达式>
        <Expr>→ID=<BoolExpr>|<BoolExpr>                                    */
	/************************************************************************/	
	void Expression();      
	
	/************************************************************************/
	/* <布尔表达式>→<算术表达式>|<算术表达式>(>|<|>=|<=|==|!=)<算术表达式>
       <BoolExpr>→<AdditiveExpr>|< AdditiveExpr >(>|<|>=|<=|==|!=)< AdditiveExpr >*/
	/************************************************************************/
	void BoolExpr();        

	/************************************************************************/
	/* <算术表达式>→<项>{(+|-)<项>}
       <AdditiveExpr>→<Term>{(+|-)< Term >}                                */
	/************************************************************************/
	void AdditiveExpr();    
    
	/************************************************************************/
	/* <项>→<因子>{(*|/)<因子>}
       < Term >→<Factor>{(*| /)< Factor >}                                 */
	/************************************************************************/
	void Term();           

	/************************************************************************/
	/* <因子>→(<算术表达式>)|<标识符>|<无符号整数>
       < Factor >→(<AdditiveExpr>)| ID|NUM                                 */
	/************************************************************************/
	void Factor();
	
	void EnterLever();
	void QuitLever();
	int  Insert(string name,int type,int obj);       //不冲突0 ，冲突1
 	int  Lookup(string name,int obj,int idPosition); //含有0 ，没有1

};

#endif
