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
- podstawa wszystkich klas opisuj¹cych struktury danych bêd¹ce typu adaptor.
- dziedzicz¹ca po Container.
*/
template <class T>
class Adaptors : public Container<T>
{
public:

	/*1.PUSH I POP*/

	/**
	Dodanie nowego elementu na TOP kontenera i zwiêkszenie jego wielkoœci.
	@param value Nowy element.
	*/
	virtual void Push(const T& value) = 0;

	/**
	Usuniêcie elementu z TOPu i zmniejszenie jego wielkoœci.
	*/
	virtual void Pop() = 0;



	/*2.CZYSZCZENIE I WIELKOŒÆ*/

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
	Zniszczenie zawartoœci kontenera i ustawienie jego wielkoœci na 0.
	*/
	virtual void Clear() = 0;

	/**
	Zwrócenie maksymlanej iloœci elementów jakie jest w w stanie zmieœciæ kontener.
	@return Maksymalna wielkoœæ kontenera.
	*/
	virtual int MaxSize() = 0;

	/**
	Wyœwietlenie wszystkich elementów kontenera.
	*/
	virtual void Show() = 0;
};