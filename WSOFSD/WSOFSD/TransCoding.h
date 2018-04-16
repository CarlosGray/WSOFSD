#pragma once
#include <iostream>
class CTransCoding
{
private:
	CTransCoding();
	~CTransCoding();

public:
	static std::wstring Ansi2Unicode(const std::string str);
	static std::string Unicode2Ansi(const std::wstring str);
	static std::wstring UTF82Unicode(const std::string str);
	static std::string Unicode2UTF8(const std::wstring str);
};

