#pragma once

#include "ResourceHolder.h"

class ResourceManager
{
public:
	static ResourceManager& get()
	{
		static ResourceManager m;
		return m;
	}

	ResourceHolder<sf::Texture> textures;
	ResourceHolder<sf::Font> fonts;
	ResourceHolder<sf::SoundBuffer> sounds;
private:
	ResourceManager()
		: textures("tex", "png")
		, fonts("fonts", "ttf")
		, sounds("audio", "wav")
	{

	}
};