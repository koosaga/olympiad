#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

struct seg {
	struct node {
		int sum0, sum1, opt;
		node() { sum0 = sum1 = opt = 0; }
		node(int x) {
			sum0 = (x == 0);
			sum1 = (x == 1);
			opt = 0;
		}
		node operator+(const node &nd) const {
			node ret;
			ret.sum0 = sum0 + nd.sum0;
			ret.sum1 = sum1 + nd.sum1;
			ret.opt = min({opt + nd.sum0, sum1 + nd.opt});
			return ret;
		}
	};
	int lim;
	vector<node> tree;
	void init(vector<int> &a) {
		for (lim = 1; lim <= sz(a); lim <<= 1)
			;
		tree.resize(2 * lim);
		for (int i = 0; i < sz(a); i++) {
			tree[i + lim] = node(a[i]);
		}
		for (int i = lim - 1; i; i--)
			tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
	void update(int x, int v){
		x += lim;
		tree[x] = node(v);
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] + tree[2*x+1];
		}
	}
} seg[25];
int n;

int init(string s) {
	n = sz(s);
	int ret = 0;
	for (int i = 0; i < 25; i++) {
		vector<int> seq(n);
		for (int j = 0; j < n; j++)
			seq[j] = (s[j] > i + 'a');
		seg[i].init(seq);
		ret += seg[i].tree[1].opt;
	}
	return ret;
}

int update(int idx, char c) {
	int ret = 0;
	for (int i = 0; i < 25; i++) {
		seg[i].update(idx, c > i + 'a');
		ret += seg[i].tree[1].opt;
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;
	cout << init(s) << "\n";
	int q;
	cin >> q;
	while (q--) {
		int idx;
		string v;
		cin >> idx >> v;
		cout << update(idx-1, v[0]) << "\n";
	}
}