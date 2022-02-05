#pragma once
#include <string>
using namespace std;



class Json
{
public:
	static string ParseYandexTranslate(const string& text);
	static string StringifyYandexTranslate(const string& text);
	struct TranslateText {
		string text;
		string detectedLanguageCode;
	};
};

