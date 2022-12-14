#include <iostream>
#include <iomanip>
//#include <windows.h>
#include <cmath>

std::string binary(uint8_t num){
	std::string answer = "";
	for(int i = sizeof(num) * 8; i > 0; i--){
		if((num & (1 << (i - 1))) != 0){
			answer += '1';
		}else{
			answer += '0';
		}
	}
	return answer;
}

std::string fixedVariable(uint8_t num){
	short int size = 8 * sizeof(num);
	uint8_t order = 0;
	std::string answer = "";

	for(int i = size; i > 0; i--){ 
		if((num & ( 1 << (i - 1))) != 0){
			order = i;
			break;
		}
	}

	int temp = 0;
    while(pow(2, temp) <= size) 
        temp++;

	for(int i = temp; i > 0; i--){ 
		if((order & (1 << (i - 1))) != 0){
			answer += '1';
		}else{
			answer += '0';
		}
	}
	answer += ' ';

	for(int i = (order - 1); i > 0; i--){ 
		if((num & (1 << (i - 1))) != 0){
			answer += '1';
		}else{
			answer += '0';
		}
	}
	return answer;
}

std::string gammaCodeElias(uint8_t num){

	short int size = 8 * sizeof(num);
	uint8_t order = 0;
	std::string answer = "";

	for(int i = size; i > 0; i--){ 
		if((num & ( 1 << ( i- 1))) != 0){
			order = i;
			break;
		}
	}

	for(int i = (order - 1); i > 0; i--) 
		answer += '0';
	
	answer += ' ';

	for(int i = order; i > 0; i--){ 
		if((num & (1 << (i - 1))) != 0){
			answer += '1';
		}else{
			answer += '0';
		}
	}
	return answer;
}

std::string omegaCodeElias(uint8_t num){
    if (num == 0)
        return "";

    short int size = 8 * sizeof(num);
	uint8_t order = 0;
    std::string temp = "";
	std::string answer = "0";

    while (num != 1){
        temp = "";

        for(int i = size; i > 0; i--){
            if((num & ( 1 << ( i- 1))) != 0){
                order = i;
                break;
            }
        }
        
        for(int i = order; i > 0; i--){
            if((num & (1 << (i - 1))) != 0){
                temp += '1';
            }else{
                temp += '0';
            }
        }    
        temp += " " + answer;
        answer = temp;
        num = order - 1;

    }

	return answer;
}

int main(int argc, const char **argv) {
	// std::ios::sync_with_stdio(false);

	uint8_t	number = 0; // 0 - 255
	// std::cout << sizeof(number);

	std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n";
	std::cout << "|" << std::setw(15) << "";
	std::cout << "|                              |                                                      Codovoe slovo                                                 |" << "\n";

	std::cout << "|" << std::setw(15) << "     Chislo    ";
	std::cout << "|        Binary code           |--------------------------------------------------------------------------------------------------------------------|" << "\n";

	std::cout << "|" << std::setw(15) << "";
	std::cout << "|                              |            Fixed + Variable          |              Y-kod alliasa            |              w-kod alliasa          |" << "\n";
	std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n";
	
	do
	{
		std::cout << "|";
		std::cout << std::left << std::setw(15) << (int)number;
		std::cout << "|";
		std::cout << std::left << std::setw(30) << binary(number);
		std::cout << "|";
		std::cout << std::left << std::setw(38) << fixedVariable(number);
		std::cout << "|";
		std::cout << std::left << std::setw(38) << gammaCodeElias(number);
		std::cout << "|";
		std::cout << std::left << std::setw(38) << omegaCodeElias(number);
		std::cout << "|";
		std::cout << "\n";

		number ++;
	} while(number != 0);
	std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n";
	
	// fixedVariable(0);
	//pauseAtTheEnd();
	return 0;
}
