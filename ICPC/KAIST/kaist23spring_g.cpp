#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int N = 35;
const int OFF = N * 100000;

// O(N^2S / 64)
tuple<int, vector<vector<int>>, vector<int>> solve(vector<int> a) {
	int n = sz(a);
	vector<bitset<2 * OFF + 5>> bs(n + 1);
	for (int j = 0; j < n; j++) {
		bs[j + 1] = (bs[j] | (bs[j] << a[j]) | (bs[j] >> a[j]));
		bs[j + 1][a[j] + OFF] = 1;
		bs[j + 1][-a[j] + OFF] = 1;
	}
	vector<int> rems;
	for (int j = OFF;; j++) {
		if (bs[n][j]) {
			int cost = j - OFF;
			vector<pi> vect;
			for (int k = n - 1; k >= 0; k--) {
				if (bs[k][j - a[k]] || j - a[k] == OFF) {
					j -= a[k];
					vect.push_back({a[k], +1});
					if (j == OFF) {
						for (int z = 0; z < k; z++)
							rems.push_back(a[z]);
						break;
					}
				} else if (bs[k][j + a[k]] || j + a[k] == OFF) {
					j += a[k];
					vect.push_back({a[k], -1});
					if (j == OFF) {
						for (int z = 0; z < k; z++)
							rems.push_back(a[z]);
						break;
					}
				} else if (bs[k][j]) {
					rems.push_back(a[k]);
				} else {
					assert(0);
				}
			}
			vector<vector<int>> seqs;
			sort(all(vect));
			// fucking sex
			while (sz(vect) > 1) {
				bool good = 0;

				for (int j = 0; j < sz(vect) - 1; j++) {
					if (vect[j][1] == -1 && vect[j + 1][1] == +1) {
						good = 1;
						seqs.push_back({vect[j + 1][0], vect[j][0]});
						pi toins = {vect[j + 1][0] - vect[j][0], +1};
						vect.erase(vect.begin() + j);
						vect.erase(vect.begin() + j);
						vect.push_back(toins);
						sort(all(vect));
						break;
					}
				}
				if (!good) {
					// +++++ ..... -----
					int cnt = 0;
					for (int j = 0; j < sz(vect); j++) {
						if (vect[j][1] == +1)
							cnt++;
					}
					if (cnt == sz(vect) || cnt == 0) {
						vector<int> unsign;
						for (int j = 0; j < sz(vect); j++) {
							unsign.push_back(vect[j][0]);
						}
						seqs.push_back(unsign);
						int mx = *max_element(all(unsign));
						int mn = *min_element(all(unsign));
						vect.clear();
						vect.push_back({mx - mn, +1});
					} else {
						seqs.push_back({vect[cnt - 1][0], vect[cnt][0]});
						pi toins = {vect[cnt][0] - vect[cnt - 1][0], -1};
						vect.erase(vect.begin() + cnt);
						vect.erase(vect.begin() + cnt - 1);
						vect.push_back(toins);
						sort(all(vect));
					}
				}
			}
			rems.push_back(vect[0][0]);
			assert(cost == vect[0][0]);
			return make_tuple(cost, seqs, rems);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	int cnt = 1;
	for (auto &x : a) {
		cin >> x;
	}
	if (n == 2) {
		cout << "1\n2 " << a[0] << " " << a[1] << "\n";
		return 0;
	}
	auto print = [&](vector<vector<int>> seq) {
		cout << sz(seq) << "\n";
		for (auto &x : seq) {
			cout << sz(x);
			for (auto &y : x) {
				cout << " " << y;
			}
			cout << "\n";
		}
	};
	sort(all(a));
	if (n <= N) {
		int opt = 0;
		vector<vector<int>> ans;
		for (int i = 0; i < n; i++) {
			vector<int> smol;
			for (int j = 0; j < n; j++) {
				if (i != j)
					smol.push_back(a[j]);
			}
			auto [cost, g, w] = solve(smol);
			w.push_back(a[i]);
			g.push_back(w);
			if (opt < a[i] - cost) {
				opt = a[i] - cost;
				ans = g;
			}
		}
		print(ans);
	} else {
		vector<int> smol;
		for (int j = 0; j < min(N, n - 1); j++) {
			smol.push_back(a[j]);
		}
		auto [cost, g, w] = solve(smol);
		for (int j = N; j < n; j++)
			w.push_back(a[j]);
		g.push_back(w);
		print(g);
	}
}