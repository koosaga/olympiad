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
using ll = long long;
using pll = pair<ll, ll>;

int n, d;
char p[810], q[810];
int oto[810], V[810], C[810][810], S[810];
void KMP(char *a, int m) {
	a[m] = 0;
	oto[0] = -1;
	rep(i, m) {
		int t = oto[i];
		while (t != -1 && a[i] != a[t])
			t = oto[t];
		oto[i + 1] = t + 1;
	}
	int pv = 0;
	rep(i, n) {
		V[i] = 0;
		while (pv != -1 && a[pv] != p[i])
			pv = oto[pv];
		pv++;
		if (pv == m) {
			V[i] = 1;
			pv = oto[pv];
		}
		S[i + 1] = S[i] + V[i];
	}
}
int main() {
	scanf("%s", p);
	n = strlen(p);
	gnr(i, n - 1, 0) {
		gnr(j, n - 1, 0) {
			if (i == j) {
				C[i][j] = n - i;
			} else {
				if (p[i] == p[j])
					C[i][j] = C[i + 1][j + 1] + 1;
				else
					C[i][j] = 0;
			}
		}
	}
	ll res = 0;
	rng(i, 0, n - 1) {
		rng(j, i, n - 1) {
			q[j - i] = p[j];
			int m = j - i + 1;
			q[m] = 0;
			KMP(q, m);
			rep(k, i) {
				if (C[k][j + 1] >= i - k) {
					int ed = j + i - k;
					if (ed + m < n) {
						res += S[n] - S[ed + m];
					}
					res += S[k];
				}
			}
		}
	}
	rng(i, 0, n - 1) {
		rng(j, i + 1, n - 1) { res += min(C[i][j], j - i); }
	}
	printf("%lld\n", res);
}
