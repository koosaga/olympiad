#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

vector<int> generate(lint n, lint m) {
	vector<int> cnt(n, 1);
	int l = 0, h = n - 1;
	lint sum = n * (n - 1) * (n - 2) / 6;
	while (sum > m) {
		while (cnt[l] == 0)
			l++;
		while (cnt[h] == 0)
			h--;
		int maxd = h - l;
		if (maxd <= 1)
			return vector<int>();
		if (maxd - 1 <= sum - m) {
			cnt[l]--;
			cnt[l + 1]++;
			cnt[h]--;
			cnt[h - 1]++;
			sum -= maxd - 1;
		} else {
			bool did = 0;
			for (int j = l + 1; j <= h - 2; j++) {
				if (cnt[j] && h - j - 1 <= sum - m) {
					sum -= h - j - 1;
					cnt[h]--;
					cnt[h - 1]++;
					cnt[j]--;
					cnt[j + 1]++;

					did = 1;
					break;
				}
			}
			if (!did)
				assert(0);
		}
	}
	vector<int> ans;
	for (int j = 0; j < n; j++) {
		for (int k = 0; k < cnt[j]; k++)
			ans.push_back(j);
	}
	return ans;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int q;
	cin >> q;
	while (q--) {
		lint n, m;
		cin >> n >> m;
		lint t = n * (n - 1) * (n - 2) / 6;
		auto deg = generate(n, t - m); // sum d (d - 1) / 2
		if (sz(deg) == 0) {
			cout << "No\n";
			continue;
		}
		vector<int> vtx(n);
		iota(all(vtx), 0);
		vector<vector<int>> adj(n, vector<int>(n));
		for (int i = 0; i < n; i++) {
			sort(all(vtx), [&](const int &p, const int &q) { return deg[p] > deg[q]; });
			int v = vtx.back();
			for (int j = n - i - 1 - deg[v]; j < n - i - 1; j++) {
				adj[v][vtx[j]] = 1;
			}
			for (int j = 0; j < n - i - 1 - deg[v]; j++) {
				deg[vtx[j]]--;
				adj[vtx[j]][v] = 1;
			}
			deg[v] = 0;
			vtx.pop_back();
		}
		cout << "Yes\n";
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < i; j++)
				cout << adj[i][j];
			cout << "\n";
		}
	}
}