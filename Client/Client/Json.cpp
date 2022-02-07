#include <iostream>
#include <string>
#include <Windows.h>
#include <locale>
#include <codecvt>
#include "nlohmann/json.hpp"
#include "Json.h"
#include "Console.h"
#pragma execution_character_set( "utf-8" )
using json = nlohmann::json;

using namespace std;

void from_json(const json& j, Json::TranslateText& p) {
	j.at("text").get_to(p.text);
	j.at("detectedLanguageCode").get_to(p.detectedLanguageCode);
}

template <typename T, size_t N>
void from_json(const json& j, T(&t)[N]) {
	if (j.size() > N) {
		throw std::runtime_error("JSON array too large");
	}
	size_t index = 0;
	for (auto& item : j) {
		from_json(item, t[index++]);
	}
}


string cp1251_to_utf8(const char* str) {
	string res;
	int result_u, result_c;
	result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
	if (!result_u) { return 0; }
	wchar_t* ures = new wchar_t[result_u];
	if (!MultiByteToWideChar(1251, 0, str, -1, ures, result_u)) {
		delete[] ures;
		return 0;
	}
	result_c = WideCharToMultiByte(65001, 0, ures, -1, 0, 0, 0, 0);
	if (!result_c) {
		delete[] ures;
		return 0;
	}
	char* cres = new char[result_c];
	if (!WideCharToMultiByte(65001, 0, ures, -1, cres, result_c, 0, 0)) {
		delete[] cres;
		return 0;
	}
	delete[] ures;
	res.append(cres);
	delete[] cres;
	return res;
}



string Json::StringifyYandexTranslate(const string text) {
	string translatedText = StringifyYandexTranslate(text, Console::_language);
	return translatedText;
}

string Json::StringifyYandexTranslate(const string text, const string language) {
	const char* tt = text.c_str();
	string newText = cp1251_to_utf8(tt);
	// return "\{\"targetLanguageCode\":\"" + language + "\",\"format\"\:\"PLAIN_TEXT\",\"texts\":\[\"" + text + "\"\],\"folderId\":\"b1gc2r4pbtafhe8v20ms\"\}";
	 json jsonResp{};
	 // jsonResp["sourceLanguageCode"] = Console::GetLanguage();// язык, на котором написан исходный текст. 
	 jsonResp["targetLanguageCode"] = language; // язык, на который переводитс€ текст.
	 jsonResp["format"] = "PLAIN_TEXT"; // ‘ормат текста.
	 jsonResp["texts"] = { newText }; // ћассив строк дл€ перевода. 
	 jsonResp["folderId"] = Console::_folderIdTranslate; // »дентификатор каталога, к которому у вас есть доступ.
	 return jsonResp.dump();
}



string Json::ParseYandexTranslate(const u8string text) {
	json jsonResp = json::parse(text);
	TranslateText parsed[1];
	from_json(jsonResp["translations"], parsed);

	return parsed[0].text;
}