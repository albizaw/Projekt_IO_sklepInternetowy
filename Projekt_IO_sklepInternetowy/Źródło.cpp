#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include "Konto.h"
#include "Item.h"
#include "Koszyk.h"
#include "Magazyn.h"
#include "Produkt.h"
#include "Zamowienie.h"
#include <fstream>

void wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}

using namespace std;

int ekranStarowy()
{
	system("cls");
	cout << "----------------------------------------------------" << endl;
	cout << "	Witaj w naszym sklepie internetowym! " << endl;
	cout << "----------------------------------------------------" << endl << endl;

	int wybor = 0;

	while (wybor > 3 || wybor < 1)
	{

		cout << "1. Administrator" << endl << endl;
		cout << "2. Sprzedawca" << endl << endl;
		cout << "3. Klient" << endl << endl;
		cout << "Wybierz opcje 1 - 3: ";
		cin >> wybor;
		system("cls");
		return wybor;
	}

}

int menuAdministratora()
{

	int wybor = 0;

	while (wybor > 3 || wybor < 1)
	{

		cout << "1. Dodaj produkt" << endl << endl;
		cout << "2. Usun produkt" << endl << endl;
		cout << "3. Wyswietl liste produktow" << endl << endl;
		cout << "4. Wyjscie do ekranu startowego" << endl << endl;
		cout << "Wybierz opcje 1 - 4: ";
		cin >> wybor;
		system("cls");
		return wybor;
	}
}

int menuSprzedawcy()
{
	int wybor = 0;

	while (wybor > 3 || wybor < 1)
	{

		cout << "1. Wy�wietl zam�wienia" << endl << endl;
		cout << "2. Realizuj zam�wienie" << endl << endl;
		cout << "3. Anuluj zamowienie" << endl << endl;
		cout << "4. Wyjscie do ekranu startowego" << endl << endl;
		cout << "Wybierz opcje 1 - 3: ";
		cin >> wybor;
		system("cls");
		return wybor;
	}
}

bool logowanieAdministatora(Konto adminLogowanie) {
	//to co robi administrator
		//logowanie
	
	string passAdmin = adminLogowanie.getPassword();
	string passAdminRight = adminLogowanie.getPassword();
	cout << "Wprowadz haslo administratora:	";
	for (int i = 0; i < passAdminRight.length(); i++)
	{
		passAdmin[i] = _getch();
		
		system("cls");
		cout << "Wprowadz haslo administratora:	";

		for (int j = 1; j <= i + 1; j++)
		{
			cout << "*";

		}
		
	}
	
	
	if (passAdmin == passAdminRight)
	{
		system("cls");
		cout << "zalogowano" << endl;
		return true;
	}
	else
	{
		system("cls");
		return false;
	}
}

bool logowanieSprzedawcy(Konto sprzedawcaLogowanie)
{
	string passDealer = sprzedawcaLogowanie.getPassword();
	string passDealerRight = sprzedawcaLogowanie.getPassword();
	cout << "Wprowadz haslo sprzedawcy:	";
	for (int i = 0; i < passDealerRight.length(); i++)
	{
		passDealer[i] = _getch();
		system("cls");
		cout << "Wprowadz haslo sprzedawcy:	";

		for (int j = 1; j <= i + 1; j++)
		{
			cout << "*";
		}

	}

	if (passDealer == passDealerRight)
	{
		system("cls");
		cout << "zalogowano" << endl;
		return true;
	}
	else
	{
		system("cls");
		return false;
	}
}


int main()
{
	//uwtorzenie obiektu magazyn do kt�rego zostn� wpisane produkty umieszczone w pliku tekstowym baza_produktow.txt
	Magazyn magazyn;
	string nazwa;
	float cena;
	unsigned int ilosc;
	Produkt tablicaProduktow[100];
	int i = 0;
	ifstream odczyt("baza_produktow.txt");
	while (!odczyt.eof())
	{
		odczyt >> nazwa >> cena >> ilosc;
		tablicaProduktow[i].ustawProdukt(nazwa, cena, ilosc);
		magazyn.dodajProdukt(&tablicaProduktow[i]);
		i++;
	}
	odczyt.close();
	
ekranStartowy:
	Konto administrator("Adam", "Minowski", "Silnehaslo123");
	Konto sprzedawca("Dawid", "Pala", "1234567890");
	int numerOpcji = ekranStarowy();
	if (numerOpcji == 1)
	{
		bool logowanieAdmin = logowanieAdministatora(administrator);
		int licznik = 1;
		while (logowanieAdmin == 0 && licznik != 3)
		{
			system("cls");
			logowanieAdmin = logowanieAdministatora(administrator);
			licznik++;
		}
		if (licznik == 3)
		{
			cout << "Wpisales bledne haslo. Przenosze do ekranu startowego" << endl;
			wait(3);
			system("cls");
			goto ekranStartowy;
		}

		//Poprawne zalogowanie do panelu administratora
		system("cls");
	adminMenu:
		system("cls");
		cout << "-------------------------------------------------------------" << endl;
		cout << "	Poprawnie zalogowano do panelu administratora " << endl;
		cout << "-------------------------------------------------------------" << endl << endl;

		int chooseAdmin = menuAdministratora();
		//Dodawanie produktu przez administratora do magazynu. Dopisany zostanie on automatycznie
		if (chooseAdmin == 1)
		{
			system("cls");
			cout << "-------------------------------------------------------------" << endl;
			cout << "	Dodawanie nowego produktu " << endl;
			cout << "-------------------------------------------------------------" << endl << endl;

			string nazwa;
			float cena;
			unsigned int ilosc;

			cout << "Nazwa produktu: ";
			cin >> nazwa;
			cout << "Cena: ";
			cin >> cena;
			cout << "Ilosc: ";
			cin >> ilosc;

			ofstream zapis("baza_produktow.txt", ios_base::app);
			zapis << endl << nazwa << endl;
			zapis << cena << endl;
			zapis << ilosc;

			tablicaProduktow[i].ustawProdukt(nazwa, cena, ilosc);
			cout <<  endl <<"-------------------------------------------------------------" << endl << endl;
			cout << "Dodany produkt:" << endl;
			tablicaProduktow[i].wyswietlProdukt();
			magazyn.dodajProdukt(&tablicaProduktow[i]);
			i++;
			zapis.close();
			wait(5);
			goto adminMenu;

		}

		//Usuwanie produktu przez administatora z magazynu. Zostanie r�wnie� usuni�ty z pliku baza_produktow.txt
		if (chooseAdmin == 2)
		{
			system("cls");
			cout << "-------------------------------------------------------------" << endl;
			cout << "	Usuwanie produktow z magazynu " << endl;
			cout << "-------------------------------------------------------------" << endl << endl;

			//wyswietlenie listy produktow
			magazyn.wyswietlListeProduktow();
			int wybor;
			cout << "x. Anuluj." << endl;
			cin >> wybor;
			if (wybor == 'x')
			{
				goto adminMenu;
			}
			magazyn.usunProdukt(wybor);
			
			//Przesuni�cie tablicy o 1 w lewo, po usuni�ciu produktu
			for (int q = 0; q < 100; q++)
			{
				if (wybor-1==q)
				{
					for (int j = q; j < 100-1; j++)
					{
						tablicaProduktow[j] = tablicaProduktow[j + 1];
					}
					break;
				}
			}

			//czyszczenie pliku baza_produktow.txt
			std::ofstream ofs;
			ofs.open("baza_produktow.txt", std::ofstream::out | std::ofstream::trunc);
			ofs.close();

			//wpisanie nowej tablicy do pliku
			ofstream zapis("baza_produktow.txt");
			for (int i = 0; i < 100; i++)
			{
				if (tablicaProduktow[i].zwrocNazwe() != "")
				{
					if (i == 0)
					{
						zapis << tablicaProduktow[i].zwrocNazwe() << endl;
						zapis << tablicaProduktow[i].zwrocCene() << endl;
						zapis << tablicaProduktow[i].zwrocIlosc();
					}
					else
					{
						zapis << endl << tablicaProduktow[i].zwrocNazwe() << endl;
						zapis << tablicaProduktow[i].zwrocCene() << endl;
						zapis << tablicaProduktow[i].zwrocIlosc();
					}
				}
			}
			zapis.close();
			odczyt.close();
			goto adminMenu;

		}

		//Wyswietlanie produktu przez administratora
		if (chooseAdmin == 3)
		{
			system("cls");
			cout << "-------------------------------------------------------------" << endl;
			cout << "	Wyswietlenie produktow z magazynu " << endl;
			cout << "-------------------------------------------------------------" << endl << endl;

			magazyn.wyswietlListeProduktow();

			int wybor;
			cout << "1. Powrot do panelu administratora." << endl;
			cout << "2. Powrot do menu glownego." << endl;
			cin >> wybor;
			if (wybor == 1)
			{
				goto adminMenu;
			}
			else if (wybor == 2)
			{
				goto ekranStartowy;
			}
		}
	
		//
		if (chooseAdmin == 4)
		{
			goto ekranStartowy;
		}
	}

	//menu sprzedawcy
	if (numerOpcji == 2)
	{
		
		bool logowanieSprzedawca = logowanieSprzedawcy(sprzedawca);
		int licznik = 1;
		while (logowanieSprzedawca == 0 && licznik != 3)
		{
			system("cls");
			logowanieSprzedawca = logowanieSprzedawcy(sprzedawca);
			licznik++;
		}
		if (licznik == 3)
		{
			cout << "Wpisales bledne haslo. Przenosze do ekranu startowego" << endl;
			wait(3);
			system("cls");
			goto ekranStartowy;
		}

		system("cls");
	sprzedawcaMenu:

		cout << "-------------------------------------------------------------" << endl;
		cout << "	Poprawnie zalogowano do panelu sprzedawcy " << endl;
		cout << "-------------------------------------------------------------" << endl << endl;

		int chooseDealer = menuSprzedawcy();

		if (chooseDealer == 1)
		{
			//wyswietlanie zamowien
			cout << "Dodam produkt" << endl;
		}

		if (chooseDealer == 2)
		{
			//realizacja zamowien
		}

		if (chooseDealer == 3)	
		{
			//anulowanie zamowien
		}

		if (chooseDealer == 4)
		{
			goto ekranStartowy;
		}


	}

	if (numerOpcji == 3)
	{
	}

	system("pause");
}