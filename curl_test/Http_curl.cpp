#include "http_curl.h"

CHttp_curl::CHttp_curl()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);

	m_pCurl = curl_easy_init();

	memset(m_szErrorContent, 0, CURL_ERROR_SIZE);
}

CHttp_curl::~CHttp_curl()
{
	curl_easy_cleanup(m_pCurl);
}

bool CHttp_curl::Setopt(const char *url, const char* szPostBody, string &strBuffer, int nTimeOut)
{
	CURLcode code;
	if(m_pCurl == NULL)
	{
		strcpy_s(m_szErrorContent, CURL_ERROR_SIZE, "Failed to create CURL connection\n");
		return false;
	}
	code = curl_easy_setopt(m_pCurl, CURLOPT_ERRORBUFFER, m_szErrorContent);
	if (code != CURLE_OK)
	{
		return false;
	}
	code = curl_easy_setopt(m_pCurl, CURLOPT_URL, url);
	if (code != CURLE_OK)
	{
		return false;
	}
	code = curl_easy_setopt(m_pCurl, CURLOPT_FOLLOWLOCATION, 1);
	if (code != CURLE_OK)
	{
		return false;
	}
	code = curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION, writer);
	if (code != CURLE_OK)
	{
		return false;
	}
	code = curl_easy_setopt(m_pCurl, CURLOPT_WRITEDATA, &strBuffer);
	if (code != CURLE_OK)
	{
		return false;
	}
	code = curl_easy_setopt(m_pCurl, CURLOPT_TIMEOUT, nTimeOut);//设置超时时间
	if (code != CURLE_OK)
	{
		return false;
	}

	if(strlen(szPostBody) > 0)
	{
		code = curl_easy_setopt(m_pCurl, CURLOPT_POST, 1);
		if (code != CURLE_OK)
		{
			return false;
		}
		code = curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDS, szPostBody);
		if (code != CURLE_OK)
		{
			return false;
		}
	}
	
	return true;
}

int CHttp_curl::writer(char *data, size_t size, size_t nmemb, string *writerData)
{
	unsigned long sizes = size * nmemb;
	if(writerData == NULL) return 0;
	writerData->append(data, sizes);
	return sizes;
}

int CHttp_curl::RunCurl(const char* szUrl, const char *szPostBody, string &strBuffer, int nTime)
{
	CURLcode code;

	if (!Setopt(szUrl, szPostBody,strBuffer, nTime))
	{
		return -1;
	}

	code = curl_easy_perform(m_pCurl);
	if (code != CURLE_OK)
	{
		return -1;
	}

	return 0;
}

int CHttp_curl::HttpGet(const char* szHttpGetUrl, string &strBuffer, int nTimeOut)
{
	return RunCurl(szHttpGetUrl, "", strBuffer, nTimeOut);
}

int CHttp_curl::HttpPost(const char* szHttpPostUrl, const char* szPostBody, string &strBuffer, int nTimeOut)
{
	return 0;
}

int CHttp_curl::HttpStop()
{
	curl_easy_reset(m_pCurl);

	return 0;
}

const char* CHttp_curl::GetErrorContent()
{
	return m_szErrorContent;
}