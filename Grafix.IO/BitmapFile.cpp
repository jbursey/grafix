#include "pch.h"
#include "BitmapFile.h"

BitmapFile::BitmapFile()
{
	
}

BitmapFile::~BitmapFile()
{
	delete _br;
	_br = 0;
}

void BitmapFile::Parse(std::vector<unsigned char> data)
{
	_br = new ByteReader(data);

	//-- bitmap header----------------------------------------------
	unsigned char header1 = _br->ReadByte();
	unsigned char header2 = _br->ReadByte();
	_header.headerField[0] = header1;
	_header.headerField[1] = header2;

	_header.bitmapSizeBytes = _br->ReadInt(true);

	//reserved 1
	_br->ReadByte();
	_br->ReadByte();

	//reserved 2
	_br->ReadByte();
	_br->ReadByte();

	_header.startingAddressData = _br->ReadInt(true);

	//-- dib headeer-------------------------------------------------

	int dibMagicSize = _br->ReadInt(true);

	switch (dibMagicSize)
	{
	case 40: //windows NT or later...parse as BITMAPINFOHEADER
		ParseBitmapInfoHeader();
		break;
	case 124: //windows NT 5.0 or later...parse as BITMAPV5HEADER
		ParseBitmapV5Header();
		break;
	default:
		break;
	}

	//-- color table if applicable------------------------------------
	if (_infoV5Header.compression == 3) //BI_BITFIELDS
	{
		//-- not super clear here, but I don't know a better way. Gimp and paint3d are not putting color index
		int bytesToData = _header.startingAddressData - _br->GetIndex();
		for (int i = 0; i < bytesToData; i++)
		{
			_br->ReadByte(); //this is color palette data somehow
		}
	}

	//-- pixel data---------------------------------------------------
	//-- local test is a 3x3 pixel bmp...3 rows
	int colorsUntilEnd = 0;
	int bytesPerColor = _infoV5Header.bitsPerPixel / 8;	
	int colorBytesLeft = _header.bitmapSizeBytes - _br->GetIndex();
	colorsUntilEnd = colorBytesLeft / bytesPerColor;
	for (int i = 0; i < colorsUntilEnd; i++)
	{
		int pix = _br->ReadInt(true);
		unsigned char r = pix >> 24;
		unsigned char g = pix >> 16;
		unsigned char b = pix >> 8;
		unsigned char a = pix >> 0;

		//--add the colors for convienience later
		Color color;
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
		
		this->Colors.push_back(color);
	}

	int stop = 0;
}

void BitmapFile::ParseBitmapInfoHeader()
{
	_infoHeader.headerSize = 40; //alread read from switch statement above
	_infoHeader.bitmapWidthPixels = _br->ReadInt(true);
	_infoHeader.bitmapHeightPixels = _br->ReadInt(true);
	_infoHeader.numberofColorPlanes = _br->ReadShort(true);
	_infoHeader.bitsPerPixel = _br->ReadShort(true);
	_infoHeader.compressionMethod = _br->ReadInt(true);
	_infoHeader.imageSizeRaw = _br->ReadInt(true);
	_infoHeader.horizontalResolution = _br->ReadInt(true);
	_infoHeader.verticalResolution = _br->ReadInt(true);
	_infoHeader.numerOfColorsInPallette = _br->ReadInt(true);
	_infoHeader.numberofImportantColors = _br->ReadInt(true);

	int stop = 0;
}

void BitmapFile::ParseBitmapV5Header()
{
	_infoV5Header.headerSize = 124;
	_infoV5Header.widthPixels = _br->ReadInt(true);
	_infoV5Header.heightPixels = _br->ReadInt(true);
	_infoV5Header.planes = _br->ReadShort(true);
	_infoV5Header.bitsPerPixel = _br->ReadShort(true);
	_infoV5Header.compression = _br->ReadInt(true); //0 = BI_RGB, 1 = BI_RLE8
	_infoV5Header.sizeimage = _br->ReadInt(true);
	_infoV5Header.horizontalResolution = _br->ReadInt(true);
	_infoV5Header.verticalResolution = _br->ReadInt(true);
	_infoV5Header.colorsUsed = _br->ReadShort(true);
	_infoV5Header.importColors = _br->ReadShort(true);
	_infoV5Header.redMask = _br->ReadShort(true);
	_infoV5Header.greenMask = _br->ReadShort(true);
	_infoV5Header.blueMask = _br->ReadShort(true);
	_infoV5Header.alphaMast = _br->ReadShort(true);
	_infoV5Header.csType = _br->ReadShort(true);
	//CIEXYZTRIPLE
	for (int i = 0; i < 4 * 3 * 3; i++)
	{
		//CIEXYZTRIPLE
		_br->ReadByte();
	}
	_infoV5Header.gammaRed = _br->ReadShort(true);
	_infoV5Header.gammaGreen = _br->ReadShort(true);
	_infoV5Header.gammaBlue = _br->ReadShort(true);
	_infoV5Header.intent = _br->ReadShort(true);
	_infoV5Header.profileData = _br->ReadShort(true);
	_infoV5Header.profileSize = _br->ReadShort(true);
	_infoV5Header.reserved = _br->ReadShort(true);

	int stop = 0;
}
