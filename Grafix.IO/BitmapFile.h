#pragma once
#include <string>
#include <vector>
//#include <wingdi.h> //bitmap v5 header
#include "ByteReader.h"

struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

//https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types?redirectedfrom=MSDN
// https://en.wikipedia.org/wiki/BMP_file_format
struct BitmapFileHeader
{
public:
	char headerField[2];
	int bitmapSizeBytes;
	char reserved1[2];
	char reserved2[2];
	int startingAddressData;
};

struct BitmapInfoHeader
{
public:
	int headerSize;
	int bitmapWidthPixels;
	int bitmapHeightPixels;
	short numberofColorPlanes;
	short bitsPerPixel;
	int compressionMethod;
	int imageSizeRaw;
	int horizontalResolution;
	int verticalResolution;
	int numerOfColorsInPallette;
	int numberofImportantColors;
};

struct BitmapV5Header
{
public:
	int headerSize;
	int widthPixels;
	int heightPixels;
	short planes;
	short bitsPerPixel;
	int compression; //BI_RGB uncompressed
	int sizeimage;
	int horizontalResolution;
	int verticalResolution;
	short colorsUsed;
	short importColors;
	short redMask;
	short greenMask;
	short blueMask;
	short alphaMast;
	short csType;
	
	//CIEXYZTRIPLE endpoints
	short gammaRed;
	short gammaGreen;
	short gammaBlue;
	short intent;
	short profileData;
	short profileSize;
	short reserved;

};

// All ints are in little endian
class BitmapFile
{
public:
	BitmapFile();
	~BitmapFile();
	void Parse(std::vector<unsigned char> data);
	std::vector<Color> Colors;
	int Width;
	int Height;
private:
	BitmapFileHeader _header;
	BitmapInfoHeader _infoHeader;
	BitmapV5Header _infoV5Header;
	//BITMAPV5HEADER _v5Header;
	ByteReader* _br = nullptr;

	void ParseBitmapInfoHeader();
	void ParseBitmapV5Header();
};


