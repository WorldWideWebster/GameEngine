//
// Created by Sean on 10/26/2020.
//

#include "TextureLibrary.h"

NullTextureLibrary TextureLibraryLocator::nullService_;
TextureLibrary* TextureLibraryLocator::service_ = &TextureLibraryLocator::nullService_;

TexturePtr TextureLibrary::load(const char *fileName, const std::string &directory, std::string type, bool gamma)
{
	// First lookup if the texture with that filename
	// is already loaded, if yes, return it instead
	// so that it can be shared.
	//
	auto texIterator = loadedTextures.find(fileName);
	if (texIterator != loadedTextures.end())
	{
		return texIterator->second;
	}
	// Texture with that filename is not loaded yet.
	// Load it and save it into the map cache.
	//
	// All the SDL loading routine you already know
	// + allocating a new Texture object. Take a look at `std::make_shared()`.
	TexturePtr newTexture = std::make_shared<Texture>(TextureFromFile(fileName, directory, type));

	// Add to the cache map so that next time if someone
	// tries to load() it again, we don't duplicate any data.
	loadedTextures.insert(std::make_pair(fileName, newTexture));

	return newTexture;
}

TexturePtr TextureLibrary::getTexture(std::string texture)
{
	auto texIterator = loadedTextures.find(texture);
	if (texIterator != loadedTextures.end())
	{
		return texIterator->second;
	};

	return nullptr;
}

std::vector<std::string> TextureLibrary::getStoredTextures(void)
{
	std::vector<std::string> textures;
	for(auto const& imap: loadedTextures)
		textures.push_back(imap.first);
	return textures;
}
