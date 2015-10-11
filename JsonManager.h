/*****************************************************************
 * JsonManager.h
 *****************************************************************
 * Created on: 11.10.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef JSONMANAGER_H_
#define JSONMANAGER_H_

#include <memory>
#include <string>
#include <curl/curl.h>

namespace PKMN
{
	using namespace std;

	class JsonManager
	{
	private:
		// Underlying CURL object
		unique_ptr<CURL> m_pCurl;

		// Return code
		CURLcode m_rc;

		// Returned content type
		string m_contentType;

		// Header list
		unique_ptr<struct curl_slist> m_pHeaders;

		// Response string recieved from HTTP server
		static string s_response;

		/**
		 * CURL write function.
		 *
		 * @param data
		 * Data to append.
		 *
		 * @param size
		 * Size of data in bytes.
		 *
		 * @param nmemb
		 * Number of members.
		 *
		 * @param buffer
		 * Buffer to append data to.
		 *
		 * @return Bytes written.
		 */
		static size_t write(void *data, size_t size, size_t nmemb, void *buffer);

	public:

		/**
		 * Default dtor.
		 */
		JsonManager(void);

		/**
		 * Fires the specified HTTP GET request and returns the
		 * retrieved JSON object.
		 *
		 * @param url
		 * Request URL.
		 *
		 * @return JSON object.
		 */
		string request(const string &url);

		/**
		 * Defaulut dtor.
		 * Release CURL resources.
		 */
		~JsonManager(void);
	};
}


#endif // JSONMANAGER_H_
