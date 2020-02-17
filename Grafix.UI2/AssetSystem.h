#pragma once
#include <map>
#include <vector>
#include <string>
#include "FileReader.h"

class AssetSystem
{
public:
	AssetSystem();
	~AssetSystem();
	void Init();
	std::vector<unsigned char> GetAsset(std::string name);

private:
	std::map<std::string, std::vector<unsigned char>> _assets;
	FileReader _fr;
};

