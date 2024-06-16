#include <iostream>

int main()
{
    int a[50], size, i;

    std::cout << "Enter size of array: ";
    std::cin >> size;

    std::cout << "Enter elements in array: ";
    for (i = 0; i < size; i++)
    {
        std::cin >> a[i];
    }
    size--;
       
    std::cout << "Array after deletion: ";
    for (i = 0; i < size; i++)
    {
        std::cout << a[i] << " ";
    }

    return 0;
}
