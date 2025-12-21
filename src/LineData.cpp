#include "LineData.h"
#include <string>
#include <stdexcept>
#include <iostream>

LineList::LineList() : head(nullptr), tail(nullptr), line_count(0) {}
LineList::LineList(std::string str)
{
	head = new Line{str, nullptr, nullptr};
	tail = head;
	line_count = 1;
}

LineList::LineList(const LineList& other) : head(nullptr), tail(nullptr), line_count(0)
{
	if (other.head == nullptr)
		return;
	head = new Line{ other.head->text, nullptr, nullptr };
	Line* iter{head};
	Line* iter_next{ other.head->next };
	while (iter_next)
	{
		iter->next = new Line{iter_next->text, nullptr, iter};
		iter = iter->next;
		iter_next = iter_next->next;
	}

	line_count = other.line_count;
}

Line& LineList::operator[](const size_t index)
{
	if (index >= line_count)
		throw std::out_of_range("Requested line does not exist!");
	
	Line* iter{ head };

	// Small optimization, determines which half of the list we're searching
	if (line_count / 2 < index)
	{
		iter = tail;
		size_t current_index = line_count - 1;
		while (index != current_index)
		{
			iter = iter->prev;
			current_index--;
		}
	}
	else
	{
		size_t current_index = 0;
		while (index != current_index)
		{
			iter = iter->next;
			current_index++;
		}
	}

	return *(iter);
}

void LineList::insert_end(std::string str)
{
	Line* new_line{ new Line{str, nullptr, tail}};
	tail->next = new_line;
	tail = new_line;
	line_count++;
}

void LineList::insert_front(std::string str)
{
	Line* new_line{ new Line{str, head, nullptr} };
	head->prev = new_line;
	head = new_line;
	line_count++;
}

void LineList::insert(std::string str, size_t index)
{
	Line* indexed_line{ &(*this)[index] };
	Line* new_line{ new Line{str, indexed_line, indexed_line->prev} };
	indexed_line->prev->next = new_line;
	indexed_line->prev = new_line;
	if (index == 0)
		head = new_line;
	
	line_count++;
}

void LineList::remove(size_t index)
{
	Line* indexed_line{ &(*this)[index] };
	line_count--;
	if (indexed_line == head)
	{
		head = indexed_line->next;
		head->prev = nullptr;
		delete indexed_line;
	}
	else if (indexed_line == tail)
	{
		tail = indexed_line->prev;
		tail->next = nullptr;
		delete indexed_line;
	}
	else
	{
		indexed_line->prev->next = indexed_line->next;
		indexed_line->next->prev = indexed_line->prev;
		delete indexed_line;
	}
}

void LineList::append(std::string str, size_t index)
{
	Line* indexed_line{ &(*this)[index] };
	indexed_line->text += str;
}

void LineList::replace(std::string str, size_t index)
{
	Line* indexed_line{ &(*this)[index] };
	indexed_line->text = str;
}

void LineList::print()
{
	Line* iter{ head };
	int line_num{ 1 };
	while (iter)
	{
		std::cout << line_num << " | " << iter->text << '\n';
		iter = iter->next;
		line_num++;
	}
}

void LineList::clear()
{
	Line* iter{ head };
	while (iter)
	{
		Line* old_iter = iter;
		iter = iter->next;
		delete old_iter;
	}

	head = nullptr;
	tail = nullptr;
	line_count = 0;
}

LineList& LineList::operator=(const LineList& other)
{
	clear();

	if (other.head == nullptr)
		return *this;

	head = new Line{ other.head->text, nullptr, nullptr };
	Line* iter{ head };
	Line* iter_next{ other.head->next };
	while (iter_next)
	{
		iter->next = new Line{ iter_next->text, nullptr, iter };
		iter = iter->next;
		iter_next = iter_next->next;
	}

	line_count = other.line_count;
	return *this;
}

LineList::~LineList()
{
	clear();
}