

#ifndef _CDD_WEB_API_H_
#define _CDD_WEB_API_H_

#include <curl/curl.h>
#include <string.h>
#include <iostream>
#include <vector>

class CDDWebApi {
public:
	// constructors
	CDDWebApi(const char *cddIPAddr);
	~CDDWebApi();

	// For communicating with CDD
	int login(char pin[4]);
	void logout();
	int requestAudioStream(char trackID[4]);

	// Changing parameters
        int changeLanguage(int language);
        int changeKnowledgeLevel(int knowledge);

	// Getting response data
	std::vector<std::string> getSupportedLanguages();
	std::vector<std::string> getSupportedKnowledgeLevels();

	// Debug stuff
	std::string getLastSentMessage();
	std::string getErr ();
	std::string getToken();
	
private:
	void filterResponse(std::string response);

	std::vector<std::string> supportedLangDescr;
	std::vector<std::string> supportedLangID;

	std::vector<std::string> supportedKLDescr;
	std::vector<std::string> supportedKLID;


	std::string error;
	std::string lastSentMessage;
	std::string token;
	CURL *cdd;
	char *ipaddr;
	char lastTrackID[4];
	char pin[5];
	std::string languageCode, knowledgeCode;
};


#endif
