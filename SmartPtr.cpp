#include <iostream>
using namespace std;

struct A {
    A() {
        cout << "Ctor" << endl;
    }
    A(int i) {
        cout << "Int " << i << endl;
    }
    ~A() {
        cout << "Dtor" << endl;
    }
    A(const A&) {
        cout << "Copy" << endl;
    }
    A& operator=(const A&) {
        cout << "assign" << endl;
        return *this;
    }
};

class SmartPtr {
public:
    SmartPtr() = default;
    explicit SmartPtr(A* a) : a_(a), counter(1) {
    }
    ~SmartPtr(){
        if(a_ && counter > 0) {
            if(--counter == 0)
              delete a_;
        }
    }
    A& operator*() {
        return *a_;
    }
    A* operator->() {
        return a_;
    }
    A* release() {  //отдаёт владение указателем
        A *p = a_;
        a_ = nullptr;
        return p;
    }
    void reset(A*x) { //берет владение указат х
            delete a_;
            a_ = x;
    }
    A* get() {
        return a_;
    }

    SmartPtr(SmartPtr& p) {
        a_ = p.a_;
        counter = ++p.counter;
    }
    SmartPtr& operator=(SmartPtr& p) {
        if(this == &p)
            return *this;
        a_ = p.a_;
        counter = ++p.counter;
        return *this;
    }

private:
    A* a_ = nullptr;
    int counter = 0;
};


