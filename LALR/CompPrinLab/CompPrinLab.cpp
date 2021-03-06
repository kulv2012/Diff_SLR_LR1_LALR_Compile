// CompPrinLab.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
#include "WordAnalyzer.h"
#include "GrammerAnalyzer.h"
#include "InforPrinter.h"
#include <Windows.h>

////////////////////--Kulv--2010/12/10---10:52:41--///////////////////////
//global of information out print object 
InforPrinter *outer = InforPrinter::MyCreateInstance() ;
////////////////////--Kulv--2010/12/10---11:19:17--///////////////////////

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//(*outer).SetPrintState(false) ;
	char str[16] ; 
	SYSTEMTIME begtime  ;
	GetLocalTime(&begtime) ;
	WordAnalyzer wordAnalyzer( string(".\\Shared\\CodeFile.cpp") ) ;
	 (*outer)  << "begin to word analyze ````" << myendl  ;
	if ( wordAnalyzer.RetrivalCode() == true ) {
		 (*outer)  << "RetrivalCode finished !\n"<< myendl ;
	}
	else {
		 (*outer) << "RetrivalCode error !"<< myendl  ;
		return -1 ;
	}
	wordAnalyzer.LaunchAnalyze() ;
	(*outer) << "Word Analyze Succeed !" << myendl ;
	////////////////////--Kulv--2010/12/13---21:52:58--///////////////////////
	GrammerAnalyzer grammerAnalyzer(wordAnalyzer.GetTokenFile()) ;
	(*outer)  << "Begin Loading C Grammar···"<< myendl; 
	grammerAnalyzer.LoadGrammer( ) ;

	grammerAnalyzer.SelfPrepare() ;

	(*outer) << "\n\nBroadcast Information:\n" ;
	grammerAnalyzer.GetBroadcastsInfo() ;

	(*outer) << "\n\nBegin Broadcast :\n" ;
	grammerAnalyzer.BeginBroadcast() ;

	(*outer) << "\n\nBuild Action ,Goto Chart !\n" ;
	grammerAnalyzer.Build_ACTION_GOTO() ;

	grammerAnalyzer.SaveActionGoto() ;
	(*outer)  << "\n\n\t\tGrammar Computer Succeeded !\n" << myendl  ;
	
	(*outer) << "\t\tStates is :\n"<< myendl ;
	grammerAnalyzer.PrintAllStates(true) ;
	/*(*outer) << "\n\nBegin Analysis!\n" ;
	grammerAnalyzer.BeginAnalyze() ;

	if ( grammerAnalyzer.GetGrammarResult() == 0 ) {
		(*outer) << "\n\t\tGrammar Analysis Succeed ! Your code is legal !\n\n" << myendl ;
	}
	else{
		(*outer) << "\n\t\tGrammar Analysis Faild ! Your code is illegal !\n\n" << myendl ;
		(*outer) << "\t\t\terror count is : " << grammerAnalyzer.GetGrammarResult()<<myendl ;
	}*/
	//(*outer).SetPrintState(true) ;
	sprintf_s(str,"%d:%d:%d" ,begtime.wHour,begtime.wMinute,begtime.wSecond ) ;
	(*outer) << "Begin Time : \t"<<str << myendl ;
	GetLocalTime(&begtime) ;
	sprintf_s(str,"%d:%d:%d" ,begtime.wHour,begtime.wMinute,begtime.wSecond ) ;
	(*outer) << "End Time : \t"<<str << myendl ;

	(*outer) << "\nend " << myendl ;
	return 0;
}


