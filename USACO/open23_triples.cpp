#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

const int MAXN = 400005;
vector<int> gph[MAXN];
int pa[MAXN], tpar[MAXN], n;
lint mass[MAXN], massDown[MAXN];
lint sum1[MAXN], sum2[MAXN];
lint ans;

void dfs(int x, int p = -1) {
	for (auto &y : gph[x]) {
		if (y != p) {
			tpar[y] = x;
			dfs(y, x);
		}
	}
}

int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }

int THRES;

void LOCK(int j) {
	ans -= (mass[j] + 1) * mass[j] * (mass[j] - 1);
	ans -= 2 * mass[j] * massDown[j];
	if (THRES <= tpar[j])
		ans -= sum1[tpar[j]] * sum1[tpar[j]] - sum2[tpar[j]];
	sum1[tpar[j]] -= mass[j];
	sum2[tpar[j]] -= mass[j] * mass[j];
}

void RELEASE(int j, int init = 0) {
	ans += (mass[j] + 1) * mass[j] * (mass[j] - 1);
	ans += 2 * mass[j] * massDown[j];
	sum1[tpar[j]] += mass[j];
	sum2[tpar[j]] += mass[j] * mass[j];
	if (THRES <= tpar[j] && !init)
		ans += sum1[tpar[j]] * sum1[tpar[j]] - sum2[tpar[j]];
}

void upd(int p, int v) {
	p = find(p);
	LOCK(p);
	mass[p] += v;
	RELEASE(p);
	if (tpar[p] != n - 1) {
		LOCK(find(tpar[tpar[p]]));
		massDown[find(tpar[tpar[p]])] += v;
		RELEASE(find(tpar[tpar[p]]));
	}
}

void merge(int x, int p) {
	p = find(p);
	x = find(x);
	upd(p, mass[x]);
	LOCK(p);
	massDown[p] -= mass[x];
	massDown[p] += massDown[x];
	RELEASE(p);
	pa[x] = p;
	LOCK(x);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(i + n);
		gph[v].push_back(i + n);
		gph[i + n].push_back(u);
		gph[i + n].push_back(v);
	}
	dfs(n - 1);
	iota(pa, pa + 2 * n, 0);
	for (int i = n; i < 2 * n - 1; i++) {
		mass[i] = sz(gph[i]) - 1;
	}
	for (int j = 0; j < n - 1; j++) {
		for (auto &k : gph[j]) {
			if (k == tpar[j])
				continue;
			massDown[tpar[j]] += mass[k];
		}
	}
	for (int i = n; i < 2 * n - 1; i++) {
		RELEASE(i, 1);
	}
	for (int i = 0; i < n; i++)
		ans += sum1[i] * sum1[i] - sum2[i];
	for (int i = 0; i < n - 1; i++) {
		cout << ans << "\n";
		ans -= sum1[i] * sum1[i] - sum2[i];
		THRES++;

		upd(tpar[i], -1);
		// compute quantity
		for (auto &j : gph[i]) {
			if (j == tpar[i])
				continue;
			merge(j, tpar[i]);
		}
	}
	cout << "0\n";
}