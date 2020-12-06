#include "labels.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;

const int MAXN = 1005;

vector<int> gph[MAXN];
int dep[MAXN];
int L[MAXN], piv;

void dfs(int x, int p = -1){
	if(dep[x] % 2 == 0) L[x] = piv++;
	for(auto &i : gph[x]){
		if(i == p) continue;
		dep[i] = dep[x] + 1;
		dfs(i, x);
	}
	if(dep[x] % 2 == 1) L[x] = piv++;
}

std::vector<int> label(int n, int k, std::vector<int> u, std::vector<int> v) {
	piv = 0;
	memset(L, 0, sizeof(L));
	for(int i=0; i<MAXN; i++) gph[i].clear();
	for(int i=0; i<n-1; i++){
		gph[u[i]].push_back(v[i]);
		gph[v[i]].push_back(u[i]);
	}
	dfs(0);
	std::vector<int> labels(L, L + n);
	return labels;
}