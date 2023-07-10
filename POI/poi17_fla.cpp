#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<int, 2>;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, _;
	cin >> n >> _;
	auto div2 = [&](int x) { return x >> 1; };
	vector<pi> vect, ban;
	vect.push_back({0, 0});
	for (int i = 0; i < n; i++) {
		int x, a, b;
		cin >> x >> a >> b;
		a++;
		if (a == b) {
			cout << "NIE\n";
			return 0;
		}
		{
			int y1 = div2(x + a + 1);
			int x1 = div2(x - a);
			if (x1 < 0) {
				cout << "NIE\n";
				return 0;
			}
			vect.push_back({x1, y1});
		}
		{
			int y1 = div2(x + b + 1);
			int x1 = div2(x - b);
			if (x1 >= 0)
				ban.push_back({x1, y1});
		}
	}
	{
		sort(all(vect));
		int cur = -1;
		vector<pi> ans;
		for (int i = 0; i < sz(vect);) {
			int j = i;
			while (j < sz(vect) && vect[i][0] == vect[j][0])
				j++;
			if (cur < vect[j - 1][1]) {
				ans.push_back(vect[j - 1]);
				cur = vect[j - 1][1];
			}
			i = j;
		}
		vect = ans;
	}
	for (auto &[x, y] : ban) {
		auto it = --lower_bound(all(vect), pi{x, int(2e9)});
		if ((*it)[1] >= y) {
			cout << "NIE\n";
			return 0;
		}
	}
	cout << vect.back()[1] << "\n";
}
