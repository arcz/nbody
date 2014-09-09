#pragma once
#include <iostream>
#include <cmath>
#include "stale.h"
// Klasa reprezentująca wektor trój-wymiarowy
class Wektor {
	public:
		// Konstruktor, przyjmuje i ustawia poszczególne parametry wektora
		Wektor(const float & x, const float & y, const float & z);
		// Konsturktor bezargumentowy, ustawia parametry wektora na 0
		Wektor();
		// funkcja zwracająca długość wektora, jeżeli długość wyniesie nie więcej niż S::Epsil, zwrócone zostanie S::Epsil
		const float len() const;
		//operatory działań na wektorach
		Wektor operator*(const float & a) const;
		Wektor operator/(const float & a) const;
		friend Wektor operator*(const float & a, const Wektor & vec);
		friend std::ostream & operator<<(std::ostream & o, const Wektor & vec);
		Wektor operator+(const Wektor & vec) const;
		Wektor operator-(const Wektor & vec) const;
		void operator+=(const Wektor & vec);
		void operator-=(const Wektor & vec);
		void operator*=(const float & a);
		// zwraca odpowiednie parametry wektora
		float & getX();
		float & getY();
		float & getZ();
		// ustawia parametry wektora na 0
		void clear();
	private:
		float x, y, z;
};
Wektor operator*(const float & a, const Wektor & vec);
std::ostream & operator<<(std::ostream & o, const Wektor & vec);

