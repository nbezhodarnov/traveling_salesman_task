#include <iostream>
#include <istream>
#include <ostream>
#include <conio.h>
#include "bool_vector.h"

using namespace std;

void bool_vector::fill_bv(char *str) {
	ui8 p = 1;
	int s = (m - 1) * 8, r = 0;
	for (int k = 0; k < s; k = k + 8) {
		r = k / 8;
		bv[r] = 0;
		for (int i = 0; i < 8; ++i) {
			if (str[k + i] == '1') {
				bv[r] |= p;
			}
			p <<= 1;
		}
		p = 1;
	}
	bv[m - 1] = 0;
	int q = (n - 1) % 8 + 1;
	for (int i = 0; i < q; ++i) {
		if (str[s + i] == '1') {
			bv[m - 1] |= p;
		}
		p <<= 1;
	}
}

void bool_vector::fill_bv(char key, int pos) {
	int p = 1, q = pos / 8;
	p <<= pos % 8;
	bv[q] &= ~p;
	if (key == '1') {
		bv[q] |= p;
	}
}

bool_vector::bool_vector(int p = 1){
	if (p > 0) {
		m = (p - 1) / 8 + 1;
		bv = new ui8[m];
		n = p;
		for (int i = 0; i < m; ++i) {
			bv[i] = 0;
		}
	} else {
		cout << "Error! Impossible number of elements. ";
		m = n = 1;
		bv = new ui8[1];
		bv[0] = 0;
	}
}

bool_vector::bool_vector(char *p){
	if ((p[0] != '\0') && (p[0] != '\n')) {
		for (n = 0; (p[n] != '\0') && (p[n] != '\n'); ++n) {}
		m = (n - 1) / 8 + 1;
		bv = new ui8[m];
		for (int i = 0; i < m; ++i) {
			bv[i] = 0;
		}
		this->fill_bv(p);
	} else {
		bv = new ui8[1];
		n = m = 1;
		bv[0] = 0;
	}
}

bool_vector::bool_vector(char *p, int i){
	if (i > 0) {
		char *s;
		for (n = 0; (p[n] != '\0') && (p[n] != '\n'); ++n) {}
		if (n < i) {
			cout << "Error. Your string has less elements that you asked. Bollean vector will fill remaining elements with 0.\n";
			s = new char[i + 1];
			for (int j = 0; j < n; ++j) {
				s[j] = p[j];
			}
			for (int j = n; j < i; ++j) {
				s[j] = '0';
			}
			s[i] = '\0';
		} else {
			s = p;
		}
		n = i;
		m = (n - 1) / 8 + 1;
		bv = new ui8[m];
		for (int j = 0; j < m; ++j) {
			bv[j] = 0;
		}
		this->fill_bv(s);
		if (s != p) {
			delete s;
		}
	} else {
		cout << "Isn't it weird to call this function with empty string or i <= 0? ";
		bv = new ui8[1];
		n = m = 1;
		bv[0] = 0;
	}
}

bool_vector::bool_vector(const bool_vector &x){
		bv = new ui8[x.m];
		n = x.n;
		m = x.m;
		for (int i = 0; i < m; ++i) {
			bv[i] = x.bv[i];
		}
}
void bool_vector::scan(int c) {
	delete []bv;
	n = c;
	m = (n - 1) / 8 + 1;
	bv = new ui8[m];
	for (int i = 0; i < m; ++i) {
		bv[i] = 0;
	}
	char r;
	int i = 0;
	while (i < c) {
		r = getchar();
		if (/*(r == '0') || */(r == '1')) {
			this->fill_bv(r, i);
		}
		i++;
	}
	getchar();
}
	
void bool_vector::print() {
	int q = m - 1;
	ui8 p = 1;
	for (int k = 0; k < q; ++k) {
		for (int i = 0; i < 8; ++i) {
			if (bv[k] & p) {
				cout << '1';
			} else {
				cout << '0';
			}
			p = p << 1;
		}
		p = 1;
	}
	q = (n - 1) % 8 + 1;
	for (int i = 0; i < q; ++i) {
		if (bv[m - 1] & p) {
			cout << '1';
		} else {
			cout << '0';
		}
		p = p << 1;
	}
	cout << '\n';
}

ostream & operator<<(ostream &r, bool_vector const&x) {
	int q = x.m - 1;
	ui8 p = 1;
	for (int k = 0; k < q; ++k) {
		for (int i = 0; i < 8; ++i) {
			if (x.bv[k] & p) {
				r << '1';
			} else {
				r << '0';
			}
			p = p << 1;
		}
		p = 1;
	}
	q = (x.n - 1) % 8 + 1;
	for (int i = 0; i < q; ++i) {
		if (x.bv[x.m - 1] & p) {
			r << '1';
		} else {
			r << '0';
		}
		p = p << 1;
	}
	r << '\n';
	return r;
}

istream & operator>>(istream &r, bool_vector &x) {
	char c[80];
	int i = 1;
	c[0] = getchar();
	while(c[i - 1] != '\n') {
		c[i] = getchar();
		i++;
	}
	delete []x.bv;
	if (c[0] != '\n') {
		x.n = i - 1;
		x.m = (x.n - 1) / 8 + 1;
		x.bv = new ui8[x.m];
		for (int j = 0; j < x.m; ++j) {
			x.bv[j] = 0;
		}
		i = 0;
		while (i < x.n) {
			if (/*(c[i] == '0') || */(c[i] == '1')) {
				x.fill_bv('1', i);
			}
			i++;
		}
		return r;
	} else {
		x.bv = new ui8[1];
		x.m = x.n = 1;
		x.bv[0] = 0;
		return r;
	}
}

bool bool_vector::operator[](int i) {
	if ((i < 0) || (i > n - 1)) {
		cout << "Error! Out of boolean vector!\n";
		return false;
	}
	i = n - i - 1;
	ui8 p = 1;
	p <<= i % 8;
	return (bool)(bv[i / 8] & p);
}

bool_vector & bool_vector::operator=(bool_vector &x) {
	if (this != &x) {
		delete []bv;
		bv = new ui8[x.m];
		n = x.n;
		m = x.m;
		for (int i = 0; i < m; i++) {
			bv[i] = x.bv[i];
		}
	}
	return *this;
}

int bool_vector::weigth() {
	int total = 0;
	ui8 p = 1;
	for(int i = 0; i < m - 1; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (bv[i] & p) {
				total++;
			}
			p <<= 1;
		}
		p = 1;
	}
	int raw = n % 8;
	for (int j = 0; j < raw; ++j) {
		if (bv[m - 1] & p) {
			total++;
		}
		p <<= 1;
	}
	return total;
}

void bool_vector::set_true(int i) {
	if (i > n) {
		cout << "Error. Out of boolean vector.\n";
		return;
	}
	i = n - 1 - i;
	ui8 p = 1;
	p <<= i % 8;
	bv[i / 8] |= p;
}

void bool_vector::set_false(int i) {
	if (i > n) {
		cout << "Error. Out of boolean vector.\n";
		return;
	}
	i = n - 1 - i;
	ui8 p = 1;
	p <<= i % 8;
	p = ~p;
	bv[i / 8] &= p;
}

void bool_vector::invert(int i) {
	if (i > n) {
		cout << "Error. Out of boolean vector.\n";
		return;
	}
	i = n - 1 - i;
	ui8 p = 1;
	p <<= i % 8;
	if (bv[i / 8] & p) {
		bv[i / 8] &= ~p;
	} else {
		bv[i / 8] |= p;
	}
}

void bool_vector::set_true(int pos, int count) {
	if (pos > n) {
		cout << "Error. Out of boolean vector.\n";
		return;
	}
	if ((pos + count) > n) {
		count = n - pos;
	}
	if (count <= 0) {
		cout << "Error. Impossible number of elements.\n";
		return;
	}
	pos = n - 1 - pos;
	ui8 p = 1;
	int i = pos % 8;
	//p <<= i;
	int raw2 = pos / 8;
	if (count > (i + 1)) {
		for (; i >= 0; --i) {
			bv[raw2] |= p;
			p <<= 1;
			count--;
		}
		int raw1 = count / 8;
		raw2--;
		for (int j = 0; j < raw1; ++j) {
			bv[raw2 - j] = 255;
			count -= 8;
		}
		if (count) {
			p = 255;
			p <<= (8 - count);
			bv[raw2 - raw1] |= p;
		}
	} else {
		for (int j = 0; j < count; ++j) {
			bv[raw2] |= p;
			p <<= 1;
		}
	}
}

void bool_vector::set_false(int pos, int count) {
	if (pos > n) {
		cout << "Error. Out of boolean vector.\n";
		return;
	}
	if ((pos + count) > n) {
		count = n - pos;
	}
	if (count <= 0) {
		cout << "Error. Impossible number of elements.\n";
		return;
	}
	pos = n - 1 - pos;
	ui8 p = 1;
	int i = pos % 8;
	//p <<= i;
	int raw2 = pos / 8;
	if (count > (1 + i)) {
		for (; i >= 0; --i) {
			bv[raw2] &= ~p;
			p <<= 1;
			count--;
		}
		int raw1 = count / 8;
		raw2--;
		for (int j = 0; j < raw1; ++j) {
			bv[raw2 - j] = 0;
			count -= 8;
		}
		if (count) {
			p = 255;
			p <<= (8 - count);
			bv[raw2 - raw1] &= ~p;
		}
	} else {
		for (int j = 0; j < count; ++j) {
			bv[raw2] &= ~p;
			p <<= 1;
		}
	}
}

void bool_vector::invert(int pos, int count) {
	if (pos > n) {
		cout << "Error. Out of boolean vector.\n";
		return;
	}
	if ((pos + count) > n) {
		count = n - pos;
	}
	if (count <= 0) {
		cout << "Error. Impossible number of elements.\n";
		return;
	}
	pos = n - 1 - pos;
	ui8 p = 1;
	int i = pos % 8;
	//p <<= i;
	int raw2 = pos / 8;
	if (count > (1 + i)) {
		for (; i >= 0; ++i) {
			if (bv[raw2] & p) {
				bv[raw2] &= ~p;
			} else {
				bv[raw2] |= p;
			}
			p <<= 1;
			count--;
		}
		int raw1 = count / 8;
		raw2--;
		for (int j = 0; j < raw1; ++j) {
			bv[raw2 - j] = ~bv[raw2 - j];
			count -= 8;
		}
		p = 1;
		raw2 -= raw1;
		for (int j = 0; j < count; ++j) {
			if (bv[raw2] & p) {
				bv[raw2] &= ~p;
			} else {
				bv[raw2] |= p;
			}
			p <<= 1;
		}
	} else {
		for (int j = 0; j < count; ++j) {
			if (bv[raw2] & p) {
				bv[raw2] &= ~p;
			} else {
				bv[raw2] |= p;
			}
			p <<= 1;
		}
	}
}

bool_vector & bool_vector::operator+(bool_vector &x) {
	bool_vector *result = new bool_vector(n + x.n);
	for (int i = 0; i < m; ++i) {
		result->bv[i] = bv[i];
	}
	/*for (int i = m; i < (result->m); ++i) {
		result->bv[i] = 0;
	}*/
	ui8 p = 1;
	int raw = n % 8;
	p <<= raw;
	if (raw + x.n < 8) {
		for (int i = 0; i < x.n; ++i) {
			if (x[i]) {
				result->bv[m - 1] |= p;
			}
			p <<= 1;
		}
	} else {
		int pos = 0;
		for (int i = raw; i < 8; ++i) {
			if (x[pos]) {
				result->bv[m - 1] |= p;
			}
			pos++;
			p <<= 1;
		}
		p = 1;
		for (int i = m; i < result->m - 1; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (x[pos]) {
					result->bv[i] |= p;
				}
				p <<= 1;
				pos++;
			}
			p = 1;
		}
		for (int i = pos; i < x.n; ++i) {
			if (x[pos]) {
				result->bv[result->m - 1] |= p;
			}
			p <<= 1;
			pos++;
		}
	}
	return *result;
}

bool_vector & bool_vector::operator+(char *s) {
	int n1;
	if ((s[0] != '\0') && (s[0] != '\n')) {
		for (n1 = 0; (s[n1] != '\0') && (s[n1] != '\n'); ++n1); 
	} else {
		bool_vector *rawbv = new bool_vector(*this);
		return *rawbv;
	}
	bool_vector *result = new bool_vector(n + n1);
	for (int i = 0; i < m; ++i) {
		result->bv[i] = bv[i];
	}
	ui8 p = 1;
	int raw = n % 8;
	p <<= raw;
	if (raw + n1 < 8) {
		for (int i = 0; i < n1; ++i) {
			if (s[i] == '1') {
				result->bv[m - 1] |= p;
			}
			p <<= 1;
		}
	} else {
		int pos = 0;
		for (int i = raw; i < 8; ++i) {
			if (s[pos] == '1') {
				result->bv[m - 1] |= p;
			}
			pos++;
			p <<= 1;
		}
		p = 1;
		for (int i = m; i < result->m - 1; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (s[pos] == '1') {
					result->bv[i] |= p;
				}
				p <<= 1;
				pos++;
			}
			p = 1;
		}
		for (int i = pos; i < n1; ++i) {
			if (s[pos] == '1') {
				result->bv[result->m - 1] |= p;
			}
			p <<= 1;
			pos++;
		}
	}
	return *result;
}

bool bool_vector::operator==(bool_vector &x) {
	if (n != x.n) {
		return false;
	} else {
		for (int i = 0; i < m; ++i){
			if (bv[i] != x.bv[i]) return false;
		}
		return true;
	}
}

bool bool_vector::operator!=(bool_vector &x) {
	if (n != x.n) {
		return true;
	} else {
		for (int i = 0; i < m; ++i){
			if (bv[i] != x.bv[i]) return true;
		}
		return false;
	}
}

bool bool_vector::operator>(bool_vector &x) {
	ui8 p1 = 128, p2 = 128;
	if (n > x.n) {
		int raw = 8 - n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((!(bv[m - 1] & p1)) && (x.bv[x.m - b] & p2)) {
					return false;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					if (x.m == 1) return true;
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((!(bv[m - b] & p1)) && (x.bv[x.m - 1] & p2)) {
					return false;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;
		for (int i = x.n - raw; i >= 0; --i) {
			if ((!(bv[(n + i - x.n) / 8] & p1)) && (x.bv[i / 8] & p2)) {
				return false;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		return true;
	} else {
		int raw = 8 - n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((!(bv[m - 1] & p1)) && (x.bv[x.m - b] & p2)) {
					return false;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((!(bv[m - b] & p1)) && (x.bv[x.m - 1] & p2)) {
					return false;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					if (m == 1) {
						while (p2) {
							if (x.bv[x.m - 1]  & p2) return false;
							p2 /= 2;
						}
						for (int i = x.m - 2; i > -1; --i) {
							if (x.bv[i]) return false;
						}
						return true;
					}
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;
		for (int i = n - raw; i >= 0; --i) {
			if ((!(bv[i / 8] & p1)) && (x.bv[(x.n + i - n) / 8] & p2)) {
				return false;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		raw = (x.n - n) / 8;
		if (x.n != n) {
			while (p2) {
				if (x.bv[raw] & p2) {
					return false;
				}
				p2 /= 2;
			}
			for (int i = raw - 1; i >= 0; --i) {
				if (x.bv[i]) {
					return false;
				}
			}
		}
		return true;
	}
}

bool bool_vector::operator<(bool_vector &x) {
	ui8 p1 = 128, p2 = 128;
	if (n > x.n) {
		int raw = 8 - n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - 1] & p1) && (!(x.bv[x.m - b] & p2))) {
					return false;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					if (x.m == 1) {
						while (p1) {
							if (bv[x.m - 1] & p1) return false;
							p1 /= 2;
						}
						for (int i = m - 2; i > -1; --i) {
							if (bv[i]) return false;
						}
						return true;
					}
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - b] & p1) && (!(x.bv[x.m - 1] & p2))) {
					return false;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;
		for (int i = x.n - raw; i >= 0; --i) {
			if ((bv[(n + i - x.n) / 8] & p1) && (!(x.bv[i / 8] & p2))) {
				return false;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		raw = (n - x.n) / 8;
		if (x.n != n) {
			while (p1) {
				if (bv[raw] & p1) {
					return false;
				}
				p1 /= 2;
			}
			for (int i = raw - 1; i >= 0; --i) {
				if (bv[i]) {
					return false;
				}
			}
		}
		return true;
	} else {
		int raw = 8 - n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - 1] & p1) && (!(x.bv[x.m - b] & p2))) {
					return false;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - b] & p1) && (!(x.bv[x.m - 1] & p2))) {
					return false;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					if (m == 1) return true;
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;
		for (int i = n - raw; i >= 0; --i) {
			if ((bv[i / 8] & p1) && (!(x.bv[(x.n + i - n) / 8] & p2))) {
				return false;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		return true;
	}
}

bool_vector & bool_vector::operator~() {
	bool_vector *result = new bool_vector(n);
	int raw2 = m - 1;
	for (int i = 0; i < raw2; ++i) {
		result->bv[i] = ~(bv[i]);
	}
	ui8 p = 1;
	int raw1 = n % 8;
	for (int j = 0; j < raw1; ++j) {
		if (!(bv[raw2] & p)) {
			result->bv[raw2] |= p;
		}
		p <<= 1;
	}
	return *result;
}

bool_vector & bool_vector::operator|(bool_vector &x) {
	ui8 p1 = 128, p2 = 128;
	if (n > x.n) {
		bool_vector *result = new bool_vector(n);
		int raw = 8 - n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		/*if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - 1] & p1) || (x.bv[x.m - b] & p2)) {
					result->bv[m - 1] |= p1;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - b] & p1) || (x.bv[x.m - 1] & p2)) {
					result->bv[m - b] |= p1;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;*/
		int raw2;
		for (int i = x.n - 1 /*- raw*/; i >= 0; --i) {
			raw2 = (n + i - x.n) / 8;
			if ((bv[raw2] & p1) || (x.bv[i / 8] & p2)) {
				result->bv[raw2] |= p1;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		raw = (n - x.n - 1) / 8;
		if (x.n != n) {
			while (p1) {
				if (bv[raw] & p1) {
					result->bv[raw] |= p1;
				}
				p1 /= 2;
			}
			for (int i = raw - 1; i >= 0; --i) {
				result->bv[i] = bv[i];
			}
		}
		return *result;
	} else {
		int raw = 8 - n % 8;
		bool_vector *result = new bool_vector(x.n);
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		/*if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - 1] & p1) || (x.bv[x.m - b] & p2)) {
					result->bv[x.m - b] |= p2;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - b] & p1) || (x.bv[x.m - 1] & p2)) {
					result->bv[x.m - 1] |= p2;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;*/
		int raw2;
		for (int i = n - 1/*- raw*/; i >= 0; --i) {
			raw2 = (x.n + i - n) / 8;
			if ((bv[i / 8] & p1) || (x.bv[raw2] & p2)) {
				result->bv[raw2] |= p2;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		raw = (x.n - n - 1) / 8;
		if (x.n != n) {
			while (p2) {
				if (x.bv[raw] & p2) {
					result->bv[raw] |= p2;
				}
				p2 /= 2;
			}
			for (int i = raw - 1; i >= 0; --i) {
				result->bv[i] = x.bv[i];
			}
		}
		return *result;
	}
}

bool_vector & bool_vector::operator&(bool_vector &x) {
	ui8 p1 = 128, p2 = 128;
	if (n > x.n) {
		bool_vector *result = new bool_vector(n);
		int raw = 8 - n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		/*if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - 1] & p1) && (x.bv[x.m - b] & p2)) {
					result->bv[m - 1] |= p1;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - b] & p1) && (x.bv[x.m - 1] & p2)) {
					result->bv[m - b] |= p1;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;*/
		int raw2;
		for (int i = x.n - 1 /*- raw*/; i >= 0; --i) {
			raw2 = (n + i - x.n) / 8;
			if ((bv[raw2] & p1) && (x.bv[i / 8] & p2)) {
				result->bv[raw2] |= p1;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		return *result;
	} else {
		int raw = 8 - n % 8;
		bool_vector *result = new bool_vector(x.n);
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		/*if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - 1] & p1) && (x.bv[x.m - b] & p2)) {
					result->bv[x.m - b] |= p2;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - b] & p1) && (x.bv[x.m - 1] & p2)) {
					result->bv[x.m - 1] |= p2;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;*/
		int raw2;
		for (int i = n - 1 /*- raw*/; i >= 0; --i) {
			raw2 = (x.n + i - n) / 8;
			if ((bv[i / 8] & p1) && (x.bv[raw2] & p2)) {
				result->bv[raw2] |= p2;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		return *result;
	}
}

bool_vector & bool_vector::operator^(bool_vector &x) {
	ui8 p1 = 128, p2 = 128;
	if (n > x.n) {
		bool_vector *result = new bool_vector(n);
		int raw = 8 - n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		/*if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if (((bv[m - 1] & p1) || (x.bv[x.m - b] & p2)) && (!((bv[m - 1] & p1) && (x.bv[x.m - b] & p2)))) {
					result->bv[m - 1] |= p1;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if (((bv[m - b] & p1) || (x.bv[x.m - 1] & p2)) && (!((bv[m - b] & p1) && (x.bv[x.m - 1] & p2)))) {
					result->bv[m - b] |= p1;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;*/
		int raw2;
		for (int i = x.n - 1 /*- raw*/; i >= 0; --i) {
			raw2 = (n + i - x.n) / 8;
			if (((bv[raw2] & p1) || (x.bv[i / 8] & p2)) && (!((bv[raw2] & p1) && (x.bv[i / 8] & p2)))) {
				result->bv[raw2] |= p1;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		raw = (n - x.n - 1) / 8;
		if (x.n != n) {
			while (p1) {
				if (bv[raw] & p1) {
					result->bv[raw] |= p1;
				}
				p1 /= 2;
			}
			for (int i = raw - 1; i >= 0; --i) {
				result->bv[i] = bv[i];
			}
		}
		return *result;
	} else {
		int raw = 8 - n % 8;
		bool_vector *result = new bool_vector(x.n);
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		/*if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if (((bv[m - 1] & p1) || (x.bv[x.m - b] & p2)) && (!((bv[m - 1] & p1) && (x.bv[x.m - b] & p2)))) {
					result->bv[x.m - b] |= p2;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if (((bv[m - b] & p1) || (x.bv[x.m - 1] & p2)) && (!((bv[m - b] & p1) && (x.bv[x.m - 1] & p2)))) {
					result->bv[x.m - 1] |= p2;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;*/
		int raw2;
		for (int i = n - 1 /*- raw*/; i >= 0; --i) {
			raw2 = (x.n + i - n) / 8;
			if (((bv[i / 8] & p1) || (x.bv[raw2] & p2)) && (!((bv[i / 8] & p1) && (x.bv[raw2] & p2)))) {
				result->bv[raw2] |= p2;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		raw = (x.n - n - 1) / 8;
		if (x.n != n) {
			while (p2) {
				if (x.bv[raw] & p2) {
					result->bv[raw] |= p2;
				}
				p2 /= 2;
			}
			for (int i = raw - 1; i >= 0; --i) {
				result->bv[i] = x.bv[i];
			}
		}
		return *result;
	}
}

bool_vector & bool_vector::operator<<(int count) {
	if ((n + count) <= 0) {
		bool_vector *result = new bool_vector;
		return *result;
	}
	if (count == 0) {
		bool_vector *result = new bool_vector(*this);
		return *result;
	}
	bool_vector *result = new bool_vector(n + count);
	if (count > 0) {
		for (int i = 0; i < m; ++i) {
			result->bv[i] = bv[i];
		}
		for (int i = m; i < result->m; ++i) {
			result->bv[i] = 0;
		}
	} else {
		int raw = result->m - 1;
		for (int i = 0; i < raw; ++i) {
			result->bv[i] = bv[i];
		}
		ui8 p = 255;
		int raw2 = 8 - (count % 8);
		p <<= raw2;
		result->bv[raw] |= (bv[raw] & ~p);
	}
	return *result;
}

bool_vector & bool_vector::operator>>(int count) {
	if ((n - count) <= 0) {
		bool_vector *result = new bool_vector;
		return *result;
	}
	if (count == 0) {
		bool_vector *result = new bool_vector(*this);
		return *result;
	}
	bool_vector *result = new bool_vector(n - count);
	if (count > 0) {
		int raw = result->m - 1;
		for (int i = 0; i < raw; ++i) {
			result->bv[i] = bv[i];
		}
		ui8 p = 255;
		int raw2 = 8 - (count % 8);
		p <<= raw2;
		result->bv[raw] |= (bv[raw] & ~p);
	} else {
		for (int i = 0; i < m; ++i) {
			result->bv[i] = bv[i];
		}
		for (int i = m; i < result->m; ++i) {
			result->bv[i] = 0;
		}
	}
	return *result;
}

bool_vector & bool_vector::operator|=(bool_vector &x) {
	ui8 p1 = 128, p2 = 128;
	if (n > x.n) {
		int raw = 8 - n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		/*if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - 1] & p1) || (x.bv[x.m - b] & p2)) {
					bv[m - 1] |= p1;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - b] & p1) || (x.bv[x.m - 1] & p2)) {
					bv[m - b] |= p1;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;*/
		int raw2;
		for (int i = x.n - 1 /*- raw*/; i >= 0; --i) {
			raw2 = (n + i - x.n) / 8;
			if (x.bv[i / 8] & p2) {
				bv[raw2] |= p1;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		raw = (n - x.n) / 8;
		return *this;
	} else {
		int raw = 8 - n % 8;
		ui8 *result = new ui8[x.m];
		for (int i = 0; i < x.m; ++i) {
			result[i] = 0;
		}
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		/*if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - 1] & p1) || (x.bv[x.m - b] & p2)) {
					result[x.m - b] |= p2;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - b] & p1) || (x.bv[x.m - 1] & p2)) {
					result[x.m - 1] |= p2;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;*/
		int raw2;
		for (int i = n - 1 /*- raw*/; i >= 0; --i) {
			raw2 = (x.n + i - n) / 8;
			if ((bv[i / 8] & p1) || (x.bv[raw2] & p2)) {
				result[raw2] |= p2;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		raw = (x.n - n - 1) / 8;
		if (x.n != n) {
			while (p2) {
				if (x.bv[raw] & p2) {
					result[raw] |= p2;
				}
				p2 /= 2;
			}
			for (int i = raw - 1; i >= 0; --i) {
				result[i] = x.bv[i];
			}
		}
		delete []bv;
		bv = result;
		n = x.n;
		m = x.m;
		return *this;
	}
}

bool_vector & bool_vector::operator&=(bool_vector &x) {
	ui8 p1 = 128, p2 = 128;
	if (n > x.n) {
		int raw = 8 - n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		/*if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - 1] & p1) && (x.bv[x.m - b] & p2)) {
					bv[m - 1] |= p1;
				} else {
					bv[m - 1] &= ~p1;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - b] & p1) && (x.bv[x.m - 1] & p2)) {
					bv[m - b] |= p1;
				} else {
					bv[m - b] &= ~p1;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;*/
		int raw2;
		for (int i = x.n - 1 /*- raw*/; i >= 0; --i) {
			raw2 = (n + i - x.n) / 8;
			if ((bv[raw2] & p1) && (x.bv[i / 8] & p2)) {
				bv[raw2] |= p1;
			} else {
				bv[raw2] &= ~p1;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		raw = (n - x.n - 1) / 8;
		while (p1) {
			if (bv[raw] & p1) {
				bv[raw] &= ~p1;
			}
			p1 /= 2;
		}
		for (int i = raw - 1; i >= 0; --i) {
			bv[i] = 0;
		}
		return *this;
	} else {
		int raw = 8 - n % 8;
		ui8 *result = new ui8[x.m];
		for (int i = 0; i < x.m; ++i) {
			result[i] = 0;
		}
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		/*if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - 1] & p1) && (x.bv[x.m - b] & p2)) {
					result[x.m - b] |= p2;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if ((bv[m - b] & p1) && (x.bv[x.m - 1] & p2)) {
					result[x.m - 1] |= p2;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;*/
		int raw2;
		for (int i = n - 1/*- raw*/; i >= 0; --i) {
			raw2 = (x.n + i - n) / 8;
			if ((bv[i / 8] & p1) && (x.bv[raw2] & p2)) {
				result[raw2] |= p2;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		delete []bv;
		bv = result;
		n = x.n;
		m = x.m;
		return *this;
	}
}

bool_vector & bool_vector::operator^=(bool_vector &x) {
	ui8 p1 = 128, p2 = 128;
	if (n > x.n) {
		int raw = 8 - n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		/*if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if (((bv[m - 1] & p1) || (x.bv[x.m - b] & p2)) && (!((bv[m - 1] & p1) && (x.bv[x.m - b] & p2)))) {
					bv[m - 1] |= p1;
				} else {
					bv[m - 1] &= ~p1;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if (((bv[m - b] & p1) || (x.bv[x.m - 1] & p2)) && (!((bv[m - b] & p1) && (x.bv[x.m - 1] & p2)))) {
					bv[m - b] |= p1;
				} else {
					bv[m - b] &= ~p1;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;*/
		int raw2;
		for (int i = x.n - 1/*- raw*/; i >= 0; --i) {
			raw2 = (n + i - x.n) / 8;
			if (((bv[raw2] & p1) || (x.bv[i / 8] & p2)) && (!((bv[raw2] & p1) && (x.bv[i / 8] & p2)))) {
				bv[raw2] |= p1;
			} else {
				bv[raw2] &= ~p1;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		return *this;
	} else {
		int raw = 8 - n % 8;
		ui8 *result = new ui8[x.m];
		for (int i = 0; i < x.m; ++i) {
			result[i] = 0;
		}
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p1 /= 2;
			}
		}
		raw = 8 - x.n % 8;
		if (raw < 8) {
			for (int i = 0; i < raw; ++i) {
				p2 /= 2;
			}
		}
		/*if ((n % 8) > (x.n % 8)) {
			raw = n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if (((bv[m - 1] & p1) || (x.bv[x.m - b] & p2)) && (!((bv[m - 1] & p1) && (x.bv[x.m - b] & p2)))) {
					result[x.m - b] |= p2;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p2) {
					b++;
					p2 = 128;
				}
			}
			p1 = 128;
		} else {
			raw = x.n % 8;
			int b = 1;
			for (int i = 0; i < raw; ++i) {
				if (((bv[m - b] & p1) || (x.bv[x.m - 1] & p2)) && (!((bv[m - b] & p1) && (x.bv[x.m - 1] & p2)))) {
					result[x.m - 1] |= p2;
				}
				p1 /= 2;
				p2 /= 2;
				if (!p1) {
					b++;
					p1 = 128;
				}
			}
			p2 = 128;
		}
		raw++;*/
		int raw2;
		for (int i = n - 1/*- raw*/; i >= 0; --i) {
			raw2 = (x.n + i - n) / 8;
			if (((bv[i / 8] & p1) || (x.bv[raw2] & p2)) && (!((bv[i / 8] & p1) && (x.bv[raw2] & p2)))) {
				result[raw2] |= p2;
			}
			p1 /= 2;
			p2 /= 2;
			if (!p1) {
				p1 = 128;
			}
			if (!p2) {
				p2 = 128;
			}
		}
		raw = (x.n - n - 1) / 8;
		if (x.n != n) {
			while (p2) {
				if (x.bv[raw] & p2) {
					result[raw] |= p2;
				}
				p2 /= 2;
			}
			for (int i = raw - 1; i >= 0; --i) {
				result[i] = x.bv[i];
			}
		}
		delete []bv;
		bv = result;
		n = x.n;
		m = x.m;
		return *this;
	}
}

bool_vector & bool_vector::operator<<=(int count) {
	if ((n + count) <= 0) {
		bool_vector result;
		*this = result;
		return *this;
	}
	if (count == 0) {
		return *this;
	}
	int raw1 = (n + count) / 8 + 1;
	ui8 *result = new ui8[raw1];
	for (int i = 0; i < raw1; ++i) {
		result[i] = 0;
	}
	if (count > 0) {
		for (int i = 0; i < m; ++i) {
			result[i] = bv[i];
		}
		for (int i = m; i < raw1; ++i) {
			result[i] = 0;
		}
	} else {
		for (int i = 0; i < raw1; ++i) {
			result[i] = bv[i];
		}
		ui8 p = 255;
		int raw2 = 8 - (count % 8);
		p <<= raw2;
		result[raw1] |= (bv[raw1] & ~p);
	}
	delete []bv;
	bv = result;
	n += count;
	m = raw1;
	return *this;
}

bool_vector & bool_vector::operator>>=(int count) {
	if ((n - count) <= 0) {
		bool_vector result;
		*this = result;
		return *this;
	}
	if (count == 0) {
		return *this;
	}
	int raw1 = (n - count) / 8 + 1;
	ui8 *result = new ui8[raw1];
	for (int i = 0; i < raw1; ++i) {
		result[i] = 0;
	}
	if (count > 0) {
		int raw = raw1;
		for (int i = 0; i < raw; ++i) {
			result[i] = bv[i];
		}
		ui8 p = 255;
		int raw2 = 8 - (count % 8);
		p <<= raw2;
		result[raw] |= (bv[raw] & ~p);
	} else {
		for (int i = 0; i < m; ++i) {
			result[i] = bv[i];
		}
		for (int i = m; i < raw1; ++i) {
			result[i] = 0;
		}
	}
	delete []bv;
	bv = result;
	n -= count;
	m = raw1;
	return *this;
}

/*massif & massif::operator-=(int pos) {
	if ((pos >= n) || (pos < 0)) {
		cout << "Error. Out of massif.\n";
		return *this;
	}
	if ((pos == 0) && (n = 1)) {
		adress[0] = 0;
		return *this;
	}
	this->move_left(pos);
	return *this;
}

massif & massif::operator-(double key) {
	bool *a = new bool[n];
	for (int i = 0; i < n; ++i) {
		a[i] = false;
	}
	int minus = 0;
	for (int i = 0; i < n; i++) {
		if (adress[i] == key) {
			a[i] = true;
			minus++;
		}
	}
	int pos = 0;
	if (!minus) {
		delete []a;
		return *this;
	}
	if (n == minus) {
		delete []a;
		massif *c = new massif;
		return *c;
	}
	massif *c = new massif(n - minus);
	for (int i = 0; i < c->n; ++i) {
		while (a[i + pos]) {
			pos++;
		}
		c->adress[i] = adress[i + pos];
	}
	delete []a;
	return *c;
}*/