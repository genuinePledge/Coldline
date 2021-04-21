#pragma once

#include <string>
#include <map>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

template <typename Resource>
class ResourceHolder
{
public:
	ResourceHolder(const std::string& folder, const std::string& extension)
		: m_folder("res/" + folder + "/")
		, m_extension("." + extension)
	{
	}

	const Resource& get(const std::string& name)
	{
		if (!exist(name))
			add(name);
		return m_res.at(name);
	}

	bool exist(const std::string& name)
	{
		return m_res.find(name) != m_res.end();
	}

	void add(const std::string& name)
	{
		Resource r;
		r.loadFromFile(getFullName(name));
		m_res.insert(std::make_pair(name, r));
	}

	void save(const std::string& name, const sf::Texture& tex)
	{
		Resource r;
		r = tex;
		m_res.insert(std::make_pair(name, r));
	}

private:
	std::string getFullName(const std::string& name)
	{
		return m_folder + name + m_extension;
	}

	std::string m_folder;
	std::string m_extension;

	std::map<std::string, Resource> m_res;
};