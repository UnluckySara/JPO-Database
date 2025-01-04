#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "DataBase.hpp"

namespace sl
{
	Film::Film() = default;

	Film::Film(const std::string& title, const std::string& director, const int year, float rating)
			: m_title(title), m_director(director), m_year(year), m_rating(rating) {}

	bool Film::operator==(const Film& other) const
	{
		return m_title == other.m_title && m_director == other.m_director;
	}

	FilmDataBase::FilmDataBase() : m_filepath(DbFolder / m_filename) {}

	FilmDataBase::FilmDataBase(const std::string& filename)
			: m_filename(filename), m_filepath(DbFolder / filename) {}

	void FilmDataBase::addFilm(const Film& film)
	{
		if(std::find(m_film.begin(), m_film.end(), film) == m_film.end())
		{
			m_film.push_back(film);
			std::cout << "Video added: " << film.m_title << std::endl;
		}
		else
		{
			std::cout << "The video already exists in the database." << std::endl;
		}
	}

	void FilmDataBase::displayFilms() const
	{
		std::cout << std::left << std::setw(30) << "Title"
				  << std::setw(30) << "Director"
				  << std::setw(10) << "Year"
				  << std::setw(10) << "Rating" << std::endl;
		std::cout << std::string(80, '-') << std::endl;

		for (const auto& film : m_film)
		{
			std::cout << std::setw(30) << film.m_title
                      << std::setw(30) << film.m_director
                      << std::setw(10) << film.m_year
                      << std::setw(10) << film.m_rating << std::endl;
		}
		std::cout << "\nPress Enter to continue...";
    	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	void FilmDataBase::saveToFile() const
	{
		std::ofstream file(m_filepath.string());
        if (!file.is_open())
		{
			std::cerr << "Could not open file for writing: " << m_filename << std::endl;
			return;
		}

		for (const auto& film : m_film)
		{
			file << film.m_title << ";" << film.m_director << ";" 
			<< film.m_year << ";" << film.m_rating << std::endl;
		}
		std::cout << "Saved database to file: " << m_filename << std::endl;
	}

	void FilmDataBase::loadFromFile()
	{
		std::ifstream file(m_filepath.string());
		if (!file.is_open())
		{
			std::cerr << "Could not open file for reading: " << m_filename << std::endl;
		    return;
		}

		m_film.clear();
		std::string line;

		while (std::getline(file, line))
		{
			std::stringstream ss(line);
		    std::string title, director, yearStr, ratingStr;
		    int year;
		    float rating;
			if (std::getline(ss, title, ';') &&
		        std::getline(ss, director, ';') &&
		        std::getline(ss, yearStr, ';') &&
		        std::getline(ss, ratingStr, ';'))
			{
		        try
		        {
		            year = std::stoi(yearStr);
		            rating = std::stof(ratingStr);
		            m_film.emplace_back(title, director, year, rating);
		        }
		        catch (const std::invalid_argument& ex)
		        {
		            std::cerr << "Error parsing line: " << line << std::endl;
		            continue;
		        }
			}
			else
			{
				std::cerr << "Malformed line: " << line << std::endl;
			}
		}
		std::cout << "Database loaded from file: " << m_filename << std::endl;
	}

	void FilmDataBase::deleteDatabase()
    {
        if (std::filesystem::remove(m_filepath))
        {
            std::cout << "Database has been deleted: " << m_filename << std::endl;
        }
        else
        {
            std::cerr << "Failed to delete file: " << m_filename << std::endl;
        }
    }

    void FilmDataBase::changeDatabase(const std::string& new_filename)
    {
       	auto old_path = m_filepath;
        m_filename = new_filename;
        m_filepath = DbFolder / m_filename;
        std::filesystem::rename(old_path, m_filepath);
        std::cout << "Database changed to: " << m_filename << std::endl;
    }

    void FilmDataBase::removeFilm(const std::string& title)
    {
        auto it = std::remove_if(m_film.begin(), m_film.end(),
            [&title](const Film& f) { return f.m_title == title; });

        if (it != m_film.end())
        {
            m_film.erase(it, m_film.end());
            std::cout << "A movie titled '" << title << "' has been deleted." << std::endl;
        }
        else
        {
            std::cout << "No movie with the title found '" << title << "'." << std::endl;
        }
    }

    void FilmDataBase::sortFilms(const std::string& criteria)
	{
		if (criteria == "title")
		{
		    std::sort(m_film.begin(), m_film.end(), 
		        [](const Film& a, const Film& b) { return a.m_title < b.m_title; });
		}
		else if (criteria == "director")
		{
		    std::sort(m_film.begin(), m_film.end(), 
		        [](const Film& a, const Film& b) { return a.m_director < b.m_director; });
		}
		else if (criteria == "year")
		{
		    std::sort(m_film.begin(), m_film.end(), 
		       [](const Film& a, const Film& b) { return a.m_year < b.m_year; });
		}
		else if (criteria == "rating")
		{
		    std::sort(m_film.begin(), m_film.end(), 
		        [](const Film& a, const Film& b) { return a.m_rating < b.m_rating; });
		}
		else
		{
		    std::cerr << "Invalid sorting criterion."<< std::endl;
		}
		std::cout << "The videos have been sorted."<< std::endl;
	}

}