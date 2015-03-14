

#include <CDDWebApi.h>


CDDWebApi::CDDWebApi(const char *cddIPAddr)
{
	size_t ipLength = strlen(cddIPAddr);
	ipaddr = malloc(sizeof(char) * (ipLength + 1)); // IP Address must include null terminator
	strncpy(ipaddr, cddIPAddr, strlen(cddIPAddr));
}

CDDWebApi::~CDDWebApi()
{
	free(ipAddr);
	ipAddr = NULL;
}

void CDDWebApi::login(char pin[4])
{

}
void CDDWebApi::logout()
{

}

void CDDWebApi::requestAudioStream(char trackID[4], int language, int knowledgeLevel)
{

}
void CDDWebApi::changeLanguage(int language)
{

}
void CDDWebApi::changeKnowledgeLevel(int knowledge)
{

}

