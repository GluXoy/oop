#include <iostream>
#include <optional>
#include "stdafx.h"

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (!searchString.size()) {
		return subject;
	}

	size_t pos = 0;

	std::string result = "";
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);

		if (foundPos == std::string::npos) {
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
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");

	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	std::ifstream inputFile;
	inputFile.open(argv[1]);
	if (!inputFile.is_open()) 
	{	
		std::cout << "Failed to open" << argv[1] << "for reading" << std::endl;
		return 1;
	}	
	std::cout << argv[1] << '\n';


	std::ofstream outputFile;
	outputFile.open(argv[2]);
	if (!outputFile.is_open())
	{
		std::cout << "Failed to open" << argv[2] << "for writing" << std::endl;
		return 1;
	}
	std::cout << argv[2] << '\n';

	std::string search = argv[3];
	std::cout << argv[3] << '\n';

	std::string replace = argv[4];
	std::cout << argv[4] << '\n';

	CopyStreamWithReplacement(inputFile, outputFile, search, replace);

	if (!outputFile.flush())
	{
		std::cout << "Failed to write data to output file\n";
		return 1;
	}

	return 0;
}
