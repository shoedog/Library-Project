/******************************************************************************
 *		
 *	Author: Wesley Jinks
 *	Date Created: 12/2/2014
 *	Last Modication Date: 12/7/2014
 *	FileName: menu.cpp
 *
 *	OverView: This program is a menu for a Library. It includes 10 menu options.
 *	 These are add a book, add a member, view book information, view member
 *	 information, check out a book, place a book on hold, return a book,
 *	 increment the date, add pay fines, as well as quit.
 *
 *	Input: It will take input for the menu options as well as input related to
 *	 information on a book, information on a member, and a fine payment amount.
 *
 *	Output: It will output a menu with the options, prompts for information 
 *		that needs to be input for each option, and the status of each menu 
 *		operation.
 *
 *
 * ***************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include "Book.h"
#include "Patron.h"
#include "Library.h"


int main()
{
	Library LibraryX;   //Represents a library object
	std::string bookId; //Represents a Book object ID
	std::string author; //A Book object author
	std::string title;  //Book object title
  std::string patronId;  //Patron object ID
  std::string patronName; //Patron object name
	char choice;          //Choice for menu
	double finePayment;  //fine amount for patron fine

	//Loop for menu
	do
	{
		std::cout << std::endl;
		std::cout << "Welcome to the Library System. Choose an option from the Menu"
						  << " below." << std::endl  << std::endl;
		//Menu Options
		std::cout << "  1: Add Book to Library " << std::endl
							<< "  2: Add Member to Library " << std::endl
							<< "  3: Check Out Book for Patron " << std::endl
						  << "  4: Return Book for Patron " << std::endl
							<< "  5: Request Hold for Patron " << std::endl
							<< "  6: Take Fine Payment " << std::endl
							<< "  7: Increment Current Date/Update Overdue Fines " << std::endl
						  << "  8: View Patron Information " << std::endl
							<< "  9: View Book Information " << std::endl
							<< "  0: Quit " << std::endl << std::endl
						  << " Enter the number of the choice. "
						  << " Example: To Quit enter 0. " << std::endl;
		std::cin >> choice;

		switch( choice )
		{
			case '1': //Call addBook() to add book to library
				std::cout << std::endl;
				LibraryX.addBook();
				break;

			case '2': //Call addMember to add member to Library
				std::cout << std::endl;
				LibraryX.addMember();
				break;

			case '3':  //Get input for Patron and ID number to call checkOutBook()
								// and check out a book from the library
				std::cout << "Enter Patron ID of person who wants to check out book: "
								  << std::endl;
				std::cin.ignore();
				std::getline( std::cin, patronId );
				std::cout << "Enter ID number of book to check out: " << std::endl;
				std::getline( std::cin, bookId );	
				std::cout << std::endl;
			  LibraryX.checkOutBook( patronId, bookId );
				break;

			case '4': //Get input for Book to return a book to the library by 
								// calling returnBook()
				std::cout << "Enter ID number of book to return: " << std::endl;
				std::cin.ignore();
				std::getline( std::cin, bookId );	
				std::cout << std::endl;
			  LibraryX.returnBook(  bookId );
				break;

			case '5':  //Get input for Patron and Book to call requestBook() and put
								//the book on hold for that Patron 
				std::cout << "Enter Patron ID of person who wants to reserve book: "
								  << std::endl;
				std::cin.ignore();
				std::getline( std::cin, patronId );
				std::cout << "Enter ID number of book to reserve: " << std::endl;
				std::getline( std::cin, bookId );	
				std::cout << std::endl;
			  LibraryX.requestBook( patronId, bookId );
				break;

			case '6':  //Get input for patron and fine amount to call payFine() and
								// pay a fine for a patron
				std::cout << "Enter Patron ID of person who wants to pay their fine: "
								  << std::endl;
				std::cin.ignore();
				std::getline( std::cin, patronId );
				std::cout << "Enter Fine Amount to Pay" << std::endl;
			  std::cin >> finePayment;	
				finePayment *= -1;
				std::cout << std::endl;
			  LibraryX.payFine( patronId, finePayment );	
				break;

			case '7': //increments the current date with incrementCurrentDate()
				LibraryX.incrementCurrentDate();
				std::cin.get();
				break;

			case '8': //Get input for patron to call viewPatronInfo() and view their
								// information
				std::cout << "Enter Patron Id to view their info: " << std::endl;
				std::cin.ignore();
				std::getline( std::cin, patronId );	
				std::cout << std::endl;
				LibraryX.viewPatronInfo( patronId ); 
				break;

			case '9': //Get input for Book to call viewBookInfo() and view the books
							// information
				std::cout << "Enter Book ID: ";
				std::cin.ignore();
			  std::getline( std::cin, bookId );
				std::cout << std::endl;
			  LibraryX.viewBookInfo( bookId );
				break;

			case '0': //Quits the program
				std::cout << "Quitting the Program. Good-bye. " << std::endl;
				break;
		}
		
		//If the choice is not to quit, prompts user to hit enter to return to
		//	the menu
		if( choice != '0' )
		{
			std::cout << "Press Enter to Return to the Menu. " << std::endl;
			std::cin.get();
		}

	}while( choice != '0' ); //loop terminates if the choice is 0

	return 0;
}
