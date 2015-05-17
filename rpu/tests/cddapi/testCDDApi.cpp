#include <CDDWebApi.h>

int main (void)
{
	CDDWebApi *test = new CDDWebApi ("127.0.0.1");

	if (test->login ("1111")!=0) {
	    std::cout << "Sent: " << test->getLastSentMessage() << "\n";
	    std::cout << "Error: " << test->getErr() << "\n";
	  }
	else {
	  std::cout << "Sent:" << test->getLastSentMessage() << "\n";
	  std::cout << "Token:" << test->getToken() << "\n";
	  std::vector<std::string> kl = test->getSupportedKnowledgeLevels();
	  int loop =0;
	  std::cout << "\nSupported Knowledge Levels: \n";
	  while (loop < kl.size()) {
	    std::cout  << kl[loop] << "\n";
	    loop++;
	  }
	  std::vector<std::string> lang = test->getSupportedLanguages();
	  loop=0;
	  std::cout << "\nSupported Languages:\n";
	  while (loop < lang.size()){
	    std::cout << lang[loop] << "\n";
	    loop++;
	  }
	}
	delete test;
	return 0;
}
