#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 2100000;

struct rectangle {
	int sx, ex, sy, ey;
	lint area() { return 1ll * max(ex - sx, 0) * max(ey - sy, 0); }
	rectangle operator+(const rectangle &r) const { return (rectangle){max(sx, r.sx), min(ex, r.ex), max(sy, r.sy), min(ey, r.ey)}; }
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<rectangle> rec;
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		rec.push_back({x1, x2, y1, y2});
	}
	lint ret = 0;
	auto pfx = rec, sfx = rec;
	for (int i = 1; i < n; i++)
		pfx[i] = pfx[i - 1] + rec[i];
	for (int i = n - 2; i >= 0; i--)
		sfx[i] = sfx[i + 1] + rec[i];
	for (int i = 0; i < n; i++) {
		if (i == 0)
			ret += sfx[i + 1].area();
		else if (i < n - 1)
			ret += (pfx[i - 1] + sfx[i + 1]).area();
		else
			ret += pfx[i - 1].area();
	}
	ret -= (n)*pfx[n - 1].area();

	cout << ret << "\n";
}
