// Hassan Mehdi
// 11/08/2016

/* Description: A class containing functions and operators 
which allow a user to create linked lists of polynomials, 
add them, multiply them, differentiate them , and integrate them*/

#ifndef
#include<iostream>
#include <iomanip>
#include <ostream>
using namespace std;

struct TermNode {
	int exp;
	double coef;
	TermNode* next;
};

class PolyType {
public:
	PolyType() // empty constructor			//Preconditions: there must not be a polynomial with the same name already made
	{ polyPtr = nullptr; }					//Postconditions: A new empty polynomial of PolyType is created 

	PolyType(double r, int c) { // constructor makes a 1 node polynomial
		polyPtr = new TermNode;
		polyPtr->coef = r;				//PreConditions: there must not be a polynomial with the same name already made
		polyPtr->exp = c;				// A new polynomial node of PolyType is created with coefficient 'r' and exponent 'c'
		polyPtr->next = nullptr;
	};


	PolyType(PolyType& rhs) {// copy constructor
		TermNode* TrackRHS = rhs.polyPtr;
		polyPtr = new TermNode;
		TermNode* TrackNL = polyPtr;
		while (TrackRHS != nullptr) {				//Precondition:The polynomial that is called must already exist.
		TrackNL->exp = TrackRHS->exp;				//	Postcondition: A deep copy of the PolyType polynomial will be created
		TrackNL->coef = TrackRHS->coef;									
		if (TrackRHS->next != nullptr) {
			TrackNL->next = new TermNode;
			} else { TrackNL->next = nullptr; }
			TrackNL = TrackNL->next;
			TrackRHS = TrackRHS->next;
		}
	}
	
	~PolyType() { // destructor
		TermNode* trailer = polyPtr;				// Precondition: Object being destroyed must already exist
		TermNode* walker = polyPtr->next;			// Postcondition: Object is destroyed

		while (walker != nullptr) {
			delete trailer;
			trailer = walker;
			walker = walker->next;
		}
	}
	

	PolyType operator = (const PolyType & rhs) { //assignment
		TermNode* OldPtr = rhs.polyPtr;
		TermNode* NewList = new TermNode;
		TermNode* TrackNL = NewList;			// Precondition: Object being copied must have one or more nodes
		while (OldPtr != nullptr) {				// Postconditions: Creates a new object which is a deep copy of the old one

			TrackNL->exp = OldPtr->exp;
			TrackNL->coef = OldPtr->coef;
			TrackNL->next = nullptr;
			TrackNL = TrackNL->next;
			OldPtr = OldPtr->next;
		}
		this->polyPtr = NewList;
		this->polyPtr->next = nullptr;
		return *this;
	};

	PolyType operator + (PolyType rhs) { // return sum of parameter + self
		this->ReorderList();
		rhs.ReorderList();

		TermNode* walkerLHS = this->polyPtr;		// Precondition: two objects of polynomials. with a nullptr signifying their ending
		while (this->polyPtr->next != nullptr) {	// Postcondition: adds the coefficients of nodes whose exponents are equal, 
			walkerLHS = this->polyPtr->next;		//	and reroutes the linked list to expel all but one of the nodes with the same exponent,
		}											// ultimately adding the value of the two objects into one object

		walkerLHS->next = new TermNode;
		walkerLHS->next = rhs.polyPtr;
		this->ReorderList();

		TermNode* w1 = this->polyPtr;

		while (w1 != nullptr) {
			if (w1->next != nullptr && w1->exp == w1->next->exp) {
				w1->coef = w1->coef + w1->next->coef;
				w1->next = w1->next->next;
			}
			w1 = w1->next;
		}
		return *this;
	}


	PolyType operator * ( PolyType & rhs) {
		this->ReorderList();
		rhs.ReorderList();

		TermNode* LHS = this->polyPtr;
		TermNode* RHS = rhs.polyPtr;

		PolyType Product;
		Product.polyPtr = new TermNode;							// Preconditions: two objects of polynomials which are to be multiplied
		TermNode* newlist = Product.polyPtr;					// Postconditions: a single object returned with the product of the previous two objects 
		while (LHS != nullptr) {
			while (RHS != nullptr) {
				newlist->coef = LHS->coef * RHS->coef;
				newlist->exp = LHS->exp + RHS->exp;
				newlist->next = new TermNode;
				RHS = RHS->next;
				newlist = newlist->next;
			}
			LHS = LHS->next;
			RHS = rhs.polyPtr;
		}
		newlist->next = nullptr;
		Product.ReorderList();
		return Product;
	}

	
	PolyType differ() { // differentiation
		TermNode* walker = this->polyPtr;
		while (walker != nullptr) {						// Preconditions: an object of PolyType with one or more polynomials
			walker->coef = walker->coef * walker->exp;	// Postconditions: an object of PolyType with each polynomial differentiated
			walker->exp = walker->exp - 1;
			walker = walker->next;
		}
		return *this;
	}
	
	PolyType integr() {		// integration (with 0 as constant)
		TermNode* walker = this->polyPtr;
		while (walker != nullptr) {									// Preconditions: an object of PolyType with one or more polynomials
			walker->coef = walker->coef / (walker->exp + 1);		// Postconditions: an object of PolyType with each polynomial differentiated
			walker->exp = walker->exp + 1;
			walker = walker->next;
		}
		return *this;
	}

	void ReorderList() {							// Preconditions: A linked list of polynomials with at least two nodes with different exponent values
		TermNode* walker1 = new TermNode;			// Postcondions: An object of polynomials sorted by the size of their exponent from largest to smallest
		walker1 = polyPtr;
		TermNode* walker2 = new TermNode;
		walker2 = polyPtr->next;

		while (walker1 != nullptr) {
			while (walker2 != nullptr) {
				if (walker2->exp > walker1->exp) {
					SwapNodeVals(walker1, walker2);
				}
				walker2 = walker2->next;
			}

			walker1 = walker1->next;
			if (walker1 == nullptr) {}
			else { walker2 = walker1->next;}
		}
	}

	void SwapNodeVals(TermNode*& Node1, TermNode*& Node2) {
		TermNode* temp1 = new TermNode;
		TermNode* temp2 = new TermNode;				// Preconditions: two nodes within an object
													// Postconditions: if the node further down the linked list has a larger exponent 
		temp1->coef = Node1->coef;					//		than the node closer to the top, the two nodes switch values
		temp1->exp = Node1->exp;
		temp2->coef = Node2->coef;
		temp2->exp = Node2->exp;

		Node2->coef = temp1->coef;
		Node2->exp = temp1->exp;
		Node1->coef = temp2->coef;
		Node1->exp = temp2->exp;
	}

	friend ostream & operator << (ostream & out, const PolyType & rhs) { // coefficients printed to 2 decimal places
		TermNode* walker = rhs.polyPtr;
		while (walker->next != nullptr) {
			out << walker->coef << "x^" << walker->exp << " + ";		// Preconditions: object of PolyType has atleast one node
			walker = walker->next;										// Postconditions: polynomial equation is displayed on the screen
		}
		if (walker->next == nullptr) {
			out << walker->coef << "x^" << walker->exp;
		}
		return out;
	};

private:
	TermNode  *polyPtr;
};

#endif
