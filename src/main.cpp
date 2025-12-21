#include "LineData.h"
#include "FileHandler.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
	LineList text{};
	std::filesystem::path chosen_path{};

	if (argc == 3)
	{
		try 
		{
			chosen_path = FileHandler::find_directory(argv[1], argv[2]);
		}
		catch(const std::invalid_argument& e)
		{
			std::cerr << "Error: " << e.what();
			return 1;
		}
	}
	else if(argc == 2)
		chosen_path = FileHandler::find_directory(argv[1]);
	else
	{
		std::cerr << "Error: Need file name to initialize to (and, optionally, a directory!)";
		return 1;
	}

	if (FileHandler::file_exists(chosen_path))
	{
		std::ifstream input{chosen_path};
		std::string line{};
		while (std::getline(input, line))
			text.insert_end(line);
		text.print();
		input.close();
	}

	std::ofstream output {chosen_path, std::ios::app};
	
	// Comes back with the file, then loops through the command handler until the user asks to quit the program.
	// Invalid command! Type 'help' to pull up the command menu.
	return 0;
}