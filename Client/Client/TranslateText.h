#pragma once
#include <string>
using std::string;

class TranslateText
{
public:
	static string Translate(const string text);
	static string Translate(const string text, const string language);
};

