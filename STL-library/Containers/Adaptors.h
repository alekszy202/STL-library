#pragma once
#include <iostream>
#include <limits>
#include <regex>
#include <iterator>
#include <exception>
#include <sstream>
#include "Containers.h"

/**
Deklaracja klasy Adaptors.
- podstawa wszystkich klas opisuj�cych struktury danych b�d�ce typu adaptor.
- dziedzicz�ca po Container.
*/
template <class T>
class Adaptors : public Container<T>
{
public:

	/*1.PUSH I POP*/

	/**
	Dodanie nowego elementu na TOP kontenera i zwi�kszenie jego wielko�ci.
	@param value Nowy element.
	*/
	virtual void Push(const T& value) = 0;

	/**
	Usuni�cie elementu z TOPu i zmniejszenie jego wielko�ci.
	*/
	virtual void Pop() = 0;



	/*2.CZYSZCZENIE I WIELKO��*/

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
	Zniszczenie zawarto�ci kontenera i ustawienie jego wielko�ci na 0.
	*/
	virtual void Clear() = 0;

	/**
	Zwr�cenie maksymlanej ilo�ci element�w jakie jest w w stanie zmie�ci� kontener.
	@return Maksymalna wielko�� kontenera.
	*/
	virtual int MaxSize() = 0;

	/**
	Wy�wietlenie wszystkich element�w kontenera.
	*/
	virtual void Show() = 0;
};