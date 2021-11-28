#ifndef rev_iterator_H
# define rev_iterator_H

template<typename T>
class rev_iterator
{
	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef rev_iterator<T> iterator;

		pointer _ptr;

		rev_iterator() : _ptr(nullptr) {}
		rev_iterator(const pointer ptr) : _ptr(ptr) {}
		virtual ~rev_iterator() {}

		rev_iterator(const iterator & other) {*this = other;}

		iterator &operator=(const iterator & other) {
			this->_ptr = other._ptr;
			return *this;
		}

		bool operator==(const iterator & other) {return this->_ptr == other._ptr;}
		bool operator!=(const iterator & other) {return this->_ptr != other._ptr;}

		T& operator*() {return *this->_ptr;}
		T* operator->() {return this->_ptr;}

		iterator operator++(int) {
			iterator tmp = *this;
			--this->_ptr;
			return tmp;
		}

		iterator &operator++() {
			--this->_ptr;
			return *this;
		}

		iterator operator--(int) {
			iterator tmp = *this;
			++this->_ptr;
			return tmp;
		}

		iterator &operator--() {
			++this->_ptr;
			return *this;
		}

		size_t operator-(const iterator & other) {
			return this->_ptr - other._ptr; }
		iterator operator-(size_t n) {
			return this->_ptr + n; }
		size_t operator+(const iterator & other) {
			return this->_ptr + other._ptr; }
		iterator operator+(size_t n) {
			return this->_ptr - n; }

		bool operator>(const iterator & other) {return this->_ptr > other._ptr;}
		bool operator>=(const iterator & other) {return this->_ptr >= other._ptr;}
		bool operator<(const iterator & other) {return this->_ptr < other._ptr;}
		bool operator<=(const iterator & other) {return this->_ptr <= other._ptr;}

		iterator &operator+=(size_t n) {
			this->_ptr -= n;
			return *this;
		}

		iterator &operator-=(size_t n) {
			this->_ptr += n;
			return *this;
		}

		T& operator[](size_t n){
			return *(this->_ptr + n);
		}
};

#endif
