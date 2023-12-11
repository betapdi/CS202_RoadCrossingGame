#include "GMAP.h"

GMAP::GMAP(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTextures()
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
	, mRoadBounds(0.f, 0.f, mWorldView.getSize().x, Constants::ROAD_SIZE)
	, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
	, mScrollSpeed(-100.f)
	, mPlayerAircraft(nullptr)
{
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void GMAP::update(float deltaTime)
{
	// Scroll the world
	mWorldView.move(0.f, mScrollSpeed * deltaTime);

	if (mWorldView.getCenter().y - mWorldView.getSize().y / 2.f > mWorldBounds.top + mWorldBounds.height)
	{
		mWorldBounds.left = 0;
		mWorldBounds.top = 0;
		mWorldView.setCenter(mSpawnPosition);
	}

	//Move the player sidewards (plane scouts follow the main aircraft)
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	//If player touches borders, flip its X velocity
	if (position.x <= mWorldBounds.left + 150.f
		|| position.x >= mWorldBounds.left + mWorldBounds.width - 150.f)
	{
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}

	// Apply movements
	mSceneGraph.update(deltaTime);
}

void GMAP::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void GMAP::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		CSCENENODE::Ptr layer(new CSCENENODE());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<CSPRITENODE> backgroundSprite(new CSPRITENODE(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));


	//	--- PLAYER ---
	// Add player's aircraft
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->attachChild(std::move(leader));

	// Add two escorting aircrafts, placed relatively to the main plane
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));

	// --- ROAD ---
	sf::Texture& texture1 = mTextures.get(Textures::DOTTED_ROAD);
	sf::IntRect textureRect1(mRoadBounds);
	texture1.setRepeated(true);
	texture1.setSmooth(true);

	std::unique_ptr<CROAD> road1(new CROAD(texture1, textureRect1));
	road1->setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height / 2);
	mSceneLayers[Road]->attachChild(std::move(road1));

	sf::Texture& texture2 = mTextures.get(Textures::DEFAULT_ROAD);
	texture2.setRepeated(true);
	texture2.setSmooth(true);

	std::unique_ptr<CROAD> road2(new CROAD(texture2, textureRect1));
	road2->setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height / 2 - Constants::ROAD_SIZE);
	mSceneLayers[Road]->attachChild(std::move(road2));

	std::unique_ptr<CROAD> road3(new CROAD(texture2, textureRect1));
	road3->setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height / 2 + Constants::ROAD_SIZE);
	mSceneLayers[Road]->attachChild(std::move(road3));

	sf::Texture& texture3 = mTextures.get(Textures::PAVEMENT);
	texture3.setRepeated(true);
	texture3.setSmooth(true);

	std::unique_ptr<CROAD> pave(new CROAD(texture3, textureRect1));
	pave->setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height / 2 - 2 * Constants::ROAD_SIZE);
	mSceneLayers[Road]->attachChild(std::move(pave));

	std::unique_ptr<CROAD> pave1(new CROAD(texture3, textureRect1));
	pave1->setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height / 2 - 3 * Constants::ROAD_SIZE);
	mSceneLayers[Road]->attachChild(std::move(pave1));
}

void GMAP::generateRoads() {
	//::vector<CROAD::Type> roadTypes = { CROAD::DEFAULT_ROAD,CROAD::DOTTED_ROAD };
	//mSceneLayers[Road]
}