#ifndef OTHERS_H
#define OTHERS_H
#include <random>

int randInt(int min, int max) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

int randBiasedInt(int minValue, int maxValue, double probabilityOfZeroToOne) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    double randomValue = distribution(gen);

    if (randomValue < probabilityOfZeroToOne) {
        return 0;
    }
    else {
        std::uniform_int_distribution<int> intDistribution(minValue, maxValue);
        return intDistribution(gen);
    }
}


//void GWORLD::generateObstacle() {
//	for (int i = mWorldBounds.top + mWorldBounds.height; i <= mWorldBounds.height; i -= Constants::ROAD_SIZE) {
//		int isPrint = randInt(0, 1);
//		if (isPrint) {
//			int numOfObstacle = randInt(0, Constants::maxObstacle);
//			for (int j = 0; j < numOfObstacle; ++j) {
//				int startPos = j * (mWorldBounds.width / numOfObstacle);
//				int endPos = startPos + mWorldBounds.width / numOfObstacle;
//				int type = randInt(0, COBSTACLE::SHOP_2);
//
//				std::unique_ptr<COBSTACLE> obstacle(new COBSTACLE(type, mTextures));
//				obstacle->setPosition(randInt(startPos, endPos), i);
//				mSceneLayers[Obstacle]->attachChild(std::move(obstacle));
//			}
//		}
//	}
//}
#endif // !OTHERS_H
