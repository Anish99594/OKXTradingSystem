#include <iostream>
#include <curl/curl.h>
#include "order_management.h"

std::string apiKey = "2301c886-aeef-48bb-af07-156f485f0d18";
std::string secretKey = "6ACE84DBDBB7A8246A9FDCC07579A18D";
std::string passphrase = "Anish*2000";


size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string makeRequest(const std::string& url, const std::string& data = "") {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("OK-ACCESS-KEY: " + apiKey).c_str());
        headers = curl_slist_append(headers, ("OK-ACCESS-SIGN: " + data).c_str());
        headers = curl_slist_append(headers, ("OK-ACCESS-PASSPHRASE: " + passphrase).c_str());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

void startOrderManagement() {
    std::string url = "https://www.okx.com/api/v5/market/tickers?instType=SPOT";
    std::string response = makeRequest(url);
    std::cout << "Market Tickers: " << response << std::endl;
}
