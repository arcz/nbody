#pragma once
#include <iostream>
#include <cmath>
#include "stale.h"

class Wektor {
	public:
		Wektor(const double & x, const double & y, const double & z);
		Wektor();
		const double len() const;
		Wektor operator*(const double & a) const;
		Wektor operator/(const double & a) const;
		friend Wektor operator*(const double & a, const Wektor & vec);
		friend std::ostream & operator<<(std::ostream & o, const Wektor & vec);
		Wektor operator+(const Wektor & vec) const;
		Wektor operator-(const Wektor & vec) const;
		void operator+=(const Wektor & vec);
		void operator-=(const Wektor & vec);
		void operator*=(const double & a);
		double & getX();
		double & getY();
		double & getZ();
		void clear();
	private:
		double x, y, z;
};
Wektor operator*(const double & a, const Wektor & vec);
std::ostream & operator<<(std::ostream & o, const Wektor & vec);

