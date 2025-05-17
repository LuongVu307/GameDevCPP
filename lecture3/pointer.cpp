#include <iostream>


void pp(int & i) //Try without &
{
    std::cout << &i << " " << i << " " << sizeof(i) << "\n";
}


int main(int argc, char * argv[])
{
    int a = 10;
    int b = 25;


    std::cout << &a << " " << a << " " << sizeof(a) << "\n";
    std::cout << &b << " " << b << " " << sizeof(b) << "\n";

    // Difference of those is 4 bytes

    pp(a);
    pp(b);

    std::cout << "\n";

    int arr[10] = {}; //Try initialize without anything (no "= {}")

    for (size_t i=0; i<10; i++)
    {
        pp(arr[i]);
    } //Continously allocation into the stack

    int * harr = new int[10];

    for (size_t i=0; i<10; i++)
    {
        pp(harr[i]);
    }

    std::cout << "\n";

    
    int c = 10;
    int d = 25;
    int* pc = &c;
    int* pd = &d;
    

    *(&a) = 17; // Same as *pa = 17  
    // The left one meant "Dereference of the address of a <-- 17"
    // The right one said that "dereference the pointer of a <-- 17" 


    pp(c);
    pp(d);


    return 0;
}