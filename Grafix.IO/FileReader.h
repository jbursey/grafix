#pragma once
#include <vector>
#include <string>

class FileReader
{
public:
	static std::vector<unsigned char> ReadAllBytes(std::string path);
};

