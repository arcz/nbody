#pragma once
#include <iostream>
#include <random>
#include "Cialo.h"
#include <thread>
#include <mutex>

using namespace std;

//Klasa reprezentująca bufor przechowujący dane o wszystkich cząsteczkach
class Bufor{
	public:
		//Konstruktor, przyjmuje:
		//int size - ilość cząsteczek
		Bufor(const int size);
		~Bufor();
		//funkcja generująca wstępne dane w buforze, przyjmuje:
		//float minDist - minimalne przesunięcie począkowe
		//float maxDist - maksmalne przesunięcie początkowe
		//float minM - minimalna masa cząsteczki
		//float maxM - maksymalna masa cząsteczki
		void setRandom(float minDist, float maxDist, float minM, float maxM);
		//funkcja zwracająca tablicę obiektów typu Cialo, które reprezentują poszczególne cząsteczki
		Cialo * getData();
		//funkcja zwracająca ilość cząsteczek
		const int getN()const;
		//funkcja obliczająca następny krok iteracyjny w modelu
		void next(float deltaTime);
	private:
		Cialo * data;
		const int n;
};

