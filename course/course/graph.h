#pragma once
#include <string>
#include "queue.h"

using namespace std;

class graph
{
private:
	class list
	{
	public:
		class node
		{
		public:
			string vertex;
			size_t bandwidth;
			size_t flow;
			node* prev;
			node* next;
			node(string vertex, size_t bandwidth);
			~node();
		};
		node* head;
		node* tail;
		size_t size;
		string vertex;
		char color;
		list* prev;
		list* next;
		list(string vertex);
		~list();
	};
	list* head;
	list* tail;
	size_t size;
public:
	graph();
	~graph();
	void add(string vertexstart, string vertexfinish, size_t bandwidth);
	void write();
	void clear_color();
	bool transport_net_check();
	void dfs_for_net(string vertex);
	bool dfs_for_cycles(string vertex);
	bool dfs_fing_way(queue* parents, queue* copyparents);
	size_t find_max_flow();
};