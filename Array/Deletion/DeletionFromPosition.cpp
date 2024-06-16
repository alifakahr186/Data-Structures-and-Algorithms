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

    std::cout << "Enter position to delete: ";
    std::cin >> pos;

    if (pos <= 0 || pos > size)
    {
        std::cout << "Invalid position: ";
    }
    else
    {
        for (i = pos - 1; i < size - 1; i++)
        {
            a[i] = a[i+1];
        }

        size--;

        std::cout << "Array after deletion: ";
        for (i = 0; i < size; i++)
        {
            std::cout << a[i] << " ";
        }
    }

    return 0;
}
