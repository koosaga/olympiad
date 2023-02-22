#include "workshop.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

vector<int> ord20, ord6, ord4;

void init() {
	for (int i = 0; i < (1 << 20); i++) {
		int cnt = 0;
		for (int j = 0; j < 20; j++) {
			if ((i >> j) & 1)
				cnt++;
		}
		if (cnt == 10)
			ord20.push_back(i);
	}
	for (int i = 0; i < (1 << 6); i++) {
		int cnt = 0;
		for (int j = 0; j < 6; j++) {
			if ((i >> j) & 1)
				cnt++;
		}
		if (cnt == 3)
			ord6.push_back(i);
	}
	for (int i = 0; i < (1 << 4); i++) {
		int cnt = 0;
		for (int j = 0; j < 4; j++) {
			if ((i >> j) & 1)
				cnt++;
		}
		if (cnt == 2)
			ord4.push_back(i);
	}
}

int comp(int u, int v, vector<int> &ord) {
	assert(u != v);
	u = ord[u];
	v = ord[v];
	int i = 0;
	while ((u >> i) % 2 == 1 || (v >> i) % 2 == 0)
		i++;
	return i;
}

int morning(int my_num, int right_num) { return comp(my_num, right_num, ord20) ; }

int afternoon(int left_num, int my_num, int right_num) {
	int u = comp(left_num, my_num, ord6);
	int v = comp(my_num, right_num, ord6);
	return comp(u, v, ord4);
}

int evening(int left_num, int my_num, int right_num) {
	if (my_num <= 2)
		return my_num;
	int u = 0;
	while (u == left_num || u == right_num)
		u++;
	return u;
}