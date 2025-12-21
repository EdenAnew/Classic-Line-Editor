#include "CommandHandler.h"
#include "LineData.h"
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>

namespace CommandHandler {

	void HandleInsertion()
	{
		if (args.size() < 2)
			throw std::invalid_argument("Not enough arguments given!");
		else if (args.size() < 3)
		{
			std::string addition_text = args.at(1);
			(*text_ref).insert_end(addition_text);
		}
		else
		{
			std::string addition_text = args.at(1);
			size_t line_number{ };
			try {
				line_number = std::stoi(args.at(2));
			}
			catch (std::invalid_argument& e) {
				throw std::invalid_argument("Invalid line number given!");
			}
			(*text_ref).insert(addition_text, line_number - 1);
		}
	}

	void HandleRemoval()
	{
		if (args.size() < 2)
			throw std::invalid_argument("Not enough arguments given!");
		size_t line_number{ };
		try {
			line_number = std::stoi(args.at(1));
		}
		catch (std::invalid_argument& e) {
			throw std::invalid_argument("Invalid line number given!");
		}
		(*text_ref).remove(line_number - 1);
	}

	void HandleAppendment()
	{
		if (args.size() < 3)
			throw std::invalid_argument("Not enough arguments given!");
		else
		{
			std::string addition_text = args.at(1);
			size_t line_number{ };
			try {
				line_number = std::stoi(args.at(2));
			}
			catch (std::invalid_argument& e) {
				throw std::invalid_argument("Invalid line number given!");
			}
			(*text_ref).append(addition_text, line_number - 1);
		}
	}

	void HandleReplacement()
	{
		if (args.size() < 3)
			throw std::invalid_argument("Not enough arguments given!");
		else
		{
			std::string replacement_text = args.at(1);
			size_t line_number{ };
			try {
				line_number = std::stoi(args.at(2));
			}
			catch (std::invalid_argument& e) {
				throw std::invalid_argument("Invalid line number given!");
			}
			(*text_ref).replace(replacement_text, line_number - 1);
		}
	}

	void HelpMessage()
	{
		std::cout
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
			<< "**               Line Editor Help Menu               **\n"
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
			<< " Command         Description         Additional Inputs \n\n"
			<< " -ins, -insert   Inserts line        text, # optional  \n"
			<< " EXAMPLE: \"-ins \"Hello World!\" 5\"                  \n\n"
			<< " -rem, -remove   Removes line        line #            \n"
			<< " EXAMPLE: \"-rem 5\"                                   \n\n"
			<< " -app, -append   Appends text        text, line #      \n"
			<< " EXAMPLE: \"-app \" this is the end of the line.\" 5\" \n\n"
			<< " -rep, -replace  Replaces line       text, line #      \n"
			<< " EXAMPLE: \"-rep \"New text on this line!\" 5\"        \n\n"
			<< " -pri, -print    Prints all text     N/A               \n"
			<< " EXAMPLE: \"-print\"                                   \n\n"
			<< " -cle, -clear    Clears all text     N/A               \n"
			<< " EXAMPLE: \"-clear\"                                   \n\n"
			<< " -hel, -help     Displays this menu  N/A               \n"
			<< " EXAMPLE: \"-help\"                                   \n\n";
	}
}