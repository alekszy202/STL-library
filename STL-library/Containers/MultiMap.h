#pragma once
#include <iostream>
#include "Associative.h"

using namespace std;

/**
Deklaracja klasy MultiMap
- Odpowiednik STLowego MultiMapy/s�ownika.
- Dziedzicz�ca po Associative.

@param key Dynamicznie zaalokowana tablica T�w.
@param data Dynamicznie zaalokowana tablica T�w.
@param size Ilo�� wpisanych element�w
*/
template <class T, class V>
class MultiMap : public Associative<T>
{
	//Dynamicznie zaalokowana tablica T�w
	T* key;
	//Dynamicznie zaalokowana tablica T�w
	V* data;
	//Wielko�� kontenera
	int size;

	string showTypeKey()
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

	string showTypeValue()
	{
		//Typy arytmetyczne
		if (is_arithmetic_v<V>)
		{
			return typeid(V).name();
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
	MultiMap()
	{
		if (allowedType())
		{
			size = 0;
			key = new T[size];
			data = new V[size];
		}
		else
		{
			size = 0;
			key = nullptr;
			data = nullptr;
			cerr << "\n[MultiMap<" << showTypeKey() << "><" << showTypeValue() << ">] " << "[Konstruktor domy�lny] Niedozwolony typ kontenera!" << endl;
		}
	}

	/**
	Konstruktor dwuoargumentowy.
	- Dodaje podany klucz i warto�� jako pierwszy element.

	@param key Warto�� do wpisania - klucz.
	@param value Warto�� do wpisania.
	*/
	MultiMap(T key, V value)
	{
		if (allowedType())
		{
			//Warto�� jest pustym Tiem
			if (key == returnEmptyKey() || value == returnEmptyValue())
			{
				this->size = 0;
				this->key = nullptr;
				this->data = nullptr;
				cerr << "\n[MultiMap<" << showTypeKey() << "><" << showTypeValue() << ">] " << "[Konstruktor dwuargumentowy] Element nie mo�e by� pusty!" << endl;
			}
			//Warto�� nie jest pusta
			else
			{
				size = 1;
				this->key = new T[size];
				this->data = new V[size];
				this->key[0] = key;
				this->data[0] = value;
			}
		}
		else
		{
			this->size = 0;
			this->key = nullptr;
			this->data = nullptr;
			cerr << "\n[MultiMap<" << showTypeKey() << "><" << showTypeValue() << ">] " << "[Konstruktor dwuargumentowy] Niedozwolony typ kontenera!" << endl;
		}
	}

	/**
	Konstruktor kopiuj�cy.
	- Tworzy kontener b�d�cy kopi� podanego.

	@param other Wska�nik na drugi kontener.
	*/
	MultiMap(const MultiMap& other)
	{
		if (!other.Empty())
		{
			size = other.size;
			key = new T[size];
			data = new V[size];
			for (int i = 0; i < size; i++)
			{
				key[i] = other.key[i];
				data[i] = other.data[i];
			}
		}
		//Wektor wychodzi poza zakres
		else
		{
			size = 0;
			key = new T[size];
			data = new V[size];
		}
	}



	/*2.DESTRUKTOR*/

	/**
	Destruktor
	- g��wna metoda zwalniaj�ca pami��
	*/
	~MultiMap()
	{
		if (data)
		{
			delete[] data;
		}
		
		if (key)
		{
			delete[] key;
		}
	}



	/*3.PRZECI??ONE OPERATORY*/

	/**
	Operator przeci��ony przypisania "="

	@param value Wska�nik na drugi kontener.
	@return Przypisany kontener.
	*/
	MultiMap<T, V>& operator = (const MultiMap& other)
	{
		//Je�eli wielko�� MultiMapy nie wykracza poza zakres
		if (!other.Empty())
		{
			//Przypisanie danych z drugiego obiektu
			this->size = size;
			delete[] this->key;
			delete[] this->data;

			//Je�li obiekt posiada tablic� to zaalokuj na ni� pamiec i przepisz
			if (other.data)
			{
				this->key = new T[size];
				this->data = new V[size];
				for (int i = 0; i < size; i++)
				{
					key[i] = other.key[i];
					data[i] = other.data[i];
				}
			}
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
	bool operator == (const MultiMap& other) const
	{
		//Wielko�ci i pojemno�ci obu MultiMap s� r�wne
		if (size == other.Size())
		{
			//Por�wnanie wszystkich element�w
			for (int i = 0; i < size; i++)
			{
				//Je�eli kt�ry� nie jest r�wny
				if (key[i] != other.key[i] || data[i] != other.data[i])
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
	bool operator != (const MultiMap& other) const
	{
		//Negacja wynik�w z operatora ==
		return !(*this == other);
	}



	/*4.PUSH I POP*/

	/**
	Usuni�cie ostatniego elementu i zmniejszenie wielko�ci o jeden.
	*/
	void PopBack()
	{
		try
		{
			//Map nie ma element�w
			if (size == 0)
			{
				throw out_of_range("[PopBack] Proba usuniecia ostatniego elementu z pustej map!");
			}
			//MultiMap ma jednen element
			else if (size == 1)
			{
				Clear();
			}
			//MultiMap ma wi�cej ni� jeden element, zwalnia ostatni
			else
			{
				size--;
				T* tmpKey = new T[size];
				V* tmpValue = new V[size];
				for (int i = 0; i < size; i++)
				{
					tmpKey[i] = key[i];
					tmpValue[i] = data[i];
				}
				delete[] key;
				delete[] data;
				key = tmpKey;
				data = tmpValue;
			}
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[MultiMap<" << showTypeKey() << "><" << showTypeValue() << ">] " << e.what() << endl;
		}
	}

	/**
	Usuni�cie pierwszego elementu i zmniejszenie wielko�ci o jeden.
	*/
	void PopFront()
	{
		try
		{
			//Map nie ma element�w
			if (size == 0)
			{
				throw out_of_range("[PopFront] Proba usuniecia ostatniego elementu z pustej mapa!");
			}
			//Map ma jednen element
			else if (size == 1)
			{
				Clear();
			}
			//Map ma wi�cej ni� jeden element, zwalnia ostatni
			else
			{
				size--;
				T* tmpKey = new T[size];
				V* tmpValue = new V[size];
				for (int i = 0; i < size; i++)
				{
					tmpKey[i] = key[i + 1];
					tmpValue[i] = data[i + 1];
				}
				delete[] key;
				delete[] data;
				key = tmpKey;
				data = tmpValue;
			}
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[MultiMap<" << showTypeKey() << "><" << showTypeValue() << ">] " << e.what() << endl;
		}
	}



	/*5.REFERENCJE I WSKA?NIKI*/

	/**
	Zwr�cenie wska�nika na warto�� spod podanego klucza.

	@param key Podany klucz.
	@return Wska�nik na dany element.
	*/
	V* AtPtr(T key)
	{
		if (size != 0)
		{
			if (findIfExist(key))
			{
				for (int i = 0; i < size; i++)
				{
					if (key == this->key[i]) return &this->data[i];
				}
			}
		}
		return nullptr;
	}

	/**
	Zwr�cenie wska�nika na ostatni elementu.

	@return Wska�nika na ostatni element.
	*/
	V* End() const noexcept
	{
		//Je�eli MultiMap istnieje
		if (size != 0)
		{
			return &data[size - 1];
		}
		return nullptr;
	}

	/**
	Zamienienie key i data oraz zwr�cenie wska�nika na ostatni elementu.

	@return Wska�nika na ostatni element.
	*/
	V* Rend() noexcept
	{
		//Je�eli MultiMap istnieje
		if (size != 0)
		{
			Reverse();
			return &data[size - 1];
		}
		return nullptr;
	}

	/**
	Zwr�cenie wska�nika na pierwszy elementu.

	@return Wska�nika na pierwszy element.
	*/
	V* Begin() const noexcept
	{
		//Je�eli MultiMap istnieje
		if (size != 0)
		{
			return &data[0];
		}
		return nullptr;
	}

	/**
	Zamienienie key i data oraz zwr�cenie wska�nika na pierwszy elementu.

	@return Wska�nika na pierwszy element.
	*/
	V* Rbegin() noexcept
	{
		//Je�eli MultiMap istnieje
		if (size != 0)
		{
			Reverse();
			return &data[0];
		}
		return nullptr;
	}



	/*6.WPROWADZANIE DANYCH*/

	/**
	Sprawdzenie czy podana para jest unikatowa

	@param key Podany klucz pary.
	@param value Warto�� spod podanego klucza.
	@return Status operacji: true - para jest unikalna, false - ukorzystan� ju� tak� par�.
	*/
	bool usedPair(const T& key, const V& value)
	{
		if (key != returnEmptyKey() && value != returnEmptyValue())
		{
			for (int i = 0; i < size; i++)
			{
				if (key == this->key[i])
				{
					if (value == this->data[i])
					{
						return true;
					}
				}
			}
			return false;
		}
		return true;
	}

	/**
	Dodanie elementu przed podan� pozycj� i zwi�kszenie jego wieko�ci.

	@param key Nowy element - klucz.
	@param value Nowy element.
	*/
	void Insert(const T& key, const V& value)
	{
		try
		{
			//Pojemno�� nie wykracza poza zakres
			if ((size + 1) < MaxSize())
			{
				//Warto�� nie jest pusta
				if (value != returnEmptyValue() && !usedPair(key, value))
				{
					T* tmp1 = new T[size + 1];
					V* tmp2 = new V[size + 1];
					for (int i = 0; i < size; i++)
					{
						tmp1[i] = this->key[i];
						tmp2[i] = this->data[i];
					}
					tmp1[size] = key;
					tmp2[size] = value;
					delete[] this->key;
					delete[] this->data;
					this->key = tmp1;
					this->data = tmp2;
					size++;
					Sort();
				}
				//Warto�� jest pusta
				else
				{
					//Gdy podany indeks jest liczb� ujemn�
					throw invalid_argument("[Insert] Bledny argument!");
				}
			}
			//Map wykracza poza skal�
			else
			{
				//Gdy podany indeks jest wi�kszy ni� istnieje element�w
				throw out_of_range("[Insert] Pe�en kontener!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[MultiMap<" << showTypeKey() << "><" << showTypeValue() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[MultiMap<" << showTypeKey() << "><" << showTypeValue() << ">] " << e.what() << endl;
		}
	}

	/**
	Wstawienie nowego elementu na podan� pozycje.

	@param key Nowy element - klucz.
	@param value Nowy element.
	@param position Pozycja, na kt�r� metoda wstawia element.
	*/
	void Emplace(T key, V value, int position)
	{
		try
		{
			//Nowa pojemno�� nie wykracza poza zakres
			if ((size + 1) < MaxSize())
			{
				//Pozycja wykracza poza pojemno��
				if ((position < 0) || (position >= size))
				{
					throw out_of_range("[Emplace] Indeks poza skala!");
				}
				//Pozycja jest poprawna
				else if (!usedPair(key, value))
				{
					this->key[position] = key;
					data[position] = value;
					Sort();
				}
				else
				{
					//Gdy podany indeks jest liczb� ujemn�
					throw invalid_argument("[Emplace] Bledny argument!");
				}
			}
			//Pojemno�� wykracza poza zakres
			else
			{
				throw out_of_range("[Emplace] Map przekracza maksymaln� wielko��!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[MultiMap<" << showTypeKey() << "><" << showTypeValue() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[MultiMap<" << showTypeKey() << "><" << showTypeValue() << ">] " << e.what() << endl;
		}
	}

	/**
	Zamiana zawarto�ci mi�dzy dwoma kontenerami.

	@param tmp Drugi kontener.
	*/
	void Swap(MultiMap& tmp)
	{
		//Je�eli MultiMap istnieje
		if (size != 0)
		{
			T* buffKey = nullptr;
			buffKey = this->key;
			this->key = tmp.key;
			tmp.key = buffKey;

			V* buffData = nullptr;
			buffData = this->data;
			this->data = tmp.data;
			tmp.data = buffData;

			int buffSize = 0;
			buffSize = this->size;
			this->size = tmp.size;
			tmp.size = buffSize;
		}
	}

	/**
	Szukanie elementu po podanej warto�ci.

	@param value Warto�� elementu do odszukania.
	@return Warto�� odszukanego elementu.
	*/
	int findElement(const V value)
	{
		//Je�eli istnieje MultiMap
		if (size != 0)
		{
			for (int i = 0; i < size; i++)
			{
				//Je�eli znaleziono szukany element zwr�cenie jego indeksu
				if (this->data[i] == value) return i;
			}
		}
		return -1;
	}

	/**
	Sprawdzenie czy element istnieje, szukany po warto�ci.

	@param value Szukana warto��.
	@return Status operacji: true je�eli jest pusty, w innym przypadku false.
	*/
	bool findIfExist(const V value)
	{
		//Je�eli MultiMap istnieje
		if (key && data)
		{
			for (int i = 0; i < size; i++)
			{
				//Je�eli znaleziono szukany element
				if (data[i] == value) return true;
			}
		}
		//Je�li nie ma takiego elementu
		return false;
	}



	/*7.CZYSZCZENIE I WIELKO??*/

	/**
	Sprawdzenie czy typ zmiennej jest w�a�ciwy

	@return Status operacji: true, je�eli jest; false je�li nie.
	*/
	bool allowedType()
	{
		bool validKey = false;
		bool validValue = false;

		const char* type = typeid(this).name();
		string className(type);
		string partOfClassName = className.substr(className.find(","));


		//Sprawdzenie klucza
		if (is_arithmetic_v<T> || className.find("string") != string::npos)
		{
			validKey = true;
		}

		//Sprawdzenie warto�ci
		if (is_arithmetic_v<V> || partOfClassName.find("string") != string::npos)
		{
			validValue = true;
		}

		if (validKey && validValue) {
			return true;
		}

		return false;
	}

	/**
	Zwr�cenie w�a�ciwego wyzerowania dla danego typu

	@return "Zero" dla danego typu zmiennych.
	*/
	T returnEmptyKey()
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
	Zwr�cenie w�a�ciwego wyzerowania dla danego typu

	@return "Zero" dla danego typu zmiennych.
	*/
	V returnEmptyValue()
	{
		//Typy arytmetyczne
		if (is_arithmetic_v<V>)
		{
			return static_cast<V>(0);
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
					V value;
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
		//Je�eli pojemno�� nie jest wi�ksza od zera
		if (!(size > 0)) return true;
		//Je�eli jest wi�ksza od zera
		else return false;
	}

	/**
	Zwr�cenie wielko�ci kontenera.

	@return Warto�� spod zmiennej size.
	*/
	int Size() const noexcept
	{
		//Zwr�cenie warto�ci spod zmiennej size
		return this->size;
	}

	/**
	Zniszczenie zawarto�ci kontenera i ustawienie jego wielko�ci na 0
	*/
	void Clear() noexcept
	{
		if (key || data)
		{
			size = 0;
			T* tmpKey = new T[size];
			V* tmpValue = new V[size];
			delete[] key;
			delete[] data;
			this->key = tmpKey;
			this->data = tmpValue;
		}
	}

	/**
	Usuni�cie wybranego elementu po pozycji.

	@param position Pozycja elementu do usuni�cia.
	*/
	void Erase(int position)
	{
		try
		{
			if (size != 0)
			{
				//Je�eli indeks wykracza poza pojemno��
				if ((position < 0) || (position >= size))
				{
					throw invalid_argument("Indeks poza skala!");
				}
				//Indeks jest poprawny
				else
				{
					size--;
					T* tmp1 = new T[size];
					V* tmp2 = new V[size];
					int cor = 0;
					for (int i = 0; i < size; i++)
					{
						if (position == i) cor++;
						tmp1[i] = key[i + cor];
						tmp2[i] = data[i + cor];
					}
					delete[] key;
					delete[] data;
					key = tmp1;
					data = tmp2;
				}
			}
			else
			{
				throw invalid_argument("[Erase] Pusty kontener!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[MultiMap<" << showTypeKey() << "><" << showTypeValue() << ">] " << e.what() << endl;
		}
	}

	/**
	Usuni�cie wybranych element�w z przedzia�u.

	@param first Pierwszy indeks przedzia�u.
	@param last Ostatni indeks przedzia�u.
	*/
	void Erase(int first, int last)
	{
		try
		{
			if (size != 0)
			{
				//Kt�rykolwiek z podanych zmiennych wykracza poza pojemno��
				if ((first < 0) || (last < 0) || (first >= size) || (last >= size) || (first >= last))
				{
					throw invalid_argument("Indeks poza skala!");
				}
				//Zmienne s� poprawne
				else
				{
					int diff = abs(first - last);
					size -= diff;
					T* tmp1 = new T[size];
					V* tmp2 = new V[size];
					int cor = 0;
					for (int i = 0; i < size; i++)
					{
						if (first == i) cor = diff;
						tmp1[i] = key[i + cor];
						tmp2[i] = data[i + cor];
					}
					delete[] key;
					delete[] data;
					key = tmp1;
					data = tmp2;
				}
			}
			else
			{
				throw invalid_argument("[Erase] Pusty kontener!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[MultiMap<" << showTypeKey() << "><" << showTypeValue() << ">] " << e.what() << endl;
		}
	}

	/**
	Zwr�cenie maksymlanej ilo�ci element�w jakie jest w w stanie zmie�ci� kontener

	@return Wielko�� maksymalna kontenera.
	*/
	int MaxSize()
	{
		return numeric_limits<int>::max();
	}



	/*8.SORTOWANIE/PRZESTAWIANIE*/

	/**
	Odwr�cenie element�w kontenera kolejno�ci�.
	*/
	void Reverse() noexcept
	{
		//Je�eli MultiMap istnieje
		if (size != 0)
		{
			T* tmp1 = new T[size];
			V* tmp2 = new V[size];
			for (int i = 0; i < size; i++)
			{
				tmp1[i] = key[size - 1 - i];
				tmp2[i] = data[size - 1 - i];
			}
			delete[] key;
			delete[] data;
			key = tmp1;
			data = tmp2;
		}
	}

	/**
	Sortowanie element�w w kontenerze
	*/
	void Sort()
	{
		//Je�eli vector istnieje
		if (size != 0)
		{
			int i, j;
			for (i = 0; i < (size - 1); i++)
			{
				for (j = 0; j < (size - i - 1); j++)
				{
					if (key[j] > key[j + 1])
					{
						swap(key[j], key[j + 1]);
						swap(data[j], data[j + 1]);
					}
					else if (key[j] == key[j + 1])
					{
						if (data[j] > data[j + 1])
						{
							swap(data[j], data[j + 1]);
						}
					}
				}
			}
		}
	}

	/**
	Wy�wietlenie wszystkich element�w kontenera.
	*/
	void Show()
	{
		if (size != 0)
		{
			cout << "|  ";
			for (int i = 0; i < size; i++)
			{
				cout << this->key[i] << " : "
					<< this->data[i] << "  |  ";
			}
			cout << endl;
		}
		else
		{
			cout << "Kontener jest pusty!" << endl;
		}
	}
};
