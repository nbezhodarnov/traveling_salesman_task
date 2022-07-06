#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>

using namespace std;

class matrix {
	protected:
	double **a;
	int n;
	
	public:
	matrix() {
		a = NULL;
		n = 0;
	}
	matrix(double **, int);
	matrix(matrix &);
	matrix & operator=(matrix &);
	int normalize();
	void inf(int, int, bool);
	double* operator[](int i){
		if ((i >= 0) && (i < n)) return a[i];
		return NULL;
	}
	virtual ~matrix();
};

matrix::matrix(double **input, int k) {
	n = k;
	a = new double*[n];
	for (int i = 0; i < n; ++i) {
		a[i] = new double[n];
		for (int j = 0; j < n; ++j) {
			a[i][j] = input[i][j];
		}
	}
}

matrix::matrix(matrix &x) {
	/*if (x != NULL)*/ {
		n = x.n;
		a = new double*[n];
		for (int i = 0; i < n; ++i) {
			a[i] = new double[n];
			for (int j = 0; j < n; ++j) {
				a[i][j] = x.a[i][j];
			}
		}
	} /*else {
		a = NULL;
		n = 0;
	}*/
}

matrix & matrix::operator=(matrix &x) {
	if (this != &x) {
		if (a) {
			for (int i = 0; i < n; ++i) {
				delete []a[i];
			}
			delete []a;
		}
		n = x.n;
		a = new double*[n];
		for (int i = 0; i < n; ++i) {
			a[i] = new double[n];
			for (int j = 0; j < n; ++j) {
				a[i][j] = x.a[i][j];
			}
		}
	}
	return *this;
}

void matrix::inf(int line, int coloumn, bool is) {
	if (is) {
		for(int i = 0; i < n; ++i) {
			a[i][coloumn] = a[line][i] = INFINITY;
		}
		a[coloumn][line] = INFINITY;
	} else {
		a[line][coloumn] = INFINITY;
	}
}

int matrix::normalize() {
	double *min_lines = new double[n], *min_coloumns = new double[n];
	for (int i = 0; i < n; ++i) {
		min_lines[i] = INFINITY;
		for (int j = 0; j < n; ++j) {
			if (a[i][j] < min_lines[i]) min_lines[i] = a[i][j];
		}
		if (min_lines[i] != INFINITY) for (int j = 0; j < n; ++j) {
			a[i][j] -= min_lines[i];
		}
	}
	for (int i = 0; i < n; ++i) {
		min_coloumns[i] = INFINITY;
		for (int j = 0; j < n; ++j) {
			if (a[j][i] < min_coloumns[i]) min_coloumns[i] = a[j][i];
		}
		if (min_coloumns[i] != INFINITY) for (int j = 0; j < n; ++j) {
			a[j][i] -= min_coloumns[i];
		}
	}
	int result;
	double sum = 0;
	for (int i = 0; i < n; ++i) {
		if (min_lines[i] != INFINITY) sum += min_lines[i];
		if (min_coloumns[i] != INFINITY) sum += min_coloumns[i];
	}
	result = sum;
	delete []min_lines;
	delete []min_coloumns;
	/*int in = 0, out = 0;
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
					max = min_line + min_coloumn;
					in = i;
					out = j;
				}
			}
		}
	}
	if (max = -INFINITY) {
		result[3] = -1;
	} else {
		result[0] = in;
		result[1] = out;
		result[3] = (int)max;
	}*/
	return result;
}

matrix::~matrix() {
	if (a) {
		for (int i = 0; i < n; ++i) {
			delete []a[i];
		}
		delete []a;
	}
}

#endif