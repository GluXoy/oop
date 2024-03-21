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
		try
		{
			if (ParseURL(url, protocol, port, host, document))
			{
				cout << "HOST: " << host << endl;
				cout << "PORT: " << port << endl;
				cout << "DOC: " << document << endl;
			}
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << '\n';
		}
	}

	return 0;
}