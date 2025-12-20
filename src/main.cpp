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
		chosen_path = FileHandler::find_directory(argv[1], argv[2]);
	else if(argc == 2)
		chosen_path = FileHandler::find_directory(argv[1]);
	else
	{
		//Display the help menu
		//Quit
		return 1;
	}

	if (FileHandler::file_exists(chosen_path))
	{
		std::ifstream input{chosen_path};
		std::string line{};
		while (std::getline(input, line))
			text.insert_end(line);
		input.close();
	}

	std::ofstream output {chosen_path, std::ios::app};
	
	// Comes back with the file, then loops through the command handler until the user asks to quit the program.
	// Invalid command! Type 'help' to pull up the command menu.
	return 0;
}