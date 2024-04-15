#include "Bruno.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

namespace FUCKING2 {
const int MAXT = 2100000;
vector<int> a;
int cnt, x, queryCnt;
pi binsearch;
vector<pi> seqs;
int mode;
int d, p, n;
int wordsize(pi bsint) {
	int z = 1;
	while ((1 << z) < bsint[1] - bsint[0] + 1)
		z++;
	// cout << "send by" << bsint[0] << " " << bsint[1] << " " << z << endl;

	return z;
}
void Sends(int x, int b) {
	for (int i = 0; i < b; i++) {
		SendB((x >> i) & 1);
	}
}

struct seg {
	int lim;
	pi tree[MAXT];
	void init(vector<int> v) {
		fill(tree, tree + MAXT, pi{-int(2e9), -1});
		for (lim = 1; lim <= sz(v); lim <<= 1)
			;
		for (int i = 0; i < sz(v); i++)
			tree[i + lim] = pi{v[i], i};
		for (int i = lim - 1; i; i--)
			tree[i] = max(tree[2 * i], tree[2 * i + 1]);
	}
	pi query(int l, int r) {
		l += lim;
		r += lim;
		pi ret = pi{-int(2e9), -1};
		while (l < r) {
			if (l % 2 == 1)
				ret = max(ret, tree[l++]);
			if (r % 2 == 0)
				ret = max(ret, tree[r--]);
			l >>= 1;
			r >>= 1;
		}
		if (l == r)
			ret = max(ret, tree[l]);
		return ret;
	}
} seg;

string bits;

void dfs(int l, int r) {
	if (l > r) {
		return;
	}
	int m = seg.query(l, r)[1];
	bits += "0";
	dfs(l, m - 1);
	bits += "1";
	dfs(m + 1, r);
}

void SENDCART(vector<int> v) {
	for (auto &x : v)
		x = -x;
	seg.init(v);
	dfs(0, sz(v) - 1);
	for (auto &b : bits)
		SendB(b - '0');
}
void InitB(int N, std::vector<int> P) {
	n = N;
	a = P;
}

array<int, 3> findFromSeg(int ps, int pe, int p, int d) {
	if (d == 0)
		return array<int, 3>{ps, pe, (ps + pe) / 2};
	int pm = (ps + pe) / 2;
	if ((p >> (d - 1)) & 1)
		return findFromSeg(pm + 1, pe, p, d - 1);
	else
		return findFromSeg(ps, pm, p, d - 1);
}

pi bsint;

void ReceiveB(bool y) {
	queryCnt++;
	// cout << "R";
	if (mode == 0) {
		d = d * 2 + y;
		cnt++;
		if (cnt == 3 && (d <= 1)) {
			cnt = 0;
			mode = (d == 0 ? 2 : 1);
		} else if (cnt == 4) {
			cnt = 0;
			mode = 69;
			d -= 2;
		}
	} else if (mode == 1) {
		p = p * 2 + y;
		cnt++;
		if (cnt == d) {
			mode = 2;
		}
	} else if (mode == 69) {
		p = p * 2 + y;
		cnt++;
		if (cnt == d) {
			mode = 2;
		}
	}
	if (mode == 2) {
		auto [ps, pe, x] = findFromSeg(0, n - 1, p, d);
		bsint = pi{ps, x};
		if (d == 13) {
			vector<int> arr(a.begin() + ps, a.begin() + pe + 1);
			SENDCART(arr);
			// just send whole array
		} else {
			seqs.push_back({x, x});
			for (int i = 1; i < pe - ps + 1; i++) {
				auto [l, r] = seqs.back();
				int vl = (l > ps ? a[l - 1] : int(-1e9));
				int vr = (r + 1 <= pe ? a[r + 1] : int(-1e9));
				if (vl < vr)
					r++;
				else
					l--;
				seqs.push_back({l, r});
			}
			binsearch = pi{0, sz(seqs) - 1};

			int m = (binsearch[0] + binsearch[1]) / 2;
			Sends(seqs[m][0] - bsint[0], wordsize(bsint));
		}
		mode = 3;
		return;

	} else if (mode == 3) {
		//	cout << "y is " << y << endl;
		int m = (binsearch[0] + binsearch[1]) / 2;
		if (y) {
			binsearch[1] = m;
			bsint = pi{seqs[m][0], bsint[1]};
		} else {
			binsearch[0] = m + 1;
			bsint = pi{bsint[0], seqs[m][0]};
		}
		if (binsearch[0] == binsearch[1]) {
			int l = seqs[binsearch[0]][0];
			int r = seqs[binsearch[0]][1];
			int minv = min_element(a.begin() + l, a.begin() + r + 1) - a.begin();
			// cout << "sent " << l << " " << r << " " << minv << endl;
			Sends(minv, 20);
		} else {
			if (queryCnt == 18) {
				auto ilow = seqs[binsearch[0]];
				auto ihigh = seqs[binsearch[1]];
				vector<int> arr;
				for (int j = ihigh[0]; j < ilow[0]; j++) {
					arr.push_back(a[j]);
				}
				int m1 = ilow[0] - bsint[0];
				int m2 = ihigh[0] - bsint[0];
				Sends(m1, wordsize(bsint));
				Sends(m2, wordsize(bsint));

				auto ptr = min_element(a.begin() + ilow[0], a.begin() + ilow[1] + 1);
				arr.push_back(*ptr);
				for (int j = ilow[1] + 1; j <= ihigh[1]; j++) {
					arr.push_back(a[j]);
				}
				// send final.
				Sends(ptr - a.begin(), 20);
				SENDCART(arr);
				return;
			}
			int m = (binsearch[0] + binsearch[1]) / 2;
			Sends(seqs[m][0] - bsint[0], wordsize(bsint));
		}
	}
}
} // namespace FUCKING2
void InitB(int N, std::vector<int> P) { FUCKING2::InitB(N, P); }

void ReceiveB(bool y) { FUCKING2::ReceiveB(y); }
