

#ifndef _CDD_WEB_API_H_
#define _CDD_WEB_API_H_

#include <iostream>
#include <curl/curl.h>
#include <string.h>

class CDDWebApi {
public:
	CDDWebApi(const char *cddIPAddr);
	~CDDWebApi();

	int login(char pin[4]);
	void logout();

	int requestAudioStream(char trackID[4]);
        int changeLanguage(int language);
        int changeKnowledgeLevel(int knowledge);

	
private:
	
	CURL *cdd;
	char *ipaddr;
	char lastTrackID[4];
	char token[5];
	int languageCode, knowledgeCode;
};


#endif
