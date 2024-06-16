#include <iostream>

int main()
{
    int a[50], size, pos, i;

    std::cout << "Enter size of array: ";
    std::cin >> size;

    std::cout << "Enter elements in array: ";
    for (i = 0; i < size; i++)
    {
        std::cin >> a[i];
    }

    // Delete the first element of the array
    for (i = 0; i < size - 1; i++)
    {
        a[i] = a[i+1];
    }
    size--;

    std::cout << "Array after deletion: ";
    for (i = 0; i < size; i++)
    {
        std::cout << a[i] << " ";
    }

    return 0;
}
