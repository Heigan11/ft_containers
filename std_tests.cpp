#include <iostream>
#include <ctime>

void std_test_vector();
void std_test_stack();
void std_test_map();

int main(){
	std::cout << "============================" << std::endl;
	std::cout << "=======std_test_vector======" << std::endl;
	std::cout << "============================" << std::endl;
	std_test_vector();
	std::cout << "============================" << std::endl;
	std::cout << "=======std_test_stack========" << std::endl;
	std::cout << "============================" << std::endl;
	std_test_stack();
	std::cout << "============================" << std::endl;
	std::cout << "=======std_test_map=========" << std::endl;
	std::cout << "============================" << std::endl;
	std_test_map();

	return 0;
}
