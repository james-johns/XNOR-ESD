

#include <CDDWebApi.h>
#include <stdlib.h>
/*! CDDWebApi::CDDWebApi(const char *cddIPAddr)
 * @author Thomas Deacon
 * @brief CDDWebApi Constructor
 * 
 * @param[in] cddIPAddr char string containing ip address of cdd server
 */
CDDWebApi::CDDWebApi(const char *cddIPAddr)
{
	size_t ipLength = strlen(cddIPAddr);

	// IP Address must include null terminator
	ipaddr = (char*)malloc(sizeof(char) * (ipLength + 1)); 
	strncpy(ipaddr, cddIPAddr, strlen(cddIPAddr));
	cdd = curl_easy_init();
}

/*! CDDWebApi::~CDDWebApi()
 * @author Thomas Deacon
 * @brief CDDWebApi destructor
 */
CDDWebApi::~CDDWebApi()
{
	free(ipaddr);
	ipaddr = NULL;
	curl_easy_cleanup (cdd);
}

/*! size_t writeToString
 * @author Thomas Deacon
 * @brief Function used to take libcurl output and store in a string
 * Original function written by Joachim Isaksson
 * Available at stackoverflow.com
 *
 * @param[ void ptr        Location of input
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

/*! CDDWebApi::login(char pin[4])
 * @author Thomas Deacon
 * @brief Sends login request to CDD and processes return data
 * 
 * @param[in] pin is a 4 digit pin used to authenticate the RPU
 */
int CDDWebApi::login(char pin[4])
{
	// Check initialisation was successfull
	if (!cdd)
		return -1;

	//std::cout << "Init success!\n";
	//std::cout << "IP:" << ipaddr << "\nPin:" << pin << "\n";

	// Configure libCuRL to output response to a string
	std::string toSend, response;
	curl_easy_setopt (cdd, CURLOPT_WRITEFUNCTION, writeToString);
	curl_easy_setopt (cdd, CURLOPT_WRITEDATA, &response);
	
	// Construct a string to request a login
	toSend = "http://";
	toSend += ipaddr;
	toSend += ":80/api.cgi?&action=1&pin=";
	toSend += pin;

	std::cout << "\nOutput: " << toSend << "\n";

	// Send login request
	curl_easy_setopt (cdd, CURLOPT_URL, toSend.c_str());
	int errorCode = curl_easy_perform(cdd);
	if (errorCode != CURLE_OK)
	{
		std::cout << "Error: " << errorCode << "\n";
		std::cout << "See: http://curl.haxx.se/libcurl/c/libcurl-errors.html\n";
		return -1;
	}

	std::cout << "\nResponse:\n" << response << "\n\n";

	// Check response
	/*size_t firstLine = response.find ("\n");
	if (response.substr (0, firstLine).compare ("HTTP/1.1 200 OK")==0) {
		// Auth Successful, copy token
		strncpy (token, response.substr
			 (firstLine+1, firstLine+6).c_str(), 5);
		return 0;
	} else {
		// failed
		return -1;
		} */
	return 0;    
	
}

/*! CDDWebApi::logout()
 * @author Thomas Deacon
 * @brief Clears currently stored token
 */
void CDDWebApi::logout()
{
	strncpy (token, "    \0", 5);
}

int CDDWebApi::requestAudioStream(char trackID[4])
{
	// Check initialisation was successfull
	if (!cdd)
		return -1;

	// Configure libCuRL to output response to a string
	std::string toSend, response;
	curl_easy_setopt (cdd, CURLOPT_WRITEFUNCTION, writeToString);
	curl_easy_setopt (cdd, CURLOPT_WRITEDATA, &response);
	
	// Construct a string to request a track
	toSend = "http://";
	toSend += ipaddr;
	toSend += token;
	toSend += languageCode;
	toSend += knowledgeCode;

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
int CDDWebApi::changeLanguage(int language)
{
	languageCode = language;
	return 0;
}
int CDDWebApi::changeKnowledgeLevel(int knowledge)
{
	knowledgeCode = knowledge;
	return 0;
}
