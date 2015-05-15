#include <CDDWebApi.h>

int main (void)
{
	CDDWebApi *test = new CDDWebApi ("127.0.0.1");
	test->login ("1111");
	delete test;
	return 0;
}
