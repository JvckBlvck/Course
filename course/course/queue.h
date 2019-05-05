#pragma once
#include <string>

using namespace std;

class queue
{
private:
	class node
	{
	public:
		string vertex;
		string parent;
		node* prev;
		node* next;
		node(string vertex, string parent);
		~node();
	};
	node* head;
	node* tail;
	size_t size;
public:
	queue();
	~queue();
	void add(string vertex, string parent);
	string sub();
	string return_parent(string vertrex);
	string return_head();
	string return_tail();
	bool is_empty();
	void clear();
	bool contains(string vertex);
	void write();
	void way_creating(queue* myqueue);
};