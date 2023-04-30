#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 30005;

int w[MAXN];
vector<int> divs[MAXN];

struct hasher {
	size_t operator()(const vector<short> &v) const {
		size_t foo = 0;
		for (auto &x : v) {
			foo = (foo << 16) + foo + x;
		}
		return foo;
	}
};

unordered_map<vector<short>, int, hasher> mp;

void norm(vector<short> &v) {
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
}

int f(vector<short> needs) {
	norm(needs);
	if (sz(needs) == 1 && needs[0] == 1)
		return w[1];
	if (mp.count(needs))
		return mp[needs];
	int ret = 1e9;
	for (int i = 0; i < sz(needs); i++) {
		if (needs[i] == 1)
			continue;
		vector<short> copies = needs;
		copies[i]--;
		ret = min(ret, f(copies) + w[needs[i]]);
		copies[i]++;
		copies.erase(copies.begin() + i);
		for (auto &j : divs[needs[i]]) {
			copies.push_back(j);
			copies.push_back(needs[i] / j);
			ret = min(ret, f(copies) + w[needs[i]]);
			copies.pop_back();
			copies.pop_back();
		}
	}
	return mp[needs] = ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> w[i];
	for (int i = 2; i * i <= n; i++) {
		for (int j = i * i; j <= n; j += i)
			divs[j].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		cout << f({(short)i}) << "\n";
	}
}