#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 100005;

vector<pi> gph[MAXN];
vector<lint> mergeCost[MAXN];
int piv;

void make_merge(int x, vector<lint> &w) {
	for (int i = 0; i < sz(gph[x]); i++) {
		make_merge(gph[x][i][1], w);
		if (i + 1 < sz(gph[x]))
			mergeCost[x].push_back(w[piv++]);
	}
}

struct node {
	lint val[2][2][2];
	node() {
		memset(val, 0x3f, sizeof(val));
		for (int a = 0; a < 2; a++) {
		    val[a][a][a] = 0;
		}
	}
	node promote(lint C) {
		node ret;
		memset(ret.val, 0x3f, sizeof(ret.val));
		for (int a = 0; a < 2; a++) {
			for (int b = 0; b < 2; b++) {
				for (int c = 0; c < 2; c++) {
					ret.val[a][b][c] = min(ret.val[a][b][c], val[a][b][c] + C);
					ret.val[a ^ 1][b][c] = min(ret.val[a ^ 1][b][c], val[a][b][c]);
				}
			}
		}
		return ret;
	}
	node merge(node &p, lint W) {
		node ret;
		memset(ret.val, 0x3f, sizeof(ret.val));
		for (int a = 0; a < 2; a++) {
			for (int b0 = 0; b0 < 2; b0++) {
				for (int c0 = 0; c0 < 2; c0++) {
					for (int b1 = 0; b1 < 2; b1++) {
						for (int c1 = 0; c1 < 2; c1++) {
							ret.val[a][b0][c1] = min(ret.val[a][b0][c1], val[a][b0][c0] + p.val[a][b1][c1] + (1 ^ c0 ^ b1) * W);
						}
					}
				}
			}
		}
		return ret;
	}
};

long long place_police(vector<int> P, vector<long long> C, vector<long long> W) {
	for (int i = 0; i < sz(P); i++) {
		gph[P[i]].push_back({C[i], i + 1});
	}
	make_merge(0, W);
	assert(piv == sz(W) - 1);
	int n = sz(P) + 1;
	vector<node> dp(n);
	for (int i = n - 1; i >= 0; i--) {
		if (sz(gph[i]) == 0) {
			continue;
		}
		vector<node> vect;
		for (auto &[w, j] : gph[i]) {
			vect.push_back(dp[j].promote(w));
		}
		dp[i] = vect[0];
		for (int j = 1; j < sz(vect); j++) {
			dp[i] = dp[i].merge(vect[j], mergeCost[i][j - 1]);
		}
	}
	lint ret = 1e18;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				ret = min(ret, dp[0].val[i][j][k] + (1 ^ j ^ k) * W.back());
			}
		}
	}
	return ret;
}