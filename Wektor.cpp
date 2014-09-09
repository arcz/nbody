#include "Wektor.h"

Wektor::Wektor(): x(0.0), y(0.0), z(0.0){}
Wektor::Wektor(const double & x, const double & y, const double & z): x(x), y(y), z(z){}
const double Wektor::len()const{
	double r = sqrt(x*x + y*y + z*z);
	return r > S::Epsil ? r : S::Epsil;
}

Wektor Wektor::operator*(const double & a)const {
	return Wektor(x*a, y*a, z*a);
}

Wektor Wektor::operator/(const double & a)const {
	return Wektor(x/a, y/a, z/a);
}
Wektor Wektor::operator+(const Wektor & vec) const{
	return Wektor(x+vec.x, y+vec.y, z+vec.z);
}
Wektor Wektor::operator-(const Wektor & vec) const{
	return Wektor(x-vec.x, y-vec.y, z-vec.z);
}

void Wektor::operator+=(const Wektor & vec){
	x+=vec.x;
	y+=vec.y;
	z+=vec.z;
}

void Wektor::operator-=(const Wektor & vec){
	x-=vec.x;
	y-=vec.y;
	z-=vec.z;
}
void Wektor::operator*=(const double & a){
	x*=a; y*=a; z*=a;
}		
double & Wektor::getX(){
	return x;
}
double & Wektor::getY(){
	return y;
}
double & Wektor::getZ(){
	return z;
}
void Wektor::clear(){
	x=0; y=0; z=0;
}

Wektor operator*(const double & a, const Wektor & vec){
	return vec*a;
}

std::ostream & operator<<(std::ostream & o, const Wektor & vec){
	return o << "[" << vec.x << "," << vec.y << "," << vec.z << "]";
}
