/*!
 * @file CDDWebApi.cpp
 * @author Thomas Deacon
 */
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
	ipaddr[ipLength] = '\0';
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
 *! Original function written by Joachim Isaksson
 *! Available at stackoverflow.com
 *
 * @param[in] void ptr        Location of input
 * @param[in] size_t size     Size of input
 * @param[in] size_t count    Occurances of input
 * @param[out] void stream    Location of output
 * @return                    Size of input string
 */
size_t writeToString (void *ptr, size_t size, size_t count, void *stream)
{
	((std::string*)stream)->append((char*)ptr,0,size*count);
	return size*count;
}

/*! void CDDWebApi::filterResponse (std::string response)
 * @author Thomas Deacon
 * @brief Takes an input string and breaks it up into appropriate strings
 *
 * @param response[in] The response from the CDD to be filtered
 */
void CDDWebApi::filterResponse (std::string response)
{
	// Search for first seperator to identify end of token
	size_t identifier=response.find (":");
	token = response.substr(0, identifier);
	
	// Search for next seperator to copy knowledge levels
	identifier++;
	size_t next = response.substr(identifier, response.length()).find(":");
	std::string knowledgelvl = response.substr (identifier, next);

	// Search for next seperator to copy languages
	identifier+=next+1;
	next=response.length();
	std::string languages = response.substr (identifier, next);

	// Reset variables for new string
	identifier=0;
	next=0;
	supportedKLDescr.clear();
	supportedKLID.clear();
	size_t end = knowledgelvl.length();
	
	// Loop until end of string
	while (next < end) {
		//Find next knowledge level identifier
		next = knowledgelvl.substr(identifier, end).find (".");
		supportedKLID.push_back(
			knowledgelvl.substr (identifier, next));
		identifier += next +1;
		
		// Find next knowledge level description
		next = knowledgelvl.substr(identifier, end).find ("-");
		supportedKLDescr.push_back 
			(knowledgelvl.substr (identifier, next));
		identifier += next +1;
	}
	// Reset variables for tokenising languages
	identifier=0;
	next=0;
	supportedLangID.clear();
	supportedLangDescr.clear();
	end = languages.length();
	
	// Loop until end of string
	while (next < end) {
		// Find next language ID
		next = languages.substr(identifier, end).find (".");
		supportedLangID.push_back (languages.substr (identifier, next));
		identifier += next +1;

		// Find next language description
		next = languages.substr(identifier, end).find ("-");
		supportedLangDescr.push_back 
			(languages.substr (identifier, next));
		identifier += next +1;
	}
}

/*! std::string CDDWebApi::getToken()
 * @author Thomas Deacon
 * @returns A string containing the current token supplied by the CDD at login
 */
std::string CDDWebApi::getToken()
{
	return token;
}

/*! std::string CDDWebApi::getLastSentMessage()
 * @author Thomas Deacon
 * @brief A debugging tool to verify the last message sent
 * @returns A string containing the last transmitted message
 */
std::string CDDWebApi::getLastSentMessage()
{
	return lastSentMessage;
}

/*! std::string CDDWebApi::getErr()
 * @author Thomas Deacon
 * @returns A string containing the last recorded error (if present)
 */
std::string CDDWebApi::getErr()
{
	return error;
}

/*! std::vector<std::string> CDDWebApi::getSupportedLanguages()
 * @author Thomas Deacon
 * @returns A vector of strings, each element is a description of a supported
 *! language.
 */
std::vector<std::string> CDDWebApi::getSupportedLanguages()
{
	return supportedLangDescr;
}

/*! std::vector<std::string> CDDWebApi::getSupportedKnowledgeLevels()
 * @author Thomas Deacon
 * @returns A vector of strings, each element is a description of a supported
 *! knowledge level
 */
std::vector<std::string> CDDWebApi::getSupportedKnowledgeLevels()
{
	return supportedKLDescr;
}

/*! CDDWebApi::login(const char pin)
 * @author Thomas Deacon
 * @brief Sends login request to CDD and processes return data
 * 
 * @param[in] pin is the pin used to authenticate the RPU
 * @returns 0 upon success, -1 upon CuRL fault and -2 for an invalid response
 */
int CDDWebApi::login(const char *newPin)
{
	// Check initialisation was successfull
	if (!cdd) {
		error = "COMMS INIT FAULT";
		return -1;
	}

	// Configure libCuRL to output response to a string
	std::string toSend, response;
	curl_easy_setopt (cdd, CURLOPT_WRITEFUNCTION, writeToString);
	curl_easy_setopt (cdd, CURLOPT_WRITEDATA, &response);
	
	// Construct a string to request a login
	toSend = "http://";
	toSend += ipaddr;
	toSend += ":80/api.cgi?&action=1&pin=";
	toSend += newPin;
	lastSentMessage.clear();
	lastSentMessage = toSend;

	// Send login request
	curl_easy_setopt (cdd, CURLOPT_URL, toSend.c_str());
	int errorCode = curl_easy_perform(cdd);
	if (errorCode != CURLE_OK) {
		error = "COMMS TRANSMISSION FAULT";
		return -1;
	}

	// Check if response indicates an error
	if (response.compare ("could not find a record <br>")==0){
		error="INVALID PIN";
		return -2;
	}
	else if (response.compare ("PIN number required<br>")==0){
		error="MAULFORMED PIN";
		return -2;
	}
	else if (response.compare ("invalid request")==0){
		error="INVALID REQUEST";
		return -2;
	}
	else if (response.find(":")==std::string::npos) {
		error="UNDEFINED RESPONSE";
		return -2;
	}
	// Response is ok, filter
	filterResponse(response);
	strncpy (pin, newPin, 4);
	languageCode=1;
	knowledgeCode=1;
	return 0;    
	
}

/*! void CDDWebApi::logout()
 * @author Thomas Deacon
 * @brief Used to logout the RPU, and clears all associated variables used
 */
void CDDWebApi::logout()
{
	// Configure libCuRL to output response to a string
	std::string toSend, response;
	curl_easy_setopt (cdd, CURLOPT_WRITEFUNCTION, writeToString);
	curl_easy_setopt (cdd, CURLOPT_WRITEDATA, &response);
	
	// Construct a string to request a login
	toSend = "http://";
	toSend += ipaddr;
	toSend += ":80/api.cgi?&action=0&pin=";
	toSend += pin;
	lastSentMessage.clear();
	lastSentMessage = toSend;

	// Send login request
	curl_easy_setopt (cdd, CURLOPT_URL, toSend.c_str());
	curl_easy_perform(cdd);
	strncpy (pin, "    ", 4);
	languageCode=1;
	knowledgeCode= 1;

}

/*! int CDDWebApi::requestAudioStream (char trackID[4])
 * @author Thomas Deacon
 * @brief This constructs and sends a request for an audio track to be played
 * @param trackID Is the 4 digit track identifier for the audio playback.
 * @returns 0 regardless of error (will fix...hopefully).
 */
int CDDWebApi::requestAudioStream(const char *trackID)
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
	toSend += ":80/api.cgi?&token=";
	toSend += token;
	toSend += "&trackid=";
	toSend += trackID;
	toSend += "&language=";
	toSend += languageCode;
	toSend += "&knowledge=";
	toSend += knowledgeCode;

	// Send login request
	curl_easy_setopt (cdd, CURLOPT_URL, toSend.c_str());
	curl_easy_perform(cdd);
	lastSentMessage.clear();
	lastSentMessage = toSend;
	// ERROR CHECKING GOES HERE!!
}

/*! void CDDWebApi::changeLanguage (int language)
 * @author Thomas Deacon
 * @brief Changes the selected language based on the value passed to it. Value
 *! should represent a position from CDDWebApi::getSupportedLanguages() vector.
 * @param[in] language is the position of the vector
 */
void CDDWebApi::changeLanguage(int language)
{
	languageCode = language;
}

/*! void CDDWebApi::changeknowledgeLevel (int knowledge)
 * @author Thomas Deacon
 * @brief Changes the selected knowledge level based on the value passed to it.
 *! Value should represent a position from
 *! CDDWebApi::getSupportedKnowledgeLevels vector.
 * @param[in] knowledge is the position of the vector
 */
void CDDWebApi::changeKnowledgeLevel(int knowledge)
{
	knowledgeCode = knowledge;
}



