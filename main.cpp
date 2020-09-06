#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

class Array{
public:
    explicit Array(const int& initial_allocated){ // конструктор с параметром
        allocated = initial_allocated;
        mem = new int[allocated];
        for (int i = 0; i < allocated; ++i)
            mem[i] = 0;
    }
    Array (const Array & source) //конструктор копирования
    {
        size = source.size;
        allocated = source.allocated;
        mem = new int[allocated];
        for (int i = 0; i < allocated; ++i)
            mem[i] = source.mem[i];
    }
    Array(){ //конструктор без параметров
        allocated = 1;
        mem = new int;
        mem[0] = 0;
    }
    ~Array(){
        delete mem;
    };
    int get_size() const{
        return size;
    }
    int get_elem(int i) const{
        return mem[i];
    }
    void add_number_to_array(const int& number){
        if(size == allocated){
            allocated *= 2;
            int * tmp = new int[allocated];
            assert(NULL != tmp);
            for(int i = 0; i < size; ++i){
                tmp[i] = mem[i];
            }
            delete [] mem;
            mem = tmp;
        }
        mem[size++] = number;
    }
    void print() //показать массив
    {
        for (int i = 0; i < size; i++)
            cout << mem[i] << "  ";
        cout << endl;
    }
    Array& operator=(const Array& array){
        size = array.size;
        allocated = array.allocated;
        delete [] mem;
        mem = new int[allocated];
        for(int i = 0; i < size; ++i)
            mem[i] = array.mem[i];
        return *this;
    }
private:
    int *mem;
    int allocated = 0, size = 0;
};
Array read_array(){
    ifstream f("in.txt");
    Array a(1);
    int number = 0;
    if (f.is_open())
    {
        while(f >> number) {
            a.add_number_to_array(number);
        }
    }
    f.close();
    return a;
}
int main() {
    Array A = read_array();
    A.print();
    Array B(3);
    B.add_number_to_array(5);
    B.add_number_to_array(7);
    B.add_number_to_array(6);
    B.print();
    Array C(3);
    B = C = A;
    B.add_number_to_array(6);
    B.print();
    C.print();


}
