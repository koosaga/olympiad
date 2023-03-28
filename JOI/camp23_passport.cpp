#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXT = 530000;

struct passport {
	int l, r, idx;
};

struct seg {
	pi tree[MAXT];
	int lim;
	void init(int n, vector<passport> &a) {
		for (lim = 1; lim <= n; lim <<= 1)
			;
		fill(tree, tree + MAXT, pi{int(-1e9), -1});
		for (int i = 0; i < n; i++) {
			tree[i + lim] = {a[i].r, i};
		}
		for (int i = lim - 1; i > 0; i--) {
			tree[i] = max(tree[2 * i], tree[2 * i + 1]);
		}
	}
	pi query(int s, int e) {
		s += lim;
		e += lim;
		pi ret{int(-1e9), -1};
		while (s < e) {
			if (s % 2 == 1)
				ret = max(ret, tree[s++]);
			if (e % 2 == 0)
				ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			ret = max(ret, tree[s]);
		return ret;
	}
	void remove(int p) {
		p += lim;
		tree[p] = pi{int(-1e9), -1};
		while (p > 1) {
			p >>= 1;
			tree[p] = max(tree[2 * p], tree[2 * p + 1]);
		}
	}
} seg;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<passport> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].l >> a[i].r;
		a[i].idx = i;
		a[i].l--;
		a[i].r--;
	}
	auto dijkstra = [&](vector<int> dp) {
		seg.init(n, a);
		priority_queue<pi, vector<pi>, greater<pi>> pq;
		vector<int> cnt(n);
		for (int i = 0; i < n; i++) {
			pq.push({dp[i], i});
			cnt[a[i].l]++;
		}
		for (int i = 1; i < n; i++)
			cnt[i] += cnt[i - 1];
		while (sz(pq)) {
			auto [d, v] = pq.top();
			pq.pop();
			if (dp[v] != d)
				continue;
			while (true) {
				auto z = seg.query(0, cnt[v] - 1);
				int nvtx = a[z[1]].idx;
				if (z[0] >= v) {
					if (dp[nvtx] > d + 1) {
						dp[nvtx] = d + 1;
						pq.push({dp[nvtx], nvtx});
					}
				} else
					break;
				seg.remove(z[1]);
			}
		}
		return dp;
	};
	vector<int> toLeft(n), toRight(n);
	for (int i = 0; i < n; i++) {
		toLeft[i] = 1e9;
		if (a[i].l == 0)
			toLeft[i] = 0;
	}
	for (int i = n - 1; i >= 0; i--) {
		toRight[i] = 1e9;
		if (a[i].r == n - 1)
			toRight[i] = 0;
	}
	sort(all(a), [&](const passport &a, const passport &b) { return a.l < b.l; });
	toLeft = dijkstra(toLeft);
	toRight = dijkstra(toRight);
	vector<int> dp(n, 1e9);
	for (int i = 0; i < n; i++) {
		int z = toLeft[i] + toRight[i];
		dp[i] = z;
	}
	dp = dijkstra(dp);
	int q;
	cin >> q;
	while (q--) {
		int z;
		cin >> z;
		z--;
		if (dp[z] > 1e8)
			cout << "-1\n";
		else
			cout << dp[z] + 1 << "\n";
	}
}