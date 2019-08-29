
#include "BinaryTree.h"

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
	if (p != nullptr)
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


