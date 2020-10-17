#include <algorithm>
#include <iostream>

typedef std::string Key;
template<typename T>
T *begin(std::pair<T *, T *> const &p) { return p.first; }
template<typename T>
T *end(std::pair<T *, T *> const &p) { return p.second; }

///////////////////////////////
struct Value {//struct for value hash_table
    unsigned age = 0;
    unsigned weight = 0;
    Value(const Value &v) {//copy constructor
        age = v.age;
        weight = v.weight;
    }

    Value(int a, int b) {//constructor with parameter
        age = a;
        weight = b;
    }
    Value() = default;//default constructor

    friend bool operator==(const Value &a, const Value &b) {
        return a.age == b.age && a.weight == b.weight;
    }
};

//////////////////////////////////////////////////
struct ListOfValues {
    ListOfValues(const Key &k, const Value &v) {//constructor with parameter
        key = k;
        value = v;
    }
    ListOfValues(const ListOfValues &W) {//copy constructor
        key = W.key;
        value = W.value;
    }
/*
    const Key &getKey() const { return key; }//the "key" field must be unavailable for editing
    Value &getValue() { return value; }
    ListOfValues *getNext() { return next; }
    void setNext(ListOfValues *n) { next = n; }
*/
    Key key;
    Value value{};
    ListOfValues *next = nullptr;
};

/////////////////////////////////////////////////////
class HashTable {
    constexpr static int kBeginTableSize = 2;
    constexpr static int IncreaseFactor = 2;

public:
    HashTable() {//default constructor
        H = new ListOfValues *[capacity];
        std::fill(&H[0], &H[capacity], nullptr);
    }
    ~HashTable() {//simple destructor
        clear();
        delete[] H;
    }

    HashTable(const HashTable &b) {//copy constructor
        capacity = b.capacity;
        H = new ListOfValues *[capacity];
        std::fill(&H[0], &H[capacity], nullptr);
        for (auto bpos : std::make_pair(b.H, b.H + capacity)) {
            for (; bpos; bpos = getNext(*bpos)) {
                insert(getKey(*bpos), getValue(*bpos));
            }
        }
    }

    void clear() {
        for (int i = 0; i < capacity; ++i) {
            if (H[i]) {
                auto *ptr = getNext(*H[i]);//remove head element
                delete H[i];
                size_--;
                H[i] = nullptr;
                while (ptr) {//remove following elements
                    auto *p = getNext(*ptr);
                    delete ptr;
                    size_--;
                    ptr = p;
                }
            }
        }
    }

    void swap(HashTable &b) {//swap all private fields of the table
        std::swap(size_, b.size_);
        std::swap(H, b.H);
        std::swap(capacity, b.capacity);
    }

    HashTable &operator=(const HashTable &b) {
        if (*this == b)//do not copy the same element
            return *this;
        clear();
        delete[] H;//remove "this" and copy "b"
        capacity = b.capacity;
        H = new ListOfValues *[capacity];
        std::fill(&H[0], &H[capacity], nullptr);
        for (auto bpos : std::make_pair(b.H, b.H + capacity)) {
            for (; bpos; bpos = getNext(*bpos)) {
                insert(getKey(*bpos), getValue(*bpos));
            }
        }
        return *this;
    }

    bool erase(const Key &k) {
        const int key = hash(k);
        if (H[key] == nullptr)//if the required key is missing
            return false;
        if (getKey(*H[key]) == k) {//if the required key is in the head
            auto *p = H[key];
            H[key] = getNext(*H[key]);
            delete p;
            size_--;
            return true;
        }//search for the required key in the list
        for (auto *ptr = H[key]; getNext(*ptr); ptr = getNext(*ptr)) {
            if (getKey(*getNext(*ptr)) == k) {
                auto *p = getNext(*ptr);
                setNext(*ptr, getNext(*getNext(*ptr)));
                delete p;
                size_--;
                return true;
            }
        }
        return false;
    }

    bool insert(const Key &k, const Value &v) {
        if (is_almost_full())
            resize();
        if (contains(k))
            return false;
        const int key = hash(k);
        auto *V = new ListOfValues(k, v);
        if (H[key] == nullptr) {//if there is no element with such a key
            H[key] = V;
            size_++;
            return true;
        }
        auto *ptr = H[key];//insert an element at the end of the list, if elements with such a key exist
        for (;getNext(*ptr); ptr = getNext(*ptr)) {
        }
        setNext(*ptr, V);
        size_++;
        return true;
    }

    bool contains(const Key &k) const {
        const int key = hash(k);
        if (H[key] == nullptr)//if there is no element with such a key
            return false;
        for (auto pos : std::make_pair(H, H + capacity)) {//search for the required key in the list
            for (; pos; pos = getNext(*pos)) {
                if (getKey(*pos) == k)
                    return true;
            }
        }

        return false;
    }

    Value &operator[](const Key &k) {
        if (!contains(k))
            insert(k, Value());
        return at(k);
    }

    Value &at(const Key &k) {
        const int key = hash(k);
        if (H[key] == nullptr) {//if there is no element with such a key
            throw std::exception();
        }
        auto pos = H[key];//search for the required key in the list
        for (; pos; pos = getNext(*pos)) {
            if (getKey(*pos) == k)
                return getValue(*pos);
        }

        throw std::exception();
    }
    const Value &at(const Key &k) const {

        const int key = hash(k);
        if (H[key] == nullptr){//if there is no element with such a key
            throw std::exception();
        }
        auto pos = H[key];//search for the required key in the list
        for (; pos; pos =getNext(*pos)) {
            if (getKey(*pos) == k) {
                return getValue(*pos);
            }
        }
        throw std::exception();
    }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    friend bool operator==(const HashTable &a, const HashTable &b) {
        if (a.size() != b.size())
            return false;
        for (auto pos : std::make_pair(a.H, a.H + a.capacity)) {//each element of table a must be in table b
            for (; pos; pos = getNext(*pos)) {
                if (!b.contains(getKey(*pos)))
                    return false;
            }
        }
        return true;
    }

    friend bool operator!=(const HashTable &a, const HashTable &b) {
        return !(a == b);
    }

private:
    ListOfValues **H;
    int size_ = 0;
    int capacity = kBeginTableSize;

    static const Key &getKey  ( const ListOfValues& v)  { return v.key; }//the "key" field must be unavailable for editing
    static Value &getValue(ListOfValues& v) { return v.value; }
    static ListOfValues *getNext(ListOfValues& v) { return v.next; }
    void setNext(ListOfValues& v, ListOfValues *n) { v.next = n; }

    void resize() {
        size_ = 0;
        int old_tsize = capacity;
        capacity *= IncreaseFactor;
        auto _H = new ListOfValues *[capacity];//create a new array 2 times larger
        std::fill(&_H[0], &_H[capacity], nullptr);
        std::swap(H, _H);
        for (auto bpos : std::make_pair(_H, _H + old_tsize)) {//add all elements of the old array to the new one
            for (; bpos; bpos = getNext(*bpos)) {
                insert(getKey(*bpos), getValue(*bpos));
            }
        }
        for (int i = 0; i < old_tsize; ++i) {//delete old array
            if (_H[i]) {
                auto *ptr = getNext(*_H[i]);
                delete _H[i];
                while (ptr) {
                    auto *p = ptr;
                    ptr = getNext(*ptr);
                    delete p;
                }
            }
        }
        delete[] _H;
    }
    int hash(const Key &k) const {//hash function
        const int TS = capacity;
        int p = 0;
        for (const auto &i : k) {
            p += i;
        }
        return p % TS;
    }
    bool is_almost_full() const { return double(size_) / capacity > 0.75; }
};
