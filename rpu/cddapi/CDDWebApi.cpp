

#include <CDDWebApi.h>
#include <stdlib.h>

CDDWebApi::CDDWebApi(const char *cddIPAddr)
{
  size_t ipLength = strlen(cddIPAddr);
  ipaddr = (char*)malloc(sizeof(char) * (ipLength + 1)); // IP Address must include null terminator
  strncpy(ipaddr, cddIPAddr, strlen(cddIPAddr));
}

CDDWebApi::~CDDWebApi()
{
  free(ipaddr);
  ipaddr = NULL;
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
  using namespace std;
  ((string*)stream)->append((char*)ptr,0,size*count);
  return size*count;
}


void CDDWebApi::login(char pin[4])
{

  // Check if curl has been initialised
  if (!cdd)
    {
      cdd = curl_easy_init();
    }

  // Check initialisation was successfull
  if (cdd)
    {
      // Construct & send message
      std::string toSend, response;
      curl_easy_setopt (cdd, CURLOPT_WRITEFUNCTION, writeToString);
      curl_easy_setopt (cdd, CURLOPT_WRITEDATA, &response);

      toSend = "http://";
      toSend += ipaddr;
      toSend += ":8080/api.cgi?&loginflag=1&pin=";
      toSend += pin;

      curl_easy_setopt (cdd, CURLOPT_URL, toSend.c_str());
      curl_easy_perform(cdd);

      // Check response
      size_t firstLine = response.find ("\n");
      if (response.substr (0, firstLine).compare ("HTTP/1.1 200 OK")==0)
	{
	  // Auth Successful, copy token
	  strncpy (token, response.substr(firstLine+1, firstLine+6).c_str(), 5);
	}
      else
	{
	  // failed
	}     
    }
}
void CDDWebApi::logout()
{
  curl_easy_cleanup (cdd);
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

