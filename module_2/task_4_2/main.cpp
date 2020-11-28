
#include <iostream>

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

template <class Key, class Value, class Comparator = DefaultComparator<Key>>
class AVLTree {
    struct Node {
        Key key;
        Value value;
        
        Node* left;
        Node* right;
        
        uint32_t height;
        
        Node(Key key, Value value): key(key), value(value),
                                    left(nullptr), right(nullptr),
                                    height(1) {}
    };
public:
    AVLTree(Comparator comp): root(nullptr), node_count(0), comp(comp) {}
    
    ~AVLTree() {
        delete root;
    }
    
    Value* find(const Key& key) {
        return find_aux(key, root);
    }
    
private:
    Node* root;
    size_t node_count;
    
    Comparator comp;
    
    Value* find_aux(const Key& key, Node* node) {
        if (!node) {
            return nullptr;
        }
        
        int res = comp(key, node->key);
        if (res == -1) {
            return find_aux(key, node->left);
        } else if (res == 1) {
            return find_aux(key, node->right);
        }
        return &node->value;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
