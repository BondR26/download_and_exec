//
// Created by 26bon on 2/12/2024.
//
#include <iostream>
#include <filesystem>
#include <string>
#include <algorithm>
#include <fstream>

#include "smart_curl.h"


size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *data)
{
    data->append((char*)contents, size * nmemb);
    return size * nmemb;
}

SmartCurl::SmartCurl(const std::string& url_) : _url(url_)
{
    _curl = curl_easy_init();

    if (_curl)
    {
        curl_easy_setopt(_curl, CURLOPT_URL, url_.c_str());
        curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_response);
        curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    }
    else
    {
        std::cout << "Error initializing curl." << std::endl;
    };
}

SmartCurl::~SmartCurl()
{
    curl_easy_cleanup(_curl);
}

bool SmartCurl::isValidExecutable()
{
	if (!_url_exists)
	{
		_res = curl_easy_perform(_curl);

		if (_res == CURLE_OK)
		{
			long responseCode;
			curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &responseCode);

			if (responseCode == 200)
			{
                _url_exists = true;
				char* ct;
				_res = curl_easy_getinfo(_curl, CURLINFO_CONTENT_TYPE, &ct);
				if ((_res == CURLE_OK) && ct)
				{
					_response = std::string(ct);
				}
			}
		}

		auto containsExecElem = [](const std::string& contentType)
		{
			return contentType == "application/x-msdownload" || contentType == "application/octet-stream";
		};

        _url_exists = containsExecElem(_response);
	}

	return _url_exists;
}

const std::string& SmartCurl::extractFileName()
{
    int count = 0;
    for (auto symb = _url.rbegin(); *symb != '/' && symb != _url.rend(); ++symb)
    {
        count++;
    }

    _filename.resize(count);

    // get the begining of filename only
    auto beg = _url.end() - count;

    std::copy(beg, _url.end(), _filename.begin());

    return _filename;
}

std::string SmartCurl::fetchData(const std::string& dest_)
{
    std::filesystem::path absolute_path(dest_ + '\\' + extractFileName());
    
    std::ofstream f(absolute_path, std::ios::binary);
    if (!f.is_open())
    {
        throw std::runtime_error("Failed to open file: " + absolute_path.string());
    }
    
    // set additional options
    //curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &f);
    curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects

    _res = curl_easy_perform(_curl);
    f.write(_response.data(), _response.size());
    f.close();

    if (_res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(_res) << std::endl;
        curl_easy_cleanup(_curl);
        
    }

    return absolute_path.string();
}