#pragma once

#include <iostream>

typedef struct binary_tree tree_s;

struct binary_tree {
	int value;
	tree_s* left, * right;

	binary_tree(tree_s* new_left, tree_s* new_right, int new_value) {
		left = new_left;
		right = new_right;
		value = new_value;
	}
};

void add_node(tree_s*& node, int val);
void visual_tree(tree_s*& p, int level);
void print_tree(tree_s*& node);
tree_s* find_node(tree_s*& node, int value);
void free_tree(tree_s* node);