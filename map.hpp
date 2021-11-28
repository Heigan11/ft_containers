#ifndef MAP_H
# define MAP_H

# include "pair.hpp"
# include <memory>
# include <iostream>
# include <string>
# include <sstream>
# include <limits>
# include "bidirectional_iterator.hpp"
# include "node.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> >>
	class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type,mapped_type> value_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;
			typedef std::allocator<ft::node<ft::pair<const Key,T>>> node_allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef bidirectional_iterator<Key, T> iterator;
			typedef bidirectional_iterator<Key, T> const_iterator;
			typedef rev_iterator<Key, T> reverse_iterator;
			typedef rev_iterator<const Key, T> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;
			typedef ft::node<value_type>* node;
			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				friend class map<Key, T, Compare, Alloc>;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					bool operator() (const value_type& x, const value_type& y) const{
						return comp(x.first, y.first);
					}
			};

		private:
			allocator_type _alloc;
			node_allocator_type _node_alloc;
			size_type _size;
			key_compare _comp;
			node _root;
			node _end;
			node _begin;

			node create_node(key_type first, mapped_type second, node parent){
				node tmp = this->_node_alloc.allocate(1);
				this->_node_alloc.construct(tmp, ft::node<value_type>(ft::make_pair<const key_type,mapped_type>(first, second), parent, nullptr, nullptr));
				return tmp;
			}

			node insert_node(node n, key_type first, mapped_type second){
				if (!this->_root->data.first)
				{
					this->_root = this->create_node(first, second, n);
					this->_root->parent = nullptr;
					return this->_root;
				}
				if (first < n->data.first)
				{
					if(n->left == nullptr)
					{
						n->left = this->create_node(first, second, n);
						return (n->left);
					}
					else
						return this->insert_node(n->left, first, second);
				}
				else {
					if (n->right == this->_end){
						n->right = this->create_node(first, second, n);
						this->_end->parent = n->right;
						return (n->right);
					}
					if(n->right == nullptr)
					{
						n->right = this->create_node(first, second, n);
						return (n->right);
					}
					else
						return this->insert_node(n->right, first, second);
				}
				return(n);
			}

			node find_node(node n, key_type first)
			{
				node tmp;
				if (n->data.first == first)
					return n;
				if (n->right != nullptr){
					if ((tmp = this->find_node(n->right, first)))
						return tmp;
				}
				if (n->left != nullptr){
					if ((tmp = this->find_node(n->left, first)))
						return tmp;
				}
				return 0;
			}

			void deep_clear(node n){
				if (n->right)
					deep_clear(n->right);
				if (n->left)
					deep_clear(n->left);
				if (n != this->_begin){
					this->_node_alloc.destroy(n);
					this->_node_alloc.deallocate(n, 1);
				}
			}

			void delete_node(node n){
				if (this->size() == 0) {
					this->_node_alloc.destroy(n);
					this->_root = this->_node_alloc.allocate(1);
					this->_node_alloc.construct(this->_root, ft::node<value_type>());
					this->_root->right = this->create_node(key_type(), mapped_type(), this->_root);
					this->_end = this->_root->right;
					this->_root->left = this->create_node(key_type(), mapped_type(), this->_root);
					this->_begin = this->_root->left;
					return;
				}
				if (n == this->_root && n->right != this->end().ptr){
					if (n->right != nullptr){
						this->_root = n->right;
						n->right->parent = nullptr;
						if (n->left != nullptr)
							n->left->parent = n->right;
					}
					this->_node_alloc.destroy(n);
					this->_node_alloc.deallocate(n, 1);
					return;
				}
				if (n == this->_root && n->right == this->end().ptr){
					if (n->left != nullptr){
						this->_root = n->left;
						n->left->parent = nullptr;
					}
					n->right->parent = nullptr;
					this->_node_alloc.destroy(n);
					this->_node_alloc.deallocate(n, 1);
					return;
				}
				node tmp = n->parent;
				if (n->left == nullptr && n->right == nullptr){
					if (tmp->right == n)
						tmp->right = nullptr;
					else
						tmp->left = nullptr;
				} else if (n->left == nullptr && n->right != nullptr) {
					if (tmp->right == n){
						tmp->right = n->right;
					}
					else
						tmp->left = n->right;
					n->right->parent = tmp;
				} else if (n->left != nullptr && n->right == nullptr) {
					if (tmp->right == n)
						tmp->right = n->left;
					else
						tmp->left = n->left;
					n->left->parent = tmp;
				}
				this->_node_alloc.destroy(n);
				this->_node_alloc.deallocate(n, 1);
				n = nullptr;
			}

		public:

		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());
		map (iterator first, iterator last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());
		map (const map& x);
		~map();
		map& operator= (const map& x);

		iterator begin() {
			iterator tmp = iterator(this->_begin->parent);
			if (this->_begin->data.first){
				this->_node_alloc.destroy(this->_begin);
				this->_node_alloc.deallocate(this->_begin, 1);}
			tmp.ptr->left = nullptr;
			node n = this->_root;
			while (n->left != nullptr)
				n = n->left;
			return iterator(n); }

		const_iterator begin() const {
			iterator tmp = iterator(this->_begin->parent);
			tmp.ptr->left = nullptr;
			node n = this->_root;
			while (n->left != nullptr)
				n = n->left;
			return const_iterator(n);}

		iterator end() {
			iterator tmp = iterator(this->_end->parent);
			this->_node_alloc.destroy(this->_end);
			this->_node_alloc.deallocate(this->_end, 1);
			tmp.ptr->right = nullptr;
			node n = this->_root;
			while (n->right != nullptr)
				n = n->right;
			n->right = this->create_node(key_type(), mapped_type(), n);
			this->_end = n->right;
			return iterator(this->_end);}

		const_iterator end() const {
			iterator tmp = iterator(this->_end->parent);
			this->_node_alloc.destroy(this->_end);
			this->_node_alloc.deallocate(this->_end, 1);
			tmp.ptr->right = nullptr;
			const node n = this->_root;
			while (n->right != nullptr)
				n = n->right;
			n->right = this->create_node(key_type(), mapped_type(), n);
			this->_end = n->right;
			return const_iterator(this->_end);}

		reverse_iterator rbegin(){
			iterator tmp = this->end();
			return reverse_iterator(tmp.ptr->parent);}

		const_reverse_iterator rbegin() const{
			iterator tmp = this->end();
			return const_reverse_iterator(tmp.ptr->parent);}

		reverse_iterator rend()
		{
			iterator tmp = iterator(this->_begin->parent);
			this->_node_alloc.destroy(this->_begin);
			this->_node_alloc.deallocate(this->_begin, 1);
			tmp.ptr->left = nullptr;
			node n = this->_root;
			while (n->left != nullptr)
				n = n->left;
			n->left = this->create_node(key_type(), mapped_type(), n);
			this->_begin = n->left;
			return reverse_iterator(this->_begin);
		}

		const_reverse_iterator rend() const{
			iterator tmp = iterator(this->_begin->parent);
			this->_node_alloc.destroy(this->_begin);
			this->_node_alloc.deallocate(this->_begin, 1);
			tmp.ptr->left = nullptr;
			node n = this->_root;
			while (n->left != nullptr)
				n = n->left;
			n->left = this->create_node(key_type(), mapped_type(), n);
			this->_begin = n->left;
			return const_reverse_iterator(this->_begin);
		}

		bool empty() const {return this->_size == 0;}
		size_type size() const {return this->_size;}
		size_type max_size() const {
			return std::numeric_limits<size_type>::max() / (sizeof(value_type)) / 2;}

		mapped_type& operator[] (const key_type& k);

		pair<iterator,bool> insert (const value_type& val);
		iterator insert (iterator position, const value_type& val);
		void insert (iterator first, iterator last);
		void erase (iterator position);
		size_type erase (const key_type& k);
		void erase (iterator first, iterator last);
		void swap (map& x);
		void clear();

		key_compare key_comp() const {return this->_comp;}
		value_compare value_comp() const {return value_compare(key_compare());}

		iterator find (const key_type& k);
		const_iterator find (const key_type& k) const;
		size_type count (const key_type& k) const;
		iterator lower_bound (const key_type& k);
		const_iterator lower_bound (const key_type& k) const;
		iterator upper_bound (const key_type& k);
		const_iterator upper_bound (const key_type& k) const;
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
		pair<iterator,iterator>             equal_range (const key_type& k);

		allocator_type get_allocator() const {
			return this->_alloc;
		}
	};

	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(const key_compare& comp, const allocator_type& alloc)
	{
		this->_alloc = alloc;
		this->_node_alloc = node_allocator_type();
		this->_comp = comp;
		this->_size = 0;
		this->_root = this->_node_alloc.allocate(1);
		this->_node_alloc.construct(this->_root, ft::node<value_type>());
		this->_root->right = this->create_node(key_type(), mapped_type(), this->_root);
		this->_end = this->_root->right;
		this->_root->left = this->create_node(key_type(), mapped_type(), this->_root);
		this->_begin = this->_root->left;
	}

	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(iterator first, iterator last, const key_compare& comp,
			const allocator_type& alloc)
	{
		this->_alloc = alloc;
		this->_node_alloc = node_allocator_type();
		this->_comp = comp;
		this->_size = 0;
		this->_root = this->_node_alloc.allocate(1);
		this->_node_alloc.construct(this->_root, ft::node<value_type>());
		this->_root->right = this->create_node(key_type(), mapped_type(), this->_root);
		this->_end = this->_root->right;
		this->_root->left = this->create_node(key_type(), mapped_type(), this->_root);
		this->_begin = this->_root->left;
		this->insert(first, last);
	}

	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(const map& x)
	{
		this->_alloc = x._alloc;
		this->_node_alloc = node_allocator_type();
		this->_comp = x._comp;
		this->_size = 0;
		this->_root = this->_node_alloc.allocate(1);
		this->_node_alloc.construct(this->_root, ft::node<value_type>());
		this->_root->right = this->create_node(key_type(), mapped_type(), this->_root);
		this->_end = this->_root->right;
		this->_root->left = this->create_node(key_type(), mapped_type(), this->_root);
		this->_begin = this->_root->left;
		iterator begin = x.begin();
		for (size_t i = 0; i < x._size; i++)
		{
			this->insert(begin, begin.ptr->data);
			++begin;
		}
	}

	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::~map() {
		this->deep_clear(this->_root);
		this->_node_alloc.destroy(this->_begin);
		this->_node_alloc.deallocate(this->_begin, 1);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::map& map<Key, T, Compare, Alloc>::operator= (const map& x){
		this->deep_clear(this->_root);
		this->_node_alloc.destroy(this->_begin);
		this->_node_alloc.deallocate(this->_begin, 1);
		this->_alloc = x._alloc;
		this->_node_alloc = node_allocator_type();
		this->_comp = x._comp;
		this->_size = 0;
		this->_root = this->_node_alloc.allocate(1);
		this->_node_alloc.construct(this->_root, ft::node<value_type>());
		this->_root->right = this->create_node(key_type(), mapped_type(), this->_root);
		this->_end = this->_root->right;
		this->_root->left = this->create_node(key_type(), mapped_type(), this->_root);
		this->_begin = this->_root->left;
		iterator begin = x.begin();
		for (size_t i = 0; i < x._size; i++)
		{
			this->insert(begin, begin.ptr->data);
			++begin;
		}
		return *this;
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::find (const key_type& k){
		node tmp = this->find_node(this->_root, k);
		if (tmp == 0){
			return this->end();
		}
		return iterator(tmp);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::find (const key_type& k) const{
		node tmp = this->find_node(this->_root, k);
		if (tmp == 0)
			return this->end();
		return const_iterator(tmp);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type map<Key, T, Compare, Alloc>::count (const key_type& k) const{
		const_iterator begin = this->begin();
		for (size_t i = 0; i < this->_size; i++) {
			if (begin.ptr->data.first == k)
				return 1;
			++begin;
		}
		return 0;
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::lower_bound (const key_type& k) {
		iterator begin = this->begin();
		for (size_t i = 0; i < this->_size; i++) {
			if (this->_comp(begin.ptr->data.first, k) == 0)
				return begin;
			++begin;
		}
		return this->end();
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::lower_bound (const key_type& k) const {
		const_iterator begin = this->begin();
		for (size_t i = 0; i < this->_size; i++) {
			if (this->_comp(begin.ptr->data.first, k) == 0)
				return begin;
			++begin;
		}
		return this->end();
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::upper_bound (const key_type& k) {
		iterator begin = this->begin();
		for (size_t i = 0; i < this->_size; i++) {
			if (this->_comp(begin.ptr->data.first, k) == 0)
				return ++begin;
			++begin;
		}
		return this->end();
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::upper_bound (const key_type& k) const {
		const_iterator begin = this->begin();
		for (size_t i = 0; i < this->_size; i++) {
			if (this->_comp(begin.ptr->data.first, k) == 0)
				return ++begin;
			++begin;
		}
		return this->end();
	}

	template <class Key, class T, class Compare, class Alloc>
	T& map<Key, T, Compare, Alloc>::operator[] (const Key& k){
		if (this->find(k) != this->end())
			return this->find(k).ptr->data.second;
		this->insert(ft::make_pair<const Key, T>(k, T()));
		return this->find(k)->second;
	}

	template <class Key, class T, class Compare, class Alloc>
	ft::pair<typename map<Key, T, Compare, Alloc>::const_iterator, typename map<Key, T, Compare, Alloc>::const_iterator>
	map<Key, T, Compare, Alloc>::equal_range (const key_type& k) const {
		return ft::make_pair<const Key, T>(this->lower_bound(k), this->upper_bound(k));
	}

	template <class Key, class T, class Compare, class Alloc>
	ft::pair<typename map<Key, T, Compare, Alloc>::iterator, typename map<Key, T, Compare, Alloc>::iterator>
	map<Key, T, Compare, Alloc>::equal_range (const key_type& k) {
		return ft::make_pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k));
	}


	template <class Key, class T, class Compare, class Alloc>
	ft::pair<typename map<Key, T, Compare, Alloc>::iterator,bool> map<Key, T, Compare, Alloc>::insert (const value_type& val){
		if (this->find(val.first) != this->end())
			return (ft::make_pair(this->find(val.first), false));
		++this->_size;
		return (ft::make_pair(iterator(this->insert_node(this->_root, val.first, val.second)), true));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::insert (iterator position, const value_type& val){
		if (this->find(val.first) != this->end())
			return this->end();
		iterator tmp = this->find(val.first);
		if (tmp != this->end())
			return tmp;
		++this->_size;
		return iterator(this->insert_node(this->_root, val.first, val.second));
	}

	template <class Key, class T, class Compare, class Alloc>
	void map<Key, T, Compare, Alloc>::insert (iterator first, iterator last){
		while (first != last) {
			if (this->find(first->first) == this->end())
				this->insert(*first);
			++first;
		}
	}

	template <class Key, class T, class Compare, class Alloc>
	void map<Key, T, Compare, Alloc>::erase (iterator position){
		this->_size--;
		this->delete_node(position.ptr);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type map<Key, T, Compare, Alloc>::erase (const key_type& k){
		iterator it = this->find(k);
		if (it != iterator(this->_end)){
			this->erase(it);
			return 1;
		}
		return 0;
	}

	template <class Key, class T, class Compare, class Alloc>
	void map<Key, T, Compare, Alloc>::erase (iterator first, iterator last){
		while (first != last)
		{
			this->erase(first);
			++first;
		}
	}

	template <class Key, class T, class Compare, class Alloc>
	void map<Key, T, Compare, Alloc>::swap (map& x){
		node root = this->_root;
		this->_root = x._root;
		x._root = root;
	}

	template <class Key, class T, class Compare, class Alloc>
	void map<Key, T, Compare, Alloc>::clear() {
		this->erase(this->begin(), this->end());
	}
}

#endif
