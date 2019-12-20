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

	int operator[](const int index);

	List& operator=(const List& self);

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

void print(List& l)
{
	for (int i = 1; i <= l.size; ++i)
	{
		std::cout << l[i]<< ' ';
	}
	std::cout << std::endl;
}

int main()
{
	List l,l1;
	l.pushback(100);
	l.pushfront(98);
	l.insert(99,2);
	std::cout << "list l after pushback 100, pushfront 98, insert 98,2 " << std::endl;
	print(l);
	l1 = l;
	std::cout << "list l1 after copy " << std::endl;
	print(l1);
	l.remove(2);
	std::cout << "list l after remove 2" << std::endl;
	print(l);
	std::cout << "list l1 after remove 2 in l" << std::endl;
	print(l1);
	l.popback();
	std::cout << "list l after popback" << std::endl;
	print(l);
	std::cout << "list l1 after popback in l" << std::endl;
	print(l1);
	l.popfront();
	std::cout << "list l after popfront" << std::endl;
	print(l);
	std::cout << "list l1 after remove in l" << std::endl;
	print(l1);
	
}

int List::operator[](const int index)
{
	if (index > size)
	{
		return NULL;
	}

	Node* current = first;
	for (int i = 1; i <= index-1; ++i)
	{
		current = current->next;
	}

	return current->data;
}

List& List::operator=(const List& self)
{
    while (size!=0)
		{
			popfront();
		}
	Node* current = self.first;
	for (int i = 1; i <= self.size; ++i)
	{
		int b = current->data;
		pushback(b);
		current = current->next;
	}

	size = self.size;

	return *this;
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
