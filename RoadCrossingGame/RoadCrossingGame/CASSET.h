#ifndef CASSET_
#define CASSET_

#include "CSingleton.h"
#include <string>
#include <map>
#include "SFML/Graphics.hpp"

class CASSET : public CSingleton<CASSET> {
public:
	CASSET();
	~CASSET();

	//Texture
	void AddTexture(std::string name);
	void RemoveTexture(std::string name);
	sf::Texture* GetTexture(std::string name);

	//Font
	void AddFont(std::string name);
	void RemoveFont(std::string name);
	sf::Font* GetFont(std::string name);
private:
	std::map<std::string, sf::Texture*> m_textures;
	std::map<std::string, sf::Font*> m_fonts;

	std::string path;
	std::string texturePath;
	std::string fontPath;
};

#endif // !CASSET_