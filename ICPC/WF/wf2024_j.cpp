#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 530000;

struct mtrx {
	lint a[5][5];
	mtrx() {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				a[i][j] = (i == j ? 0 : -1e18);
			}
		}
	}
	mtrx operator+(const mtrx &m) {
		mtrx ret;
		for (int i = 0; i < 5; i++)
			ret.a[i][i] = -1e18;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				for (int k = 0; k < 5; k++) {
					ret.a[i][k] = max(ret.a[i][k], a[i][j] + m.a[j][k]);
				}
			}
		}
		return ret;
	}
} tree[MAXT];
int lim;

mtrx make_mat(int typ, int len, int win) {
	mtrx M;
	len *= -1;
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
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i + j > 0)
				M.a[i][j] += win;
		}
	}
	return M;
}

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

lint query() { return tree[1].a[0][0]; }

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<array<int, 3>> a(n);
	vector<pi> seq;
	for (int i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1];
		if (a[i][0] == 2)
			cin >> a[i][2];
		seq.push_back({a[i][1], i});
	}
	sort(all(seq));
	vector<int> mp(n);
	for (int i = 0; i < sz(seq); i++)
		mp[seq[i][1]] = i;
	seq.push_back({seq[n - 1][0], -1});
	vector<mtrx> M(n);
	for (int i = 0; i < n; i++) {
		M[i] = make_mat(0, seq[i + 1][0] - seq[i][0], 0);
	}
	init(M);
	for (int i = 0; i < n; i++) {
		int pos = mp[i];
		M[pos] = make_mat(a[i][0] == 1 ? -1 : 1, seq[pos + 1][0] - seq[pos][0], a[i][2]);
		upd(pos, M[pos]);
		cout << query() << "\n";
	}
}