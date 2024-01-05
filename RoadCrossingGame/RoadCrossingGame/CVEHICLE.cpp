#include "CVEHICLE.h"
#include "CRESOURCEHOLDER.h"

/*CVEHICLE::CVEHICLE() {
	//
}

void CVEHICLE::updateCurrent(float deltaTime)
{
}

void CVEHICLE::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}
*/
/*Textures::ID toTextureID(CVEHICLE::Vehicle type) {
	switch (type) {
	case CVEHICLE::BLUE_CAR_L:
		return Textures::BLUE_CAR_L;
		break;
	case CVEHICLE::BLUE_CAR_R:
		return Textures::BLUE_CAR_R;
		break;
	case CVEHICLE::GREEN_CAR_L:
		return Textures::GREEN_CAR_L;
		break;
	case CVEHICLE::GREEN_CAR_R:
		return Textures::GREEN_CAR_R;
		break;
		/*case CVEHICLE::ORANGE_CAR_L:
			return Textures::ORANGE_CAR_L;
			break;
		case CVEHICLE::ORANGE_CAR_R:
			return Textures::ORANGE_CAR_R;
			break;
	case CVEHICLE::RED_CAR_L:
		return Textures::RED_CAR_L;
		break;
	case CVEHICLE::RED_CAR_R:
		return Textures::RED_CAR_R;
		break;
	case CVEHICLE::TRUCK_L:
		return Textures::TRUCK_L;
		break;
	case CVEHICLE::TRUCK_R:
		return Textures::TRUCK_R;
		break;
	case CVEHICLE::BUS_L:
		return Textures::BUS_L;
		break;
	case CVEHICLE::BUS_R:
		return Textures::BUS_R;
		break;
	}
}

CVEHICLE::Vehicle fromIntToType(int type) {
	switch (type) {
	case 0:
		return CVEHICLE::BLUE_CAR_L;
		break;
	case 1:
		return CVEHICLE::BLUE_CAR_R;
		break;
	case 2:
		return CVEHICLE::GREEN_CAR_L;
		break;
	case 3:
		return CVEHICLE::GREEN_CAR_R;
		break;
		//case 4:
			//return CVEHICLE::ORANGE_CAR_L;
			//break;
		//case 5:
			//return CVEHICLE::ORANGE_CAR_R;
			//break;
	case 4:
		return CVEHICLE::RED_CAR_L;
		break;
	case 5:
		return CVEHICLE::RED_CAR_R;
		break;
	case 6:
		return CVEHICLE::TRUCK_L;
		break;
	case 7:
		return CVEHICLE::TRUCK_R;
		break;
	case 8:
		return CVEHICLE::BUS_L;
		break;
	case 9:
		return CVEHICLE::BUS_R;
		break;
	}
}

int CVEHICLE::fromIntToDir(int dir) {
	if (dir % 2 != 0) {
		return 1;
	}
	else return -1;
}

sf::FloatRect CVEHICLE::getBound() const
{
	return this->sprite.getGlobalBounds();
}


CVEHICLE::CVEHICLE(int type, const TextureHolder& textures, sf::Vector2f position, float speedMove)
	: mType(fromIntToType(type))
	, mDirection(fromIntToDir(type))
	, sprite(textures.get(toTextureID(mType)))
	, speedMove(speedMove)
{
	//initSprite(position);
	this->spawnTimeMax = 50.f;
	this->spawnerTime = this->spawnTimeMax;
	this->deltaTime = 0.1f;
	std::cout << "Direction: " << this->mDirection << std::endl;
	sprite.setPosition(position.x, position.y);
	if (type == 8 || type == 9) {
		sprite.setScale(0.5f, 0.5f);
	}
	sprite.setScale(2.f, 2.f);
	///*sf::FloatRect bounds = mAnimation.getLocalBounds();
	//mAnimation.setOrigin(bounds.width / 2, 0);
}

/*void CVEHICLE::initSprite(sf::Vector2f position)
{
	this->sprite.setTexture(this->mTexture);
	this->sprite.setScale(1.5f, 1.5f);
	this->sprite.setPosition(position.x, position.y);
}

void CVEHICLE::updateCurrent(float deltaTime)
{
	//mAnimation.update(deltaTime);
	//if (mWorldBound.intersects(mAnimation.getGlobalBounds())) {
	//sf::Vector2f getPos = mAnimation.getPosition();
	//if (getPos.x >= Constants::SCREEN_WIDTH || getPos.x <= 0) {
	//	mAnimation.setPosition(orgPos);
	//}
	//mAnimation.move(mDirection * mSpeed * deltaTime, 0);
	//}
	//deltaTime = 1;
	this->spawnerTime += deltaTime;
	if (this->spawnerTime >= this->spawnTimeMax) {
		this->spawnerTime = 0.f;
	}

	this->sprite.move(mDirection * 2.0f, 0);
	updateVehicle();
}
void CVEHICLE::updateVehicle()
{
	this->spawnerTime += deltaTime;
	if (this->spawnerTime >= this->spawnTimeMax) {
		this->spawnerTime = 0.f;
	}
	this->sprite.move(mDirection * this->speedMove, 0);
}
int CVEHICLE::getDirection()
{
	return mDirection;
}

void CVEHICLE::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite, states);
}
*/
Textures::ID toTextureID(CVEHICLE::Vehicle type) {
	switch (type) {
	case CVEHICLE::BLUE_CAR_L:
		return Textures::BLUE_CAR_L;
		break;
	case CVEHICLE::BLUE_CAR_R:
		return Textures::BLUE_CAR_R;
		break;
	case CVEHICLE::GREEN_CAR_L:
		return Textures::GREEN_CAR_L;
		break;
	case CVEHICLE::GREEN_CAR_R:
		return Textures::GREEN_CAR_R;
		break;
		/*case CVEHICLE::ORANGE_CAR_L:
			return Textures::ORANGE_CAR_L;
			break;
		case CVEHICLE::ORANGE_CAR_R:
			return Textures::ORANGE_CAR_R;
			break;*/
	case CVEHICLE::RED_CAR_L:
		return Textures::RED_CAR_L;
		break;
	case CVEHICLE::RED_CAR_R:
		return Textures::RED_CAR_R;
		break;
	case CVEHICLE::TRUCK_L:
		return Textures::TRUCK_L;
		break;
	case CVEHICLE::TRUCK_R:
		return Textures::TRUCK_R;
		break;
	case CVEHICLE::OLD_TRAIN_L:
		return Textures::OLD_TRAIN_L;
		break;
	case CVEHICLE::OLD_TRAIN_R:
		return Textures::OLD_TRAIN_R;
		break;
	case CVEHICLE::TRAIN_L:
		return Textures::TRAIN_L;
		break;
	case CVEHICLE::TRAIN_R:
		return Textures::TRAIN_R;
		break;
		/*case CVEHICLE::BUS_L:
			return Textures::BUS_L;
			break;
		case CVEHICLE::BUS_R:
			return Textures::BUS_R;
			break;*/
	}
}

CVEHICLE::Vehicle fromIntToType(int type) {
	switch (type) {
	case 0:
		return CVEHICLE::BLUE_CAR_L;
		break;
	case 1:
		return CVEHICLE::BLUE_CAR_R;
		break;
	case 2:
		return CVEHICLE::GREEN_CAR_L;
		break;
	case 3:
		return CVEHICLE::GREEN_CAR_R;
		break;
		//case 4:
			//return CVEHICLE::ORANGE_CAR_L;
			//break;
		//case 5:
			//return CVEHICLE::ORANGE_CAR_R;
			//break;
	case 4:
		return CVEHICLE::RED_CAR_L;
		break;
	case 5:
		return CVEHICLE::RED_CAR_R;
		break;
	case 6:
		return CVEHICLE::TRUCK_L;
		break;
	case 7:
		return CVEHICLE::TRUCK_R;
		break;
		/*case 8:
			return CVEHICLE::BUS_L;
			break;
		case 9:
			return CVEHICLE::BUS_R;
			break;*/
	case 8:
		return CVEHICLE::OLD_TRAIN_L;
		break;
	case 9:
		return CVEHICLE::OLD_TRAIN_R;
		break;
	case 10:
		return CVEHICLE::TRAIN_L;
		break;
	case 11:
		return CVEHICLE::TRAIN_R;
		break;
	}
}

int CVEHICLE::fromIntToDir(int dir) {
	if (dir % 2 == 0) {
		return -1;
	}
	else {
		return 1;
	}
}

/*sf::FloatRect CVEHICLE::getBound() const
{
	return this->sprite.getGlobalBounds();
}


CVEHICLE::CVEHICLE(int type, const TextureHolder& textures, sf::Vector2f position, float speedMove)
	: mType(fromIntToType(type))
	, mDirection(fromIntToDir(type))
	, sprite(textures.get(toTextureID(mType)))
	, speedMove(speedMove)
{
	//initSprite(position);
	//this->spawnTimeMax = 50.f;
	//this->spawnerTime = this->spawnTimeMax;
	//this->deltaTime = 40.f;
	std::cout << "Direction: " << this->mDirection << std::endl;
	sprite.setPosition(position.x, position.y);
	sprite.setScale(2.f, 2.f);
	if (type == 10 || type == 11) {
		sprite.setScale(1.2f, 1.2f);
	}
	//sprite.setScale(2.f, 2.f);
	///*sf::FloatRect bounds = mAnimation.getLocalBounds();
	//mAnimation.setOrigin(bounds.width / 2, 0);
}

void CVEHICLE::initSprite(sf::Vector2f position)
{
	this->sprite.setTexture(this->mTexture);
	this->sprite.setScale(1.5f, 1.5f);
	this->sprite.setPosition(position.x, position.y);
}

void CVEHICLE::updateCurrent(float deltaTime)
{
	//mAnimation.update(deltaTime);
	//if (mWorldBound.intersects(mAnimation.getGlobalBounds())) {
	//sf::Vector2f getPos = mAnimation.getPosition();
	//if (getPos.x >= Constants::SCREEN_WIDTH || getPos.x <= 0) {
	//	mAnimation.setPosition(orgPos);
	//}
	//mAnimation.move(mDirection * mSpeed * deltaTime, 0);
	//}
	//deltaTime = 1;
	this->spawnerTime += deltaTime;
	if (this->spawnerTime >= this->spawnTimeMax) {
		this->spawnerTime = 0.f;
	}

	this->sprite.move(mDirection * 2.0f, 0);
	updateVehicle(deltaTime);
}
void CVEHICLE::updateVehicle(float deltaTime)
{
	this->spawnerTime += deltaTime;
	if (this->spawnerTime >= this->spawnTimeMax) {
		this->sprite.move(mDirection * this->speedMove * deltaTime, 0);
		this->spawnerTime = 0.f;
	}
	this->sprite.move(mDirection * this->speedMove * deltaTime, 0);
}
int CVEHICLE::getDirection()
{
	return mDirection;
}

void CVEHICLE::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite, states);
}*/



/*CTRAIN::CTRAIN(int type, sf::FloatRect mWorldBound, const TextureHolder& textures, float speedMove, float frameTime)
	: mType(fromIntToType(type))
	, mWorldBound(mWorldBound)
	, mSpeed(speedMove)
	, mDirection(fromIntToDir(type))
	, mAnimation(textures.get(toTextureID(mType)), getFrameNum(type), frameTime)
{
	mAnimation.setScale(1.2, 1.2);
	sf::FloatRect bounds = mAnimation.getLocalBounds();
	mAnimation.setOrigin(bounds.width / 2, 0);
}

sf::Vector2i CTRAIN::getFrameNum(int type) {
	if (type == 10 || type == 11) {
		return sf::Vector2i(3, 1);
	}
	else if(type == 8 || type == 9) return sf::Vector2i(4, 1);
	//return sf::Vector2i(4, 1);
}

void CTRAIN::saveOrgPos(const sf::Vector2f& position) {
	orgPos = position;
}

void CTRAIN::updateCurrent(float deltaTime) {
	mAnimation.update(deltaTime);
	mAnimation.move(mDirection * mSpeed * deltaTime, 0);

}

sf::FloatRect CTRAIN::getBound() const
{
	return mAnimation.getGlobalBounds();
}

int CANIMAL::getDirection() {
	return mDirection;
}

void CTRAIN::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mAnimation, states);
}*/

CVEHICLE::CVEHICLE(int type, sf::FloatRect mWorldBound, const TextureHolder& textures, float speedMove, float frameTime)
	: mType(fromIntToType(type))
	, mWorldBound(mWorldBound)
	, mSpeed(speedMove)
	, mDirection(fromIntToDir(type))
	, mAnimation(textures.get(toTextureID(mType)), getFrameNum(type), frameTime)
{
	if (type == 8 || type == 9) {
		mAnimation.setScale(1.2f, 1.2f);
	}
	else if (type == 10 || type == 11) {
		mAnimation.setScale(1.5f, 1.5f);
	}
	else {
		mAnimation.setScale(2.5f, 2.5f);
	}
	/*sf::FloatRect bounds = mAnimation.getLocalBounds();
	mAnimation.setOrigin(bounds.width / 2, 0);*/
}

sf::Vector2i CVEHICLE::getFrameNum(int type) {
	if (type == 8 || type == 9) {
		return sf::Vector2i(4, 1);
	}
	else if (type == 10 || type == 11) {
		return sf::Vector2i(3, 1);
	}
	else {
		return sf::Vector2i(1, 1);
	}
}

void CVEHICLE::saveOrgPos(const sf::Vector2f& position) {
	orgPos = position;
}

void CVEHICLE::updateCurrent(float deltaTime) {
	mAnimation.update(deltaTime);
	mAnimation.move(mDirection * mSpeed * deltaTime, 0);
}

int CVEHICLE::getDirection() {
	return mDirection;
}

void CVEHICLE::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mAnimation, states);
}

bool CVEHICLE::isIntersect(const sf::FloatRect& rect) {
	sf::FloatRect currRect = getBorder();
	//std::cout << rect.left << " " << rect.top << std::endl;
	//std::cout << currRect.left << " " << currRect.top << " " << orgPos.x << " " << orgPos.y << std::endl;
	return currRect.intersects(rect);
}

sf::FloatRect CVEHICLE::getBorder() {
	return sf::FloatRect(mAnimation.getGlobalBounds().left + orgPos.x, mAnimation.getGlobalBounds().top + orgPos.y, mAnimation.getGlobalBounds().width, mAnimation.getGlobalBounds().height);
}

sf::FloatRect CVEHICLE::getBound() const
{
	return mAnimation.getGlobalBounds();
}