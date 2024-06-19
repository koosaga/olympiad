#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2000005;

int op(char c) {
	if (c == '|')
		return 1;
	if (c == '&')
		return 2;
	if (c == '^')
		return 3;
	return 0;
}

// code by spectaclehong (https://www.acmicpc.net/problem/status/21884)
#define ln (n + 1)
#define rn (n + 2 * (md - s + 1))
#define md (s + e >> 1)
#define lch ln, s, md
#define rch rn, md + 1, e

const int NN = 2e6 + 5;

char inp[NN];

struct Node2 {
	int idx;
	bool mat[2];
	Node2(int idx = 0, int a = 0, int b = 1) : idx(idx) { mat[0] = a, mat[1] = b; }

	void set(bool R = 0) {
		char c = inp[idx];
		if (c == '0')
			*this = Node2(idx, 0, 0);
		else if (c == '1')
			*this = Node2(idx, 1, 1);
		else if (R) {
			if (c == '&')
				*this = Node2(idx, 0, 1);
			else if (c == '|')
				*this = Node2(idx, 1, 1);
			else
				*this = Node2(idx, 1, 0);
		} else {
			if (c == '&')
				*this = Node2(idx, 0, 0);
			else
				*this = Node2(idx, 0, 1);
		}
	}

	Node2 operator+(const Node2 &o) const { return {0, mat[o.mat[0]], mat[o.mat[1]]}; }

	bool val() { return mat[0]; }
} tree[NN * 2];

vector<int> v[NN];

int siz[NN], par[NN], head[NN], tail[NN], in[NN], rin[NN], tn;

int dfs_size(int cur) {
	siz[cur] = 1;
	for (int &nxt : v[cur]) {
		siz[cur] += dfs_size(nxt);
		if (siz[v[cur][0]] < siz[nxt])
			swap(v[cur][0], nxt);
	}
	head[cur] = cur;
	return siz[cur];
}

void dfs_hld(int cur) {
	in[cur] = ++tn;
	rin[tn] = cur;
	for (int &nxt : v[cur]) {
		head[nxt] = nxt == v[cur][0] ? head[cur] : nxt;
		dfs_hld(nxt);
		par[nxt] = cur;
	}
	tail[cur] = v[cur].size() ? tail[v[cur][0]] : cur;
}

int N, M;
int word[NN];

void update(int i, bool R, int n, int s, int e) {
	if (e < i || i < s)
		return;
	if (s != e) {
		update(i, R, lch);
		update(i, R, rch);
		tree[n] = tree[ln] + tree[rn];
	} else {
		tree[n].idx = rin[s];
		tree[n].set(R);
	}
}

void update(int cur) {
	int s = in[head[cur]];
	int e = in[tail[cur]];
	bool R = 0;
	if (v[cur].size() == 2) {
		int ch = v[cur][1];
		int n = in[ch] * 2 - 1;
		R = tree[n].val();
	}
	update(in[cur], R, s * 2 - 1, s, e);
}

void build() {
	for (int i = tn; i >= 1; i--) {
		update(rin[i]);
	}
}

void update(int x, int w) {
	inp[x] = '1';
	for (int cur = x; cur; cur = par[head[cur]])
		update(cur);
}

vector<pi> upds;
int dfs_expr();
int dfs_tok();

int p, n;
char str[MAXN];

int dfs_tok() {
	if (str[p] == '[') {
		int cur = 0;
		p++;
		while (str[p] != ']') {
			cur = cur * 10 + str[p++] - '0';
		}
		p++;
		++n; //	printf("num %d %d\n", cur, n);
		inp[n] = '0';
		upds.push_back({cur, n});
		return n;
	}
	if (str[p] == '(') {
		p++;
		int ans = dfs_expr();
		p++;
		return ans;
	}
	if (str[p] == '!') {
		p++;
		int son = dfs_tok();
		n++;
		inp[n] = '1';
		par[n] = n + 1;
		par[son] = n + 1;
		n++;
		inp[n] = '^';
		//	printf("no %d %d %d\n", n - 1, son, n);
		return n;
	}
	assert(0);
}

int fuck(vector<int> &v, int s, int e, int fucked = 0) {
	if (s == e)
		return v[s];
	if (fucked <= 0) {
		for (int i = e - 1; i >= s; i -= 2) {
			if (v[i] == 1) {
				int lson = fuck(v, s, i - 1, 0);
				int rson = fuck(v, i + 1, e, 1);
				int mid = v[i];
				n++;
				inp[n] = '|';
				par[lson] = n;
				par[rson] = n;
				return n;
			}
		}
	}
	if (fucked <= 1) {
		for (int i = e - 1; i >= s; i -= 2) {
			if (v[i] == 3) {
				int lson = fuck(v, s, i - 1, 1);
				int rson = fuck(v, i + 1, e, 2);
				int mid = v[i];
				n++;

				inp[n] = '^';
				par[lson] = n;
				par[rson] = n;
				return n;
			}
		}
	}
	if (fucked <= 2) {
		for (int i = e - 1; i >= s; i -= 2) {
			if (v[i] == 2) {
				int lson = fuck(v, s, i - 1, 2);
				int rson = fuck(v, i + 1, e, 2);
				int mid = v[i];
				++n;
				par[lson] = n;
				par[rson] = n;
				inp[n] = '&';
				return n;
			}
		}
	}
	assert(0);
}

int dfs_expr() {
	vector<int> fucks;
	while (true) {
		int ch = dfs_tok();
		fucks.push_back(ch);
		if (op(str[p]) == 0)
			break;
		else
			fucks.push_back(op(str[p++]));
	}
	/*
	cout << "[";
	for (int i = 0; i < sz(fucks); i++)
		cout << fucks[i] << ",";
	cout << "]" << endl;*/
	return fuck(fucks, 0, sz(fucks) - 1);
}

int main() {
	int q;
	scanf("%*d %d", &q);
	scanf("%s", str);
	int rt = dfs_expr();
	par[rt] = rt + 1;
	{
		for (int i = 1; i < n; i++) {
			v[par[i]].push_back(i);
		}
		dfs_size(rt);
		dfs_hld(rt);
		for (int i = tn; i >= 1; i--) {
			update(rin[i]);
		}
	}
	auto query = [&]() { return tree[1].val(); };
	vector<pi> ans;
	ans.push_back({0, query()});
	sort(all(upds));
	for (int i = 0; i < sz(upds);) {
		int j = i;
		while (j < sz(upds) && upds[i].first == upds[j].first) {
			update(upds[j++].second, 1);
		}
		ans.push_back({upds[i].first, query()});
		i = j;
	}
	while (q--) {
		int x;
		scanf("%d", &x);
		auto z = lower_bound(all(ans), pi{x, 2});
		if ((--z)->second)
			printf("True\n");
		else
			printf("False\n");
	}
}
