#include "Cialo.h"
Cialo::Cialo(){}
Cialo::Cialo(const Cialo& dane):
	poz(dane.poz), pred(dane.pred) ,sila(dane.sila), masa(dane.masa){}
Cialo::Cialo(const Wektor& pozycja, const double& masa):
poz(pozycja), pred(Wektor(0,0,0)), sila(Wektor(0,0,0)), masa(abs(masa)){}

Cialo::Cialo(const Zakres& zakPoz, const Zakres& zakMasa):
	poz(Wektor(zakPoz.getRandom(), zakPoz.getRandom(), zakPoz.getRandom())),
	pred(Wektor(0,0,0)),
	sila(Wektor(0,0,0)),
	masa(zakMasa.getRandom())
	{}
void Cialo::set(const Zakres& zakPoz, const Zakres& zakMasa){
	poz = Wektor(zakPoz.getRandom(), zakPoz.getRandom(), zakPoz.getRandom());
	pred = Wektor(0,0,0);
	sila = Wektor(0,0,0);
	masa = zakMasa.getRandom();
}

Wektor & Cialo::getPoz() { return poz;}
Wektor & Cialo::getPred() { return pred;}
Wektor & Cialo::getSila() { return sila;}
const double & Cialo::getMasa() const { return masa;}

Wektor Cialo::silaPomiedzy(const Cialo & drugie) const{
	Wektor r = (drugie.poz - poz);
	double dlug = r.len();
	return (S::G*masa*drugie.masa/(dlug*dlug*dlug))*r;
//	std::cout << "R: " << dlug << " M1: "<< masa << " M2: " << drugie.masa << " F: "  << F << std::endl;

}

void Cialo::aktualizuj(double D){
	Wektor v = (sila/masa)*D;
	pred += v;
	poz += pred*D;
//	std::cout << "V:" << pred << " Vtmp: " << poz << std::endl;

}
void Cialo::clearF(){
	sila.clear();
}

