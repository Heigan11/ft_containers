#ifndef STACK_H
# define STACK_H

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;
			container_type ctnr;

			explicit stack (const container_type& ctnr = container_type()) : ctnr(ctnr) {}
			bool empty() const {return this->ctnr.empty();}
			size_type size() const {return this->ctnr.size();}
			value_type& top() {return this->ctnr.back();}
			const value_type& top() const {return this->ctnr.back();}
			void push (const value_type& val) {this->ctnr.push_back(val);}
			void pop() {this->ctnr.pop_back();}
	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.ctnr == rhs.ctnr;
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return lhs.ctnr != rhs.ctnr;
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return lhs.ctnr < rhs.ctnr;
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return lhs.ctnr <= rhs.ctnr;
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return lhs.ctnr > rhs.ctnr;
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return lhs.ctnr >= rhs.ctnr;
	}
}

#endif
