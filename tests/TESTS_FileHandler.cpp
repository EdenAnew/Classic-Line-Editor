#include "doctest.h"
#include "../include/FileHandler.h"
#include <filesystem>
#include <fstream>

TEST_CASE("FileHandler_FindDirectory_Expected_Behavior")
{
	char c1[] = "";
	CHECK_THROWS_WITH(FileHandler::find_directory(c1, c1), "Path does not exist!\n");
	
	char c2[] = "TEST_FileHandler_File.txt";
	std::filesystem::path p1{ FileHandler::find_directory(c2) };
	REQUIRE(std::filesystem::exists("./LineEditorOutput"));
	if (std::filesystem::is_empty("./LineEditorOutput"))
		std::filesystem::remove("./LineEditorOutput");

	std::filesystem::path p2{ "./LineEditorOutput/TEST_FileHandler_File.txt" };
	CHECK_EQ(p1, p2);
}

TEST_CASE("FileHandler_FileExists_Expected_Behavior")
{
	std::filesystem::path p1{ "" };
	CHECK_EQ(FileHandler::file_exists(p1), false);

	std::filesystem::path p2{ std::filesystem::current_path() };
	std::ofstream output{ "TEST_FileHandler_File.txt" };
	REQUIRE(output.is_open());
	output.close();
	p2 += "/TEST_FileHandler_File.txt";
	CHECK_EQ(FileHandler::file_exists(p2), true);
	std::filesystem::remove(p2);
}