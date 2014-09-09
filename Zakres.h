#pragma once
#include <limits>
#include <random>
class Zakres{
	public:
		Zakres(float min, float max): min(min), max(max){};
		Zakres(float max): min(0), max(max){};
		Zakres(): min(std::numeric_limits<float>::min()), max(std::numeric_limits<float>::max()){};
		float getMax()const {return max;}
		float getMin()const {return min;}
		float getRandom()const {
			std::random_device rd;
			std::default_random_engine gen(rd());
			std::uniform_real_distribution<float> dist(min, max);
			return dist(gen);
		}
	private:
		const float min, max;

};
