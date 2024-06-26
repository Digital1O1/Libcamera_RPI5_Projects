// Website reference : https://www.geeksforgeeks.org/templates-cpp/
// Reference video : https://www.youtube.com/watch?v=p3OQDb4nWfg
#include <iostream>
using namespace std;

// Declare template with type parameter 'T' meaning that 'Array' can be instantiated with any data type
// The whole purpose of a template is to allow someone to write generic/reusable code.
// You can define functions/class/data structures w/o specifying exact data types they'll operate on meaning that you can create a single function/class to work with different data types to help combat redundancy
template <typename T>
class Array
{
private:
    T *ptr;
    int size;

public:
    // Constructor that takes array and it's size as argumetns
    Array(T arr[], int s);
    void print();
};

// Constructor
// template <typename T> specifies the function is part of the template class
template <typename T>

// Definition of the constructor outisde the class
Array<T>::Array(T arr[], int s)
{
    ptr = new T[s];
    size = s;
    for (int i = 0; i < size; i++)
        ptr[i] = arr[i];
}
// template <typename T> specifies the function is part of the template class
template <typename T>
void Array<T>::print()
{
    for (int i = 0; i < size; i++)
        cout << " " << *(ptr + i);
    cout << endl;
}

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    Array<int> a(arr, 5);
    a.print();
    return 0;
}
