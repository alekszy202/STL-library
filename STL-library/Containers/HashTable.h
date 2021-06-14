#pragma once
#include <iostream>
#include <limits>
#include <regex>
#include <iterator>
#include <exception>
#include <sstream>
#include <cstdint>
#include <functional>
#include "Containers.h"
#include "Nudes.h"

using namespace std;

/**
Deklaracja klasy HashTable
- Odpowiednik tablicy hashującej.

@param key Dynamicznie zaalokowana tablica HashTableNode
@param size Liczba wpisanych elementów
*/
template <class T>
class HashTable : public Container<T>
{
	//Dynamicznie zaalokowana tablica HashTableNode
	HashTableNode::HashTableNode<T>* dataHash;
	//Liczba zajętych miejsc
	int setValues;
	//Maksymalna ilość wpisanych elementow
	static const int maxSize = 200;



	/*FUNKCJE POMOCNICZE*/

	/**
	Funkcja hashująca.

	@param value Wartość do zashaszowania.
	@return Hash
	*/
	int HashFunction(T value)
	{
		return hash<T>{}(value);
	}

	/**
	Dodaje nowe elementy do określonej gałęzi tablicy hashującej

	@param branch Głąź do której dodajemy
	@param amoundToAdd Ilość elementów do dodania
	*/
	void addToBranch(HashTableNode<T>* branch, int amoundToAdd)
	{
		T data = branch->data;
		int key = branch->key;

		HashTableNode<T>* tmp = branch;
		while (branch->pNext)
		{
			branch = branch->pNext;
		}

		for (int i = 0; i < amoundToAdd; i++) {
			branch->pNext = new HashTableNode<T>(key, data, nullptr);
			branch = branch->pNext;
		}
	}

	/**
	Zlicza ilość elementów w danej gałęzi

	@param branch gałąź do sprawdzenia
	@return liczba elementów w gałęzi
	*/
	int lengthOfBranch(HashTableNode<T>* branch)
	{
		int branchLength = 0;
		HashTableNode<T>* tmp = branch;

		while (tmp)
		{
			branchLength++;
			tmp = tmp->pNext;
		}

		return branchLength;
	}

	/**
	Usuwanie elementów z gałęzi

	@param branch Gałąź do usunięcia
	*/
	void deleteBranch(HashTableNode<T>* branch)
	{
		if (branch)
		{
			HashTableNode<T>* tmp = branch;
			while (branch->pNext)
			{
				branch = tmp->pNext;
				delete tmp;
				tmp = branch;
			}
		}
	}

	/**
	Informacja o typie danych w kontenerze.

	@return String z nazwą typu danych.
	*/
	string showType()
	{
		//Typy arytmetyczne
		if (is_arithmetic_v<T>)
		{
			return typeid(T).name();
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
					string ss = "string";
					return ss;
				}
			}
		}
	}

public:

	/*1.KONSTRUKTORY*/

	/**
	Konstruktor domyślny
	*/
	HashTable()
	{
		if (allowedType())
		{
			this->dataHash = new HashTableNode<T>[maxSize];
			this->setValues = 0;
		}
		else
		{
			this->dataHash = nullptr;
			this->setValues = 0;
			cerr << "\n[HashTable<" << showType() << ">] " << "[Konstruktor domyslny] Niedozwolony typ!" << endl;
		}
	}

	/**
	Konstruktor jednoargumentowy.
	- Dodaje podaną wartość na element o indeksie wykawanym przez funkcję hashującą

	@param value Wartość do wpisania.
	*/
	HashTable(T value)
	{
		if (allowedType())
		{
			//Wartość jest pustym Tiem
			if (value != returnEmpty())
			{
				this->dataHash = new HashTableNode<T>[maxSize];
				this->setValues = 1;

				int hash = HashFunction(value);
				int index = abs(hash % maxSize);

				this->dataHash[index].key = hash;
				this->dataHash[index].data = value;
				this->dataHash[index].pNext = nullptr;
			}
			//Wartość nie jest pusta
			else
			{
				this->dataHash = new HashTableNode<T>[maxSize];
				this->setValues = 0;
				cerr << "\n[HashTable<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Bledny argument, stworzono pusty kontener!" << endl;
			}
		}
		else
		{
			this->dataHash = nullptr;
			this->setValues = 0;
			cerr << "\n[HashTable<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Niedozwolony typ!" << endl;
		}
	}

	/**
	Konstruktor dwuargumentowy.
	- Dodaje podaną wartość na element o indeksie wykawanym przez funkcję hashującą

	@param value Wartość do wpisania.
	@param count Liczba elementów do stworenia
	*/
	HashTable(T value, int count)
	{
		if (allowedType())
		{
			//Liczba nie wykracza poza zakres
			if (value != returnEmpty() && count >= 1)
			{
				this->dataHash = new HashTableNode<T>[maxSize];
				this->setValues = 1;

				int hash = HashFunction(value);
				int index = abs(hash % maxSize);

				this->dataHash[index].key = hash;
				this->dataHash[index].data = value;

				if (count > 1)
				{
					this->dataHash[index].pNext = new HashTableNode<T>(hash, value, nullptr);
					HashTableNode<T>* tmp = this->dataHash[index].pNext;

					for (int i = 0; i < (count - 2); i++)
					{
						tmp->pNext = new HashTableNode<T>(hash, value, nullptr);
						tmp = tmp->pNext;
					}
				}
				else if (count == 1)
				{
					this->dataHash[index].pNext = nullptr;
				}
			}
			//Wielkość wykracza poza zakres
			else
			{
				this->dataHash = new HashTableNode<T>[maxSize];
				this->setValues = 0;
				cerr << "\n[HashTable<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Bledny argument, stworzono pusty kontener!" << endl;
			}
		}
		else
		{
			this->dataHash = nullptr;
			this->setValues = 0;
			cerr << "\n[HashTable<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Niedozwolony typ!" << endl;
		}
	}

	/**
	Konstruktor kopiujący.
	- Tworzy kontener będący kopią podanego.

	@param other Wskaźnik na drugi kontener.
	*/
	HashTable(HashTable& other)
	{
		if (allowedType())
		{
			if (!other.Empty())
			{
				this->dataHash = new HashTableNode<T>[maxSize];
				this->setValues = other.setValues;

				for (int i = 0; i < maxSize; i++)
				{
					if (other.dataHash[i].key != -1)
					{
						this->dataHash[i].key = other.dataHash[i].key;
						this->dataHash[i].data = other.dataHash[i].data;
						this->dataHash[i].pNext = nullptr;

						if (other.dataHash[i].pNext)
						{
							this->dataHash[i].pNext = new HashTableNode<T>(other.dataHash[i].pNext->key, other.dataHash[i].pNext->data, nullptr);
							HashTableNode<T>* tmp = this->dataHash[i].pNext;
							HashTableNode<T>* tmpOther = other.dataHash[i].pNext;

							while (tmpOther->pNext)
							{
								tmp->pNext = new HashTableNode<T>(tmpOther->pNext->key, tmpOther->pNext->data, nullptr);
								tmp = tmp->pNext;
								tmpOther = tmpOther->pNext;
							}
						}
					}
				}
			}
			else
			{
				this->dataHash = new HashTableNode<T>[maxSize];
				this->setValues = 0;
				cerr << "\n[HashTable<" << showType() << ">] " << "[Konstruktor kopiujący] Bledny argument, stworzono pusty kontener!" << endl;
			}
		}
		else
		{
			this->dataHash = nullptr;
			this->setValues = 0;
			cerr << "\n[HashTable<" << showType() << ">] " << "[Konstruktor kopiujący] Niedozwolony typ!" << endl;
		}
	}



	/*2.DESTRUKTOR*/

	/**
	Destruktor
	- główna metoda zwalniająca pamięć
	*/
	~HashTable()
	{
		for (int i = 0; i < maxSize; i++)
		{
			if (this->dataHash[i].key != -1)
			{
				deleteBranch(this->dataHash[i].pNext);
				this->dataHash[i].pNext = nullptr;
			}
		}
		delete[] this->dataHash;
	}

	/*3.PRZECIĄŻONE OPERATORY*/

	/**
	Operator przeciążony przypisania "="

	@param value Wskaźnik na drugi kontener.
	@return Przypisany kontener.
	*/
	HashTable<T>& operator=(HashTable& rhs)
	{
		if (!rhs.Empty())
		{
			int setValues = rhs.setValues;
			this->dataHash = new HashTableNode<T>[maxSize];

			for (int i = 0; i < maxSize; i++)
			{
				if (rhs.dataHash[i].key != -1)
				{
					this->dataHash[i].key = rhs.dataHash[i].key;
					this->dataHash[i].data = rhs.dataHash[i].data;
					this->dataHash[i].pNext = nullptr;

					if (rhs.dataHash[i].pNext)
					{
						this->dataHash[i].pNext = new HashTableNode<T>(rhs.dataHash[i].pNext->key, rhs.dataHash[i].pNext->data, nullptr);
						HashTableNode<T>* tmp = this->dataHash[i].pNext;
						HashTableNode<T>* tmpRhs = rhs.dataHash[i].pNext;

						while (tmpRhs->pNext)
						{
							tmp->pNext = new HashTableNode<T>(tmpRhs->pNext->key, tmpRhs->pNext->data, nullptr);
							tmp = tmp->pNext;
							tmpRhs = tmpRhs->pNext;
						}
					}
				}
			}
		}
		else
		{
			int setValues = 0;
			this->dataHash = new HashTableNode<T>[maxSize];;
		}
		return *this;
	}

	/**
	Operator przeciążony porównania "=="

	@param rhs Wskaźnik na drugi kontener.
	@return Status operacji: true, jeżeli są równe; false jeśli nie.
	*/
	bool operator==(HashTable& rhs)
	{
		int size1 = this->setValues;
		int size2 = rhs.setValues;

		if (size1 == size2)
		{
			if (size1 == 0) return true;


			for (int i = 0; i < maxSize; i++)
			{
				if (rhs.dataHash[i].key != -1)
				{
					if ((this->dataHash[i].key != rhs.dataHash[i].key) || (this->dataHash[i].data != rhs.dataHash[i].data))
					{
						return false;
					}

					int branch1 = lengthOfBranch(&this->dataHash[i]);
					int branch2 = lengthOfBranch(&rhs.dataHash[i]);
					
					if (branch1 != branch2)
					{
						return false;
					}
				}
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	/**
	Operator przeciążony porównania "!="

	@param rhs Wskaźnik na drugi kontener.
	@return Status operacji: true, jeżeli nie są równe; false jeśli są.
	*/
	bool operator!=(HashTable& rhs)
	{
		return !(*this == rhs);
	}



	/*4.PUSH I POP*/

	/**
	Usunięcie największego elementu i zmniejszenie wielkości o jeden.
	*/
	void PopMax()
	{
		try
		{
			if (setValues != 0)
			{
				HashTableNode<T>* tmp = findMax();
				deleteBranch(tmp->pNext);
				tmp->key = -1;
				tmp->data = returnEmpty();
				tmp->pNext = nullptr;
				setValues--;
			}
			else
			{
				throw out_of_range("[PopMax] Brak danych do usunięcia!");
			}
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[HashTable<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Usunięcie najmniejszego elementu i zmniejszenie wielkości o jeden.
	*/
	void PopMin()
	{
		try
		{
			if (setValues != 0)
			{
				HashTableNode<T>* tmp = findMin();
				deleteBranch(tmp->pNext);
				tmp->key = -1;
				tmp->data = returnEmpty();
				tmp->pNext = nullptr;
				setValues--;
			}
			else
			{
				throw out_of_range("[PopMin] Brak danych do usunięcia!");
			}
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[HashTable<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Zwraca pozycje podanej wartości

	@param value Wartość do sprawdzenia
	@return Indeks danej wartości lub -1 gdy nie występuje
	*/
	int findValue(T value)
	{
		if (allowedType() && value != returnEmpty())
		{
			if (setValues != 0)
			{
				for (int i = 0; i < maxSize; i++)
				{
					if (this->dataHash[i].data == value)
					{
						return i;
					}
				}
			}
		}
		return -1;
	}

	/**
	Sprawdzenie czy element o podanej wartości znajduje się w kontenerze.

	@param value Wartość do sprawdzenia
	@return Status operacji: true, jeżeli istnieje taki element; false, jeśli nie.
	*/
	bool findIfExist(T value)
	{
		if (allowedType() && value != returnEmpty())
		{
			if (setValues != 0)
			{
				for (int i = 0; i < maxSize; i++)
				{
					if (this->dataHash[i].data == value)
					{
						return true;
					}
				}
				return false;
			}
			else
			{
				throw out_of_range("[findIfExist] Brak danych w kontenerze!");
			}
		}
		else
		{
			throw invalid_argument("[findIfExist] Bledny argument!");
		}
		return false;
	}

	/**
	Zwrócenie pointera na największą wartość w konternerze.

	@return Pointer na maxa.
	*/
	HashTableNode<T>* findMax()
	{
		try
		{
			if (setValues != 0)
			{
				T max = returnEmpty();
				HashTableNode<T>* tmp = nullptr;
				for (int i = 0; i < maxSize; i++)
				{
					if (dataHash[i].key != -1)
					{
						if (max < dataHash[i].data)
						{
							max = dataHash[i].data;
							tmp = &dataHash[i];
						}
					}
				}
				return tmp;
			}
		}
		return nullptr;
	}

	/**
	Zwrócenie największej wartości w konternerze.

	@return Wartość max.
	*/
	T findMaxValue()
	{
		if (setValues != 0)
		{
			return findMax()->data;
		}
		return returnEmpty();
	}

	/**
	Zwrócenie pointera na najmniejszą wartość w konternerze.

	@return Pointer na mina.
	*/
	HashTableNode<T>* findMin()
	{
		if (setValues != 0)
		{
			T min = findMax()->data;
			HashTableNode<T>* tmp = nullptr;
			for (int i = 0; i < maxSize; i++)
			{
				if (dataHash[i].key != -1)
				{
					if (min > dataHash[i].data)
					{
						min = dataHash[i].data;
						tmp = &dataHash[i];
					}
				}
			}
			return tmp;
		}
		return nullptr;
	}

	/**
	Zwrócenie najmniejszej wartości w konternerze.

	@return Wartość min.
	*/
	T findMinValue()
	{
		if (setValues != 0)
		{
			return findMin()->data;
		}
		else
		{
			throw invalid_argument("[findMinValue] Pusty kontener!");
		}
		return returnEmpty();
	}



	/*6.WPROWADZANIE DANYCH*/

	/**
	Wprowadza wartość do tablicy haszującej z uwzględnieniem zabezpieczeń

	@param value Wartość do wprowadzenia
	*/
	void Insert(T value)
	{
		try
		{
			//Wartość nie jest pusta
			if (allowedType() && value != returnEmpty())
			{
				if ((setValues < maxSize) || ((setValues == maxSize) && findIfExist(value)))
				{
					int hash = HashFunction(value);
					int index = abs(hash % maxSize);

					if (this->dataHash[index].key == -1)
					{
						this->dataHash[index].key = hash;
						this->dataHash[index].data = value;
						this->setValues++;
					}
					else
					{
						if (this->dataHash[index].data == value)
						{
							addToBranch(&this->dataHash[index], 1);
						}
						else
						{
							int valuePosition = findValue(value);

							if (valuePosition != -1)
							{
								addToBranch(&this->dataHash[valuePosition], 1);
							}
							else
							{
								int indexBackup = index++;
								while (this->dataHash[index].key != -1)
								{
									if (index != maxSize)
										index++;
									else
										index = 0;
								}

								this->dataHash[index].key = hash;
								this->dataHash[index].data = value;
								this->setValues++;
							}
						}
					}
				}
				else
				{
					throw out_of_range("[Insert] Kontener jest pełen!");
				}
			}
			else
			{
				throw invalid_argument("[Insert] Pusty argument!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[HashTable<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[HashTable<" << showType() << ">] " << e.what() << endl;
		}
	}


	/**
	Wprowadza wartość do tablicy haszującej z uwzględnieniem zabezpieczeń

	@param value Wartość do wprowadzenia
	@param amoundToAdd Liczba danych do wprowadzenia
	*/
	void Insert(T value, int amoundToAdd)
	{
		try
		{
			if (allowedType() && value != returnEmpty() && amoundToAdd > 0)
			{
				if ((setValues < maxSize) || ((setValues == maxSize) && findIfExist(value)))
				{
					int hash = HashFunction(value);
					int index = abs(hash % maxSize);

					if (this->dataHash[index].key == -1)
					{
						this->dataHash[index].key = hash;
						this->dataHash[index].data = value;
						addToBranch(&this->dataHash[index], amoundToAdd - 1);
					}
					else
					{
						if (this->dataHash[index].data == value)
						{
							addToBranch(&this->dataHash[index], amoundToAdd);
						}
						else
						{
							int valuePosition = findValue(value);

							if (valuePosition != -1)
							{
								addToBranch(&this->dataHash[valuePosition], amoundToAdd);
							}
							else
							{
								int indexBackup = index++;
								while (this->dataHash[index].key != -1)
								{
									if (index != maxSize)
										index++;
									else
										index = 0;
								}

								this->dataHash[index].key = hash;
								this->dataHash[index].data = value;
								addToBranch(&this->dataHash[index], amoundToAdd - 1);
								this->setValues++;
							}
						}
					}
				}
				else
				{
					throw out_of_range("[Insert] Kontener jest pełen!");
				}
			}
			else
			{
				throw invalid_argument("[Insert] Bledny argument!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[HashTable<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[HashTable<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Wstawienie nowego elementu na podaną pozycje.

	@param oldValue Element do zastąpienia.
	@param newValue Element zastępujący.
	*/
	void Emplace(T oldValue, T newValue)
	{
		try
		{
			if (setValues != 0)
			{
				if (allowedType() && findIfExist(oldValue) && newValue != returnEmpty())
				{
					Erase(oldValue);
					Insert(newValue);
				}
				else
				{
					throw invalid_argument("[Emplace] Argumenty są błędne!");
				}
			}
			else
			{
				throw invalid_argument("[Emplace] Kontener jest pusty!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[HashTable<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Zamiana zawartości między dwoma kontenerami.

	@param tmp Drugi kontener.
	*/
	void Swap(HashTable& rhs)
	{
		HashTableNode<T>* tmpData = this->dataHash;
		this->dataHash = rhs.dataHash;
		rhs.dataHash = tmpData;

		int tmpValues = this->setValues;
		this->setValues = rhs.setValues;
		rhs.setValues = tmpValues;
	}



	/*7.CZYSZCZENIE I WIELKOŚĆ*/

	/**
	Sprawdzenie czy typ zmiennej jest właściwy

	@return Status operacji: true, jeżeli jest; false jeśli nie.
	*/
	bool allowedType()
	{
		//Typy arytmetyczne
		if (is_arithmetic_v<T>)
		{
			return true;
		}
		const char* type = typeid(this).name();
		string str(type);
		regex reg("(string)");
		smatch matches;
		while (regex_search(str, matches, reg))
		{
			if (matches.ready() != 0)
			{
				return true;
			}
		}
		return false;
	}

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

	/**
	Sprawdzenie czy kontener jest pusty.

	@return Status operacji: true jeżeli jest pusty, w innym przypadku false.
	*/
	bool Empty() const noexcept
	{
		if (setValues == 0) return true;
		else return false;
	}

	/**
	Zwrócenie wielkości kontenera.

	@return Wartość spod zmiennej size.
	*/
	int Size() const noexcept
	{
		return setValues;
	}

	/**
	Zniszczenie zawartości kontenera i ustawienie jego wielkości na 0
	*/
	void Clear()
	{
		//Jeżeli tablica istnieje
		if (setValues != 0)
		{
			for (int i = 0; i < maxSize; i++)
			{
				if (this->dataHash[i].key != -1)
				{
					Erase(dataHash[i].data);
				}
			}
			setValues = 0;
		}
	}

	/**
	Usuwa wartość z tablicy hashującej o ile istnieje

	@param value Wartość do usunięcia
	*/
	void Erase(T value)
	{
		try
		{
			if (allowedType())
			{
				if(value != returnEmpty() && findIfExist(value))
				{
					int valuePosition = findValue(value);

					if (valuePosition != -1)
					{
						if (this->dataHash[valuePosition].pNext != nullptr)
						{
							deleteBranch(this->dataHash[valuePosition].pNext);
						}
						this->dataHash[valuePosition].key = -1;
						this->dataHash[valuePosition].data = returnEmpty();
						this->dataHash[valuePosition].pNext = nullptr;
					}
				}
				else
				{
					throw invalid_argument("[Erase] Wartosc nie wystepuje w kontenerze!");
				}
				
			}
			else
			{
				throw invalid_argument("[Erase] Niewlasciwy argument!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[HashTable<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Zwrócenie maksymlanej ilości elementów jakie jest w w stanie zmieścić kontener

	@return Wielkość maksymalna kontenera.
	*/
	int MaxSize()
	{
		return maxSize;
	}

	/**
	Wyświetlenie wszystkich elementów kontenera.
	*/
	void Show()
	{
		if (setValues != 0)
		{
			cout << endl;

			for (int i = 0; i < maxSize; i++)
			{
				if (this->dataHash[i].key != -1)
					cout << "[" << i << "] Key: " << this->dataHash[i].key
					<< " | Value: " << this->dataHash[i].data
					<< " | Count: " << lengthOfBranch(&this->dataHash[i])
					<< endl;
			}
		}
		else
		{
			cout << "\nKontener jest pusty." << endl;
		}
	}
};