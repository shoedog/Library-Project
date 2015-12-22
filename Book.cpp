
#include "Book.h"
#include "Patron.h"

Book::Book()
{}

/******************************************************************************
 *												Book Constructor
 *		Entry: String idc represents and IdCode, String t represents a title, 
 *					string a represents an author
 *						
 *		Exit: Sets Book IdCode, title, and author equal to the strings that
 *				are passed to the function. Sets checkedOutBy and requestedBy to 
 *				NULL, sets location to ON_SHELF
 *
 *		Purpose: Creates a Book object
 *
 * ***************************************************************************/
Book::Book(std::string idc, std::string t, std::string a)
{
	idCode = idc;
	title = t;
	author = a;
	checkedOutBy = NULL;
	requestedBy = NULL;
	location = ON_SHELF;
}
    
//Accessor for IdCode
std::string Book::getIdCode()
{ return idCode; }

//Accessor for title
std::string Book::getTitle()
{ return title; }

//Accessor for author
std::string Book::getAuthor()
{ return author; }

//Accessor for location
Locale Book::getLocation()
{ return location; }

//Mutator for Location.
// Entry: lo is a Locale
// Exit: sets location equal to location
void Book::setLocation(Locale lo)
{ location = lo; }

//Accessor for Patron that checked out Book
Patron* Book::getCheckedOutBy()
{ return checkedOutBy; }

//Mutator for Patron to check out book
//Entry: A pointer to a Patron *p
//Exit: Sets checkedOutBy equal to p
void Book::setCheckedOutBy(Patron* p)    
{ checkedOutBy = p; }

//Accessor for Patron that requested a Book
Patron* Book::getRequestedBy()
{ return requestedBy; }

//Mutator for Patron to request book
//Entry: Pointer to a patron *p
//Exit: sets requestedBy equal to p
void Book::setRequestedBy(Patron* p)
{ requestedBy = p; }

//Accessor for the Date that the book was checked out
int Book::getDateCheckedOut()
{ return dateCheckedOut; }

//Mutator to set dateCheckedOut for the date that the book was checked out to
//an integer d that is passed to the function
void Book::setDateCheckedOut(int d)
{ dateCheckedOut = d; }









