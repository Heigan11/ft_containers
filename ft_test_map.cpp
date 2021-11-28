#include "pair.hpp"
#include "map.hpp"
#include "bidirectional_iterator.hpp"
#include "node.hpp"
#include <iostream>
#include <string>
#include <ctime>

void ft_constructor_map(){

	std::cout << "=======empty constructor========" << std::endl;
	ft::map<const char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	for (ft::map<const char,int>::iterator it=first.begin(); it!=first.end(); ++it)
		std::cout << it->first << " => " << it->second << std::endl;

	std::cout << "=======range constructor========" << std::endl;
	ft::map<const char,int> second (first.begin(),first.end());

	for (ft::map<const char,int>::iterator it=second.begin(); it!=second.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "=======copy constructor========" << std::endl;
	ft::map<const char,int> third (second);

	for (ft::map<const char,int>::iterator it=third.begin(); it!=third.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void ft_operator_map(){
	ft::map<const char,int> first;
	ft::map<const char,int> second;

	first['x']=8;
	first['y']=16;
	first['z']=32;

	second = first;
	first = ft::map<const char,int>();

	std::cout << "Size of first: " << first.size() << '\n';
	std::cout << "Size of second: " << second.size() << '\n';
	std::cout << "second contains:\n";
	for (ft::map<const char,int>::iterator it=second.begin(); it!=second.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void ft_begin_end_map(){
	ft::map<const char,int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	for (ft::map<const char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void ft_rbegin_rend_map(){
	ft::map<const char,int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	ft::map<const char,int>::reverse_iterator rit;
	for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
	std::cout << rit->first << " => " << rit->second << '\n';
}

void ft_empty_map(){
	ft::map<const char,int> mymap;

	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;

	while (!mymap.empty())
	{
		std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
		mymap.erase(mymap.begin());
	}
}

void ft_size_map(){
	ft::map<const char,int> mymap;
	mymap['a']=101;
	mymap['b']=202;
	mymap['c']=302;

	std::cout << "mymap.size() is " << mymap.size() << '\n';
}

void ft_max_size_map(){
	int i;
	ft::map<const int,int> mymap;

	if (mymap.max_size()>1000)
	{
		for (i=0; i<1000; i++) mymap[i]=0;
		std::cout << "The map contains 1000 elements.\n";
	}
	else std::cout << "The map could not hold 1000 elements.\n";
}

void ft_operator_b_map(){
	ft::map<const char,std::string> mymap;

	mymap['a']="an element";
	mymap['b']="another element";
	mymap['c'] = mymap['b'];

	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
	std::cout << "mymap['b'] is " << mymap['b'] << '\n';
	std::cout << "mymap['c'] is " << mymap['c'] << '\n';
	std::cout << "mymap['d'] is " << mymap['d'] << '\n';

	std::cout << "mymap now contains " << mymap.size() << " elements.\n";
}

void ft_insert_map(){
	ft::map<const char,int> mymap;

	// first insert function version (single parameter):
	mymap.insert ( ft::pair<const char,int>('a',100) );
	mymap.insert ( ft::pair<const char,int>('z',200) );

	ft::pair<ft::map<const char,int>::iterator,bool> ret;
	ret = mymap.insert ( ft::pair<const char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	ft::map<const char,int>::iterator it = mymap.begin();
	mymap.insert (it, ft::pair<const char,int>('b',300));  // max efficiency inserting
	mymap.insert (it, ft::pair<const char,int>('c',400));  // no max efficiency inserting

	// third insert function version (range insertion):
	ft::map<const char,int> anothermap;
	anothermap.insert(mymap.begin(),mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void ft_erase_map(){

	ft::map<const char,int> mymap;
	ft::map<const char,int>::iterator it;

	// insert some values:
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;

	it=mymap.find('b');
	mymap.erase (it);                   // erasing by iterator

	mymap.erase ('c');                  // erasing by key

	it = mymap.find ('e');
	mymap.erase ( it, mymap.end() );    // erasing by range

	// show content:
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void ft_clear_map(){

	ft::map<const char,int> mymap;

	mymap['x']=100;
	mymap['y']=200;
	mymap['z']=300;

	std::cout << "mymap contains:\n";
	for (ft::map<const char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	mymap.clear();

	mymap['a']=1101;
	mymap['b']=2202;

	std::cout << "mymap contains:\n";
	for (ft::map<const char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void ft_swap_map(){
	ft::map<const char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

 	foo.swap(bar);

	std::cout << "foo contains:\n";
	for (ft::map<const char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
		for (ft::map<const char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
	std::cout << it->first << " => " << it->second << '\n';
}

void ft_key_comp_map(){
	ft::map<const char,int> mymap;

	ft::map<const char,int>::key_compare mycomp = mymap.key_comp();

	mymap['a']=100;
	mymap['b']=200;
	mymap['c']=300;

	std::cout << "mymap contains:\n";

	char highest = mymap.rbegin()->first;     // key value of last element

	ft::map<const char,int>::iterator it = mymap.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mycomp((*it++).first, highest) );
}

void ft_value_comp_map(){
	ft::map<const char,int> mymap;

	mymap['x']=1001;
	mymap['y']=2002;
	mymap['z']=3003;

	std::cout << "mymap contains:\n";

	ft::pair<const char,int> highest = *mymap.rbegin();

	ft::map<const char,int>::iterator it = mymap.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mymap.value_comp()(*it++, highest) );
}

void ft_find_map(){
	ft::map<const char,int> mymap;
	ft::map<const char,int>::iterator it;

	mymap['a']=50;
	mymap['b']=100;
	mymap['c']=150;
	mymap['d']=200;

	it = mymap.find('b');
	if (it != mymap.end())
	mymap.erase (it);

	// print content:
	std::cout << "elements in mymap:" << '\n';
	std::cout << "a => " << mymap.find('a')->second << '\n';
	std::cout << "c => " << mymap.find('c')->second << '\n';
	std::cout << "d => " << mymap.find('d')->second << '\n';
}

void ft_count_map(){
	ft::map<const char,int> mymap;
	char c;

	mymap ['a']=101;
	mymap ['c']=202;
	mymap ['f']=303;

	for (c='a'; c<'h'; c++)
	{
		std::cout << c;
		if (mymap.count(c)>0)
			std::cout << " is an element of mymap.\n";
		else
			std::cout << " is not an element of mymap.\n";
	}
}

void ft_lower_bound_map(){
	ft::map<const char,int> mymap;
	ft::map<const char,int>::iterator itlow,itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['d']=80;
	mymap['e']=100;

	itlow=mymap.lower_bound ('b');  // itlow points to b
	itup=mymap.upper_bound ('d');   // itup points to e (not d!)

	mymap.erase(itlow,itup);        // erases [itlow,itup)

	// print content:
	for (ft::map<const char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

}

void ft_equal_range_map(){
	ft::map<const char,int> mymap;

	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;

	ft::pair<ft::map<const char,int>::iterator,ft::map<const char,int>::iterator> ret;
	ret = mymap.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';
}

void ft_get_allocator_map(){
	int psize;
	ft::map<const char,int> mymap;
	ft::pair<const char,int>* p;

	// allocate an array of 5 elements using mymap's allocator:
	p=mymap.get_allocator().allocate(5);

	// assign some values to array
	psize = sizeof(ft::map<const char,int>::value_type)*5;

	std::cout << "The allocated array has a size of " << psize << " bytes.\n";

	mymap.get_allocator().deallocate(p,5);
}


void ft_test_map(){

	std::cout << "=======constructor========" << std::endl;
	ft_constructor_map();

	std::cout << "=======operator'='========" << std::endl;
	ft_operator_map();

	std::cout << "=======begin/end========" << std::endl;
	ft_begin_end_map();

	std::cout << "=======rbegin/rend========" << std::endl;
	ft_rbegin_rend_map();

	std::cout << "=======empty========" << std::endl;
	ft_empty_map();

	std::cout << "=======size========" << std::endl;
	ft_size_map();

	std::cout << "=======max_size========" << std::endl;
	ft_max_size_map();

	std::cout << "=======operator[]========" << std::endl;
	ft_operator_b_map();

	std::cout << "=======insert========" << std::endl;
	ft_insert_map();

	std::cout << "=======erase========" << std::endl;
	ft_erase_map();

	std::cout << "=======swap========" << std::endl;
	ft_swap_map();

	std::cout << "=======clear========" << std::endl;
	ft_clear_map();

	std::cout << "=======key_comp========" << std::endl;
	ft_key_comp_map();

	std::cout << "=======value_comp========" << std::endl;
	ft_value_comp_map();

	std::cout << "=======find========" << std::endl;
	ft_find_map();

	std::cout << "=======count========" << std::endl;
	ft_count_map();

	std::cout << "=======lower_bound/upper_bound========" << std::endl;
	ft_lower_bound_map();

	std::cout << "=======equal_range========" << std::endl;
	ft_equal_range_map();

	std::cout << "=======get_allocator========" << std::endl;
	ft_get_allocator_map();
}
