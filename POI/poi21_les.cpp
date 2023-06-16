#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
 
const int MAXN = 500005;
 
struct level_structure {
	vector<lint> v;
	int fr = 0;
	lint sum_odd = 0, sum_even = 0;
	lint current_odd_gamma = 0;
	lint removed_odd_gamma = 0;
	lint current_even_gamma = 0;
	lint removed_even_gamma = 0;
	priority_queue<pi, vector<pi>, greater<pi>> pqOdd, pqEven; // valid till fr <= i.second
	void clear() {
		fr = 0;
		v.clear();
		sum_even = sum_odd = 0;
		current_odd_gamma = 0;
		removed_odd_gamma = 0;
		current_even_gamma = 0;
		removed_even_gamma = 0;
		while (sz(pqOdd))
			pqOdd.pop();
		while (sz(pqEven))
			pqEven.pop();
	}
	void push(lint x) {
		if (v.size() & 1) {
			sum_odd += x;
			if (v.size() >= 2) {
				current_odd_gamma += 2 * v[v.size() - 1] - x - v[v.size() - 2];
				pqOdd.emplace(current_odd_gamma, v.size() - 2);
			}
		} else {
			sum_even += x;
			if (v.size() >= 2) {
				current_even_gamma += 2 * v[v.size() - 1] - x - v[v.size() - 2];
				pqEven.emplace(current_even_gamma, v.size() - 2);
			}
		}
		v.push_back(x);
	}
	void pop() {
		if (fr & 1) {
			sum_odd -= v[fr];
			if (fr + 2 < v.size())
				removed_odd_gamma += 2 * v[fr + 1] - v[fr + 2] - v[fr];
		} else {
			sum_even -= v[fr];
			if (fr + 2 < v.size())
				removed_even_gamma += 2 * v[fr + 1] - v[fr + 2] - v[fr];
		}
		while (!pqOdd.empty() && pqOdd.top().second < fr)
			pqOdd.pop();
		while (!pqEven.empty() && pqEven.top().second < fr)
			pqEven.pop();
		fr++;
	}
	lint query() {
		if (fr % 2 == v.size() % 2)
			return abs(sum_even - sum_odd);
		lint ans = 0;
		if (v.size() & 1)
			ans = sum_even - sum_odd - v[fr];
		else
			ans = sum_odd - sum_even - v[fr];
		if (fr & 1) {
			if (!pqOdd.empty())
				ans += min(0ll, pqOdd.top().first - removed_odd_gamma);
		} else {
			if (!pqEven.empty())
				ans += min(0ll, pqEven.top().first - removed_even_gamma);
		}
		return ans;
	}
} ds[3 * MAXN];
 
lint prv_ans[3 * MAXN];
 
lint query(vector<lint> a, vector<lint> b, lint d) {
	if (sz(a) == 0 && sz(b) == 0)
		return 0;
	if (sz(a) < sz(b))
		swap(a, b);
	vector<pi> v;
	for (int i = 0; i < sz(a); i++)
		v.emplace_back(a[i], +1);
	for (int i = 0; i < sz(a) - sz(b); i++)
		v.emplace_back(0, -1);
	for (int i = 0; i < sz(b); i++)
		v.emplace_back(b[i], -1);
	sort(all(v));
	v.resize(2 * v.size());
	copy(v.begin(), v.begin() + v.size() / 2, v.begin() + v.size() / 2);
	for (int i = v.size() / 2; i < v.size(); i++)
		v[i].first += d;
	lint f = sz(a);
	for (auto &i : v) {
		int assign_floor = max(f, f + i.second);
		f += i.second;
		i.second = assign_floor;
	}
	lint ans = 1e18;
	int p1 = 0, p2 = 0;
	lint cur = 0;
	for (int i = 0; i < sz(v) / 2; i++) {
		while (p2 < v.size() && v[p2].first < v[i].first + d) {
			cur -= prv_ans[v[p2].second];
			ds[v[p2].second].push(v[p2].first);
			cur += (prv_ans[v[p2].second] = ds[v[p2].second].query());
			p2++;
		}
		while (p1 < v.size() && v[p1].first < v[i].first) {
			cur -= prv_ans[v[p1].second];
			ds[v[p1].second].pop();
			cur += (prv_ans[v[p1].second] = ds[v[p1].second].query());
			p1++;
		}
		ans = min(ans, cur);
	}
	for (int i = 0; i < sz(a) * 3 + 4; i++) {
		ds[i].clear();
		prv_ans[i] = 0;
	}
	return ans;
}
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, d;
	cin >> n >> d;
	vector<vector<lint>> pos(n);
	for (auto &v : pos) {
		int z;
		cin >> z;
		v.resize(z);
		for (auto &w : v)
			cin >> w;
	}
	for (int i = 1; i < n; i++) {
		cout << query(pos[i - 1], pos[i], d) << "\n";
	}
}