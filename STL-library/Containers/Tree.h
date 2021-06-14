#pragma once
#include <iostream>
#include <limits>
#include <regex>
#include <iterator>
#include <exception>
#include <sstream>
#include "Containers.h"
#include "Nudes.h"

using namespace std;

template <class T>
class Tree : public Container<T>
{
	//Korzeń drzewa
	TreeNode<T>* root;
	//Ilość elementów w drzewie
	int size;



	/*KLASY POMOCNICZE*/

	/**
	Rekurencyjna funkcja pomocnicza dla operatora =.
	Skopiowanie do kontenera wartości z drugiego.

	@param rhs Wskaźnik na element z drugiego drzewa.
	@return Wskaźnik na skopiowane elementy.
	*/
	TreeNode<T>* CopyRec(TreeNode<T>* rhs)
	{
		TreeNode<T>* copyNode = nullptr;
		if (root)
		{
			copyNode = new TreeNode<T>();
			copyNode->data = rhs->data;
			if (rhs->pLeft != nullptr)
			{
				copyNode->pLeft = CopyRec(rhs->pLeft);
			}
			else
			{
				copyNode->pLeft = nullptr;
			}
			if (rhs->pRight != nullptr)
			{
				copyNode->pRight = CopyRec(rhs->pRight);
			}
			else
			{
				copyNode->pRight = nullptr;
			}
		}
		return copyNode;

	}

	/**
	Rekurencyjna funkcja pomocnicza dla operatora ==.
	Sprawdzenie czy oba kontenery są identyczne.

	@param root Wskaźnik na element pierwszego drzewa.
	@param rhs Wskaźnik na element drugiego drzewa.
	@return Status operacji: true, jeżeli są równe; false, jeśli nie.
	*/
	bool sameRec(TreeNode<T>* root, TreeNode<T>* rhs)
	{
		if (root != nullptr && rhs != nullptr)
		{
			sameRec(root->pLeft, rhs->pLeft);
			if (root->data != rhs->data)
			{
				return false;
			}
			sameRec(root->pRight, rhs->pRight);
			if (root->data != rhs->data)
			{
				return false;
			}
			return true;
		}
	}

	/**
	Rekurencyjna funkcja pomocnicza dla Insert.
	Dodanie elementu z podaną wartością.

	@param root Wskaźnik na element drzewa.
	@param value Wartość do dodania.
	@return Wskaźnik na dodany element z podaną wartością.
	*/
	TreeNode<T>* InsertRec(TreeNode<T>* root, T value)
	{
		if (root == nullptr)
		{
			TreeNode<T>* newNode = new TreeNode<T>(value, nullptr, nullptr);
			root = newNode;
			size++;
		}
		else if (value >= root->data)
		{
			root->pRight = InsertRec(root->pRight, value);
		}
		else
		{
			root->pLeft = InsertRec(root->pLeft, value);
		}
		return root;
	}

	/**
	Rekurencyjna funkcja pomocnicza dla Remove.
	Usunięcie elementu z podaną wartością.

	@param root Wskaźnik na element drzewa.
	@param value Wartość do usunięcia.
	@return Wskaźnik na element z podaną wartością.
	*/
	TreeNode<T>* removeRec(TreeNode<T>* root, T value)
	{
		TreeNode<T>* tmp;
		if (root == nullptr)
		{
			return nullptr;
		}
		else if (value < root->data)
		{
			root->pLeft = removeRec(root->pLeft, value);
		}
		else if (value > root->data)
		{
			root->pRight = removeRec(root->pRight, value);
		}
		else if (root->pLeft && root->pRight)
		{
			tmp = findMinRec(root->pRight);
			root->data = tmp->data;
			root->pRight = removeRec(root->pRight, root->data);
		}
		else
		{
			tmp = root;
			if (root->pLeft == nullptr)
			{
				root = root->pRight;
			}
			else if (root->pRight == nullptr)
			{
				root = root->pLeft;
			}
			delete tmp;
			size--;
		}

		return root;
	}

	/**
	Rekurencyjna funkcja pomocnicza dla findParent.
	Znalezienie rodzica elementu z podaną wartością.

	@param root Wskaźnik na element drzewa.
	@param value Wartość do znalezienia.
	@return Wskaźnik na rodzica elementu z podaną wartością.
	*/
	TreeNode<T>* findParentRec(TreeNode<T>* root, T value)
	{
		if (this->root == nullptr || (this->root->pLeft == nullptr && this->root->pRight == nullptr))
		{
			return nullptr;
		}
		else if ((root->pLeft != nullptr && root->pLeft->data == value) || (root->pRight != nullptr && root->pRight->data == value))
		{
			return root;
		}
		else if (value < root->data)
		{
			return findParentRec(root->pLeft, value);
		}
		else if (value > root->data)
		{
			return findParentRec(root->pRight, value);
		}
	}

	/**
	Rekurencyjna funkcja pomocnicza dla findMin.
	Znalezienie elementu drzewa z najmniejszą wartością.

	@param root Wskaźnik na element drzewa.
	@return Wskaźnik na element z najmniejszą wartością.
	*/
	TreeNode<T>* findMinRec(TreeNode<T>* root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		else if (root->pLeft == nullptr)
		{
			return root;
		}
		else
		{
			return findMinRec(root->pLeft);
		}
	}

	/**
	Rekurencyjna funkcja pomocnicza dla findMax.
	Znalezienie elementu drzewa z największą wartością.

	@param root Wskaźnik na element drzewa.
	@return Wskaźnik na element z największą wartością.
	*/
	TreeNode<T>* findMaxRec(TreeNode<T>* root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		else if (root->pRight == nullptr)
		{
			return root;
		}
		else
		{
			return findMaxRec(root->pRight);
		}
	}

	/**
	Rekurencyjna funkcja pomocnicza dla findElement.
	Znalezienie elementu drzewa z podaną wartością.

	@param root Wskaźnik na element drzewa.
	@param value Wartość do znalezienia.
	@return Wskaźnik na element z podaną wartością.
	*/
	TreeNode<T>* findRec(TreeNode<T>* root, T value)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		else if (value < root->data)
		{
			return findRec(root->pLeft, value);
		}
		else if (value > root->data)
		{
			return findRec(root->pRight, value);
		}
		else
		{
			return root;
		}
	}

	/**
	Rekurencyjna funkcja pomocnicza dla Clear.
	Wyczyszczenie drzewa.

	@param root Wskaźnik na element drzewa.
	*/
	void clearRec(TreeNode<T>* root)
	{
		if (root != nullptr)
		{
			clearRec(root->pLeft);
			clearRec(root->pRight);
			root->pLeft = nullptr;
			root->pRight = nullptr;
			delete root;
		}
	}

	/**
	Rekurencyjna funkcja pomocnicza dla Height.
	Zliczanie wysokości drzewa.

	@param root Wskaźnik na element drzewa.
	*/
	int heightRec(TreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		else
		{
			int lHeight = heightRec(root->pLeft);
			int rHeight = heightRec(root->pRight);

			return max(lHeight, rHeight) + 1;
		}
	}

	/**
	Rekurencyjna funkcja pomocnicza dla leafCount.
	Zliczanie ilości liści w drzewie.

	@param root Wskaźnik na element drzewa.
	*/
	int leafRec(TreeNode<T>* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		else if (root->pLeft == nullptr && root->pRight == nullptr)
		{
			return 1;
		}
		else
		{
			return leafRec(root->pLeft) + leafRec(root->pRight);
		}
	}

	/**
	Rekurencyjna funkcja pomocnicza dla inOrderShow.
	Wyświetlanie drzewa według rosnącej kolejności.

	@param root Wskaźnik na element drzewa.
	*/
	void InOrderRec(TreeNode<T>* root)
	{
		if (root == nullptr)
		{
			return;
		}
		else
		{
			InOrderRec(root->pLeft);
			cout << root->data << " ";
			InOrderRec(root->pRight);
		}
	}

	/**
	Rekurencyjna funkcja pomocnicza dla preOrderShow.
	Wyświetlanie drzewa według kolejności Pre.

	@param root Wskaźnik na element drzewa.
	*/
	void preOrderRec(TreeNode<T>* root)
	{
		if (root == nullptr)
		{
			return;
		}
		else
		{
			cout << root->data << " ";
			preOrderRec(root->pLeft);
			preOrderRec(root->pRight);
		}
	}

	/**
	Rekurencyjna funkcja pomocnicza dla postOrderShow.
	Wyświetlanie drzewa według kolejności Post.

	@param root Wskaźnik na element drzewa.
	*/
	void postOrderRec(TreeNode<T>* root)
	{
		if (root == nullptr)
		{
			return;
		}
		else
		{
			postOrderRec(root->pLeft);
			postOrderRec(root->pRight);
			cout << root->data << " ";
		}
	}

	/**
	Rekurencyjna funkcja pomocnicza dla levelOrderShow.
	Wyświetlanie drzewa według jego poziomów.

	@param root Wskaźnik na element drzewa.
	@param level Ilość poziomów do wyświetlenia.
	*/
	void levelOrderRec(TreeNode<T>* root, int level)
	{
		if (root == nullptr)
		{
			return;
		}
		if (level == 0)
		{
			cout << root->data << " ";
		}
		else
		{
			levelOrderRec(root->pLeft, level - 1);
			levelOrderRec(root->pRight, level - 1);
		}
	}

	/**
	Rekurencyjna funkcja pomocnicza treeShow.
	Wyświetlanie kontenera w formie drzewa	.

	@param root Wskaźnik na element drzewa.
	@param space Odległość między poziomami.
	@param count Podana odległość.
	*/
	void treeRec(TreeNode<T>* root, int space, int count)
	{
		if (root == nullptr)
		{
			return;
		}
		space += count;
		treeRec(root->pRight, space, count);
		cout << endl;

		for (int i = count; i < space; i++)
		{
			cout << " ";
		}
		cout << root->data << endl;

		treeRec(root->pLeft, space, count);
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
	Tree()
	{
		if (allowedType())
		{
			root = nullptr;
			size = 0;
		}
		else
		{
			root = nullptr;
			size = 0;
			cerr << "\n[Tree<" << showType() << ">] " << "[Konstruktor domyslny] Niedozwolony typ!" << endl;
		}
	}

	/**
	Konstruktor jednoargumentowy.
	- Dodaje podaną wartość jako pierwszy element.

	@param value Wartość do wpisania.
	*/
	Tree(T value)
	{
		if (allowedType() && value != returnEmpty())
		{
			this->root = new TreeNode<T>(value, nullptr, nullptr);
			this->size = 1;
		}
		else
		{
			root = nullptr;
			size = 0;
			cerr << "\n[Tree<" << showType() << ">] " << "[Konstruktor domyslny] Niedozwolony typ!" << endl;
		}
	}

	/**
	Konstruktor kopiujący.
	- Tworzy kontener będący kopią podanego.

	@param other Wskaźnik na drugi kontener.
	*/
	Tree(Tree& other) 
	{
		if (!other.Empty())
		{
			this->size = other.size;

			this->root = new TreeNode<T>();
			root = CopyRec(other.root);
		}
		else
		{
			root = nullptr;
			size = 0;
		}
	}



	/*2.DESTRUKTOR*/

	/**
	Destruktor
	- główna metoda zwalniająca pamięć
	*/
	~Tree()
	{
		TreeNode<T>* tmp = nullptr;
		clearRec(root);
		root = tmp;
		size = 0;
	}



	/*3.PRZECIĄŻONE OPERATORY*/

	/**
	Operator przeciążony przypisania "="

	@param value Wskaźnik na drugi kontener.
	@return Przypisany kontener.
	*/
	Tree<T>& operator=(Tree& rhs)
	{
		if (!rhs.Empty())
		{
			TreeNode<T>* tmp = CopyRec(rhs.root);
			this->root = tmp;
			this->size = rhs.size;
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

	@param rhs Wskaźnik na drugi kontener.
	@return Status operacji: true, jeżeli są równe; false jeśli nie.
	*/
	bool operator==(Tree& rhs)
	{
		int size1 = this->size;
		int size2 = rhs.size;

		if (size1 == size2)
		{
			if (root->data == rhs.root->data)
			{
				return sameRec(root, rhs.root);
			}
			else
			{
				return false;
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
	bool operator!=(Tree& rhs)
	{
		return !(*this == rhs);
	}



	/*4.PUSH I POP*/

	/**
	Usunięcie najmniejszego elementu i zmniejszenie wielkości o jeden.
	*/
	void PopMin()
	{
		try
		{
			//Brak elementów
			if (this->root == nullptr)
			{
				throw out_of_range("Proba usuniecia ostatniego elementu z pustej listy!");
			}
			//Jeden element w liście
			else if (this->root->pLeft == nullptr && this->root->pRight == nullptr)
			{
				delete root;
				root = nullptr;
				size = 0;
			}
			//Więcej niż jeden element w liście
			else
			{
				TreeNode<T>* min = findMinRec(root);
				removeRec(root, min->data);
			}
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Tree<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Usunięcie najmniejszego elementu i zmniejszenie wielkości o jeden.
	*/
	void PopMax()
	{
		try
		{
			//Brak elementów
			if (this->root == nullptr)
			{
				throw out_of_range("Proba usuniecia ostatniego elementu z pustej listy!");
			}
			//Jeden element w liście
			else if (this->root->pLeft == nullptr && this->root->pRight == nullptr)
			{
				delete root;
				root = nullptr;
				size = 0;
			}
			//Więcej niż jeden element w liście
			else
			{
				TreeNode<T>* max = findMaxRec(root);
				removeRec(root, max->data);
			}
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Tree<" << showType() << ">] " << e.what() << endl;
		}
	}

	

	/*5.REFERENCJE I WSKAŹNIKI*/


	/**
	Znalezienie elementu w drzwie dla podanej wartości.

	@param value Wartość, której poszukujemy.
	@return Pointer na element.
	*/
	TreeNode<T>* findValue(T value)
	{
		if (allowedType())
		{
			if (value != returnEmpty())
			{
				return findRec(root, value);
			}
		}
		return nullptr;
	}

	/**
	Znalezienie rodzica dla podanej wartości.

	@param value Wartość, dla której poszukujemy rodzica.
	@return Pointer na rodzica.
	*/
	TreeNode<T>* findParent(T value)
	{
		if (allowedType())
		{
			if (root->data == value)
			{
				return nullptr;
			}
			else if (value != returnEmpty() && findIfExist(value))
			{
				return findParentRec(root, value);
			}
		}
		return nullptr;
	}

	/**
	Znalezienie wartości najmniejszej w drzewie.

	@return pointer na mina.
	*/
	TreeNode<T>* findMinPtr()
	{
		if (root)
		{
			return findMinRec(root);
		}
		return nullptr;
	}

	/**
	Znalezienie wartości najmniejszej w drzewie.

	@return pointer na mina.
	*/
	TreeNode<T>& findMin()
	{
		if (root)
		{
			return *findMinRec(root);
		}
		return nullptr;
	}

	/**
	Znalezienie wartości największej w drzewie.

	@return pointer na maxa.
	*/
	TreeNode<T>* findMaxPtr()
	{
		if (root)
		{
			return findMaxRec(root);
		}
		return nullptr;
	}

	/**
	Znalezienie wartości największej w drzewie.

	@return pointer na maxa.
	*/
	TreeNode<T>& findMax()
	{
		if (root)
		{
			return *findMaxRec(root);
		}
		T empty = returnEmpty();
		return empty;
	}



	/*6.WPROWADZANIE DANYCH*/

	/**
	Dodanie podanego elementu i zwiększenie wiekości kontenera.

	@param value Nowy element.
	*/
	void Insert(const T& value)
	{
		try
		{
			if (allowedType())
			{
				if (value != returnEmpty() && !findIfExist(value))
				{
					if (this->root == nullptr)
					{
						TreeNode<T>* newNode = new TreeNode<T>(value, nullptr, nullptr);
						this->root = newNode;
						size = 1;
					}
					else if ((size + 1) <= MaxSize())
					{
						if (value >= root->data)
						{
							root->pRight = InsertRec(root->pRight, value);
						}
						else
						{
							root->pLeft = InsertRec(root->pLeft, value);
						}

					}
					else
					{
						throw out_of_range("Kontener posiada już maksymalny rozmiar!");
					}
				}
				else
				{
					throw invalid_argument("Wartość nie może być pusta!");
				}
			}
			else
			{
				throw invalid_argument("Wartość ma niewłaściwy typ!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Tree<" << showType() << ">] " << e.what() << endl;
		}
		catch (const out_of_range& e)
		{
			cerr << "\n[Tree<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Wstawienie nowego elementu na pozycje podanego starego.

	@param oldValue Stary element.
	@param newValue Nowy element.
	*/
	void Emplace(T oldValue, T newValue)
	{
		try
		{
			if (allowedType())
			{
				if (newValue != returnEmpty() && findIfExist(oldValue) && !findIfExist(newValue))
				{
					Remove(oldValue);
					Insert(newValue);
				}
				else
				{
					throw invalid_argument("Wartość nie może być pusta!");
				}
			}
			else
			{
				throw invalid_argument("Wartość ma niewłaściwy typ!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Tree<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Zamiana zawartości między dwoma kontenerami.

	@param rhs Drugi kontener.
	*/
	void Swap(Tree& rhs)
	{
		TreeNode<T>* tmpData = this->root;	//Zmienna tymczasowa przechowująca głowę
		this->root = rhs.root;				//Przypisanie głowy obiektu z argumentu
		rhs.root = tmpData;					//Przypisanie głowy this do obiektu z argumentu
		
		int tmpSize = this->size;
		this->size = rhs.size;
		rhs.size = tmpSize;
	}

	/**
	Stwierdzenie czy dany element istnieje w drzewie.

	@param value Wartość, której poszukujemy.
	@return Status operacji: true, jeżeli element z podaną wartością został odnaleziony; false, jeśli nie.
	*/
	bool findIfExist(T value)
	{
		if (allowedType())
		{
			if (value != returnEmpty())
			{
				if (findRec(root, value) != nullptr)
				{
					return true;
				}
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
		if (size == 0) return true;
		return false;
	}

	/**
	Zwrócenie wielkości kontenera.

	@return Wartość spod zmiennej size.
	*/
	int Size() const noexcept
	{
		return size;
	}

	/**
	Zniszczenie zawartości kontenera i ustawienie jego wielkości na 0
	*/
	void Clear()
	{
		if (root)
		{
			size = 0;
			clearRec(root);
			root = nullptr;
		}
	}

	/**
	Usunięcie wybranego elementu ze zwolnieniem pamięci.

	@param value Wartość elementu do usunięcia.
	@return Status operacji: true, jeżeli element istniał i został usunięty; false jeśli nie.
	*/
	void Remove(T value)
	{
		try
		{
			if (allowedType())
			{
				if (value != returnEmpty() && findIfExist(value))
				{
					removeRec(root, value);
				}
				else
				{
					throw invalid_argument("Wartość nie może być pusta!");
				}
			}
			else
			{
				throw invalid_argument("Wartość ma niewłaściwy typ!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Tree<" << showType() << ">] " << e.what() << endl;
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
	Zliczenie wysokosci drzewa.

	@return Wysokość drzewa.
	*/
	int Height()
	{
		if (root == nullptr)
		{
			return 0;
		}
		else if (root->pLeft == nullptr && root->pRight == nullptr)
		{
			return 1;
		}
		else
		{
			return heightRec(root);
		}
	}

	/**
	Zliczenie ilości liści drzewa - elementów bez dzieci.

	@return Ilość liści w drzewie.
	*/
	int leafCount()
	{
		if (root == nullptr)
		{
			return 0;
		}
		else if (root->pLeft == nullptr && root->pRight == nullptr)
		{
			return 1;
		}
		else
		{
			return leafRec(root);
		}
	}

	/**
	Zliczenie różnicy miedzy lewą, a prawą wysokością drzewa.

	@return Różnica między wysokościami drzewa.
	*/
	int heightDiffrence()
	{
		if (root == nullptr)
		{
			return 0;
		}
		else if (root->pLeft == nullptr && root->pRight == nullptr)
		{
			return 0;
		}
		else
		{
			int lHeight = Height(root->pLeft);
			int rHeight = Height(root->pRight);
			return lHeight - rHeight;
		}
	}



	/*8.SORTOWANIE/PRZESTAWIANIE*/

	/**
	Wyświetlenie wszystkich elementów kontenera rosnąco.
	*/
	void inOrderShow()
	{
		try
		{
			if (root != nullptr)
			{
				cout << "\nWielkość: " << size << endl;
				cout << "Dane: ";
				InOrderRec(root);
				cout << endl;

			}
			else
			{
				throw invalid_argument("Nie można wyświetlić pustego kontenera!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Tree<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Wyświetlenie wszystkich elementów kontenera in kolejności Pre.
	*/
	void preOrderShow()
	{
		try
		{
			if (root != nullptr)
			{
				cout << "\nWielkość: " << size << endl;
				cout << "Dane: ";
				preOrderRec(root);
				cout << endl;

			}
			else
			{
				throw invalid_argument("Nie można wyświetlić pustego kontenera!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Tree<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Wyświetlenie wszystkich elementów kontenera in kolejności Post.
	*/
	void postOrderShow()
	{
		try
		{
			if (root != nullptr)
			{
				cout << "\nWielkość: " << size << endl;
				cout << "Dane: ";
				postOrderRec(root);
				cout << endl;

			}
			else
			{
				throw invalid_argument("Nie można wyświetlić pustego kontenera!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Tree<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Wyświetlenie drzewa według poziomów drzewa.
	*/
	void levelOrderShow()
	{
		try
		{
			if (root != nullptr)
			{
				int height = Height();
				for (int i = 0; i < height; i++)
				{
					cout << "Poziom: " << i << " -> ";
					levelOrderRec(root, i);
					cout << endl;
				}
			}
			else
			{
				throw invalid_argument("Nie można wyświetlić pustego kontenera!");
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "\n[Tree<" << showType() << ">] " << e.what() << endl;
		}
	}

	/**
	Rotacja drzewa w lewą stronę.

	@return Pointer na korzeń po rotacji.
	*/
	TreeNode<T>* leftRotation()
	{
		if (root != nullptr)
		{
			if (root->pRight != nullptr)
			{
				TreeNode<T>* tmp;
				tmp = root->pRight;
				root->pRight = tmp->pLeft;
				tmp->pLeft = root;
				root = tmp;
				return root;
			}
		}
		return nullptr;
	}
	/**
	Rotacja drzewa w prawą stronę.

	@return Pointer na korzeń po rotacji.
	*/
	TreeNode<T>* rightRotation()
	{
		if (root != nullptr)
		{
			if (root->pLeft != nullptr)
			{
				TreeNode<T>* tmp;
				tmp = root->pLeft;
				root->pLeft = tmp->pRight;
				tmp->pRight = root;
				root = tmp;
				return root;
			}
		}
		return nullptr;
	}

	/**
	Wyświetlenie kontenera w formie drzewa.
	*/
	void Show()
	{
		if (root)
		{
			treeRec(root, 0, 10);
		}
		else
		{
			cout << "Kontener jest pusty!" << endl;
		}
	}
};