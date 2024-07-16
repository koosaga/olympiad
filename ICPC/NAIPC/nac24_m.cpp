#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int MAXN = 5005;

bitset<MAXN> xcoord[MAXN], ycoord[MAXN];
int dist[MAXN][MAXN];
vector<pi> que[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, x, y;
	cin >> n >> x >> y;
	for (int i = 0; i < n; i++) {
		int sx, ex, sy, ey;
		cin >> sx >> ex >> sy >> ey;
		sx -= x;
		ex -= x;
		sy -= y;
		ey -= y;
		sx = max(sx, 0);
		sy = max(sy, 0);
		ex = min(ex, n);
		ey = min(ey, n);
		for (int j = sx; j <= ex; j++) {
			xcoord[j][i] = 1;
		}
		for (int j = sy; j <= ey; j++) {
			ycoord[j][i] = 1;
		}
	}
	memset(dist, 0x3f, sizeof(dist));
	auto enq = [&](int x, int y, int d) {
		if (dist[x][y] > d) {
			dist[x][y] = d;
			que[d].push_back({x, y});
		}
	};
	enq(0, 0, 0);
	int ans = 0;
	for (int i = 0; i <= n; i++) {
		for (auto &[x, y] : que[i]) {
			ans = max(ans, x + y);
			auto mask = ((xcoord[x] & ycoord[y]) >> i);
			if (mask.any()) {
				int z = mask._Find_first() + i;
				enq(x + 1, y, z + 1);
				enq(x, y + 1, z + 1);
			}
		}
	}
	cout << ans << "\n";
}