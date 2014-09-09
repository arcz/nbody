#pragma once
#include <limits>
#include <random>

// Klasa reprezentująca zakres liczb zmiennoprzecinkowych
class Zakres{
	public:
		// Konstruktor, przyjmuje:
		// float min - najmniejsza wartość z zakresu
		// float max - największa wartość z zakresu
		Zakres(float min, float max): min(min), max(max){};
		// Konstruktor, przyjmuje:
		// float max - największa wartość z zakresu
		// jako najmniejsza wartość jest przyjmowane 0
		Zakres(float max): min(0), max(max){};
		// Konstruktor bezargumentowy, tworzy obiekt reprezentujący pełny zakres liczb typu float dostępny na danej architekturze
		Zakres(): min(std::numeric_limits<float>::min()), max(std::numeric_limits<float>::max()){};
		// funkcja zwracająca największą liczbę z zakresu
		float getMax()const {return max;}
		// funkcja zwracająca najmniejszą liczę z zakresu
		float getMin()const {return min;}
		// funkcja zwracająca losową liczbę z zakresu
		float getRandom()const {
			std::random_device rd;
			std::default_random_engine gen(rd());
			std::uniform_real_distribution<float> dist(min, max);
			return dist(gen);
		}
	private:
		const float min, max;

};
