#pragma once
#include "Wektor.h"
#include "Zakres.h"
#include "stale.h"
#include <mutex>

class Cialo{
	public:
		Cialo();
		Cialo(const Cialo & dane);
		Cialo(const Wektor& pozycja, const double& masa);
		Cialo(const Zakres& zakPoz, const Zakres& zakMasa);
		Wektor & getPoz();
		Wektor & getPred();
		Wektor & getSila();
		void set(const Zakres& zakPoz, const Zakres& zakMasa);
		const double & getMasa() const;
		// siła działająca na ciało pochodząca od grawitacji ciała drugiego
		Wektor silaPomiedzy(const Cialo & drugie) const;
		// aktualizacja pozycji i predkości na podstawie aktualnej siły
		void aktualizuj(double deltaTime);
		// zeruje siłę
		void clearF();
		std::mutex mut;
	private:
		Wektor poz, pred, sila;
		double masa;
};
