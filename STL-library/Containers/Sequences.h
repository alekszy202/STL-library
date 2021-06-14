#pragma once
#include <iostream>
#include <limits>
#include <regex>
#include <iterator>
#include <exception>
#include <sstream>
#include "Containers.h"

using namespace std;

/**
Deklaracja klasy Sequences.
- Podstawa wszystkich klas opisuj¹cych sekwencyjne struktury danych.
- Dziedzicz¹ca po Container.
*/
template <class T>
class Sequences : public Container<T>
{
public:

	/*1.PUSH I POP*/

	/**
	Usuniêcie ostatniego elementu i zmniejszenie wielkoœci o jeden.
	*/
	virtual void PopBack() = 0;

	/**
	Usuniêcie pierwszego elementu i zmniejszenie wielkoœci o jeden.
	*/
	virtual void PopFront() = 0;

	/**
	Dodanie nowego elementu na koñcu kontenera, po ostatnimm oraz zwiêkszenie wielkoœci o jeden.
	@param value Nowy element.
	*/
	virtual void PushBack(const T& value) = 0;

	/**
	Dodanie nowego elementu na pocz¹tku kontenera, po ostatnimm oraz zwiêkszenie wielkoœci o jeden.
	@param value Nowy element.
	*/
	virtual void PushFront(const T& value) = 0;



	/*2.WPROWADZANIE DANYCH*/

	/**
	Dodanie elementu przed podan¹ pozycj¹ i zwiêkszenie jego wiekoœci.
	@param position Pozycja, przed któr¹ metoda wstawia element.
	@param value Nowy element.
	*/
	virtual void Insert(int position, const T& value) = 0;
	/**
	Wype³nienie kontenera elementem przed podan¹ pozycj¹ i zwiêkszenie jego wiekoœci.
	@param position Pozycja, przed któr¹ metoda wstawia element.
	@param n Iloœæ kopii nowego elementu do wstawienia.
	@param value Nowy element.
	*/
	virtual void Insert(int position, int n, const T& value) = 0;
	/**
	Wype³nienie kontenera przedzia³em przed podan¹ pozycj¹ i zwiêkszenie jego wiekoœci.
	@param position Pozycja, przed któr¹ metoda wstawia element.
	@param n Iloœæ elementów do wstawienia.
	@param valuePtr Pointer na nowe elementy.
	*/
	virtual void Insert(int position, int n, T* valuePtr) = 0;

	/**
	Wstawienie nowego elementu na podan¹ pozycje.
	@param value Nowy element.
	@param position Pozycja, na któr¹ metoda wstawia element.
	*/
	virtual void Emplace(T value, int position) = 0;

	/**
	Zast¹pienie starych elementów podanymi ze wskaŸnika/tablicy.
	@param count Iloœæ elementów do zast¹pienia.
	@param valuePtr Pointer na nowe elementy.
	*/
	virtual void Assign(int count, T* valuePtr) = 0;
	/**
	Zast¹pienie starych elementów podan¹ wartoœci¹.
	@param count Iloœæ elementów do zast¹pienia.
	@param value Nowa wartoœæ.
	*/
	virtual void Assign(int count, const T value) = 0;

	/**
	Sprawdzenie czy element istnieje, szukany po wartoœci.
	@param value Szukana wartoœæ.
	@return Status operacji: true je¿eli jest pusty, w innym przypadku false.
	*/
	virtual bool findIfExist(const T value) = 0;



	/*3.CZYSZCZENIE I WIELKOŒÆ*/

	/**
	Sprawdzenie czy typ zmiennej jest w³aœciwy
	@return Status operacji: true, je¿eli jest; false jeœli nie.
	*/
	virtual bool allowedType() = 0;

	/**
	Zwrócenie w³aœciwego wyzerowania dla danego typu
	@return "Zero" dla danego typu zmiennych.
	*/
	virtual T returnEmpty() = 0;

	/**
	Sprawdzenie czy kontener jest pusty.
	@return Status operacji: true je¿eli jest pusty, w innym przypadku false.
	*/
	virtual bool Empty() const noexcept = 0;

	/**
	Zwrócenie wielkoœci kontenera.
	@return Wartoœæ spod zmiennej size.
	*/
	virtual int Size() const noexcept = 0;

	/**
	Zniszczenie zawartoœci kontenera i ustawienie jego wielkoœci na 0
	*/
	virtual void Clear() = 0;

	/**
	Usuniêcie wybranego elementu po pozycji.
	@param position Pozycja elementu do usuniêcia.
	*/
	virtual void Erase(int position) = 0;
	/**
	Usuniêcie wybranych elementów z przedzia³u.
	@param first Pierwszy indeks przedzia³u.
	@param last Ostatni indeks przedzia³u.
	*/
	virtual void Erase(int first, int last) = 0;

	/**
	Zwrócenie maksymlanej iloœci elementów jakie jest w w stanie zmieœciæ kontener
	@return Wielkoœæ maksymalna kontenera.
	*/
	virtual int MaxSize() = 0;

	/**
	Zmiana wielkoœci kontenera na podan¹.
	- Mniejsza ni¿ aktualna: uciêcie kontenera.
	- Wiêksza ni¿ aktualna: nowe elementy s¹ puste.

	@param n Nowa wielkoœæ kontenera.
	*/
	virtual void Resize(int n) = 0;

	/**
	Zmiana wielkoœci kontenera na podan¹ i dodanie nowych elementów.
	- Mniejsza ni¿ aktualna: uciêcie kontenera.
	- Wiêksza ni¿ aktualna: nowe elementy maj¹ podan¹ wartoœæ.

	@param n Nowa wielkoœæ kontenera.
	@param value Wartoœæ nowych elementów.
	*/
	virtual void Resize(int n, const T& value) = 0;



	/*4.SORTOWANIE*/

	/**
	Sortowanie elementów w kontenerze
	*/
	virtual void Sort() = 0;

	/**
	Funkcja wykorzystywana w Sort()
	@param tab WskaŸnik na tablicê elementów kontenera.
	@param count Iloœæ elementów w tablicy.
	*/
	void insertionsort(T* tab, int count)
	{
		int i, j;
		T v;
		for (i = 1; i < count; i++)
		{
			j = i;
			v = tab[i];
			while ((j > 0) && (tab[j - 1] > v))
			{
				tab[j] = tab[j - 1];
				j--;
			}
			tab[j] = v;
		}
	}

	/**
	Odwrócenie elementów kontenera kolejnoœci¹.
	*/
	virtual void Reverse() noexcept = 0;

	/**
	Wyœwietlenie wszystkich elementów kontenera.
	*/
	virtual void Show() = 0;
};