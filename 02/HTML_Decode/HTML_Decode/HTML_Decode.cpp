#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "decode.h"


int main()
{
	std::string htmlString;

	while (std::getline(std::cin, htmlString))
	{
		std::cout << "Decoded html-string: " << HtmlDecode(htmlString, replacements) << '\n';
	}
	
	return 0;
}
