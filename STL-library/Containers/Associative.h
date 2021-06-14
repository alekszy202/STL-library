#pragma once
#include <iostream>
#include <limits>
#include <regex>
#include <iterator>
#include <exception>
#include <sstream>
#include "Containers.h"

/**
Deklaracja klasy Associative.
- podstawa wszystkich klas opisuj�cych struktury danych b�d�ce typu asocjacyjnego.
- dziedzicz�ca po Container.
*/
template <class T>
class Associative : public Container<T>
{
public:

	/*4.PUSH I POP*/

	/**
	Usuni�cie ostatniego elementu i zmniejszenie wielko�ci o jeden.
	*/
	virtual void PopBack() = 0;

	/**
	Usuni�cie pierwszego elementu i zmniejszenie wielko�ci o jeden.
	*/
	virtual void PopFront() = 0;



	/*7.CZYSZCZENIE I WIELKO??*/

	/**
	Sprawdzenie czy typ zmiennej jest w�a�ciwy
	@return Status operacji: true, je�eli jest; false je�li nie.
	*/
	virtual bool allowedType() = 0;

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
	virtual void Clear() noexcept = 0;

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



	/*8.SORTOWANIE/PRZESTAWIANIE*/

	/**
	Odwr�cenie element�w kontenera kolejno�ci�.
	*/
	virtual void Reverse() noexcept = 0;

	/**
	Sortowanie element�w w kontenerze
	*/
	virtual void Sort() = 0;

	/**
	Wy�wietlenie wszystkich element�w kontenera.
	*/
	virtual void Show() = 0;
};