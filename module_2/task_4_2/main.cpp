#include <iostream>
#include <istream>
#include <sstream>

#include <assert.h>
#include <queue>
#include <set>

template <class T>
struct DefaultComparator {
    int operator() (const T& l, const T& r) const {
        if (l < r)
            return -1;
        if (l == r)
            return 0;
        return 1;
    }
};

template <class Key, class Value, class Comparator = DefaultComparator<Key>>
class AVLTree {
    struct Node {
        Key key;
        Value value;
        
        Node* left;
        Node* right;
        
        uint8_t height;
        
        int rank;
        
        Node(Key key, Value value): key(key), value(value),
        left(nullptr), right(nullptr),
        height(1), rank(1) {}
    };
public:
    AVLTree(Comparator comp = Comparator()): root(nullptr), node_count(0), comp(comp) {}
    
    ~AVLTree() {
        delete root;
    }
    
    Value* find(const Key& key) {
        return find_aux(root, key);
    }
    
    void insert(const Key& key, const Value& value) {
        root = insert_aux(root, key, value);
    }
    
    void erase(const Key& key) {
        root = erase_aux(root, key);
    }
    
    Value kth_position(int k) {
        Node* curNode = root;
        int cur_rank = rank(curNode->left);
        while(curNode && k != cur_rank) {
            if (k < cur_rank) {
                curNode = curNode->left;
            } else {
                k = k - rank(curNode->left) - 1;
                curNode = curNode->right;
            }
            cur_rank = rank(curNode->left);
        }
        
        return curNode->key;
    }
    
    uint8_t height_tree() {
        return height(root);
    }
    
    void print() {
        Node* cur = root;
        std::queue<Node*> queue;
        Node* SEP = nullptr;
        
        if (!cur) return;
        
        queue.push(cur);
        queue.push(SEP);
        
        while(!queue.empty()) {
            Node* poped = queue.front();
            queue.pop();
            
            if (poped != SEP) {
                std::cout << poped->key << " ";
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
    
    int min_depth() {
        if (!root) return 0;
        return min_depth_aux(root);
    }
    
private:
    
    int min_depth_aux(Node *root) {
        if (!root) return 0;
        
        if (!root->left) {
            return min_depth_aux(root->right) + 1;
        } else if (!root->right) {
            return min_depth_aux(root->left) + 1;
        }
        
        return std::min(min_depth_aux(root->left), min_depth_aux(root->right)) + 1;
    }
    
    Node* root;
    size_t node_count;
    
    Comparator comp;
    
    Value* find_aux(Node* node, const Key& key) {
        if (!node) {
            return nullptr;
        }
        
        int res = comp(key, node->key);
        if (res == -1) {
            return find_aux(node->left, key);
        } else if (res == 1) {
            return find_aux(node->right, key);
        }
        return &node->value;
    }
    
    Node* insert_aux(Node* node, const Key& key, const Value& value) {
        if (!node) {
            node_count++;
            return new Node(key, value);
        }
        
        int res = comp(key, node->key);
        if (res == -1) {
            node->left = insert_aux(node->left, key, value);
        } else {
            node->right = insert_aux(node->right, key, value);
        }
        return balance(node);
    }
    
    Node* erase_aux(Node* node, const Key& key) {
        if (!node) {
            return nullptr;
        }
        
        int res = comp(key, node->key);
        if (res == -1) {
            node->left = erase_aux(node->left, key);
        } else if (res == 1) {
            node->right = erase_aux(node->right, key);
        } else {
            Node* left = node->left;
            Node* right = node->right;
            
            delete node;
            
            if (right == nullptr) {
                return left;
            }
            
            if (!right->left && !right->right) {
                right->left = left;
                return balance(right);
            }
            
            Node* min_node = find_and_remove_min(right);
            min_node->right = right;
            min_node->left = left;
            
//            Node* min_node = find_min(right);
//            min_node->right = remove_min(right);
//            min_node->left = left;
            
            return balance(min_node);
        }
        
        return balance(node);
    }
    
    Node* find_and_remove_min(Node* node) {
        Node* minNode = node;
        while(minNode->left) {
            minNode = minNode->left;
        }
        
        Node* finded_min = minNode; // 5
        
        Node* prev = node;
        minNode = node->left;
        
        if (minNode) {
            while(minNode->left) {
                prev = minNode;
                balance(minNode);
                minNode = minNode->left;
                
            }
        }
        
        
        if (minNode && minNode->right) {
            prev->left = minNode->right;
            finded_min->right = node;
        }
        
        if (minNode && minNode->right == nullptr) {
            prev->left = nullptr;
            finded_min->right = node;
        }
//        if (!minNode) {
//            finded_min->right = nullptr;
//        }
//        finded_min->left = node->left;
        
//        finded_min->right = minNode->right;
        
        return finded_min;
    }
    
    Node* find_min(Node* node) {
        if (!node->left) {
            return node;
        }
        return find_min(node->left);
    }
    
    Node* remove_min(Node* node) {
        if (!node->left) {
            return node->right;
        }
        node->left = remove_min(node->left);
        return balance(node);
    }
    
    uint8_t height(Node* node) {
        if (!node) {
            return 0;
        }
        return node->height;
    }
    
    void fix_height(Node* node) {
        if (!node) return;
        
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }
    
    int rank(Node* node) {
        if (!node) return 0;
        
        return node->rank;
    }
    
    void fix_rank(Node* node) {
        if (!node) return;
        
        node->rank = rank(node->left) + rank(node->right) + 1;
    }
    
    uint8_t balance_factor(Node* node) {
        return height(node->right) - height(node->left);
    }
    
    Node* balance(Node* node) {
        fix_height(node);
        fix_rank(node);
        
        int bf = balance_factor(node);
        if (bf == 2) {
            if (balance_factor(node->right) < 0) {
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        } else if (bf == -2) {
            if (balance_factor(node->left) > 0) {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }
        return node;
    }
    
    Node* rotate_left(Node* p) {
        Node* q = p->right;
        p->right = q->left;
        q->left = p;
        fix_height(p);
        fix_height(q);
        fix_rank(p);
        fix_rank(q);
        return q;
    }
    
    Node* rotate_right(Node* p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        fix_height(p);
        fix_height(q);
        fix_rank(p);
        fix_rank(q);
        return q;
    }
};

int run(std::istream& input, std::ostream& output) {
    AVLTree<int, int> tree;
    
    int size;
    input >> size;
    
    for (int i = 0; i < size; i++) {
        int num, kth;
        input >> num >> kth;
        
        if (num >= 0) {
            tree.insert(num, num);
        } else {
            tree.erase(num * (-1));
        }
//        tree.print();
        output << tree.kth_position(kth) << "\n";
    }
    
    return 0;
}

void testLogic() {
    {
        std::stringstream sstr_input;
        sstr_input << "5" << std::endl;
        sstr_input << "10 0" << std::endl;
        sstr_input << "11 0" << std::endl;
        sstr_input << "12 0" << std::endl;
        sstr_input << "-9 0" << std::endl;
        sstr_input << "-11 0" << std::endl;
        
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "10\n10\n10\n10\n10\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "3" << std::endl;
        sstr_input << "1 0" << std::endl;
        sstr_input << "2 0" << std::endl;
        sstr_input << "-1 0" << std::endl;
        
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "1\n1\n2\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "3" << std::endl;
        sstr_input << "1 0" << std::endl;
        sstr_input << "2 0" << std::endl;
        sstr_input << "-2 0" << std::endl;

        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "1\n1\n1\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "5" << std::endl;
        sstr_input << "40 0" << std::endl;
        sstr_input << "10 1" << std::endl;
        sstr_input << "4 1" << std::endl;
        sstr_input << "-10 0" << std::endl;
        sstr_input << "50 2" << std::endl;
        
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "40\n40\n10\n4\n50\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "9" << std::endl;
        sstr_input << "1 0" << std::endl;
        sstr_input << "2 0" << std::endl;
        sstr_input << "3 0" << std::endl;
        sstr_input << "4 0" << std::endl;
        sstr_input << "5 0" << std::endl;
        
        sstr_input << "-4 0" << std::endl;
        sstr_input << "-5 0" << std::endl;
        sstr_input << "-1 0" << std::endl;
        sstr_input << "-2 0" << std::endl;
        
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "1\n1\n1\n1\n1\n1\n1\n2\n3\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "3" << std::endl;
        sstr_input << "1 0" << std::endl;
        sstr_input << "2 0" << std::endl;
        sstr_input << "-2 0" << std::endl;
        
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "1\n1\n1\n");
    }
    
    std::cout << "TEST PASSED" << std::endl;
}

int main(int argc, const char * argv[]) {
    AVLTree<int, int> tree;

    tree.insert(10, 10);
    tree.insert(20, 11);
    tree.insert(30, 12);
    tree.insert(40, 12);
    tree.insert(50, 12);
    tree.insert(60, 12);

    tree.print();

    tree.erase(40);

    tree.print();

    return 0;
    
//    testLogic();
    return run(std::cin, std::cout);
}
