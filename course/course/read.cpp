#include "read.h"
#include <fstream>

void read(graph* mygraph)
{
	fstream in;
	in.open("C:\\Users\\senny\\source\\repos\\course\\course\\in.txt", ios::in);
	in.unsetf(ios::skipws);
	string newvertexstrat, newvertexfinish;
	size_t newbandwidth;
	char c;
	while (!in.eof())
	{
		newvertexstrat.clear();
		c = 'a';
		while ((!in.eof()) && (c != ' ') && (c != '\n'))
		{
			in >> c;
			if ((c != ' ') && (c != '\n'))
				newvertexstrat += c;
		}
		if ((newvertexstrat.length() == 0) || (in.eof()) || (c == '\n'))
			while ((!in.eof()) && (c != '\n'))
				in >> c;
		else
		{
			newvertexfinish.clear();
			c = 'a';
			while ((!in.eof()) && (c != ' ') && (c != '\n'))
			{
				in >> c;
				if ((c != ' ') && (c != '\n'))
					newvertexfinish += c;
			}
			if ((newvertexfinish.length() == 0) || (in.eof()) || (c == '\n'))
				while ((!in.eof()) && (c != '\n'))
					in >> c;
			else
			{
				c = 'a';
				in >> c;
				in.unget();
				if ((c != '0') && (c != '1') && (c != '2') && (c != '3') && (c != '4') && (c != '5') && (c != '6') && (c != '7') && (c != '8') && (c != '9'))
					while ((!in.eof()) && (c != '\n'))
						in >> c;
				else
				{
					in >> newbandwidth;
					c = 'a';
					in >> c;
					if ((!in.eof()) && (c != '\n'))
						while ((!in.eof()) && (c != '\n'))
							in >> c;
					else
						mygraph->add(newvertexstrat, newvertexfinish, newbandwidth);
				}
			}
		}
	}
	in.close();
}
