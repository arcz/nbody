#include "Bufor.h"

Bufor::Bufor(const int size): n(size){
	data = new Cialo[n];
}

Bufor::~Bufor(){
	delete [] data;
}
void Bufor::setRandom(double minDist, double maxDist, double minW, double maxW){
	for(int i=0; i<n;++i){
		data[i].set( Zakres(minDist, maxDist), Zakres(minW, maxW) );
	}
}

Cialo * Bufor::getData(){
	return data;
}
const int Bufor::getN()const {
	return n;
}

void milyPanPracownik(Bufor& buf, int major, int minor){
	int diff = minor - major;
	Wektor tmp;
	Cialo * data = buf.getData();
	for(int i=major; i<buf.getN(); i+=2 ){
		minor = i + diff;
		for(int j=minor; j < buf.getN() ; j+=2){
			tmp = data[i].silaPomiedzy(data[j]);
			{
			std::unique_lock<std::mutex> m(data[j].mut);
			std::unique_lock<std::mutex> n(data[i].mut);
			data[i].getSila()+=tmp;
			data[j].getSila()-=tmp;
			}

		}
	}
}

void Bufor::next(double deltaTime){
	for(int i = 0 ; i<n ; ++i) data[i].clearF();
	
	std::thread ts[4];
	ts[0] = std::thread(milyPanPracownik,std::ref(*this), 0, 1);
	ts[1] = std::thread(milyPanPracownik,std::ref(*this), 0, 2);
	ts[2] = std::thread(milyPanPracownik,std::ref(*this), 1, 2);
	ts[3] = std::thread(milyPanPracownik,std::ref(*this), 1, 3);

	for(auto& t : ts) t.join();
/*				To samo tylko bez watkow
	Wektor tmp;
	for( int i = 0; i < n; ++i){
		for(int j = i+1; j < n ; ++j){
			tmp = data[i].silaPomiedzy(data[j]);
			data[i].getSila()+= tmp;
//			std::cout <<"T:"<< tmp << std::endl 
//				<< "F:"<< data[i].getSila() << std::endl;
			data[j].getSila()-= tmp;
		}
	}*/
	for(int i = 0; i<n ; ++i) data[i].aktualizuj(deltaTime);
}

