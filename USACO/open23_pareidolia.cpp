#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const string t = "bessie";
const int MAXT = 530000;

struct node {
	int where[6];
	lint coeff[6];
	int out[6];
	lint sum;
	node() {
		iota(where, where + 6, 0);
		memset(coeff, 0, sizeof(coeff));
		memset(out, 0, sizeof(out));
		sum = 0;
	}
	node(char c, int pos) {
		iota(where, where + 6, 0);
		memset(coeff, 0, sizeof(coeff));
		memset(out, 0, sizeof(out));
		if (c == t[0])
			out[1] = 1;
		else
			out[0] = 1;
		sum = 0;
		for (int i = 0; i < 6; i++) {
			if (c == t[i]) {
				where[i] = (i + 1) % 6;
				if (i == 5)
					coeff[i] = pos;
			}
		}
	}
	node operator+(const node &nd) const {
		node ret;
		ret.sum = sum + nd.sum;
		for (int i = 0; i < 6; i++) {
			ret.out[i] += nd.out[i];
			ret.out[nd.where[i]] += out[i];
			ret.sum += nd.coeff[i] * out[i];
		}
		for (int i = 0; i < 6; i++) {
			ret.coeff[i] = coeff[i] + nd.coeff[where[i]];
			ret.where[i] = nd.where[where[i]];
		}
		return ret;
	}
};

struct seg {
	node tree[MAXT];
	int lim, n;
	void init(string &s) {
		n = sz(s);
		for (lim = 1; lim <= n; lim <<= 1)
			;
		for (int i = 0; i < n; i++) {
			tree[i + lim] = node(s[i], n - i);
		}
		for (int i = lim - 1; i; i--)
			tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
	void upd(int x, char c) {
		x += lim;
		tree[x] = node(c, n - (x - lim));
		while (x > 1) {
			x >>= 1;
			tree[x] = tree[2 * x] + tree[2 * x + 1];
		}
	}
	lint query() { return tree[1].sum; }
} seg;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;
	int q;
	cin >> q;
	seg.init(s);
	cout << seg.query() << "\n";
	while (q--) {
		int p;
		char c;
		cin >> p >> c;
		seg.upd(p - 1, c);
		cout << seg.query() << "\n";
	}
}