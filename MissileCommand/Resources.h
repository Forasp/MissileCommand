#pragma once
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <SFML/Graphics/Texture.hpp>

namespace FFTex
{
	enum ID
	{
		Crate_1,
		Crate_2
	};
}

template<typename Resource, typename Identifier>

class Resources
{
protected:
	void AddResource(Identifier _ID, const std::string& _Filename);

	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;

public:
	void LoadResource(Identifier _ID, const std::string& _Filename);

	template<typename Parameters>
	void LoadResource(Identifier _ID, const std::string& _Filename, const Parameters& _SecondParam);

	Resource& GetResource(Identifier _ID);
	const Resource& GetResource(Identifier _ID);
};

typedef Resources<sf::Texture, FFTex::ID> TextureResources;

#include "Resources.inl"
