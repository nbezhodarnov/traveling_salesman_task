#include <iostream>
#include <conio.h>
#include <stdio.h>

#include "matrix.h"
#include "bintree.hpp"
#include "bool_vector.hpp"

using namespace std;

double** map_creating(int n, int min, int max) {
	cout << "Map:\n   ";
	for (int i = 1; i <= n; ++i) {
		printf("%3d ", i);
	}
	cout << '\n';
	double **a = new double*[n];
	for (int i = 0; i < n; ++i) {
		printf("%3d ", i + 1);
		a[i] = new double[n];
		for (int j = 0; j < i; ++j) {
			a[i][j] = rand() % (max - min) + min;
			printf("%3d ", (int)a[i][j]);
		}
		a[i][i] = INFINITY;
		//printf("%3d ", a[i][i]);
		cout << "inf ";
		for (int j = i + 1; j < n; ++j) {
			a[i][j] = rand() % (max - min) + min;
			printf("%3d ", (int)a[i][j]);
		}
		cout << '\n';
	}
	return a;
}

int* step(bintree &tree, node *parent, int n) {
	int *temp, temp2, *result;
	node* node_temp;
	//temp = parent->normalize();
	result = new int[n];
	for (int i = 0; i < n; ++i) result[i] = parent->arr[i];
	matrix way1 = *parent, way2 = *parent;
	temp = parent->get_branch();
	if (temp[0] != -1) {
		way1.inf(temp[0], temp[1], true);
		way2.inf(temp[0], temp[1], false);
		//delete[]temp;
		temp2 = way2.normalize();
		node_temp = new node(parent->key + temp2, 0, 0, parent, &way2, result, n);
		parent->left = node_temp;
		//delete[]temp;
		temp2 = way1.normalize();
		result[temp[0]] = temp[1];
		node_temp = new node(parent->key + temp2, 0, 0, parent, &way1, result, n);
		delete[]result;
		parent->right = node_temp;
	}
	delete[]temp;
	bool done = true;
	for (int i = 0; i < n; ++i) {
		if (parent->arr[i] == -1) {
			for (int j = i + 1; j < n; ++j) {
				if (parent->arr[j] == -1) {
					done = false;
					break;
				}
			}
			if (!done) break;
		}
	}
	if (!done) return step(tree, tree.find_min_leaf(), n);
	result = new int[n];
	for (int i = 0; i < n; ++i) result[i] = parent->arr[i];
	return result;
}

int* branch_and_bound(double **a, int n) {
	matrix ways(a, n);
	int temp, *result;
	temp = ways.normalize();
	result = new int[n];
	for (int i = 0; i < n; ++i) result[i] = -1;
	node *node_temp = new node(temp, 0, 0, 0, &ways, result, n);
	delete []result;
	bintree tree(node_temp);
	result = step(tree, tree.root_get(), n);
	bool_vector last(n);
	for (int i = 0; i < n; ++i) last.set_true(result[i]);
	int k = 0;
	while (last[k]) k++;
	for (int i = 0; i < n; ++i) {
		if (result[i] == -1) {
			result[i] = k;
			break;
		}
	}
	return result;
}

int main() {
	double **a;
	int n;
	cout << "Input number of cities: ";
	cin >> n;
	a = map_creating(n, 1, 99);
	/*a = new double*[n];
	for (int i = 0; i < n; ++i) {
		a[i] = new double[n];
		for (int j = 0; j < i; ++j) {
			cin >> a[i][j];
		}
		cin >> a[i][i];
		a[i][i] = INFINITY;
		for (int j = i + 1; j < n; ++j) {
			cin >> a[i][j];
		}
	}*/
	int *result = branch_and_bound(a, n);
	cout << "Way: 1 -";
	int i = 0;
	while (result[i]) {
		cout << a[i][result[i]] << "-> " << result[i] + 1 << " -";
		i = result[i];
	}
	cout << a[i][result[i]] << "-> 1" << "\nPrice: ";
	int total = 0;
	for (int j = 0; j < n; ++j) {
		total += a[j][result[j]];
	}
	cout << total << '\n';
	for (int i = 0; i < n; ++i) {
		delete[]a[i];
	}
	delete[]a;
	getch();
	return 0;
}