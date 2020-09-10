#include <iostream>
#include <algorithm>
using namespace std;
typedef string Key;
#define HASHTABLESIZE 13


struct Value {
    unsigned age = 0;
    unsigned weight = 0;
    Value(const Value& v){
        age = v.age;
        weight = v.weight;
    }
    Value(int a, int b){
        age = a;
        weight = b;
    }
    Value() = default;
};

class ListOfValues {
private:
    Key key;
    Value value{};
    ListOfValues *next;
public:
    ListOfValues(const int& k, const Value& v) {
        key = k;
        value = v;
        next = nullptr;
    }
    ListOfValues(const ListOfValues& W) {
        key = W.key;
        value = W.value;
        next = nullptr;
    }
    Key getKey() {
        return key;
    }
    Value& getValue() {
        return value;
    }
    void setValue(const Value& v) {
        value = v;
    }
    ListOfValues *getNext() {
        return next;
    }
    void setNext(ListOfValues *n) {
        next = n;
    }
};



class HashTable{
private:
    ListOfValues* H[HASHTABLESIZE]{};
    int Size = 0;
    static int hash(const Key& k){
        int p = 0;
        for(const auto& i : k){
            p += i;
        }
        return p % HASHTABLESIZE;
    }
public:
    HashTable(){
        for(auto & i : H)
            i = nullptr;
    }
    ~HashTable(){
        for(auto & i : H){
            if(!i){
                delete [] i;
            }
        }
    }

    HashTable(const HashTable& b){
        for(int i = 0; i < HASHTABLESIZE; ++i){
            H[i] = b.H[i];
        }
    }

// Очищает контейнер.
    void clear(){
        Size = 0;
        for(auto& i : H){
            delete [] i;
        }
    }
    // Обменивает значения двух хэш-таблиц.
    // Подумайте, зачем нужен этот метод, при наличии стандартной функции
    // std::swap.
    void swap(HashTable& b){
        std::swap(Size, b.Size);
        std::swap(H, b.H);
    }

    HashTable& operator=(const HashTable& b){
        clear();
        Size = b.Size;
        for(auto i : b.H){
            if(i){
                insert(i->getKey(), i->getValue());
                auto* ptr = i;
                while(ptr -> getNext()){
                    insert(ptr->getKey(), ptr->getValue());
                    ptr = ptr -> getNext();
                }
            }
        }
        return *this;
    }



    // Удаляет элемент по заданному ключу.
    bool erase(const Key& k){
        const int key = hash(k);
        if(H[key] == nullptr)
            return false;
        else {
            if(H[key]->getKey() == k){
                auto* p = H[key];
                H[key] =H[key]->getNext();
                delete p;
                Size--;
                return true;
            }
        }
        auto *ptr = H[key];
        while(ptr -> getNext()){
            if(ptr -> getNext() -> getKey() == k){
                
                return true;
            }
            ptr = ptr -> getNext();
        }
        return false;
    }
    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, const Value& v){
        if(contains(k))
            return false; //если такой ключ уже существует
        const int key = hash(k);
        auto* V = new (nothrow) ListOfValues(key, v);
        if(!V) return false;
        if(H[key] == nullptr){
            H[key] = V;
            Size++;
            return true;
        }
        auto *ptr = H[key];
        while(ptr -> getNext()){
            ptr = ptr -> getNext();
        }
        ptr -> setNext(V);
        Size++;
        return true;
    }

    // Проверка наличия значения по заданному ключу.
    bool contains(const Key& k) const{
        const int key = hash(k);
        if(H[key] == nullptr)
            return false;
        else {
            if(H[key]->getKey() == k)
                return true;
        }
        auto *ptr = H[key];
        while(ptr -> getNext()){
            if(ptr -> getNext() -> getKey() == k)
                return true;
            ptr = ptr -> getNext();
        }
        return false;
    }

    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнере, следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него.
    Value& operator[](const Key& k){
        if(!contains(k))
            insert(k, {0, 0});
        return H[hash(k)]->getValue();
    }

    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value& at(const Key& k){
        if(!contains(k)) throw exception();
        return H[hash(k)]->getValue();
    }
    const Value& at(const Key& k) const{
        if(!contains(k)) throw exception();
        return H[hash(k)]->getValue();
    }

    size_t size() const{
        return Size;
    }
    bool empty() const{
        return Size;
    }

    friend bool operator==(const HashTable& a, const HashTable& b){
        
    }

    friend bool operator!=(const HashTable& a, const HashTable& b);
};


int main() {
    HashTable h;
    h.insert("peter", {5, 10});
    cout << h.size() << endl;
    h.insert("bob", {2, 7});
    if(h.insert("peter", {5, 10}))
        cout << "yes" << endl;
    else cout << "no" << endl;
    cout << h.size() << endl;
    h.clear();
    cout << h.size() << endl;
    return 0;
}
