#include "Resources.h"


/*
Resources::Resources() 
{

}

Resources::~Resources()
{

}

std::vector<FFTexture>* Resources::GetTextures()
{
	return &mTextures;
}

void Resources::AddTexture(std::string _ResourceLocation)
{
	// Check if texture already exists, ignore if so.
	for (std::vector<FFTexture>::iterator it = mTextures.begin(); it != mTextures.end(); ++it)
	{
		if (it->mResourceLocation == _ResourceLocation)
		{
			return;
		}
	}

	sf::Texture* TextureFile;

	// If the file loads properly, add it to textures
	if (TextureFile->loadFromFile(_ResourceLocation))
	{
		mTextures.push_back(FFTexture(_ResourceLocation, TextureFile));
	}
}

FFTexture* Resources::GetTexture(std::string _ResourceLocation)
{
	// Check if texture already exists, ignore if so.
	for (std::vector<FFTexture>::iterator it = mTextures.begin(); it != mTextures.end(); ++it)
	{
		if (it->mResourceLocation == _ResourceLocation)
		{
			return it._Ptr;
		}
	}
}
*/