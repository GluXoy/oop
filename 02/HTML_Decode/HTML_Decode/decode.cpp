#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

string HtmlDecode(string const& html, const map<string, string>& replacements)
{
	string str = html;
	const char ENCODE_EL = '&';

	size_t pos = 0;
	while ((pos = str.find(ENCODE_EL, pos)) != string::npos)
	{
		bool encoded = false;
		for (const auto& el : replacements)
		{
			if (str.find(el.first, pos) == pos)
			{
				str.replace(pos, el.first.size(), el.second);
				pos += el.second.size();
				encoded = true;
				break;
			}
		}
		if (!encoded)
		{
			++pos;
		}
	}

	return str;
}