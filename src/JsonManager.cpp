/*****************************************************************
 * JsonManager.cpp
 *****************************************************************
 * Created on: 11.10.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "JsonManager.h"
#include <iostream>

namespace PKMN
{
	string JsonManager::s_response;

	size_t JsonManager::write(void *data, size_t size, size_t nmemb, void *buffer)
	{
		if(data == nullptr) return 0;
		s_response.append((const char *)data, size * nmemb);
		return size * nmemb;
	}

	JsonManager::JsonManager(void)
		:m_pCurl(nullptr), m_rc(CURLE_OK), m_contentType(""), m_pHeaders(nullptr)
	{
		// Set headers for JSON requests
		curl_slist_append(m_pHeaders.get(), "Accept: application/json");
		curl_slist_append(m_pHeaders.get(), "Content-Type: application/json");

		// Init CURL
		m_pCurl.reset(curl_easy_init());
		if(m_pCurl == nullptr)
		{
			cout << "Error: Couldn't initialize CURL object." << endl;
		}
		else
		{
			// Set default parameters (for RESTful JSON)
			curl_easy_setopt(m_pCurl.get(), CURLOPT_HTTPHEADER, m_pHeaders.get());
			curl_easy_setopt(m_pCurl.get(), CURLOPT_HTTPGET, 1);
			curl_easy_setopt(m_pCurl.get(), CURLOPT_WRITEFUNCTION, &write);
		}
	}

	string JsonManager::request(const string &url)
	{
		if(m_pCurl != nullptr)
		{
			// Set URL
			curl_easy_setopt(m_pCurl.get(), CURLOPT_URL, url.c_str());

			// Request was successful
			if((m_rc = curl_easy_perform(m_pCurl.get())) == CURLE_OK)
			{
				char *contentType = nullptr;
				if((m_rc = curl_easy_getinfo(m_pCurl.get(), CURLINFO_CONTENT_TYPE, &contentType)) == CURLE_OK)
				{
					if(contentType != nullptr)
					{
						return s_response;
					}
					else
					{
						cout << "Error: Returned content type is null!" << endl;
					}
				}
				else
				{
					cout << "Error: Couldn't get returned content type!" << endl;
				}
			}

			// CURL error
			else
			{
				cout << "Error: Request failed!" << endl;
			}
		}

		// Request failed smh
		return "";
	}

	JsonManager::~JsonManager(void)
	{
		curl_slist_free_all(m_pHeaders.get());
		curl_easy_cleanup(m_pCurl.get());
	}
}
