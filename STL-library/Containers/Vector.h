#pragma once
#include <iostream>
#include <limits>
#include <regex>
#include <iterator>
#include <exception>
#include <sstream>
#include "Sequences.h"

using namespace std;

/**
Deklaracja klasy Vector
- Odpowiednik STLowego wektora.
- Dziedzicząca po Sequences.

@param data Dynamicznie zaalokowana tablica Tów.
@param size Ilość wpisanych elementów
@param capacity Ilość zaalokowanej pamięci.
*/
template <class T>
class Vector : public Sequences<T>
{
	//Dynamicznie zaalokowana tablica Tów
	T* data;
	//Ilość wpisanych elementów
	int size;
	//Ilość zaalokowanej pamięci
	int capacity;

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
	Vector()
	{
		if (allowedType())
		{
			size = 0;
			capacity = 0;
			data = new T[capacity];
		}
		else
		{
			size = 0;
			capacity = 0;
			data = nullptr;
			cerr << "\n[Vector<" << showType() << ">] " << "[Konstruktor domyslny] Niedozwolony typ!" << endl;
		}
	}

	/**
	Konstruktor jednoargumentowy.
	- Dodaje podaną wartość jako pierwszy element.

	@param value Wartość do wpisania.
	*/
	Vector(T value)
	{
		if (allowedType())
		{
			if (value != returnEmpty())
			{
				this->size = 1;
				this->capacity = 1;
				data = new T[capacity];
				this->data[0] = value;
			}
			else
			{
				size = 0;
				capacity = 0;
				data = new T[capacity];
				cerr << "\n[Vector<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Pusty argument!" << endl;
			}
		}
		else
		{
			size = 0;
			capacity = 0;
			data = nullptr;
			cerr << "\n[Vector<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Niedozwolony typ kontenera!" << endl;
		}
	}

	/**
	Konstruktor dwuargumentowy.
	- Dodaje podaną ilość elementów o podanej wartości.

	@param value Wartość do wpisania.
	@param size Ilość elementów do stworzenia.
	*/
	Vector(T value, int size)
	{
		if (allowedType() && value != returnEmpty())
		{
			if (size > 0 && size < MaxSize())
			{
				int count = 0;
				capacity = size;
				data = new T[capacity];
				for (int i = 0; i < capacity; i++)
				{
					data[i] = value;
					if (value != returnEmpty())
					{
						count++;
					}
				}
				this->size = count;
			}
			//Wielkość wykracza poza zakres
			else
			{
				this->size = 0;
				capacity = 0;
				data = new T[capacity];
				cerr << "\n[Vector<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Podany indeks nie jest liczba dodatnia!") << endl;
			}
		}
		else
		{
			this->size = 0;
			capacity = 0;
			data = nullptr;
			cerr << "\n[Vector<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Niedozwolony typ kontenera!") << endl;
		}
	}

	/**
	Konstruktor kopiujący.
	- Tworzy kontener będący kopią podanego.

	@param other Wskaźnik na drugi kontener.
	*/
	Vector(Vector& other)
	{
		if (!other.Empty())
		{
			this->size = other.size;
			this->capacity = other.capacity;
			data = new T[capacity];

			for (int i = 0; i < capacity; i++)
			{
				data[i] = other.data[i];
			}
		}
		else
		{
			size = 0;
			capacity = 0;
			data = new T[capacity];
		}
	}



	/*2.DESTRUKTOR*/

	/**
	Destruktor
	- główna metoda zwalniająca pamięć
	*/
	~Vector()
	{
		delete[] data;
		data = nullptr;
	}



	/*3.PRZECI¥¯ONE OPERATORY*/

	/**
	Operator przeciążony przypisania "="

	@param value Wskaźnik na drugi kontener.
	@return Przypisany kontener.
	*/
	Vector<T>& operator = (const Vector& value)
	{
		//Jeżeli wielkość Vectora nie wykracza poza zakres
		if (!value.Empty())
		{
			//Przypisanie danych z drugiego obiektu
			this->size = value.size;
			this->capacity = value.capacity;
			delete[] this->data;

			//Jeśli obiekt posiada tablicę to zaalokuj na nią pamiec i przepisz
			if (value.data)
			{
				this->data = new T[capacity];
				for (int i = 0; i < capacity; i++)
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
	bool operator == (const Vector& value) const
	{
		//Wielkości i pojemności obu Vector są równe
		if ((size == value.Size()) && (capacity == value.Capacity()))
		{
			//Porównanie wszystkich elementów
			for (int i = 0; i < capacity; i++)
			{
				//Jeżeli któryś nie jest równy
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
	bool operator!=(const Vector& value) const
	{
		//Negacja wyników z operatora ==
		return !(*this == value);
	}

	/**
	Operator przeciążony indeksowy "[ ]"

	@param index Indeks elementu.
	@return Wartość elementu spod podanego indeksu.
	*/
	T operator[] (const int index)
	{
		if (index < capacity)
		{
			//Zwrócenie wartości spod danego indeksu
			return this->At(index);
		}
		return returnEmpty();
	}



	/*4.PUSH I POP*/

	/**
	Usunięcie ostatniego elementu i zmniejszenie wielkości o jeden.
	*/
	void PopBack()
	{
		try
		{
			//Brak elementów
			if (capacity == 0)
			{
				throw out_of_range("[PopBack] Proba usuniecia ostatniego elementu z pustej listy!");
			}
			//Vector ma jednen element
			else if (capacity == 1)
			{
				Clear();
			}
			//Vector ma więcej niż jeden element, zwalnia ostatni
			else
			{
				T* tmp = new T[capacity - 1];
				for (int i = 0; i < (capacity - 1); i++)
				{
					tmp[i] = data[i];
				}
				//Jesli element ma zawartosc to zmniejsz takze "size"
				if (data[capacity - 1] != returnEmpty()) size--;
				delete[] data;
				data = tmp;
				capacity--;
			}
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Usunięcie pierwszego elementu i zmniejszenie wielkości o jeden.
	*/
	void PopFront()
	{
		try
		{
			//Vector nie ma elementów
			if (capacity == 0)
			{
				throw out_of_range("Proba usuniecia ostatniego elementu z pustego vectora!");
			}
			//Vector ma jednen element
			else if (capacity == 1)
			{
				Clear();
			}
			//Vector ma więcej niż jeden element, zwalnia ostatni
			else
			{
				T* tmp = new T[capacity - 1];
				for (int i = 0; i < (capacity - 1); i++)
				{
					tmp[i] = data[i + 1];
				}
				//Jesli element ma zawartosc to zmniejsz takze "size"
				if (data[0] != returnEmpty()) size--;
				delete[] data;
				data = tmp;
				capacity--;
			}
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Dodanie nowego elementu na końcu kontenera, po ostatnimm oraz zwiększenie wielkości o jeden.

	@param value Nowy element.
	*/
	void PushBack(const T& value)
	{
		try
		{
			//Pojemność nie przekracza wielkości maksymalnej
			if ((capacity + 1) < MaxSize())
			{
				//Wartość nie jest pusta
				if (value != returnEmpty())
				{
					//Pojemność jest równa zerze
					if (capacity == 0)
					{
						data = new T[1];
						data[0] = value;
						size++;
						capacity++;
					}
					//Pojemność jest większa od zera
					else
					{
						T* tmp = new T[capacity + 1];
						for (int i = 0; i < capacity; i++)
						{
							tmp[i] = data[i];
						}
						tmp[capacity] = value;
						delete[] data;
						data = tmp;
						size++;
						capacity++;
					}
				}
				//Argument jest pusty
				else
				{
					throw std::invalid_argument("Pusty argument!");
				}
			}
			//Kontener wykracza poza zakres
			else
			{
				throw out_of_range("Vector przekracza maksymalną wielkość!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Dodanie nowego elementu na początku kontenera, po ostatnimm oraz zwiększenie wielkości o jeden.

	@param value Nowy element.
	*/
	void PushFront(const T& value)
	{
		try
		{
			//Nowa pojemność jest mniejsza od zakresu
			if ((capacity + 1) < MaxSize())
			{
				//Wartość nie jest pusta
				if (value != returnEmpty())
				{
					//Pojemność wynosi zero
					if (capacity == 0)
					{
						data = new T[1];
						data[0] = value;
						size++;
						capacity++;
					}
					//Pojemność jest większa od zera
					else
					{
						T* tmp = new T[capacity + 1];
						for (int i = 0; i < capacity; i++)
						{
							tmp[i + 1] = data[i];
						}
						tmp[0] = value;
						delete[] data;
						data = tmp;
						size++;
						capacity++;
					}
				}
				//Jest pusta
				else
				{
					throw std::invalid_argument("Pusty argument!");
				}
			}
			//Nowa pojemność wykracza poza zakres
			else
			{
				throw out_of_range("Vector przekracza maksymalną wielkość!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}



	/*5.REFERENCJE I WSKANIKI*/

	/**
	Zwrócenie referencji elementu spod podanego indeksu.

	@param index Indeks podanego elementu.
	@return Referencja na dany element.
	*/
	T& At(int index)
	{
		if (capacity != 0)
		{
			//Indeks wykracza poza zakres
			if ((index < 0) || (index >= capacity))
			{
				throw invalid_argument("Indeks poza zakresem!");
			}
			return data[index];
		}
		T empty = returnEmpty();
		return empty;
	}

	/**
	Zwrócenie wskaźnika na element spod podanego indeksu.

	@param index Indeks podanego elementu.
	@return Wskaźnik na dany element.
	*/
	T* AtPtr(int index)
	{
		if (capacity != 0)
		{
			//Indeks wykracza poza zakres
			if ((index < 0) || (index >= capacity))
			{
				throw invalid_argument("Indeks poza zakresem!");
			}
			else
			{
				return &data[index];
			}
		}
		return nullptr;
	}

	/**
	Zwrócenie referencji ostatniego elementu.

	@return Referencja na ostatni element.
	*/
	T& Back()
	{
		//Jeżeli vector istnieje
		if (data)
		{
			return data[capacity - 1];
		}
		T empty = returnEmpty();
		return empty;

	}

	/**
	Zwrócenie wskaźnika na ostatni elementu.

	@return Wskaźnika na ostatni element.
	*/
	T* End() const noexcept
	{
		//Jeżeli vector istnieje
		if (data)
		{
			return &data[capacity - 1];
		}
		return nullptr;
	}

	/**
	Zwrócenie referencji pierwszego elementu.

	@return Referencja na pierwszy element.
	*/
	T& Front()
	{
		//Jeżeli vector istnieje
		if (data)
		{
			return data[0];
		}
		T empty = returnEmpty();
		return empty;
	}

	/**
	Zwrócenie wskaźnika na pierwszy elementu.

	@return Wskaźnika na pierwszy element.
	*/
	T* Begin() const noexcept
	{
		//Jeżeli vector istnieje
		if (data)
		{
			return &data[0];
		}
		return nullptr;
	}




	/*6.WPROWADZANIE DANYCH*/

	/**
	Dodanie elementu przed podaną pozycją i zwiększenie jego wiekości.

	@param position Pozycja, przed którą metoda wstawia element.
	@param value Nowy element.
	*/
	void Insert(int position, const T& value)
	{
		try
		{
			//Pojemność nie wykracza poza zakres
			if ((capacity + 1) < MaxSize())
			{
				//Wartość nie jest pusta
				if (value != returnEmpty())
				{
					//Pozycja wykracza poza pojemność
					if ((position < 0) || (position >= capacity))
					{
						throw invalid_argument("Indeks poza skala!");
					}
					//Pozycja jest poprawna
					else if (position == 0)
					{
						PushFront(value);
					}
					else
					{
						int cor = 0;
						T* tmp = new T[capacity + 1];
						for (int i = 0; i < capacity; i++)
						{
							tmp[i + cor] = data[i];
							if ((i + 1) == position)
							{
								tmp[i + 1] = value;
								cor++;
							}
						}
						delete[] data;
						data = tmp;
						capacity++;
						size++;
					}
				}
				//Wartość jest pusta
				else
				{
					throw invalid_argument("Pusty argument!");
				}
			}
			//Vector wykracza poza skalę
			else
			{
				throw out_of_range("Vector przekracza maksymalną wielkość!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Wypełnienie kontenera elementem przed podaną pozycją i zwiększenie jego wiekości.

	@param position Pozycja, przed którą metoda wstawia element.
	@param n Ilość kopii nowego elementu do wstawienia.
	@param value Nowy element.
	*/
	void Insert(int position, int n, const T& value)
	{
		try
		{
			//Nowa pojemność wykraczałaby poza zakres
			if ((capacity + n) < MaxSize())
			{
				//Wartość nie jest pusta
				if (value != returnEmpty())
				{
					//Pozycja wykracza poza pojemność
					if ((position < 0) || (position >= capacity))
					{
						throw invalid_argument("Indeks poza skala!");
					}
					//Pozycja jest poprawna
					else if (position == 0)
					{
						for (int i = 0; i < n; i++)
						{
							PushFront(value);
						}
					}
					else
					{
						int cor = 0;
						T* tmp = new T[capacity + n];
						for (int i = 0; i < capacity; i++)
						{
							tmp[i + cor] = data[i];
							if ((i + 1) == position)
							{
								for (int j = 1; j < (n + 1); j++)
								{
									tmp[i + j] = value;
									cor++;
								}
							}
						}
						delete[] data;
						data = tmp;
						capacity += n;
						size += n;
					}
				}
				//Wartość jest pusta
				else
				{
					throw invalid_argument("Pusty argument!");
				}
			}
			//Vector wykraczałby poza skalę
			else
			{
				throw out_of_range("Vector przekracza maksymalną wielkość!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Wypełnienie kontenera przedziałem przed podaną pozycją i zwiększenie jego wiekości.

	@param position Pozycja, przed którą metoda wstawia element.
	@param n Ilość elementów do wstawienia.
	@param valuePtr Pointer na nowe elementy.
	*/
	void Insert(int position, int n, T* valuePtr)
	{
		try
		{
			//Nowa pojemność wykraczałaby poza zakres
			if ((capacity + n) < MaxSize())
			{
				//Wartość pod wskaźniekiem jest pusta
				if (*valuePtr != returnEmpty())
				{
					//Pozycja wykracza poza pojemność
					if ((position < 0) || (position >= capacity))
					{
						throw invalid_argument("Indeks poza skala!");
					}
					//Pozycja jest poprawna
					else if (position == 0)
					{
						for (int i = 0; i < n; i++)
						{
							PushFront(*valuePtr);
						}
						valuePtr++;
					}
					else
					{
						int cor = 0;
						T* tmp = new T[capacity + n];
						for (int i = 0; i < capacity; i++)
						{
							tmp[i + cor] = data[i];
							if ((i + 1) == position)
							{
								for (int j = 1; j < (n + 1); j++)
								{
									tmp[i + j] = *valuePtr;
									valuePtr++;
									cor++;
								}
							}
						}
						delete[] data;
						data = tmp;
						capacity += n;
						size += n;
					}
				}
				//Wartość jest pusta
				else
				{
					throw invalid_argument("Pusty argument!");
				}
			}
			//Vector jest pusty
			else
			{
				throw out_of_range("Vector przekracza maksymalną wielkość!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Wstawienie nowego elementu na podaną pozycje.

	@param value Nowy element.
	@param position Pozycja, na którą metoda wstawia element.
	*/
	void Emplace(T value, int position)
	{
		try
		{
			if (data)
			{
				//Nowa pojemność nie wykracza poza zakres
				if ((capacity + 1) < MaxSize())
				{
					//Pozycja wykracza poza pojemność
					if ((position < 0) || (position >= capacity))
					{
						throw invalid_argument("Indeks poza skala (funkcja Insert)!");
					}
					//Pozycja jest poprawna
					else
					{
						data[position] = value;
					}
				}
				//Pojemność wykracza poza zakres
				else
				{
					throw out_of_range("Vector przekracza maksymalną wielkość!");
				}
			}
			else
			{
				throw invalid_argument("Pusty kontener!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Zastąpienie starych elementów podanymi ze wskaźnika/tablicy.

	@param count Ilość elementów do zastąpienia.
	@param valuePtr Pointer na nowe elementy.
	*/
	void Assign(int count, T* valuePtr)
	{
		try
		{
			//Nowa pojemność nie wykracza poza zakres
			if (count > 0 && count < MaxSize())
			{
				int counter = 0;
				T* tmp = new T[count];
				for (int i = 0; i < count; i++)
				{
					//Jeżeli istnieje pointer
					if (valuePtr)
					{
						tmp[i] = *valuePtr;
						if (*valuePtr != returnEmpty()) counter++;
						valuePtr++;
					}
					//Pointer nie istnieje
					else
					{
						throw exception("Bledny argument!");
					}
				}

				Clear();
				capacity = count;
				size = counter;
				data = tmp;
			}
			//Nowa pojemność wykracza poza zakres
			else
			{
				throw out_of_range("Vector przekracza maksymalną wielkość!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Zastąpienie starych elementów podaną wartością.

	@param count Ilość elementów do zastąpienia.
	@param value Nowa wartość.
	*/
	void Assign(int count, const T value)
	{
		try
		{
			//Nowa pojemność nie wykracza poza zakres
			if (count > 0 && count < MaxSize())
			{
				//Wartość nie jest pusta
				if (value != returnEmpty())
				{
					Clear();
					capacity = count;
					size = count;
					T* tmp = new T[count];
					data = tmp;

					for (int i = 0; i < count; i++)
					{
						data[i] = value;
					}
				}
				//Wartość jest pusta
				else
				{
					throw invalid_argument("Bledny argument!");
				}
			}
			//Nowa pojemność wykracza poza zakres
			else
			{
				throw out_of_range("Vector przekracza maksymalną wielkość!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Zamiana zawartości między dwoma kontenerami.

	@param tmp Drugi kontener.
	*/
	void Swap(Vector& tmp)
	{
		//Jeżeli vector istnieje
		if (data)
		{
			int buffCapacity = 0;
			buffCapacity = this->capacity;
			this->capacity = tmp.capacity;
			tmp.capacity = buffCapacity;
			
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

	/**
	Szukanie elementu po podanej wartości.

	@param value Wartość elementu do odszukania.
	@return Indeks elementu, jeżeli został odnaleziony.
	*/
	int findElement(const T value)
	{
		//Jeżeli istnieje vector
		if (data)
		{
			for (int i = 0; i < capacity; i++)
			{
				//Jeżeli znaleziono szukany element zwrócenie jego indeksu
				if (data[i] == value) return i;
			}
		}
		//Jeśli nie ma takie elementu zwrócenie "blędu"
		return -1;
	}

	/**
	Sprawdzenie czy element istnieje, szukany po wartości.

	@param value Szukana wartość.
	@return Status operacji: true jeżeli jest pusty, w innym przypadku false.
	*/
	bool findIfExist(const T value)
	{
		//Jeżeli vector istnieje
		if (data)
		{
			for (int i = 0; i < capacity; i++)
			{
				//Jeżeli znaleziono szukany element
				if (data[i] == value) return true;
			}
			
		}
		//Jeśli nie ma takiego elementu
		return false;
	}



	/*7.CZYSZCZENIE I WIELKOŒÆ*/

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
		//Jeżeli pojemność nie jest większa od zera
		if (!(capacity > 0)) return true;
		//Jeżeli jest większa od zera
		else return false;
	}

	/**
	Zwrócenie wielkości kontenera.

	@return Wartość spod zmiennej size.
	*/
	int Size() const noexcept
	{
		//Zwrócenie wartości spod zmiennej size
		return this->size;
	}

	/**
	Zwrócenie wielkości pamięci zaalokowanej dla kontenera.

	@return Wielkość zaalokowanej pamięci.
	*/
	const int Capacity() const noexcept
	{
		//Zwrócenie wartości spod zmiennej capacity
		return this->capacity;
	}

	/**
	Zniszczenie zawartości kontenera i ustawienie jego wielkości na 0
	*/
	void Clear()
	{
		//Jeżeli istnieje kontener
		if (data)
		{
			size = 0;
			capacity = 0;
			T* tmp = new T[capacity];
			this->data = tmp;
		}
	}

	/**
	Usunięcie wybranego elementu po pozycji.

	@param position Pozycja elementu do usunięcia.
	*/
	void Erase(int position)
	{
		try
		{
			if (data)
			{
				//Jeżeli indeks wykracza poza pojemność
				if ((position < 0) || (position >= capacity))
				{
					throw invalid_argument("Indeks poza skala!");
				}
				//Indeks jest poprawny
				else
				{
					if (data[position] != returnEmpty())
					{
						data[position] = returnEmpty();
						size--;
					}
				}
			}
			else
			{
				throw invalid_argument("Pusty kontener!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Usunięcie wybranych elementów z przedziału.

	@param first Pierwszy indeks przedziału.
	@param last Ostatni indeks przedziału.
	*/
	void Erase(int first, int last)
	{
		try
		{
			if (data)
			{
				//Którykolwiek z podanych zmiennych wykracza poza pojemność
				if ((first < 0) || (last < 0) || (first >= capacity) || (last >= capacity) || (first >= last))
				{
					throw invalid_argument("Indeks poza skala!");
				}
				//Zmienne są poprawne
				else
				{
					for (int i = first; i <= last; i++)
					{
						if (data[i] != returnEmpty())
						{
							data[i] = returnEmpty();
							size--;
						}
					}
				}
			}
			else
			{
				throw invalid_argument("Pusty kontener!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Zwrócenie maksymlanej ilości elementów jakie jest w w stanie zmieścić kontener

	@return Wielkość maksymalna kontenera.
	*/
	int MaxSize()
	{
		return numeric_limits<int>::max();
	}

	/**
	Zarezerwowanie pamięci dla podanej ilości elementów.

	@param n Ilość pamięci do zarezerwowania.
	*/
	void Reserve(int n)
	{
		try
		{
			if (n != 0)
			{
				//Nowa pojemność nie wykracza poza zakres
				if (n > 0 && n < MaxSize())
				{
					//Jeżeli nowa pojemność jest mniejsza bądź równa starej
					if (n <= capacity) return;
					else
					{
						size = 0;
						T* tmp = new T[n];
						for (int i = 0; i < n; i++)
						{
							//Przepisanie wartości z wcześniej istniejącego vectora
							if (i < capacity)
							{
								tmp[i] = data[i];
								//Jeżeli wartość nie jest pusta zwiększysć wielkość
								if (tmp[i] != returnEmpty()) size++;
							}
							//Zapisanie nowych indeksów pustymi Tami
							else
							{
								tmp[i] = returnEmpty();
							}
						}

						delete[] data;
						data = tmp;
						capacity = n;
					}
				}
				//Vector poza skalą
				else
				{
					throw out_of_range("Vector przekracza maksymalną wielkość!");
				}
			}
			else
			{
				throw invalid_argument("Pusty argument!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Zmiana wielkości kontenera na podaną.
	- Mniejsza niż aktualna: ucięcie kontenera.
	- Większa niż aktualna: nowe elementy są puste.

	@param n Nowa wielkość kontenera.
	*/
	void Resize(int n)
	{
		try
		{
			if (n != 0)
			{
				//Nowa pojemność nie wykracza poza skalę
				if (n > 0 && n < MaxSize())
				{
					//Pojemności są identyczne
					if (n == capacity) return;
					else
					{
						size = 0;
						T* tmp = new T[n];
						for (int i = 0; i < n; i++)
						{
							//Przepisanie wartości z wcześniej istniejącego vectora
							if (i < capacity)
							{
								tmp[i] = data[i];
								//Jeżeli wartość nie jest pusta zwiększysć wielkość
								if (tmp[i] != returnEmpty()) size++;
							}
							//Zapisanie nowych indeksów pustymi Tami
							else
							{
								tmp[i] = returnEmpty();
							}
						}

						delete[] data;
						data = tmp;
						capacity = n;
					}
				}
				//Vector poza skalą
				else
				{
					throw out_of_range("Vector przekracza maksymalną wielkość!");
				}
			}
			else
			{
				throw invalid_argument("Pusty argument!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Zmiana wielkości kontenera na podaną i dodanie nowych elementów.
	- Mniejsza niż aktualna: ucięcie kontenera.
	- Większa niż aktualna: nowe elementy mają podaną wartość.

	@param n Nowa wielkość kontenera.
	@param value Wartość nowych elementów.
	*/
	void Resize(int n, const T& value)
	{
		try
		{
			if (n != 0)
			{
				//Nowa pojemność nie wykracza poza skalę
				if (n > 0 && n < MaxSize())
				{
					//Pojemności są identyczne
					if (n == capacity) return;
					else
					{
						size = 0;
						T* tmp = new T[n];
						for (int i = 0; i < n; i++)
						{
							//Przepisanie wartości z wcześniej istniejącego vectora
							if (i < capacity)
							{
								tmp[i] = data[i];
								//Jeżeli wartość nie jest pusta zwiększysć wielkość
								if (tmp[i] != returnEmpty()) size++;
							}
							//Zapisanie nowych indeksów podaną wartością
							else
							{
								tmp[i] = value;
								//Jeżeli wartość nie jest pusta zwiększysć wielkość
								if (tmp[i] != returnEmpty()) size++;
							}
						}

						delete[] data;
						data = tmp;
						capacity = n;
					}
				}
				//Vector poza skalą
				else
				{
					throw out_of_range("Vector przekracza maksymalną wielkość!");
				}
			}
			else
			{
			throw invalid_argument("Pusty argument!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Vector<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Redukcja ilości zajętej pamięci, by móc przechowywać tylko niepuste elementy.
	*/
	void ShrinkToFit()
	{
		//Jeżeli istnieje vector
		if (data)
		{
			T* tmp = new T[size];
			int count = 0;
			for (int i = 0; i < capacity; i++)
			{
				//Jeżeli wartość nie jest pusta
				if (data[i] != returnEmpty())
				{
					tmp[count] = data[i];
					count++;
				}
			}
			delete[] data;
			data = tmp;
			size = count;
			capacity = count;

		}
	}



	/*8.SORTOWANIE/PRZESTAWIANIE*/

	/**
	Sortowanie elementów w kontenerze
	*/
	void Sort()
	{
		//Jeżeli vector istnieje
		if (data)
		{
			this->insertionsort(data, capacity);
		}
	}

	/**
	Odwrócenie elementów kontenera kolejnością.
	*/
	void Reverse() noexcept
	{
		//Jeżeli vector istnieje
		if (data)
		{
			T* tmp = new T[capacity];
			for (int i = 0; i < capacity; i++)
			{
				tmp[i] = data[capacity - 1 - i];
			}
			delete[] data;
			data = tmp;
		}
	}

	/**
	Wyświetlenie wszystkich elementów kontenera.
	*/
	void Show()
	{
		if (capacity != 0)
		{
			cout << "\n|  ";
			for (int i = 0; i < capacity; i++)
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