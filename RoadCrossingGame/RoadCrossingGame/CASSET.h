#ifndef CASSET_H
#define CASSET_H

#include "CSingleton.h"
#include <string>
#include <map>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class CASSET : public CSingleton<CASSET> {
public:
	CASSET();
	~CASSET();

	//Texture
	void AddTexture(std::string name);
	void RemoveTexture(std::string name);
	void ExtractObjectsTexture();
	sf::Texture* GetTexture(std::string name);

	//Font
	void AddFont(std::string name);
	void RemoveFont(std::string name);
	sf::Font* GetFont(std::string name);	
	
	//Audio

	// --- SFX ---
	void AddSound(std::string name);
	void RemoveSound(std::string name);
	sf::Sound* GetSound(std::string name);

	// --- MUSIC ---
	void AddMusic(std::string name);
	void RemoveMusic(std::string name);
	sf::Music* GetMusic(std::string name);

	void playMusic(std::string name);
	void playSFX(std::string name);
	void setAllow(bool isAllowed);
private:
	std::map<std::string, sf::Texture*> m_textures;
	std::map<std::string, sf::Font*> m_fonts;
	std::map<std::string, sf::Sound*> m_sound;
	std::map<std::string, sf::Music*> m_music;

	std::string path;
	std::string texturePath;
	std::string fontPath;
	std::string soundPath;

	bool isAllowed;
};

#endif // !CASSET_H