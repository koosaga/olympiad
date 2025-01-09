#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXT = 300005;
const int mod = 1e9 + 7;

lint sum(lint x) { return x * (x + 1) / 2; }

string expand(string s) {
	string t = s;
	for (int i = 0; i < sz(s); i++) {
		if (t[i] == '0') {
			if (i > 0 && s[i - 1] == '1')
				t[i] = '1';
			if (i + 1 < sz(s) && s[i + 1] == '1')
				t[i] = '1';
		}
	}
	return t;
}

int brute(string s) {
	if (count(all(s), '0') == 0)
		return count(all(s), '1');
	int ret = 1e9;
	for (int i = 0; i < sz(s); i++) {
		if (s[i] == '0') {
			s[i] = '2';
			ret = min(ret, brute(expand(s)));
			s[i] = '0';
		}
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		string s;
		cin >> s;
		if (count(all(s), '0') == n) {
			cout << 0 << "\n";
			continue;
		}
		vector<int> v1, v2;
		lint save = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == '0') {
				int j = i;
				while (j < n && s[j] == '0')
					j++;
				if (i == 0 || j == n)
					v1.push_back(j - i);
				else
					v2.push_back(j - i);
				i = j - 1;
			}
		}
		sort(all(v1));
		sort(all(v2));
		reverse(all(v1));
		reverse(all(v2));
		map<int, int> mp;
		for (auto &x : v1)
			mp[x]++;
		int cur = sz(v1);
		auto solve = [&](int t, int nxt) {
			auto it = mp.end();
			lint ans = 0;
			int tbeg = t;
			while (it != mp.begin()) {
				auto [k, v] = *--it;
				if (k - t - v > 0) {
					ans += sum(k - t) - sum(k - v - t);
					t += v;
				} else {
					if (k > t) {
						ans += sum(k - t);
						t = k;
					}
					break;
				}
			}
			if (2 * t + 1 <= nxt)
				ans++;
			return ans;
		};
		v2.push_back(-1);
		save = max(save, solve(0, v2[0]));
		for (int i = 0; i < sz(v2) - 1; i++) {
			if (v2[i] > 2 * i + 1) {
				mp[v2[i] - i - 1]++;
				cur++;
				save = max(save, solve(i + 1, v2[i + 1]) + i + 1);
			} else if (v2[i] == 2 * i + 1) {
				save = max(save, solve(i + 1, v2[i + 1]) + i + 1);
			}
		}
		cout << n - save << "\n";
	}
}