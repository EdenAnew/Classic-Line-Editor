#include "doctest.h"
#include "../include/CommandHandler.h"
#include "../include/LineData.h"
#include <sstream>
#include <vector>

TEST_CASE("CommandHandler_Insertion_Valid")
{
	LineList text;
	std::stringstream stream;
	CommandHandler::args.clear();
	REQUIRE_EQ(CommandHandler::args.size(), 0);
	CommandHandler::text_ref = &text;

	CommandHandler::args.push_back("");
	CHECK_THROWS_WITH(CommandHandler::HandleInsertion(), "Not enough arguments given!\n");
	CommandHandler::args.push_back("1");
	CommandHandler::HandleInsertion();
	SUBCASE("Insertion_Without_Position_Argument")
	{
		text.print(stream);
		REQUIRE_EQ(stream.str(), "1 | 1\n");
	}
	SUBCASE("Insertion_With_Position_Argument")
	{
		CommandHandler::args.at(1) = "2";
		CommandHandler::args.push_back("1");
		CommandHandler::HandleInsertion();
		text.print(stream);
		CHECK_EQ(stream.str(), "1 | 2\n2 | 1\n");
	}
	SUBCASE("Insertion_With_Invalid_Position_Argument_Throws")
	{
		CommandHandler::args.push_back("throw");	
		CHECK_THROWS_WITH(CommandHandler::HandleInsertion(), "Invalid line number given!\n");
	}
}

TEST_CASE("CommandHandler_Removal_Valid")
{
	LineList text;
	std::stringstream stream;
	text.insert_end("text");
	CommandHandler::args.clear();
	REQUIRE_EQ(CommandHandler::args.size(), 0);
	CommandHandler::text_ref = &text;
	
	CommandHandler::args.push_back("");
	CHECK_THROWS_WITH(CommandHandler::HandleRemoval(), "Not enough arguments given!\n");
	
	CommandHandler::args.push_back("1");
	CommandHandler::HandleRemoval();
	text.print(stream);
	CHECK_EQ(stream.str(), "");

	CommandHandler::args.at(1) = "throw";
	CHECK_THROWS_WITH(CommandHandler::HandleRemoval(), "Invalid line number given!\n");
}

TEST_CASE("CommandHandler_Appendment_Valid")
{
	LineList text;
	std::stringstream stream;
	text.insert_end("text");
	CommandHandler::args.clear();
	REQUIRE_EQ(CommandHandler::args.size(), 0);
	CommandHandler::text_ref = &text;

	CommandHandler::args.push_back("");
	CHECK_THROWS_WITH(CommandHandler::HandleAppendment(), "Not enough arguments given!\n");

	CommandHandler::args.push_back(" and more text");
	CommandHandler::args.push_back("1");
	CommandHandler::HandleAppendment();
	text.print(stream);
	CHECK_EQ(stream.str(), "1 | text and more text\n");

	CommandHandler::args.at(2) = "throw";
	CHECK_THROWS_WITH(CommandHandler::HandleAppendment(), "Invalid line number given!\n");
}

TEST_CASE("CommandHandler_Replacement_Valid")
{
	LineList text;
	std::stringstream stream;
	text.insert_end("text");
	CommandHandler::args.clear();
	REQUIRE_EQ(CommandHandler::args.size(), 0);
	CommandHandler::text_ref = &text;

	CommandHandler::args.push_back("");
	CHECK_THROWS_WITH(CommandHandler::HandleReplacement(), "Not enough arguments given!\n");

	CommandHandler::args.push_back("words");
	CommandHandler::args.push_back("1");
	CommandHandler::HandleReplacement();
	text.print(stream);
	CHECK_EQ(stream.str(), "1 | words\n");

	CommandHandler::args.at(2) = "throw";
	CHECK_THROWS_WITH(CommandHandler::HandleReplacement(), "Invalid line number given!\n");
}

TEST_CASE("CommandHandler_Process_Valid")
{
	LineList text;
	std::stringstream stream;
	std::string input{};
	CommandHandler::text_ref = &text;
	text.insert_end("Example Line");
	SUBCASE("Process_Parses_Valid_Two_Arguments")
	{
		input = "insert \"Example Line 2\"";
		CommandHandler::ProcessCommands(input);
		text.print(stream);
		CHECK_EQ(stream.str(), "1 | Example Line\n2 | Example Line 2\n");
	}
	SUBCASE("Process_Parses_Valid_Two_Arguments_Ignores_Spaces")
	{
		input = "insert       \"Example Line 2\"        ";
		CommandHandler::ProcessCommands(input);
		text.print(stream);
		CHECK_EQ(stream.str(), "1 | Example Line\n2 | Example Line 2\n");
	}
	SUBCASE("Process_Parses_Valid_Three_Arguments")
	{
		input = "insert \"Example Line 2\" 1";
		CommandHandler::ProcessCommands(input);
		text.print(stream);
		CHECK_EQ(stream.str(), "1 | Example Line 2\n2 | Example Line\n");
	}
	SUBCASE("Process_Parses_Valid_Three_Arguments_Ignores_Spaces")
	{
		input = "insert        \"Example Line 2\"          1          ";
		CommandHandler::ProcessCommands(input);
		text.print(stream);
		CHECK_EQ(stream.str(), "1 | Example Line 2\n2 | Example Line\n");
	}
	SUBCASE("Process_Notices_Missing_Quote")
	{
		input = "insert \"Example Line 2";
		CHECK_THROWS_WITH(CommandHandler::ProcessCommands(input), "Only one quote found! Did you forget to include a closer?\n");
	}
	SUBCASE("Process_Notices_Invalid_Command")
	{
		input = "FAKE_COMMAND \"Example Line 2\"";
		CHECK_THROWS_WITH(CommandHandler::ProcessCommands(input), "Command wasn't valid!\n");
	}
}