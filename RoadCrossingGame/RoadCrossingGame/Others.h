#ifndef OTHERS_H
#define OTHERS_H
#include <random>
#include <cstdlib>
#include<time.h>
#include "COBSTACLE.h"

int randInt(int min, int max) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

float randPos(float min, float max) {
	static std::random_device rd;
    static std::default_random_engine engine(rd());
	std::uniform_real_distribution<float> dist(min, max);
	return dist(engine);
}

int randBiasedInt(int minValue, int maxValue, double probabilityOfZeroToOne) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    double randomValue = distribution(gen);

    if (randomValue < probabilityOfZeroToOne) {
        return minValue;
    }
    else {
        std::uniform_int_distribution<int> intDistribution(minValue, maxValue);
        return intDistribution(gen);
    }
}

int randObject(int minValue, int maxValue, double probabilityOfZeroToOne) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    double randomValue = distribution(gen);

    if (randomValue < probabilityOfZeroToOne) {
        std::uniform_int_distribution<int> intDistribution1(minValue, minValue + 2);
        return intDistribution1(gen);
    }
    else {
        std::uniform_int_distribution<int> intDistribution2(minValue, maxValue);
        return intDistribution2(gen);
    }
}


int isIntersect(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
    return (int)rect1.intersects(rect2);

int randEvenOdd(int lb, int ub, bool isOdd) {
    int randNum = 2 * (rand() % ((ub - lb) / 2 + 1)) + lb;
    int randNum2 = 2 * (rand() % ((ub - 2 - lb) / 2 + 1)) + lb;
    if (isOdd) {
        if (lb % 2 == 0 && ub % 2 == 0) {
            return randNum2;
        }
        else if (lb % 2 == 0) {
            return randNum + 1;
        }
        else if (lb % 2 != 0) {
            return randNum;
        }
    }
    else {
        if (lb % 2 != 0 && ub % 2 != 0) {
            return 2 * (rand() % ((ub - 2 - lb) / 2 + 1)) + lb;
        }
        else if (lb % 2 != 0) {
            return randNum + 1;
        }
        else if (lb % 2 == 0) {
            return randNum;
        }
    }
}
#endif // !OTHERS_H
