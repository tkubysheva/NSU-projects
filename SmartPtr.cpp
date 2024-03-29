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
    explicit SmartPtr(A* a) : a_(a), counter(new int) {
      *counter = 1;
    }
    ~SmartPtr(){
        if(a_) {
          if(*counter > 0) {
            --(*counter);
            if (*counter == 0) {
              delete a_;
              delete counter;
            }
          }
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
        if(p.counter)
          ++(*p.counter);
        counter = p.counter;
    }
    SmartPtr &operator=(SmartPtr& p) {
      if(this == &p)
        return *this;
      if(a_) {
        if(*counter > 0) {
          --(*counter);
          if (*counter == 0) {
            delete a_;
            delete counter;
          }
        }
      }
      a_ = p.a_;
      if(p.counter)
        ++(*p.counter);
      counter = p.counter;
      return *this;
    }

private:
    A* a_ = nullptr;
    int* counter = nullptr;
};

int main() {
  SmartPtr p1(new A);
  SmartPtr p2(p1);
  SmartPtr p3;
  p1 = p3;
  p3 = p1;
  SmartPtr p4(p3);
  return 0;
}
