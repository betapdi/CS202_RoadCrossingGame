#include "GMAP.h"

GMAP::GMAP(sf::RenderWindow& window, const int& yMapCoordinate, std::vector<CSCENENODE*>* mSceneLayers, CSCENENODE* mSceneGraph, TextureHolder* mTextures)
	: mWindow(window)
	, mWorldBounds(0.f, yMapCoordinate, window.getDefaultView().getSize().x, 2000.f)
	, mRoadBounds(0.f, 0.f, window.getDefaultView().getSize().x, Constants::ROAD_SIZE)
	, mScrollSpeed(-100.f)
{
	this->mSceneGraph = mSceneGraph;
	this->mSceneLayers = mSceneLayers;
	this->mTextures = mTextures;

	//std::cout << this->mSceneLayers->size() << std::endl;
	buildScene();
}

sf::Vector2f GMAP::getCoordinate() {
	return sf::Vector2f(mWorldBounds.left, mWorldBounds.top);
}

void GMAP::rebuild(const int& yMapCoordinate) {

}

void GMAP::handleTouchBorder(Aircraft* mPlayerAircraft) {

}

void GMAP::update(float deltaTime)
{
	// Scroll the map


	//Move the player sidewards (plane scouts follow the main aircraft)
	//sf::Vector2f position = mPlayerAircraft->getPosition();
	//sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	////If player touches borders, flip its X velocity
	//if (position.x <= mWorldBounds.left + 150.f
	//	|| position.x >= mWorldBounds.left + mWorldBounds.width - 150.f)
	//{
	//	velocity.x = -velocity.x;
	//	mPlayerAircraft->setVelocity(velocity);
	//}

}

void GMAP::draw() {}

void GMAP::buildScene()
{
	// Prepare the tiled background
	sf::Texture& texture = mTextures->get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<CSPRITENODE> backgroundSprite(new CSPRITENODE(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers->at(Background)->attachChild(std::move(backgroundSprite));

	// --- ROAD ---
	sf::Texture& texture1 = mTextures->get(Textures::DOTTED_ROAD);
	sf::IntRect textureRect1(mRoadBounds);
	texture1.setRepeated(true);
	texture1.setSmooth(true);

	std::unique_ptr<CROAD> road1(new CROAD(texture1, textureRect1));
	road1->setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height / 2);
	mSceneLayers->at(Road)->attachChild(std::move(road1));

	sf::Texture& texture2 = mTextures->get(Textures::DEFAULT_ROAD);
	texture2.setRepeated(true);
	texture2.setSmooth(true);

	std::unique_ptr<CROAD> road2(new CROAD(texture2, textureRect1));
	road2->setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height / 2 - Constants::ROAD_SIZE);
	mSceneLayers->at(Road)->attachChild(std::move(road2));

	std::unique_ptr<CROAD> road3(new CROAD(texture2, textureRect1));
	road3->setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height / 2 + Constants::ROAD_SIZE);
	mSceneLayers->at(Road)->attachChild(std::move(road3));

	sf::Texture& texture3 = mTextures->get(Textures::PAVEMENT);
	texture3.setRepeated(true);
	texture3.setSmooth(true);

	std::unique_ptr<CROAD> pave(new CROAD(texture3, textureRect1));
	pave->setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height / 2 - 2 * Constants::ROAD_SIZE);
	mSceneLayers->at(Road)->attachChild(std::move(pave));

	std::unique_ptr<CROAD> pave1(new CROAD(texture3, textureRect1));
	pave1->setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height / 2 - 3 * Constants::ROAD_SIZE);
	mSceneLayers->at(Road)->attachChild(std::move(pave1));
}

void GMAP::generateRoads() {
	//::vector<CROAD::Type> roadTypes = { CROAD::DEFAULT_ROAD,CROAD::DOTTED_ROAD };
	//mSceneLayers[Road]
}