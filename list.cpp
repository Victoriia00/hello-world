#include <iostream>

class Node 
{
public:
	Node() = default;
	Node(int d) : data(d)
	{}

	int data;
	Node* next = nullptr;
};

class List
{
public:
	List() : first(nullptr) 
	{}

	void append(int d);
	void remove(int n);

	Node* first;
};


int main()
{
	List l;
	l.append(5);
}

void List::append(int d)
{
	Node* current = first;
	while (current->next)
	{
		current = current->next;
	}

	current->next = &(Node(d));
}
void List::remove(int n)
{
	Node* current = first;

	for (int i = 1; i < n;++i)
	{
		current = current->next;
	}

	Node* removed = current->next;

	current->next = removed->next;

	removed->next = nullptr;
}
