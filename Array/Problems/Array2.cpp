#include <iostream>


int main(){

	int numbers[] {3, 8, 2, 1, 5, 4, 6};
	int max_number = numbers[0]; 

	for (int i = 1; i < sizeof(numbers)/sizeof(numbers[0]); i++) {
	if (numbers[i] > max_number) {
		max_number = numbers[i]; 
	}
	}
    
    for (int i = 0; i<sizeof(numbers)/sizeof(numbers[0]); i++){
        if (numbers[i] < max_number){
            std::cout << numbers[i] << " Min" << std::endl;
        }else
        {
            std::cout << numbers[i] << " Max" << std::endl;
        }
        
    }
    
    return 0;
}