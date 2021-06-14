#pragma once
#include <iostream>
#include <limits>
#include <regex>
#include <iterator>
#include <exception>
#include <sstream>
#include "Adaptors.h"

using namespace std;

/**
Deklaracja klasy Queue
- Odpowiednik STLowego kolejki.
- Dziedzicz¹ca po Adaptors.

@param data Dynamicznie zaalokowana tablica Tów.
@param size Iloœæ wpisanych elementów
@param front Sta³a opisuj¹ca indeks TOPu.
*/
template <class T>
class Queue : public Adaptors<T>
{
	//Dynamicznie zaalokowana tablica Tow
	T* data;
	//Wielkoœæ Queue = iloœæ zaalokowanej pamiêci
	int size;
	//Sta³a opisuj¹ca indeks Frontu
	static const int front = 0;

	/**
	Informacja o typie danych w kontenerze.

	@return String z nazw¹ typu danych.
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
	Konstruktor domyœlny
	*/
	Queue()
	{
		if (allowedType())
		{
			data = nullptr;
			size = 0;
		}
		else
		{
			data = nullptr;
			size = 0;
			cerr << "\n[Queue<" << showType() << ">] " << "[Konstruktor domyslny] Niedozwolony typ!" << endl;
		}
	}

	/**
	Konstruktor jednoargumentowy.
	- Dodaje podan¹ wartoœæ jako pierwszy element.

	@param value Wartoœæ do wpisania.
	*/
	Queue(T value)
	{
		if (allowedType())
		{
			//Wartoœæ jest pustym Tiem
			if (value == returnEmpty())
			{
				data = nullptr;
				size = 0;
				cerr << "\n[Queue<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Element nie mo¿e byæ pusty!" << endl;
			}
			//Wartoœæ nie jest pusta
			else
			{
				size = 1;
				data = new T[size];
				data[front] = value;
			}
		}
		else
		{
			data = nullptr;
			size = 0;
			cerr << "\n[Queue<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Niedozwolony typ kontenera!" << endl;
		}
	}

	/**
	Konstruktor dwuargumentowy.
	- Dodaje podan¹ iloœæ elementów o podanej wartoœci.

	@param value Wartoœæ do wpisania.
	@param size Iloœæ elementów do stworzenia.
	*/
	Queue(T value, int size)
	{
		if (allowedType())
		{
			//Wielkoœæ kontenera wykracza poza zakres
			if ((size + 1) > MaxSize() || size <= 0)
			{
				data = nullptr;
				size = 0;
				cerr << "\n[Queue<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Queue poza zakresem!" << endl;
			}
			//Wartoœæ jest pustym Tiem
			else if (value == returnEmpty())
			{
				data = nullptr;
				size = 0;
				cerr << "\n[Queue<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Element nie mo¿e byæ pusty!" << endl;
			}
			//Wartoœæ nie jest pusta
			else
			{
				this->size = size;
				data = new T[size];
				for (int i = 0; i < size; i++)
				{
					data[i] = value;
				}
			}
		}
		else
		{
			data = nullptr;
			size = 0;
			cerr << "\n[Queue<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Niedozwolony typ kontenera!" << endl;;
		}
	}

	/**
	Konstruktor kopiuj¹cy.
	- Tworzy kontener bêd¹cy kopi¹ podanego.

	@param other WskaŸnik na drugi kontener.
	*/
	Queue(const Queue& other)
	{
		if (!other.Empty())
		{
			size = other.size;
			data = new T[size];
			for (int i = 0; i < size; i++)
			{
				data[i] = other.data[i];
			}
		}
		else
		{
			data = nullptr;
			size = 0;
		}
	}



	/*2.DESTRUKTOR*/

	/**
	Destruktor
	- g³ówna metoda zwalniaj¹ca pamiêæ
	*/
	~Queue()
	{
		//Jeœli Queue istnieje
		if (data)
		{
			delete[] data;
		}
	}



	/*3.PRZECI¥¯ONE OPERATORY*/

	/**
	Operator przeci¹¿ony przypisania "="

	@param value WskaŸnik na drugi kontener.
	@return Przypisany kontener.
	*/
	Queue<T>& operator = (const Queue& value)
	{
		//Je¿eli wielkoœæ Queue nie wykracza poza zakres
		if (!value.Empty())
		{
			//Przypisanie danych z drugiego obiektu
			this->size = value.size;
			delete[] this->data;

			//Jeœli obiekt posiada tablicê to zaalokuj na ni¹ pamiec i przepisz
			if (value.data)
			{
				this->data = new T[size];
				for (int i = 0; i < size; i++)
				{
					data[i] = value.data[i];
				}

			}
			return *this;
		}
		else
		{
			Clear();
		}
		return *this;
	}

	/**
	Operator przeci¹¿ony porównania "=="

	@param value WskaŸnik na drugi kontener.
	@return Status operacji: true, je¿eli s¹ równe; false jeœli nie.
	*/
	bool operator == (const Queue& value) const
	{
		//Wielkoœci obu Queue s¹ równe
		if (size == value.Size())
		{
			//Porównanie wszystkich elementów
			for (int i = 0; i < size; i++)
			{
				//Je¿eli nie s¹ równe
				if (data[i] != value.data[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	/**
	Operator przeci¹¿ony porównania "!="
	
	@param value WskaŸnik na drugi kontener.
	@return Status operacji: true, je¿eli nie s¹ równe; false jeœli s¹.
	*/
	bool operator != (const Queue& value) const
	{
		//Negacja wyników z operatora ==
		return !(*this == value);
	}



	/*4.PUSH I POP*/

	/**
	Dodanie nowego elementu na koniec kontenera i zwiêkszenie jego wielkoœci.

	@param value Nowy element.
	*/
	void Push(const T& value)
	{
		try
		{
			//Wartoœæ nie jest pusta
			if (value != returnEmpty())
			{
				//Wielkosc Queue wykracza³aby poza zakres
				if ((size + 1) >= MaxSize())
				{
					throw out_of_range("[Push] Queue poza zakresem!");
				}
				//Queue nie ma elementów
				if (size == 0)
				{
					size++;
					T* data = new T[size];
					data[front] = value;
				}
				//Queue ma przynajmniej jeden element
				else
				{
					T* tmp = new T[size + 1];
					for (int i = 0; i < (size + 1); i++)
					{
						tmp[i] = data[i];
					}
					tmp[size] = value;
					delete[] data;
					data = tmp;
					size++;
				}
			}
			//Wartoœæ jest pusta
			else
			{
				throw invalid_argument("[Push] Element nie mo¿e byæ pusty!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Queue<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Queue<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Usuniêcie elementu z FRONTu i zmniejszenie jego wielkoœci.
	*/
	void Pop()
	{
		try
		{
			//Queue nie ma elementów
			if (size <= 0)
			{
				throw out_of_range("[Pop] Proba usuniecia ostatniego elementu z pustego stacka!");
			}
			//Queue ma jeden element
			else if (size == 1)
			{
				Clear();
			}
			//Queue ma wiêcej ni¿ jeden element
			else
			{
				size--;
				T* tmp = new T[size];
				for (int i = 0; i < size; i++)
				{
					tmp[i] = data[i + 1];
				}
				delete[] data;
				data = tmp;
			}
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Queue<" << showType() << ">] " << e.what() << endl;
		}
	}



	/*5.REFERENCJE I WSKA?NIKI*/

	/**
	Zwrócenie referencji na BACK.

	@return Referencja na BACK.
	*/
	T& Back()
	{
		//Back istnieje
		if (size > 0)
		{
			return data[size - 1];
		}
		T empty = returnEmpty();
		return empty;
	}

	/**
	Zwrócenie wskaŸnika na BACK.

	@return WskaŸnik na BACK.
	*/
	T* BackPtr()
	{
		//Back istnieje
		if (size > 0)
		{
			return &data[size - 1];
		}
		return nullptr;
	}

	/**
	Zwrócenie referencji na FRONT.

	@return Referencja na FRONT.
	*/
	T& Front()
	{
		//Front istnieje
		if (data)
		{
			return data[front];
		}
		T empty = returnEmpty();
		return empty;
	}

	/**
	Zwrócenie wskaŸnika na FRONT.

	@return WskaŸnik na FRONT.
	*/
	T* FrontPtr()
	{
		//Front istnieje
		if (data)
		{
			return &data[front];
		}
		return nullptr;
	}



	/*6.WPROWADZANIE DANYCH*/

	/**
	Zamiana zawartoœci miêdzy dwoma kontenerami.

	@param tmp Drugi kontener.
	*/
	void Swap(Queue& tmp)
	{
		//Je¿eli istnieje kontener
		if (data)
		{
			int buffSize = 0;
			buffSize = this->size;
			this->size = tmp.size;
			tmp.size = buffSize;
			
			T* buffData = nullptr;
			buffData = this->data;
			this->data = tmp.data;
			tmp.data = buffData;
		}
	}



	/*7.CZYSZCZENIE I WIELKOŒÆ*/

	/**
	Sprawdzenie czy typ zmiennej jest w³aœciwy

	@return Status operacji: true, je¿eli jest; false jeœli nie.
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
	Zwrócenie w³aœciwego wyzerowania dla danego typu

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

	@return Status operacji: true je¿eli jest pusty, w innym przypadku false.
	*/
	bool Empty() const noexcept
	{
		//Je¿eli wielkoœæ nie jest wiêksza od zera
		if (!(size > 0)) return true;
		//Je¿eli jest mniejsza b¹dŸ równa zerze
		else return false;
	}

	/**
	Zwrócenie wielkoœci kontenera.

	@return Wartoœæ spod zmiennej size.
	*/
	int Size() const noexcept
	{
		//Zwrócenie wartoœci zmiennej size
		return this->size;
	}

	/**
	Zniszczenie zawartoœci kontenera i ustawienie jego wielkoœci na 0.
	*/
	void Clear()
	{
		//Je¿eli istnieje kontener
		if (data)
		{
			size = 0;
			T* tmp = new T[size];
			delete[] data;
			this->data = tmp;
		}
	}

	/**
	Zwrócenie maksymlanej iloœci elementów jakie jest w w stanie zmieœciæ kontener.

	@return Maksymalna wielkoœæ kontenera.
	*/
	int MaxSize()
	{
		//Zwraca wielkoœæ maksymaln¹
		return numeric_limits<int>::max();
	}

	/**
	Wyœwietlenie wszystkich elementów kontenera.	
	*/
	void Show()
	{
		if (size != 0)
		{
			cout << "\n|  ";
			for (int i = 0; i < size; i++)
			{
				cout << this->data[i] << "  |  ";
			}
			cout << endl;
		}
		else
		{
			cout << "\nKontener jest pusty!" << endl;
		}
	}
};