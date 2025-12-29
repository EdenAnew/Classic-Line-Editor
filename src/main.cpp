#include "../include/LineData.h"
#include "../include/CommandHandler.h"
#include "../include/FileHandler.h"
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
		std::ifstream input_f{chosen_path};
		std::string line{};
		while (std::getline(input_f, line))
			text.insert_end(line);
		text.print();
		input_f.close();
	}
	std::cout << "Success! File location is: " << chosen_path << '\n';

	std::string input{};
	CommandHandler::text_ref = &text;

	while (!CommandHandler::quit)
	{
		try {
			std::getline(std::cin, input);
			CommandHandler::ProcessCommands(input);
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << "Error: " << e.what() << "Type \'help\' to pull up the command menu!\n";
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "Error: " << e.what() << "Type \'help\' to pull up the command menu!\n";
		}
	}

	std::ofstream output{ chosen_path };
	text.write_to_file(output);
	output.close();
	return 0;
}