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

void CASSET::ExtractObjectsTexture() {
	texturePath = "../Assets/Texture/objects/";

	//Extract static objects
	std::string staticsPath = texturePath + "Statics/Objects.png";
	sf::Texture* texture = new sf::Texture;

	//Streets
	texture->loadFromFile(staticsPath, sf::IntRect(16, 608, 31, 623)); 
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_street_sewer", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(48, 608, 63, 623));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_street", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(80, 608, 95, 623));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_street_dotted_horizontal", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(112, 608, 127, 623));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_street_dotted_vertical", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(16, 640, 31, 655));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_street_yellow_vertical", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(48, 640, 63, 655));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_street_yellow_horizontal", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(80, 640, 95, 655));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_street_road_markings_right", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(112, 640, 127, 655));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_street_road_markings_middle", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(144, 640, 159, 655));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_street_road_markings_left", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(16, 672, 31, 687));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_street_manhole", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(80, 672, 95, 687));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_street_white_horizontal", texture));

	//Vehicles
	texture->loadFromFile(staticsPath, sf::IntRect(17, 384, 80, 415));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_vehicle_van_horizontal_1", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(16, 448, 79, 479));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_vehicle_van_horizontal_2", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(129, 389, 176, 415));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_vehicle_car_horizontal_1", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(128, 453, 175, 479));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_vehicle_car_horizontal_2", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(271, 400, 304, 449));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_vehicle_van_horizontal_1", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(240, 483, 271, 527));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_vehicle_car_horizontal_1", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(304, 483, 335, 527));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_vehicle_car_horizontal_2", texture));

	//Signs
	texture->loadFromFile(staticsPath, sf::IntRect(385, 468, 398, 495));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_sign_1", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(418, 470, 429, 495));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_sign_2", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(450, 470, 461, 495));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_sign_3", texture));

	//Trees
	texture->loadFromFile(staticsPath, sf::IntRect(384, 514, 399, 543));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_tree_1", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(415, 517, 432, 543));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_tree_2", texture));

	//Fences
	texture->loadFromFile(staticsPath, sf::IntRect(400, 131, 415, 143));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_fence_1", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(432, 133, 447, 143));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_fence_2", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(464, 128, 479, 143));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_fence_3", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(497, 131, 510, 143));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_fence_cone", texture));

	//Decorations (still obstacles)
	texture->loadFromFile(staticsPath, sf::IntRect(401, 160, 414, 175));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_decoration_bin_1", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(402, 192, 413, 207));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_decoration_bin_2", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(434, 192, 445, 207));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_decoration_bin_3", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(432, 160, 447, 175));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_decoration_mailbox", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(466, 162, 475, 175));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_decoration_fire_hydrant", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(496, 176, 520, 207));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_decoration_vending_machine", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(544, 185, 559, 207));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_decoration_cardboard_1", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(576, 185, 591, 207));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_decoration_cardboard_2", texture));

	texture->loadFromFile(staticsPath, sf::IntRect(608, 188, 630, 207));
	m_textures.insert(std::pair<std::string, sf::Texture*>("static_decoration_cardboard_3", texture));

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


	AddTexture("character/clown.png");

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