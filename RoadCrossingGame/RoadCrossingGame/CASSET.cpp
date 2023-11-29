#include "CASSET.h"

void CASSET::AddTexture(std::string name) {
	path = "../Assets/";
	texturePath = path + "Texture/";
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(texturePath + name);

	//check if the same textures
	auto it = m_textures.find(name);
	if (it != m_textures.end()) {
		return;
	}
	m_textures.insert(std::pair<std::string, sf::Texture*>(name, texture));
}

void CASSET::RemoveTexture(std::string name) {
	path = "../Assets/";
	texturePath = path + "Texture/";
	auto it = m_textures.find(name);
	if (it != m_textures.end()) {
		return;
	}
	if (it->second != nullptr) delete it->second;
	m_textures.erase(it);
}

sf::Texture* CASSET::GetTexture(std::string name) {
	path = "../Assets/";
	texturePath = path + "Texture/";
	auto it = m_textures.find(name);
	if (it != m_textures.end()) {
		return it->second;
	}
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(texturePath + name);
	m_textures.insert(std::pair<std::string, sf::Texture*>(name, texture));
	return texture;
}

void CASSET::AddFont(std::string name) {
	path = "../Assets/";
	fontPath = path + "Font/";
	sf::Font* font = new sf::Font;
	font->loadFromFile(fontPath + name);

	//check if the same font
	auto it = m_fonts.find(name);
	if (it != m_fonts.end()) {
		return;
	}
	m_fonts.insert(std::pair<std::string, sf::Font*>(name, font));
}

void CASSET::RemoveFont(std::string name) {
	path = "../Assets/";
	fontPath = path + "Font/";
	auto it = m_fonts.find(name);
	if (it != m_fonts.end()) {
		return;
	}
	if (it->second != nullptr) delete it->second;
	m_fonts.erase(it);
}

sf::Font* CASSET::GetFont(std::string name) {
	path = "../Assets/";
	fontPath = path + "Font/";
	auto it = m_fonts.find(name);
	if (it != m_fonts.end()) {
		return it->second;
	}
	sf::Font* font = new sf::Font;
	font->loadFromFile(fontPath + name);
	m_fonts.insert(std::pair<std::string, sf::Font*>(name, font));
	return font;
}

CASSET::CASSET() {
	//Textures
	AddTexture("city/1.png");
	AddTexture("city/2.png");
	AddTexture("city/3.png");
	AddTexture("city/4.png");
	AddTexture("city/5.png");
	AddTexture("city/6.png");
	AddTexture("cursor.png");
	AddTexture("hand-cursor.png");

	//Fonts
	AddFont("LuckiestGuy-Regular.ttf");
	AddFont("BruceForeverRegular.ttf");

	//Audio

}

CASSET::~CASSET() {
	for (auto it : m_textures) {
		if (it.second != nullptr) {
			delete it.second;
		}
	}
	m_textures.clear();

	for (auto it : m_fonts) {
		if (it.second != nullptr) {
			delete it.second;
		}
	}
	m_fonts.clear();
}