#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXT = 270000;
int n, m;

struct seg {
	struct node {
		int l, r, add;
		node() {
			l = 0, r = n;
			add = 0;
		}
		node(int x) {
			l = 0, r = n;
			add = x % (n + 1);
		}
		node(int L, int R, int A) { l = L, r = R, add = A % (n + 1); }
		bool operator<(const node &nd) const { return l < nd.l; }
	};
	vector<node> tree[MAXT];
	void merge(vector<node> &a, vector<node> &b, vector<node> &ret) {
		for (auto &z : a) {
			int is = z.l + z.add;
			int ie = z.r + z.add;
			is %= n + 1, ie %= n + 1;
			auto loop = [&](int l, int r, int v) {
				auto it = --upper_bound(all(b), node(l, -1, -1));
				while (l <= r && it != b.end()) {
					int nl = max(l, it->l);
					int nr = min(r, it->r);
					ret.push_back({(nl - v + n + 1) % (n + 1), (nr - v + n + 1) % (n + 1), (v + it->add) % (n + 1)});
					l = nr + 1;
					it++;
				}
			};
			if (is <= ie) {
				loop(is, ie, z.add);
			} else {
				loop(is, n, z.add);
				loop(0, ie, z.add);
			}
		}
		sort(all(ret));
		for (int i = 1; i < sz(ret); i++)
			assert(ret[i].l - 1 == ret[i - 1].r);
		assert(ret[0].l == 0);
		assert(ret.back().r == n);
	}
	int lim;
	void init(vector<int> &a) {
		for (lim = 1; lim <= sz(a); lim <<= 1)
			;
		for (int i = 0; i < sz(a); i++) {
			tree[i + lim].push_back(node(0, a[i] - 1, a[i] + 1));
			tree[i + lim].push_back(node(a[i], n, a[i]));
		}
		for (int i = sz(a); i < lim; i++)
			tree[i + lim].push_back(node());
		for (int i = lim - 1; i; i--) {
			merge(tree[2 * i], tree[2 * i + 1], tree[i]);
		}
	}
	int query(int l, int r, int v) {
		l += lim;
		r += lim;
		vector<int> v1, v2;
		while (l < r) {
			if (l % 2 == 1)
				v1.push_back(l++);
			if (r % 2 == 0)
				v2.push_back(r--);
			l >>= 1;
			r >>= 1;
		}
		if (l == r)
			v1.push_back(l);
		reverse(all(v2));
		for (auto &z : v2)
			v1.push_back(z);
		for (auto &nd : v1) {
			auto it = --upper_bound(all(tree[nd]), node(v, -1, -1));
			assert(it->l <= v && v <= it->r);
			v += it->add;
			v %= (n + 1);
		}
		return v;
	}
} seg;

const int MAXN = 120005;
int nxt[18][18][MAXN];
lint DS[18][MAXN][2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	string s;
	cin >> s;
	vector<int> apos = {0}, bpos = {n};
	for (int i = 0; i < n; i++) {
		if (s[i] == 'B')
			apos.push_back(i + 1);
	}
	for (int i = n - 1; i >= 0; i--) {
		if (s[i] == 'R')
			bpos.push_back(i);
	}
	apos.push_back(n + 1);
	bpos.push_back(-1);
	string t = s;
	vector<int> A(m);
	for (auto &x : A) {
		cin >> x;
	}
	seg.init(A);
	int q;
	cin >> q;
	vector<int> gp2(n + 1);
	auto gp = [&](int x) {
		if (x == 0)
			return 0;
		int i = 1;
		while ((1 << i) <= x)
			i++;
		return i;
	};
	auto width = [&](int x) {
		if (x == 0)
			return 0;
		return 1 << (x - 1);
	};
	for (int i = 0; i <= n; i++) {
		gp2[i] = gp(i);
	}

	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 18; j++) {
			if (width(i) + width(j) >= n)
				continue;
			int l = width(i), r = n - width(j);
			for (int k = m - 1; k >= 0; k--) {
				if (l <= A[k] - 1 && A[k] - 1 < r && (s.back() == 'R' || A[k] != n)) {
					nxt[i][j][k] = k + 1;
				} else {
					nxt[i][j][k] = nxt[i][j][k + 1];
				}
			}
		}
		for (int k = m - 1; k >= 0; k--) {
			DS[i][k][0] = (A[k] <= width(i) ? A[k] : 0) + DS[i][k + 1][0];
			DS[i][k][1] = (A[k] > n - width(i) ? (n - A[k]) : 0) + DS[i][k + 1][1];
		}
	}
	auto getnxt = [&](int g1, int g2, int i, int j) {
		int w = nxt[g1][g2][i];
		if (w == 0)
			w = 1e9;
		return min(j, w - 1);
	};
	auto sum1 = [&](int l, int r, int g1, int g2) { return DS[g1][l][0] - DS[g1][r + 1][0]; };
	auto sum2 = [&](int l, int r, int g1, int g2) { return DS[g2][l][1] - DS[g2][r + 1][1]; };
	vector<int> sumR(n + 1);
	vector<int> sumB(n + 1);
	for (int i = 1; i <= n; i++) {
		sumR[i] = sumR[i - 1] + (s[i - 1] == 'R');
		sumB[i] = sumB[i - 1] + (s[i - 1] == 'B');
	}

	auto getsum = [&](int l, int r, char c) {
		if (c == 'R')
			return sumR[r] - sumR[l];
		else
			return sumB[r] - sumB[l];
	};
	lint lac = 0, lbc = 0;
	while (q--) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		int LA = 0, LB = 0, ans = -1;
		auto strips = [&](int l, int r, int v) {
			v %= n + 1;
			v += n + 1;
			v %= n + 1;
			return seg.query(l, r, v);
		};
		for (int i = l; i <= r; i++) {
			int pos = A[i];
			int g1 = gp2[apos[LA]];
			int g2 = gp2[n - bpos[LB]];
			int nxt = getnxt(g1, g2, i, r);
			if (nxt > i) {
				int s = i, e = nxt;
				while (s != e) {
					int m = (s + e + 1) / 2;
					lint DA = sum1(i, m - 1, g1, g2);
					lint DB = sum2(i, m - 1, g1, g2);
					if (LA + DA < sz(apos) && LB + DB < sz(bpos) && apos[LA + DA] < bpos[LB + DB])
						s = m;
					else
						e = m - 1;
				}
				LA += sum1(i, s - 1, g1, g2);
				LB += sum2(i, s - 1, g1, g2);
				i = s;
				pos = A[i];
			}
			int is_current_B = (pos - 1 >= bpos[LB] || (pos - 1 >= apos[LA] && s[pos - 1] == 'B'));
			int DA = pos + is_current_B;
			int DB = n + 1 - pos - is_current_B;
			if (LA + DA < sz(apos) && apos[LA + DA] <= bpos[LB]) {
				LA += DA;
				continue;
			}
			if (LB + DB < sz(bpos) && apos[LA] <= bpos[LB + DB]) {
				LB += DB;
				continue;
			}
			// Always killing
			int acnt = min(apos[LA], pos - 1) + getsum(apos[LA], min(bpos[LB], pos - 1), 'R');
			int bcnt = min(n - pos, n - bpos[LB]) + getsum(max(pos, apos[LA]), bpos[LB], 'B');
			if (acnt >= bcnt) {
				// eat sz(b) A from pos leftward
				if (apos[LA] >= pos - 1) {
					ans = strips(i + 1, r, pos - 1 - bcnt);
					break;
				}
				pos = n + 1 - pos - is_current_B;
				pos -= getsum(apos[LA], bpos[LB], 'R');
				int corn = apos[LA] - pos;
				ans = strips(i + 1, r, corn);
				break;
			} else {
				if (bpos[LB] <= pos) {
					ans = strips(i + 1, r, pos + acnt + 1);
					break;
				}
				pos = pos + is_current_B;
				pos -= getsum(apos[LA], bpos[LB], 'B');
				int corn = bpos[LB] + pos;
				ans = strips(i + 1, r, corn);
				break;
			}
		}

		if (ans == -1) {
			ans = apos[LA] + getsum(apos[LA], bpos[LB], 'R');
		}
		cout << ans << "\n";
	}
}

// RR|RBR
// RBBBB