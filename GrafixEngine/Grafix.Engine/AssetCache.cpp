#include "AssetCache.h"

AssetCache::AssetCache()
{
}

AssetCache::~AssetCache()
{
}

void AssetCache::Init()
{
	//--cache assets
}

bool AssetCache::Cache(std::string id, std::string path)
{
	FileReader fr;
	auto bytes = fr.ReadAllBytes(path);

	_cache.insert_or_assign(id, bytes);
}

std::vector<unsigned char> AssetCache::GetItem(std::string id)
{
	return _cache[id];
}
