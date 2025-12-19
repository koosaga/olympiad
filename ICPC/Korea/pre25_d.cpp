#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
vector<int> split(int n, vector<pi> edges) {
	if (sz(edges) == 0)
		return {};
	vector<vector<int>> gph(n);
	vector<int> nxt(sz(edges) * 2), vis(sz(edges) * 2);
	for (int i = 0; i < sz(edges); i++) {
		auto [u, v] = edges[i];
		v += n / 2;
		gph[u].push_back(2 * i);
		gph[v].push_back(2 * i + 1);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < sz(gph[i]); j += 2) {
			nxt[gph[i][j]] = (gph[i][j + 1] ^ 1);
			nxt[gph[i][j + 1]] = (gph[i][j] ^ 1);
		}
	}
	vector<int> ans;
	for (int i = 0; i < sz(edges) * 2; i++) {
		if (!vis[i]) {
			for (int j = i; !vis[j]; j = nxt[j]) {
				ans.push_back(j);
				vis[j] = vis[j ^ 1] = 1;
			}
		}
	}
	return ans;
}

vector<int> EdgeColoringRegular(int n, int k, vector<pi> edges) {
	/*cerr << n << " " << k << " " << sz(edges) << endl;
	for (auto &[u, v] : edges)
		cout << u << " " << v << endl;*/
	assert(k > 0);
	if (k == 1) {
		return vector<int>(sz(edges));
	}
	if (k % 2 == 0) {
		auto decomp = split(2 * n, edges);
		vector<pi> sub[2];
		for (int i = 0; i < sz(decomp); i++) {
			sub[i % 2].push_back(edges[decomp[i] / 2]);
		}
		vector<int> rec[2];
		rec[0] = EdgeColoringRegular(n, k / 2, sub[0]);
		rec[1] = EdgeColoringRegular(n, k / 2, sub[1]);
		vector<int> ans(sz(edges));
		for (int i = 0; i < sz(decomp); i++) {
			ans[decomp[i] / 2] = rec[i % 2][i / 2] + (i % 2) * (k / 2);
		}
		return ans;
	}
	int t = 0;
	while ((1 << t) < k * n)
		t++;
	vector<array<int, 4>> todnc;
	int alph = (1 << t) / k;
	int beta = (1 << t) - k * alph; // < k
	for (int i = 0; i < sz(edges); i++) {
		todnc.push_back({edges[i][0], edges[i][1] + n, alph, i});
	}
	if (beta > 0) {
		for (int i = 0; i < n; i++) {
			todnc.push_back({i, i + n, beta, -1});
		}
	}
	for (int i = 0; i < t; i++) {
		vector<pi> toeuler;
		vector<array<int, 4>> sub[2];
		for (auto &[u, v, k, idx] : todnc) {
			if (k % 2)
				toeuler.push_back({u, v - n});
		}
		sub[1] = sub[0];
		auto pth = split(2 * n, toeuler);
		vector<int> parity(sz(toeuler));
		for (int i = 1; i < sz(pth); i += 2)
			parity[pth[i] / 2] = 1;
		int ptr = 0, bal = 0;
		for (auto &[u, v, k, idx] : todnc) {
			int l = k / 2, r = k / 2;
			if (k % 2) {
				if (parity[ptr++])
					r++;
				else
					l++;
			}
			if (idx == -1)
				bal += l - r;
			if (l)
				sub[0].push_back({u, v, l, idx});
			if (r)
				sub[1].push_back({u, v, r, idx});
		}
		if (bal >= 0)
			todnc = sub[1];
		else
			todnc = sub[0];
	}
	vector<int> ans(sz(edges), -1);
	for (auto &[u, v, z, idx] : todnc) {
		assert(z == 1 && idx != -1);
		ans[idx] = k - 1;
	}
	vector<pi> sub;
	for (int i = 0; i < sz(edges); i++) {
		if (ans[i] == -1)
			sub.push_back(edges[i]);
	}
	int piv = 0;
	auto sol = EdgeColoringRegular(n, k - 1, sub);
	for (int i = 0; i < sz(edges); i++) {
		if (ans[i] == -1)
			ans[i] = sol[piv++];
	}
	return ans;
}

vector<int> EdgeColoring(int l, int r, vector<pi> edges) {
	if (sz(edges) == 0)
		return vector<int>();
	vector<int> d[2];
	cr(d[0], l);
	cr(d[1], r);
	for (auto &[x, y] : edges)
		d[0][x]++, d[1][y]++;
	int k = max(*max_element(all(d[0])), *max_element(all(d[1])));
	for (int i = 0; i < 2; i++) {
		vector<int> ord(l);
		iota(all(ord), 0);
		sort(all(ord), [&](int x, int y) { return d[i][x] < d[i][y]; });
		vector<int> maps(l);
		int nl = 0;
		for (int j = 0; j < sz(ord);) {
			int nxt = j, sum = 0;
			while (nxt < sz(ord) && sum + d[i][ord[nxt]] <= k) {
				sum += d[i][ord[nxt]];
				maps[ord[nxt]] = nl;
				nxt++;
			}
			nl++;
			j = nxt;
		}
		for (auto &e : edges) {
			e[i] = maps[e[i]];
		}
		l = nl;
		swap(l, r);
	}
	int n = max(l, r);
	cr(d[0], n);
	cr(d[1], n);
	for (auto &[x, y] : edges)
		d[0][x]++, d[1][y]++;
	int j = 0;
	int orig = sz(edges);
	for (int i = 0; i < n; i++) {
		while (d[0][i] < k) {
			while (d[1][j] == k)
				j++;
			edges.push_back({i, j});
			d[0][i]++;
			d[1][j]++;
		}
	}
	auto sol = EdgeColoringRegular(n, k, edges);
	sol.resize(orig);
	return sol;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	bool triv = true;
	vector<pi> edges;
	vector<vector<int>> a(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		set<int> s;
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
			edges.push_back({i, a[i][j] / n});
			s.insert(a[i][j] / n);
		}
		if (sz(s) != n)
			triv = false;
	}
	if (triv) {
		cout << "0\n";
		return 0;
	}
	auto sol = EdgeColoring(n, n, edges);
	for (int i = 0; i < n; i++) {
		vector<int> dest(n);
		for (int j = 0; j < n; j++) {
			dest[sol[i * n + j]] = a[i][j];
		}
		for (int j = 0; j < n; j++)
			a[i][j] = dest[j];
	}
	cout << (n * n - n) / 2 << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (a[i][j] > a[j][i])
				swap(a[i][j], a[j][i]);
			cout << a[i][j] << " " << a[j][i] << "\n";
		}
	}
}