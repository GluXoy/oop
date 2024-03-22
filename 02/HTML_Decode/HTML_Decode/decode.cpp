#include <algorithm>
#include <iostream>
#include <vector>
#include "decode.h"

using namespace std;

vector<Pair> replacements =
{
	{"&quot;", "\""},
	{"&apos;", "'"},
	{"&lt;", "<"},
	{"&gt;", ">"},
	{"&amp;", "&"}
};

string HtmlDecode(string const& html, const vector<Pair>& replacements)
{
	string str = html;
	const char ENCODE_EL = '&';

	size_t pos = 0;
	while ((pos = str.find(ENCODE_EL, pos)) != string::npos)
	{
		bool isEncoded = false;
		for (const auto& pair : replacements)
		{
			if (str.find(pair.encode, pos) == pos)
			{
				str.replace(pos, pair.encode.size(), pair.decode);
				pos += pair.decode.size();
				isEncoded = true;
				break;
			}
		}
		if (!isEncoded)
		{
			++pos;
		}
	}

	return str;
}