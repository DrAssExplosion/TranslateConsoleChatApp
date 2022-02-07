#define CURL_STATICLIB 
#include <iostream>
#include <string>

#include "curl/curl.h"
#include "TranslateText.h"
#include "Console.h"
#include "Json.h"


#ifdef _DEBUG
#pragma comment(lib, "curl/libcurl_a_debug.lib" )
#else
#pragma comment(lib, "curl/libcurl_a.lib" )
#endif

#pragma comment(lib, "Wldap32.lib" )
#pragma comment(lib, "Crypt32.lib" )
#pragma comment(lib, "Normaliz.lib" )
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma execution_character_set( "utf-8" )
using namespace std;


static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
	string& text = *static_cast<string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}


string TranslateText::Translate(const string text) {
	string result = TranslateText::Translate(text, Console::_language);
	return result;
};
string TranslateText::Translate(const string text, const string language) {
	u8string response;
	CURL* curl = curl_easy_init();

	struct curl_slist* headers = NULL;
	string token_header = "Authorization: Bearer " + Console::_accessToken; // access_token is keyword 
	string jsonstr = Json::StringifyYandexTranslate(text, language);

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://translate.api.cloud.yandex.net/translate/v2/translate"); // Url
		curl_easy_setopt(curl, CURLOPT_POST, 1L); // POST

		/* Header */
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, token_header.c_str()); // Token
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		/* BODY JSON DATA */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)jsonstr.size()); // Size
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonstr.c_str()); // Data

		/* Other */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		// curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // LOG

		curl_easy_perform(curl);
		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
	};
	// cout << jsonstr << endl;
	return Json::ParseYandexTranslate(response);
}
