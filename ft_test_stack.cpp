#include "stack.hpp"
#include <iostream>
#include <deque>

void ft_constructor(){
	std::deque<int> mydeque (3,100);          // deque with 3 elements
	ft::vector<int> myvector (2,200);        // vector with 2 elements

	ft::stack<int, std::deque<int>> first;                    // empty stack
	ft::stack<int, std::deque<int>> second (mydeque);         // stack initialized to copy of deque

	ft::stack<int> third;  // empty stack using vector
	ft::stack<int> fourth (myvector);

	std::cout << "size of first: " << first.size() << '\n';
	std::cout << "size of second: " << second.size() << '\n';
	std::cout << "size of third: " << third.size() << '\n';
	std::cout << "size of fourth: " << fourth.size() << '\n';
}

void ft_empty(){
	ft::stack<int> mystack;
	int sum (0);

	for (int i=1;i<=10;i++) mystack.push(i);

	while (!mystack.empty())
	{
		sum += mystack.top();
		mystack.pop();
	}

	std::cout << "total: " << sum << '\n';
}

void ft_size(){
	ft::stack<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<5; i++) myints.push(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';
}

void ft_top(){
	ft::stack<int> mystack;

	mystack.push(10);
	mystack.push(20);

	mystack.top() -= 5;

	std::cout << "mystack.top() is now " << mystack.top() << '\n';
}

void ft_push_pop(){
	ft::stack<int> mystack;

	for (int i=0; i<5; ++i) mystack.push(i);

	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}
	std::cout << '\n';
}

void ft_comparisons(){
	ft::stack<int> foo;   // three ints with a value of 100
	for (int i=0; i<3; ++i) foo.push(100);
	ft::stack<int> bar;   // two ints with a value of 200
	for (int i=0; i<2; ++i) bar.push(200);

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

void ft_test_stack(){
	std::cout << "=======constructor========" << std::endl;
	ft_constructor();
	std::cout << "=======empty========" << std::endl;
	ft_empty();
	std::cout << "=======size========" << std::endl;
	ft_size();
	std::cout << "=======top========" << std::endl;
	ft_top();
	std::cout << "=======push_pop========" << std::endl;
	ft_push_pop();
	std::cout << "=======comparisons========" << std::endl;
	ft_comparisons();

}
