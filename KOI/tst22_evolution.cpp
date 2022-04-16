#include <bits/stdc++.h>
#include "evolution.h"
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 500005;
 
int n;
vector<int> gph[MAXN];
int par[MAXN];
pi dp[MAXN];
 
struct sammax{
	pi a[3];
	void init(){
		fill(a, a + 3, pi(-1, -1));
	}
	void insert(pi v){
		for(int i = 0; i < 3; i++){
			if(v.second == a[i].second){
				a[i] = v;
				sort(a, a + 3);
				reverse(a, a + 3);
				return;
			}
		}
		for(int i = 0; i < 3; i++){
			if(a[i].first <= v.first){
				rotate(a+i, a+2, a+3);
				a[i] = v;
				return;
			}
		}
	}
	lint query(){
		return max({a[0].first, a[0].first + a[1].first + 1, a[1].first + a[2].first + 2});
	}
	lint ruery(){
		return max({a[0].first, a[1].first + 1});
	}
}subMax[MAXN];
 
void init(){
	n = 1;
	subMax[1].init();
}
 
int analyze(int R){
	return dp[R].second;
}
 
void observation(int P){
	gph[P].push_back(++n);
	int v = n;
	par[v] = P;
	dp[v] = pi(0, 0);
	subMax[v].init();
	while(v > 1){
		pi prv = dp[par[v]];
		dp[par[v]].second = max(dp[par[v]].second, dp[v].second);
		subMax[par[v]].insert(pi(dp[v].first, v));
		dp[par[v]].second = max(dp[par[v]].second, subMax[par[v]].query());
		dp[par[v]].first = max(dp[par[v]].first, subMax[par[v]].ruery());
		if(prv == dp[par[v]]) break;
		v = par[v];
	}
}

