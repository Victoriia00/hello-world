#include <iostream>

class Node
{
public:
	Node() {};
	Node(int d, Node* n)
	{
		data = d;
		next = n;
	}

	int data;
	Node* next = NULL;
};

class List
{
public:
	List() 
	{}

	~List()
	{
		while (size!=0)
		{
			popfront();
		}
	}

	int length();
	void pushfront(int d);
	int popfront();
	void pushback(int d);
	int popback();
	void insert(int d, int index);
	void remove(int index);

	Node* first = NULL;
	int size = 0;
};


int main()
{
	List l;
	l.pushback(100);
	l.pushback(99);
	l.insert(98,2);
	l.remove(2);
	//std::cout << l.popback() << " "<< l.size;
}

int List::length()
{
	return this->size;
}

void List::pushfront(int d)
{
	first = new Node(d, first);
	++size;
}

int List::popfront()
{
	if (first == NULL)
	{
		return NULL;
	}

	int popped = first->data; 
	Node* temp = first;
	first = first->next;
	delete temp;
	--size;
	return popped;
}

void List::pushback(int d)
{
	Node* newNode = new Node(d, NULL);
	Node* current = first;

	if (current == NULL)
	{
		first = newNode;
		++size;
		return;
	}

	while (current->next != NULL)
	{
		current = current->next;
	}

	current->next = newNode;
	++size;
}

int List::popback()
{
	if (first == NULL)
	{
		return NULL;
	}

	Node* current = first;
	while (current->next != NULL)
	{
		current = current->next;
	}

	int popped = current->data;
	Node* temp = current;
	current = NULL;
	--size;
	delete temp;
	return popped;
}

void List::insert(int d, int index)
{
	if (index > size)
	{
		return;
	}
	Node* current = first;
	for (int i = 1; i < index -1; ++i)
	{
		current = current->next;
	}

	Node* newNode = new Node(d, current->next);
	current->next = newNode;
	++size;
}

void List::remove(int index)
{
	if (index > size)
	{
		return;
	}


	Node* current = first;
	for (int i = 1; i < index-1; ++i)
	{
		current = current->next;
	}

	Node* temp = current->next;
	current->next = temp->next;
	--size;
	delete temp;
}
