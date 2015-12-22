#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Patron.h"
#include "Book.h"
#include "Library.h"

//Constructor for Library Object. Sets currentDate to 0. Reserves 100 memory
//   locations for holdings and members vectors respectively
Library::Library()
{
	currentDate = 0;
	holdings.reserve(100);
	members.reserve(100);
}

/******************************************************************************
 *												addBook()
 *		Entry: none
 *
 *		Exit: Takes input for an idCode, title, and author. Creates a Book
 *			object, and adds that object to the holdings vector.
 *
 *		Purpose: To get user input for a Book object and add it to the holdings
 *						vector. 
 *
 * ***************************************************************************/
void Library::addBook()
{
	std::string idCode; //Book idCode
	std::string title;  //Book title
	std::string author; //Book author

	//Prompt for and get input for Book ID
	std::cout << "Enter Book Information. " << std::endl
					  << "What is the idCode? ";
	std::cin.ignore();
	std::getline( std::cin, idCode );

	//Checks to see if ID Code is already in use. If so prints message and returns
	//  to the menu
	for( int i = 0; i < holdings.size(); i++ )
	{
		if( holdings[i].getIdCode() == idCode )
		{
			std::cout << "That ID Code is already taken. Returning to the menu. "
							  << std::endl;
			return;	
		}
	}

	//Prompts for and gets input for title
	std::cout << "What is the Title? ";
	std::getline( std::cin, title );

	//Prompts for and gets input for Author
	std::cout << "Who is the Author? ";
	std::getline( std::cin, author );

	//Creates Book Objects by passing idCode, title, and author
	//  Adds Book object to holdings vector
	holdings.push_back( Book( idCode, title, author ) );
}

/******************************************************************************
 *												addMember()
 *		Entry: none
 *
 *		Exit: Takes input for an idNum and name. Creates a Patron
 *			object, and adds that object to the members vector.
 *
 *		Purpose: To get user input for a Patron object and add it to the members
 *						vector. 
 ******************************************************************************/
void Library::addMember()
{
	std::string idNum;  //Represents a Patron id Number
	std::string name;   //Represents a Patron name

	//Prompt for and get user input for Patron ID number
	std::cout << "Enter Patron Information. " << std::endl
					  << "What is the id Number? ";
	std::cin.ignore();	
	std::getline( std::cin, idNum );
	
	//Loops over members of library. If ID number is already in use prints a 
	//   message and returns to the menu.
	for( int i = 0; i < members.size(); i++ )
	{
		if( members[i].getIdNum() == idNum )
		{
			std::cout << "That ID is already taken. Returning to the menu. "
							  << std::endl;
			return;	
		}
	}

	//Prompts for and gets input for Patron name
	std::cout << "What is the Patron's Name? ";
	std::getline( std::cin, name );

	
	Patron newPatron( idNum, name);  //Creates Patron object with idNum and name
	members.push_back( newPatron );  //Adds Patron to members vector
}

/******************************************************************************
 *												checkOutBook( string patronID, string bookID )
 *		Entry: Takes string representing a patron id, and a string representing
 *					a book id
 *
 *		Exit: Creates pointer to patron represented by patronID and pointer to
 *		   book represented by bookID. Validates that both ID's are in the 
 *		   system, and if not returns to menu. If book is already checked out
 *		   prints a message and returns to the menu. If book is on hold for 
 *		   another patron print a message and return to the menu. If book is able
 *		   to be checked out, books checkedOutBy(), dateCheckedOut(), and 
 *		   location are updated; and the Patron's vector of checked out books
 *		   is updated. A message is printed saying that the book has been checked
 *		   out by the patron.
 *
 *		Purpose: To check out a book for a patron.
 ******************************************************************************/
void Library::checkOutBook(std::string patronID, std::string bookID)
{
	Patron *patronP;  //Pointer to patron that wants to check out book
	Book *bookB;     //Pointer to book to check out
	bool patronTest = 0; //Tests if patron is in the system
	bool bookTest = 0;   //Tests if book is in the system

	//Sets the patronP pointer to the element of members vector that has a
	//matching ID, if there is a match set patronTest to true
	for( int p = 0; p < members.size(); p++ )
	{
		if( patronID == members[p].getIdNum() )
		{
			patronP = &members[p];
			patronTest = 1;
		}
	}

	//Sets the bookB pointer to the element of the holdings vector that has a
	//matching ID, there is a match set bookTest to true
	for( int b = 0; b < holdings.size(); b++ )
	{
		if(  bookID == holdings[b].getIdCode() )
		{
			bookB = &holdings[b];
			bookTest = 1;
		}
	}
	
	//Checks if the Book ID and Patron ID are in the system. If not
	// prints a message and returns to the menu. 
	if( patronTest == 0 )
	{
		std::cout << "That patron ID: " << patronID << " is not in the system. "
						  << "Returning to the menu. " << std::endl;
		return;
	}
	else if( bookTest == 0 )
	{
		std::cout << "That book ID: " << bookID << " is not in the system. "
						  << "Returning to the menu. " << std::endl;
		return;
	}

	//If the book is already checked out, print a message and return to the menu
	if( bookB->getLocation() == CHECKED_OUT )
	{
		std::cout << "That book is already checked out. Returning to the menu. "
						  << std::endl;
		return;
	}	

	//If the book is on hold by another patron, print that message and
	//  return to the menu
	//Else IF the book is on hold for the Patron, change requested by to NULL
	// because the requesting Patron is checking the book out
	if( bookB->getLocation() == ON_HOLD )
	{
		if( bookB->getRequestedBy() != patronP )
		{
			std::cout << "That book is on hold for another patron. Returning "
							  << "to the menu. " << std::endl;
			return;
		}
		else if( bookB->getRequestedBy() == patronP )
		{
			bookB->setRequestedBy( NULL );
		}
	}

	bookB->setCheckedOutBy( patronP ); //Update books checked out by patron
	bookB->setDateCheckedOut( currentDate ); //Update books checked out date
	bookB->setLocation( CHECKED_OUT ); //Update books location
	patronP->addBook( bookB );  //Add book to Patrons checked out book vector
	
	//Print that the Book: title has been checked out by Patron: name
	std::cout << bookB->getTitle() << " has been checked out to "
					  << patronP->getName() << "." << std::endl;
}
    
/******************************************************************************
 *												returnBook( string bookID )
 *		Entry: Takes a string representing a book ID
 *
 *		Exit: Tests to see if the Book ID is in the system. If not prints a
 *				message and returns to the menu. Tests if the Book is checked out.
 *				If it is not checked out, prints an error message and returns to the
 *				menu. Otherwise, removes the book from the patrons' checked out book
 *				vector, changes the Book's checkedOutBy() to NULL, changes the Book's
 *				location to either ON_HOLD or ON_SHELF dependent on if a Patron has
 *				requested it, and prints a message that is has been returned.  
 *
 *		Purpose: To return a book to the library and update its information,
 *				and the Patron's information.
 ******************************************************************************/
void Library::returnBook(std::string bookID)
{
	Patron *patronPerson;  //Pointer to a Patron
	Book *returnedBook;    //Pointer to a book
	bool bookExist = 0;    //Is the book in the system? Default to false

	//Loop over the holdings vector. If the bookID matches an ID for a book in the
	//  vector then set returnedBook pointer equal to the address of that book. 
	//  If match then change bookExist to true.
	for( int i = 0; i < holdings.size(); i++ )
	{
		if( holdings[i].getIdCode() == bookID )
		{
			returnedBook = &holdings[i];
			bookExist = 1;
		}
	}

	//If the Book ID isn't in the library, print a message tell the user and
	//  return to the menu.
	if( bookExist = 0 )
	{
			std::cout << "That Book is not recorded in the library. " 
							<< "Returning to the menu." << std::endl;
		return;
	}

	//If the book is not checked out, print a message and return to menu
	if( returnedBook->getLocation() != CHECKED_OUT )
	{
		std::cout << "That book is not recorded as having been checked out. "
							<< "Returning to menu. " << std::endl;
		return;
	}
	else
	{
		//Get the Patron that checked out the Book
		patronPerson = returnedBook->getCheckedOutBy();
 
		//Update the Patron's List by removing Book
		patronPerson->removeBook( returnedBook );

		//Update checkedOutBy Person of Book to NULL
		returnedBook->setCheckedOutBy( NULL );

		//Update the Books Location to either Hold or Shelf
		if( returnedBook->getRequestedBy() != NULL )
			returnedBook->setLocation( ON_HOLD );
		else
		{
			returnedBook->setLocation( ON_SHELF );
			returnedBook->setRequestedBy( NULL );		 
		}
	}	
	
	//Print that the Book has been returned
	std::cout << returnedBook->getTitle() << " has been returned. "
						<< std::endl;
}

/******************************************************************************
 *										requestBook( string patronID, string bookID )
 *	Entry: Takes a string representing a Patron's ID and a string representing
 *		a Book's ID
 *
 *	Exit: Tests if the Book and the Patron are in the system, and if not prints
 *	  a message and returns to the menu. If the book is not requested by a
 *	  Patron then Book is requested by Patron. If Book is located on the shelf
 *	  then it is moved to on hold. If book is already requested by another 
 *	  Patron then a message is printed as such and the function returns to the
 *	  menu.
 *
 *	Purpose: To place a book on hold and request a book that is checked out. 
 *
 * ***************************************************************************/   
void Library::requestBook(std::string patronID, std::string bookID)
{
	Patron *holdFor;  //Pointer to Patron that Book is being held for
	Book *heldBook;  //Point to Book being held
	bool patronIdMatch = 0; //Bool to test patronID
	bool bookIdMatch = 0;  //Bool to test bookID

	//Loops over members and holdings. If an Patron ID in members matches patronID
	//  patronIdMatch is set to true and holdFor is set to that Patron's memory 
	//  address. If Book ID in holdings matches bookID, bookIdMatch is set to true
	//  and heldBook is set to the memory address of the book.
	for( int i = 0; i < members.size(); i++ )
	{
		for( int j = 0; j < holdings.size(); j++ )
		{
			if( members[i].getIdNum() == patronID )
			{
				patronIdMatch = 1;
				holdFor = &members[i];
			}
			
			if( holdings[j].getIdCode() == bookID )
			{
				bookIdMatch = 1;
				heldBook = &holdings[j];
			}
		}
	}

  //Print Book is not in Library system and return to menu	
	if( bookIdMatch == 0 )
	{
		std::cout << "Your Book ID Code: " << bookID 
							<< " does not match a code in our system. Returning to menu. "
							<< std::endl;	
		return;
	}
	else if( patronIdMatch == 0 ) //Print Patron not in Library & return to menu	
	{
		std::cout << "Your patron ID Number: " << patronID
							<< " does not match a code in our system. Returning to menu. "
							<< std::endl;	
		return;
	}

	//If book is not on hold for a patron
	if( heldBook->getRequestedBy() == NULL )
	{ 
		//update book location to on_hold if on on_shelf
		if( heldBook->getLocation() == ON_SHELF ) 
		{	
			heldBook->setLocation( ON_HOLD );
		}

		//update requested by to requesting Patron
		heldBook->setRequestedBy( holdFor );
 
		//print that Book title is on hold for patron name
		std::cout << heldBook->getTitle() << " is on hold for "
							<<  holdFor->getName() << ". " << std::endl;
		return;
	}
	else //Book is requestedBy a Patron
	{
		//Print Book is requested by another patron and return to menu
		holdFor = heldBook->getRequestedBy();
		std::cout << heldBook->getTitle() << " is already reserved for "
						<< holdFor->getName() << ". " << std::endl;
		return;
	}
}

/******************************************************************************
 *											incrementCurrentDate()
 *	Entry: None
 *	
 *	Exit: increments the current date by 1. Loops over all members of the
 *		library, and their checked out books. If any are overdue, adds a daily
 *		fine to their fine total. 
 *
 *	Purpose: To increase the date and update fines for members based on 
 *		overdue books. 
 *
 * ***************************************************************************/    
void Library::incrementCurrentDate()
{
	std::vector<Book*> checkedOut;
	int daysOut;

	currentDate++;
	std::cout << "Date is: " << currentDate << ". " << std::endl;
	
	//Loop over all members of the library
	for( int p = 0; p < members.size(); p++ )
	{
	  //Assign a Vector of checked out Books for each member
		checkedOut = members[p].getCheckedOutBooks(); 
		
	  if( !checkedOut.empty()  )
		{
			//Loop over all checked out Books. Find how many daysOut the book has been
			//  checked out. If the book has been checked out Longer than the allowed
			//  CHECK_OUT_LENGTH, then add the DAILY_FINE to the members fine amount
			for( int b = 0; b < checkedOut.size(); b++ )
			{
				 daysOut = checkedOut[b]->getDateCheckedOut();
				 daysOut = currentDate - daysOut;
			 
				 if( daysOut > Book::CHECK_OUT_LENGTH )
					 members[p].amendFine( DAILY_FINE );
			}
		}
	}
}
 
/******************************************************************************
 *												payFine( string patronID, double payment )
 *	Entry: Takes a string representing a patron ID and a double representing 
 *		a payment.
 *
 *	Exit: Tests if Patron is in the system. If not, prints a message and 
 *		returns to the menu. If so, updates the amount of their fine total by
 *		the payment and prints out their remaining balance.
 *
 *	Purpose: To take payments on fines and update the fine total for a Patron	 
 *
 * ***************************************************************************/   
void Library::payFine(std::string patronID, double payment)
{
	Patron *patronP;  //Represents the patron paying the fine
	bool foundPatron = 0; //Tests if patron is in the system

	//Loop over members of library looking for a Patron ID that matches the 
	//  ID passed as an argument to payFine(). If one matches set pointer
	//  equal to it and set foundPatron to True
	for( int p = 0; p < members.size(); p++ )
	{
		if( patronID == members[p].getIdNum() )
		{
			patronP = &members[p];
			foundPatron = 1;
		}
	}

  //If foundPatron is false then there is no Patron with that ID in the library.
  //Print a message and return to the menu
	if( foundPatron == 0 )
	{
		std::cout << "Patron: " << patronID << " is not in the system. Returning "
						  << "to the menu. " << std::endl;
		return;
	}

	//Adjust the fines for the Patron based on their payment.
  patronP->amendFine( payment );
	
	//Print the Patrons Balance
	std::cout << "Fines for " << patronP->getName() << " are now "
					  << patronP->getFineAmount() << ". " << std::endl;
}

/******************************************************************************
 *									viewPatronInfo( string PatronID )
 *	Entry: none
 *
 *	Exit: If patron is not in the system, prints a message and returns to the
 *		menu. Otherwise prints Patrons id number, name, any checked out books,
 *		and any fines.
 *
 *	Purpose: To print information on a patron
 *
 * ***************************************************************************/    
void Library::viewPatronInfo(std::string patronID)
{ 
	std::vector<Book*> checkedOut;
	Patron *patronInfo;
	bool patronFound = 0;

	//Tests if there are members of the library. Prints a message and returns to
	//the menu if there are no members
	if( members.empty() )
	{
			std::cout << "Patron Id: " << patronID << " is not in the Library.";
			return;
	}

	//Loops over members of the library to find a matching ID number to patronID
	// If there is a matching IdNum then set patronInfo to that members memory
	// location and set patronFound to True.
	for( int i = 0; i < members.size(); i++ )
	{
		if( members[i].getIdNum() == patronID )
		{	
			patronInfo = &members[i];
			patronFound = 1;
		}
  }	
	
	//If patronFound is false, print a message and return to the menu.
	if( patronFound == 0 )	
	{
			std::cout << "Patron ID is not in the Library System." << std::endl;
			return;
	}
	
	//Get vector for checked out books for the patron	
	checkedOut = patronInfo->getCheckedOutBooks();

	//Print Id Number and Name of Patron
	std::cout << std::endl << "Patron Information: " << std::endl;
	std::cout << "  ID Number: " << patronInfo->getIdNum() << std::endl
				    << "  Name: " << patronInfo->getName() << std::endl;

	//Prints Checked out Books or that no Books are checked out
	if( checkedOut.size() != 0 )
	{
		std::cout << "  Checked out books: " << std::endl;
		for( int j = 0; j < checkedOut.size(); j++ )
			std::cout << "    Title: " << checkedOut[j]->getTitle() <<	std::endl; 
	}
	else
		std::cout << "  No books currently checked out. " << std::endl;

	//Prints fines for patron
	std::cout	<< "  Fines: " << patronInfo->getFineAmount() << std::endl;
}
    
/******************************************************************************
 *									viewBookInfo( string BookID )
 *	Entry: none
 *
 *	Exit: If book is not in the system, prints a message and returns to the
 *		menu. Otherwise prints Books id number, title, author, location, if
 *		it is requested by anyone, and if it is checked out by anyone as well
 *		as the date checked out.
 *
 *	Purpose: To print information on a Book.
 *****************************************************************************/
void Library::viewBookInfo(std::string bookID)
{
	Patron *patronPerson; //Represents a pointer to a patron
	Book *bookItem;      //Represents a point to a Book
	bool bookFound = 0;  //Tests if the bookID is in the system

	//If the holdings vector is empty print a message and return to the menu
	if( holdings.empty() )
	{
			std::cout << "Book Id: " << bookID << " is not in the Library.";
			return;
	}

	//If a Book from holdings has its IdCode matching the bookID then have
	//   bookItem equal that Book's memory location and set bookFound to true
	for( int i = 0; i < holdings.size(); i++ )
	{
		if( holdings[i].getIdCode() == bookID)
		{
			bookItem = &holdings[i];
			bookFound = 1;
		}
	}
	
	//If the book is not in the system, print a message and return to the menu
	if( bookFound == 0 )
	{
			std::cout << "Book Id: " << bookID << " is not in the Library.";
			return;
	}

	//Print Book's Id Code, Title, and Author
	std::cout << "ID Code: " << bookItem->getIdCode() << std::endl
					  << "Title: " << bookItem->getTitle() << std::endl
					  <<	"Author: " << bookItem->getAuthor() << std::endl
					  << "Location: ";
	//Print Book's Location
	if( bookItem->getLocation() == 0 )
			std::cout << "On Shelf" << std::endl;
	else if( bookItem->getLocation() == 1 )
			std::cout << "On Hold" << std::endl;
	else
			std::cout << "Checked Out" << std::endl;

	//If the book has been checked out, print the Patron and date checked out
	if( bookItem->getCheckedOutBy() != NULL )
	{
		patronPerson = bookItem->getCheckedOutBy();
		std::cout	 <<	"Checked Out By: " << patronPerson->getName()
							 << std::endl
						   << "Date Checked Out: " << bookItem->getDateCheckedOut()
							 << std::endl;
	}

	//If the Books is requested by a patron, print their name
  if( bookItem->getRequestedBy() != NULL )
	{
		patronPerson = bookItem->getRequestedBy();
		std::cout <<	"Requested by: " << patronPerson->getName() << std::endl;	
	}
}



