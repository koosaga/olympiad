#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int mod = 1e9 + 7;
const int MAXT = 270000;
const int MAXL = 30;

// bitonic sequence read left-to-right
struct seqs {
	vector<pi> seq;
	bool closed;
	seqs() {
		seq.clear();
		closed = false;
	}
	void cleanup_close() {
		assert(closed);
		while (sz(seq) >= 2 && seq[sz(seq) - 2][0] > seq.back()[0]) {
			int d = seq[sz(seq) - 2][0] - seq.back()[0];
			auto w = seq.back();
			seq.pop_back();
			seq.back()[1] += (w[1] >> d);
		}
	}
	seqs operator+(const seqs &s) const {
		if (closed)
			return *this;
		seqs ret;
		ret.seq = seq;
		ret.closed = false;
		for (auto &[x, c] : s.seq) {
			while (sz(ret.seq) >= 2 && ret.seq[sz(ret.seq) - 2][0] > ret.seq.back()[0] && ret.seq.back()[0] < x) {
				auto w = ret.seq.back();
				if (w[1] % 2 == 1) {
					ret.closed = true;
					ret.cleanup_close();
					return ret;
				}
				ret.seq.back()[1] /= 2;
				ret.seq.back()[0] += 1;
				if (ret.seq[sz(ret.seq) - 2][0] == ret.seq.back()[0]) {
					ret.seq[sz(ret.seq) - 2][1] += ret.seq.back()[1];
					ret.seq.pop_back();
				}
			}
			if (sz(ret.seq) > 0 && ret.seq.back()[0] == x) {
				ret.seq.back()[1] += c;
			} else {
				ret.seq.push_back({x, c});
			}
		}
		if (s.closed) {
			ret.closed = true;
			ret.cleanup_close();
		}
		return ret;
	}
	const void debug() const {
		cout << "------------" << endl;

		cout << "closed = " << closed << endl;
		for (auto &[x, c] : seq)
			cout << x << " " << c << endl;
		cout << "------------" << endl;
	}
};

int solve(seqs L, seqs R) {
	L.closed = true;
	R.closed = true;
	L.cleanup_close();
	R.cleanup_close();
	vector<int> Lcnt(MAXL), Rcnt(MAXL);
	for (auto &[x, c] : L.seq)
		Lcnt[x] += c;
	for (auto &[x, c] : R.seq)
		Rcnt[x] += c;
	int carry = 0;
	int ans = 0;
	for (int i = 0; i < MAXL; i++) {
		carry += (Lcnt[i] + Rcnt[i]);
		if (carry % 2) {
			ans = max(ans, i);
			int carryL = carry / 2;
			int carryR = carry / 2;
			for (int j = i + 1; j < MAXL; j++) {
				carryL += Lcnt[j];
				carryR += Rcnt[j];
				if (carryL)
					ans = max(ans, j);
				if (carryR)
					ans = max(ans, j);
				carryL /= 2;
				carryR /= 2;
			}
			break;
		}
		carry /= 2;
	}
	return ans;
}

struct node {
	int opt;
	seqs L, R;
	node() {
		opt = 0;
		L = seqs();
		R = seqs();
	}
	node(int x) {
		opt = x;
		L = seqs();
		R = seqs();
		L.seq.push_back({x, 1});
		R.seq.push_back({x, 1});
	}
	node operator+(const node &nd) const {
		node ret;
		ret.opt = max({opt, nd.opt, solve(R, nd.L)});
		ret.L = L + nd.L;
		ret.R = nd.R + R;
		return ret;
	}
	int getsol() {
		/*
		cout << "opt = " << opt << endl;
		cout << "L deb" << endl;
		L.debug();
		cout << "R deb" << endl;
		R.debug();*/
		seqs rightAppend;
		rightAppend.closed = true;
		return max({opt, solve(L, rightAppend), solve(R, rightAppend)});
	}
};

node tree[MAXT];
int lim;

void prepare_game(std::vector<int> A) {
	int n = sz(A);
	for (lim = 1; lim <= n; lim <<= 1)
		;
	for (int i = 0; i < n; i++) {
		tree[i + lim] = node(A[i]);
	}
	for (int i = lim - 1; i; i--) {
		tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
}

int play_game(int l, int r) {
	l += lim;
	r += lim;
	node ansL, ansR;
	while (l < r) {
		if (l % 2 == 1)
			ansL = ansL + tree[l++];
		if (r % 2 == 0)
			ansR = tree[r--] + ansR;
		l >>= 1;
		r >>= 1;
	}
	if (l == r)
		ansL = ansL + tree[l];

	return (ansL + ansR).getsol();
}

void update_game(int p, int v) {
	p += lim;
	tree[p] = node(v);
	while (p > 1) {
		p >>= 1;
		tree[p] = tree[2 * p] + tree[2 * p + 1];
	}
}