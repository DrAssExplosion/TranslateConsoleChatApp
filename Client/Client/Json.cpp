#include "Json.h"
#include "Console.h"
#include <iostream>
#include <string>
#include "nlohmann/json.hpp"

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




string Json::StringifyYandexTranslate(const string& text) {
	json jsonResp{};
	// jsonResp["sourceLanguageCode"] = Console::GetLanguage();// язык, на котором написан исходный текст. 
	jsonResp["targetLanguageCode"] = Console::_language; // язык, на который переводитс€ текст.
	jsonResp["format"] = "PLAIN_TEXT"; // ‘ормат текста.
	jsonResp["texts"] = { text }; // ћассив строк дл€ перевода. 
	jsonResp["folderId"] = Console::_folderIdTranslate; // »дентификатор каталога, к которому у вас есть доступ.
	return jsonResp.dump();
}



string Json::ParseYandexTranslate(const string& text) {
	json jsonResp = json::parse(text);
	TranslateText parsed[1];
	from_json(jsonResp["translations"], parsed);

	return parsed[0].text;
}