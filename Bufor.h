#pragma once
#include <iostream>
#include <random>
#include "Cialo.h"
#include <thread>
#include <mutex>

using namespace std;


class Bufor{
	public:
		Bufor(const int size);
		~Bufor();
		void setRandom(double minDist, double maxDist, double minW, double maxW);
		Cialo * getData();
		const int getN()const;
		void next(double deltaTime);
//		void threadWorker(int b1, int e1, double deltaTime);
//		friend void threadWorker(Bufor&, int,int);
	private:
		Cialo * data;
		const int n;
};

