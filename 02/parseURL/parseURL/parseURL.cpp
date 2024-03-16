#include <iostream>
#include "parse.h"

using namespace std;

int main()
{
	string url;
	Protocol protocol;
	int port;
	string host; 
	string document;

	while (getline(cin, url))
	{
		if (ParseURL(url, protocol, port, host, document))
		{
			cout << "HOST: " << host << endl;
			cout << "PORT: " << port << endl;
			cout << "DOC: " << document << endl;
		}
	}

	return 0;
}