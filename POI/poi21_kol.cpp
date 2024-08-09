#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 1000005;

lint spt[20][MAXN];
int lg[MAXN], ptr[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for (int i = 1; i < MAXN; i++) {
		lg[i] = lg[i - 1];
		while ((2 << lg[i]) <= i)
			lg[i]++;
	}
	int n;
	cin >> n;
	vector<pi> v;
	{
		vector<pi> a(n), b;
		for (auto &[x, y] : a)
			cin >> x >> y;
		sort(all(a));
		for (int i = 0; i < n;) {
			int j = i;
			lint g = 0;
			while (j < n && a[j][0] == a[i][0])
				g = gcd(g, a[j++][1]);
			b.push_back({a[i][0], g});
			i = j;
		}
		n = sz(b);
		v = b;
	}
	for (int i = 0; i < n; i++)
		spt[0][i] = v[i][1];
	for (int i = 1; i <= 19; i++) {
		for (int j = 0; j < n; j++) {
			spt[i][j] = spt[i - 1][j];
			if (j + (1 << (i - 1)) < n)
				spt[i][j] = gcd(spt[i][j], spt[i - 1][j + (1 << (i - 1))]);
		}
	}
	auto query = [&](int s, int e) {
		int l = lg[e - s];
		return gcd(spt[l][s], spt[l][e - (1 << l)]);
	};
	for (int i = 0; i < n; i++)
		ptr[v[i][0]]++;
	for (int i = 1; i < MAXN; i++)
		ptr[i] += ptr[i - 1];
	int ans = 1;
	for (int g = 2; g <= 500000; g++) {
		lint h = g;
		for (int j = 0; j < 500000; j += g) {
			int l = ptr[j], r = ptr[j + g - 1];
			if (l < r)
				h = gcd(h, query(l, r));
			if (h <= ans)
				break;
		}
		ans = max(ans, (int)h);
	}
	cout << max(1ll * ans, spt[19][0]) << "\n";
}