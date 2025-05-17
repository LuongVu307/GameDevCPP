#include <iostream>


void pp(int & i) //Try without &
{
    std::cout << &i << " " << i << " " << sizeof(i) << "\n";
}


int main(int argc, char * argv[])
{    
    int a = 10;
    int b = 25;

    int* pa = &a;
    int* pb = &b;
    

    *(&a) = 17; // Same as *pa = 17  
    // The left one meant "Dereference of the address of a <-- 17"
    // The right one said that "dereference the pointer of a <-- 17" 

    *(pb+1) = 100; // Or try -1

    pp(a);
    pp(b);

    std::cout << "\n";

    return 0;
}