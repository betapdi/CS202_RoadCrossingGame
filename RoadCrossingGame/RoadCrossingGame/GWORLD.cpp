#include "GWORLD.h"
#include "Others.h"
GWORLD::GWORLD(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTextures()
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2048.f)
	, mRoadBounds(0.f, 0.f, mWorldView.getSize().x, Constants::ROAD_SIZE)
	, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
	, mScrollSpeed(-50.f)
	, mPlayerAircraft(nullptr)
{
	isInit = true;
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void GWORLD::update(float deltaTime)
{
	// Scroll the world
	mWorldView.move(0.f, mScrollSpeed * deltaTime);

	sf::Vector2f curView = mWorldView.getCenter();
	sf::Vector2f viewSize = mWorldView.getSize();

	//Move the player sidewards (plane scouts follow the main aircraft)
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	if (curView.y <= viewSize.y / 2) {
		// --> keep player position
		mWorldView.setCenter(mSpawnPosition);
		mPlayerAircraft->setPosition(position);
	}

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

void GWORLD::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void GWORLD::loadTextures()
{
	mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures.load(Textures::Desert, "Media/Textures/Desert.png");

	// --- ROAD TEXTURES ---
	mTextures.load(Textures::DEFAULT_ROAD,		"Media/Textures/default_road_resize.png");
	mTextures.load(Textures::DOTTED_ROAD,		"Media/Textures/white_dotted_road.png");
	mTextures.load(Textures::RAIL_ROAD,			"Media/Textures/railroad_tile.png");


	// --- PAVEMET TEXTURES ---
	mTextures.load(Textures::PAVEMENT,			"Media/Textures/pavement.png");

	// --- OBSTACLES ---
	mTextures.load(Textures::FAST_FOOD_STORE,	"Media/Textures/fast_food_store.png");
	mTextures.load(Textures::COFFEE_SHOP,		"Media/Textures/coffee_shop.png");
	mTextures.load(Textures::GROCERY,			"Media/Textures/grocery.png");
	mTextures.load(Textures::SHOP,				"Media/Textures/shop_1.png");
	mTextures.load(Textures::BARBER_SHOP,		"Media/Textures/barber_shop.png");
	mTextures.load(Textures::BREAD_SHOP,		"Media/Textures/bread_shop.png");
	mTextures.load(Textures::VEGETABLE_SHOP,	"Media/Textures/vegetable_shop.png");
	mTextures.load(Textures::HOUSE,				"Media/Textures/house.png");
	mTextures.load(Textures::BLUE_SIGN,			"Media/Textures/blue_sign.png");
	mTextures.load(Textures::GREEN_SIGN,		"Media/Textures/green_sign.png");
	mTextures.load(Textures::WHITE_SIGN,		"Media/Textures/hotdog.png");
	mTextures.load(Textures::VENDING_MACHINE,	"Media/Textures/vending_machine.png");
	mTextures.load(Textures::GRASS,				"Media/Textures/grass.png");
}

void GWORLD::buildScene()
{
	//Randomly generate road and pavement
	generatePosition(isInit);

	//std::cout << mapPos.size() << std::endl;
	//for (int i = 0; i < mapPos.size(); ++i) {
	//	std::cout << mapPos[i].first.x << " - " << mapPos[i].first.y << std::endl;
	//	std::cout << mapPos[i].second << std::endl;
	//}

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
	//mSceneLayers[Background]->attachChild(std::move(backgroundSprite));


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
	generateRoads();
	//generateObstacle();
}

void GWORLD::generatePosition(bool isInit) {
	if (isInit) {
		for (int i = 0; i < 3; ++i) {
			mapPos.push_back(std::pair<sf::Vector2f, int>(sf::Vector2f(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height - i * Constants::ROAD_SIZE),0));
		}
		for (int i = mWorldBounds.top + mWorldBounds.height - 3 * Constants::ROAD_SIZE; i >= mWorldBounds.top; i -= Constants::ROAD_SIZE) {
			int isRoad = randBiasedInt(0, 2, 0.1);
			mapPos.push_back(std::pair<sf::Vector2f, int>(sf::Vector2f(mWorldBounds.left, i), isRoad));
		}
		isInit = 0;
	}
	else {
		for (int i = mWorldBounds.top + mWorldBounds.height; i >= mWorldBounds.top; i -= Constants::ROAD_SIZE) {
			int isRoad = randBiasedInt(0, 2, 0.1);
			mapPos.push_back(std::pair<sf::Vector2f, int>(sf::Vector2f(mWorldBounds.left, i), isRoad));
		}
	}
}

void GWORLD::generateRoads() {
	for (int i = 0; i < mapPos.size(); ++i) {
		sf::IntRect textureRect1(mRoadBounds);
		sf::Texture* mText = nullptr;
		if (mapPos[i].second == 1) {
			mText = &mTextures.get(Textures::DEFAULT_ROAD);
		}
		else if (mapPos[i].second == 2) {
			mText = &mTextures.get(Textures::RAIL_ROAD);
		}
		else {
			mText = &mTextures.get(Textures::PAVEMENT);
		}
		mText->setRepeated(true);
		if (mText) {
			std::unique_ptr<CROAD> road(new CROAD(*mText, textureRect1));
			road->setPosition(mapPos[i].first);
			mSceneLayers[Road]->attachChild(std::move(road));
		}
	}
}

void GWORLD::generateObstacle() {
	for (int i = 0; i < mapPos.size(); ++i) {
		if (mapPos[i].second == 0) {
			int numOfObstacle = randInt(0, Constants::maxObstacle);
			for (int j = 0; j < numOfObstacle; ++j) {
				int startPos = j * (mWorldBounds.width / numOfObstacle);
				int endPos = startPos + mWorldBounds.width / numOfObstacle;
				int type = randInt(0, COBSTACLE::GRASS);

				std::unique_ptr<COBSTACLE> obstacle(new COBSTACLE(type, mTextures));
				obstacle->setPosition(randInt(startPos, endPos), mapPos[i].first.y);
				//std::cout << "Pos: " << obstacle->getPosition().x << " - " << obstacle->getPosition().y << std::endl;
				mSceneLayers[Obstacle]->attachChild(std::move(obstacle));
			}
		}
	}
}