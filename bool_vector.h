#ifndef BOOL_VECTOR_H
#define BOOL_VECTOR_H

#include <iostream>
//#include <stdint.h>

using namespace std;

typedef unsigned char ui8;

class bool_vector {
	ui8 *bv;
	int n, m;

	void fill_bv(char*);
	void fill_bv(char, int);

	public:
	bool_vector(int);
	bool_vector(char*);
	bool_vector(char*, int);
	bool_vector(const bool_vector &);
	~bool_vector(){
		delete []bv;
	}
	void scan(int);
	void print();
	friend ostream & operator<<(ostream &, bool_vector const&);
	friend istream & operator>>(istream &, bool_vector &);
	bool operator[](int);
	int weigth();
	void set_true(int);
	void set_false(int);
	void invert(int);
	void set_true(int, int);
	void set_false(int, int);
	void invert(int, int);
	bool_vector & operator=(bool_vector &);
	bool_vector & operator+(bool_vector &);
	bool_vector & operator+(char *);
	bool operator==(bool_vector &);
	bool operator!=(bool_vector &);
	bool operator>(bool_vector &);
	bool operator<(bool_vector &);
	bool_vector & operator~();
	bool_vector & operator|(bool_vector &);
	bool_vector & operator&(bool_vector &);
	bool_vector & operator^(bool_vector &);
	bool_vector & operator<<(int);
	bool_vector & operator>>(int);
	bool_vector & operator|=(bool_vector &);
	bool_vector & operator&=(bool_vector &);
	bool_vector & operator^=(bool_vector &);
	bool_vector & operator<<=(int);
	bool_vector & operator>>=(int);
	/*int find(double);
	massif & operator+=(double);
	massif & operator+(double);
	massif & operator+=(massif &);
	massif & operator+(massif &);
	massif & operator-=(int);
	massif & operator-(double);
	int max();
	int min();
	void sorting(char);
	massif & operator-(massif &);
	int is_sorted();*/
};

#endif