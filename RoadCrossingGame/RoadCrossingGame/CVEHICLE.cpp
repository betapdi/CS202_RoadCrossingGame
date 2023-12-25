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
}*/

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
	/*this->spawnerTime += deltaTime;
	if (this->spawnerTime >= this->spawnTimeMax) {
		this->spawnerTime = 0.f;
	}

	this->sprite.move(mDirection * 2.0f, 0);*/
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