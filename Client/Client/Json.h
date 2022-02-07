#pragma once
#include <string>
using namespace std;



class Json
{
public:
	static string ParseYandexTranslate(const u8string text);
	static string StringifyYandexTranslate(const string text);
	static string StringifyYandexTranslate(const string text, const string language);
	struct TranslateText {
		string text;
		string detectedLanguageCode;
	};
};

