#pragma once
#include <iostream>
#include <cmath>
#include "stale.h"

class Wektor {
	public:
		Wektor(const float & x, const float & y, const float & z);
		Wektor();
		const float len() const;
		Wektor operator*(const float & a) const;
		Wektor operator/(const float & a) const;
		friend Wektor operator*(const float & a, const Wektor & vec);
		friend std::ostream & operator<<(std::ostream & o, const Wektor & vec);
		Wektor operator+(const Wektor & vec) const;
		Wektor operator-(const Wektor & vec) const;
		void operator+=(const Wektor & vec);
		void operator-=(const Wektor & vec);
		void operator*=(const float & a);
		float & getX();
		float & getY();
		float & getZ();
		void clear();
	private:
		float x, y, z;
};
Wektor operator*(const float & a, const Wektor & vec);
std::ostream & operator<<(std::ostream & o, const Wektor & vec);

