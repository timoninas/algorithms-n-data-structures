# Data Structers

One of the most important brances of programming

## Delete element binary search tree

 When we delete a node, three possibilities arise:
 
1. Node to be deleted is leaf: Simply remove from the tree.

2. Node to be deleted has only one child: Copy the child to the node and delete the child

3. Node to be deleted has two children: Find inorder successor of the node. Copy contents of the inorder successor to the node and delete the inorder successor. Note that inorder predecessor can also be used.
