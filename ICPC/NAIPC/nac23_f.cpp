#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define fi first
#define se second
using ll = long long;
using pll = pair<ll, ll>;
bool Do(pll A, pll B, pll C, pll D) {
	if (A.fi == B.fi + C.fi + D.fi && B.se == C.se && B.se == D.se && A.se + B.se == A.fi) {
		return true;
	}
	if (A.fi + B.fi == C.fi + D.fi && A.se == B.se && C.se == D.se && A.se + C.se == A.fi + B.fi) {
		return true;
	}
	if (A.fi == B.fi && A.fi == C.fi && A.fi == D.fi && A.fi == A.se + B.se + C.se + D.se)
		return true;
	if (A.fi == B.fi && C.se == D.se && A.se + B.se + C.se == A.fi)
		return true;
	if (B.se == C.se + D.se && C.fi == D.fi && B.fi + C.fi == A.fi && A.fi == A.se + B.se)
		return true;
	return false;
}
int main() {
	vector<pll> w(4);
	for (int i = 0; i < 4; i++) {
		scanf("%lld%lld", &w[i].fi, &w[i].se);
	}
	vector<int> Z(4);
	for (int i = 0; i < 4; i++)
		Z[i] = i;
	do {
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 4; j++) {
				if ((i >> j) & 1)
					swap(w[j].fi, w[j].se);
			}
			if (Do(w[Z[0]], w[Z[1]], w[Z[2]], w[Z[3]])) {
				puts("1");
				return 0;
			}
			for (int j = 0; j < 4; j++) {
				if ((i >> j) & 1)
					swap(w[j].fi, w[j].se);
			}
		}
	} while (next_permutation(all(Z)));

	puts("0");
}
