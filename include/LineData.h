#pragma once
#include <string>
#include <fstream>

struct Line {
	std::string text;
	Line* next;
	Line* prev;
};

class LineList {
public:
	LineList();
	LineList(std::string);
	LineList(const LineList& other);
	~LineList();
	LineList& operator=(const LineList& other);
	Line& operator[](const size_t index);
	void insert_end(std::string);
	void insert_front(std::string);
	void insert(std::string, size_t);
	void remove(size_t);
	void append(std::string, size_t);
	void replace(std::string, size_t);
	void print();
	void clear();
	void write_to_file(std::ofstream&);
private:
	Line* head;
	Line* tail;
	size_t line_count;
};