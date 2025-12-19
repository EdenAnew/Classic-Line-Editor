#include "LineData.h"
#include <string>

int main()
{
	LineList l1{ "This is the first line!" };
	l1.insert_front("INCOMING LINES:");
	l1.insert_end("This is the third line!");
	l1.insert("This is the second line", 2);
	l1.append("!", 2);
	l1.insert_end("And this is the fourth line!");
	l1.print();

	LineList l2{ "Wait, I apologize! The previous message actually counted wrong!" };
	l2.insert_end("Let me fix that for you.");
	l2.print();

	l1.remove(0);
	l1.replace("Okay, now this really is the first line!", 0);
	l1.print();

	l2.clear();
	l2.print();
	return 0;
}