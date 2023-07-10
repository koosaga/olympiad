#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;

#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define rng(i, b, e) for (int i = (b); i <= (e); i++)
#define rep(i, k) rng(i, 0, k - 1)
#define gnr(i, e, b) for (int i = (e); i >= (b); i--)
#define per(i, k) gnr(i, k - 1, 0)
#define fi first
#define se second
#define pb push_back
#define vc vector
using vi = vector<int>;
using ll = long long;
using pll = pair<ll, ll>;
map<char, int> Map;
int cnt = 0;
int Num(char a) {
	if (Map.count(a)) {
		return Map[a];
	}
	Map[a] = ++cnt;
	return cnt;
}
int C[4][4], OC[4][4];
map<vi, int> W;
int Do(vi TP) {
	if (W.count(TP))
		return W[TP];
	int Z[3][3], Y[3][3];
	rep(i, 9) { Z[i / 3][i % 3] = TP[i]; }
	int st = TP[9];
	rep(i, 3) {
		if (Z[st][i]) {
			vi YY;
			rep(j, 3) rep(k, 3) Y[j][k] = Z[j][k];
			Y[st][i]--;
			rep(j, 3) rep(k, 3) YY.pb(Y[j][k]);
			YY.pb(i);
			if (!Do(YY)) {
				W[TP] = 1;
				return 1;
			}
		}
	}
	W[TP] = 0;
	return 0;
}
bool Win(int b, int e) {
	rng(i, 1, 3) rng(j, 1, 3) C[i][j] = OC[i][j];
	C[b][e]--;
	rng(i, 1, 3) C[i][i] %= 2;
	rng(i, 1, 3) {
		rng(j, i + 1, 3) {
			int t = min(C[i][j], C[j][i]);
			C[i][j] -= t, C[j][i] -= t;
		}
	}
	if (C[1][2] && C[2][3] && C[3][1]) {
		int t = (min({C[1][2], C[2][3], C[3][1]}) - 3) / 2 * 2;
		t = max(t, 0);
		C[1][2] -= t, C[2][3] -= t, C[3][1] -= t;
	}
	if (C[2][1] && C[3][2] && C[1][3]) {
		int t = (min({C[2][1], C[3][2], C[1][3]}) - 3) / 2 * 2;
		t = max(t, 0);
		C[2][1] -= t, C[3][2] -= t, C[1][3] -= t;
	}
	vi TP;
	rng(i, 1, 3) {
		rng(j, 1, 3) { TP.pb(C[i][j]); }
	}
	TP.pb(e - 1);
	return !Do(TP);
}
int main() {
	int n;
	scanf("%d", &n);
	rep(i, n) {
		char p[100];
		scanf("%s", p);
		int m = strlen(p);
		int b = Num(p[0]);
		int e = Num(p[m - 1]);
		C[b][e]++;
	}
	rng(i, 1, 3) rng(j, 1, 3) OC[i][j] = C[i][j];
	int res = 0;
	rng(i, 1, 3) {
		rng(j, 1, 3) {
			if (OC[i][j]) {
				if (Win(i, j)) {
					res += OC[i][j];
				}
			}
		}
	}
	printf("%d\n", res);
}