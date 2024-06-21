//
// Created by 26bon on 2/12/2024.
//

#ifndef COOL_PROJECT_SMART_CURL_H
#define COOL_PROJECT_SMART_CURL_H

#include <curl/curl.h>
#include <string>

class SmartCurl
{
public:
    SmartCurl(const std::string& url_);
    ~SmartCurl();

    bool isValidExecutable();

    // returns the absolute path of the fetched file
    std::string fetchData(const std::string& dest_);

private:

    // get the filename out of the url
    const std::string& extractFileName();
    
    CURL* _curl;
    CURLcode _res;
    std::string _response;
    std::string _url;
    bool _url_exists = false;
    std::string _filename;
};


#endif //COOL_PROJECT_SMART_CURL_H
