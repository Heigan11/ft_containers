#include <iostream>
#include <string>
#include <deque>
#include <map>
#include "map.hpp"
#include <ctime>
#include <stack>
#include <vector>

void ft_test_vector();
void ft_test_stack();
void ft_test_map();

void std_test_vector();
void std_test_stack();
void std_test_map();

int main(){

	std::map<const int, int> std_map_int;

	srand(time(0));
	unsigned int start_time =  clock();

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

	for (int i = 0; i < 1000; ++i)
	{
		std_map_int.insert(std::make_pair<const int, int>(rand(), rand()));
	}
	int sum = 0;
	for (int i = 0; i < 1000; i++)
	{
		int access = rand();
		sum += std_map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;
	unsigned int end_time = clock();
	unsigned int search_time_std = end_time - start_time;
	std::cout << "time: " << search_time_std << std::endl;

	ft::map<const int, int> ft_map_int;
	start_time =  clock();

	std::cout << "============================" << std::endl;
	std::cout << "=======ft_test_vector=======" << std::endl;
	std::cout << "============================" << std::endl;
	ft_test_vector();
	std::cout << "============================" << std::endl;
	std::cout << "=======ft_test_stack========" << std::endl;
	std::cout << "============================" << std::endl;
	ft_test_stack();
	std::cout << "============================" << std::endl;
	std::cout << "=======ft_test_map==========" << std::endl;
	std::cout << "============================" << std::endl;
	ft_test_map();

	for (int i = 0; i < 1000; ++i)
	{
		ft_map_int.insert(ft::make_pair<const int, int>(rand(), rand()));
	}
	sum = 0;
	for (int i = 0; i < 1000; i++)
	{
		int access = rand();
		sum += ft_map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;
	end_time = clock();
	unsigned int search_time = end_time - start_time;
	std::cout << "time_std: " << search_time_std << std::endl;
	std::cout << "time_ft: " << search_time << std::endl;

	return 0;
}

