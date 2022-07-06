#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include "matrix.h"

using namespace std;

bool isnt_cycle(int* r, int from, int to, int n) {
	int i = to, j = 1;
	while ((r[i] != -1) && (r[i] != to)) {
		i = r[i];
		j++;
	}
	if ((r[i] == to) && (j != n)) {
		return false;
	}
	return true;
}

class bintree;

class node: public matrix {
	//int key;
	node *left, *right, *parent;
	

public:
	int key, *arr, n;
	node(int k = 0, node *L = NULL, node *R = NULL, node *P = NULL, matrix *x = NULL, int *temp = NULL, int count = 0): matrix(*x) {
		key = k; left = L; right = R; parent = P; n = count;
		arr = new int[n];
		for (int i = 0; i < n; ++i) arr[i] = temp[i];
	};
	/*int Key() {
		return key;
	}*/
	friend ostream& operator<<(ostream &out, node *t) {
		if (t) out << t->key;
		else out << "Empty!";
		return out;
	};
	int* get_branch();
	~node() {
		if (arr) delete []arr;
	}
	friend class bintree;
	friend int* branch_and_bound(double**, int);
	friend int* step(bintree&, node*, int);
};

int* node::get_branch(){
	int *result = new int[3];
	int in = 0, out = 0;
	double min_line, min_coloumn, max = -INFINITY;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (a[i][j] == 0) {
				min_line = INFINITY;
				for (int k = 0; k < i; ++k) {
					if (a[i][k] < min_line) {
						min_line = a[i][k];
					}
				}
				for (int k = i + 1; k < n; ++k) {
					if (a[i][k] < min_line) {
						min_line = a[i][k];
					}
				}
				min_coloumn = INFINITY;
				for (int k = 0; k < j; ++k) {
					if (a[k][j] < min_coloumn) {
						min_coloumn = a[k][j];
					}
				}
				for (int k = j + 1; k < n; ++k) {
					if (a[k][j] < min_coloumn) {
						min_coloumn = a[k][j];
					}
				}
				if (((min_line + min_coloumn) != INFINITY) && ((min_line + min_coloumn) > max)) {
					int city = arr[i];
					arr[i] = j;
					if (isnt_cycle(arr, i, j, n)) {
						max = min_line + min_coloumn;
						in = i;
						out = j;
					} else {
						a[i][j] = INFINITY;
					}
					arr[i] = city;
				}
			}
		}
	}
	if (max == -INFINITY) {
		result[2] = result[0] = -1;
	} else {
		result[0] = in;
		result[1] = out;
		result[2] = (int)max;
		arr[in] = out;
		key += max;
	}
	return result;
}

struct element {
	node *link;
	element *next;
	element(node *l, element *n) {
		link = l;
		next = n;
	}
};

class bintree {
	node *root;

	node* tree(int, node*);
	void copy(node*, bool, node*);
	void create(int*, int, node*, int);

public:
	bintree() {
		root = NULL;
	};
	bintree(node *n) {
		root = n;
	}
	bintree(int);
	bintree(int*, int);
	bintree(bintree &);
	bintree & operator=(bintree &);

protected:
	void add(int, node*);
	void tree_traversal_LCR(node*);
	void tree_traversal_LRC(node*);
	void tree_traversal_RLC(node*);
	void tree_traversal_by_levels(element*);
	node* find_key(int, node*);
	node* find_min(node*);
	node* find_min_leaf(node*);
	node* find_max(node*);
	void print_tree(node*, int);
	int height(node*, int);

public:
	void add(int k) {
		add(k, root);
	};
	void del(node*);
	void tree_traversal_LCR() {
		tree_traversal_LCR(root);
	};
	void tree_traversal_LRC() {
		tree_traversal_LRC(root);
	};
	void tree_traversal_RLC() {
		tree_traversal_RLC(root);
	};
	void tree_traversal_by_levels(){
		element *start = new element(root, 0);
		tree_traversal_by_levels(start);
	};
	void print_tree() {
		print_tree(root, 0);
	};
	node* root_get() {
		return root;
	};
	~bintree();
	node* find_key(int k) {
		return find_key(k, root);
	};
	node* find_min() {
		return find_min(root);
	};
	node* find_min_leaf() {
		return find_min_leaf(root);
	};
	node* find_max() {
		return find_max(root);
	};
	void clean();
	bool empty() {
		if (root) return false;
		return true;
	};
	int height() {
		return height(root, 0);
	};
};

#endif