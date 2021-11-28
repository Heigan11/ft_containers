#include <stack>
#include <vector>
#include <iostream>
#include <deque>

void std_constructor(){
	std::deque<int> mydeque (3,100);          // deque with 3 elements
	std::vector<int> myvector (2,200);        // vector with 2 elements

	std::stack<int> first;                    // empty stack
	std::stack<int> second (mydeque);         // stack initialized to copy of deque

	std::stack<int, std::vector<int>> third;  // empty stack using vector
	std::stack<int, std::vector<int>> fourth (myvector);

	std::cout << "size of first: " << first.size() << '\n';
	std::cout << "size of second: " << second.size() << '\n';
	std::cout << "size of third: " << third.size() << '\n';
	std::cout << "size of fourth: " << fourth.size() << '\n';
}

void std_empty(){
	std::stack<int> mystack;
	int sum (0);

	for (int i=1;i<=10;i++) mystack.push(i);

	while (!mystack.empty())
	{
		sum += mystack.top();
		mystack.pop();
	}

	std::cout << "total: " << sum << '\n';
}

void std_size(){
	std::stack<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<5; i++) myints.push(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';
}

void std_top(){
	std::stack<int> mystack;

	mystack.push(10);
	mystack.push(20);

	mystack.top() -= 5;

	std::cout << "mystack.top() is now " << mystack.top() << '\n';
}

void std_push_pop(){
	std::stack<int> mystack;

	for (int i=0; i<5; ++i) mystack.push(i);

	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}
	std::cout << '\n';
}

void std_comparisons(){
	std::stack<int> foo;   // three ints with a value of 100
	for (int i=0; i<3; ++i) foo.push(100);
	std::stack<int> bar;   // two ints with a value of 200
	for (int i=0; i<2; ++i) bar.push(200);

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

void std_test_stack(){
	std::cout << "=======constructor========" << std::endl;
	std_constructor();
	std::cout << "=======empty========" << std::endl;
	std_empty();
	std::cout << "=======size========" << std::endl;
	std_size();
	std::cout << "=======top========" << std::endl;
	std_top();
	std::cout << "=======push_pop========" << std::endl;
	std_push_pop();
	std::cout << "=======comparisons========" << std::endl;
	std_comparisons();

}
