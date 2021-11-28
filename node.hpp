#ifndef NODE_H
# define NODE_H

# include "pair.hpp"

namespace ft{
template <class T>
	class node {
		public:

			T data;
			node* parent;
			node* left;
			node* right;

			node() : data(), parent(nullptr), left(nullptr), right(nullptr) {}
			node(const T &data) : data(data), parent(nullptr), left(nullptr), right(nullptr) {}
			node(node* parent, node* left, node* right) :
			data(), parent(parent), left(left), right(right) {}
			node(const T &data, node* parent, node* left, node* right) :
			data(data), parent(parent), left(left), right(right) {}
			node &operator=(const node &other){
				this->data = other.data;
				this->parent = other.parent;
				this->left = other.left;
				this->right = other.right;
				return (*this);
			}
			virtual ~node() {}

			bool operator==(const node &other) {return (this->data == other.data);}
			bool operator!=(const node &other) {return !(*this == other);}
	};
}
#endif
