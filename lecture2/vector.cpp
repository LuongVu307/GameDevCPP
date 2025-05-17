#include <iostream>
#include <vector>


int main(int argc, char * argv[])
{
    std::vector<float> vec;
    vec.push_back(42.2);
    vec.push_back(10.4);

    std::cout << vec[0] << "\n";
    std::cout << vec[1] << "\n";
    std::cout << vec[2] << "\n"; // No error even though the size is not that large


    std::cout << "List iteration" << std::endl;
    // Iterating through list
    for (size_t i=0; i < vec.size(); i++)
    {
        std::cout << vec[i] << std::endl;
    }

    // Faster way to iterate

    for (auto a : vec) // Make it "auto"
    {
        std::cout << a << "\n";
    }
    


    return 0;
}