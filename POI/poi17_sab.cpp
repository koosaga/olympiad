#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 500005;

vector<int> gph[MAXN];
int sz[MAXN];

void dfs(int x) {
	sz[x] = 1;
	for (auto &y : gph[x]) {
		dfs(y);
		sz[x] += sz[y];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		gph[p].push_back(i);
	}
	dfs(0);
	auto trial = [&](double T) {
		T = max(T, 1e-8);
		vector<int> max_valid(n, -1);
		for (int i = n - 1; i >= 0; i--) {
			if (sz(gph[i]) == 0) {
				max_valid[i] = (int)floor(1 / T);
			} else {
				for (auto &j : gph[i]) {
					if (max_valid[j] >= sz[i] - 1) {
						max_valid[i] = max(max_valid[i], max_valid[j]);
					}
				}
				if (max_valid[i] >= 0) {
					max_valid[i] = max(max_valid[i], (int)floor(min(1e8, sz[i] / T)));
				}
			}
		}
		for (int i = 0; i < n; i++) {
			if (sz[i] > k && max_valid[i] >= 0)
				return false;
		}
		return true;
	};
	double s = 0, e = 1;
	for (int i = 0; i < 45; i++) {
		double m = (s + e) / 2;
		if (trial(m))
			e = m;
		else
			s = m;
	}
	cout << setprecision(69) << (s + e) / 2 << "\n";
}