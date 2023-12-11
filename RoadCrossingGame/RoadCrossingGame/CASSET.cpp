#include "CASSET.h"
#include <iostream>

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

void CASSET::loadTexture(std::string path, std::string name, sf::IntRect area) {
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(path, area);
	m_textures.insert(std::pair<std::string, sf::Texture*>(name, texture));
}

sf::Texture* CASSET::GetObjectTexture(std::string name) {
	auto it = m_textures.find(name);
	if (it != m_textures.end()) {
		return it->second;
	}

	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(texturePath + name);
	m_textures.insert(std::pair<std::string, sf::Texture*>(name, texture));
	return texture;
}

void CASSET::ExtractObjectsTexture() {
	texturePath = "../Assets/Texture/objects/";

	//Extract static objects
	std::string staticsPath = texturePath + "Statics/Objects.png";

	//Streets
	loadTexture(staticsPath, "static_street_sewer", sf::IntRect(16, 608, 16, 16));

	loadTexture(staticsPath, "static_street", sf::IntRect(48, 608, 16, 16));

	loadTexture(staticsPath, "static_street_dotted_horizontal", sf::IntRect(80, 608, 16, 16));

	loadTexture(staticsPath, "static_street_dotted_vertical", sf::IntRect(112, 608, 16, 16));

	loadTexture(staticsPath, "static_street_yellow_vertical", sf::IntRect(16, 640, 16, 16));

	loadTexture(staticsPath, "static_street_yellow_horizontal", sf::IntRect(48, 640, 16, 16));

	loadTexture(staticsPath, "static_street_road_markings_right", sf::IntRect(80, 640, 16, 16));

	loadTexture(staticsPath, "static_street_road_markings_middle", sf::IntRect(112, 640, 16, 16));

	loadTexture(staticsPath, "static_street_road_markings_left", sf::IntRect(144, 640, 16, 16));

	loadTexture(staticsPath, "static_street_manhole", sf::IntRect(16, 672, 16, 16));

	loadTexture(staticsPath, "static_street_white_horizontal", sf::IntRect(80, 672, 16, 16));

	//Vehicles
	loadTexture(staticsPath, "static_vehicle_van_horizontal_1", sf::IntRect(17, 384, 64, 32));

	loadTexture(staticsPath, "static_vehicle_van_horizontal_2", sf::IntRect(16, 448, 64, 32));

	loadTexture(staticsPath, "static_vehicle_car_horizontal_1", sf::IntRect(129, 389, 48, 27));

	loadTexture(staticsPath, "static_vehicle_car_horizontal_2", sf::IntRect(128, 453, 48, 27));

	loadTexture(staticsPath, "static_vehicle_van_vertical_1", sf::IntRect(271, 400, 34, 50));

	loadTexture(staticsPath, "static_vehicle_car_vertical_1", sf::IntRect(240, 483, 32, 45));

	loadTexture(staticsPath, "static_vehicle_car_vertical_2", sf::IntRect(304, 483, 32, 45));

	//Signs
	loadTexture(staticsPath, "static_sign_1", sf::IntRect(385, 468, 14, 27));

	loadTexture(staticsPath, "static_sign_2", sf::IntRect(418, 470, 12, 26));

	loadTexture(staticsPath, "static_sign_3", sf::IntRect(450, 470, 12, 26));

	//Trees
	loadTexture(staticsPath, "static_tree_1", sf::IntRect(384, 514, 16, 30));

	loadTexture(staticsPath, "static_tree_2", sf::IntRect(415, 517, 18, 27));

	//Fences
	loadTexture(staticsPath, "static_fence_1", sf::IntRect(400, 131, 16, 13));

	loadTexture(staticsPath, "static_fence_2", sf::IntRect(432, 133, 16, 11));

	loadTexture(staticsPath, "static_fence_3", sf::IntRect(464, 128, 16, 16));

	loadTexture(staticsPath, "static_fence_cone", sf::IntRect(497, 131, 14, 13));

	//Decorations (still obstacles)
	loadTexture(staticsPath, "static_decoration_bin_1", sf::IntRect(401, 160, 14, 16));

	loadTexture(staticsPath, "static_decoration_bin_2", sf::IntRect(402, 192, 12, 16));

	loadTexture(staticsPath, "static_decoration_bin_3", sf::IntRect(434, 192, 12, 16));

	loadTexture(staticsPath, "static_decoration_mailbox", sf::IntRect(432, 160, 16, 16));

	loadTexture(staticsPath, "static_decoration_fire_hydrant", sf::IntRect(466, 162, 10, 14));

	loadTexture(staticsPath, "static_decoration_vending_machine", sf::IntRect(496, 176, 25, 32));

	loadTexture(staticsPath, "static_decoration_cardboard_1", sf::IntRect(544, 185, 16, 23));

	loadTexture(staticsPath, "static_decoration_cardboard_2", sf::IntRect(576, 185, 16, 23));

	loadTexture(staticsPath, "static_decoration_cardboard_3", sf::IntRect(608, 188, 23, 20));

	//Extract animations
	std::string animationsPath1 = texturePath + "Animations/BD001.png";
	std::string animationsPath2 = texturePath + "Animations/BL001.png";
	std::string animationsPath3 = texturePath + "Animations/SL001.png";


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

void CASSET::AddSound(std::string name) {
	path = "../Assets/";
	soundPath = path + "Audio/";

	sf::Sound* sound = new sf::Sound;
	sf::SoundBuffer* buffer = new sf::SoundBuffer;
	buffer->loadFromFile(soundPath + name);
	sound->setBuffer(*buffer);

	//check if the same sound
	auto it = m_sound.find(name);
	if (it != m_sound.end()) {
		return;
	}
	m_sound.insert(std::pair<std::string, sf::Sound*>(name, sound));
}

void CASSET::RemoveSound(std::string name) {
	auto it = m_sound.find(name);
	if (it != m_sound.end()) {
		return;
	}
	if (it->second != nullptr) delete it->second;
	m_sound.erase(it);
}

sf::Sound* CASSET::GetSound(std::string name) {
	path = "../Assets/";
	fontPath = path + "Audio/";

	auto it = m_sound.find(name);
	if (it != m_sound.end()) {
		return it->second;
	}

	sf::Sound* sound = new sf::Sound;
	sf::SoundBuffer* buffer = new sf::SoundBuffer;
	buffer->loadFromFile(fontPath + name);
	sound->setBuffer(*buffer);
	m_sound.insert(std::pair<std::string, sf::Sound*>(name, sound));
	return sound;
}

void CASSET::AddMusic(std::string name) {
	path = "../Assets/";
	soundPath = path + "Audio/";

	sf::Music* music = new sf::Music;
	music->openFromFile(soundPath + name);

	//check if the same sound
	auto it = m_music.find(name);
	if (it != m_music.end()) {
		return;
	}
	m_music.insert(std::pair<std::string, sf::Music*>(name, music));
}

void CASSET::RemoveMusic(std::string name) {
	auto it = m_music.find(name);
	if (it != m_music.end()) {
		return;
	}
	if (it->second != nullptr) delete it->second;
	m_music.erase(it);
}

sf::Music* CASSET::GetMusic(std::string name) {
	path = "../Assets/";
	soundPath = path + "Audio/";

	auto it = m_music.find(name);
	if (it != m_music.end()) {
		return it->second;
	}

	sf::Music* music = new sf::Music;
	music->openFromFile(soundPath + name);
	m_music.insert(std::pair<std::string, sf::Music*>(name, music));	
	return music;
}

void CASSET::playMusic(std::string name) {
	if (isAllowed) {
		//play music
		GetMusic(name)->play();
	}
}

void CASSET::playSFX(std::string name) {
	if (isAllowed) {
		// play sfx
		GetSound(name)->play();
	}
}

void CASSET::setAllow(bool isAllowed) {
	this->isAllowed = isAllowed;
}

CASSET::CASSET() {
	//Textures
	AddTexture("city/1.png");
	AddTexture("city/2.png");
	AddTexture("city/3.png");
	AddTexture("city/4.png");
	AddTexture("city/5.png");
	AddTexture("city/6.png");

	AddTexture("gui/cursor.png");
	AddTexture("gui/back.png");
	AddTexture("gui/cursor1.png");
	AddTexture("gui/move_left.png");
	AddTexture("gui/move_right.png");
	AddTexture("gui/music_off.png");
	AddTexture("gui/music_on.png");
	AddTexture("gui/sfx_off.png");
	AddTexture("gui/sfx_on.png");
	AddTexture("gui/quit.png");

	ExtractObjectsTexture();

	//Fonts
	AddFont("LuckiestGuy-Regular.ttf");
	AddFont("BruceForeverRegular.ttf");

	//Audio

}

CASSET::~CASSET() {
	for (auto &it : m_textures) {
		if (it.second != nullptr) {
			delete it.second;
		}
	}
	m_textures.clear();

	for (auto &it : m_fonts) {
		if (it.second != nullptr) {
			delete it.second;
		}
	}
	m_fonts.clear();
}