#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include "DataBase.hpp"
#include "Menu.hpp"

void displayFilesInDirectory()
{
    namespace fs = std::filesystem;
    std::cout << sl::DbFolder.string() << "\n";
    if (!fs::exists(sl::DbFolder))
    {
        fs::create_directory(sl::DbFolder);
    }
    std::cout << "Available files in database: \n";
    for (const auto& entry : fs::directory_iterator(sl::DbFolder))
    {
        if (entry.is_regular_file())
        {
            std::cout << " - " << entry.path().filename().string() << std::endl;
        }
    }
    std::cout << std::endl;
}

int main()
{
	std::string filename;
    displayFilesInDirectory();
    std::cout << "Enter database name or new to create one: ";
    std::getline(std::cin, filename);

    sl::FilmDataBase db(filename);
    db.loadFromFile();

    sl::Menu menu(db);
    menu.run();

    return 0;
}