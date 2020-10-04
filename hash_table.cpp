#include <algorithm>
#include <iostream>

typedef std::string Key;
template <typename T> T *begin(std::pair<T *, T *> const &p) { return p.first; }
template <typename T> T *end(std::pair<T *, T *> const &p) { return p.second; }

///////////////////////////////
struct Value {                //struct for value hash_table
  unsigned age = 0;
  unsigned weight = 0;
  Value(const Value &v) {     //copy constructor
    age = v.age;
    weight = v.weight;
  }

  Value(int a, int b) {       //constructor with parameter
    age = a;
    weight = b;
  }
  Value() = default;          //default constructor

  friend bool operator==(const Value &a, const Value &b) {
    return a.age == b.age && a.weight == b.weight;
  }
};

//////////////////////////////////////////////////
class ListOfValues { 
public:
  ListOfValues(const Key &k, const Value &v) {  //constructor with parameter
    key = k;
    value = v;
  }
  ListOfValues(const ListOfValues &W) {         //copy constructor
    key = W.key;
    value = W.value;
  }

  const Key &getKey() const { return key; }     //the "key" field must be unavailable for editing
  Value &getValue() { return value; }
  ListOfValues *getNext() { return next; }
  void setNext(ListOfValues *n) { next = n; }
private:
  Key key;
  Value value{};
  ListOfValues *next = nullptr;
};

/////////////////////////////////////////////////////
class HashTable {
  constexpr static int kBeginTableSize = 2;
  constexpr static int IncreaseFactor = 2;

public:
  HashTable() {                              //default constructor
    H = new ListOfValues *[capacity];
    std::fill(&H[0], &H[capacity], nullptr);
  }
  ~HashTable() {                             //simple destructor
    clear();
    delete[] H;
  }

  HashTable(const HashTable &b) {            //copy constructor
    capacity = b.capacity;
    H = new ListOfValues *[capacity];
    std::fill(&H[0], &H[capacity], nullptr);
    for (auto bpos : std::make_pair(b.H, b.H + capacity)) {
      for (; bpos; bpos = bpos->getNext()) {
        insert(bpos->getKey(), bpos->getValue());
      }
    }
  }

  void clear() {
    for (int i = 0; i < capacity; ++i) {
      if (H[i]) {
        auto *ptr = H[i]->getNext();         //remove head element
        delete H[i];
        size_--;
        H[i] = nullptr;
        while (ptr) {                        //remove following elements
          auto *p = ptr->getNext();
          delete ptr;
          size_--;
          ptr = p;
        }
      }
    }
  }

  void swap(HashTable &b) {                  //swap all private fields of the table
    std::swap(size_, b.size_);
    std::swap(H, b.H);
    std::swap(capacity, b.capacity);
  }

  HashTable &operator=(const HashTable &b) {
    if (*this == b)                         //do not copy the same element
      return *this;
    clear();
    delete[] H;                             //remove "this" and copy "b"
    capacity = b.capacity;
    H = new ListOfValues *[capacity];
    std::fill(&H[0], &H[capacity], nullptr);
    for (auto bpos : std::make_pair(b.H, b.H + capacity)) {
      for (; bpos; bpos = bpos->getNext()) {
        insert(bpos->getKey(), bpos->getValue());
      }
    }
    return *this;
  }

  bool erase(const Key &k) {
    const int key = hash(k);
    if (H[key] == nullptr)       //if the required key is missing
      return false;
    if (H[key]->getKey() == k) { //if the required key is in the head
      auto *p = H[key];
      H[key] = H[key]->getNext();
      delete p;
      size_--;
      return true;
    }                             //search for the required key in the list
    for (auto *ptr = H[key]; ptr->getNext(); ptr = ptr->getNext()) {
      if (ptr->getNext()->getKey() == k) {
        auto *p = ptr->getNext();
        ptr->setNext(ptr->getNext()->getNext());
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
    if (H[key] == nullptr) {     //if there is no element with such a key
      H[key] = V;
      size_++;
      return true;
    }
    auto *ptr = H[key];          //insert an element at the end of the list, if elements with such a key exist
    for (; ptr->getNext(); ptr = ptr->getNext()) {
    }
    ptr->setNext(V);
    size_++;
    return true;
  }

  bool contains(const Key &k) const {
    const int key = hash(k);
    if (H[key] == nullptr)                              //if there is no element with such a key
      return false;
    for (auto pos : std::make_pair(H, H + capacity)) {  //search for the required key in the list
      for (; pos; pos = pos->getNext()) {
        if (pos->getKey() == k)
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
    if (H[key] == nullptr) {   //if there is no element with such a key
      throw std::exception();
    }
    auto pos = H[key];         //search for the required key in the list
    for (; pos; pos = pos->getNext()) {
      if (pos->getKey() == k)
        return pos->getValue();
    }
    throw std::exception();
  }
  const Value &at(const Key &k) const {
    const int key = hash(k);
    if (H[key] == nullptr)        //if there is no element with such a key
      throw std::exception();
    auto pos = H[key];            //search for the required key in the list
    for (; pos; pos = pos->getNext()) {
      if (pos->getKey() == k)
        return pos->getValue();
    }
    throw std::exception();
  }

  size_t size() const { return size_; }
  bool empty() const { return size_ == 0; }

  friend bool operator==(const HashTable &a, const HashTable &b) {
    if (a.size() != b.size())
      return false;
    for (auto pos : std::make_pair(a.H, a.H + a.capacity)) { //each element of table a must be in table b
      for (; pos; pos = pos->getNext()) {
        if (!b.contains(pos->getKey()))
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

  void resize() {
    size_ = 0;
    int old_tsize = capacity;
    capacity *= IncreaseFactor;
    auto _H = new ListOfValues *[capacity];                //create a new array 2 times larger
    std::fill(&_H[0], &_H[capacity], nullptr);
    std::swap(H, _H);
    for (auto bpos : std::make_pair(_H, _H + old_tsize)) { //add all elements of the old array to the new one
      for (; bpos; bpos = bpos->getNext()) {
        insert(bpos->getKey(), bpos->getValue());
      }
    }
    for (int i = 0; i < old_tsize; ++i) {                  //delete old array
      if (_H[i]) {
        auto *ptr = _H[i]->getNext();
        delete _H[i];
        while (ptr) {
          auto *p = ptr;
          ptr = ptr->getNext();
          delete p;
        }
      }
    }
    delete[] _H;
  }
  int hash(const Key &k) const { //hash function
    const int TS = capacity;
    int p = 0;
    for (const auto &i : k) {
      p += i;
    }
    return p % TS;
  }
  bool is_almost_full() { return double(size_) / capacity > 0.75; }
};
