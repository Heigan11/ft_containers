#ifndef VECTOR_H
# define VECTOR_H
# define CAP_UP 2

# include <memory>
# include "random_access_iterator.hpp"
# include "rev_iterator.hpp"
# include <iostream>
# include <string>
# include <sstream>
# include <limits>

namespace ft
{
	template <class T, class Alloc = std::allocator<T>>
	class vector
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef random_access_iterator<value_type> iterator;
			typedef random_access_iterator<const value_type> const_iterator;
			typedef rev_iterator<value_type> reverse_iterator;
			typedef rev_iterator<const value_type> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

		private:
			allocator_type _alloc;
			size_type _size;
			size_type _capacity;
			pointer _ptr;


		public:
			explicit vector (const allocator_type& alloc = allocator_type());
			explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type());
			vector (iterator first, iterator last,
				const allocator_type& alloc = allocator_type());
			vector (const vector& x);
			vector &operator=(const vector& x);
			virtual ~vector() {
				this->_alloc.destroy(this->_ptr);
				this->_alloc.deallocate(this->_ptr, 1);
			};

			iterator begin() {
				return iterator(this->_ptr);}
			const_iterator begin() const {
				return const_iterator(this->_ptr);}
			iterator end() {
				return iterator(this->_ptr + this->_size);}
			const_iterator end() const {
				return const_iterator(this->_ptr + this->_size);}
			reverse_iterator rbegin(){
				return reverse_iterator(this->_ptr + this->_size - 1);}
			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(this->_ptr + this->_size - 1);}
			reverse_iterator rend() {
				return reverse_iterator(this->_ptr - 1);}
			const_reverse_iterator rend() const {
				return const_reverse_iterator(this->_ptr - 1);}

			size_type size() const {
				return this->_size;}
			size_type max_size() const {
				return std::numeric_limits<size_type>::max() / (sizeof(value_type)) / 2;}
			size_type capacity() const {
				return this->_capacity;}
			bool empty() const {
				return this->_size == 0;}
			void resize (size_type n, value_type val = value_type());
			void reserve (size_type n);

			reference operator[] (size_type n) {
				return this->_ptr[n];}
			const_reference operator[] (size_type n) const {
				return this->_ptr[n];}
			reference at (size_type n){
				if (n >= this->_size) {
					char buffer [33];
					std::string msg = "vector::_M_range_check: __n (which is ";
					msg += itoa(n, buffer, 10);
					msg += ") >= this->size() (which is ";
					msg += itoa(this->_size, buffer, 10);
					msg += ")";
					throw std::out_of_range(msg);
				}
				return this->_ptr[n];
			}
			const_reference at (size_type n) const {
				return this->at(n);};
			reference front() {
				return *this->_ptr;}
			const_reference front() const {
				return *this->_ptr;}
			reference back(){
				return *(this->_ptr + this->_size - 1);}
			const_reference back() const{
				return *(this->_ptr + this->_size - 1);}

			void assign (iterator first, iterator last);
			void assign (size_type n, const value_type& val);
			void assign (const_iterator first, const_iterator last);
			void push_back (const value_type& val);
			void pop_back();
			iterator insert (iterator position, const value_type& val);
			void insert (iterator position, size_type n, const value_type& val);
			void insert (iterator position, iterator first, iterator last);
			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);
			void swap (vector& x);
			void clear();

			allocator_type get_allocator() const;
	};

		template <class T, class Alloc>
		vector<T, Alloc>::vector(const allocator_type& alloc) :
		_alloc(alloc), _size(0), _capacity(0), _ptr(nullptr) {}

		template <class T, class Alloc>
		vector<T, Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc) :
		_alloc(alloc), _size(n), _capacity(n) {
			this->_ptr = this->_alloc.allocate(this->_capacity);
			this->_alloc.construct(this->_ptr, value_type());
			for (size_type i = 0; i < n; i++){
				this->_ptr[i] = val;
			}
		}

		template <class T, class Alloc>
		vector<T, Alloc>::vector(iterator first, iterator last, const allocator_type& alloc) :
		_alloc(alloc) {
			this->_size = last - first;
			this->_capacity = this->_size;
			this->_ptr = this->_alloc.allocate(this->_capacity);
			this->_alloc.construct(this->_ptr, value_type());
			this->assign(first, last);
		}

		template <class T, class Alloc>
		vector<T, Alloc>::vector (const vector& x) : _alloc(x._alloc), _size(0), _capacity(0), _ptr(nullptr) {
			*this = x;
		}

		template <class T, class Alloc>
		vector<T, Alloc> &vector<T, Alloc>::operator=(const vector<T, Alloc>& x){
			this->assign(x.begin(), x.end());
			return *this;
		}

		template <class T, class Alloc>
		void vector<T, Alloc>::assign (iterator first, iterator last){
			this->clear();
			while (first != last) {
				this->push_back(*first);
				++first;
			}
		}

		template <class T, class Alloc>
		void vector<T, Alloc>::assign (const_iterator first, const_iterator last){
			this->clear();
			while (first != last) {
				this->push_back(*first);
				++first;
			}
		}

		template <class T, class Alloc>
		void vector<T, Alloc>::assign (size_type n, const value_type& val){
			this->clear();
			while (n > this->_size)
				this->push_back(val);
		}

		template <class T, class Alloc>
		void vector<T, Alloc>::push_back (const value_type& val){
			if (this->_size == this->_capacity)
			{
				if (this->_size == 0)
					this->reserve(1);
				else if (this->_size == 1)
					this->reserve(2);
				else
					this->reserve(this->_capacity * CAP_UP);
			}
			this->_ptr[this->_size] = val;
			this->_size++;
		}

		template <class T, class Alloc>
		void vector<T, Alloc>::reserve (size_type n){
			if (n > this->_capacity) {
				this->_capacity = n;
				pointer new_arr = this->_alloc.allocate(n);
				this->_alloc.construct(new_arr, value_type());
				for (size_type i = 0; i < this->_size; i++){
					new_arr[i] = this->_ptr[i];
				}
				if (this->_ptr != nullptr) {
					this->_alloc.destroy(this->_ptr);
					this->_alloc.deallocate(this->_ptr, 1);
					this->_ptr = nullptr;
				}
				this->_ptr = new_arr;
			}
		}

		template <class T, class Alloc>
		void vector<T, Alloc>::clear() {
			if (this->_ptr != nullptr) {
				this->_alloc.destroy(this->_ptr);
				this->_alloc.deallocate(this->_ptr, 1);
				this->_ptr = nullptr;
			}
			this->_size = 0;
			this->_capacity = 0;
		}

		template <class T, class Alloc>
		void vector<T, Alloc>::pop_back() {
			if (this->_size != 0) {
				this->_size--;
				if (this->_size == 0 && this->_ptr != nullptr){
					this->_capacity = 0;
					this->_alloc.destroy(this->_ptr);
					this->_alloc.deallocate(this->_ptr, 1);
					this->_ptr = nullptr;
					return ;
				}
				this->_capacity = this->_size * CAP_UP;
				pointer new_arr = this->_alloc.allocate(this->_capacity);
				this->_alloc.construct(new_arr, value_type());
				for (size_type i = 0; i < this->_size; i++){
					new_arr[i] = this->_ptr[i];
				}
				if (this->_ptr != nullptr) {
					this->_alloc.destroy(this->_ptr);
					this->_alloc.deallocate(this->_ptr, 1);
					this->_ptr = nullptr;
				}
				this->_ptr = new_arr;
			}
		}

		template <class T, class Alloc>
		void vector<T, Alloc>::resize (size_type n, value_type val) {
			while (n < this->_size)
				this->pop_back();
			while (n > this->_size)
				this->push_back(val);
		}

		template <class T, class Alloc>
		typename vector<T, Alloc>::iterator vector<T, Alloc>::insert (iterator position, const value_type& val){
			size_type n = position - this->begin();
			insert(position, 1, val);
			return iterator(&this->_ptr[n]);
		}

		template <class T, class Alloc>
		void vector<T, Alloc>::insert (iterator position, size_type n, const value_type& val) {
			if (position == this->end()){
				for (size_type i = 0; i < n; i++) {
					this->push_back(val);
				}
				return;
			}
			if (position == this->begin()){
				vector<T, Alloc> tmp(position, this->end());
				this->clear();
				for (size_type i = 0; i < n; i++) {
					this->push_back(val);
				}
				iterator it = tmp.begin();
				iterator ite = tmp.end();
				while (it != ite)
				{
					this->push_back(*it);
					++it;
				}
				return ;
			}
			vector<T, Alloc> vec_end(position, this->end());
			this->_size -= this->end() - position;
			for (size_type i = 0; i < n; i++) {
				this->push_back(val);
			}
			iterator it = vec_end.begin();
			iterator ite = vec_end.end();
			while (it != ite)
			{
				this->push_back(*it);
				++it;
			}
			vec_end.clear();
		}

		template <class T, class Alloc>
		void vector<T, Alloc>::insert (iterator position, iterator first, iterator last) {
			vector<T, Alloc> vec_end(position, this->end());
			this->_size -= this->end() - position;
			while (first != last)
			{
				this->push_back(*first);
				++first;
			}
			iterator it = vec_end.begin();
			iterator ite = vec_end.end();
			while (it != ite)
			{
				this->push_back(*it);
				++it;
			}
		}

		template <class T, class Alloc>
		typename vector<T, Alloc>::iterator vector<T, Alloc>::erase (iterator position){
			iterator it(position);
			iterator ite(this->end() - 1);
			while (it != ite)
			{
				*it = *(it + 1);
				++it;
			}
			this->pop_back();
			return position;
		}

		template <class T, class Alloc>
		typename vector<T, Alloc>::iterator vector<T, Alloc>::erase (iterator first, iterator last){
			iterator tmp(last);
			iterator end = this->end();
			while (last != end)
			{
				*first = *last;
				++first;
				++last;
			}
			this->_size -= last - first;
			return (tmp);
		}

		template <class T, class Alloc>
		void vector<T, Alloc>::swap (vector& x){
			vector<T, Alloc> tmp = *this;
			*this = x;
			x = tmp;
		}

		template <class T, class Alloc>
		typename vector<T, Alloc>::allocator_type vector<T, Alloc>::get_allocator() const{
			return this->_alloc;
		}

		template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
			if (lhs.size() != rhs.size())
				return false;
			for (size_t i = 0; i < lhs.size(); i++)
			{
				if (*(lhs.begin() + i) != *(rhs.begin() + i))
					return false;
			}
			return true;
		}

		template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
			return !(lhs == rhs);
		}

		template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
			for (size_t i = 0; i < lhs.size(); i++)
			{
				if (*(lhs.begin() + i) > *(rhs.begin() + i))
					return false;
				if (*(lhs.begin() + i) < *(rhs.begin() + i))
					return true;
			}
			if (lhs.size() < rhs.size())
				return true;
			return false;
		}

		template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
			if (lhs < rhs || lhs == rhs)
				return true;
			return false;
		}

		template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
			if (lhs == rhs)
				return false;
			return !(lhs < rhs);
		}

		template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
			if (lhs > rhs || lhs == rhs)
				return true;
			return false;
		}

		template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
			vector<T,Alloc> tmp = x;
			x = y;
			y = tmp;
		}
}

#endif
