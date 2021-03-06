#pragma once
#include "Item.h"
#include "Zamowienie.h"

class Koszyk
{
private:
	//Item* produkt[10];
	int id;
	Item produkt[10];
	Zamowienie* noweZamowienie;
public:
	/**
		* Konstruktor domyslny klasy Koszyk
		* <p>
		* Tworzy nowy obiekt klasy Koszyk.
		*/
	Koszyk();
	/**
	* Dodaje item do tablicy produktow.
	* @return void
	*/
	void dodajItem(Item dodawany);
	/**
	* Usuwa item z tablicy produktow.
	* @return void
	*/
	void usunItem(int idPrzedmiotuDoUsuniecia);
	/**
	* Wypisuje produkty znajdujace sie w koszyku.
	* @return void
	*/
	void wypiszKoszyk();
	/**
	* Zwraca id produktu w koszyku.
	* @return id typ int
	*/
	int zwrocId();
	Zamowienie* zwrocAdresZamowienia();
	Item zwrocItem(int idItemu);
};