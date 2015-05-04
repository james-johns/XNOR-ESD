

#include <CDDWebApi.h>
#include <stdlib.h>

CDDWebApi::CDDWebApi(const char *cddIPAddr)
{
	size_t ipLength = strlen(cddIPAddr);

	// IP Address must include null terminator
	ipaddr = (char*)malloc(sizeof(char) * (ipLength + 1)); 
	strncpy(ipaddr, cddIPAddr, strlen(cddIPAddr));
	cdd = curl_easy_init();
}

CDDWebApi::~CDDWebApi()
{
	free(ipaddr);
	ipaddr = NULL;
	curl_easy_cleanup (cdd);
}

/**
 * size_t writeToString
 *
 * Source available from :
 * stackoverflow.com/questions/9786150/save-curl-content-result-into-a-string-in-c
 *
 * @param void ptr        Location of input
 * @param size_t size     Size of input
 * @param size_t count    Occurances of input
 * @param void stream     Location of output
 * @return                Size of input string
 */
size_t writeToString (void *ptr, size_t size, size_t count, void *stream)
{
	((std::string*)stream)->append((char*)ptr,0,size*count);
	return size*count;
}


int CDDWebApi::login(char pin[4])
{
	// Check initialisation was successfull
	if (!cdd)
		return -1;

	// Configure libCuRL to output response to a string
	std::string toSend, response;
	curl_easy_setopt (cdd, CURLOPT_WRITEFUNCTION, writeToString);
	curl_easy_setopt (cdd, CURLOPT_WRITEDATA, &response);
	
	// Construct a string to request a login
	toSend = "http://";
	toSend += ipaddr;
	toSend += ":8080/api.cgi?&loginflag=1&pin=";
	toSend += pin;
      
	// Send login request
	curl_easy_setopt (cdd, CURLOPT_URL, toSend.c_str());
	curl_easy_perform(cdd);

	// Check response
	size_t firstLine = response.find ("\n");
	if (response.substr (0, firstLine).compare ("HTTP/1.1 200 OK")==0) {
		// Auth Successful, copy token
		strncpy (token, response.substr
			 (firstLine+1, firstLine+6).c_str(), 5);
		return 0;
	} else {
		// failed
		return -1;
	}     
	
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

