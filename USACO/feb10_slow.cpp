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
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct seg{
	int tree[270000], lazy[270000];
	void lazydown(int p){
		tree[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
	}
	int query(int s, int e, int p, int x){
		if(s == e) return tree[x];
		int m = (s+e)/2;
		lazydown(x);
		if(p <= m) return query(s, m, p, 2*x);
		return query(m+1, e, p, 2*x+1);
	}
}seg;

vector<int> graph[100005];
int dfn[100005], size[100005], piv;

void dfs(int x, int p){
	dfn[x] = ++piv;
	size[x] = 1;
	for(auto &i : graph[x]){
		if(i != p) dfs(i, x), size[x] += size[i];
	}
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		graph[s].push_back(e);
		graph[e].push_back(s);
	}
	dfs(1, 0);
	for(int i=0; i<n; i++){
		int t;
		scanf("%d",&t);
		printf("%d\n",seg.query(1, n, dfn[t], 1));
		seg.add(dfn[t], dfn[t] + size[t] - 1, 1, n, 1, 1);
	}
}