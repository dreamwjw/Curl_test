#ifndef HTTP_CURL_H_
#define HTTP_CURL_H_

#include <string>
using namespace std;

#include "curl.h"

class CHttp_curl
{
private:
	CURL* m_pCurl;
	char m_szErrorContent[CURL_ERROR_SIZE];

private:
	static int writer(char *, size_t, size_t, string *);
	bool Setopt(const char *url, const char* szPostBody, string &strBuffer, int nTimeOut);
	int RunCurl(const char* szUrl, const char *szPostBody, string &strBuffer, int nTimeOut);

public:
	CHttp_curl();
	~CHttp_curl();
	int HttpGet(const char* szHttpGetUrl, string &strBuffer, int nTimeOut = 15);
	int HttpPost(const char* szHttpPostUrl, const char* szPostBody, string &strBuffer, int nTimeOut = 15);
	int HttpStop();
	const char* GetErrorContent();
};


#endif /* HTTP_CURL_H_ */