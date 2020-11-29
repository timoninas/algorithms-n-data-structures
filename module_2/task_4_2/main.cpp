
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
        return find_aux(root, key);
    }
    
    void insert(const Key& key, const Value& value) {
        root = insert_aux(root, key, value);
    }
    
    void erase(const Key& key) {
        root = erase_aux(root, key);
    }
    
private:
    Node* root;
    size_t node_count;
    
    Comparator comp;
    
    Value* find_aux(Node* node, const Key& key) {
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
    
    Node* insert_aux(Node* node, const Key& key, const Value& value) {
        if (!node) {
            node_count++;
            return new Node(key, value);
        }
        
        int res = comp(key, node->key);
        if (res == -1) {
            node->left =  find_aux(key, node->left);
        } else if (res == 1) {
            node->right =  find_aux(key, node->right);
        }
        return balance(node);
    }
    
    Node* erase_aux(Node* node, const Key& key) {
        if (!node) {
            return nullptr;
        }
        
        int res = comp(key, node->key);
        if (res == -1) {
            node->left =  find_aux(key, node->left);
        } else if (res == 1) {
            node->right =  find_aux(key, node->right);
        } else {
            Node* left = node->left;
            Node* right = node->right;
            
            delete node;
            
            if (node->right == nullptr) {
                return left;
            }
            
            Node* min_node = find_and_remove_min(right);
            min_node->right = right;
            min_node->left = left;
            
            return balance(min_node);
        }
        
        return balance(node);
    }
    
    Node* find_and_remove_min(Node* node) {
        Node* curNode = node;
        while(curNode->left) {
            curNode = curNode->left;
        }
        
        Node* finded_min = curNode; // 5
        
        curNode = node;
        while(curNode->left) {
            if (curNode->left->key == finded_min->key) {
                break;
            }
            curNode = curNode->left;
        }
        
        curNode->left = finded_min->right;
        finded_min->left = nullptr;
        finded_min->right = nullptr;
        
        return finded_min;
    }
    
    Node* balance(Node* node) {
        return nullptr;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
