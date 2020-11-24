#pragma once
#include <iostream>
typedef std::string Key;

struct Value {
    unsigned age = 0;
    unsigned weight = 0;
    friend bool operator==(const Value &a, const Value &b) {
        return a.age == b.age && a.weight == b.weight;
    }
};


class HashTable {
public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable &b);
    void clear();
    void swap(HashTable &b);
    HashTable &operator=(const HashTable &b);
    bool erase(const Key &k);
    bool insert(const Key &k, const Value &v);
    bool contains(const Key &k) const;
    Value &operator[](const Key &k);
    Value &at(const Key &k);
    const Value &at(const Key &k) const;
    size_t size() const;
    bool empty() const;
    friend bool operator==(const HashTable &a, const HashTable &b);
    friend bool operator!=(const HashTable &a, const HashTable &b);

private:
    struct ListOfValues {
        Key key;
        Value value{};
        ListOfValues *next = nullptr;
    };
    constexpr static size_t kBeginTableSize = 2;
    constexpr static int IncreaseFactor = 2;
    constexpr static double FillFactor = 0.75;
    ListOfValues **H;
    size_t size_ = 0;
    size_t capacity = kBeginTableSize;
    void resize();
    size_t hash(const Key &k) const;
    bool is_almost_full() const;
    static const Key &getKey(const ListOfValues &v) { return v.key; }//the "key" field must be unavailable for editing
    static Value &getValue(ListOfValues &v) { return v.value; }
    static ListOfValues *getNext(ListOfValues &v) { return v.next; }
    void setNext(ListOfValues &v, ListOfValues *n) { v.next = n; }
};
