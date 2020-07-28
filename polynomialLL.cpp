//============================================================================
// Name        : polynomialLL.cpp
// Author      : Seongbeom Jeon
// Description : Perform basic operations on polynomials using linked lists
//============================================================================

#include <iostream>
using namespace std;

//Exceptions for Linked List class
class LinkedListMemory {};
class LinkedListNotFound {};
class LinkedListBounds {};
class LinkedListAttachToEmpty {};

template <class DT>
class LinkedList {
protected:
	DT* _info; //Stored in the node
	LinkedList<DT>* _next; //Points to the next linked list

public:
	LinkedList(); //Default constructor
	LinkedList(const DT& info); //Constructor with info 
	LinkedList(const LinkedList<DT>& ll); //Copy constructor
	LinkedList(const DT& info, LinkedList<DT>* next);
	virtual ~LinkedList(); //Destructor
	void copy(const LinkedList<DT>& ll); //Copy method
	void operator=(const LinkedList<DT>& ll); //Overloaded = method
	DT& infoAt(int pos); //Returns the info at specified position of the linked list
	DT& operator[](int pos); //overloaded [] operator, returns info at [x];
	bool isEmpty(); //Returns true if Linked list is occupied, otherwise false
	void add(const DT& Obj); //Add objects to the beginning of the linked list
	void insertAt(const DT& newObj, int pos); //Insert object at specified position of linked list
	DT remove(); //Remove the first element in the linked list
	DT removeAt(int pos); //Remove object at specified positin of linked list
	int size(); //Returns the current size of the linked list
	LinkedList<DT>* next(); //Returns the linked list pointed to by the _next
	void setNext(LinkedList<DT>* next); //Set the pointer to next linkedlist and return the previous pointer

};

class Term {
protected:
	int coefficient; //coefficient of the term
	int exponent; //degree of the term
public:
	Term(); //Default constructor
	Term(int coeff, int expo); //Constructor that accepts coefficient and the exponent
	Term(const Term& t); //Copy constructor
	virtual ~Term(); //Destructor
	void copy(const Term& t); //Copy method
	void operator=(const Term& t); //Overloaded = method
	void display(ostream& output); //Display the individual term
	friend ostream& operator<<(ostream& output, Term& t);
	int getCoefficient(); //Get the coefficient of the term
	int getExponent(); //Get the exponent;
	void Coeff(int val); //Set the coefficient (for adding)
	void Exp(int val); //Set the exponent

};

template <class DT>
class Polynomial {
protected:
	LinkedList<Term>* myPoly;
public:
	Polynomial(); //Default constructor
	Polynomial(int size); //Constructor with size initialized
	virtual ~Polynomial(); //Destructor
	DT evaluatePoly(DT x); //Evaluate the polynomial with the given value
	bool addTerm(int coefficient, int exponent); //Add term to polynomial, determine if it was successful or not
	bool deleteTerm(int exponent); //Delete the term with specified exponent in it
	Polynomial<DT> addPolynomial(Polynomial<DT> x); //Add the polynomial with the given polynomial
	Polynomial<DT> operator+ (Polynomial x); //Overload + to add the polynomials
	Polynomial multiplyPolynomial(Polynomial x); //Multiply the polynomial with the given polynomial
	Polynomial operator* (Polynomial x); //Overload * to multiply
	void display(ostream& output); //Display the polynomial
	friend ostream& operator<<(ostream& output, Polynomial p) { //Overloaded ostream for Polynomial
		p.display(output);
		return output;
	}
	void sort();


};

template <class DT>
LinkedList<DT>::LinkedList() {
	_info = NULL;
	_next = NULL;
}

template <class DT>
LinkedList<DT>::LinkedList(const DT& info, LinkedList<DT>* next) {
	_info = new DT(info);
	if (_info == NULL) {
		throw LinkedListMemory();
	}
	_next = next;
}

template <class DT>
void LinkedList<DT>::copy(const LinkedList<DT>& ll) {

	if (ll._info == NULL)
		_info = NULL;
	else {
		_info = new DT(*(ll._info));
		if (_info == NULL)
			throw LinkedListMemory();
	}
	if (ll._next == NULL)
		_next = NULL;
	else {
		_next = new DT(*(ll._next));
		if (_next == NULL)
			throw LinkedListMemory();
	}
}

template <class DT>
LinkedList<DT>::LinkedList(const DT& info) {
	_info = new DT(info);
	if (_info == NULL) {
		throw LinkedListMemory();
	}

	_next = NULL;
}

template <class DT>
LinkedList<DT>::LinkedList(const LinkedList<DT>& ll) {
	copy(ll);
}

template<class DT>
LinkedList<DT>::~LinkedList() {
	if (_info != NULL) {
		delete _info;
		_info = NULL;
	}

	if (_next != NULL) {
		delete _next;
		_next = NULL;
	}
}

template <class DT>
void LinkedList<DT>::operator=(const LinkedList<DT>& ll) {
	if (_info != NULL) {
		delete _info;
	}

	if (_next != NULL) {
		delete _next;
	}

	copy(ll);
}

template <class DT>
bool LinkedList<DT>::isEmpty() {
	return (_info == NULL);
}

template <class DT>
DT& LinkedList<DT>::infoAt(int pos) {
	if (this->isEmpty()) {
		throw LinkedListBounds();
	}
	if (pos == 0) {
		return *_info;
	}
	if (_next == NULL) {
		throw LinkedListBounds();
	}
	else {
		return _next->infoAt(pos - 1);
	}
}

template <class DT>
DT& LinkedList<DT>::operator[] (int pos) {
	return infoAt(pos);
}

template <class DT>
void LinkedList<DT>::add(const DT& Obj) {
	if (_info == NULL) {
		_info = new DT(Obj);
	}

	else {
		LinkedList<DT> *List = new LinkedList<DT>(*_info, _next);
		if (List == NULL) {
			throw LinkedListMemory();
		}

		*_info = Obj;
		_next = List;
	}
}
template <class DT>
void LinkedList<DT>::insertAt(const DT& newObj, int pos) {
	if (pos == 0) {
		add(newObj);
	}

	else {
		if (_next == NULL) {
			_next = new LinkedList(newObj);
			if (_next == NULL) {
				throw LinkedListMemory();
			}
		}

		else {
			_next->insertAt(newObj, pos - 1);
		}
	}
}

template <class DT>
DT LinkedList<DT>::remove() {
	if (isEmpty()) {
		throw LinkedListBounds();
	}

	DT temp = *_info;
	delete _info;

	if (_next == NULL) {
		_info = NULL;
	}

	else {
		LinkedList<DT>* end = _next;
		_info = _next->_info;
		_next = _next->_next;
		end->_info = NULL;
		end->_next = NULL;

		delete end;
	}

	return temp;
}
template <class DT>
DT LinkedList<DT>::removeAt(int pos) {
	if (isEmpty()) {
		throw LinkedListBounds();
	}
	if (pos == 0) {
		return remove();
	}

	if (_next == NULL) {
		throw LinkedListBounds();
	}

	return _next->removeAt(pos - 1);
}

template <class DT>
int LinkedList<DT>::size() {
	if (_next == NULL) {
		if (_info == NULL) {
			return 0;
		}

		else {
			return 1;
		}
	}
	else {
		return (1 + _next->size());
	}
}

template <class DT>
LinkedList<DT>* LinkedList<DT>::next() {
	return _next;
}

template <class DT>
void LinkedList<DT>::setNext(LinkedList<DT>* next) {
	if (isEmpty()) {
		throw LinkedListAttachToEmpty();
	}
	_next = next;
}
Term::Term() {
	coefficient = NULL;
	exponent = NULL;
}

Term::Term(int coeff, int expo) {
	coefficient = coeff;
	exponent = expo;
}

Term::~Term() {

}

void Term::copy(const Term& t) {
	coefficient = t.coefficient;
	exponent = t.exponent;
}

Term::Term(const Term& t) {
	copy(t);
}

void Term::operator=(const Term& t) {
	copy(t);
}

void Term::display(ostream& output) {
	output << "(" << coefficient << "," << exponent << ")";
}
ostream& operator<<(ostream& output, Term& t) {
	t.display(output);

	return output;
}
int Term::getCoefficient() {
	return coefficient;
}

void Term::Coeff(int val) {
	coefficient = val;
}

void Term::Exp(int val) {
	exponent = val;
}
int Term::getExponent() {
	return exponent;
}

template <class DT>
Polynomial<DT>::Polynomial() {
	myPoly = new LinkedList<Term>();
}

template <class DT>
Polynomial<DT>::Polynomial(int size) {
	myPoly = new LinkedList<Term>();

	for (int i = 0; i < size; i++) {
		//Set the specified size with 0,0 terms
		myPoly->add(*new Term(0, 0));
	}
}

template <class DT>
Polynomial<DT>::~Polynomial() {
	
}

template <class DT>
bool Polynomial<DT>::addTerm(int coefficient, int exponent) {

	//Check if term with same exponent exists in the polynomial
	int newCoeff;
	int index;
	bool dup = false;
	for (int i = 0; i < myPoly->size(); i++) {
		//If true, record the sum of coefficient and the index
		if (exponent == (*myPoly)[i].getExponent()) {
			dup = true;
			newCoeff = (*myPoly)[i].getCoefficient() + coefficient;
			index = i;
		}
	}
	//Add new term at the beginning if the poly is empty
	if (myPoly->isEmpty()) {
		myPoly->add(*new Term(coefficient, exponent));
	}
	else if (dup == true) {
		//Replace the term if duplicate is found
		myPoly->infoAt(index) = *new Term(newCoeff, exponent);
	}
	else {
		//myPoly->insertAt(*(new Term(coefficient, exponent)), myPoly->size());
		myPoly->add(*new Term(coefficient, exponent));
	}


	return dup;

}

template <class DT>
bool Polynomial<DT>::deleteTerm(int exponent) {
	//Loop through the linked list to find matching exponent
	//Then set the coeff of the term to 0

	bool found = false;
	for (int i = 0; i < myPoly->size(); i++) {
		if ((*myPoly)[i].getExponent() == exponent) {
			myPoly->infoAt(i) = *new Term(0, exponent);
			found = true;
		}
	}

	return found;
}

template <class DT>
DT Polynomial<DT>::evaluatePoly(DT x) {
	int result = 0;
	//Loop through the polynomial to calculate sum of each term evaluated
	for (int i = 0; i < myPoly->size(); i++) {
		result = result + ((*myPoly)[i].getCoefficient() * pow(x, (*myPoly)[i].getExponent()));
	}

	return result;
}

template <class DT>
Polynomial<DT> Polynomial<DT>::addPolynomial(Polynomial x) {

	Polynomial* sum = new Polynomial();

	LinkedList<Term>* poly1;
	LinkedList<Term>* poly2;

	poly1 = myPoly;
	poly2 = x.myPoly;

	//Loop through each polynomial to add individual term to sum
	while (poly1 != NULL) {
		int coeff, expo;
		coeff = poly1->infoAt(0).getCoefficient();
		expo = poly1->infoAt(0).getExponent();

		sum->addTerm(coeff, expo);

		poly1 = poly1->next();
	}

	//the addTerm automatically adds term with same exponent
	while (poly2 != NULL) {
		int co2, ex2;
		co2 = poly2->infoAt(0).getCoefficient();
		ex2 = poly2->infoAt(0).getExponent();

		sum->addTerm(co2, ex2);

		poly2 = poly2->next();
	}

	return *sum;


}

template <class DT>
Polynomial<DT> Polynomial<DT>::operator+ (Polynomial x) {
	return addPolynomial(x);
}
template <class DT>
Polynomial<DT> Polynomial<DT>::multiplyPolynomial(Polynomial x) {
	//This method effectively FOILS the two polynomials
	Polynomial* mult = new Polynomial();
	LinkedList<Term>* poly1;
	LinkedList<Term>* poly2;

	poly1 = myPoly;
	poly2 = x.myPoly;

	//Loop through the first polynomial
	while (poly1 != NULL) {
		//Within the loop, loop through the second
		while (poly2 != NULL) {
			int coeff, expo;

			//Multiply the coefficient of the first and second
			coeff = poly1->infoAt(0).getCoefficient() * poly2->infoAt(0).getCoefficient();
			//Then add the exponents to multiply them
			expo = poly1->infoAt(0).getExponent() + (poly2->infoAt(0).getExponent());
			//Add these term to the multiple
			mult->addTerm(coeff, expo);

			//Set the secondll to its next pointer
			poly2 = poly2->next();

		}

		//Return the second ll of terms to its original position
		poly2 = x.myPoly;
		//Set the first ll to the next term to iterate through
		poly1 = poly1->next();

	}
	return *mult;
}

template <class DT>
Polynomial<DT> Polynomial<DT>::operator* (Polynomial x) {
	return multiplyPolynomial(x);
}

template <class DT>
void Polynomial<DT>::display(ostream& output) {
	sort();
	//Make a temporary linked list to preserve the original ll
	LinkedList<Term>* temp;
	temp = myPoly; //Set it equal to the original
	while (temp != NULL) {
		if (temp->infoAt(0).getCoefficient() != 0) { //don't print out the 0 value
			if (temp->next() != NULL && temp->infoAt(1).getCoefficient() != 0) { //print a plus sign if there's a next value
				output << temp->infoAt(0) << " + ";
			}
			else {
				output << temp->infoAt(0);
			}

		}
		temp = temp->next();


	}

}

template <class DT>
void Polynomial<DT>::sort() {
	//Stop if the ll is empty or has only one element in it
	if (myPoly == NULL || myPoly->next() == NULL) {
		return;
	}

	//Copy the ll
	LinkedList<Term>* test = myPoly->next();

	//Iterate through the ll to compare each values in ll
	//then swaps the values (info) if the next term is greater than the previous
	//until no more values are found
	while (test != NULL) {
		Term data = test->infoAt(0);
		bool found = false;
		LinkedList<Term>* test2 = myPoly;
		while (test2 != test) {
			if (test2->infoAt(0).getExponent() < test->infoAt(0).getExponent() && !found) {
				data = test2->infoAt(0);
				test2->infoAt(0) = test->infoAt(0);
				found = true;
				test2 = test2->next();
			}
			else {
				if (found) {
					Term temp = data;
					data = test2->infoAt(0);
					test2->infoAt(0) = temp;
				}
				test2 = test2->next();
			}
		}

		//Return to original info
		test2->infoAt(0) = data;
		//Set the pointer to next
		test = test->next();

	}

}

int main() {

	// Create an array of polynomial
	Polynomial<int>* Polynomials = new Polynomial<int>[10];
	char command;
	int polynum, coefficient, exponent, value;
	int i, j;

	cin >> command;
	while (!cin.eof()) {
		switch (command) {
		case 'I': cin >> polynum >> coefficient >> exponent;
			if (!Polynomials[polynum].addTerm(coefficient, exponent)) {
				cout << "Term added successfully" << endl;
			}
			else {
				cout << "Term with exponent " << exponent << " exists in polynomial "
					<< polynum << ", add " << coefficient << " to the existing coefficient" << endl;
			}
			break;
		case 'D': cin >> polynum >> exponent;
			if (!Polynomials[polynum].deleteTerm(exponent)) {
				cout << "There is no term in polynomial " << polynum << " with an exponent of "
					<< exponent << endl;
			}
			else {
				cout << "Deleted term successfully" << endl;
			}
			break;
		case 'A': cin >> i >> j; cout << Polynomials[i] + Polynomials[j] << endl; break;
		case 'M': cin >> i >> j; cout << Polynomials[i] * Polynomials[j] << endl; break;
		case 'E': cin >> polynum >> value;
			cout << Polynomials[polynum].evaluatePoly(value) << endl;
			break;
		case 'P': cin >> polynum;
			cout << "Polynomial " << polynum << ": " << Polynomials[polynum];
			break;

		default: cout << "Missing" << endl;
		}
		cin >> command;
	}

	delete[] Polynomials;
}


