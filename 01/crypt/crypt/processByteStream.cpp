#include "stdafx.h"
#include "processByteStream.h"

unsigned char Encode(unsigned char byte)
{
	std::bitset<8> bits(byte);
	std::bitset<8> result;
	result[0] = bits[2];
	result[1] = bits[6];
	result[2] = bits[7];
	result[3] = bits[0];
	result[4] = bits[1];
	result[5] = bits[3];
	result[6] = bits[4];
	result[7] = bits[5];

	return static_cast<unsigned char>(result.to_ulong());
}

unsigned char Decode(unsigned char byte)
{
	std::bitset<8> bits(byte);
	std::bitset<8> result;
	result[0] = bits[3];
	result[1] = bits[4];
	result[2] = bits[0];
	result[3] = bits[5];
	result[4] = bits[6];
	result[5] = bits[7];
	result[6] = bits[1];
	result[7] = bits[2];

	return static_cast<unsigned char>(result.to_ulong());
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	Args args;
	if (argc != 5)
	{
		std::cout << "Usage: " << argv[0] << " crypt/decrypt <input file> <output file> <key>" << '\n';
		return std::nullopt;
	}
	args.cryptStatus = argv[1];
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	args.key = argv[4];
	return args;
}

void processByteStream(std::ifstream& inputFile, std::ofstream& outputFile, int key, bool crypt)
{
	char byte;
	while (inputFile.get(byte))
	{
		if (crypt)
		{
			byte ^= key;
			byte = Encode(byte);
		}
		else
		{
			byte = Decode(byte);
			byte ^= key;
		}
		outputFile.put(byte);
	}
	if (inputFile.bad())
	{
		throw std::runtime_error("Failed to reading input file!");
	}
}

void ProcessFile(const std::optional<Args>& args)
{
	bool cryptStatus;
	if (args->cryptStatus == "decrypt")
	{
		cryptStatus = false;
	}
	else if (args->cryptStatus == "crypt")
	{
		cryptStatus = true;
	}
	else
	{
		throw std::invalid_argument("The Crypt status should be crypt/decrypt!\nYour status : " + args->cryptStatus);
	}

	std::ifstream inputFile(args->inputFileName, std::ios::binary);
	if (!inputFile)
	{
		throw std::runtime_error("Failed to open input file: " + args->inputFileName);
	}

	std::ofstream outputFile(args->outputFileName, std::ios::binary);
	if (!outputFile)
	{
		throw std::runtime_error("Failed to open output file: " + args->outputFileName);
	}

	int key = stoi(args->key);
	if (key > 255 || key < 0)
	{
		throw std::invalid_argument("The key value can be from 0 to 255!");
	}

	processByteStream(inputFile, outputFile, key, cryptStatus);
}
