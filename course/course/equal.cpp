#include "equal.h"

using namespace std;

bool equal_graphs(graph graph1, graph graph2)
{
	if (graph1.size != graph2.size)
		return false;
	graph::list* cur11 = graph1.head;
	graph::list* cur12 = graph2.head;
	graph::list::node* cur21;
	graph::list::node* cur22;
	while (cur11 != NULL)
	{
		if (cur11->size != cur12->size)
			return false;
		if (cur11->vertex != cur12->vertex)
			return false;
		cur21 = cur11->head;
		cur22 = cur12->head;
		while (cur21 != NULL)
		{
			if (cur21->vertex != cur22->vertex)
				return false;
			if (cur21->bandwidth != cur22->bandwidth)
				return false;
			cur21 = cur21->next;
			cur22 = cur22->next;
		}
		cur11 = cur11->next;
		cur12 = cur12->next;
	}
	return true;
}

bool equal_size_t(size_t value1, size_t value2)
{
	if (value1 == value2)
		return true;
	return false;
}
