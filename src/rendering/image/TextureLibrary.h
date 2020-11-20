//
// Created by Sean on 10/26/2020.
//

#ifndef GAMEENGINE_TEXTURELIBRARY_H
#define GAMEENGINE_TEXTURELIBRARY_H
#include <map>
#include <memory>
#include <rendering/image/texture.h>

typedef std::shared_ptr<Texture> TexturePtr;

class TextureLibrary
{
public:
	virtual TexturePtr load(const char *fileName, const std::string &directory,
			std::string type = "texture_diffuse", bool gamma = true);
	virtual TexturePtr getTexture(std::string texture);
	std::vector<std::string> getStoredTextures(void);
private:
	std::map<std::string, TexturePtr> loadedTextures;
};


class NullTextureLibrary: public TextureLibrary
{
public:
	virtual TexturePtr load(const char *fileName, const std::string &directory,
			std::string type = "texture_diffuse", bool gamma = true) {return nullptr;}
	virtual TexturePtr getTexture(std::string texture) {return nullptr;};
};

class TextureLibraryLocator
{
public:
	static void initialize() { service_ = &nullService_; }

	static TextureLibrary& getTextureLibrary() { return *service_; }

	static void provide(TextureLibrary* service)
	{
		if (service == NULL)
		{
			// Revert to null service.
			service_ = &nullService_;
		}
		else
		{
			service_ = service;
		}
	}

private:
	static NullTextureLibrary nullService_;
	static TextureLibrary* service_;
};


#endif //GAMEENGINE_TEXTURELIBRARY_H
