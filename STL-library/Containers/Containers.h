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
- Podstaw¹ wszystkich innych klas.
*/
template <class T>
class Container
{

public:

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