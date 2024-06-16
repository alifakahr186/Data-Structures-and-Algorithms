#include <iostream>
using namespace std;

int main()
{
    int a[5], i;
    int *q = a;

    for (i = 0; i < 5; i++)
    {
        cin >> a[i];
    }

    for (i = 0; i < 5; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}
