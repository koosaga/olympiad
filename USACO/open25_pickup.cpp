#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

struct mtrx {
	lint a[5][5];
	mtrx() {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				a[i][j] = (i == j ? 0 : 4e18);
			}
		}
	}
	mtrx operator+(const mtrx &m) {
		mtrx ret;
		for (int i = 0; i < 5; i++)
			ret.a[i][i] = 4e18;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				for (int k = 0; k < 5; k++) {
					ret.a[i][k] = min(ret.a[i][k], a[i][j] + m.a[j][k]);
				}
			}
		}
		return ret;
	}
};

mtrx make_mat(int typ, lint len) {
	mtrx M;
	if (typ != 0) {
		M.a[0][2] = 2 * len;
		if (typ == -1)
			M.a[0][1] = len;
		M.a[0][3] = len;
		if (typ == -1) {
			M.a[2][1] = len;
			M.a[3][4] = len * 2;
		}
		M.a[4][0] = 0;
		if (typ == -1)
			M.a[3][0] = 0;
		M.a[1][0] = 0;
	}
	M.a[1][1] = M.a[3][3] = len;
	M.a[2][2] = M.a[4][4] = 2 * len;
	if (typ == 1) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (i + j == 0)
					M.a[i][j] = 4e18;
			}
		}
	}
	return M;
}

mtrx ipow(mtrx m, lint d) {
	if (d == 0)
		return mtrx();
	if (d & 1) {
		return ipow(m, d - 1) + m;
	}
	return ipow(m + m, d >> 1);
}

struct event {
	lint pos;
	int type;
	int idx;
	int dx;
	bool operator<(const event &e) const { return make_tuple(pos, idx, type, dx) < make_tuple(e.pos, e.idx, e.type, e.dx); }
};

const int MAXT = 270000;
struct seg {
	int lim;
	mtrx tree[MAXT];
	void init(vector<mtrx> &M) {
		for (lim = 1; lim <= sz(M); lim <<= 1)
			;
		for (int i = 0; i < sz(M); i++)
			tree[i + lim] = M[i];
		for (int i = lim - 1; i; i--)
			tree[i] = tree[2 * i] + tree[2 * i + 1];
	}

	void upd(int x, mtrx p) {
		x += lim;
		tree[x] = p;
		while (x > 1) {
			x >>= 1;
			tree[x] = tree[2 * x] + tree[2 * x + 1];
		}
	}
	mtrx query(int l, int r) {
		mtrx L, R;
		l += lim;
		r += lim;
		while (l < r) {
			if (l % 2 == 1)
				L = L + tree[l++];
			if (r % 2 == 0)
				R = tree[r--] + R;
			l >>= 1;
			r >>= 1;
		}
		if (l == r)
			L = L + tree[l];
		return L + R;
	}
} seg;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lint t;
	int n, m;
	cin >> t >> n >> m;
	vector<event> events;
	for (int i = 0; i < n; i++) {
		lint l, r;
		cin >> l >> r;
		events.push_back({l, i, -1, +1});
		events.push_back({r + t, i, -1, -1});
	}
	for (int i = 0; i < m; i++) {
		lint l, r;
		cin >> l >> r;
		events.push_back({l, -i - 1, +1, +1});
		events.push_back({r + t, -i - 1, +1, -1});
	}
	sort(all(events));
	vector<array<lint, 3>> vect;
	for (int i = 0; i < sz(events); i++) {
		vect.push_back({events[i].pos % t, events[i].idx, events[i].type});
	}
	vect.push_back({t, 0, -1});
	sort(all(vect));
	vect.resize(unique(all(vect)) - vect.begin());
	vector<mtrx> M(sz(vect) - 1);
	vector<int> cnt(sz(vect));
	for (int i = 0; i < sz(vect) - 1; i++) {
		M[i] = make_mat(0, vect[i + 1][0] - vect[i][0]);
	}
	seg.init(M);
	auto inside_query = [&](array<lint, 3> l, array<lint, 3> r) {
		if (l == r)
			return mtrx();
		assert(l <= r);
		int ll = lower_bound(all(vect), l) - vect.begin();
		int rr = lower_bound(all(vect), r) - vect.begin();
		if (ll == rr) {
			return make_mat(0, r[0] - l[0]);
		}
		auto A = make_mat(0, vect[ll][0] - l[0]);
		auto B = seg.query(ll, rr - 2);
		auto C = make_mat((cnt[rr - 1] > 0) * vect[rr - 1][1], r[0] - vect[rr - 1][0]);
		return A + B + C;
	};
	auto query = [&](array<lint, 3> l, array<lint, 3> r) {
		if (l[0] / t == r[0] / t)
			return inside_query(array<lint, 3>{l[0] % t, l[1], l[2]}, array<lint, 3>{r[0] % t, r[1], r[2]});
		auto A = inside_query(array<lint, 3>{l[0] % t, l[1], l[2]}, array<lint, 3>{t, -int(1e9), -1});
		auto B = ipow(inside_query(array<lint, 3>{0, -int(1e9), -1}, array<lint, 3>{t, -int(1e9), -1}), r[0] / t - l[0] / t - 1);
		auto C = inside_query(array<lint, 3>{0, -int(1e9), -1}, array<lint, 3>{r[0] % t, r[1], r[2]});
		return A + B + C;
	};
	mtrx ans;
	for (int i = 0; i < sz(events); i++) {
		array<lint, 3> k{events[i].pos % t, events[i].idx, events[i].type};
		int pos = lower_bound(all(vect), k) - vect.begin();
		cnt[pos] += events[i].dx;
		M[pos] = make_mat(vect[pos][1] * (cnt[pos] > 0 ? 1 : 0), vect[pos + 1][0] - vect[pos][0]);
		seg.upd(pos, M[pos]);
		if (i + 1 < sz(events))
			ans = ans + query(array<lint, 3>{events[i].pos, events[i].idx, events[i].type}, array<lint, 3>{events[i + 1].pos, events[i + 1].idx, events[i + 1].type});
	}
	cout << ans.a[0][0] << "\n";
}