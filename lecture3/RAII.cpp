#include <iostream>

template <typename T>

class DynamicArray //Previously IntArray
{
    T* m_arr;
    size_t m_size;

public:
    
    DynamicArray(size_t size):
        m_arr(new T[size]{}),
        m_size(size)
    {
        std::cout << "Array Constructor\n";
    }

    ~DynamicArray()
    {
        delete [] m_arr;
        std::cout << "Array Destructor\n";
    }

    T get(size_t index) const
    {
        return m_arr[index];
    }

    void set(size_t index, T val)
    {
        m_arr[index] = val;
    }

    void print() const
    {
        for (size_t i=0; i<m_size; i++)
        {
            std::cout << i << " " << m_arr[i] << "\n";
        }
    }

    const T & operator [] (size_t index) const
    {
        return m_arr[index];
    }

    T & operator [] (size_t index) 
    {
        return m_arr[index];
    }
};


int main(int argc, char * argv[])
{    

    // IntArray myArray(10);

    // myArray.set(4, 7);
    // myArray.set(2, 104);


    // myArray.print();

    DynamicArray<float> myArray(10);

    myArray.set(4, 7.13);
    myArray.set(2, 10.8);


    myArray.print();

    myArray[5] = 1.234;
    myArray[3] = 38.1;

    myArray.print();

    const DynamicArray<float> yourArray(10);

    std::cout << yourArray[2] << "\n";
    yourArray.print();

    DynamicArray<float> hisArray(10);

    hisArray[1] = 2.1;

    hisArray
    .print();


    return 0;
}