#pragma once
#include <iostream>
#include "Adaptors.h"

using namespace std;

/**
Deklaracja klasy PriorityQueue
- Odpowiednik STLowego kolejki.
- Dziedzicz�ca po Adaptors.

@param data Dynamicznie zaalokowana tablica T�w.
@param size Ilo�� wpisanych element�w
@param front Sta�a opisuj�ca indeks TOPu.
*/
template <class T>
class PriorityQueue : public Adaptors<T>
{
	//Dynamicznie zaalokowana tablica Tow
	T* data;
	//Wielko�� PriorityQueue = ilo�� zaalokowanej pami�ci
	int size;
	//Sta�a opisuj�ca indeks Frontu
	static const int front = 0;
	//Indeks Maxa
	int max;

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
	PriorityQueue()
	{
		if (allowedType())
		{
			data = nullptr;
			size = 0;
			max = -1;
		}
		else
		{
			data = nullptr;
			size = 0;
			max = -1;
			cerr << "\n[PriorityQueue<" << showType() << ">] " << "[Konstruktor domyslny] Niedozwolony typ!" << endl;
		}
	}

	/**
	Konstruktor jednoargumentowy.
	- Dodaje podan� warto�� jako pierwszy element.

	@param value Warto�� do wpisania.
	*/
	PriorityQueue(T value)
	{
		if (allowedType())
		{
			//Warto�� jest pustym Tiem
			if (value == returnEmpty())
			{
				data = nullptr;
				size = 0;
				max = -1;
				cerr << "\n[PriorityQueue<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Element nie mo�e by� pusty!" << endl;
			}
			//Warto�� nie jest pusta
			else
			{
				size = 1;
				data = new T[size];
				data[front] = value;
				max = front;
			}
		}
		else
		{
			data = nullptr;
			size = 0;
			max = -1;
			cerr << "\n[PriorityQueue<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Niedozwolony typ kontenera!" << endl;
		}
	}

	/**
	Konstruktor dwuargumentowy.
	- Dodaje podan� ilo�� element�w o podanej warto�ci.

	@param value Warto�� do wpisania.
	@param size Ilo�� element�w do stworzenia.
	*/
	PriorityQueue(T value, int size)
	{
		if (allowedType())
		{
			//Wielko�� kontenera wykracza poza zakres
			if ((size + 1) > MaxSize() || size <= 0)
			{
				data = nullptr;
				size = 0;
				max = -1;
				cerr << "\n[PriorityQueue<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Queue poza zakresem!" << endl;
			}
			//Warto�� jest pustym Tiem
			else if (value == returnEmpty())
			{
				data = nullptr;
				size = 0;
				max = -1;
				cerr << "\n[PriorityQueue<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Element nie mo�e by� pusty!" << endl;
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
				max = front;
			}
		}
		else
		{
			data = nullptr;
			size = 0;
			max = -1;
			cerr << "\n[PriorityQueue<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Niedozwolony typ kontenera!" << endl;;
		}
	}

	/**
	Konstruktor kopiuj�cy.
	- Tworzy kontener b�d�cy kopi� podanego.

	@param other Wska�nik na drugi kontener.
	*/
	PriorityQueue(const PriorityQueue& other)
	{
		//Wielko�� wektora nie przerkacza zakresu
		if (!other.Empty())
		{
			data = nullptr;
			size = 0;
			max = -1;
			for (int i = 0; i < size; i++)
			{
				data[i] = other.data[i];
			}
			max = other.max;
		}
		//Wektor wychodzi poza zakres
		else
		{
			data = nullptr;
			size = 0;
			max = -1;
		}
	}



	/*2.DESTRUKTOR*/

	/**
	Destruktor
	- g��wna metoda zwalniaj�ca pami��
	*/
	~PriorityQueue()
	{
		//Je�li PriorityQueue istnieje
		if (data)
		{
			delete[] data;
		}
	}



	/*3.PRZECI??ONE OPERATORY*/

	/**
	Operator przeci��ony przypisania "="

	@param value Wska�nik na drugi kontener.
	@return Przypisany kontener.
	*/
	PriorityQueue<T>& operator = (const PriorityQueue& value)
	{
		//Je�eli wielko�� PriorityQueue nie wykracza poza zakres
		if (value.size < MaxSize())
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
				max = value.max;

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
	bool operator == (const PriorityQueue& value) const
	{
		//Wielko�ci obu PriorityQueue s� r�wne
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
	bool operator != (const PriorityQueue& value) const
	{
		//Negacja wynik�w z operatora ==
		return !(*this == value);
	}



	/*4.PUSH I POP*/

	/**
	Dodanie nowego elementu na TOP kontenera i zwi�kszenie jego wielko�ci.

	@param value Nowy element.
	*/
	void Push(const T& value)
	{
		try
		{
			//Warto�� nie jest pusta
			if (value != returnEmpty())
			{
				//Wielkosc PriorityQueue wykracza�aby poza zakres
				if ((size + 1) >= MaxSize())
				{
					throw out_of_range("Stack poza zakresem!");
				}
				//PriorityQueue nie ma element�w
				if (size == 0)
				{
					size++;
					T* data = new T[size];
					data[front] = value;
					max = front;
				}
				//PriorityQueue ma przynajmniej jeden element
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
					//Sprawdzenie czy nowy element nie jest najwi�kszym
					if (value > data[max])
					{
						max = (size - 1);
					}
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
			cerr << "\n[PriorityQueue<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[PriorityQueue<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Usuni�cie elementu Max i zmniejszenie jego wielko�ci.
	*/
	void Pop()
	{
		try
		{
			//PriorityQueue nie ma element�w
			if (size <= 0)
			{
				throw invalid_argument("Proba usuniecia ostatniego elementu z pustego stacka!");
			}
			//PriorityQueue ma jeden element
			else if (size == 1)
			{
				Clear();
			}
			//PriorityQueue ma wi�cej ni� jeden element
			else
			{
				T* tmp = new T[size - 1];
				int count = 0;
				for (int i = 0; i < size; i++)
				{
					if (i == max)
					{
						count++;
					}
					tmp[i] = data[i + count];
				}
				delete[] data;
				data = tmp;
				size--;
				findMax();
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[PriorityQueue<" << showType() << ">] " << e.what() << endl;
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
			return data[max];
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
			return &data[max];
		}
		return nullptr;
	}



	/*6.WPROWADZANIE DANYCH*/

	/**
	Zamiana zawarto�ci mi�dzy dwoma kontenerami.

	@param tmp Drugi kontener.
	*/
	void Swap(PriorityQueue& tmp)
	{
		//Je�eli istnieje kontener
		if (data)
		{
			T* buffData = nullptr;
			buffData = this->data;
			this->data = tmp.data;
			tmp.data = buffData;

			int sizeBuff = 0;
			sizeBuff = this->size;
			this->size = tmp.size;
			tmp.size = sizeBuff;

			int maxBuff = 0;
			maxBuff = this->max;
			this->max = tmp.max;
			tmp.max = maxBuff;
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
	void Clear() noexcept
	{
		//Je�eli istnieje kontener
		if (data)
		{
			size = 0;
			max = 0;
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
	Odnalezienie nowego Maxa i przypisanie go do zmiennej.
	*/
	void findMax()
	{
		if (data)
		{
			T tmpMax = 0;
			int index = 0;
			for (int i = 0; i < size; i++)
			{
				if (data[i] > tmpMax)
				{
					tmpMax = data[i];
					index = i;
				}
			}
			max = index;
		}
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