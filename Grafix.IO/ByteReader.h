#pragma once
#include <vector>
class ByteReader
{
public:
	ByteReader(std::vector<unsigned char> data);
	int ReadInt(bool asLittleEndian);
	short ReadShort(bool asLittleEndian);
	void Reset();
	unsigned char ReadByte();	
private:
	int _index;
	std::vector<unsigned char> _data;
};

