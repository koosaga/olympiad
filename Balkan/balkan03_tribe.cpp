#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n;
vector<int> gph[100005];

int ord[100005], dfn[100005], par[100005], piv;

void dfs(int x, int p){
	ord[++piv] = x;
	par[x] = p;
	for(auto &i : gph[x]){
		gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
		dfs(i, x);
	}
}

int retrieve(int *tcnt){
	for(int i=20; i; i--){
		if(tcnt[i]){
			tcnt[i-1] += tcnt[i] - 1;
		}
	}
	int ret = 1;
	for(int i=1; i<=20; i++){
		if(tcnt[i]) ret++;
	}
	return ret;
}

int dp[100005], pdp[100005];
int cnt[100005][25];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d%d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, -1);
	for(int i=n; i; i--){
		int p = ord[i];
		for(auto &j : gph[p]){
			cnt[p][dp[j]]++;
		}
		int tcnt[22] = {};
		for(int i=1; i<=20; i++){
			tcnt[i] = cnt[p][i];
		}
		dp[p] = retrieve(tcnt);
	}
	for(int i=2; i<=n; i++){
		int p = ord[i];
		int tcnt[22] = {};
		for(int j=1; j<=20; j++){
			tcnt[j] = cnt[par[p]][j];
		}
		tcnt[dp[p]]--;
		if(par[par[p]] != -1){
			tcnt[pdp[par[p]]]++;
		}
		pdp[p] = retrieve(tcnt);
	}
	int ret = 0;
	for(int i=1; i<=n; i++){
		int tcnt[22] = {};
		for(auto &j : gph[i]){
			tcnt[dp[j]]++;
		}
		if(par[i] != -1){
			tcnt[pdp[i]]++;
		}
		ret = max(ret, retrieve(tcnt));
	}
	cout << ret;
}