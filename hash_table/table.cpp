#include "table.h"
#include <algorithm>
#include <iostream>

typedef std::string Key;
template<typename T>
T *begin(std::pair<T *, T *> const &p) { return p.first; }
template<typename T>
T *end(std::pair<T *, T *> const &p) { return p.second; }

HashTable::HashTable() {//default constructor
    H = new ListOfValues *[capacity];
    std::fill(H, H + capacity, nullptr);
}

HashTable::~HashTable() {//simple destructor
    clear();
    delete[] H;
}

HashTable::HashTable(const HashTable &b) {//copy constructor
    capacity = b.capacity;
    H = new ListOfValues *[capacity];
    std::fill(H, H + capacity, nullptr);
    for (auto bpos : std::make_pair(b.H, b.H + capacity)) {
        for (; bpos; bpos = getNext(*bpos)) {
            insert(getKey(*bpos), getValue(*bpos));
        }
    }
}

void HashTable::clear() {
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

void HashTable::swap(HashTable &b) {//swap all private fields of the table
    std::swap(size_, b.size_);
    std::swap(H, b.H);
    std::swap(capacity, b.capacity);
}

HashTable &HashTable::operator=(const HashTable &b) {
    if (this == &b)//do not copy the same element
        return *this;
    clear();
    delete[] H;//remove "this" and copy "b"
    capacity = b.capacity;
    H = new ListOfValues *[capacity];
    std::fill(H, H + capacity, nullptr);
    for (auto bpos : std::make_pair(b.H, b.H + capacity)) {
        for (; bpos; bpos = getNext(*bpos)) {
            insert(getKey(*bpos), getValue(*bpos));
        }
    }
    return *this;
}

bool HashTable::erase(const Key &k) {
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

bool HashTable::insert(const Key &k, const Value &v) {
    if (is_almost_full())
        resize();
    if (contains(k))
        return false;
    const int key = hash(k);
    auto *V = new ListOfValues({k, v, nullptr});
    if (H[key] == nullptr) {//if there is no element with such a key
        H[key] = V;
        size_++;
        return true;
    }
    auto *ptr = H[key];//insert an element at the end of the list, if elements with such a key exist
    for (; getNext(*ptr); ptr = getNext(*ptr)) {
    }
    setNext(*ptr, V);
    size_++;
    return true;
}

bool HashTable::contains(const Key &k) const {
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

Value &HashTable::operator[](const Key &k) {
    if (!contains(k))
        insert(k, Value());
    return at(k);
}

Value &HashTable::at(const Key &k) {
    const int key = hash(k);
    if (H[key] == nullptr) {//if there is no element with such a key
        throw std::runtime_error("NO SUCH KEY EXISTS");
    }
    auto pos = H[key];//search for the required key in the list
    for (; pos; pos = getNext(*pos)) {
        if (getKey(*pos) == k)
            return getValue(*pos);
    }

    throw std::runtime_error("NO SUCH KEY EXISTS");
}
const Value &HashTable::at(const Key &k) const {

    const int key = hash(k);
    if (H[key] == nullptr) {//if there is no element with such a key
        throw std::runtime_error("NO SUCH KEY EXISTS");
    }
    auto pos = H[key];//search for the required key in the list
    for (; pos; pos = getNext(*pos)) {
        if (getKey(*pos) == k) {
            return getValue(*pos);
        }
    }
    throw std::runtime_error("NO SUCH KEY EXISTS");
}

size_t HashTable::size() const { return size_; }
bool HashTable::empty() const { return size_ == 0; }

bool operator==(const HashTable &a, const HashTable &b) {
    if (a.size() != b.size())
        return false;
    for (auto pos : std::make_pair(a.H, a.H + a.capacity)) {//each element of table a must be in table b
        for (; pos; pos = HashTable::getNext(*pos)) {
            if (!b.contains(HashTable::getKey(*pos)))
                return false;
        }
    }
    return true;
}

bool operator!=(const HashTable &a, const HashTable &b) {
    return !(a == b);
}


void HashTable::resize() {
    size_ = 0;
    int old_tsize = capacity;
    capacity *= IncreaseFactor;
    auto _H = new ListOfValues *[capacity];//create a new array 2 times larger
    std::fill(_H, _H + capacity, nullptr);
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
size_t HashTable::hash(const Key &k) const {//hash function
    const size_t TS = capacity;
    size_t p = 0;
    for (const auto &i : k) {
        p += i;
    }
    return p % TS;
}
bool HashTable::is_almost_full() const { return double(size_) / capacity > FillFactor; }
