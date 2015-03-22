

#ifndef _CDD_WEB_API_H_
#define _CDD_WEB_API_H_

class CDDWebApi {
public:
	CDDWebApi(const char *cddIPAddr);
	~CDDWebApi();

	void login(char pin[4]);
	void logout();

	void requestAudioStream(char trackID[4], int language, int knowledgeLevel);
	void changeLanguage(int language);
	void changeKnowledgeLevel(int knowledge);
	
private:
	const char *ipaddr;
	char lastTrackID[4];
};


#endif
