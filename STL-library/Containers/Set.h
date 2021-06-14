#pragma once
#include <iostream>
#include "Associative.h"

using namespace std;

/**
Deklaracja klasy Set
- Odpowiednik STLowego Seta/zbioru.
- Dziedzicz¹ca po Associative.

@param key Dynamicznie zaalokowana tablica Tów.
@param data Dynamicznie zaalokowana tablica Tów.
@param size Iloœæ wpisanych elementów
*/
template <class T>
class Set : public Associative<T>
{
	//Dynamicznie zaalokowana tablica Tów
	T* key;
	//Wielkoœæ kontenera
	int size;

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

	/**
	Funkcja wykorzystywana w Sort()

	@param tab WskaŸnik na tablicê elementów kontenera.
	@param count Iloœæ elementów w tablicy.
	*/
	void insertionsort(T* tab, int count)
	{
		int i, j;
		T v;
		for (i = 1; i < count; i++)
		{
			j = i;
			v = tab[i];
			while ((j > 0) && (tab[j - 1] > v))
			{
				tab[j] = tab[j - 1];
				j--;
			}
			tab[j] = v;
		}
	}

public:

	/*1.KONSTRUKTORY*/

	/**
	Konstruktor domyœlny
	*/
	Set()
	{
		if (allowedType())
		{
			size = 0;
			key = new T[size];
		}
		else
		{
			cerr << "\n[Set<" << showType() << ">] " << "[Konstruktor domyslny] Niedozwolony typ!" << endl;
		}
	}

	/**
	Konstruktor jednooargumentowy.
	- Dodaje podany klucz jako pierwszy element.

	@param key Wartoœæ do wpisania - klucz.
	*/
	Set(T key)
	{
		if (allowedType())
		{
			//Wartoœæ jest pustym Tiem
			if (key == returnEmpty())
			{
				this->size = 0;
				this->key = nullptr;
				cerr << "\n[Set<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Niedozwolony typ!" << endl;
			}
			//Wartoœæ nie jest pusta
			else
			{
				size = 1;
				this->key = new T[size];
				this->key[0] = key;
			}
		}
		else
		{
			this->size = 0;
			this->key = nullptr;
			cerr << "\n[Set<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Niedozwolony typ!" << endl;
		}
	}

	/**
	Konstruktor kopiuj¹cy.
	- Tworzy kontener bêd¹cy kopi¹ podanego.

	@param other WskaŸnik na drugi kontener.
	*/
	Set(const Set& other)
	{
		if (!other.Empty())
		{
			size = other.size;
			key = new T[size];
			for (int i = 0; i < size; i++)
			{
				key[i] = other.key[i];
			}
		}
		else
		{
			this->size = 0;
			this->key = nullptr;
		}
	}



	/*2.DESTRUKTOR*/

	/**
	Destruktor
	- g³ówna metoda zwalniaj¹ca pamiêæ
	*/
	~Set()
	{
		if (key)
		{
			delete[] key;
		}
	}



	/*3.PRZECI??ONE OPERATORY*/

	/**
	Operator przeci¹¿ony przypisania "="

	@param value WskaŸnik na drugi kontener.
	@return Przypisany kontener.
	*/
	Set<T>& operator = (const Set& other)
	{
		//Je¿eli wielkoœæ Sety nie wykracza poza zakres
		if (!other.Empty())
		{
			//Przypisanie danych z drugiego obiektu
			this->size = other.size;
			delete[] this->key;

			//Jeœli obiekt posiada tablicê to zaalokuj na ni¹ pamiec i przepisz
			if (other.key)
			{
				this->key = new T[size];
				for (int i = 0; i < size; i++)
				{
					key[i] = other.key[i];
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
	bool operator == (const Set& other) const
	{
		//Wielkoœci i pojemnoœci obu Set s¹ równe
		if (size == other.Size())
		{
			//Porównanie wszystkich elementów
			for (int i = 0; i < size; i++)
			{
				//Je¿eli któryœ nie jest równy
				if (key[i] != other.key[i])
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
	bool operator != (const Set& other) const
	{
		//Negacja wyników z operatora ==
		return !(*this == other);
	}



	/*4.PUSH I POP*/

	/**
	Usuniêcie ostatniego elementu i zmniejszenie wielkoœci o jeden.
	*/
	void PopBack()
	{
		try
		{
			//Map nie ma elementów
			if (size == 0)
			{
				throw out_of_range("[PopBack] Proba usuniecia ostatniego elementu z pustej map!");
			}
			//Set ma jednen element
			else if (size == 1)
			{
				Clear();
			}
			//Set ma wiêcej ni¿ jeden element, zwalnia ostatni
			else
			{
				size--;
				T* tmp = new T[size];
				for (int i = 0; i < size; i++)
				{
					tmp[i] = key[i];
				}
				delete[] key;
				key = tmp;
			}
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Set<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Usuniêcie pierwszego elementu i zmniejszenie wielkoœci o jeden.
	*/
	void PopFront()
	{

		try
		{
			//Map nie ma elementów
			if (size == 0)
			{
				throw out_of_range("[PopFront] Proba usuniecia ostatniego elementu z pustej mapa!");
			}
			//Set ma jednen element
			else if (size == 1)
			{
				Clear();
			}
			//Set ma wiêcej ni¿ jeden element, zwalnia ostatni
			else
			{
				size--;
				T* tmp = new T[size];
				for (int i = 0; i < size; i++)
				{
					tmp[i] = key[i + 1];
				}
				delete[] key;
				key = tmp;
			}
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Set<" << showType() << ">] " << e.what() << endl;
		}
	}



	/*5.REFERENCJE I WSKA?NIKI*/

	/**
	Zwrócenie wskaŸnika na wartoœæ spod podanego klucza.

	@param key Podany klucz.
	@return WskaŸnik na dany element.
	*/
	T* AtPtr(T key)
	{
		if (size != 0)
		{
			if (findIfExist(key))
			{
				for (int i = 0; i < size; i++)
				{
					if (key == this->key[i])
					{
						return &this->key[i];
					}
				}
			}
		}
		return nullptr;
	}

	/**
	Zwrócenie wskaŸnika na ostatni elementu.

	@return WskaŸnika na ostatni element.
	*/
	T* End() const noexcept
	{
		//Je¿eli Set istnieje
		if (size != 0)
		{
			return &key[size - 1];
		}
		return nullptr;
	}

	/**
	Zamienienie key oraz zwrócenie wskaŸnika na ostatni elementu.

	@return WskaŸnika na ostatni element.
	*/
	T* Rend() noexcept
	{
		//Je¿eli Set istnieje
		if (size != 0)
		{
			Reverse();
			return &key[size - 1];
		}
		return nullptr;
	}

	/**
	Zwrócenie wskaŸnika na pierwszy elementu.

	@return WskaŸnika na pierwszy element.
	*/
	T* Begin() const noexcept
	{
		//Je¿eli Set istnieje
		if (size != 0)
		{
			return &key[0];
		}
		return nullptr;
	}

	/**
	Zamienienie key i data oraz zwrócenie wskaŸnika na pierwszy elementu.

	@return WskaŸnika na pierwszy element.
	*/
	T* Rbegin() noexcept
	{
		//Je¿eli Set istnieje
		if (size != 0)
		{
			Reverse();
			return &key[0];
		}
		return nullptr;
	}



	/*6.WPROWADZANIE DANYCH*/

	/**
	Dodanie elementu przed podan¹ pozycj¹ i zwiêkszenie jego wiekoœci.

	@param data Nowy element - klucz.
	*/
	void Insert(const T& data)
	{
		try
		{
			//Pojemnoœæ nie wykracza poza zakres
			if ((size + 1) < MaxSize())
			{
				//Wartoœæ nie jest pusta
				if (data != returnEmpty())
				{
					if (ifUnique(data))
					{
						size++;
						T* tmp = new T[size];
						for (int i = 0; i < (size - 1); i++)
						{
							tmp[i] = key[i];
						}
						tmp[size - 1] = data;
						delete[] key;
						key = tmp;
						Sort();
					}
					else
					{
						throw invalid_argument("[Insert] Argument nie jest unikalny!");
					}
				}
				//Wartoœæ jest pusta
				else
				{
					throw invalid_argument("[Insert] Pusty argument!");
				}
			}
			//Set wykracza poza skalê
			else
			{
				throw out_of_range("Set przekracza maksymaln¹ wielkoœæ!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Set<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Set<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Dodanie elementu przed podan¹ pozycj¹ i zwiêkszenie jego wiekoœci.

	@param position Pozycja, przed któr¹ metoda wstawia element.
	@param data Nowy element.
	*/
	void Insert(int position, const T& data)
	{
		try
		{
			//Pojemnoœæ nie wykracza poza zakres
			if ((size + 1) < MaxSize())
			{
				//Wartoœæ nie jest pusta
				if (data != returnEmpty())
				{
					//Pozycja wykracza poza pojemnoœæ
					if ((position < 0) || (position >= MaxSize()) || position >= size)
					{
						throw invalid_argument("[Insert] Indeks poza skala!");
					}
					//Pozycja jest poprawna
					else if ((key[position - 1] < data && key[position] > data) || (key[position - 1] > data && key[position] < data))
					{
						int cor = 0;
						T* tmp = new T[size + 1];
						for (int i = 0; i < size; i++)
						{
							if (i == position)
							{
								tmp[i] = data;
								cor++;
							}
							tmp[i + cor] = key[i];
						}
						delete[] key;
						key = tmp;
						size++;
					}
					else if (ifUnique(data))
					{
						size++;
						T* tmp = new T[size];
						for (int i = 0; i < (size - 1); i++)
						{
							tmp[i] = key[i];
						}
						tmp[size - 1] = data;
						delete[] key;
						key = tmp;
						Sort();
					}
					else
					{
						throw invalid_argument("[Insert] Argument nie jest unikalny!");
					}
				}
				//Wartoœæ jest pusta
				else
				{
					throw invalid_argument("[Insert] Pusty argument!");
				}
			}
			//Set wykracza poza skalê
			else
			{
				throw out_of_range("Set przekracza maksymaln¹ wielkoœæ!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Set<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Set<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Wstawienie nowego elementu na podan¹ pozycje.

	@param key Nowy element - klucz.
	@param position Pozycja, na któr¹ metoda wstawia element.
	*/
	void Emplace(T key, int position)
	{
		try
		{
			//Nowa pojemnoœæ nie wykracza poza zakres
			if ((size + 1) < MaxSize())
			{
				if (ifUnique(key))
				{
					//Pozycja wykracza poza pojemnoœæ
					if ((position < 0) || (position >= size))
					{
						throw exception("[Emplace] Indeks poza skala!");
					}
					//Pozycja jest poprawna
					else
					{
						this->key[position] = key;
						Sort();
					}
				}
				else
				{
					throw invalid_argument("[Emplace] Wartosc nie jest unikatowa!");
				}
			}
			//Pojemnoœæ wykracza poza zakres
			else
			{
				throw out_of_range("[Emplace] Set przekracza maksymaln¹ wielkoœæ!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Set<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Set<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Zamiana zawartoœci miêdzy dwoma kontenerami.

	@param tmp Drugi kontener.
	*/
	void Swap(Set& tmp)
	{
		//Je¿eli Set istnieje
		if (size != 0)
		{
			T* buffKey = nullptr;
			buffKey = this->key;
			this->key = tmp.key;
			tmp.key = buffKey;

			int buffSize = 0;
			buffSize = this->size;
			this->size = tmp.size;
			tmp.size = buffSize;
		}
	}

	/**
	Sprawdzenie czy element istnieje, szukany po wartoœci.

	@param value Szukana wartoœæ.
	@return Status operacji: true je¿eli jest pusty, w innym przypadku false.
	*/
	bool findIfExist(const T value)
	{
		//Je¿eli Set istnieje
		if (size != 0)
		{
			for (int i = 0; i < size; i++)
			{
				//Je¿eli znaleziono szukany element
				if (key[i] == value) return true;
			}
		}
		//Jeœli nie ma takiego elementu
		return false;
	}



	/*7.CZYSZCZENIE I WIELKO??*/

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
		//Je¿eli pojemnoœæ nie jest wiêksza od zera
		if (!(size > 0)) return true;
		//Je¿eli jest wiêksza od zera
		else return false;
	}

	/**
	Zwrócenie wielkoœci kontenera.

	@return Wartoœæ spod zmiennej size.
	*/
	int Size() const noexcept
	{
		//Zwrócenie wartoœci spod zmiennej size
		return this->size;
	}

	/**
	Zniszczenie zawartoœci kontenera i ustawienie jego wielkoœci na 0
	*/
	void Clear() noexcept
	{
		if (key)
		{
			size = 0;
			T* tmp = new T[size];
			delete[] key;
			this->key = tmp;
		}
	}

	/**
	Usuniêcie wybranego elementu po pozycji.

	@param position Pozycja elementu do usuniêcia.
	*/
	void Erase(int position)
	{
		try
		{
			if (size != 0)
			{
				//Je¿eli indeks wykracza poza pojemnoœæ
				if ((position < 0) || (position >= size))
				{
					throw invalid_argument("[Erase] Indeks poza skala!");
				}
				//Indeks jest poprawny
				else
				{
					T* tmp = new T[size - 1];
					int cor = 0;
					for (int i = 0; i < (size - 1); i++)
					{
						if (position == i) cor++;
						tmp[i] = key[i + cor];
					}
					delete[] key;
					key = tmp;
					size--;
				}
			}
			else
			{
				throw invalid_argument("[Erase] Pusty kontener!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Set<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Usuniêcie wybranych elementów z przedzia³u.

	@param first Pierwszy indeks przedzia³u.
	@param last Ostatni indeks przedzia³u.
	*/
	void Erase(int first, int last)
	{
		try
		{
			if (size != 0)
			{
				//Którykolwiek z podanych zmiennych wykracza poza pojemnoœæ
				if ((first < 0) || (last < 0) || (first >= size) || (last >= size) || (first >= last))
				{
					throw invalid_argument("[Erase] Indeks poza skala!");
				}
				//Zmienne s¹ poprawne
				else
				{
					int diff = (abs(first - last) + 1);
					T* tmp = new T[size - diff];
					int cor = 0;
					for (int i = 0; i < (size - diff); i++)
					{
						if (first == i) cor = diff;
						tmp[i] = key[i + cor];
					}
					delete[] key;
					key = tmp;
					size -= diff;
				}
			}
			else
			{
				throw invalid_argument("[Erase] Pusty kontener!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Set<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Zwrócenie maksymlanej iloœci elementów jakie jest w w stanie zmieœciæ kontener

	@return Wielkoœæ maksymalna kontenera.
	*/
	int MaxSize()
	{
		return numeric_limits<int>::max();
	}

	/**
	Usuniêcie wybranego elementu po wartoœci.

	@param value Wartoœæ elementu do usuniêcia.
	*/
	void Remove(T value)
	{
		try
		{
			if (size != 0)
			{
				//Je¿eli indeks wykracza poza pojemnoœæ
				if (!findIfExist(value))
				{
					throw invalid_argument("[Remove] Wartoœæ do usuniêcia nie istnieje!");
				}
				//Indeks jest poprawny
				else
				{
					size--;
					T* tmp = new T[size];
					int correction = 0;
					for (int i = 0; i < size; i++)
					{
						if (key[i] == value)
						{
							correction++;
						}
						tmp[i] = key[i + correction];
					}
					delete[] key;
					key = tmp;
				}
			}
			else
			{
				throw invalid_argument("[Erase] Pusty kontener!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Set<" << showType() << ">] " << e.what() << endl;
		}
	}



	/*8.SORTOWANIE/PRZESTAWIANIE*/

	/**
	Odwrócenie elementów kontenera kolejnoœci¹.
	*/
	void Reverse() noexcept
	{
		//Je¿eli Set istnieje
		if (size != 0)
		{
			T* tmp = new T[size];
			for (int i = 0; i < size; i++)
			{
				tmp[i] = key[size - 1 - i];
			}
			delete[] key;
			key = tmp;
		}
	}

	/**
	Sortowanie elementów w kontenerze
	*/
	void Sort()
	{
		//Je¿eli vector istnieje
		if (size != 0)
		{
			this->insertionsort(key, size);
		}
	}

	/**
	Sprawdzenie czy klucz jest wyj¹tkowy.
	*/
	bool ifUnique(T key)
	{
		if (key != returnEmpty())
		{
			for (int i = 0; i < size; i++)
			{
				if (this->key[i] == key)
				{
					return false;
				}
			}
			return true;
		}
		return false;
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
				cout << this->key[i] << "  |  ";
			}
			cout << endl;
		}
		else
		{
			cout << "\nKontener jest pusty!" << endl;
		}
	}
};