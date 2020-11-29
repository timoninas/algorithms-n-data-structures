#include <iostream>
#include <stack>
#include <istream>
#include <sstream>


template <class T>
struct DefaultComparator {
    bool operator() (const T& l, const T& r) const {
        return l < r;
    }
};

template<> struct DefaultComparator<std::string> {
    bool operator() (const std::string& l, const std::string& r) const {
        int left = 0;
        int right = 0;
        for (int i = 0; i < l.size(); i++) {
            left += l[i];
        }
        for (int i = 0; i < r.size(); i++) {
            right += r[i];
        }
        return l < r;
    }
};

template<class T>
struct Node {
    T value;
    
    Node* left;
    Node* right;
    
    Node(T value): value(value), left(nullptr), right(nullptr) { }
};

template<class T, class Comparator = DefaultComparator<T>>
class BinaryTree {
    
public:
    BinaryTree(Comparator comparator = DefaultComparator<T>()): root(nullptr) { }
    
    ~BinaryTree() {
        std::stack<Node<T>*> stack;
        if (root) {
            stack.push(root);
        }
        
        root = nullptr;
        
        while(!stack.empty()) {
            Node<T>* poped = stack.top();
            stack.pop();
            
            if (poped->left != nullptr) {
                stack.push(poped->left);
            }
            if (poped->right != nullptr) {
                stack.push(poped->right);
            }
            delete poped;
        }
    }
    
    void add(const T& value) {
        if (!root) {
            root = new Node<T>(value);
            return;
        }
        
        Node<T>* current = root;
        while(current) {
            if (current->value <= value) {
                if (current->right == nullptr) {
                    current->right = new Node<T>(value);
                    break;
                } else {
                    current = current->right;
                }
            } else {
                if (current->left == nullptr) {
                    current->left = new Node<T>(value);
                    break;
                } else {
                    current = current->left;
                }
            }
        }
    }
    
    void in_order(void(*callback)(Node<T>*)) {
        if (!root) return;
        
        std::stack<Node<T>*> stack;
        stack.push(root);
        bool onlyLeft = true;
        
        while(!stack.empty()) {
            Node<T>* poped = stack.top();
            
            if (onlyLeft) {
                if (poped->left == nullptr) {
                    onlyLeft = false;
                } else {
                    stack.push(poped->left);
                }
            } else {
                stack.pop();
                callback(poped);
                if (poped->right != nullptr) {
                    stack.push(poped->right);
                    onlyLeft = true;
                }
            }
        }
    }
    
private:
    Node<T>* root;
};

void print_node_value(Node<int>* node) {
    std::cout << node->value << " ";
}

int run(std::istream& input, std::ostream& output) {
    int size = 0;
    input >> size;
    
    BinaryTree<int> tree;
    
    for (int i = 0; i < size; i++) {
        int number = 0;
        input >> number;
        
        tree.add(number);
    }
    
    tree.in_order(print_node_value);
    std::cout << std::endl;
    
    return 0;
}

// Выведите элементы в порядке in-order (слева направо)
int main(int argc, const char * argv[]) {
    //       5
    //    2     6
    //  1   3
            
    // in-order -> 1 2 3 5 6
    
    return run(std::cin, std::cout);
}

// Input
// 10
// 9
// 10
// 4
// 3
// 2
// 7
// 8
// 5
// 1
// 6

// Output
// 1 2 3 4 5 6 7 8 9 10
