#include <algorithm>
#include <iostream>


typedef std::string Key;
template <typename T> T* begin(std::pair<T*, T*> const& p)
{ return p.first; }
template <typename T> T* end(std::pair<T*, T*> const& p)
{ return p.second; }

struct Value {
  unsigned age = 0;
  unsigned weight = 0;
  Value(const Value &v) {
    age = v.age;
    weight = v.weight;
  }

  Value(int a, int b) {
    age = a;
    weight = b;
  }
  Value()= default;

  friend bool operator==(const Value &a, const Value &b) {
    return a.age == b.age && a.weight == b.weight;
  }

};

class ListOfValues {
public:
  ListOfValues(const Key &k, const Value &v) {
    key = k;
    value = v;
  }
  ListOfValues(const ListOfValues &W) {
    key = W.key;
    value = W.value;
  }

  //????????????
  const Key& getKey() const { return key; }
  Value &getValue() { return value; }
  ListOfValues *getNext() { return next; }
  void setNext(ListOfValues *n) { next = n; }

private:
  Key key;
  Value value{};
  ListOfValues *next = nullptr;
};

class HashTable {
  constexpr static int kBeginTableSize = 2;
  constexpr static int IncreaseFactor = 2;
  int hash(const Key &k) const {
    const int TS = capacity;
    int p = 0;
    for (const auto &i : k) {
      p += i;
    }
    return p % TS;
  }
  bool is_almost_full() { return double(size_) / capacity > 0.75; }

public:
  HashTable() {
    H = new ListOfValues *[capacity];
    std::fill(&H[0], &H[capacity], nullptr);
  }
  ~HashTable() {
    clear();
    delete[] H;
  }

  HashTable(const HashTable &b) {
    capacity = b.capacity;
    H = new ListOfValues *[capacity];
    std::fill(&H[0], &H[capacity], nullptr);
    for(auto bpos : std::make_pair(b.H, b.H + capacity)){
      for(; bpos; bpos = bpos -> getNext() ){
        insert(bpos->getKey(), bpos -> getValue());
      }
    }
  }

  void resize() {
    std::cout << "RESIZE" << std::endl;
    size_ = 0;
    int old_tsize = capacity;
    capacity *= IncreaseFactor;
    auto _H = new ListOfValues *[capacity];
    std::fill(&_H[0], &_H[capacity], nullptr);
    std::swap(H, _H);
    for(auto bpos : std::make_pair(_H, _H + capacity)){
      for(; bpos; bpos = bpos -> getNext() ){
        insert(bpos->getKey(), bpos -> getValue());
      }
    }
    std::cout << std::endl;
    for (int i = 0; i < old_tsize; ++i) {
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

  // Очищает контейнер.
  void clear() {
    for (int i = 0; i < capacity; ++i) {
      if (H[i]) {
        auto *ptr = H[i]->getNext();
        delete H[i];
        while (ptr) {
          auto *p = ptr->getNext();
          delete ptr;
          ptr = p;
        }
      }
    }
  }
  // Обменивает значения двух хэш-таблиц.
  // Подумайте, зачем нужен этот метод, при наличии стандартной функции
  // std::swap.
  void swap(HashTable &b) {
    std::swap(size_, b.size_);
    std::swap(H, b.H);
    std::swap(capacity, b.capacity);
  }


  HashTable &operator=(const HashTable &b) {
    if (*this == b)
      return *this;
    clear();
    delete[] H;
    capacity = b.capacity;
    H = new ListOfValues *[capacity];
    std::fill(&H[0], &H[capacity], nullptr);
    for(auto bpos : std::make_pair(b.H, b.H + capacity)){
      for(; bpos; bpos = bpos -> getNext() ){
        insert(bpos->getKey(), bpos -> getValue());
      }
    }
    return *this;
  }

  // Удаляет элемент по заданному ключу.
  bool erase(const Key &k) {
    const int key = hash(k);
    if (H[key] == nullptr)
      return false;
    else {
      if (H[key]->getKey() == k) {
        auto *p = H[key];
        H[key] = H[key]->getNext();
        delete p;
        size_--;
        return true;
      }
    }
    auto *ptr = H[key];
    while (ptr->getNext()) {
      if (ptr->getNext()->getKey() == k) {
        auto *p = ptr->getNext();
        ptr->setNext(ptr->getNext()->getNext());
        delete p;
        size_--;
        return true;
      }
      ptr = ptr->getNext();
    }
    return false;
  }
  // Вставка в контейнер. Возвращаемое значение - успешность вставки.
  bool insert(const Key &k, const Value &v) {
    if (is_almost_full())
      resize();
    if (contains(k))
      return false; //если такой ключ уже существует
    const int key = hash(k);
    auto *V = new ListOfValues(k, v);
    if (H[key] == nullptr) {
      H[key] = V;
      size_++;
      return true;
    }
    auto *ptr = H[key];
    while (ptr->getNext()) {
      ptr = ptr->getNext();
    }
    ptr->setNext(V);
    size_++;
    return true;
  }

  // Проверка наличия значения по заданному ключу.
  bool contains(const Key &k) const {
    const int key = hash(k);
    if (H[key] == nullptr)
      return false;
    for(auto pos : std::make_pair(H, H + capacity)){
      for(; pos; pos = pos -> getNext() ){
        if(pos->getKey() == k)
          return true;
      }
    }
    /*else {
      if (H[key]->getKey() == k)
        return true;
    }
    auto *ptr = H[key];
    while (ptr->getNext()) {
      if (ptr->getNext()->getKey() == k)
        return true;
      ptr = ptr->getNext();
    }*/
    return false;
  }

  // Возвращает значение по ключу. Небезопасный метод.
  // В случае отсутствия ключа в контейнере, следует вставить в контейнер
  // значение, созданное конструктором по умолчанию и вернуть ссылку на него.
  Value &operator[](const Key &k) {
    if (!contains(k))
      insert(k, Value());
    return at(k);
  }

  // Возвращает значение по ключу. Бросает исключение при неудаче.
  Value &at(const Key &k) {
    const int key = hash(k);
    if (H[key] == nullptr){
      throw std::exception();
    }
    auto pos = H[key];
    for(; pos; pos = pos -> getNext() ){
      if(pos->getKey() == k)
        return pos->getValue();
    }
    throw std::exception();
  }
  const Value &at(const Key &k) const {
    const int key = hash(k);
    if (H[key] == nullptr)
      throw std::exception();
    auto pos = H[key];
    for(; pos; pos = pos -> getNext() ){
      if(pos->getKey() == k)
        return pos->getValue();
    }
    throw std::exception();
  }

  size_t size() const { return size_; }
  bool empty() const { return size_ == 0; }

  friend bool operator==(const HashTable &a, const HashTable &b) {
    if (a.size() != b.size())
      return false;
    for (int i = 0; i < a.capacity; ++i) {
      if (a.H[i]) {
        if (!b.contains(a.H[i]->getKey()))
          return false;
        auto *ptr = a.H[i];
        while (ptr->getNext()) {
          if (!b.contains(a.H[i]->getNext()->getKey()))
            return false;
          ptr = ptr->getNext();
        }
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
};

int main() {
  HashTable h,
  p;
  h["key"] = {10, 765};
  p = h;
  std::cout << "Weight: " << h["key"].weight << "; Age: " << h["key"].age
            << std::endl;
  std::cout << h.size() << std::endl;
  h.erase("key");
  std::cout << "Weight: " << h.at("u").weight
            << std::endl;
  std::cout << h.size() << std::endl;
}
