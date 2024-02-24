#include "stdafx.h"

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty()) 
	{
		return subject;
	}

	size_t pos = 0;

	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);

		result.append(subject, pos, foundPos - pos);
		if (foundPos == std::string::npos)
		{
			return result;
		}

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
		if (output.fail())
		{
			throw std::runtime_error("Error: writing to output file!");
		}
	}

	if (!input.eof() || input.bad())
	{
		throw std::runtime_error("Error: reading from input stream!");
	}
}


void ParseArguments(char* argv[], std::ifstream& input, std::ofstream& output,
	 std::string& searchString, std::string& replacementString)
{
	input.open(argv[1]);
	if (!input.is_open())
	{
		throw std::runtime_error("Failed to open " + std::string(argv[1]) + " for reading!");
	}

	output.open(argv[2]);
	if (!output.is_open())
	{
		throw std::runtime_error("Failed to open " + std::string(argv[2]) + " for writing!");
	}

	std::cout << "Input file: " << argv[1] << '\n';
	std::cout << "Output file: " << argv[2] << '\n';

	searchString = argv[3];
	std::cout << "Search string: " << argv[3] << '\n';

	replacementString = argv[4];
	std::cout << "Replace string: " << argv[4] << '\n';
}

void CopyFileWithReplacement(char* argv[])
{
	std::ifstream input;
	std::ofstream output;
	std::string search;
	std::string replace;

	ParseArguments(argv, input, output, search, replace);
	CopyStreamWithReplacement(input, output, search, replace);

	if (!output.flush())
	{
		throw std::runtime_error("Failed to write data to output file");
	}
}