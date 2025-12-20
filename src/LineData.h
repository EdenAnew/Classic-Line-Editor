#pragma once
#include <string>

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
	void insert(std::string, int);
	void remove(int);
	void append(std::string, int);
	void replace(std::string, int);
	void print();
	void clear();
private:
	Line* head;
	Line* tail;
	int line_count;
};