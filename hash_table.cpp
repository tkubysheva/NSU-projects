#include <iostream>
#include <algorithm>
using namespace std;
typedef string Key;


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
    ListOfValues(const Key& k, const Value& v) {
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
    static const int begin_table_size = 2; // начальный размер нашей таблицы
    int table_size;
private:
    ListOfValues** H;
    int Size = 0;
    int hash(const Key& k) const{
        const int TS = table_size;
        int p = 0;
        for(const auto& i : k){
            p += i;
        }
        return p % TS;
    }
    bool fill_factor(){
        return double(Size)/table_size > 0.75;
    }
public:
    HashTable(){
        table_size = begin_table_size;
        H = new ListOfValues* [table_size];
        for(int i = 0; i < table_size; ++i)
            H[i] = nullptr;
    }
    ~HashTable(){
        clear();
    }

    HashTable(const HashTable& b){
        table_size = b.table_size;
        H = new ListOfValues* [table_size];
        for(int i = 0; i < table_size; ++i)
            H[i] = nullptr;
        for(int i = 0; i < table_size; ++i){
            if(b.H[i]){
                insert(b.H[i]->getKey(), b.H[i]->getValue());
                auto* ptr = b.H[i];
                while(ptr -> getNext()){
                    insert(ptr-> getNext()->getKey(), ptr-> getNext()->getValue());
                    ptr = ptr -> getNext();
                }
            }
        }
    }

    void resize() {
        cout << "RESIZE" << endl;
        int old_tsize = table_size;
        table_size *= 2;
        auto _H = new ListOfValues* [table_size];
        for(int i = 0; i < table_size; ++i)
            _H[i] = nullptr;
        std::swap(H, _H);
        for(int i = 0; i < old_tsize; ++i){
            if(_H[i]){
                cout << "1 ";
                insert(_H[i]->getKey(), _H[i]->getValue());
                auto* ptr = _H[i];
                while(ptr -> getNext()){
                    insert(ptr-> getNext()->getKey(), ptr-> getNext()->getValue());
                    ptr = ptr -> getNext();
                }
            }
        }
        cout << endl;

      /*  for(int i = 0; i < old_tsize; ++i){
            if(_H[i]){
                auto* ptr = _H[i]->getNext();
                auto* p = _H[i];
                _H[i] = _H[i]->getNext();
                delete p;
                while(ptr){
                    p = ptr ->getNext();
                    ptr -> setNext(ptr ->getNext() -> getNext());
                    delete p;
                }
            }
        }               ДОДЕЛАТЬ
        */ 
    }
// Очищает контейнер.
    void clear(){
        for(int i = 0; i < table_size; ++i){
            if(H[i]){
                auto* ptr = H[i]->getNext();
                erase(H[i]->getKey());
                while(ptr){
                    auto* p = ptr -> getNext();
                    erase(ptr->getKey());
                    ptr = p;
                }
            }
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
        for(int i = 0; i < table_size; ++i){
            if(b.H[i]){
                insert(b.H[i]->getKey(), b.H[i]->getValue());
                auto* ptr = b.H[i];
                while(ptr -> getNext()){
                    insert(ptr-> getNext()->getKey(), ptr-> getNext()->getValue());
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
                auto* p = ptr ->getNext();
                ptr -> setNext(ptr ->getNext() -> getNext());
                delete p;
                Size--;
                return true;
            }
            ptr = ptr -> getNext();
        }
        return false;
    }
    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, const Value& v){
        if(fill_factor()) resize();
        if(contains(k))
            return false; //если такой ключ уже существует
        const int key = hash(k);
        auto* V = new (nothrow) ListOfValues(k, v);
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
        return Size == 0;
    }

    friend bool operator==(const HashTable& a, const HashTable& b){
        if(a.size() != b.size()) return false;
        for(int i = 0; i < a.table_size; ++i){
            if(a.H[i] && !b.contains(a.H[i]->getKey())) return false;
        }
        return true;
    }

    friend bool operator!=(const HashTable& a, const HashTable& b){
        return !(a == b);
    }
};


int main() {
    HashTable h;
    h.insert("peter", {15, 160});
    cout << h.size() << endl; //1

    h.insert("bob", {12, 157}); //2//
    h.insert("bbo", {9, 100}); //3//


    if(h.insert("peter", {22, 180}))
        cout << "yes" << endl;
    else cout << "no" << endl; //no
    cout << h.size() << endl; //3

    h.erase("peter");
    cout << h.size() << endl; //2

    if(h.insert("peter", {5, 60}))
        cout << "yes" << endl; //yes
    else cout << "no" << endl;
    cout << h.size() << endl; //3

    h["peter"] = {13, 140};
    cout << "Weight: " << h.at("peter").weight << "; Age: " << h.at("peter").age << endl; //140, 13

    HashTable d = h;
    cout << (h == d) << endl; //1
    cout << d.size() << endl; //3

    d.insert("mary", {80, 155});
    cout << (h == d) << endl; //0
    cout << h.contains("mary") << endl; //0
    HashTable p = h;
    p.insert("rob", {43, 180});
    p.insert("ben", {67, 169});
    h.clear();
    cout << h.empty() << endl; //1
    cout << d.size() << endl; //4
    cout << p.size() << endl; //5
    p.swap(d);
    //swap(p, d) дает неверные результаты для Size
    cout << d.size() << endl; //5
    cout << p.size() << endl; //4
    cout << p.contains("mary") << endl; //1
    cout << d.contains("mary") << endl; //0
    return 0;
}
