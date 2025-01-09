# Database Movie Manager

The DatabaseMovieManager project is a console application designed for managing a movie database.
It allows users to:
- Add new movies to the database,
- Display the database content in a readable format,
- Sort movies by selected criteria (title, director, year, rating),
- Delete individual movies,
- Rename the database and save it to disk.

## Table of Contents

- [Autor](#autor)
- [Implemented Classes](#implemented-classes)
- [Compilaton Instruction](#compilaton-instruction)
- [Additional Information](#additional-information)
- [Documetation](#documentation)

## Autor

Project Title: Database Movie Manager
Version: 1.0
Author: Sara Libirt 
Date: 10.01.2025

## Implemented Classes

Film
A class representing a single movie.
1. Attributes:
  - m_title: Movie title (string),
  - m_director: Movie director (string),
  - m_year: Production year (int),
  - m_rating: Movie rating (float).
2. Methods:
  - Default and parameterized constructors,
  - Equality operator operator== for comparing movies.

FilmDataBase
A class managing the entire movie database.
1. Attributes:
  - m_film: A vector storing objects of the Film class,
  - m_filename: Database file name (string),
  - m_filepath: Full path to the file (std::filesystem::path).
2. Methods:
  - addFilm: Adds a new movie to the database,
  - displayFilms: Displays all movies in the database,
  - saveToFile: Saves the database content to a file,
  - loadFromFile: Loads the database from a file,
  - deleteDatabase: Deletes the database file from disk,
  - changeDatabase: Changes the name and location of the database,
  - removeFilm: Removes a movie by title,
  - sortFilms: Sorts the database by the selected criterion.

Menu
A class handling the application's user interface.
1. Attributes:
  - db: A FilmDataBase object passed by reference.
2. Methods:
  - displayMainMenu: Displays the application's main menu,
  - displayEditMenu: Displays the database editing submenu,
  - displaySortMenu: Displays options for sorting movies,
  - addRecord: Handles adding a new movie,
  - sortRecords: Handles sorting the database,
  - deleteRecord: Handles deleting a movie by title,
  - handleEditDatabase: Manages database editing operations,
  - run: Main program loop.

## Compilation/Execution Instructions

1. Prepare the Environment:
  - Ensure you have a compiler supporting the C++20 standard.
  - Install CMake version 3.10 or higher.
2. Project Structure:
  - The src/ folder contains source files (main.cpp, DataBase.cpp, Menu.cpp),
  - The include/ folder contains header files (DataBase.hpp, Menu.hpp),
3. Compilation:
  - Run CMake to generate build files:
    ```bash
    cmake . -B bulid
  - Compile the project using the command:
    ```bash
    make
4. Execution:
  - After compilation, the executable file named DatabaseMovieManager will be available in the build folder.
  - Run the application:
    ```bash
    ./DatabaseMovieManager
    
 ## Additional Information

 - Database Folder: All database files are stored in the DataBase directory.
 - The application automatically creates the DataBase if it does not exist.

## Documetation
[View documentation](DatabaseMovieManager.pdf)
