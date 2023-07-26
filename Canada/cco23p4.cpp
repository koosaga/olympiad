#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int solve(string s) {
	if (sz(s) <= 2)
		return 0;
	int cnt = count(all(s), '1');
	if (3 * cnt + 2 >= sz(s)) {
		int ans = 0;
		int fast = 0;
		int canfast = 0;
		if (s[0] == '1')
			canfast++;
		if (s.back() == '1')
			canfast++;
		for (int i = 0; i < sz(s) - 1; i++) {
			if (s.substr(i, 2) == "11")
				canfast++;
		}
		for (int i = 0; i < sz(s);) {
			if (s[i] == '1') {
				i++;
				continue;
			}
			int j = i;
			while (j < sz(s) && s[i] == s[j])
				j++;
			int d = j - i;
			if (d >= 2) {
				if (d % 2 == 1)
					ans++, d--;
				fast += d / 2 - 1;
			}
			i = j;
		}
		if (fast <= canfast) {
			ans += fast;
		} else {
			ans += canfast;
			ans += fast * 2 - canfast * 2;
		}
		return ans;
	} else {
		return -1;
	}
}

int dm(string s) {
	map<string, int> vis;
	queue<pair<string, int>> que;
	auto enq = [&](string s, int d) {
		if (!vis.count(s)) {
			vis[s] = d;
			que.emplace(s, d);
		}
	};
	enq(s, 0);
	while (sz(que)) {
		auto [s, d] = que.front();
		bool ok = 0;
		for (int i = 0; i + 3 <= sz(s); i++) {
			if (s.substr(i, 3) == "000") {
				ok = 1;
				break;
			}
		}
		if (!ok)
			return d;
		que.pop();
		for (int i = 0; i < sz(s); i++) {
			for (int j = 2; j <= sz(s) - i; j++) {
				auto k = s;
				reverse(k.begin() + i, k.begin() + i + j);
				enq(k, d + 1);
			}
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s, t;
	cin >> s >> t;
	if (sz(t) == 1) {
		if (count(all(s), t[0]) == 0)
			cout << "0\n";
		else
			cout << "-1\n";
		return 0;
	}
	if (sz(t) == 2) {
		if (t[0] != t[1]) {
			if (t[0] == '0') {
				for (auto &x : s)
					x ^= 1;
			}
			t = "10";
			vector<int> poses;
			for (int i = 0; i < sz(s); i++) {
				if (s[i] == '1')
					poses.push_back(i);
			}
			poses.push_back(sz(s));
			int ans = 0;
			for (int i = 1; i < sz(poses); i++)
				if (poses[i - 1] + 1 != poses[i])
					ans++;
			cout << ans << "\n";
		} else {
			int cnt = count(all(s), t[0]);
			if (2 * cnt - 1 <= sz(s)) {
				int ans = 0;
				for (int i = 0; i + 1 < sz(s); i++) {
					if (s[i] == t[0] && s[i + 1] == t[0])
						ans++;
				}
				cout << ans << "\n";
			} else {
				cout << "-1\n";
			}
		}
		return 0;
	}
	if (t[0] == '1') {
		for (auto &x : s)
			x ^= 1;
		for (auto &x : t)
			x ^= 1;
	}
	if (t[2] == '1') {
		int ans = 0;
		for (int i = 0; i + 3 <= sz(s); i++) {
			if (s.substr(i, 3) == t)
				ans++;
		}
		cout << ans << "\n";
		return 0;
	}
	if (t[1] == '1') {
		int ans = 0;
		for (int i = 0; i + 3 <= sz(s); i++) {
			if (s.substr(i, 3) == t) {
				ans++;
			}
		}
		cout << (ans + 1) / 2 << "\n";
		return 0;
	}
	cout << solve(s) << "\n";
}