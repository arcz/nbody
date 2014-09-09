#pragma once
#include <limits>
#include <random>
class Zakres{
	public:
		Zakres(double min, double max): min(min), max(max){};
		Zakres(double max): min(0), max(max){};
		Zakres(): min(std::numeric_limits<double>::min()), max(std::numeric_limits<double>::max()){};
		double getMax()const {return max;}
		double getMin()const {return min;}
		double getRandom()const {
			std::random_device rd;
			std::default_random_engine gen(rd());
			std::uniform_real_distribution<double> dist(min, max);
			return dist(gen);
		}
	private:
		const double min, max;

};
