#include "BinaryTree.h"

int main()
{
	/*tree_s* object1 = new binary_tree(nullptr, nullptr, 5);

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

	free_tree(object1);*/
	tree_s* object1 = nullptr;
	int action = 0;

	while (action != -1) {

		actions_binarytree();

		std::cout << " Input action: ";
		std::cin >> action;

		switch (action) {

		case 0: 
			continue;
			break;

		case 1:
			int value;

			std::cout << " Input number: ";
			std::cin >> value;

			if (!object1) {
				object1 = new binary_tree(nullptr, nullptr, value);
				std::cout << " Initilized and added\n";
			}
			else {
				add_node(object1, value);
				std::cout << " Added\n";
			}

			

			break;
			
		case 4:
			if (!object1) {
				std::cout << " \nBinary tree is absent\n";
			}
			else {
				visual_tree(object1, 0);
			}
			
			break;

		case 5:
			print_tree(object1);
			break;

		case 6:
			free_tree(object1);
			object1 = nullptr;

			break;

		case -1:
			break;

		default:
			std::cout << "\n Incorrect input!\n";
		}
	}

	std::cout << "\n Programm succesfully completed!\n";
}