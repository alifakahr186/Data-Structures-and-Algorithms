#include <iostream>


int main(){

	int numbers[] {3, 8, 2, 1, 5, 4, 6};
	int max_number = numbers[0]; 
    int second_max = numbers[0]; 



	for (int i = 1; i < sizeof(numbers)/sizeof(numbers[0]); i++){
    if (numbers[i] > max_number){
        second_max = max_number;
        max_number = numbers[i];
    
	}else if (numbers[i] > second_max){
        second_max = numbers[i];
    }


    }

    std::cout << "Max " << max_number << std::endl;
    std::cout << "Second_Max " << second_max << std::endl; 


    
    return 0;
}