#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2000005;

int nxt2[MAXN][30], nxt3[MAXN][30];
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int m, n;
	cin >> m >> n;
	vector<int> a(n);
	for (auto &x : a) {
		cin >> x;
	}
	vector<int> pfx(n), sfx(n + 1), pfx2(n), sfx2(n + 1);
	for (int i = 0; i < n; i++) {
		pfx[i] = sfx[i] = a[i];
		pfx2[i] = sfx2[i] = a[i];
	}
	lint ans = 0;
	for (int i = 1; i < n; i++)
		pfx[i] = pfx[i - 1] | a[i];
	for (int i = n - 1; i >= 0; i--)
		sfx[i] = sfx[i + 1] | a[i];
	for (int i = 1; i < n; i++)
		pfx2[i] = pfx2[i - 1] & a[i];
	sfx2[n] = (1 << m) - 1;
	for (int i = n - 1; i >= 0; i--)
		sfx2[i] = sfx2[i + 1] & a[i];
	vector<int> nxt0(m), nxt1(m);
	for (int i = 0; i < m; i++) {
		int j = n - 1;
		while (j >= 0 && ((a[n - 1] ^ a[j]) >> i) % 2 == 0)
			j--;
		if ((a[n - 1] >> i) & 1) {
			nxt1[i] = n - 1;
			nxt0[i] = j;
		} else {
			nxt1[i] = j;
			nxt0[i] = n - 1;
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < m; j++) {
			if ((a[i] >> j) & 1) {
				nxt2[i][j] = (i + 1 < n ? nxt2[i + 1][j] : n);
				nxt3[i][j] = i;
			} else {
				nxt2[i][j] = i;
				nxt3[i][j] = (i + 1 < n ? nxt3[i + 1][j] : n);
			}
		}
	}
	for (int i = 1; i < n; i++) {
		auto orMatch = [&]() {
			vector<pi> idxs;
			for (int j = 0; j < m; j++) {
				if ((pfx[i - 1] >> j) & 1)
					continue;
				if (nxt1[j] > i)
					idxs.push_back({nxt1[j], j});
			}
			sort(all(idxs));
			reverse(all(idxs));
			int las = n - 1;
			int orv = pfx[i - 1];
			vector<array<int, 3>> ors, ort;
			for (int i = 0; i < sz(idxs); i++) {
				if (idxs[i][0] <= las) {
					ors.push_back({idxs[i][0], las, orv});
					las = idxs[i][0] - 1;
				}
				orv |= (1 << idxs[i][1]);
			}
			if (i <= las) {
				ors.push_back({i, las, orv});
			}
			idxs.clear();
			for (int j = 0; j < m; j++) {
				if (nxt3[i][j] < n) {
					idxs.push_back({nxt3[i][j], j});
				}
			}
			sort(all(idxs));
			las = i;
			orv = 0;
			for (int j = 0; j < sz(idxs); j++) {
				if (las < idxs[j][0]) {
					ort.push_back({las, idxs[j][0] - 1, orv});
					las = idxs[j][0];
				}
				orv |= (1 << idxs[j][1]);
			}
			if (las <= n - 1) {
				ort.push_back({las, n - 1, orv});
			}
			int j = 0;
			vector<pi> ans;
			for (int i = 0; i < sz(ors); i++) {
				while (j < sz(ort) && ort[j][2] < ors[i][2])
					j++;
				if (j < sz(ort) && ort[j][2] == ors[i][2]) {
					int l = max(ort[j][0], ors[i][0]);
					int r = min(ort[j][1], ors[i][1]);
					if (l <= r) {
						ans.push_back({l, r});
					}
				}
			}
			return ans;
		};
		auto andMatch = [&]() {
			vector<pi> idxs;
			for (int j = 0; j < m; j++) {
				if (((pfx2[i - 1] >> j) & 1) == 0)
					continue;
				if (nxt0[j] > i)
					idxs.push_back({nxt0[j], j});
			}
			sort(all(idxs));
			reverse(all(idxs));
			int las = n - 1;
			int andv = pfx2[i - 1];
			vector<array<int, 3>> ors, ort;
			for (int i = 0; i < sz(idxs); i++) {
				if (idxs[i][0] <= las) {
					ors.push_back({idxs[i][0], las, andv});
					las = idxs[i][0] - 1;
				}
				andv ^= (1 << idxs[i][1]);
			}
			if (i <= las) {
				ors.push_back({i, las, andv});
			}
			idxs.clear();
			for (int j = 0; j < m; j++) {
				if (nxt2[i][j] < n) {
					idxs.push_back({nxt2[i][j], j});
				}
			}
			sort(all(idxs));
			las = i;
			andv = (1 << m) - 1;
			for (int j = 0; j < sz(idxs); j++) {
				if (las < idxs[j][0]) {
					ort.push_back({las, idxs[j][0] - 1, andv});
					las = idxs[j][0];
				}
				andv ^= (1 << idxs[j][1]);
			}
			if (las <= n - 1) {
				ort.push_back({las, n - 1, andv});
			}
			int j = 0;
			vector<pi> ans;
			for (int i = 0; i < sz(ors); i++) {
				while (j < sz(ort) && ort[j][2] > ors[i][2])
					j++;
				if (j < sz(ort) && ort[j][2] == ors[i][2]) {
					int l = max(ort[j][0], ors[i][0]);
					int r = min(ort[j][1], ors[i][1]);
					if (l <= r) {
						ans.push_back({l, r});
					}
				}
			}
			return ans;
		};
		auto a1 = orMatch();
		auto a2 = andMatch();
		vector<pi> v;
		int j = 0;
		for (int i = 0; i < sz(a1); i++) {
			while (j < sz(a2) && a2[j][1] < a1[i][0])
				j++;
			for (int k = j; k < sz(a2); k++) {
				if (a2[k][0] > a1[i][1])
					break;
				int l = max(a1[i][0], a2[k][0]);
				int r = min(a1[i][1], a2[k][1]);
				ans += max(r - l + 1, 0);
			}
		}
	}
	cout << ans << "\n";
}