#include "BinaryTree.h"

int main()
{
	tree_s* object1 = new binary_tree(nullptr, nullptr, 5);

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