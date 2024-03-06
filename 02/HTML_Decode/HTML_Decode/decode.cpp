#include <algorithm>
#include <iostream>
#include <map>

void decodeHtmlEntity(std::string& str, const std::string& encodeEl, const std::string& decodeEl)
{
	size_t pos = 0;
	while ((pos = str.find(encodeEl, pos)) != std::string::npos)
	{
		str.replace(pos, encodeEl.size(), decodeEl);
		pos += decodeEl.size();
	}
}

std::string HtmlDecode(std::string const& html, std::map<std::string, std::string> replacements)
{
	std::string decodedHtmlStr = html;

	for (const auto& replacement : replacements) {
		decodeHtmlEntity(decodedHtmlStr, replacement.first, replacement.second);
	}

	return decodedHtmlStr;
}