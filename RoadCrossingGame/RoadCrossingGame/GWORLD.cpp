#include "GWORLD.h"
#include <numeric>

GWORLD::GWORLD(sf::RenderWindow& window)
	: mWindow(window)
	, mTextures()
	, mScrollSpeed(100.f)
	, mPlayerAircraft(nullptr)
{
	//mWindow.setView(sf::View(sf::FloatRect(0, SCREEN_HEIGHT * 2, SCREEN_WIDTH, SCREEN_HEIGHT)));
	//std::cout << "View position: " << mWindow.getView().getCenter().x << ", " << mWindow.getView().getCenter().y << std::endl;
	mSpawnPosition = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 5 / 2);
	loadTextures();
	buildPlayer();
	buildMaps();
}

GMAP* GWORLD::getCurrentMap() {
	return &mMaps[id.front()];
}

void GWORLD::update(float deltaTime)
{
	if (mWindow.getView().getCenter().y != 1800) {
		mWindow.setView(sf::View(sf::FloatRect(0, SCREEN_HEIGHT * 2, SCREEN_WIDTH, SCREEN_HEIGHT)));
		//std::cout << "View position: " << mWindow.getView().getCenter().x << ", " << mWindow.getView().getCenter().y << std::endl;
	}

	//std::cout << "Player position: " << mPlayerAircraft->getPosition().x << ", " << mPlayerAircraft->getPosition().y << std::endl;
	//Handle map out of world
	handleMapOutOfWorld(deltaTime);

	//Handle player touches border
	GMAP* currMap = getCurrentMap();

	//Move the player sidewards (plane scouts follow the main aircraft)
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	//If player touches borders, flip its X velocity
	if (position.x <= 150.f
		|| position.x >= SCREEN_WIDTH - 150.f)
	{
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}

	// Apply movements && Scroll the world downward
	for (auto& it : mMaps) {
		it.update(deltaTime);
	}
}

void GWORLD::handleMapOutOfWorld(float deltaTime) {
	GMAP* currMap = getCurrentMap();
	float yCoordinate = currMap->getCoordinate().y;
	float lastYCoordinate = mMaps[id.back()].getCoordinate().y;

	//out of world
	if (yCoordinate > (float)Constants::SCREEN_HEIGHT * 3) {
		std::cout << id.front() << std::endl;
		GMAP* currMap = getCurrentMap();
		currMap->rebuild(lastYCoordinate);
		std::rotate(id.begin(), id.begin() + 1, id.end());
	}
}

void GWORLD::buildPlayer() {
	// Initialize the different layers
	for (std::size_t currMap = 0; currMap < 3; ++currMap) {
		for (std::size_t i = 0; i < LayerCount; ++i) {
			CSCENENODE::Ptr layer(new CSCENENODE());
			worldSceneLayers[currMap].push_back(layer.get());
			worldSceneGraph[currMap].attachChild(std::move(layer));
		}
	}

	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, 0.f);
	worldSceneLayers[0][Air]->attachChild(std::move(leader));

	// Add two escorting aircrafts, placed relatively to the main plane
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));
}

void GWORLD::buildMaps() {
	id.resize(3); std::iota(id.begin(), id.end(), 0);

	for (std::size_t i = 0; i < 3; ++i) {
		mMaps.push_back(GMAP(mWindow, (float)Constants::SCREEN_HEIGHT * (2 - i), &worldSceneLayers[i], &worldSceneGraph[i], &mTextures, &mScrollSpeed));
		std::cout << SCREEN_HEIGHT * (2 - i) << std::endl;
	}
}

void GWORLD::draw() {
	for (std::size_t i = 0; i < LayerCount; ++i) {
		for (std::size_t currMap = 0; currMap < 3; ++currMap) {
			mWindow.draw(*worldSceneLayers[currMap][i]);
		}
	}
}

void GWORLD::loadTextures()
{
	mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
	mTextures.load(Textures::DEFAULT_ROAD, "Media/Textures/default_road_resize.png");
	mTextures.load(Textures::DOTTED_ROAD, "Media/Textures/white_dotted_road.png");
	mTextures.load(Textures::PAVEMENT, "Media/Textures/pavement.png");
	//mTextures.load(Textures::DOTTED_ROAD, "Media/Textures/Objects.png");
}