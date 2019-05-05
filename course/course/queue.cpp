#include "queue.h"
#include <iostream>

queue::node::node(string vertex, string parent)
{
	this->vertex = vertex;
	this->parent = parent;
	next = NULL;
	prev = NULL;
}

queue::node::~node()
{
	vertex.clear();
}

queue::queue()
{
	head = NULL;
	tail = NULL;
	size = 0;
}

queue::~queue()
{
	clear();
}

void queue::add(string vertex, string parent)
{
	if (size==0)
	{
		head = new node(vertex, parent);
		tail = head;
	}
	else
	{
		tail->next = new node(vertex, parent);
		tail->next->prev = tail;
		tail = tail->next;
	}
	size++;
}

string queue::sub()
{
	string mystring = head->vertex;
	if (size > 1)
	{
		head = head->next;
		head->prev->vertex.clear();
		delete head->prev;
		head->prev = NULL;
	}
	else 
		delete head;
	size--;
	return mystring;
}

string queue::return_parent(string vertrex)
{
	node* cur = head;
	while (cur->vertex != vertrex)
		cur = cur->next;
	return cur->parent;
}

string queue::return_head()
{
	return head->vertex;
}

string queue::return_tail()
{
	return tail->parent;
}

bool queue::is_empty()
{
	if (size == 0)
		return true;
	return false;
}

void queue::clear()
{
	string mystring;
	while (is_empty() == false)
		mystring = sub();
	head = NULL;
	tail = NULL;
}

bool queue::contains(string vertex)
{
	node* cur = head;
	while (cur != NULL)
	{
		if (cur->vertex == vertex)
			return true;
		cur = cur->next;
	}
	return false;
}

void queue::write()
{
	node* cur = head;
	while (cur != NULL)
	{
		cout << cur->parent << "->" << cur->vertex << "\n";
		cur = cur->next;
	}
}

void queue::way_creating(queue* myqueue)
{
	node* cur = head;
	while (cur->vertex != "t")
		cur = cur->next;
	myqueue->add(cur->vertex, cur->parent);
	while (cur->parent != "s")
	{
		cur = head;
		while (cur->vertex != myqueue->return_tail())
			cur = cur->next;
		myqueue->add(cur->vertex, cur->parent);
	}
}


