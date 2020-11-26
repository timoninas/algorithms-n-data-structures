#include <istream>
#include <sstream>
#include <iostream>

#include <string>
#include <vector>
#include <assert.h>

using std::string;

template<class T> struct HashFunc;

template<> struct HashFunc<int> {
    size_t operator() (const int& key) {
        return key;
    }
};

template<> struct HashFunc<std::string> {
    size_t operator() (const std::string& key) {
        size_t hash = 0;
        int a = 37;
        for(int i = 0; i < key.size(); i++) {
            hash = (hash * a + key[i]);
        }
        return hash;
    }
};

static constexpr size_t BUCKETS_COUNT[] = {
        7, 17, 37, 73, 149, 251, 509, 1021, 2027, 5003, 10837, 22073, 100003, 1000000
};

template <class Key, class Value>
struct Node {
    Key key;
    Value value;

    // -1 - deleted
    //  0 - free
    //  1 - not free
    int status;

    void set(const Key& key, const Value& value, int8_t status) {
        this->key = key;
        this->value = value;
        this->status = status;
    }
    
    Node() {
        status = 0;
    }
};

template <class Key, class Value, class Hash = HashFunc<Key>>
class HashTable {
public:
    explicit HashTable(Hash hash = Hash()): buckets(0), buckets_count(0), index_idx(-1), items_count(0), hash(hash) { }
    
    ~HashTable() {
        buckets.clear();
    }

    bool insert(const Key& key, const Value& value) {
        if (!buckets.size() || 3 * buckets_count < 4 * items_count) {
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

//        std::cout << "\ninsert key = " << key << "; value = " << value << std::endl;
//        std::cout << "items_count = " << items_count << std::endl;
        return true;
    }

    bool find(const Key& key) {
        for (int i = 0; i < buckets.size(); i++) {
            size_t index = hash_double(key, i);
            
            if (buckets[index].status == 1 && buckets[index].key == key) {
                return true;
            } else if (buckets[index].status == 0) {
                break;
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
                break;
            }
        }
        return false;
    }

private:
    std::vector<Node<Key, Value>> buckets;
    size_t buckets_count;
    size_t items_count;

    size_t index_idx;

    Hash hash;

    void grow() {
        std::vector<Node<Key, Value>> old_buckets = buckets;
        buckets_count = BUCKETS_COUNT[++index_idx];
        buckets = std::vector<Node<Key, Value>>(buckets_count);
        items_count = 0;
        
//        std::cout << "buckets_count = " << buckets_count << std::endl;
//        std::cout << "items_count = " << items_count << std::endl;
        
        for (int i = 0; i < old_buckets.size(); i++) {
            if (old_buckets[i].status == 1) {
                insert(old_buckets[i].key, old_buckets[i].value);
            }
        }
        
//        std::cout << std::endl;
//        std::cout << "buckets_count = " << buckets_count << std::endl;
//        std::cout << "items_count = " << items_count << std::endl;
    }

    size_t hash_double(const Key& key, int iteration) {
        size_t size = BUCKETS_COUNT[index_idx];
        size_t hash_value1 = hash(key) % size;
        size_t hash_value2 = (hash(key) + 1) % size;
        return (hash_value1 + hash_value2 * (1 + iteration)) % size;
    }
};

int run(std::istream& input, std::ostream& output) {
    HashTable<string, string> hash;
    
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
        for (int i = 0; i < 70000; i++) {
            sstr_input << operation << " "<< std::to_string(i) << std::endl;
        }
        
        operation = "-";
        for (int i = 0; i < 70000; i++) {
            sstr_input << "?" << " " << std::to_string(i) << std::endl;
            sstr_input << operation << " "<< std::to_string(i) << std::endl;
            sstr_input << "?" << " " << std::to_string(i) << std::endl;
        }
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
//        assert(sstr_output.str() == "1\n");
        std::cout << sstr_output.str() << std::endl;
    }
}


int main(int argc, const char * argv[]) {
//    testLogic();
//    std::cout << "TEST PASSED" << std::endl;
//    return 0;
    
    return run(std::cin, std::cout);
}

