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
- podstawa wszystkich klas opisuj¹cych struktury danych bêd¹ce typu asocjacyjnego.
- dziedzicz¹ca po Container.
*/
template <class T>
class Associative : public Container<T>
{
public:

	/*4.PUSH I POP*/

	/**
	Usuniêcie ostatniego elementu i zmniejszenie wielkoœci o jeden.
	*/
	virtual void PopBack() = 0;

	/**
	Usuniêcie pierwszego elementu i zmniejszenie wielkoœci o jeden.
	*/
	virtual void PopFront() = 0;



	/*7.CZYSZCZENIE I WIELKO??*/

	/**
	Sprawdzenie czy typ zmiennej jest w³aœciwy
	@return Status operacji: true, je¿eli jest; false jeœli nie.
	*/
	virtual bool allowedType() = 0;

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
	virtual void Clear() noexcept = 0;

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



	/*8.SORTOWANIE/PRZESTAWIANIE*/

	/**
	Odwrócenie elementów kontenera kolejnoœci¹.
	*/
	virtual void Reverse() noexcept = 0;

	/**
	Sortowanie elementów w kontenerze
	*/
	virtual void Sort() = 0;

	/**
	Wyœwietlenie wszystkich elementów kontenera.
	*/
	virtual void Show() = 0;
};