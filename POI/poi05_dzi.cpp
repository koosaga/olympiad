#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
int mod;

struct disj{
	int pa[1000005];
	void init(int n){
		for(int i=1; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

bool in_diam[1000005];
vector<int> gph[1000005];
int n, m;
int par[1000005];
bool vis[1000005];

pi dfs(int x, int p){
	par[x] = p;
	vis[x] = 1;
	pi ret(0, x);
	for(auto &i : gph[x]){
		if(i == p) continue;
		auto t = dfs(i, x);
		t.first++;
		ret = max(ret, t);
	}
	return ret;
}

int main(){
	scanf("%d %d %d",&n,&m,&mod);
	disj.init(n);
	for(int i=0; i<m; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		if(!disj.uni(x, y)){
			puts("0");
			return 0;
		}
		gph[x].push_back(y);
		gph[y].push_back(x);
	}
	int cnt1 = 0, cnt2 = 0;
	lint ret = 1;
	for(int i=1; i<=n; i++){
		if(vis[i]) continue;
		if(gph[i].size() == 0) cnt1++;
		else{
			auto t = dfs(i, 0);
			auto u = dfs(t.second, 0);
			if(u.first > 2) ret *= 2, ret %= mod;
			for(int i=u.second; i; i=par[i]){
				in_diam[i] = 1;
			}
			for(int i=u.second; i; i=par[i]){
				int cnt = 0;
				for(auto &j : gph[i]){
					if(gph[j].size() != 1 && !in_diam[j]){
						puts("0");
						return 0;
					}
					if(gph[j].size() == 1) cnt++;
				}
				for(int j=1; j<=cnt; j++){
					ret *= j;
					ret %= mod;
				}
			}
			cnt2++;
		}
	}
	for(int i=1; i<=cnt2; i++){
		ret *= 2;
		ret *= i;
		ret %= mod;
	}
	for(int i=n-cnt1+1; i<=n; i++){
		ret *= i+1;
		ret %= mod;
	}
	ret %= mod;
	cout << ret;
}

