#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;

struct bit {
	lint tree[MAXN];
	void add(int x, int v) {
		for (int i = x + 2; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	lint query(int x) {
		lint ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;
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
		vector<int> cnt(10);
		for (int i = 0; i < sz(s); i++)
			cnt[s[i] - '0']++;
		auto trial = [&](int a, int b) {
			auto z = cnt;
			z[1] -= 2 * b;
			z[0] -= a;
			if (*min_element(all(z)) < 0)
				return false;
			int sum = accumulate(z.begin(), z.begin() + 6, 0);
			if (sum < a + b)
				return false;
			sum = accumulate(z.begin(), z.begin() + 10, 0);
			if (sum < 3 * a + 2 * b)
				return false;
			return true;
		};
		int ans = 0;
		int j = n / 4;
		for (int i = 0; trial(i, 0); i++) {
			while (j && trial(i, j) == 0)
				j--;
			ans = max(ans, i + j);
		}
		cout << ans << "\n";
	}
}