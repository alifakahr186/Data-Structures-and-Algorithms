#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

class Hash
{
private:
    static const int SIZE = 10;
    Node* bucket[SIZE];

public:

    Hash()
    {
        for (int i = 0; i < SIZE; i++)
        {
            bucket[i] = nullptr;
        }
    }

    int hashFunction(int key)
    {
        return key % SIZE;
    }

    void insert(int key)
    {
        int index = hashFunction(key);

        Node* newNode = new Node(key);

        // No Collision
        if (bucket[index] == nullptr)
        {
            bucket[index] = newNode;
            return;
        }

        // Collision -> Separate Chaining
        Node* temp = bucket[index];

        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    void search(int key)
    {
        int index = hashFunction(key);

        Node* temp = bucket[index];

        while (temp != nullptr)
        {
            if (temp->data == key)
            {
                cout << key << " Found in Bucket[" << index << "]" << endl;
                return;
            }

            temp = temp->next;
        }

        cout << key << " Not Found!" << endl;
    }

    void remove(int key)
    {
        int index = hashFunction(key);

        Node* temp = bucket[index];
        Node* prev = nullptr;

        while (temp != nullptr)
        {
            if (temp->data == key)
            {
                // First Node
                if (prev == nullptr)
                {
                    bucket[index] = temp->next;
                }
                else
                {
                    prev->next = temp->next;
                }

                delete temp;

                cout << key << " Deleted Successfully." << endl;
                return;
            }

            prev = temp;
            temp = temp->next;
        }

        cout << key << " Not Found!" << endl;
    }

    void display()
    {
        for (int i = 0; i < SIZE; i++)
        {
            cout << "Bucket[" << i << "] --> ";

            Node* temp = bucket[i];

            while (temp != nullptr)
            {
                cout << temp->data << " -> ";
                temp = temp->next;
            }

            cout << "NULL" << endl;
        }
    }

    // Destructor
    ~Hash()
    {
        for (int i = 0; i < SIZE; i++)
        {
            Node* temp = bucket[i];

            while (temp != nullptr)
            {
                Node* next = temp->next;
                delete temp;
                temp = next;
            }
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