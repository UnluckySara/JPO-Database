#pragma once
#include "DataBase.hpp"

namespace sl
{
	/**
	 * \brief
	 * 
	 * Class representing a user interface for managing a movie database.
	 * The menu contains three levels of management. 
	 * The first is for managing the database. 
	 * The second is for managing the contents of the database. 
	 * The third is for sorting criteria. You must always save the database otherwise 
	 * the changes will be lost.
	 */
	class Menu
	{
	private:
		sl::FilmDataBase& db;

		/**
		 * \brief Clears the console screen.
		 * 
		 * With each selection and confirmation the screen is cleared. 
		 * (The exception is displaying the contents of the database). 
		 * Some messages may not appear on the console screen
		 */
		void clearScreen();

		/**
		 * \brief Displays the main program menu.
		 */
		void displayMainMenu();

		/**
		 * \brief Displays the database edit menu.
		 */
		void displayEditMenu();

		/**
		 * \brief Displays the movie sorting menu.
		 */
    	void displaySortMenu();

    	/**
		 * \brief Validates the user's selection.
		 * 
		 * Checks and sets user-supplied text.
		 * This function prevents entering incorrect data and
		 * causing the program to freeze.
		 * 
		 * \param choice Choice in text form.
		 * \param option Variable to which the result will be written.
		 * 
		 * \return Integer in the given interval (Size integer).
		 */
   		bool validateChoice(std::string choice, int& option);

   		/**
		 * \brief Supports database edit operations.
		 * 
		 * Menu:
		 * 1 - Add record
		 * 2 - Display database contents
		 * 3 - Sort records
		 * 4 - Delete record
		 * 0 - Exit
		 */
		void handleEditDatabase();

		/**
		 * \brief Adds a new movie to the database.
		 * 
		 * The user is asked for each parameter separately. 
		 * There are no restrictions on the length of the title or director(s).
		 * 
		 * Year restrictions: not less than 1888.
		 * Ranking range from 0.0 to 10.0
		 */
		void addRecord();

		/**
		 * \brief Sorts records in the database according to selected criteria.
		 * 
		 * Sort by:
		 * 1 - Title\n
		 * 2 - Director(s)
		 * 3 - Year
		 * 4 - Rating
		 * 0 - Exit
		 */
    	void sortRecords();

    	/**
		 * \brief Deletes a movie based on its title.
		 */
    	void deleteRecord();
    public:

    	/**
		 * \brief Menu class constructor.
		 * 
		 * \param database A reference to a database object.
		 */
    	Menu(sl::FilmDataBase& database);

    	/**
		 * \brief Starts the user interface.
		 */
		void run();
	};
}