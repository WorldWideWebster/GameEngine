//
// Created by Sean on 10/31/2020.
//

#include "TextureViewer.h"
#include <rendering/image/TextureLibrary.h>

TextureViewer::TextureViewer()
{
	this->setName("TextureViewer");
	this->open();
}

void TextureViewer::showWidgets(void)
{
	static std::vector<std::string> textures = TextureLibraryLocator::getTextureLibrary().getStoredTextures();
	for (auto& it : textures)
	{
		ImGui::Text(it.c_str());
	}
}

