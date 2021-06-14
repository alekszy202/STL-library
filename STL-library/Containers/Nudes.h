#pragma once
#include <iostream>
using namespace std;

/**
Deklaracja klasy ListNode
- Klasa pomocnicza dla klasy List.

@param data Wartość elementu.
@param pNext Wskaźnik na nastêpny element.
*/
template <class T>
class ListNode
{
public:
	//Wartość elementu listy
	T data;
	//Wskaźnik na kolejny element
	ListNode* pNext;



	/*1.KONSTRUKTORY*/

	/**
	Konstruktor dwuargumentowy
	
	@param value Wartość do wpisania 
	@param pNext Wskaźnik na następny element
	*/
	ListNode(T value, ListNode* pNext) :
		data(value),
		pNext(pNext)
	{}
};

/**
Deklaracja klasy ListBiNode
- Klasa pomocnicza dla klasy ListBi i ListCircle.

@param data Wartoœæ elementu.
@param pNext WskaŸnik na nastêpny element.
@param pPrev WskaŸnik na poprzedni element.
*/
template <class T>
class ListBiNode
{
public:
	//Wartość elementu listy
	T data;
	//Wskaźnik na kolejny element
	ListBiNode* pNext;
	//Wskaźnik na poprzedni element
	ListBiNode* pPrev;



	/*1.KONSTRUKTORY*/

	/**
	Konstruktor trójargumentowy

	@param value Wartość do wpisania
	@param pNext Wskaźnik na następny element
	@param pPrev Wskaźnik na poprzedni element
	*/
	ListBiNode(T value, ListBiNode* pNext, ListBiNode* pPrev) :
		data(value),
		pNext(pNext),
		pPrev(pPrev)
	{}
};


/**
-Klasa pomocnicza klasy HashTable

@param key klucz dostępu do danych
@param data dane pod adresem zamieszczonym w kluczu
@param pNext wskaźnik na następny element
*/
template <class T>
class HashTableNode
{
public:
	int key;
	T data;
	HashTableNode* pNext;

	/*1.KONSTRUKTORY*/

	/**
	Konstruktor domyślny
	*/
	HashTableNode() :
		key(-1),
		data(returnEmpty()),
		pNext(nullptr)
	{}

	/**
	Konstruktor trójargumentowy

	@param _key klucz dostępu do danych
	@param _data dane pod adresem zamieszczonym w kluczu
	@param _pNext wskaźnik na następny element
	*/
	HashTableNode(int _key, T _data, HashTableNode* _pNext) :
		key(_key),
		data(_data),
		pNext(_pNext)
	{}

	/**
	Zwrócenie właściwego wyzerowania dla danego typu

	@return "Zero" dla danego typu zmiennych.
	*/
	T returnEmpty()
	{
		//Typy arytmetyczne
		if (is_arithmetic_v<T>)
		{
			return static_cast<T>(0);
		}
		else
		{
			const char* type = typeid(this).name();
			string str(type);
			regex reg("(string)");
			smatch matches;
			while (regex_search(str, matches, reg))
			{
				if (matches.ready() != 0)
				{
					T value;
					string ss;
					stringstream convert(ss);
					convert >> value;
					return value;
				}
			}
		}
	}
};

/**
-Klasa pomocnicza klasy Tree

@param data Wartość elementu.
@param pLeft Wskaźnik na lewe dziecko.
@param pRight Wskażnik na prawe dziecko.
*/
template <class T>
class TreeNode 
{
public:
	//Wartość elementu
	T data;
	//Wskaźnik na lewe dziecko
	TreeNode* pLeft;
	//Wskażnik na prawe dziecko
	TreeNode* pRight;



	/*1.KONSTRUKTORY*/

	/**
	Konstruktor domyślny
	*/
	TreeNode() :
		data(returnEmpty()),
		pLeft(nullptr),
		pRight()
	{}

	/**
	Konstruktor trójargumentowy

	@param data Wartość do wpisania.
	@param pLeft Wskaźnik na lewe dziecko.
	@param pRight Wskażnik na prawe dziecko.
	*/
	TreeNode(T data, TreeNode* pLeft, TreeNode* pRight) :
		data(data),
		pLeft(pLeft),
		pRight(pRight)
	{}

	/**
	Zwrócenie właściwego wyzerowania dla danego typu
	@return "Zero" dla danego typu zmiennych.
	*/
	T returnEmpty()
	{
		//Typy arytmetyczne
		if (is_arithmetic_v<T>)
		{
			return static_cast<T>(0);
		}
		else
		{
			const char* type = typeid(this).name();
			string str(type);
			regex reg("(string)");
			smatch matches;
			while (regex_search(str, matches, reg))
			{
				if (matches.ready() != 0)
				{
					T value;
					string ss;
					stringstream convert(ss);
					convert >> value;
					return value;
				}
			}
		}
	}
};
