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
		void setRandom(float minDist, float maxDist, float minW, float maxW);
		Cialo * getData();
		const int getN()const;
		void next(float deltaTime);
//		void threadWorker(int b1, int e1, float deltaTime);
//		friend void threadWorker(Bufor&, int,int);
	private:
		Cialo * data;
		const int n;
};

