#include "graph.h"
#include <iostream>

using namespace std;

graph::list::node::node(string vertex, size_t bandwidth)
{
	this->vertex = vertex;
	this->bandwidth = bandwidth;
	flow = 0;
	prev = NULL;
	next = NULL;
}

graph::list::node::~node()
{
	vertex.clear();
}

graph::list::list(string vertex)
{
	this->vertex = vertex;
	prev = NULL;
	next = NULL;
	head = NULL;
	tail = NULL;
	size = 0;
}

graph::list::~list()
{
	vertex.clear();
	node* cur1 = head;
	node* cur2;
	while (cur1 != NULL)
	{
		cur2 = cur1;
		cur1 = cur1->next;
		cur2->vertex.clear();
		delete cur2;
		size--;
	}
}

graph::graph()
{
	head = NULL;
	tail = NULL;
	size = 0;
}

graph::~graph()
{
	list* cur1 = head;
	list* cur2;
	list::node* cur3;
	list::node* cur4;
	while (cur1 != NULL)
	{
		cur2 = cur1;
		cur1 = cur1->next;
		cur2->vertex.clear();
		cur3 = cur2->head;
		while (cur3 != NULL)
		{
			cur4 = cur3;
			cur3 = cur3->next;
			cur4->vertex.clear();
			delete cur4;
			cur2->size--;
		}
		size--;
	}
}

void graph::add(string vertexstart, string vertexfinish, size_t bandwidth)
{
	if (size == 0)
	{
		head = new list(vertexstart);
		tail = head;
		head->head = new list::node(vertexfinish, bandwidth);
		head->tail = head->head;
		head->size++;
		size++;
	}
	else
	{
		list* cur1 = head;
		while ((cur1 != NULL) && (cur1->vertex != vertexstart))
			cur1 = cur1->next;
		if (cur1 == NULL)
		{
			tail->next = new list(vertexstart);
			tail->next->prev = tail;
			tail = tail->next;
			tail->head = new list::node(vertexfinish, bandwidth);
			tail->tail = tail->head;
			tail->size++;
			size++;
		}
		else
		{
			if (cur1->size == 0)
			{
				cur1->head = new list::node(vertexfinish, bandwidth);
				cur1->tail = cur1->head;
				cur1->size++;
			}
			else
			{
				list::node* cur2 = cur1->head;
				while ((cur2 != NULL) && (cur2->vertex != vertexfinish))
					cur2 = cur2->next;
				if (cur2 == NULL)
				{
					cur1->tail->next = new list::node(vertexfinish, bandwidth);
					cur1->tail->next->prev = cur1->tail;
					cur1->tail = cur1->tail->next;
					cur1->size++;
				}
			}
		}
	}
	list* cur3 = head;
	while ((cur3 != NULL) && (cur3->vertex != vertexfinish))
		cur3 = cur3->next;
	if (cur3 == NULL)
	{
		tail->next = new list(vertexfinish);
		tail->next->prev = tail;
		tail = tail->next;
		size++;
	}
}

void graph::write()
{
	list* cur1 = head;
	list::node* cur2;
	while (cur1 != NULL)
	{
		cout << cur1->vertex;
		cur2 = cur1->head;
		while (cur2 != NULL)
		{
			cout << "->" << cur2->vertex << "(" << cur2->bandwidth << ")";
			cur2 = cur2->next;
		}
		cout << "\n";
		cur1 = cur1->next;
	}
}

void graph::clear_color()
{
	list* cur1 = head;
	while (cur1 != NULL)
	{
		cur1->color = 'w';
		cur1 = cur1->next;
	}
}

bool graph::transport_net_check()
{
	clear_color();
	size_t scheck, tcheck;
	list* cur1 = head;
	tcheck = 0;
	while (cur1 != NULL)
	{
		if (cur1->head == NULL)
			if (cur1->vertex == "t")
				tcheck++;
			else
				tcheck += 2;
		cur1 = cur1->next;
	}
	if (tcheck != 1)
	{
		cout << "Uncorrect sink. Isn`t transport net.\n";
		return false;
	}
	cur1 = head;
	list* cur2;
	list::node* cur3;
	size_t scheck1;
	scheck = 0;
	while (cur1 != NULL)
	{
		scheck1 = 0;
		cur2 = head;
		while (cur2 != NULL)
		{
			cur3 = cur2->head;
			while (cur3 != NULL)
			{
				if (cur3->vertex == cur1->vertex)
					scheck1++;
				cur3 = cur3->next;
			}
			cur2 = cur2->next;
		}
		if (scheck1 == 0)
			if (cur1->vertex == "s")
				scheck++;
			else
				scheck += 2;
		cur1 = cur1->next;
	}
	if (scheck != 1)
	{
		cout << "Uncorrect source. Isn`t transport net.\n";
		return false;
	}
	dfs_for_net("s");
	cur1 = head;
	while (cur1 != NULL)
	{
		if (cur1->color == 'w')
		{
			cout << "Isn`t neted graph. Isn`n transport net.\n";
			return false;
		}
		cur1 = cur1->next;
	}
	clear_color();
	if (dfs_for_cycles("s") == false)
	{
		cout << "There are cycles. Isn`n transport net.\n";
		return false;
	}
	return true;
}

void graph::dfs_for_net(string vertex)
{
	list* cur1 = head;
	while (cur1->vertex != vertex)
		cur1 = cur1->next;
	cur1->color = 'b';
	list::node* cur2 = cur1->head;
	list* cur3;
	while (cur2 != NULL)
	{
		cur3 = head;
		while (cur2->vertex != cur3->vertex)
			cur3 = cur3->next;
		if (cur3->color == 'w')
			dfs_for_net(cur3->vertex);
		cur2 = cur2->next;
	}
}

bool graph::dfs_for_cycles(string vertex)
{
	list* cur1 = head;
	while (cur1->vertex != vertex)
		cur1 = cur1->next;
	cur1->color = 'g';
	list::node * cur2 = cur1->head;
	list * cur3;
	while (cur2 != NULL)
	{
		cur3 = head;
		while (cur2->vertex != cur3->vertex)
			cur3 = cur3->next;
		if (cur3->color == 'w')
			if (dfs_for_cycles(cur3->vertex) == false)
				return false;
		if (cur3->color == 'g')
			return false;
		cur2 = cur2->next;
	}
	cur1->color = 'b';
	return true;
}

bool graph::dfs_fing_way(queue* parents, queue* copyparents)
{
	queue myqueue;
	list* cur1 = head;
	while (cur1->vertex != "s")
		cur1 = cur1->next;
	list::node * cur2;
	myqueue.add(cur1->vertex, "-");
	while (myqueue.is_empty() == false)
	{
		myqueue.sub();
		cur2 = cur1->head;
		while (cur2 != NULL)
		{
			if ((cur2->bandwidth > cur2->flow) && (parents->contains(cur2->vertex) == false))
			{
				myqueue.add(cur2->vertex, "-");
				parents->add(cur2->vertex, cur1->vertex);
				copyparents->add(cur2->vertex, cur1->vertex);
				if (cur2->vertex == "t")
					return true;
			}
			cur2 = cur2->next;
		}
		cur1 = head;
		if (myqueue.is_empty() == false)
			while (cur1->vertex != myqueue.return_head())
				cur1 = cur1->next;
	}
	if (myqueue.is_empty() == true)
		return false;
	return true;
}

size_t graph::find_max_flow()
{
	bool wayexist = true;
	queue parents;
	queue copyparents;
	queue newparents;
	queue newcopyparents;
	int flow;
	size_t sumflow = 0;
	string vertex, parent;
	list* cur1;
	list::node* cur2;
	while (wayexist == true)
	{ 
		parents.clear();
		copyparents.clear();
		newparents.clear();
		newcopyparents.clear();
		wayexist = dfs_fing_way(&parents, &copyparents);
		if (wayexist == true)
		{
			parents.way_creating(&newparents);
			copyparents.way_creating(&newcopyparents);
			flow = -1;
			vertex.clear();
			parent.clear();
			while (newparents.is_empty() == false)
			{
				vertex = newparents.return_head();
				parent = newparents.return_parent(vertex);
				vertex = newparents.sub();
				cur1 = head;
				while (cur1->vertex != parent)
					cur1 = cur1->next;
				cur2 = cur1->head;
				while (cur2->vertex != vertex)
					cur2 = cur2->next;
				if ((flow < 0) || ((cur2->bandwidth - cur2->flow) < flow))
					flow = cur2->bandwidth - cur2->flow;
			}
			vertex.clear();
			parent.clear();
			while (newcopyparents.is_empty() == false)
			{
				vertex = newcopyparents.return_head();
				parent = newcopyparents.return_parent(vertex);
				vertex = newcopyparents.sub();
				cur1 = head;
				while (cur1->vertex != parent)
					cur1 = cur1->next;
				cur2 = cur1->head;
				while (cur2->vertex != vertex)
					cur2 = cur2->next;
				cur2->flow += flow;
			}
		}
	}
	cur1 = head;
	while (cur1->vertex != "s")
		cur1 = cur1->next;
	cur2 = cur1->head;
	while (cur2 != NULL)
	{
		sumflow += cur2->flow;
		cur2 = cur2->next;
	}
	return sumflow;
}
