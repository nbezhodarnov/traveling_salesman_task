#include <iostream>
#include "bintree.h"

using namespace std;

node* bintree::tree(int n, node *p) {
	if (n == 0) return NULL;
	node *child = new node(rand() % 100);
	child->parent = p;
	int n_left = (n - 1) / 2, n_right = n - 1 - n_left;
	child->left = tree(n_left, child);
	child->right = tree(n_right, child);
	return child;
};

void bintree::copy(node *old, bool is_left, node *new1) {
	if (old == NULL) return;
	node *child = new node(old->key);
	child->parent = new1;
	if (is_left) new1->left = child;
	else new1->right = child;
	copy(old->left, true, child);
	copy(old->right, false, child);
};

void bintree::create(int *a, int begin, node *p, int end) {
	if (begin > end) return;
	if (begin == end) {
		p->right = new node(a[begin], NULL, NULL, p);
		return;
	}
	p->left = new node(a[begin], NULL, NULL, p);
	p->right = new node(a[begin + (end - begin + 1) / 2], NULL, NULL, p);
	if ((begin - end) != 1) {
		create(a, begin + 1, p->left, begin - 1 + (end - begin + 1) / 2);
		create(a, begin + 1 + (end - begin + 1) / 2, p->right, end);
	}
};

bintree::bintree(int n) {
	root = tree(n, 0);
};

bintree::bintree(int *a, int n) {
	root = new node(a[0]);
	create(a, 1, root, n - 1);
};

bintree::bintree(bintree &old) {
	if (old.root) {
		root = new node(old.root->key);
		if (old.root->left) {
			copy(old.root->left, true, root);
		}
		if (old.root->right) {
			copy(old.root->right, false, root);
		}
	} else {
		root = NULL;
	}
};

void bintree::add(int k, node *p) {
	if (p->left == NULL) {
		node *child = new node(k);
		p->left = child;
		child->parent = p;
		return;
	}
	if (p->right == NULL) {
		node *child = new node(k);
		p->right = child;
		child->parent = p;
		return;
	}

	if (rand() % 2) {
		add(k, p->right);
	} else {
		add(k, p->left);
	}
};

void bintree::del(node *p) {
	node *temp = p->parent;

	if ((p->left == NULL) && (p->right == NULL)) {
		if (temp->left == p) {
			temp->left = NULL;
		} else {
			temp->right = NULL;
		}
		delete p;
		return;
	}

	if ((p->left == NULL) && (p->right)) {
		p->right->parent = temp;
		if (temp->left == p) {
			temp->left = p->right;
		} else {
			temp->right = p->right;
		}
		delete p;
		return;
	}

	if ((p->left) && (p->right == NULL)) {
		p->left->parent = temp;
		if (temp->left == p) {
			temp->left = p->left;
		} else {
			temp->right = p->left;
		}
		delete p;
		return;
	}

	node *runner = p->left;
	while (runner->left) runner = runner->left;
	if (runner->right == NULL) {
		//if (runner->parent->left == runner) {
			runner->parent->left = NULL;
		/*} else {
			runner->parent->right = NULL;
		}*/
		runner->left = p->left;
		runner->right = p->right;
		if (runner->left) runner->left->parent = runner;
		runner->right->parent = runner;
		runner->parent = temp;
		if (temp->left == p) {
			temp->left = runner;
		} else {
			temp->right = runner;
		}
	} else {
		runner->parent->left = runner->right;
		runner->right->parent = runner->parent;
		runner->right = p->right;
		runner->left = p ->left;
		runner->left->parent = runner;
		runner->right->parent = runner;
		if (temp->left == p) {
			temp->left = runner;
		} else {
			temp->right = runner;
		}
		runner->parent = temp;
	}
	delete p;
};
void bintree::tree_traversal_LCR(node *p) {
	if (p->left) tree_traversal_LCR(p->left);
	cout << p << ' ';
	if (p->right) tree_traversal_LCR(p->right);
};

void bintree::tree_traversal_LRC(node *p) {
	if (p->left) tree_traversal_LRC(p->left);
	if (p->right) tree_traversal_LRC(p->right);
	cout << p << ' ';
};

void bintree::tree_traversal_RLC(node *p) {
	if (p->right) tree_traversal_RLC(p->right);
	if (p->left) tree_traversal_RLC(p->left);
	cout << p << ' ';
};

void bintree::tree_traversal_by_levels(element *temp) {
	if (temp == NULL) return;
	if (temp->link) {
		cout << temp->link << ' ';
		element *end = temp;
		while (end->next) end = end->next;
		if ((temp->link->left) || (temp->link->right))end->next = new element(temp->link->left, new element(temp->link->right, 0));
		element *t = temp->next;
		delete temp;
		tree_traversal_by_levels(t);
	} else {
		cout << "- ";
		element *t = temp->next;
		delete temp;
		tree_traversal_by_levels(t);
	}
};

bintree::~bintree() {
	if (root) {
		while (root->left) del(root->left);
		while (root->right) del(root->right);
		delete root;
		root = NULL;
	}
};

node* bintree::find_key(int k, node *p) {
	if ((!p) || (p->key == k)) return p;

	node *temp = find_key(k, p->left);
	if ((temp) && (temp->key == k)) return p;
	return find_key(k, p->right);
};

node* bintree::find_min(node *p) {
	if (!p) return p;

	node *temp = find_min(p->left), *temp2 = find_min(p->right);
	if ((temp) && (temp2)) {
		if ((temp->key <= p->key) && (temp->key <= temp2->key)) return temp;
		if ((temp2->key <= p->key) && (temp2->key <= temp->key)) return temp2;
		return p;
	}
	if (temp) {
		if (temp->key <= p->key) return temp;
		return p;
	}
	if (temp2) {
		if (temp2->key <= p->key) return temp2;
		return p;
	}
	return p;
};

node* bintree::find_min_leaf(node *p) {
	if (!p) return p;

	node *temp = find_min_leaf(p->left), *temp2 = find_min_leaf(p->right);
	if ((temp) && (temp2)) {
		if (temp->key <= temp2->key) return temp;
		return temp2;
	}
	if (temp) return temp;
	if (temp2) return temp2;
	return p;
};

node* bintree::find_max(node *p) {
	if (!p) return p;

	node *temp = find_max(p->left), *temp2 = find_max(p->right);
	if ((temp) && (temp2)) {
		if ((temp->key >= p->key) && (temp->key >= temp2->key)) return temp;
		if ((temp2->key >= p->key) && (temp2->key >= temp->key)) return temp2;
		return p;
	}
	if (temp) {
		if (temp->key >= p->key) return temp;
		return p;
	}
	if (temp2) {
		if (temp2->key >= p->key) return temp2;
		return p;
	}
	return p;
};

void bintree::print_tree(node *p, int position) {
	if (p == NULL) return;
	print_tree(p->right, position + 5);
	for (int i = 0; i < position; ++i) cout << ' ';
	cout << p << '\n';
	print_tree(p->left, position + 5);
};

int bintree::height(node *p, int h) {
	if (p == NULL) return h;
	
	int left_height = height(p->left, h + 1), right_height = height(p->right, h + 1);
	if (left_height >= right_height) return left_height;
	return right_height;
};

void bintree::clean() {
	if (root) {
		while (root->left) del(root->left);
		while (root->right) del(root->right);
		delete root;
		root = NULL;
	}
};

bintree & bintree::operator=(bintree &old) {
	clean();
	if (old.root) {
		root = new node(old.root->key);
		if (old.root->left) {
			copy(old.root->left, true, root);
		}
		if (old.root->right) {
			copy(old.root->right, false, root);
		}
	} else {
		root = NULL;
	}
	return *this;
};