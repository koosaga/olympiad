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

int n;

set<int> s;
vector<int> gph[100005];
vector<int> rev[100005];

int comp[100005], csz[100005], piv;
lint indeg[100005], outdeg[100005];
vector<int> dfn;

void dfs(int x){
	auto traverse = [&](int st, int ed){
		while(1){
			auto t = s.lower_bound(st);
			if(t == s.end() || *t > ed) break;
			int pos = *t;
			s.erase(pos);
			dfs(pos);
		}
	};
	if(gph[x].size() == 0){
		traverse(1, n);
		return;
	}
	traverse(1, gph[x][0] - 1);
	for(int i=1; i<gph[x].size(); i++){
		traverse(gph[x][i-1] + 1, gph[x][i] - 1);
	}
	traverse(gph[x].back() + 1, n);		
	dfn.push_back(x);
}

void rdfs(int x, int p){
	comp[x] = p;
	csz[p]++;
	auto traverse = [&](int st, int ed){
		while(1){
			auto t = s.lower_bound(st);
			if(t == s.end() || *t > ed) break;
			int pos = *t;
			s.erase(pos);
			rdfs(pos, p);
		}
	};
	if(rev[x].size() == 0){
		traverse(1, n);
		return;
	}
	traverse(1, rev[x][0] - 1);
	for(int i=1; i<rev[x].size(); i++){
		traverse(rev[x][i-1] + 1, rev[x][i] - 1);
	}
	traverse(rev[x].back() + 1, n);		
}

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		while(x--){
			int p;
			scanf("%d",&p);
			gph[p].push_back(i);
			rev[i].push_back(p);
		}
	}
	for(int i=1; i<=n; i++){
		s.insert(i);
		sort(gph[i].begin(), gph[i].end());
		sort(rev[i].begin(), rev[i].end());
	}
	for(int i=1; i<=n; i++){
		if(s.find(i) != s.end()){
			s.erase(i);
			dfs(i);
		}
	}
	reverse(dfn.begin(), dfn.end());
	for(int i=1; i<=n; i++) s.insert(i);
	for(int i=0; i<dfn.size(); i++){
		if(s.find(dfn[i]) != s.end()){
			s.erase(dfn[i]);
			rdfs(dfn[i], ++piv);
		}
	}
	for(int i=1; i<=piv; i++){
		indeg[i] = outdeg[i] = 1ll * (n - csz[i]) * csz[i];
	}
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			if(comp[i] != comp[j]){
				outdeg[comp[i]]--;
				indeg[comp[j]]--;
			}
		}
	}
	if(count(indeg + 1, indeg + piv + 1, 0) != 1){
		puts("0");
		return 0;
	}
	for(int i=1; i<=piv; i++){
		if(indeg[i] == 0){
			printf("%d ", csz[i]);
			for(int j=1; j<=n; j++){
				if(comp[j] == i) printf("%d ", j);
			}
		}
	}
}
