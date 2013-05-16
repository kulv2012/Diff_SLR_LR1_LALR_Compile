#include "StdAfx.h"
#include "SymbolTable.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;


////////////////////--Kulv--2010/11/25---11:17:11--///////////////////////
SymbolItem::SymbolItem()
:m_nId(-1)
, m_nFristLine(0) 
{

}
////////////////////--Kulv--2010/11/25---11:17:08--///////////////////////
////////////////////--Kulv--2010/11/25---11:17:05--///////////////////////
SymbolTable::SymbolTable(void)
:m_nIdtfSub(0) 
{
	LoadKeyWord() ;
	LoadOpSp() ;
}

SymbolTable::~SymbolTable(void)
{
	SaveSymbolTable() ;
}

bool SymbolTable::LoadKeyWord(void)
{
	//string infile(KEY_WORD_FILE) ;
	ifstream kwfile( KEY_WORD_FILE /*infile.c_str() */,ios::in) ;
	if (!kwfile) {//if orror,then exit
		throw "file open error in LoadKeyWord !" ;
	}
	size_t sub = 0 ;
	string key ;
	while ( kwfile >> key )
	{
		if ( 0 == m_hmKeyWord.count(key) ) {
			m_hmKeyWord[key] = sub++ ;
		}
	}
	kwfile.close() ;
	/*stdext::hash_map<string, size_t>::const_iterator iter = m_hmKeyWord.begin();
	while ( iter != m_hmKeyWord.end() )
	{
		 (*outer)  << iter->first << myendl  ;
		iter ++ ;
	}*/
	return true;
}

bool SymbolTable::LoadOpSp(void)
{
	ifstream osfile( OPERATOR_SPERATOR_FILE ,ios::in) ;
	if (!osfile) {//if orror,then exit
		throw "file open error in LoadOpSp !" ;
	}
	size_t sub = 16 ;
	string str ;
	while ( osfile >> str )
	{
		if ( 0 == m_hmOpSp.count( str ) ) {
			m_hmOpSp[ str ] = sub++ ;
		}
	}
	osfile.close() ;
	return true;
}

bool SymbolTable::SaveSymbolTable(void)
{
	ofstream sbfile( SYMBOL_ITEM_FILE ,ios::out) ;
	if (!sbfile) {//if orror,then exit
		throw "file open error in SaveSymbolTable !" ;
	}
	
	stdext::hash_map<string, SymbolItem>::const_iterator iter = m_hmIdentfy.begin();
	while ( iter != m_hmIdentfy.end() )
	{
		sbfile << iter->first << "\t"<<iter->second.m_nId << " " << iter->second.m_nFristLine << endl  ;
		iter ++ ;
	}

	sbfile.close() ;
	return true;
}
