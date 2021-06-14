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
- Dziedzicz�ca po Adaptors.

@param data Dynamicznie zaalokowana tablica T�w.
@param size Ilo�� wpisanych element�w
@param front Sta�a opisuj�ca indeks TOPu.
*/
template <class T>
class Queue : public Adaptors<T>
{
	//Dynamicznie zaalokowana tablica Tow
	T* data;
	//Wielko�� Queue = ilo�� zaalokowanej pami�ci
	int size;
	//Sta�a opisuj�ca indeks Frontu
	static const int front = 0;

	/**
	Informacja o typie danych w kontenerze.

	@return String z nazw� typu danych.
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
	Konstruktor domy�lny
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
	- Dodaje podan� warto�� jako pierwszy element.

	@param value Warto�� do wpisania.
	*/
	Queue(T value)
	{
		if (allowedType())
		{
			//Warto�� jest pustym Tiem
			if (value == returnEmpty())
			{
				data = nullptr;
				size = 0;
				cerr << "\n[Queue<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Element nie mo�e by� pusty!" << endl;
			}
			//Warto�� nie jest pusta
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
	- Dodaje podan� ilo�� element�w o podanej warto�ci.

	@param value Warto�� do wpisania.
	@param size Ilo�� element�w do stworzenia.
	*/
	Queue(T value, int size)
	{
		if (allowedType())
		{
			//Wielko�� kontenera wykracza poza zakres
			if ((size + 1) > MaxSize() || size <= 0)
			{
				data = nullptr;
				size = 0;
				cerr << "\n[Queue<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Queue poza zakresem!" << endl;
			}
			//Warto�� jest pustym Tiem
			else if (value == returnEmpty())
			{
				data = nullptr;
				size = 0;
				cerr << "\n[Queue<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Element nie mo�e by� pusty!" << endl;
			}
			//Warto�� nie jest pusta
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
	Konstruktor kopiuj�cy.
	- Tworzy kontener b�d�cy kopi� podanego.

	@param other Wska�nik na drugi kontener.
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
	- g��wna metoda zwalniaj�ca pami��
	*/
	~Queue()
	{
		//Je�li Queue istnieje
		if (data)
		{
			delete[] data;
		}
	}



	/*3.PRZECI��ONE OPERATORY*/

	/**
	Operator przeci��ony przypisania "="

	@param value Wska�nik na drugi kontener.
	@return Przypisany kontener.
	*/
	Queue<T>& operator = (const Queue& value)
	{
		//Je�eli wielko�� Queue nie wykracza poza zakres
		if (!value.Empty())
		{
			//Przypisanie danych z drugiego obiektu
			this->size = value.size;
			delete[] this->data;

			//Je�li obiekt posiada tablic� to zaalokuj na ni� pamiec i przepisz
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
	Operator przeci��ony por�wnania "=="

	@param value Wska�nik na drugi kontener.
	@return Status operacji: true, je�eli s� r�wne; false je�li nie.
	*/
	bool operator == (const Queue& value) const
	{
		//Wielko�ci obu Queue s� r�wne
		if (size == value.Size())
		{
			//Por�wnanie wszystkich element�w
			for (int i = 0; i < size; i++)
			{
				//Je�eli nie s� r�wne
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
	Operator przeci��ony por�wnania "!="
	
	@param value Wska�nik na drugi kontener.
	@return Status operacji: true, je�eli nie s� r�wne; false je�li s�.
	*/
	bool operator != (const Queue& value) const
	{
		//Negacja wynik�w z operatora ==
		return !(*this == value);
	}



	/*4.PUSH I POP*/

	/**
	Dodanie nowego elementu na koniec kontenera i zwi�kszenie jego wielko�ci.

	@param value Nowy element.
	*/
	void Push(const T& value)
	{
		try
		{
			//Warto�� nie jest pusta
			if (value != returnEmpty())
			{
				//Wielkosc Queue wykracza�aby poza zakres
				if ((size + 1) >= MaxSize())
				{
					throw out_of_range("[Push] Queue poza zakresem!");
				}
				//Queue nie ma element�w
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
			//Warto�� jest pusta
			else
			{
				throw invalid_argument("[Push] Element nie mo�e by� pusty!");
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
	Usuni�cie elementu z FRONTu i zmniejszenie jego wielko�ci.
	*/
	void Pop()
	{
		try
		{
			//Queue nie ma element�w
			if (size <= 0)
			{
				throw out_of_range("[Pop] Proba usuniecia ostatniego elementu z pustego stacka!");
			}
			//Queue ma jeden element
			else if (size == 1)
			{
				Clear();
			}
			//Queue ma wi�cej ni� jeden element
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
	Zwr�cenie referencji na BACK.

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
	Zwr�cenie wska�nika na BACK.

	@return Wska�nik na BACK.
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
	Zwr�cenie referencji na FRONT.

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
	Zwr�cenie wska�nika na FRONT.

	@return Wska�nik na FRONT.
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
	Zamiana zawarto�ci mi�dzy dwoma kontenerami.

	@param tmp Drugi kontener.
	*/
	void Swap(Queue& tmp)
	{
		//Je�eli istnieje kontener
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



	/*7.CZYSZCZENIE I WIELKO��*/

	/**
	Sprawdzenie czy typ zmiennej jest w�a�ciwy

	@return Status operacji: true, je�eli jest; false je�li nie.
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
	Zwr�cenie w�a�ciwego wyzerowania dla danego typu

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

	@return Status operacji: true je�eli jest pusty, w innym przypadku false.
	*/
	bool Empty() const noexcept
	{
		//Je�eli wielko�� nie jest wi�ksza od zera
		if (!(size > 0)) return true;
		//Je�eli jest mniejsza b�d� r�wna zerze
		else return false;
	}

	/**
	Zwr�cenie wielko�ci kontenera.

	@return Warto�� spod zmiennej size.
	*/
	int Size() const noexcept
	{
		//Zwr�cenie warto�ci zmiennej size
		return this->size;
	}

	/**
	Zniszczenie zawarto�ci kontenera i ustawienie jego wielko�ci na 0.
	*/
	void Clear()
	{
		//Je�eli istnieje kontener
		if (data)
		{
			size = 0;
			T* tmp = new T[size];
			delete[] data;
			this->data = tmp;
		}
	}

	/**
	Zwr�cenie maksymlanej ilo�ci element�w jakie jest w w stanie zmie�ci� kontener.

	@return Maksymalna wielko�� kontenera.
	*/
	int MaxSize()
	{
		//Zwraca wielko�� maksymaln�
		return numeric_limits<int>::max();
	}

	/**
	Wy�wietlenie wszystkich element�w kontenera.	
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