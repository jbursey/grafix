#include "FileReader.h"

std::vector<unsigned char> FileReader::ReadAllBytes(std::string path)
{
	std::vector<unsigned char> data;
	FILE* stream{};
	errno_t openerr = fopen_s(&stream, path.c_str(), "rb");
	fseek(stream, 0, SEEK_END);
	long size = ftell(stream);
	data.resize(size);
	fseek(stream, 0, 0);
	fread_s(&data[0], size, sizeof(unsigned char), size, stream);
	int closeResult = fclose(stream);

	return data;
}

