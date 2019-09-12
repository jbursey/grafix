#include "pch.h"
#include "ByteReader.h"

ByteReader::ByteReader(std::vector<unsigned char> data)
{
	_data = data;
}

int ByteReader::ReadInt(bool asLittleEndian)
{
	unsigned char v1 = _data[_index++];
	unsigned char v2 = _data[_index++];
	unsigned char v3 = _data[_index++];
	unsigned char v4 = _data[_index++];

	int val = 0;
	if (!asLittleEndian)
	{
		val |= v1 << 24;
		val |= v2 << 16;
		val |= v3 << 8;
		val |= v4 << 0;
	}
	else
	{
		val |= v1 << 0;
		val |= v2 << 8;
		val |= v3 << 16;
		val |= v4 << 24;
	}

	return val;
}

short ByteReader::ReadShort(bool asLittleEndian)
{
	unsigned char v1 = _data[_index++];
	unsigned char v2 = _data[_index++];

	short val = 0;

	if (!asLittleEndian)
	{
		val |= v1 << 8;
		val |= v2 << 0;
	}
	else
	{
		val |= v2 << 8;
		val |= v1 << 0;
	}

	return val;
}

void ByteReader::Reset()
{
	_index = 0;
}

void ByteReader::Seek(int index)
{
	if (index < 0)
	{
		index = 0;
	}
	_index = index;
}

int ByteReader::GetIndex()
{
	return _index;
}

unsigned char ByteReader::ReadByte()
{
	unsigned char v = _data[_index++];

	return v;
}
