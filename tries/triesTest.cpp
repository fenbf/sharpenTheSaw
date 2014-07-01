#include <iostream>

template <typename T> class Tree
{
protected:
	struct Node
	{
		Node *_left{ nullptr };
		Node *_right{ nullptr };
		T _value;
	};

protected:
	Node *_root;

public:
	Tree() : _root(new Node()) { }
	virtual ~Tree() 
	{ 
		delete _left;
		_left = nullptr;
		delete _right;
		_right = nullptr;
	}

	void insert() { }

	unsigned int countLeaves()
	{
		return countLeaves(_root);
	}

private:
	static unsigned int countLeaves(Node *node)
	{
		if (node == nullptr)
			return 0;

		// leaf?
		if (node->_left == nullptr && node->_right == nullptr)
			return 1;

		return countLeaves(node->_left) + countLeaves(node->_right);
	}
};

template<typename T> void buildRandomTree(Tree<T> *tree)
{

}

int main()
{
	return 0;
}