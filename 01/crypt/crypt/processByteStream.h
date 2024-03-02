#pragma once
#include <optional>

struct Args
{
	std::string cryptStatus;
	std::string inputFileName;
	std::string outputFileName;
	std::string key;
};

unsigned char Encode(unsigned char byte);

unsigned char Decode(unsigned char byte);

std::optional<Args> ParseArgs(int argc, char* argv[]);

void processByteStream(std::ifstream& inputFile, std::ofstream& outputFile, int key, bool crypt);

void ProcessFile(const std::optional<Args>& args);
