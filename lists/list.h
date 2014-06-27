#pragma once

template<typename T> class List
{
private:
	struct Node
	{
		~Node()
		{
			delete _next;
			_next = nullptr;
		}

		Node *_next = nullptr;
		T _value;
	};

private:
	Node *_head = nullptr;
public:
	List() 
	{ 
		_head = new Node();
	}
	~List()
	{
		delete _head;
		_head = nullptr;
	}

	void add(T element)
	{
		Node *n = new Node();
		n->_next = _head->_next;
		n->_value = element;
		_head->_next = n;
	}

	void iterate(void(*func)(T &value))
	{
		Node *n = _head->_next;
		while (n != nullptr)
		{
			func(n->_value);
			n = n->_next;
		}
	}
};