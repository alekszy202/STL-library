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
- Podstawa wszystkich klas opisuj�cych sekwencyjne struktury danych.
- Dziedzicz�ca po Container.
*/
template <class T>
class Sequences : public Container<T>
{
public:

	/*1.PUSH I POP*/

	/**
	Usuni�cie ostatniego elementu i zmniejszenie wielko�ci o jeden.
	*/
	virtual void PopBack() = 0;

	/**
	Usuni�cie pierwszego elementu i zmniejszenie wielko�ci o jeden.
	*/
	virtual void PopFront() = 0;

	/**
	Dodanie nowego elementu na ko�cu kontenera, po ostatnimm oraz zwi�kszenie wielko�ci o jeden.
	@param value Nowy element.
	*/
	virtual void PushBack(const T& value) = 0;

	/**
	Dodanie nowego elementu na pocz�tku kontenera, po ostatnimm oraz zwi�kszenie wielko�ci o jeden.
	@param value Nowy element.
	*/
	virtual void PushFront(const T& value) = 0;



	/*2.WPROWADZANIE DANYCH*/

	/**
	Dodanie elementu przed podan� pozycj� i zwi�kszenie jego wieko�ci.
	@param position Pozycja, przed kt�r� metoda wstawia element.
	@param value Nowy element.
	*/
	virtual void Insert(int position, const T& value) = 0;
	/**
	Wype�nienie kontenera elementem przed podan� pozycj� i zwi�kszenie jego wieko�ci.
	@param position Pozycja, przed kt�r� metoda wstawia element.
	@param n Ilo�� kopii nowego elementu do wstawienia.
	@param value Nowy element.
	*/
	virtual void Insert(int position, int n, const T& value) = 0;
	/**
	Wype�nienie kontenera przedzia�em przed podan� pozycj� i zwi�kszenie jego wieko�ci.
	@param position Pozycja, przed kt�r� metoda wstawia element.
	@param n Ilo�� element�w do wstawienia.
	@param valuePtr Pointer na nowe elementy.
	*/
	virtual void Insert(int position, int n, T* valuePtr) = 0;

	/**
	Wstawienie nowego elementu na podan� pozycje.
	@param value Nowy element.
	@param position Pozycja, na kt�r� metoda wstawia element.
	*/
	virtual void Emplace(T value, int position) = 0;

	/**
	Zast�pienie starych element�w podanymi ze wska�nika/tablicy.
	@param count Ilo�� element�w do zast�pienia.
	@param valuePtr Pointer na nowe elementy.
	*/
	virtual void Assign(int count, T* valuePtr) = 0;
	/**
	Zast�pienie starych element�w podan� warto�ci�.
	@param count Ilo�� element�w do zast�pienia.
	@param value Nowa warto��.
	*/
	virtual void Assign(int count, const T value) = 0;

	/**
	Sprawdzenie czy element istnieje, szukany po warto�ci.
	@param value Szukana warto��.
	@return Status operacji: true je�eli jest pusty, w innym przypadku false.
	*/
	virtual bool findIfExist(const T value) = 0;



	/*3.CZYSZCZENIE I WIELKO��*/

	/**
	Sprawdzenie czy typ zmiennej jest w�a�ciwy
	@return Status operacji: true, je�eli jest; false je�li nie.
	*/
	virtual bool allowedType() = 0;

	/**
	Zwr�cenie w�a�ciwego wyzerowania dla danego typu
	@return "Zero" dla danego typu zmiennych.
	*/
	virtual T returnEmpty() = 0;

	/**
	Sprawdzenie czy kontener jest pusty.
	@return Status operacji: true je�eli jest pusty, w innym przypadku false.
	*/
	virtual bool Empty() const noexcept = 0;

	/**
	Zwr�cenie wielko�ci kontenera.
	@return Warto�� spod zmiennej size.
	*/
	virtual int Size() const noexcept = 0;

	/**
	Zniszczenie zawarto�ci kontenera i ustawienie jego wielko�ci na 0
	*/
	virtual void Clear() = 0;

	/**
	Usuni�cie wybranego elementu po pozycji.
	@param position Pozycja elementu do usuni�cia.
	*/
	virtual void Erase(int position) = 0;
	/**
	Usuni�cie wybranych element�w z przedzia�u.
	@param first Pierwszy indeks przedzia�u.
	@param last Ostatni indeks przedzia�u.
	*/
	virtual void Erase(int first, int last) = 0;

	/**
	Zwr�cenie maksymlanej ilo�ci element�w jakie jest w w stanie zmie�ci� kontener
	@return Wielko�� maksymalna kontenera.
	*/
	virtual int MaxSize() = 0;

	/**
	Zmiana wielko�ci kontenera na podan�.
	- Mniejsza ni� aktualna: uci�cie kontenera.
	- Wi�ksza ni� aktualna: nowe elementy s� puste.

	@param n Nowa wielko�� kontenera.
	*/
	virtual void Resize(int n) = 0;

	/**
	Zmiana wielko�ci kontenera na podan� i dodanie nowych element�w.
	- Mniejsza ni� aktualna: uci�cie kontenera.
	- Wi�ksza ni� aktualna: nowe elementy maj� podan� warto��.

	@param n Nowa wielko�� kontenera.
	@param value Warto�� nowych element�w.
	*/
	virtual void Resize(int n, const T& value) = 0;



	/*4.SORTOWANIE*/

	/**
	Sortowanie element�w w kontenerze
	*/
	virtual void Sort() = 0;

	/**
	Funkcja wykorzystywana w Sort()
	@param tab Wska�nik na tablic� element�w kontenera.
	@param count Ilo�� element�w w tablicy.
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
	Odwr�cenie element�w kontenera kolejno�ci�.
	*/
	virtual void Reverse() noexcept = 0;

	/**
	Wy�wietlenie wszystkich element�w kontenera.
	*/
	virtual void Show() = 0;
};