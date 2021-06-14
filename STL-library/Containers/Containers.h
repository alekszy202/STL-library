#pragma once
#include <iostream>
#include <limits>
#include <regex>
#include <iterator>
#include <exception>
#include <sstream>

using namespace std;

/**
Deklaracja klasy Container.
- Podstaw� wszystkich innych klas.
*/
template <class T>
class Container
{

public:

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