#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 270000;

lint Q0(lint i, lint x, lint y) {
	cout << "? 0 " << i + 1 << " " << x << " " << y << endl;
	lint ret;
	cin >> ret;
	return ret;
}

lint Q1(lint i, lint x, lint r) {
	assert(r > 0);
	cout << "? 1 " << i + 1 << " " << x << " " << r << endl;
	lint ret;
	cin >> ret;
	assert(ret != -1);
	return ret;
}

lint n;
vector<int> ans;
lint cutpos[MAXN];
lint tot[MAXN];
void Sort(int l, int r, vector<int> p) {
	if (r - l == 1) {
		ans.push_back(p[0]);
		return;
	}
	int m = (l + r) / 2;
	int d = n / (r - l);
	vector<lint> points(sz(p));
	for (int i = 0; i < sz(points); i++) {
		points[i] = Q1(p[i], cutpos[l], tot[p[i]] / (2 * d));
	}
	vector<int> idx(sz(p));
	iota(all(idx), 0);
	sort(all(idx), [&](int x, int y) { return points[x] < points[y]; });
	cutpos[m] = points[idx[sz(idx) / 2]] >> 10;
	vector<int> L, R;
	for (int i = 0; i < sz(idx); i++) {
		if (i < sz(idx) / 2)
			L.push_back(p[idx[i]]);
		else
			R.push_back(p[idx[i]]);
	}
	Sort(l, m, L);
	Sort(m, r, R);
}

int main() {
	int k;
	cin >> k;
	n = (1 << k);
	vector<int> p(n);
	iota(all(p), 0);
	for (int i = 0; i < n; i++) {
		tot[i] = Q0(i, 0, 1ll << 40);
	}
	cutpos[0] = 0;
	cutpos[n] = 1ll << 40;
	Sort(0, n, p);
	cout << "!";
	for (auto &x : ans)
		cout << " " << x + 1;
	for (int i = 1; i < n; i++)
		cout << " " << cutpos[i];
	cout << endl;
}