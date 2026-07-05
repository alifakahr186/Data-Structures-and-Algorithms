#include <iostream>
using namespace std;

class Hash
{
private:
    static const int SIZE = 10;
    int bucket[SIZE];

public: 
    // Constructor
    Hash()
    {
        for (int i = 0; i < SIZE; i++)
        {
            bucket[i] = -1;      // -1 = Empty
        }
    }

    void insert(int key)
    {
        // Primary Hash Function
        int hash1 = (2 * key + 3) % SIZE;

        // Secondary Hash Function
        int hash2 = (3 * key + 1) % SIZE;

        // Prevent step size from becoming 0
        if (hash2 == 0)
            hash2 = 1;

        int i = 0;

        while (i < SIZE)
        {
            int index = (hash1 + i * hash2) % SIZE;

            if (bucket[index] == -1 || bucket[index] == -2)
            {
                bucket[index] = key;

                cout << key << " inserted at Bucket[" << index << "]" << endl;
                return;
            }

            i++;
        }

        cout << "Hash Table is Full! Cannot insert " << key << endl;
    }

    void search(int key)
    {
        int hash1 = (2 * key + 3) % SIZE;
        int hash2 = (3 * key + 1) % SIZE;

        if (hash2 == 0)
            hash2 = 1;

        int i = 0;

        while (i < SIZE)
        {
            int index = (hash1 + i * hash2) % SIZE;

            if (bucket[index] == key)
            {
                cout << key << " Found at Bucket[" << index << "]" << endl;
                return;
            }

            if (bucket[index] == -1)
            {
                break;
            }

            i++;
        }

        cout << key << " Not Found!" << endl;
    }

    void remove(int key)
    {
        int hash1 = (2 * key + 3) % SIZE;
        int hash2 = (3 * key + 1) % SIZE;

        if (hash2 == 0)
            hash2 = 1;

        int i = 0;

        while (i < SIZE)
        {
            int index = (hash1 + i * hash2) % SIZE;

            if (bucket[index] == key)
            {
                bucket[index] = -2;      // Deleted Marker

                cout << key << " Deleted Successfully." << endl;
                return;
            }

            if (bucket[index] == -1)
            {
                break;
            }

            i++;
        }

        cout << key << " Not Found!" << endl;
    }

    void display()
    {
        for (int i = 0; i < SIZE; i++)
        {
            cout << "Bucket[" << i << "] : ";

            if (bucket[i] == -1)
                cout << "EMPTY";
            else if (bucket[i] == -2)
                cout << "DELETED";
            else
                cout << bucket[i];

            cout << endl;
        }
    }
};

int main()
{
    Hash hash;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter Elements:\n";

    for (int i = 0; i < n; i++)
    {
        int value;
        cin >> value;
        hash.insert(value);
    }

    hash.display();

    cout << endl;

    int key;

    cout << "Enter element to search: ";
    cin >> key;

    hash.search(key);

    cout << endl;

    cout << "Enter element to delete: ";
    cin >> key;

    hash.remove(key);

    cout << endl;

    hash.display();

    return 0;
}