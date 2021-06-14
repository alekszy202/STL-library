#pragma once
#include <iostream>
#include "Adaptors.h"

using namespace std;

/**
Deklaracja klasy Stack
- Odpowiednik STLowego stosu.
- Dziedzicząca po Adaptors.

@param data Dynamicznie zaalokowana tablica Tów.
@param size Ilość wpisanych elementów
*/
template <class T>
class Stack : public Adaptors<T>
{
	//Dynamicznie zaalokowana tablica Tow
	T* data;
	//Ilość zaalokowanej pamięci = wielkość stacka
	int size;

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
	Stack()
	{
		if (allowedType())
		{
			size = 0;
			data = new T[size];
		}
		else
		{
			data = nullptr;
			size = 0;
			cerr << "\n[Stack<" << showType() << ">] " << "[Konstruktor domyslny] Niedozwolony typ!" << endl;
		}
	}

	/**
	Konstruktor jednoargumentowy.
	- Dodaje podaną wartość jako pierwszy element.

	@param value Wartość do wpisania.
	*/
	Stack(T value)
	{
		if (allowedType())
		{
			//Wartość jest pustym Tiem
			if (value == returnEmpty())
			{
				size = 0;
				data = new T[size];
				cerr << "\n[Stack<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Element nie może być pusty!" << endl;
			}
			//Wartość nie jest pusta
			else
			{
				size = 1;
				data = new T[size];
				data[0] = value;
			}
		}
		else
		{
			data = nullptr;
			size = 0;
			cerr << "\n[Stack<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Niedozwolony typ kontenera!" << endl;
		}
	}

	/**
	Konstruktor dwuargumentowy.
	- Dodaje podaną ilość elementów o podanej wartości.

	@param value Wartość do wpisania.
	@param size Ilość elementów do stworzenia.
	*/
	Stack(T value, int size)
	{
		if (allowedType())
		{
			//Wielkość kontenera wykracza poza zakres
			if ((size + 1) > MaxSize() || size <= 0)
			{
				data = new T[size];
				size = 0;
				cerr << "\n[Stack<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Stack poza zakresem!" << endl;
			}
			//Wartość jest pustym Tiem
			else if (value == returnEmpty())
			{
				data = new T[size];
				size = 0;
				cerr << "\n[Stack<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Element nie może być pusty!" << endl;
			}
			//Wartość nie jest pusta
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
			cerr << "\n[Stack<" << showType() << ">] " << "[Konstruktor dwuargumentowy]  Niedozwolony typ kontenera!" << endl;
		}
	}


	/**
	Konstruktor kopiujący.
	- Tworzy kontener będący kopią podanego.

	@param other Wskaźnik na drugi kontener.
	*/
	Stack(const Stack& other)
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
			size = 0;
			data = new T[size];
		}
	}



	/*2.DESTRUKTOR*/

	/**
	Destruktor
	- główna metoda zwalniająca pamięć
	*/
	~Stack()
	{
		//Jeśli Stack istnieje
		if (data)
		{
			delete[] data;
		}
	}



	/*3.PRZECIĄŻONE OPERATORY*/

	/**
	Operator przeciążony przypisania "="

	@param value Wskaźnik na drugi kontener.
	@return Przypisany kontener.
	*/
	Stack<T>& operator = (const Stack& value)
	{
		//Jeżeli wielkość Queue nie wykracza poza zakres
		if (!value.Empty())
		{
			//Przypisanie danych z drugiego obiektu
			this->size = value.size;
			delete[] this->data;

			//Jeśli obiekt posiada tablicę to zaalokuj na nią pamiec i przepisz
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
	Operator przeciążony porównania "=="

	@param value Wskaźnik na drugi kontener.
	@return Status operacji: true, jeżeli są równe; false jeśli nie.
	*/
	
	bool operator == (const Stack& value) const
	{
		//Wielkości obu Stack są równe
		if (size == value.Size())
		{
			//Porównanie wszystkich elementów
			for (int i = 0; i < size; i++)
			{
				//Jeżeli nie są równe
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
	Operator przeciążony porównania "!="

	@param value Wskaźnik na drugi kontener.
	@return Status operacji: true, jeżeli nie są równe; false jeśli są.
	*/
	
	bool operator != (const Stack& value) const
	{
		//Negacja wyników z operatora ==
		return !(*this == value);
	}



	/*4.PUSH I POP*/

	/**
	Dodanie nowego elementu na TOP kontenera i zwiększenie jego wielkości.

	@param value Nowy element.
	*/
	
	void Push(const T& value)
	{
		try
		{
			//Wartość nie jest pusta
			if (value != returnEmpty())
			{
				//Wielkosc stacka wykraczałaby poza zakres
				if ((size + 1) >= MaxSize())
				{
					throw out_of_range("Stack poza zakresem!");
				}
				//Stack nie ma elementów
				if (size == 0)
				{
					size++;
					T* data = new T[size];
					data[size - 1] = value;
				}
				//Stack przynajmniej jeden element
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
			//Wartość jest pusta
			else
			{
				throw invalid_argument("Element nie może być pusty!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Stack<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Stack<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Usunięcie elementu z TOPu i zmniejszenie jego wielkości.
	*/
	void Pop()
	{
		try
		{
			//Stack nie ma elementów
			if (size <= 0)
			{
				throw invalid_argument("Proba usuniecia ostatniego elementu z pustego stacka!");
			}
			//Stack ma jeden element
			else if (size == 1)
			{
				Clear();
			}
			//Stack ma więcej niż jeden element
			else
			{
				size--;
				T* tmp = new T[size];
				for (int i = 0; i < size; i++)
				{
					tmp[i] = data[i];
				}
				delete[] data;
				data = tmp;
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Stack<" << showType() << ">] " << e.what() << endl;
		}
	}



	/*5.REFERENCJE I WSKAŹ?NIKI*/

	/**
	Zwrócenie referencji na TOP.

	@return Referencja na TOP.
	*/
	T& Top()
	{
		//TOP istnieje
		if (size > 0)
		{
			return data[size - 1];
		}
		T empty = returnEmpty();
		return empty;
	}

	/**
	Zwrócenie wskaźnika na TOP.

	@return Wskaźnik na TOP.
	*/
	T* TopPtr()
	{
		//TOP istnieje
		if (size > 0)
		{
			return &data[size - 1];
		}
		return nullptr;
	}




	/*6.WPROWADZANIE DANYCH*/

	/**
	Zamiana zawartości między dwoma kontenerami.

	@param tmp Drugi kontener.
	*/
	void Swap(Stack& tmp)
	{
		//Jeżeli istnieje kontener
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
		//Jeżeli wielkość nie jest większa od zera
		if (!(size > 0)) return true;
		//Jeżeli jest mniejsza bądź równa zerze
		else return false;
	}

	/**
	Zwrócenie wielkości kontenera.

	@return Wartość spod zmiennej size.
	*/
	int Size() const noexcept
	{
		//Zwrócenie wartości zmiennej size
		return this->size;
	}

	/**
	Zniszczenie zawartości kontenera i ustawienie jego wielkości na 0.
	*/
	void Clear() noexcept
	{
		//Jeżeli istnieje kontener
		if (data)
		{
			size = 0;
			T* tmp = new T[size];
			delete[] data;
			this->data = tmp;
		}
	}

	/**
	Zwrócenie maksymlanej ilości elementów jakie jest w w stanie zmieścić kontener.

	@return Maksymalna wielkość kontenera.
	*/
	int MaxSize()
	{
		//Zwraca wielkość maksymalną
		return numeric_limits<int>::max();
	}

	/**
	Wyświetlenie wszystkich elementów kontenera.
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
