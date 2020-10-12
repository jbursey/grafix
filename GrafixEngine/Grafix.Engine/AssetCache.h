#pragma once
#include <vector>
#include <string>
#include <map>

#include "FileReader.h"

class AssetCache
{
public:
	AssetCache();
	~AssetCache();
	void Init();
	bool Cache(std::string id, std::string path);
	std::vector<unsigned char> GetItem(std::string id);

private:
	std::map<std::string, std::vector<unsigned char>> _cache;
};

