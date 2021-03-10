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

	ResourceHolder<sf::Texture> m_texture;
	ResourceHolder<sf::Font> m_font;
	ResourceHolder<sf::SoundBuffer> m_audio;
private:
	ResourceManager()
		: m_texture("tex", "png")
		, m_font("fonts", "ttf")
		, m_audio("audio", "wav")
	{

	}
};