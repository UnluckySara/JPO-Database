#pragma once
#include <filesystem>
#include <vector>


namespace sl
{
	/**
	 * \brief Constant defining the path to the database folder.
	 */
	const std::filesystem::path DbFolder = std::filesystem::current_path() / "DataBase";

	/**
	 * \brief A structure representing a single movie in the database.
	 * 
	 * One record containing the movie name, director,
	 * year of release and user rating
	 */
	struct Film
	{
		std::string m_title{}; 
		std::string m_director{};
		int m_year{};
		float m_rating{};

		/**
		 * \brief Default constructor.
		 * 
		 * Initializes all fields with default values.
		 */
		Film();

		/**
		 * \brief Parametric constructor.
		 * 
		 * Creates a single record with the given parameters.
		 * 
		 * \param title Title of the movie.
		 * \param director Name and surname of the director(s).
		 * \param year Year of production.
		 * \param rating Rating of the movie.
		 */
		Film(const std::string& title, const std::string& director, const int year, float rating);

		/**
		 * \brief Comparison operator
		 * 
		 * Compares two movies by their title and director.
		 * 
		 * \param other The structure to compare.
		 * 
		 * \return True if title and director are identical; otherwise false.
		 */
		bool operator==(const Film& other) const;
	};

	/**
	 * \brief Class for managing a movie database.
	 * 
	 * The FilmDataBase class allows you to store a collection of movies,
	 * as well as perform operations such as adding, removing, sorting, 
	 * writing, and reading from a file.
	 */
	class FilmDataBase
	{
	private:
		std::vector<Film> m_film;
		std::string m_filename = "database";
		std::filesystem::path m_filepath;
	public:

		/**
		 * \brief Default constructor
		 * 
		 * Creates a new database with the default filename "database".
		 */
		FilmDataBase();

		/**
		 * \brief Parametric constructor.
		 * 
		 * Creates a new database using the given file name.
		 * Constructor cannot be used for implicit type conversions.
		 * FilmDataBase db = "filename" <- NOT allowed.
		 * 
		 * \param filename The name of the database file.
		 */
		explicit FilmDataBase(const std::string& filename);

		/**
		 * \brief Adds a new movie to the database.
		 * 
		 * Creates a new record in the database. 
		 * The record is always added to the end of the database. 
		 * If the movie already exists in the database (identical title and director(s)), 
		 * the operation is canceled.
		 * 
		 * \param film A record representing the movie to add.
		 */
		void addFilm(const Film& film);

		/**
		 * \brief Displays all movies in the database.
		 * 
		 * Movies are displayed in a tabular format, with columns for title,
		 * director(s), year of production, and rating.
		 */
		void displayFilms() const;

		/**
		 * \brief Saves the database to a file.
		 * 
		 * All movies in the database are saved in a CSV 
		 * (semicolon separated value) file.
		 */
		void saveToFile() const;

		/**
		 * \brief Loads the database from a file.
		 * 
		 * Reads movie data from a CSV file.
		 * (Currently the only possible file format).
		 */
		void loadFromFile();

		/**
		 * \brief Deletes a database file.
		 * 
		 * Deletes the file we are currently working on.
		 * Saving a file will renew it.
		 */
		void deleteDatabase();

		/**
		 * \brief Changes the name of the database file.
		 * 
		 * Change the name of the database we are working on.
		 * 
		 * \param new_filename New name for the database file.
		 */
		void changeDatabase(const std::string& new_filename);

		/**
		 * \brief Removes the movie with the given title from the database.
		 * 
		 * If a movie with the given title exists, it is removed from the database.
		 * 
		 * \param title Title of the movie to remove.
		 */
        void removeFilm(const std::string& title);

        /**
         * \brief Sorts movies according to specific criteria.
         * 
         * Possible values of the criterion:
         * - "title" – sort by title.
         * - "director" – sort by director.
         * - "year" – sort by production year.
         * - "rating" – sort by rating.
         * 
         * Sorting is done alphabetically or from highest to lowest value.
         * If an invalid criterion is specified, the operation is canceled.
         * 
         * \param criteria Sorting criterion.
         */
		void sortFilms(const std::string& criteria);
		
	};
}
