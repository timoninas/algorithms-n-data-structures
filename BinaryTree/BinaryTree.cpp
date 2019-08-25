
#include <iostream>

typedef struct binary_tree tree_s;

struct binary_tree {
	int value;
	tree_s *left, *right;

	binary_tree(tree_s* new_left, tree_s* new_right, int new_value) {
		left = new_left;
		right = new_right;
		value = new_value;
	}
};

void add_node(tree_s *&node, int val)
{
	if (node == nullptr) {
		node = new binary_tree(nullptr, nullptr, val);
	}
	else {
		if (node->value < val) {
			add_node(node->right, val);
		}
		else {
			add_node(node->left, val);
		}
	}
}

void print_Tree(tree_s *&p, int level)
{
	if (p)
	{
		print_Tree(p->right, level + 1);
		for (int i = 0; i < level; i++) std::cout << "   ";
		std::cout << p->value << std::endl;
		print_Tree(p->left, level + 1);		
	}
}

void show_tree(tree_s *&node)
{
	if (node != nullptr) {
		
		show_tree(node->left);
		std::cout << " " << node->value;
		show_tree(node->right);
	}
}

int main()
{
	tree_s *object1 = new binary_tree(nullptr, nullptr, 5);

	add_node(object1, 3);
	add_node(object1, -1);
	add_node(object1, 7);
	add_node(object1, 4);
	add_node(object1, 1);
	add_node(object1, 30);

	for (int i = 0; i < 10; i++) {
		add_node(object1, i);
	}

	print_Tree(object1, 1);

    //std::cout << object1->value;
}
