#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#include <ctime>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <list>
using namespace std;


#define N 11000

bool used[N];
int zx, sum[N], root;
int len;
vector <int> V, ve[N], ve1[N];
int n, K, ans;
int size[N], son[N][2], ran[N], val[N];

void update(int k) {
	size[k] = size[son[k][0]] + size[son[k][1]] + 1;
}

void rotate(int &k, int t) {
	int y = son[k][t];
	son[k][t] = son[y][1 - t];
	son[y][1 - t] = k;
	update(k);
	update(y);
	k = y;
}

void ins(int &k, int x) {
	if (!k) {
		k = ++len;
		son[k][0] = son[k][1] = 0;
		size[k] = 1;
		ran[k] = rand();
		val[k] = x;
	}else {
		if (x <= val[k]) {
			ins(son[k][0], x);
			if (ran[son[k][0]] < ran[k]) {
				rotate(k, 0);
			}
			update(k);
		}else {
			ins(son[k][1], x);
			if (ran[son[k][1]] < ran[k]) {
				rotate(k, 1);
			}
			update(k);
		}
	}
}

int query(int k, int x) {
	if (k == 0)
		return 0;
	if (val[k] <= x) {
		return size[son[k][0]] + 1 + query(son[k][1], x);
	}else {
		return query(son[k][0], x);
	}
}

void dfs_size(int k) {
	used[k] = true;
	sum[k] = 1;
	for (int i = 0; i < (int) ve[k].size(); i++)
		if (!used[ve[k][i]]) {
			dfs_size(ve[k][i]);
			sum[k] += sum[ve[k][i]];
		}
	used[k] = false;
}


void dfs_zx(int k, int S) {
	used[k] = true;
	bool ok = (S - sum[k]) <= S / 2;
	for (int i = 0; i < (int) ve[k].size(); i++)
		if (!used[ve[k][i]]) {
			dfs_zx(ve[k][i], S);
			ok &= (sum[ve[k][i]] <= S / 2);
		}
	used[k] = false;
	if (ok) {
		zx = k;
	}
}

void dfs_l(int k, int l) {
	V.push_back(l);
	used[k] = true;
	for (int i = 0; i < (int) ve[k].size(); i++)
		if (!used[ve[k][i]]) {
			dfs_l(ve[k][i], l + ve1[k][i]);
		}
	used[k] = false;
}

void dfs(int k) {
	dfs_size(k);
	dfs_zx(k, sum[k]);
	k = zx;
	
	used[k] = true;
	
	root = 0;
	len = 0;
	ins(root, 0);

	for (int i = 0; i < (int) ve[k].size(); i++)
	if (!used[ve[k][i]]) {
		V.clear();
		dfs_l(ve[k][i], ve1[k][i]);
		for (int j = 0; j < (int) V.size(); j++) {
			ans += query(root, K - V[j]);
		}	
		for (int j = 0; j < (int) V.size(); j++) {
			ins(root, V[j]);
		}

	}
	
	for (int i = 0; i < (int) ve[k].size(); i++)
		if (!used[ve[k][i]]) {
			dfs(ve[k][i]);
		}
	used[k] = false;
}

int main() {
	while (scanf("%d%d", &n, &K), n) {
		for (int i = 1; i <= n; i++)
			ve[i].clear(), ve1[i].clear();
		for (int i = 1; i < n; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			ve[a].push_back(b);
			ve[b].push_back(a);
			ve1[a].push_back(c);
			ve1[b].push_back(c);
		}
		ans = 0;
		dfs(1);
		printf("%d\n", ans);
	}
}