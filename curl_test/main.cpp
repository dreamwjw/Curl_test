#include <windows.h>
#include <process.h>

#include "Http_curl.h"

unsigned int __stdcall ThreadGetPrepareTransferFileData(void *arg);

int main()
{
	CHttp_curl http_curl;
	unsigned int threadID = 0;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadGetPrepareTransferFileData, (LPVOID)&http_curl, 0, &threadID);
	if(hThread != NULL)
	{
		CloseHandle(hThread);
	}

	int i = 0;
	scanf_s("%d", &i);
	http_curl.HttpStop();

	system("pause");
}

unsigned int __stdcall ThreadGetPrepareTransferFileData(void *arg)
{
	CHttp_curl* pHttp_curl = (CHttp_curl*)arg;
	char* szHttpGetUrl = "http://192.168.6.241:6060/GetConfig/1708230009?type=All";
	string strBuffer;
	printf("%s\n", szHttpGetUrl);
	if(pHttp_curl->HttpGet(szHttpGetUrl, strBuffer) == 0)
	{
		printf(strBuffer.c_str());
	}
	else
	{
		printf("http get error, reason:[%s], url:[%s]",pHttp_curl->GetErrorContent(), szHttpGetUrl);
	}
	

	return 0;
}