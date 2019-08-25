
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

void visual_tree(tree_s *&p, int level)
{
	if (p)
	{
		visual_tree(p->right, level + 1);
		for (int i = 0; i < level; i++) std::cout << "   ";
		std::cout << p->value << std::endl;
		visual_tree(p->left, level + 1);		
	}
}

void print_tree(tree_s *&node)
{
	if (node != nullptr) {
		
		print_tree(node->left);
		std::cout << " " << node->value;
		print_tree(node->right);
	}
}

tree_s* find_node(tree_s *&node, int value)
{	
	if (!node) {
		return nullptr;
	}
	int tmp = node->value;
	
	if (tmp == value) {
		return node;
	} else if (tmp < value) {
		return find_node(node->right, value);
	} else {
		return find_node(node->left, value);
	}

	return node;
}

void free_tree(tree_s* node)
{
	if (node->left) {
		free_tree(node->left);
	}

	if (node->right) {
		free_tree(node->right);
	}

	std::cout << " " << node->value;
	delete node;
}

int main()
{
	tree_s *object1 = new binary_tree(nullptr, nullptr, 5);

	add_node(object1, 3); add_node(object1, -1);
	add_node(object1, 7); add_node(object1, 4);
	add_node(object1, 1); add_node(object1, 30);

	for (int i = 0; i < 10; i++) {
		add_node(object1, i);
	}

	tree_s* obj = find_node(object1, 300);
	if (obj) {
		std::cout << obj->value << " kek !!\n\n";
	}

	visual_tree(object1, 1);

	free_tree(object1);
}
