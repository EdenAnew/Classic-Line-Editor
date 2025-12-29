#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS
#include "doctest.h"
#include "../include/LineData.h"
#include <sstream>
#include <string>

TEST_CASE("LineList_Constructors_Valid")
{
	LineList l1{};
	std::stringstream stream;
	l1.print(stream);
	CHECK_EQ(stream.str(), "");
	stream.str("");
	
	LineList l2{ "Input" };
	l2.print(stream);
	REQUIRE_EQ(stream.str(), "1 | Input\n");
	stream.str("");

	LineList l3{l2};
	l3.print(stream);
	CHECK_EQ(stream.str(), "1 | Input\n");
	stream.str("");

	LineList l4 = l2;
	l4.print(stream);
	CHECK_EQ(stream.str(), "1 | Input\n");
	stream.str("");
}

TEST_CASE("LineList_Access_Expected_Behavior")
{
	LineList l1{"1"};
	std::stringstream stream;
	REQUIRE_EQ(l1[0].text, "1");
	l1.insert_end("2");
	l1.insert_end("3");
	CHECK_EQ(l1[0].text, "1");
	CHECK_EQ(l1[1].text, "2");
	CHECK_EQ(l1[2].text, "3");
	CHECK_THROWS_WITH(l1[3].text, "Requested line does not exist!\n");
}

TEST_CASE("LineList_Insertion_Across_List_Valid")
{
	LineList l1{};
	std::stringstream stream;
	l1.insert_end("3");
	l1.print(stream);
	REQUIRE_EQ(stream.str(), "1 | 3\n");
	stream.str("");

	l1.insert("2", 0);
	l1.print(stream);
	REQUIRE_EQ(stream.str(), "1 | 2\n2 | 3\n");
	stream.str("");

	l1.insert_front("1");
	l1.print(stream);
	CHECK_EQ(stream.str(), "1 | 1\n2 | 2\n3 | 3\n");
}

TEST_CASE("LineList_Remove_Valid")
{
	LineList l1{};
	std::stringstream stream;
	l1.insert_end("1");
	l1.insert_end("2");
	l1.insert_end("3");
	l1.print(stream);
	REQUIRE_EQ(stream.str(), "1 | 1\n2 | 2\n3 | 3\n");
	stream.str("");

	SUBCASE("Remove_First_Index")
	{
		l1.remove(0);
		l1.print(stream);
		CHECK_EQ(stream.str(), "1 | 2\n2 | 3\n");
	}
	SUBCASE("Remove_Middle_Index")
	{
		l1.remove(1);
		l1.print(stream);
		CHECK_EQ(stream.str(), "1 | 1\n2 | 3\n");
	}
	SUBCASE("Remove_Last_Index")
	{
		l1.remove(2);
		l1.print(stream);
		CHECK_EQ(stream.str(), "1 | 1\n2 | 2\n");
	}
}

TEST_CASE("LineList_Append_Valid")
{
	LineList l1{ "1" };
	std::stringstream stream;
	l1.append(" - The First Line", 0);
	l1.print(stream);
	CHECK_EQ(stream.str(), "1 | 1 - The First Line\n");
}

TEST_CASE("LineList_Replace_Valid")
{
	LineList l1{ "1" };
	std::stringstream stream;
	l1.replace("One", 0);
	l1.print(stream);
	CHECK_EQ(stream.str(), "1 | One\n");
}

TEST_CASE("LineList_Clear_Valid")
{
	LineList l1{ "1" };
	std::stringstream stream;
	l1.insert_end("2");
	l1.insert_end("3");
	l1.clear();
	l1.print(stream);
	CHECK_EQ(stream.str(), "");
}