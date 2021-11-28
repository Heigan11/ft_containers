#ifndef bidirectional_iterator_H
# define bidirectional_iterator_H

# include "node.hpp"
# include "map.hpp"
# include "pair.hpp"

namespace ft{
template<class Key, class T>
class bidirectional_iterator
{
	public:
		typedef ft::pair<Key, T> data;
		typedef bidirectional_iterator<Key, T> iterator;
		typedef ft::node<data> node;
		node* ptr;

		bidirectional_iterator() : ptr() {}
		bidirectional_iterator(node* ptr) : ptr(ptr) {}
		bidirectional_iterator(const iterator & other) {*this = other;}

		bidirectional_iterator &operator=(const iterator & other){
			ptr = other.ptr;
			return *this;
		}
		virtual ~bidirectional_iterator() {}

		bool operator==(const iterator & other) {return this->ptr == other.ptr;}
		bool operator!=(const iterator & other) {return this->ptr != other.ptr;}

		data &operator*() {return this->ptr->data;}
		data *operator->() {return &this->ptr->data;}

		bidirectional_iterator &operator++(){
			if (ptr->right == nullptr){
				while (ptr->parent != nullptr && ptr == ptr->parent->right)
					ptr = ptr->parent;
				ptr = ptr->parent;
			}
			else {
				ptr = ptr->right;
				while (ptr->left != nullptr)
					ptr = ptr->left;
			}
			return *this;
		}

		bidirectional_iterator operator++(int){
			bidirectional_iterator tmp(*this);
			this->operator++();
			return tmp;
		}

		bidirectional_iterator &operator--(){
			if (ptr->left == nullptr){
				while (ptr->parent != nullptr && ptr == ptr->parent->left)
					ptr = ptr->parent;
				ptr = ptr->parent;
			}
			else {
				ptr = ptr->left;
				while (ptr->right != nullptr)
					ptr = ptr->right;
			}
			return *this;
		}
		
		bidirectional_iterator operator--(int){
			bidirectional_iterator tmp(*this);
			this->operator--();
			return tmp;
		}
};

template<class Key, class T>
class rev_iterator
{
	public:
		typedef ft::pair<Key, T> data;
		typedef rev_iterator<Key, T> iterator;
		typedef ft::node<data> node;
		node* ptr;

		rev_iterator() : ptr() {}
		rev_iterator(node* ptr) : ptr(ptr) {}
		rev_iterator(const iterator & other) {*this = other;}

		rev_iterator &operator=(const iterator & other){
			ptr = other.ptr;
			return *this;
		}
		virtual ~rev_iterator() {}

		bool operator==(const iterator & other) {return this->ptr == other.ptr;}
		bool operator!=(const iterator & other) {return this->ptr != other.ptr;}

		data &operator*() {return this->ptr->data;}
		data *operator->() {return &this->ptr->data;}

		rev_iterator &operator++()
		{
			if (ptr->left == nullptr){
				while (ptr->parent != nullptr && ptr == ptr->parent->left)
					ptr = ptr->parent;
				ptr = ptr->parent;
			}
			else {
				ptr = ptr->left;
				while (ptr->right != nullptr)
					ptr = ptr->right;
			}
			return *this;
		}

		rev_iterator &operator--()
		{
			if (ptr->right == nullptr){
				while (ptr->parent != nullptr && ptr == ptr->parent->right)
					ptr = ptr->parent;
				ptr = ptr->parent;
			}
			else {
				ptr = ptr->right;
				while (ptr->left != nullptr)
					ptr = ptr->left;
			}
			return *this;
		}
};

}

#endif
