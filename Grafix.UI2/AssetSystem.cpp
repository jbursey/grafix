#include "AssetSystem.h"



AssetSystem::AssetSystem()
{	
}


AssetSystem::~AssetSystem()
{
	_assets.clear();	
}

void AssetSystem::Init()
{
	std::string heightMapDir = "./..\\..\\";

	std::vector<std::string> heightmaps;
	heightmaps.push_back("heightmap_test.bmp");
	heightmaps.push_back("heightmap5.bmp");
	heightmaps.push_back("test_bitmap.bmp");
	heightmaps.push_back("test_bitmap_needs_padding_5_by_5.bmp");
	heightmaps.push_back("usgs_colo_springs.bmp");
	heightmaps.push_back("usgs_ft_worth.bmp");
	heightmaps.push_back("mt_shasta.bmp");
	heightmaps.push_back("hawaii.bmp");

	std::string shaderDir = "./";
	std::vector<std::string> shaders;
	shaders.push_back("PixelShader.cso");
	shaders.push_back("PixelShaderLights.cso");
	shaders.push_back("VertexShader.cso");
	shaders.push_back("VertexShaderLights.cso");

	for (std::string hm : heightmaps)
	{
		auto hmBytes = _fr.ReadAllBytes(heightMapDir + hm);
		_assets.insert_or_assign(hm, hmBytes);
	}

	for (std::string shader : shaders)
	{
		auto shaderBytes = _fr.ReadAllBytes(shaderDir + shader);
		_assets.insert_or_assign(shader, shaderBytes);
	}
}

std::vector<unsigned char> AssetSystem::GetAsset(std::string name)
{
	if (_assets.count(name) == 1)
	{
		return _assets[name];
	}

	return std::vector<unsigned char>();
}
