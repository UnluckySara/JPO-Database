#include <iostream>
#include <string>
#include "DataBase.hpp"
#include "Menu.hpp"

namespace sl
{
	void Menu::clearScreen()
 	{
		#if defined(_WIN32) || defined(_WIN64)
        	std::system("cls");
		#else
        	std::system("clear");
		#endif
    }

 	void Menu::displayMainMenu()
    {
        clearScreen();
        std::cout << "Menu:\n"
                  << "1 - Edit database\n"
                  << "2 - Save database\n"
                  << "3 - Delete database\n"
                  << "4 - Change database name\n"
                  << "0 - Exit program\n"
                  << "Your choice: ";
    }

	void Menu::displayEditMenu()
    {
        clearScreen();
        std::cout << "Menu:\n"
                  << "1 - Add record\n"
                  << "2 - Display database contents\n"
                  << "3 - Sort records\n"
                  << "4 - Delete record\n"
                  << "0 - Exit\n"
                  << "Your choice: ";
    }

	void Menu::displaySortMenu()
    {
    	clearScreen();
        std::cout << "Sort by:\n"
                  << "1 - Title\n"
                  << "2 - Director(s)\n"
                  << "3 - Year\n"
                  << "4 - Rating\n"
                  << "0 - Exit\n"
                  << "Your choice: ";
    }

 	bool Menu::validateChoice(std::string choice, int& option)
    {
    	try 
        {
            option = std::stoi(choice);
            return true;
        }
        catch (std::invalid_argument const& ex)
       	{
            return false;
        }
        catch (std::out_of_range const& ex)
        {
            return false;
        }
    }

	void Menu::handleEditDatabase()
    {
        while (true)
        {
            displayEditMenu();
            std::string choice;
            std::cin >> choice;
            std::cin.ignore();
            int option;
            if (!validateChoice(choice, option))
                continue;

            if (option == 0)
                break;

            switch (option)
            {
            case 1:
                addRecord();
                break;
            case 2:
                db.displayFilms();
                break;
            case 3:
                sortRecords();
                break;
            case 4:
                deleteRecord();
                break;
            default:
                std::cerr << "Invalid selection, please try again.\n";
                break;
            }
        }
    }

	void Menu::addRecord()
    {
        std::string title, director;
        int year;
        float rating;

        std::cout << "Enter movie title: ";
        std::getline(std::cin, title);

        std::cout << "Enter name the director(s): ";
        std::getline(std::cin, director);

        std::cout << "Enter the year of production: ";
        bool validYear = false;
        while (!validYear)
        {
        	std::string input_year; 
            std::cin >> input_year;
            std::cin.ignore();
            try 
            {
            	year = std::stoi(input_year);
	            if (year < 1888)
	            {
	                std::cout << "Incorrect year, please try again." << std::endl;
	                continue;
	            }
	            else 
	            {
	            	validYear = true;
	            }
            }
           	catch (std::invalid_argument const& ex)
            {
            	std::cout << "Incorrect year, please try again." << std::endl;
            	continue;
            }
            catch (std::out_of_range const& ex)
            {
            	std::cout << "Incorrect year, please try again." << std::endl;
            	continue;
            }          
        }
		std::cout << "Enter rating (0.0 - 10.0): ";
        bool validRating = false;
        while (!validRating)
        {
        	std::string input_rating;
            std::cin >> input_rating;
            std::cin.ignore();
            try 
            {
            	rating = std::stof(input_rating);
	            if (rating < 0.0f || rating > 10.0f)
	            {
	                std::cout << "Incorrect number, please try again." << std::endl;
	                continue;
	            }
	            else
	            {
	            	validRating = true;
	            }	 
            }
           	catch (std::invalid_argument const& ex)
            {
            	std::cout << "Incorrect year, please try again." << std::endl;
            	continue;
            }
            catch (std::out_of_range const& ex)
            {
            	std::cout << "Incorrect year, please try again." << std::endl;
            	continue;
            }      
        }
        db.addFilm({title, director, year, rating});       
    }

	void Menu::sortRecords()
    {
        while (true)
        {
        	displaySortMenu();
	        std::string sortChoice;
	        std::cin >> sortChoice;
	        std::cin.ignore();
	        int option;
	        if (!validateChoice(sortChoice, option))
	            continue;

	        if (option == 0)
	            break;

	        switch (option)
	        {
	        case 1:
	            db.sortFilms("title");
	            break;
	        case 2:
	            db.sortFilms("director");
	            break;
	        case 3:
	            db.sortFilms("year");
	            break;
	        case 4:
	            db.sortFilms("rating");
	            break;
	        default:
	            std::cerr << "Incorrect sort selection." << std::endl;
	            break;
	        }
	    }
    }

	void Menu::deleteRecord()
    {
        std::string title;
        std::cout << "Enter the title of the video to be deleted: ";
        std::getline(std::cin, title);
        db.removeFilm(title);
    }

    Menu::Menu(sl::FilmDataBase& database) : db(database) {}

	void Menu::run()
    {
        while (true)
        {
            displayMainMenu();
            std::string choice;
            std::cin >> choice;
            std::cin.ignore();
            int option;
            if (!validateChoice(choice, option))
                continue;

            if (option == 0)
            {
                std::cout << "The program has ended." << std::endl;
                break;
            }

            switch (option)
            {
            case 1:
                handleEditDatabase();
                break;
            case 2:
                db.saveToFile();
                break;
            case 3:
                db.deleteDatabase();
                break;
            case 4:
            {
                std::string new_filename;
                std::cout << "Enter a new database name: ";
                std::getline(std::cin, new_filename);
                db.changeDatabase(new_filename);
                break;
            }
            default:
                std::cerr << "Invalid selection, please try again." << std::endl;
                break;
            }
        }
    }

}
