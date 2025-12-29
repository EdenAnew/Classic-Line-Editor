#include "../include/CommandHandler.h"
#include "../include/LineData.h"
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>
#include <cctype>
#include <algorithm>

namespace CommandHandler {

	void ProcessCommands(std::string input)
	{
		args.clear();

		std::string current_command_piece{};
		bool ignore_spaces{ true };
		size_t closing_quote = std::string::npos;

		for (size_t i{ 0 }; i < input.length(); ++i)
		{
			if (input.at(i) == '\"' && closing_quote == std::string::npos)
			{
				ignore_spaces = false;
				for (size_t j { input.length() - 1 }; j > 0; --j)
				{
					if (input.at(j) == '\"')
					{
						closing_quote = j;
						if (closing_quote == i)
							throw std::invalid_argument("Only one quote found! Did you forget to include a closer?\n");
						break;
					}
				}
				continue;
			}
			if (i == closing_quote)
			{
				ignore_spaces = true;
				continue;
			}

			if (ignore_spaces && std::isspace(input.at(i)))
			{
				if (current_command_piece != "")
					args.push_back(current_command_piece);
				current_command_piece = "";
			}
			else
				current_command_piece += input.at(i);
		}

		if (current_command_piece != "")
			args.push_back(current_command_piece);

		/*for (std::string arg : args)
			std::cout << '\n' << arg << '\n';*/

		if (CMDS.find(args.at(0)) != CMDS.end())
			CMDS.at(args.at(0))();
		else
			throw std::out_of_range("Command wasn't valid!\n");
	}

	void HandleInsertion()
	{
		if (args.size() < 2)
			throw std::invalid_argument("Not enough arguments given!\n");
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
			catch (const std::invalid_argument&) {
				throw std::invalid_argument("Invalid line number given!\n");
			}
			(*text_ref).insert(addition_text, line_number - 1);
		}
	}

	void HandleRemoval()
	{
		if (args.size() < 2)
			throw std::invalid_argument("Not enough arguments given!\n");
		size_t line_number{ };
		try {
			line_number = std::stoi(args.at(1));
		}
		catch (const std::invalid_argument&) {
			throw std::invalid_argument("Invalid line number given!\n");
		}
		(*text_ref).remove(line_number - 1);
	}

	void HandleAppendment()
	{
		if (args.size() < 3)
			throw std::invalid_argument("Not enough arguments given!\n");
		else
		{
			std::string addition_text = args.at(1);
			size_t line_number{ };
			try {
				line_number = std::stoi(args.at(2));
			}
			catch (const std::invalid_argument&) {
				throw std::invalid_argument("Invalid line number given!\n");
			}
			(*text_ref).append(addition_text, line_number - 1);
		}
	}

	void HandleReplacement()
	{
		if (args.size() < 3)
			throw std::invalid_argument("Not enough arguments given!\n");
		else
		{
			std::string replacement_text = args.at(1);
			size_t line_number{ };
			try {
				line_number = std::stoi(args.at(2));
			}
			catch (const std::invalid_argument&) {
				throw std::invalid_argument("Invalid line number given!\n");
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
			<< " ins, insert     Inserts line        text, # optional  \n"
			<< " EXAMPLE: \"ins \"Hello World!\" 5\"                   \n\n"
			<< " rem, remove     Removes line        line #            \n"
			<< " EXAMPLE: \"rem 5\"                                    \n\n"
			<< " app, append     Appends text        text, line #      \n"
			<< " EXAMPLE: \"app \" this is the end of the line.\" 5\"  \n\n"
			<< " rep, replace    Replaces line       text, line #      \n"
			<< " EXAMPLE: \"rep \"New text on this line!\" 5\"         \n\n"
			<< " pri, print      Prints all text     N/A               \n"
			<< " EXAMPLE: \"print\"                                    \n\n"
			<< " cle, clear      Clears all text     N/A               \n"
			<< " EXAMPLE: \"clear\"                                    \n\n"
			<< " hel, help       Displays this menu  N/A               \n"
			<< " EXAMPLE: \"help\"                                     \n\n"
			<< " qui, quit       Saves and quits     N/A               \n"
			<< " EXAMPLE: \"quit\"                                     \n"
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	}
}