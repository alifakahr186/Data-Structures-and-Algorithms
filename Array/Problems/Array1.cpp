#include <iostream>


int main(){

	int numbers[] {3, 8, 2, 1, 5, 4, 6};
	int max_number = numbers[0]; 
    int min_number = numbers[0]; 


	for (int i = 1; i < sizeof(numbers)/sizeof(numbers[0]); i++) {
	
	if (numbers[i] > max_number) {
		max_number = numbers[i]; 
	}
	
    if (numbers[i] < min_number)
    {
        min_number = numbers[i];
    }
    
	}
    
	std::cout << "Max To Min (" << max_number << ", " << min_number << ")"<< std::endl;
    std::cout << "Min To Max (" << min_number << ", " << max_number << ")"<< std::endl;

    
    return 0;
} 