#include "jumps.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

vector<int> a, l, r;
int nxt[18][MAXN], mxt[18][MAXN];
pi dp[18][MAXN];

void init(int N, std::vector<int> H) {
	a = H;
	l.resize(N);
	r.resize(N);
	vector<int> stk;
	for(int i = 0; i < N; i++){
		while(sz(stk) && a[stk.back()] < a[i]) stk.pop_back();
		if(sz(stk)) l[i] = stk.back();
		else l[i] = i;
		stk.push_back(i);
	}
	stk.clear();
	for(int i = N-1; i >= 0; i--){
		while(sz(stk) && a[stk.back()] < a[i]) stk.pop_back();
		if(sz(stk)) r[i] = stk.back();
		else r[i] = i;
		stk.push_back(i);
		nxt[0][i] = l[i];
		mxt[0][i] = r[i];
		dp[0][i] = pi(l[i], r[i]);
	}
	for(int i = 1; i < 18; i++){
		for(int j = 0; j < N; j++){
			nxt[i][j] = nxt[i-1][nxt[i-1][j]];
			mxt[i][j] = mxt[i-1][mxt[i-1][j]];
			int L = dp[i-1][j].first, R = dp[i-1][j].second;
			dp[i][j].first = min(dp[i-1][L].first, dp[i-1][R].first);
			dp[i][j].second = max(dp[i-1][L].second, dp[i-1][R].second);
		}
	}
}

int fixed_start(int X, int C, int D){
	int maxp = D;
	for(int i = 17; i >= 0; i--){
		if(nxt[i][maxp] >= C) maxp = nxt[i][maxp];
	}
	int qr = a[maxp];
	int s = X, e = X;
	int ret = 0;
	for(int i = 17; i >= 0; i--){
		int ns = min(dp[i][s].first, dp[i][e].first);
		int ne = max(dp[i][s].second, dp[i][e].second);
		if(a[ns] <= qr && a[ne] <= qr && ne < C){
			s = ns;
			e = ne;
			ret += (1 << i);
		}
	}
	int l1 = 0, l2 = 0;
	for(int i = 17; i >= 0; i--){
		if(mxt[i][s] < C) s = mxt[i][s], l1 += (1<<i);
		if(mxt[i][e] < C) e = mxt[i][e], l2 += (1<<i);
	}
	int dap = 1e9;
	if(C <= r[s] && r[s] <= D) dap = min(dap, l1 + ret + 1);
	if(C <= r[e] && r[e] <= D) dap = min(dap, l2 + ret + 1);
	return dap;
}

int minimum_jumps(int A, int B, int C, int D) {
	int pos = B;
	int dap = 1e9;
	if(B + 1 < C){
		int maxp = C;
		for(int i = 17; i >= 0; i--){
			if(nxt[i][maxp] > B) maxp = nxt[i][maxp];
		}
		for(int i = 17; i >= 0; i--){
			if(a[nxt[i][pos]] < a[maxp] && nxt[i][pos] >= A) pos = nxt[i][pos];
		}
	}
	dap = min(dap, fixed_start(pos, C, D));
	if(l[pos] >= A) pos = l[pos];
	dap = min(dap, fixed_start(pos, C, D));
	if(dap >= sz(a)) dap = -1;
	return dap;
}
