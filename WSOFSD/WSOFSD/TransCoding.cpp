#include "stdafx.h"
#include "TransCoding.h"


CTransCoding::CTransCoding()
{
}


CTransCoding::~CTransCoding()
{
}

std::wstring CTransCoding::Ansi2Unicode(const std::string str)
{
	int len = str.length();
	int unicodeLen = ::MultiByteToWideChar(CP_ACP,0,str.c_str(),-1,NULL,0);
	wchar_t *pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP,0,str.c_str(),-1,pUnicode,unicodeLen);

	std::wstring rt(pUnicode);
	delete []pUnicode;

	return  rt;
}

std::string CTransCoding::Unicode2Ansi(const std::wstring str)
{
	int AnsiLen = ::WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
	char *pANSI = new char[AnsiLen + 1];
	memset(pANSI, 0, (AnsiLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, pANSI, AnsiLen, NULL, NULL);

	std::string rt(pANSI);
	delete[]pANSI;

	return  rt;
}

std::wstring CTransCoding::UTF82Unicode(const std::string str)
{
	int len = str.length();
	int unicodeLen = ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, pUnicode, unicodeLen);

	std::wstring rt(pUnicode);
	delete[]pUnicode;

	return  rt;
}

std::string CTransCoding::Unicode2UTF8(const std::wstring str)
{
	int UTF8Len = ::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
	char *pUTF8 = new char[UTF8Len + 1];
	memset(pUTF8, 0, (UTF8Len + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, pUTF8, UTF8Len, NULL, NULL);

	std::string rt(pUTF8);
	delete[]pUTF8;

	return  rt;
}
