#include <iostream>


int main(){

	int numbers[] {3, 8, 2, 1, 5, 4, 6};
    int sum = 0;

    for (int i = 1; i < sizeof(numbers)/sizeof(numbers[i]); i++)
    {
        if (numbers[i] % 2 == 0){
            sum += numbers[i];
        }
                
    }

    std::cout << "Sum " << sum << std::endl;

    
    
    
    return 0;
}