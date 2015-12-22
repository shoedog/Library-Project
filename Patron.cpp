
#include "Patron.h"
#include "Book.h"

//Constructor for Default Patron with no arguments
Patron::Patron()
{}

/******************************************************************************
 *														Constructor for Patron
 *	Entry: Takes a string idn representing an Id number and a string n 
 *				representing a name
 *
 *	Exit: Sets private class variables idNum and name equal to idn and n. 
 *				Sets fineAmount to 0. Reserves 100 spaces for checked out books in
 *				the vector.
 *
 *	Purpose: Create a Patron object
 * ***************************************************************************/
Patron::Patron(std::string idn, std::string n)
{
	idNum = idn;
	name = n;
	fineAmount = 0;
	checkedOutBooks.reserve(100);
}

//Accessor for IdNum
std::string Patron::getIdNum()
{	return idNum; }

//Accessor for Name
std::string Patron::getName()
{ return name; }

//Accessor for vector of checked out Books
std::vector<Book*> Patron::getCheckedOutBooks()
{ return checkedOutBooks; }

//Mutator that adds a Book b to the checked out books vector    
void Patron::addBook(Book* b)
{  checkedOutBooks.push_back(b); }
 
//Mutator that removes a Book b from the checked out books vector   
void Patron::removeBook(Book* b)
{ 
	for( int i = 0; i < checkedOutBooks.size(); i++ )
	{
		if( b->getIdCode() == checkedOutBooks[i]->getIdCode() )
			checkedOutBooks.erase( checkedOutBooks.begin() + i );
	}
}

//Accessor to get the fineAmount of a patron   
double Patron::getFineAmount()
{ return fineAmount; }

//Mutator to adjust the fine amount for a patron by amount. A positive value 
//  increases is, and a negative one decreases it    
void Patron::amendFine(double amount)
{ fineAmount += amount; }
