#include "stdafx.h"

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty()) // empty
	{
		return subject;
	}

	size_t pos = 0;

	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);// append должен быть использован дважды а не трижды

		if (foundPos == std::string::npos)
		{
			result.append(subject, pos, subject.size() - pos);
			return result;
		}

		result.append(subject, pos, foundPos - pos);
		result.append(replacementString);
		pos = foundPos + searchString.size();
	}
	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{//проверять на ошибки
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
	// обработать ошибку чтения
	if (!output.eof())
	{
		std::cout << << '\n';
	}
}