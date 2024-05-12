#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using node = array<int, 5>;
const int score[4] = {0, 1, 2, -1};

void solve() {
	int n;
	cin >> n;
	string a;
	cin >> a;
	for (auto &z : a)
		z -= '0';
	vector<int> b(n);
	for (auto &x : b)
		cin >> x;
	int PP;
	cin >> PP;
	vector<pi> dp(n + 1);
	vector<int> trk(n + 1);
	vector<int> scsum(n + 1), sum(n + 1);
	scsum[0] = n;
	for (int i = 1; i <= n; i++) {
		sum[i] = sum[i - 1] + a[i - 1];
		scsum[i] = scsum[i - 1] + score[a[i - 1]];
	}
	vector<vector<array<int, 3>>> opts(4, vector<array<int, 3>>(3 * n + 5, array<int, 3>{int(1e9), int(1e9), int(1e9)}));
	vector<int> validTill(4, 3 * n + 4);
	for (int i = 1; i <= n; i++) {
		{
			opts[sum[i - 1] % 4][scsum[i - 1]] = min(opts[sum[i - 1] % 4][scsum[i - 1]], array<int, 3>{dp[i - 1][0], dp[i - 1][1], i - 1});
			validTill[sum[i - 1] % 4] = min(validTill[sum[i - 1] % 4], scsum[i - 1]);
		}
		dp[i] = pi{dp[i - 1][0] + a[i - 1], dp[i - 1][1] - b[i - 1]};
		trk[i] = i;
		while (validTill[sum[i] % 4] < scsum[i]) {
			opts[sum[i] % 4][validTill[sum[i] % 4] + 1] = min(opts[sum[i] % 4][validTill[sum[i] % 4] + 1], opts[sum[i] % 4][validTill[sum[i] % 4]]);
			validTill[sum[i] % 4]++;
		}
		auto [p, q, r] = opts[sum[i] % 4][scsum[i]];
		if (dp[i] > pi{p, q}) {
			dp[i] = pi{p, q};
			trk[i] = r;
		}
	}
	cout << dp[n][0] << " " << -dp[n][1] << "\n";
	if (PP == 1)
		return;
	vector<vector<int>> ans;
	auto prune = [&](vector<int> v) {
		deque<int> stk;
		for (int it = 0; it < sz(v); it++) {
			int i = v[it];
			if (a[i] <= 2)
				stk.push_back(i);
			else {
				int j = it;
				deque<int> tres;
				while (j < sz(v) && a[v[j]] == 3) {
					tres.push_back(v[j++]);
				}
				while (sz(tres) >= 2 || (sz(tres) == 1 && ((sz(stk) && a[stk.back()] == 1) || (j < sz(v) && a[v[j]] == 1)))) {
					while (sz(tres) >= 2 && sz(stk)) {
						if (a[stk.back()] == 1) {
							ans.push_back({stk.back(), tres[0]});
							tres.pop_front();
							stk.pop_back();
							while (sz(stk) && a[stk.back()] == 3) {
								tres.push_front(stk.back());
								stk.pop_back();
							}
						} else if (a[stk.back()] == 2) {
							ans.push_back({stk.back(), tres[0], tres[1]});
							tres.pop_front();
							tres.pop_front();
							stk.pop_back();
							while (sz(stk) && a[stk.back()] == 3) {
								tres.push_front(stk.back());
								stk.pop_back();
							}
						} else {
							while (sz(stk) && a[stk.back()] == 3) {
								tres.push_front(stk.back());
								stk.pop_back();
							}
						}
					}
					while (sz(stk) && sz(tres) && a[stk.back()] == 1) {
						ans.push_back({stk.back(), tres[0]});
						stk.pop_back();
						tres.pop_front();
						while (sz(stk) && a[stk.back()] == 3) {
							tres.push_front(stk.back());
							stk.pop_back();
						}
					}
					while (sz(tres) >= 2 && j < sz(v)) {
						if (a[v[j]] == 1) {
							ans.push_back({tres[sz(tres) - 1], v[j]});
							tres.pop_back();
							j++;
							while (j < sz(v) && a[v[j]] == 3) {
								tres.push_back(v[j]);
								j++;
							}
						} else if (a[v[j]] == 2) {
							ans.push_back({tres[sz(tres) - 2], tres[sz(tres) - 1], v[j]});
							tres.pop_back();
							tres.pop_back();
							j++;
							while (j < sz(v) && a[v[j]] == 3) {
								tres.push_back(v[j]);
								j++;
							}
						} else {
							while (j < sz(v) && a[v[j]] == 3) {
								tres.push_back(v[j]);
								j++;
							}
						}
					}
					while (j < sz(v) && sz(tres) && a[v[j]] == 1) {
						ans.push_back({tres[sz(tres) - 1], v[j]});
						j++;
						tres.pop_back();
						while (j < sz(v) && a[v[j]] == 3) {
							tres.push_back(v[j]);
							j++;
						}
					}
				}
				assert(sz(tres) <= 1);
				for (auto &x : tres)
					stk.push_back(x);
				it = j - 1;
			}
		}
		return stk;
	};
	auto go = [&](int l, int r) {
		vector<int> v(r - l);
		iota(all(v), l);
		deque<int> stk = prune(v);
		int sum = 0;
		for (auto &x : stk)
			sum += score[a[x]];
		assert(sum % 4 == 0);
		while (sum >= 4) {
			bool ok = 0;
			for (int i = 0; i < sz(stk) && i < 4; i++) {
				int sumIntv = 0, sumScore = 0;
				for (int j = i + 1; j <= sz(stk) && j <= 4; j++) {
					sumIntv += a[stk[j - 1]];
					sumScore += score[a[stk[j - 1]]];
					if (sumIntv % 4 == 0) {
						assert(sumScore == 0 || sumScore == 4);
						sum -= sumScore;
						vector<int> toput(stk.begin() + i, stk.begin() + j);
						ans.push_back(toput);
						vector<int> fst(stk.begin(), stk.begin() + i);
						for (int x = 0; x < j; x++)
							stk.pop_front();
						for (int x = i - 1; x >= 0; x--)
							stk.push_front(fst[x]);
						ok = 1;
						break;
					}
				}
				if (ok)
					break;
			}
		}
		assert(sum == 0);

		auto pstk = prune(vector<int>(all(stk)));
		auto realStk = vector<int>(all(pstk));

		if (sz(realStk)) {
			if (sz(realStk) != 3) {
				cout << "FUCK";
				for (auto &x : realStk)
					cout << (int)a[x];
				cout << "INPUT";
				for (auto &x : stk)
					cout << (int)a[x];
				cout << endl;
				exit(0);
			}
			assert(sz(realStk) == 3);
			ans.push_back(realStk);
		}
	};
	for (int i = n; i > 0;) {
		if (trk[i] == i) {
			i--;
			continue;
		}
		int l = trk[i], r = i; // [l, r)
		if (r - l <= 4) {
			vector<int> iot(r - l);
			iota(all(iot), l);
			ans.push_back(iot);
		} else {
			go(l, r);
		}
		i = trk[i];
	}
	cout << sz(ans) << "\n";
	for (auto &v : ans) {
		cout << sz(v) << " ";
		for (auto &w : v)
			cout << w + 1 << " ";
		cout << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
}