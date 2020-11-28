#include <iostream>
#include <istream>
#include <sstream>

#include <assert.h>
#include <string>
#include <vector>

#define INIT_SIZE 8

#define PRIME_NUM1 79
#define PRIME_NUM2 101


// MARK:- HashFunc
template<class T> struct HashFunc;

template<> struct HashFunc<int> {
    size_t operator() (const int& key, const int& simpleNum) {
        return key;
    }
};

template<> struct HashFunc<std::string> {
    size_t operator() (const std::string& key, const int& simpleNum) {
        size_t hash = 0;
        int a = simpleNum;
        for(int i = 0; i < key.size(); i++) {
            hash = (hash * a + key[i]);
        }
        return hash;
    }
};

// MARK:- Node
template <class Key, class Value>
struct Node {
    Key key;
    Value value;

    // -1 - deleted
    //  0 - free
    //  1 - not free
    int status;

    void set(const Key& key, const Value& value, int status) {
        this->key = key;
        this->value = value;
        this->status = status;
    }
    
    Node() {
        key = "";
        value = "";
        status = 0;
    }
};

// MARK:- HashTable
template <class Key, class Value, class Hash = HashFunc<Key>>
class HashTable {
public:
    // MARK: Public Methods
    explicit HashTable(Hash hash = Hash()): buckets(0), items_count(0), hash(hash) {
        buckets_count = INIT_SIZE;
        for (int i = 0; i < buckets_count; i++) {
            buckets.push_back(Node<Key, Value>());
        }
    }
    
    ~HashTable() {
        buckets.clear();
    }

    bool insert(const Key& key, const Value& value) {
        if (!buckets.size() || (3 * buckets_count) <  (4 * items_count)) {
            grow();
        }
        
        for (int i = 0; i < buckets.size(); i++) {
            size_t index = hash_double(key, i);
            
            if (buckets[index].status == 1 && buckets[index].key == key) {
                return false;
            } else if (buckets[index].status != 1) {
                buckets[index].set(key, value, 1);
                items_count++;
                break;
            }
        }
        return true;
    }

    bool find(const Key& key) {
        for (int i = 0; i < buckets.size(); i++) {
            size_t index = hash_double(key, i);
            
            if (buckets[index].status == 1 && buckets[index].key == key) {
                return true;
            } else if (buckets[index].status == 0) {
                return false;
            }
        }
        return false;
    }

    bool remove(const Key& key) {
        for (int i = 0; i < buckets.size(); i++) {
            size_t index = hash_double(key, i);
            
            if (buckets[index].status == 1 && buckets[index].key == key) {
                buckets[index].status = -1;
                items_count--;
                return true;
            } else if (buckets[index].status == 0) {
                return false;
            }
        }
        return false;
    }

private:
    // MARK: Properties
    std::vector<Node<Key, Value>> buckets;
    size_t buckets_count;
    size_t items_count;

    Hash hash;

    // MARK: Private Methods
    void grow() {
        std::vector<Node<Key, Value>> old_buckets = buckets;
        buckets_count *= 2;
        buckets = std::vector<Node<Key, Value>>(0);
        items_count = 0;
        
        for (int i = 0; i < buckets_count; i++) {
            buckets.push_back(Node<Key, Value>());
        }
        
        for (int i = 0; i < old_buckets.size(); i++) {
            if (old_buckets[i].status == 1) {
                insert(old_buckets[i].key, old_buckets[i].value);
            }
        }
    }

    size_t hash_double(const Key& key, int iteration) {
        size_t size = buckets_count;
        size_t hash_value1 = hash(key, PRIME_NUM1);
        size_t hash_value2 = 2 * hash(key, PRIME_NUM2) + 1;
        return (hash_value1 + hash_value2 * iteration) % size;
    }
};

int run(std::istream& input, std::ostream& output) {
    HashTable<std::string, std::string> hash;
    
    char operation;
    std::string key;
    
    while (input >> operation >> key) {
            bool res = false;
            switch (operation) {
                case '+':
                    res = hash.insert(key, key);
                    break;
                case '-':
                    res = hash.remove(key);
                    break;
                case '?':
                    res = hash.find(key);
                    break;
                default:
                    return 1;
            }
            if (res) {
                output << "OK" << std::endl;
            } else {
                output << "FAIL" << std::endl;
            }
        }
    
    return 0;
}

void testLogic() {
    {
        std::stringstream sstr_input;
        std::string operation = "+";
        for (int i = 0; i < 10000; i++) {
            sstr_input << operation << " "<< std::to_string(i) << std::endl;
        }

        operation = "-";
        for (int i = 0; i < 10000; i++) {
            sstr_input << "?" << " " << std::to_string(i) << std::endl;
            sstr_input << operation << " "<< std::to_string(i) << std::endl;
            sstr_input << "?" << " " << std::to_string(i) << std::endl;
        }
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
    }
    {
        std::stringstream sstr_input;
        for (int i = 0; i < 2; i++) {
            sstr_input << "?" << " "<< std::to_string(i) << std::endl;
            sstr_input << "+" << " "<< std::to_string(i) << std::endl;
            sstr_input << "?" << " "<< std::to_string(i) << std::endl;
        }

        for (int i = 0; i < 2; i++) {
            sstr_input << "-" << " "<< std::to_string(i) << std::endl;
            sstr_input << "?" << " "<< std::to_string(i) << std::endl;

        }
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "FAIL\nOK\nOK\nFAIL\nOK\nOK\nOK\nFAIL\nOK\nFAIL\n");
        std::cout << sstr_output.str() << std::endl;
    }
    {
        std::stringstream sstr_input;
        sstr_input << "?" << " " << "123" << std::endl;
        sstr_input << "+" << " " << "123" << std::endl;
        sstr_input << "+" << " " << "123" << std::endl;
        sstr_input << "?" << " " << "123" << std::endl;
        sstr_input << "-" << " " << "123" << std::endl;
        sstr_input << "?" << " " << "123" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "FAIL\nOK\nFAIL\nOK\nOK\nFAIL\n");
        std::cout << sstr_output.str() << std::endl;
    }
    {
        std::stringstream sstr_input;
        sstr_input << "+" << " " << "a" << std::endl;
        sstr_input << "+" << " " << "ab" << std::endl;
        sstr_input << "+" << " " << "abc" << std::endl;
        sstr_input << "+" << " " << "abc1" << std::endl;
        sstr_input << "+" << " " << "abc2" << std::endl;

        sstr_input << "-" << " " << "a" << std::endl;

        sstr_input << "+" << " " << "abcd" << std::endl;

        sstr_input << "-" << " " << "ab" << std::endl;

        sstr_input << "+" << " " << "abcde" << std::endl;
        sstr_input << "+" << " " << "abcdef" << std::endl;

        sstr_input << "?" << " " << "a" << std::endl;
        sstr_input << "+" << " " << "a" << std::endl;
        sstr_input << "?" << " " << "a" << std::endl;
        sstr_input << "+" << " " << "a" << std::endl;

        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        std::cout << sstr_output.str() << std::endl;
        assert(sstr_output.str() == "OK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nFAIL\nOK\nOK\nFAIL\n");
        std::cout << sstr_output.str() << std::endl;
    }
    {
        std::stringstream sstr_input;

        sstr_input << "+" << " " << "%%%%%%" << std::endl;
        sstr_input << "+" << " " << "JJJ" << std::endl;
        sstr_input << "+" << " " << "%%JJ" << std::endl;
        sstr_input << "+" << " " << "J%%J" << std::endl;
        sstr_input << "?" << " " << "J%%J" << std::endl;
        sstr_input << "+" << " " << "JJ%%" << std::endl;
        sstr_input << "+" << " " << "J%%%%" << std::endl;
        sstr_input << "+" << " " << "%%%%J" << std::endl;

        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        std::cout << sstr_output.str() << std::endl;
        assert(sstr_output.str() == "OK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n");
        std::cout << sstr_output.str() << std::endl;
    }
}

int main(int argc, const char * argv[]) {
//    testLogic();
//    std::cout << "TEST PASSED" << std::endl;
//    return 0;
    
    return run(std::cin, std::cout);
}
