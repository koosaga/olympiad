#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
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

int n, k;

vector<int> graph[200005];
int root, in[200005], out[200005], dep[200005], piv;
int par[18][200005];

void dfs(int x){
	in[x] = ++piv;
	for(int i=1; i<=17; i++){
		par[i][x] = par[i-1][par[i-1][x]];
	}
	for(auto &i : graph[x]){
		dep[i] = dep[x] + 1;
		par[0][i] = x;
		dfs(i);
	}
	out[x] = ++piv;
}

int lca(int s, int e){
	if(dep[s] > dep[e]) swap(s, e);
	int dx = dep[e] - dep[s];
	for(int i=0; i<18; i++){
		if((dx >> i) & 1) e = par[i][e];
	}
	for(int i=17; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

bool inside(int r, int x){
	return in[r] <= in[x] && out[x] <= out[r];
}

vector<int> elems[100005];
vector<pi> sgraph[200005];

pi dfs2(int x, int p){
	pi ret(0, x);
	for(auto &i : sgraph[x]){
		if(i.second == p) continue;
		pi tmp = dfs2(i.second, x);
		tmp.first += i.first;
		ret = max(ret, tmp);
	}
	return ret;
}

stack<int> stk;

int solve(int x){
	for(auto &i : elems[x]){
		if(!stk.empty()){
			while(!inside(stk.top(), i)) stk.pop();
			sgraph[stk.top()].push_back(pi(dep[i] - dep[stk.top()], i));
			sgraph[i].push_back(pi(dep[i] - dep[stk.top()], stk.top()));
		}
		stk.push(i);
	}
	while(!stk.empty()) stk.pop();
	int pos = dfs2(elems[x][0], -1).second;
	pi ret = dfs2(pos, -1);
	printf("%d %d %d\n",ret.second, pos, dep[ret.second] + dep[pos] - 2 * dep[lca(ret.second, pos)]);
	for(auto &i : elems[x]){
		sgraph[i].clear();
	}
	return ret.first;
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		int t, x;
		scanf("%d %d",&t, &x);
		elems[t].push_back(i);
		if(x == 0) root = i;
		else graph[x].push_back(i);
	}
	dfs(root);
	for(int i=1; i<=k; i++){
		int sz = elems[i].size() - 1;
		sort(elems[i].begin(), elems[i].end(), [&](const int &a, const int &b){
			return in[a] < in[b];
		});
		for(int j=0; j<sz; j++){
			elems[i].push_back(lca(elems[i][j], elems[i][j+1]));
		}
		sort(elems[i].begin(), elems[i].end(), [&](const int &a, const int &b){
			return in[a] < in[b];
		});
		elems[i].resize(unique(elems[i].begin(), elems[i].end()) - elems[i].begin());
		printf("%d\n",solve(i));
	}
}