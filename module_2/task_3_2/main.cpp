
// Task 3 2
// Вычислить количество узлов в самом широком слое
// декартового дерева и количество узлов в самом
// широком слое наивного дерева поиска.
// Вывести их разницу. Разница может быть отрицательна

#include <iostream>
#include <istream>
#include <sstream>

#include <assert.h>
#include <queue>

template <class T>
struct DefaultComparator {
    int operator() (const T& l, const T& r) const {
        if (l < r)
            return -1;
        if (l > r)
            return 1;
        return 0;
    }
};


template<class Key, class Value, class Comparator = DefaultComparator<Key>>
class BinaryTree {
    struct Node {
        Key key;
        
        Value value;
        
        Node* left;
        Node* right;
        Node(Key key, Value value): key(key),
        value(value), left(nullptr), right(nullptr) {}
    };
public:
    BinaryTree(Comparator comp = DefaultComparator<Key>()): root(nullptr), count_nodes(0), comp(comp) {}
    
    ~BinaryTree() {
        if (root) {
            std::queue<Node*> queue;
            queue.push(root);
            
            while(!queue.empty()) {
                Node* poped = queue.front();
                queue.pop();
                if (poped->left) queue.push(poped->left);
                if (poped->right) queue.push(poped->right);
                delete poped;
            }
        }
    }
    
    const Node* find(Key key) {
        if (!root) return nullptr;
        
        Node* tmpNode = root;
        while(tmpNode) {
            int res = comp(key, tmpNode->keyx);
            if (res == 0) {
                return tmpNode;
            } else if (res == -1) {
                tmpNode = tmpNode->left;
            } else {
                tmpNode = tmpNode->right;
            }
        }
        return nullptr;
    }
    
    void add(Key key, Value value) {
        Node* newNode = new Node(key, value);
        
        if (!root) {
            root = newNode;
            return;
        }
        
        Node* curNode = root;
        
        while(curNode) {
            if (newNode->key < curNode->key) {
                if (curNode->left) {
                    curNode = curNode->left;
                } else {
                    curNode->left = newNode;
                    break;
                }
            } else {
                if (curNode->right) {
                    curNode = curNode->right;
                } else {
                    curNode->right = newNode;
                    break;
                }
            }
        }
    }
    
    int count_leaves() {
        Node* cur = root;
        if (!cur) return 0;
        std::queue<Node*> queue;
        queue.push(cur);
        
        int max_width = 1;
        int current_width = 1;
        int next_width = 0;
        
        while (!queue.empty()) {
            next_width = 0;
            for (int i = 0; i < current_width; i++) {
                Node* popped = queue.front();
                queue.pop();
                if (popped->left) {
                    queue.push(popped->left);
                    next_width++;
                }
                if (popped->right) {
                    queue.push(popped->right);
                    next_width++;
                }
            }
            max_width = std::max(max_width, next_width);
            current_width = next_width;
        }
        return max_width;
    }
    
private:
    Node* root;
    size_t count_nodes;
    Comparator comp;
};



template<class Key, class Value, class Comparator = DefaultComparator<Key>>
class Treap {
    struct Node {
        Key keyx;
        Key keyy;
        
        Value value;
        
        Node* left;
        Node* right;
        Node(Key keyx, Key keyy, Value value): keyx(keyx),
        keyy(keyy), value(value), left(nullptr), right(nullptr) {}
    };
    
public:
    
    Treap(Comparator comp = DefaultComparator<Key>()): root(nullptr), count_nodes(0), comp(comp) {}
    
    ~Treap() {
        if (root) {
            std::queue<Node*> queue;
            queue.push(root);
            
            while(!queue.empty()) {
                Node* poped = queue.front();
                queue.pop();
                if (poped->left) queue.push(poped->left);
                if (poped->right) queue.push(poped->right);
                delete poped;
            }
        }
    }
    
    const Node* find(Key key) {
        if (!root) return nullptr;
        
        Node* tmpNode = root;
        while(tmpNode) {
            int res = comp(key, tmpNode->keyx);
            if (res == 0) {
                return tmpNode;
            } else if (res == -1) {
                tmpNode = tmpNode->left;
            } else {
                tmpNode = tmpNode->right;
            }
        }
        return nullptr;
    }
    
    void add(Key keyx, Key keyy, Value value) {
        Node* newNode = new Node(keyx, keyy, value);
        root = add_aux(root, newNode);
    }
    
    int count_leaves() {
        Node* cur = root;
        if (!cur) return 0;
        std::queue<Node*> queue;
        queue.push(cur);
        
        int max_width = 1;
        int current_width = 1;
        int next_width = 0;
        
        while (!queue.empty()) {
            next_width = 0;
            for (int i = 0; i < current_width; i++) {
                Node* popped = queue.front();
                queue.pop();
                if (popped->left) {
                    queue.push(popped->left);
                    next_width++;
                }
                if (popped->right) {
                    queue.push(popped->right);
                    next_width++;
                }
            }
            max_width = std::max(max_width, next_width);
            current_width = next_width;
        }
        return max_width;
    }
    
    
    void print() {
        Node* cur = root;
        std::queue<Node*> queue;
        Node* SEP = nullptr;
        
        if (!cur) return;
        
        queue.push(cur);
        queue.push(SEP);
        
        std::cout << std::endl;
        while(!queue.empty()) {
            Node* poped = queue.front();
            queue.pop();
            
            if (poped != SEP) {
                std::cout << poped->keyx << " ";
                if (poped->left) {
                    queue.push(poped->left);
                }
                if (poped->right) {
                    queue.push(poped->right);
                }
            } else {
                std::cout << std::endl;
                if (queue.empty()) return;
                queue.push(SEP);
            }
        }
    }
    
private:
    Node* root;
    size_t count_nodes;
    
    Comparator comp;
    
    Node* find_aux(Node* node, Key key) {
        if (!node) return nullptr;
    }
    
    void split(Node* currentNode, int key, Node*& left, Node*& right) {
        if (!currentNode) {
            left = nullptr;
            right = nullptr;
        } else if (currentNode->keyx <= key) {
            split(currentNode->right, key, currentNode->right, right);
            left = currentNode;
        } else {
            split(currentNode->left, key, left, currentNode->left);
            right = currentNode;
        }
    }
    
    Node* merge(Node* left, Node* right) {
        if (!left || !right) {
            return left == 0 ? right: left;
        }
        if (left->keyy > right->keyy) {
            left->right = merge(left->right, right);
            return left;
        } else {
            right->left = merge(left, right->left);
            return right;
        }
    }
    
    Node* add_aux(Node* node, Node* newNode) {
        if (!node) {
            return newNode;
        }
        
        if (newNode->keyy > node->keyy) {
            Node *left = nullptr, *right = nullptr;
            split(node, newNode->keyx, left, right);
            newNode->left = left;
            newNode->right = right;
            return newNode;
        }
        
        if (newNode->keyx < node->keyx) {
            node->left = add_aux(node->left, newNode);
        } else {
            node->right = add_aux(node->right, newNode);
        }
        
        //        MARK:- Simple insert node in treap
        //        Node* rot = root;
        //        Node* newNode = new Node(keyx, keyy, value);
        //        Node *left = nullptr, *right = nullptr;
        //        split(root, keyx, left, right);
        //        Node* newRoot = merge(left, newNode);
        //        newRoot = merge(newRoot, right);
        //        root = newRoot;
        
        return node;
    }
};

int run(std::istream& input, std::ostream& output) {
    Treap<int, int> *treap = new Treap<int, int>();
    BinaryTree<int, int> *tree = new BinaryTree<int, int>;
    
    int count;
    input >> count;
    
    for (int i = 0; i < count; i++) {
        int keyx, keyy;
        
        input >> keyx >> keyy;
        
        treap->add(keyx, keyy, keyx);
        tree->add(keyx, keyx);
    }
    
    output << treap->count_leaves() - tree->count_leaves() << std::endl;
    
    return 0;
}

void testLogic() {
    {
        std::stringstream sstr_input;
        sstr_input << "10" << std::endl;
        sstr_input << "5 11" << std::endl;
        sstr_input << "18 8" << std::endl;
        sstr_input << "25 7" << std::endl;
        sstr_input << "50 12" << std::endl;
        sstr_input << "30 30" << std::endl;
        sstr_input << "15 15" << std::endl;
        sstr_input << "20 10" << std::endl;
        sstr_input << "22 5" << std::endl;
        sstr_input << "40 20" << std::endl;
        sstr_input << "45 9" << std::endl;
        
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "1\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "10" << std::endl;
        sstr_input << "38 19" << std::endl;
        sstr_input << "37 5" << std::endl;
        sstr_input << "47 15" << std::endl;
        sstr_input << "35 0" << std::endl;
        sstr_input << "12 3" << std::endl;
        sstr_input << "0 42" << std::endl;
        sstr_input << "31 37" << std::endl;
        sstr_input << "21 45" << std::endl;
        sstr_input << "30 26" << std::endl;
        sstr_input << "41 6" << std::endl;
        
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "1\n");
    }
    
    std::cout << "TEST PASSED" << std::endl;
}

int main(int argc, const char * argv[]) {
    
//    testLogic();
//    return 0;
    
    return run(std::cin, std::cout);
}
