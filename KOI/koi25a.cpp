#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> q(n + 1);
	for (int i = 1; i < n; i++)
		cin >> q[i];
	vector<int> starts, ends;
	for (int i = 0; i < n; i++) {
		if (q[i] < q[i + 1])
			starts.push_back(i);
		else if (q[i] > q[i + 1])
			ends.push_back(i);
	}
	assert(sz(starts) == sz(ends));
	vector<int> ans;
	set<int> s;
	for (int i = 0; i < n; i++)
		s.insert(i);
	for (int i = 0; i < sz(starts); i++) {
		s.erase(starts[i]);
		s.erase(ends[i]);
	}
	for (int i = 0; i < sz(starts); i++) {
		ans.push_back(starts[i]);
		auto it = s.lower_bound(starts[i]);
		while (it != s.end() && *it < ends[i]) {
			ans.push_back(*it);
			it = s.erase(it);
		}
		ans.push_back(ends[i]);
	}
	for (auto &x : ans)
		cout << x + 1 << " ";
}