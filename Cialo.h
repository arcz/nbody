#pragma once
#include "Wektor.h"
#include "Zakres.h"
#include "stale.h"
#include <mutex>

class Cialo{
	public:
		// Konstruktor
		Cialo();
		// Konstruktor kopiujący
		Cialo(const Cialo & dane);
		// Konstruktor tworzący obiekt klasy na podstawie podanych danych, przyjmuje:
		// Wektor& pozycja - pozycja początkowa ciała
		// float& masa - masa ciała
		Cialo(const Wektor& pozycja, const float& masa);
		// Konstruktor tworzący obiekt klasy na podstawie podanych zakresów, przyjmuje:
		// Zakres& zakPoz - zakres możliwych pozycji
		// Zakres& zakMasa - zakres możliwych mas
		Cialo(const Zakres& zakPoz, const Zakres& zakMasa);
		// funkcja zwracająca pozycję ciała
		Wektor & getPoz();
		// funkcja zwracająca prędkość ciała
		Wektor & getPred();
		// funkcja zwracająca wypadkową siłę aktualnie działającą na ciało
		Wektor & getSila();
		// funkcja funkcja ustawiająca parametry obiektu na wartości z podanych zakresów, przyjmuje:
		// Zakres& zakPoz - zakres możliwych pozycji
		// Zakres& zakMasa - zakres możliwych mas	
		void set(const Zakres& zakPoz, const Zakres& zakMasa);
		// funkcja zwracająca masę ciała
		const float & getMasa() const;
		// funkcja zwracająca siłę działająca na ciało pochodząca od grawitacji ciała drugiego, przyjmuje:
		// Cialo& drugie - referencja do ciała, względem którego ma być obliczona siła
		Wektor silaPomiedzy(const Cialo & drugie) const;
		// Funkcja aktualizująca pozycję i predkość ciała na podstawie aktualnej siły, przujmuje:
		// float deltaTime - przyrost czasu, względem którego mają być prowadzone obliczenia
		void aktualizuj(float deltaTime);
		// funkcja, która ustawia wektor siły działającej na ciało na wektor zerowy
		void clearF();
		// referencja do mutexu danego ciała
		std::mutex mut;
	private:
		Wektor poz, pred, sila;
		float masa;
};
