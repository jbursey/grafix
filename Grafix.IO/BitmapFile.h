#pragma once
#include <string>
struct BitmapFileHeader
{
public:
	char headerField[2];
	int bitmapSizeBytes;
	char reserved1[2];
	char reserved2[2];
	int startingAddressData;
};

///All ints are in little endian
class BitmapFile
{
public:
	void ReadFile(std::string path);
private:
	BitmapFileHeader _header;
};


