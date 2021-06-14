#pragma once
#include <iostream>
#include "Sequences.h"
#include "Nudes.h"

using namespace std;

/**
Deklaracja klasy ListBi
- Odpowiednik STLowej listy dwukierunkowej.
- Dziedzicząca po Sequences.

@param pHead Głowa listy dwukierunkowej.
*/
template <class T>
class ListBi : public Sequences<T>
{
	//Głowa listy dwukierunkowej
	ListBiNode<T>* pHead;

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
	ListBi() : pHead(nullptr)
	{
		if (!allowedType())
		{
			cerr << "\n[ListBi<" << showType() << ">] " << "[Konstruktor domyslny] Niedozwolony typ!" << endl;
			throw invalid_argument();
		}
	}

	/**
	Konstruktor jednoargumentowy.
	- Dodaje podaną wartość jako pierwszy element.

	@param value Wartość do wpisania.
	*/
	ListBi(T value)
	{
		if (allowedType())
		{
			if (value != returnEmpty())
			{
				this->pHead = new ListBiNode<T>(value, nullptr, nullptr);
			}
			else
			{
				pHead = nullptr;
				cerr << "\n[ListBi<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Bledny argument, stworzono pusty kontener!" << endl;
			}
		}
		else
		{
			pHead = nullptr;
			cerr << "\n[ListBi<" << showType() << ">] " << "[Konstruktor jednoargumentowy] Niedozwolony typ kontenera!" << endl;
		}
	}

	/**
	Konstruktor dwuargumentowy.
	- Dodaje podaną ilość elementów o podanej wartości.

	@param value Wartość do wpisania.
	@param count Ilość elementów do stworzenia.
	*/
	ListBi(T value, int count)
	{
		if (allowedType() && value != returnEmpty())
		{
			if (count > 0 && count < MaxSize())
			{
				//Utworzenie glowy i zmiennej pomocniczej
				this->pHead = new ListBiNode<T>(value, nullptr, nullptr);
				ListBiNode<T>* tmp = this->pHead;

				//Pętla uzupelnia liste o pozostale elementy
				for (int i = 0; i < (count - 1); i++)
				{
					tmp->pNext = new ListBiNode<T>(value, nullptr, tmp);
					tmp = tmp->pNext;
				}
			}
			else
			{
				pHead = nullptr;
				cerr << "\n[ListBi<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Bledny argument, stworzono pusty kontener!" << endl;
			}
		}
		else
		{
			pHead = nullptr;
			cerr << "\n[ListBi<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Niedozwolony typ kontenera!" << endl;
		}
	}

	/**
	Konstruktor dwuargumentowy.
	- Dodaje podaną ilość elementów o wartościach ze wskaźnika.

	@param count Ilość elementów do stworzenia.
	@param valuePtr Wskaźnik na wartości.
	*/
	ListBi(int count, T* valuePtr)
	{
		if (allowedType())
		{
			if (count > 0 && count < MaxSize())
			{
				//Utworzenie glowy i zmiennej pomocniczej
				this->pHead = new ListBiNode<T>(*valuePtr, nullptr, nullptr);
				ListBiNode<T>* tmp = this->pHead;

				//Pętla uzupelnia liste o pozostale elementy
				for (int i = 0; i < (count - 1); i++)
				{
					valuePtr++;
					tmp->pNext = new ListBiNode<T>(*valuePtr, nullptr, tmp);
					tmp = tmp->pNext;
				}
			}
			else
			{
				pHead = nullptr;
				cerr << "\n[ListBi<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Bledny argument, stworzono pusty kontener!" << endl;
			}
		}
		else
		{
			pHead = nullptr;
			cerr << "\n[ListBi<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Niedozwolony typ kontenera!" << endl;
		}
	}

	/**
	Konstruktor dwuargumentowy.
	- Dodaje podaną ilość elementów o wartościach z elemntów innego kontenera.

	@param count Ilość elementów do stworzenia.
	@param ptr Wskaźnik na wartości innego kontenera.
	*/
	ListBi(int count, ListBiNode::ListBiNode<T>* ptr)
	{
		if (allowedType())
		{
			if (count > 0 && count < MaxSize())
			{
				//Utworzenie glowy i zmiennej pomocniczej
				this->pHead = new ListBiNode<T>(ptr->data, nullptr, nullptr);
				ListBiNode<T>* tmp = this->pHead;
				ListBiNode<T>* argument = ptr;

				//Pętla uzupelnia liste o pozostale elementy
				for (int i = 0; i < (count - 1); i++)	//Iteracja count-1 razy by utworzyc porzadana liczbe elementow
				{
					if (argument->pNext)
					{
						argument = argument->pNext;
					}
					else
					{
						break;
					}

					tmp->pNext = new ListBiNode<T>(argument->data, nullptr, tmp);
					tmp = tmp->pNext;
				}
			}
			else
			{
				pHead = nullptr;
				cerr << "\n[ListBi<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Bledny argument, stworzono pusty kontener!" << endl;
			}
		}
		else
		{
			pHead = nullptr;
			cerr << "\n[ListBi<" << showType() << ">] " << "[Konstruktor dwuargumentowy] Niedozwolony typ kontenera!" << endl;
		}
	}

	/**
	Konstruktor kopiujący.
	- Tworzy kontener będący kopią podanego.

	@param other Wskaźnik na drugi kontener.
	*/
	ListBi(const ListBi& other)
	{
		if (!other.Empty())
		{
			int size = other.Size();
			ListBiNode<T>* tmp = other.Begin();
			this->pHead = new ListBiNode<T>(tmp->data, nullptr, nullptr);

			ListBiNode<T>* tmp2 = this->pHead;
			for (int i = 0; i < (size - 1); i++)
			{
				tmp = tmp->pNext;
				tmp2->pNext = new ListBiNode<T>(tmp->data, nullptr, tmp2);
				tmp2 = tmp2->pNext;
			}
		}
		else
		{
			pHead = nullptr;
			cerr << "\n[ListBi<" << showType() << ">] " << "[Konstruktor kopiujący] Pusty kontener!" << endl;
		}
	}


	/*2.DESTRUKTOR*/

	/**
	Destruktor
	- główna metoda zwalniająca pamięć
	*/
	~ListBi()
	{
		ListBiNode<T>* tmp = nullptr;
		while (pHead)
		{
			tmp = pHead->pNext;
			delete pHead;
			pHead = tmp;
		}
	}



	/*3.PRZECIĄŻONE OPERATORY*/

	/**
	Operator przeciążony przypisania "="

	@param value Wskaźnik na drugi kontener.
	@return Przypisany kontener.
	*/
	ListBi<T>& operator=(const ListBi& value)
	{
		if (!value.Empty())
		{
			int size = value.Size();
			ListBiNode<T>* tmp = value.Begin();
			this->pHead = new ListBiNode<T>(tmp->data, nullptr, nullptr);

			ListBiNode<T>* tmp2 = this->pHead;
			for (int i = 0; i < (size - 1); i++)
			{
				tmp = tmp->pNext;
				tmp2->pNext = new ListBiNode<T>(tmp->data, nullptr, tmp2);
				tmp2 = tmp2->pNext;
			}
		}
		else
		{
			Clear();
		}
		return *this;
	}

	/**
	Operator przeciążony porównania "=="

	@param rhs Wskaźnik na drugi kontener.
	@return Status operacji: true, jeżeli są równe; false jeśli nie.
	*/
	bool operator==(const ListBi& rhs) const
	{
		int size1 = this->Size();
		int size2 = rhs.Size();

		if (size1 == size2)
		{
			if (size1 == 0) return true;

			for (int i = 0; i < size1; i++)
			{
				ListBiNode<T>* ptr1 = this->Begin();
				ListBiNode<T>* ptr2 = rhs.Begin();

				if (ptr1->data == ptr2->data)
				{
					ptr1 = ptr1->pNext;
					ptr2 = ptr2->pNext;
				}
				else
				{
					return false;
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
	bool operator!=(const ListBi& rhs) const
	{
		return !(*this == rhs);
	}

	/**
	Operator przeciążony indeksowy "[ ]"

	@param index Indeks elementu.
	@return Wartość elementu spod podanego indeksu.
	*/
	T operator[](int index)
	{
		if (index < this->Size())
		{
			return this->getElementValue(index);
		}
		return returnEmpty();
	}

	/**
	Operator przeciążony strumienia "<<"

	@param ostr Lewostronny operand potrzebny funkcji do funkcjonowania.
	@param list Wskaźnik na inny kontener.
	@return Zwrócenie Operandu.
	*/
	friend ostream& operator<<(ostream& ostr, const ListBi<T>& list)
	{
		ListBiNode<T>* tmp = list.pHead;
		while (tmp != nullptr)
		{
			cout << tmp->data << " ";
			tmp = tmp->pNext;
		}
		return ostr;
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
			if (this->pHead == nullptr)
			{
				throw out_of_range("[PopBack] Proba usuniecia ostatniego elementu z pustej listy!");
			}
			//Jeden element w liście
			else if (this->pHead->pNext == nullptr)
			{
				delete pHead;
				pHead = nullptr;
			}
			//Więcej niż jeden element w liście
			else
			{
				ListBiNode<T>* tmp = this->pHead;
				while (tmp->pNext->pNext)
				{
					tmp = tmp->pNext;
				}
				delete tmp->pNext;
				tmp->pNext = nullptr;
			}
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Usunięcie pierwszego elementu i zmniejszenie wielkości o jeden.
	*/
	void PopFront()
	{
		try
		{
			//Gdy głowa istnieje
			if (pHead)
			{
				//Gdy istnieje element drugi, wtedy przepinanie
				if (pHead->pNext)
				{
					ListBiNode<T>* tmp = pHead->pNext;
					delete pHead;
					pHead = tmp;
				}
				else
				{	//Gdy jest tylko pierwszy wtedy usuwamy
					delete pHead;
					pHead = nullptr;
				}
			}
			else
			{
				//Reakcja na brak elementow
				throw out_of_range("[PopFront] Lista jest pusta!");
			}
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
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
			if (value != returnEmpty())
			{
				//Gdy nie istnieje głowa, tworzy ją
				if (this->pHead == nullptr)
				{
					this->pHead = new ListBiNode<T>(value, nullptr, nullptr);
				}
				//Gdy istnieje, przechodzi do ostatniego elementu i alokuje nową wartość
				else if ((Size() + 1) < MaxSize())
				{
					ListBiNode<T>* tmp = this->pHead;
					while (tmp->pNext != nullptr)
					{
						tmp = tmp->pNext;
					}
					tmp->pNext = new ListBiNode<T>(value, nullptr, tmp);
				}
				else
				{
					throw out_of_range("[PushBack] Lista jest pełna!");
				}
			}
			else
			{
				throw invalid_argument("[PushBack] Bledny argument!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
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
			if (value != returnEmpty())
			{
				if (this->pHead == nullptr)
				{
					//Reakcja na brak elementow
					pHead = new ListBiNode<T>(value, nullptr, nullptr);
				}
				//Gdy głowa istnieje
				else if ((Size() + 1) < MaxSize())
				{
					ListBiNode<T>* tmp = pHead;
					pHead = new ListBiNode<T>(value, tmp, nullptr);
					tmp->pPrev = pHead;
				}
				else
				{
					throw out_of_range("[PushFront] Lista jest pełna!");
				}
			}
			else
			{
				throw invalid_argument("[PushFront] Bledny argument!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
		}
	}



	/*5.REFERENCJE I WSKAŹNIKI*/

	/**
	Zwrócenie referencji ostatniego elementu.

	@return Referencja na ostatni element.
	*/
	ListBiNode<T>& Back()
	{
		//Przejscie do ostatniego elementu
		if (this->pHead)
		{
			ListBiNode<T>* tmp = this->pHead;
			while (tmp->pNext)
			{
				tmp = tmp->pNext;
			}
			return *tmp;
		}
		return *(this->pHead);
	}

	/**
	Zwrócenie wskaźnika na ostatni elementu.

	@return Wskaźnika na ostatni element.
	*/
	ListBiNode<T>* End() const noexcept
	{
		//Przejscie do ostatniego elementu
		if (this->pHead)
		{
			ListBiNode<T>* tmp = this->pHead;
			while (tmp->pNext)
			{
				tmp = tmp->pNext;
			}
			return tmp;
		}
		return nullptr;
	}

	/**
	Zwrócenie referencji pierwszego elementu.

	@return Referencja na pierwszy element.
	*/
	ListBiNode<T>& Front()
	{
		if (this->pHead)
		{
			return *(this->pHead);
		}
		return *(this->pHead);
	}

	/**
	Zwrócenie wskaźnika na pierwszy elementu.

	@return Wskaźnika na pierwszy element.
	*/
	ListBiNode<T>* Begin() const noexcept
	{
		if (this->pHead)
		{
			return this->pHead;
		}
		return nullptr;
	}

	/**
	Zwrócenie referencji elementu spod podanego indeksu.

	@param index Indeks podanego elementu.
	@return Referencja na dany element.
	*/
	ListBiNode<T>& getElement(int index)
	{
		int size = this->Size();

		//Sprawdzanie poprawnosci podanego indeksu
		if ((index > -1) && (index < size))
		{
			//Przejscie do elementu o podanym indeksie
			if (this->pHead)
			{
				ListBiNode<T>* tmp = this->pHead;
				for (int i = 0; i < index; i++)
				{
					tmp = tmp->pNext;
				}
				return *tmp;
			}
		}
		return *(this->pHead);
	}

	/**
	Zwrócenie wskaźnika na element spod podanego indeksu.

	@param index Indeks podanego elementu.
	@return Wskaźnik na dany element.
	*/
	ListBiNode<T>* getElementPtr(int index)
	{
		int size = this->Size();

		//Sprawdzanie poprawnosci podanego indeksu
		if ((index > -1) && (index < size))
		{
			//Przejscie do elementu o podanym indeksie
			if (this->pHead)
			{
				ListBiNode<T>* tmp = this->pHead;
				for (int i = 0; i < index; i++)
				{
					tmp = tmp->pNext;
				}
				return tmp;
			}
		}
		return nullptr;
	}

	/**
	Zwrócenie wartości elementu spod podanego indeksu.

	@param index Indeks podanego elementu.
	@return Wartość danego elementu.
	*/
	T& getElementValue(int index)
	{
		int size = this->Size();
		T empty = returnEmpty();

		//Sprawdzanie poprawnosci podanego indeksu
		if ((index > -1) && (index < size))
		{
			//Przejscie do elementu o podanym indeksie
			if (this->pHead)
			{
				ListBiNode<T>* tmp = this->pHead;
				for (int i = 0; i < index; i++)
				{
					tmp = tmp->pNext;
				}
				return tmp->data;
			}
		}
		return empty;
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
			if (value != returnEmpty())
			{
				int size = this->Size();

				if ((size + 1) <= MaxSize())
				{
					//Czy position jest dodatnie (numeracja od 0)
					if (position == 0)
					{
						ListBiNode<T>* newNode = new ListBiNode<T>(value, pHead, nullptr);
						pHead = newNode;
						pHead->pNext->pPrev = pHead;
					}
					else if ((position > 0) && (position < size))
					{
						ListBiNode<T>* tmp = this->pHead;
						//Przejscie do elementu o wartości -1 od podanej w "position"
						for (int i = 1; i < position; i++)
						{
							tmp = tmp->pNext;
						}

						//Utworzenie nowego elementu z podaną wartością
						ListBiNode<T>* tmp2 = new ListBiNode<T>(value, tmp->pNext, tmp);
						tmp->pNext = tmp2;
						tmp2->pNext->pPrev = tmp2;
					}
					else
					{
						//Gdy podany indeks jest liczbą ujemną
						throw invalid_argument("[Insert] Podany indeks jest liczba ujemna!");
					}
				}
				else
				{
					//Gdy podany indeks jest większy niż istnieje elementów
					throw out_of_range("[Insert] Pełen kontener!");
				}
			}
			else
			{
				//Gdy podany indeks jest liczbą ujemną
				throw invalid_argument("[Insert] Bledny argument!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
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
			if (value != returnEmpty() && (n > 0) && (n < MaxSize()))
			{
				int size = this->Size();

				if ((size + n) <= MaxSize())
				{

					//Czy position jest dodatnie (numeracja od 0)
					if (position == 0)
					{
						ListBiNode<T>* newNode = nullptr;
						for (int i = 0; i < n; i++)
						{
							newNode = new ListBiNode<T>(value, pHead, nullptr);
							pHead = newNode;
							pHead->pNext->pPrev = pHead;
						}
					}
					else if ((position > 0) && (position < size))
					{
						ListBiNode<T>* tmp = this->pHead;
						//Przejscie do elementu o wartości -1 od podanej w "position"
						for (int i = 1; i < position; i++)
						{
							tmp = tmp->pNext;
						}

						//Utworzenie nowego elementu z podaną wartością
						ListBiNode<T>* tmp2 = nullptr;

						for (int j = 0; j < n; j++)
						{
							tmp2 = new ListBiNode<T>(value, tmp->pNext, tmp);
							tmp->pNext = tmp2;
							tmp2->pNext->pPrev = tmp2;
						}
					}
					else
					{
						//Gdy podany indeks jest liczbą ujemną
						throw invalid_argument("[Insert] Podany indeks jest liczba ujemna!");
					}
				}
				else
				{
					//Gdy podany indeks jest większy niż istnieje elementów
					throw out_of_range("[Insert] Pełen kontener!");
				}
			}
			else
			{
				//Gdy podany indeks jest liczbą ujemną
				throw invalid_argument("[Insert] Bledny argument!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
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
			if ((n > 0) && (n < MaxSize()))
			{
				int size = this->Size();

				if ((size + n) <= MaxSize())
				{

					//Czy position jest dodatnie (numeracja od 0)
					if (position == 0)
					{
						ListBiNode<T>* newNode = new ListBiNode<T>(*valuePtr, pHead, nullptr);
						pHead = newNode;
						pHead->pNext->pPrev = pHead;
						ListBiNode<T>* newNode2 = nullptr;

						for (int i = 0; i < (n - 1); i++)
						{
							valuePtr++;
							newNode2 = new ListBiNode<T>(*valuePtr, newNode->pNext, newNode);
							newNode->pNext = newNode2;
							newNode2->pNext->pPrev = newNode2;
							newNode = newNode2;
						}
					}
					else if ((position > 0) && (position < size))
					{
						ListBiNode<T>* tmp = this->pHead;
						//Przejscie do elementu o wartości -1 od podanej w "position"
						for (int i = 1; i < position; i++)
						{
							tmp = tmp->pNext;
						}

						//Utworzenie nowego elementu z podaną wartością
						ListBiNode<T>* tmp2 = nullptr;

						for (int j = 0; j < n; j++)
						{
							tmp2 = new ListBiNode<T>(*valuePtr, tmp->pNext, tmp);
							tmp->pNext = tmp2;
							tmp2->pNext->pPrev = tmp2;
							tmp = tmp2;
							valuePtr++;
						}
					}
					else
					{
						//Gdy podany indeks jest liczbą ujemną
						throw invalid_argument("[Insert] Podany indeks jest liczba ujemna!");
					}
				}
				else
				{
					//Gdy podany indeks jest większy niż istnieje elementów
					throw out_of_range("[Insert] Pełen kontener!");
				}
			}
			else
			{
				//Gdy podany indeks jest liczbą ujemną
				throw invalid_argument("[Insert] Bledny argument!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
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
			if (value != returnEmpty() && (position > 0) && (position < MaxSize()))
			{
				int size = this->Size();

				//Czy position jest dodatnie (numeracja od 0)
				if ((position > 0) && (position < size))
				{
					ListBiNode<T>* tmp = this->pHead;
					//Przejscie do elementu o wartości -1 od podanej w "position"
					for (int i = 0; i < position; i++)
					{
						tmp = tmp->pNext;
					}

					//Wprowadzenie nowej danej na podany indeks
					tmp->data = value;
				}
				else
				{
					//Gdy podany indeks jest liczbą ujemną
					throw invalid_argument("[Emplace] Bledna pozycja!");
				}
			}
			else
			{
				//Gdy podany indeks jest liczbą ujemną
				throw invalid_argument("[Emplace] Bledny argument!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Zastąpienie starych elementów podanymi z innego kontenera.

	@param count Ilość elementów do zastąpienia.
	@param element Nowe elementy.
	*/
	void Assign(int count, ListBiNode<T>* element)
	{
		try
		{
			if (count > 0 && count <= MaxSize())
			{
				if (element != nullptr)
				{
					this->Clear();	//Zwolnienie wcześniej istniejącej pamieci
					this->pHead = new ListBiNode<T>(element->data, nullptr, nullptr);	//Utworzenie głowy
					ListBiNode<T>* tmp = this->pHead;
					ListBiNode<T>* argument = element;

					for (int i = 0; i < (count - 1); i++)	//Iteracja count-1 razy by utworzyc porzadana liczbe elementow
					{
						if (argument->pNext)
						{
							argument = argument->pNext;
						}
						else
						{
							throw out_of_range("Podany element listy nie posiada tylu nastepnikow!");
							return;
						}

						tmp->pNext = new ListBiNode<T>(argument->data, nullptr, tmp);
						tmp = tmp->pNext;
					}
				}
				else
				{
					//Wyjątek w przypadku podania pustej listy
					throw invalid_argument("[Assign] Podana lista jest pusta!");
				}
			}
			else
			{
				//Wyjątek w przypadku podania ujemnej liczby
				throw invalid_argument("[Assign] Podana liczba nie jest liczba dodatnia!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
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
			if (count > 0 && count <= MaxSize())
			{
				if (valuePtr != nullptr)
				{
					this->Clear();	//Zwolnienie wcześniej istniejącej pamieci
					this->pHead = new ListBiNode<T>(*valuePtr, nullptr, nullptr);	//Utworzenie głowy
					ListBiNode<T>* tmp = this->pHead;

					for (int i = 1; i < count; i++)	//Iteracja count-1 razy by utworzyc porzadana liczbe elementow
					{
						tmp->pNext = new ListBiNode<T>(*(valuePtr + i), nullptr, tmp);
						tmp = tmp->pNext;
					}
				}
				else
				{
					//Wyjątek w przypadku podania pustego wskaźnika
					throw invalid_argument("[Assign] Podano pusty wskaźnik!");
				}
			}
			else
			{
				//Wyjątek w przypadku podania ujemnej liczby
				throw invalid_argument("[Assign] Podana liczba nie jest liczba dodatnia!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
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
			if (value != returnEmpty())
			{
				if (count > 0 && count <= MaxSize())
				{
					this->Clear();	//Zwolnienie wcześniej istniejącej pamieci
					this->pHead = new ListBiNode<T>(value, nullptr, nullptr);	//Utworzenie głowy
					ListBiNode<T>* tmp = this->pHead;

					for (int i = 0; i < (count - 1); i++)	//Iteracja count-1 razy by utworzyc porzadana liczbe elementow
					{
						tmp->pNext = new ListBiNode<T>(value, nullptr, tmp);
						tmp = tmp->pNext;
					}
				}
				else
				{
					//Wyjątek w przypadku podania ujemnej liczby
					throw invalid_argument("[Assign] Podana liczba nie jest liczba dodatnia!");
				}
			}
			else
			{
				throw invalid_argument("[Assign] Pusty argument!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Zamiana zawartości między dwoma kontenerami.

	@param tmp Drugi kontener.
	*/
	void Swap(ListBi& l2)
	{
		ListBiNode<T>* tmp = this->pHead;	//Zmienna tymczasowa przechowująca głowę
		this->pHead = l2.pHead;			//Przypisanie głowy obiektu z argumentu
		l2.pHead = tmp;					//Przypisanie głowy this do obiektu z argumentu
	}

	/**
	Przepięcie elementów innego kontenera na odpowiednią pozycję.

	@param position Pozycja na przepięcie.
	@param x Wskaźnik na inny kontener.
	*/
	void Splice(int position, ListBi& x)
	{
		try
		{
			int size1 = this->Size();
			int size2 = x.Size();

			if ((position < size1) && (position > -1))
			{
				if (position == 0)
				{
					x.End()->pNext = this->pHead;
					this->pHead->pPrev = x.End();

					this->pHead = x.Begin();
				}
				else if (position > 0)
				{
					ListBiNode<T>* tmp = this->pHead;
					for (int i = 1; i < position; i++)
					{
						tmp = tmp->pNext;
					}
					x.End()->pNext = tmp->pNext;
					tmp->pNext->pPrev = x.End();

					tmp->pNext = x.Begin();
					tmp->pNext->pPrev = tmp;
				}
				x.pHead = nullptr;
			}
			else
			{
				throw invalid_argument("[Splice] Podany indeks lub lista jest za mała!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Szukanie elementu po podanej wartości.

	@param value Wartość elementu do odszukania.
	@return Indeks elementu, jeżeli został odnaleziony.
	*/
	ListBiNode<T>* findElement(const T value)
	{
		//Jeśli głowa istnieje
		if (pHead)
		{
			//Jeśli podany T nie jest pusty
			if (value != returnEmpty())
			{
				//Sprawdz wszystkie elementy w poszukiwaniu elementu o tej wartosci i zwroc ja
				ListBiNode<T>* tmp = this->pHead;
				while (tmp)
				{
					if (tmp->data == value) return tmp;
					tmp = tmp->pNext;
				}
				return nullptr;
			}
		}
		return nullptr;
	}

	/**
	Sprawdzenie czy element istnieje, szukany po wartości.

	@param value Szukana wartość.
	@return Status operacji: true jeżeli jest pusty, w innym przypadku false.
	*/
	bool findIfExist(const T value)
	{
		//Jeśli głowa istnieje
		if (pHead)
		{
			//Jeśli podany T nie jest pusty
			if (value != returnEmpty())
			{
				//Sprawdz wszystkie elementy w poszukiwaniu elementu o tej wartosci i zwroc ja
				ListBiNode<T>* tmp = this->pHead;
				while (tmp)
				{
					if (tmp->data == value) return true;
					tmp = tmp->pNext;
				}
				return false;
			}
		}
		return false;
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
		if (this->pHead) { return false; }
		return true;
	}

	/**
	Zwrócenie wielkości kontenera.

	@return Wartość spod zmiennej size.
	*/
	
	int Size() const noexcept
	{
		int counter = 0;
		ListBiNode<T>* tmp = this->pHead;

		//Obrót pętlą tyle razy ile występuje elementów +  zliczanie ich
		while (tmp != nullptr)
		{
			counter++;
			tmp = tmp->pNext;
		}
		return counter;
	}

	/**
	Zniszczenie zawartości kontenera i ustawienie jego wielkości na 0
	*/
	void Clear() noexcept
	{
		if (pHead)
		{
			ListBiNode<T>* tmp = nullptr;
			while (pHead)
			{
				tmp = pHead->pNext;
				delete pHead;
				pHead = tmp;
			}
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
			//Czy indeks mieści się w przedziale <0, size>
			if ((position < this->Size()) && (position > -1))
			{
				//gdy chcemy usunac glowe
				if (position == 0)
				{
					ListBiNode<T>* tmp = this->pHead->pNext;
					delete pHead;
					pHead = tmp;
				}
				//gdy inny element
				else
				{
					ListBiNode<T>* tmp = this->pHead;
					for (int i = 0; i < position; i++)
					{
						tmp = tmp->pNext;
					}
					tmp->pPrev->pNext = tmp->pNext;
					tmp->pNext->pPrev = tmp->pPrev;
					delete tmp;
				}
			}
			else
			{
				throw invalid_argument("[Erase] Indeks elementu do usuniecia nie jest w przedziale <0,size>!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
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
			//Czy indeks mieści się w przedziale <0, size>
			if ((first < this->Size()) && (first > -1) && (last < this->Size()) && (last > -1) && (first <= last))
			{
				//gdy chcemy usunac glowe
				if (first == 0)
				{
					ListBiNode<T>* tmp = this->pHead->pNext;
					delete pHead;

					ListBiNode<T>* tmp2 = nullptr;
					for (int i = 1; i < last; i++)
					{
						tmp2 = tmp->pNext;
						delete tmp;
						tmp = tmp2;
					}
					pHead = tmp;
					tmp->pPrev = nullptr;
				}
				//gdy inny element
				else
				{
					ListBiNode<T>* tmp = this->pHead;
					for (int i = 2; i < first; i++)
					{
						tmp = tmp->pNext;
					}

					ListBiNode<T>* tmp2 = nullptr;
					for (int j = 0; j < ((last - first) + 1); j++)
					{
						tmp2 = tmp->pNext->pNext;
						delete tmp->pNext;
						tmp->pNext = tmp2;
						tmp->pNext->pPrev = tmp;
					}
				}
			}
			else
			{
				throw invalid_argument("[Erase] Podano bledne argumenty!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Usunięcie wybranego elementu ze zwolnieniem pamięci.

	@param value Wartość elementu do usunięcia.
	*/
	void Remove(const T& value)
	{
		try
		{
			//Jeśli głowa istnieje
			if (pHead)
			{
				//Jeśli podany T nie jest pusty
				if (value != returnEmpty() && findIfExist(value))
				{
					if (value == pHead->data)
					{
						//Gdy elementem do usuniecia jest glowa
						ListBiNode<T>* tmp = pHead->pNext;
						delete pHead;
						pHead = tmp;
						pHead->pPrev = nullptr;
					}
					else
					{
						//Sprawdz wszystkie elementy w poszukiwaniu elementu o tej wartosci i usun ja
						ListBiNode<T>* tmp = this->pHead->pNext;
						while (tmp)
						{
							if (tmp->data == value)
							{
								tmp->pNext->pPrev = tmp->pPrev;
								tmp->pPrev->pNext = tmp->pNext;
								delete tmp;
							}
							tmp = tmp->pNext;
						}
					}
				}
				else
				{
					throw invalid_argument("[Remove] Podano pusty T!");
				}

			}
			else
			{
				throw out_of_range("[Remove] Lista jest pusta!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
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
	Zmiana wielkości kontenera na podaną.
	- Mniejsza niż aktualna: ucięcie kontenera.
	- Większa niż aktualna: nowe elementy są puste.

	@param n Nowa wielkość kontenera.
	*/
	void Resize(int n)
	{
		try
		{
			if (n > 0 && n <= MaxSize())
			{
				int size = this->Size();
				if (n < size)
				{
					this->Erase(n, size - 1);
				}
				else
				{
					int diff = abs(size - n);
					for (int i = 0; i < diff; i++)
					{
						this->PushBack(returnEmpty());
					}
				}
			}
			else
			{
				throw invalid_argument("[Resize] Wartosc powiekszenia mniejsza od 0!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
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
			if (value != returnEmpty())
			{
				if (n > 0 && n <= MaxSize())
				{
					int size = this->Size();
					if (n < size)
					{
						this->Erase(n, size - 1);
					}
					else
					{
						int diff = abs(size - n);
						for (int i = 0; i < diff; i++)
							this->PushBack(value);
					}
				}
				else
				{
					throw invalid_argument("[Resize] Wartosc powiekszenia mniejsza od 0!");
				}
			}
			else
			{
				throw invalid_argument("[Resize] Pusty argument!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[ListBi<" << showType() << ">] " << e.what() << endl;
		}
	}



	/*8.SORTOWANIE/PRZESTAWIANIE*/

	/**
	Sortowanie elementów w kontenerze
	*/
	void Sort()
	{
		if (pHead)
		{
			//Utworzenie tablicy do zapisu
			int size = this->Size();
			T* tab = new T[size];

			//Pobranie elementow z listy
			ListBiNode<T>* tmp = pHead;
			for (int i = 0; i < size; i++)
			{
				tab[i] = tmp->data;
				tmp = tmp->pNext;
			}

			//Sortowanie tablicy
			this->insertionsort(tab, size);

			//Zapis nowego ukladu
			tmp = pHead;
			for (int j = 0; j < size; j++)
			{
				tmp->data = tab[j];
				tmp = tmp->pNext;
			}

			delete[] tab;
		}
	}

	/**
	Odwrócenie elementów kontenera kolejnością.
	*/
	void Reverse() noexcept
	{
		//Jeśli głowa istnieje
		if (pHead)
		{
			//Tworzy tablice na dane
			int size = this->Size();
			T* tab = new T[size];

			//Zapisuje dane z listy do tablicy
			ListBiNode<T>* tmp = pHead;
			for (int i = 0; i < size; i++)
			{
				tab[i] = tmp->data;
				tmp = tmp->pNext;
			}

			//Zapisuje dane z tablicy w odwrotnej kolejnosci
			tmp = pHead;
			for (int j = 1; j < (size + 1); j++)
			{
				tmp->data = tab[size - j];
				tmp = tmp->pNext;
			}

			delete[] tab;
		}
	}

	/**
	Wyświetlenie wszystkich elementów kontenera.
	*/
	void Show()
	{
		if (pHead)
		{
			cout << "\n| ";
			int size = Size();
			ListBiNode<T>* tmp = this->pHead;
			for (int i = 0; i < size; i++)
			{
				cout << tmp->data << " | ";
				tmp = tmp->pNext;
			}
			cout << endl;
		}
		else
		{
			cout << "\nKontener jest pusty!" << endl;
		}
	}
};