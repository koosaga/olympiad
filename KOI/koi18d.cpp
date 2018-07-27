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
const int MAXN = 300005;
const int mod = 1e9 + 7;

int n, m, k;
int a[MAXN], b[MAXN];
int r1, r2;
vector<int> g1[MAXN], g2[MAXN];
int s1[MAXN], e1[MAXN], s2[MAXN], e2[MAXN];
int d1[MAXN], d2[MAXN];

int piv;

void dfs1(int x){
	s1[x] = piv;
	if(x <= k){
		piv++;
	}
	for(auto &i : g1[x]){
		d1[i] = d1[x] + 1;
		dfs1(i);
	}
	e1[x] = piv;
}

void dfs2(int x){
	s2[x] = piv;
	if(x <= k){
		piv++;
	}
	for(auto &i : g2[x]){
		d2[i] = d2[x] + 1;
		dfs2(i);
	}
	e2[x] = piv;
}

struct disj{
	int pa[MAXN], sz[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
		fill(sz, sz + n + 1, 1);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	int getsz(int x){
		return sz[find(x)];
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		sz[p] += sz[q];
		pa[q] = p; return 1;
	}
}disj;

struct event{
	int ty, l, de, pos;
	bool operator<(const event &e)const{
		return pi(l, -de) < pi(e.l, -e.de);
	}
};

int idx1[MAXN], idx2[MAXN];
int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		if(a[i]) g1[a[i]].push_back(i);
		else r1 = i;
	}
	for(int i=1; i<=m; i++){
		scanf("%d",&b[i]);
		if(b[i]) g2[b[i]].push_back(i);
		else r2 = i;
	}
	dfs1(r1);
	piv = 0;
	dfs2(r2);
	disj.init(k);
	vector<event> ev;
	for(int i=1; i<=k; i++){
		idx1[i] = i;
		idx2[i] = i;
	}
	for(int i=k+1; i<=n; i++){
		ev.push_back({1, e1[i] - s1[i], d1[i], i});
	}
	for(int i=k+1; i<=m; i++){
		ev.push_back({2, e2[i] - s2[i], d2[i], i});
	}
	sort(ev.begin(), ev.end());
	for(int i=0; i<ev.size(); i++){
		if(ev[i].ty == 1){
			idx1[ev[i].pos] = idx1[g1[ev[i].pos][0]];
			for(auto &j : g1[ev[i].pos]){
				disj.uni(idx1[j], idx1[ev[i].pos]);
			}
			if(disj.getsz(idx1[ev[i].pos]) != ev[i].l){
				puts("NO");
				return 0;
			}
		}
		else{
			idx2[ev[i].pos] = idx2[g2[ev[i].pos][0]];
			for(auto &j : g2[ev[i].pos]){
				disj.uni(idx2[j], idx2[ev[i].pos]);
			}
			if(disj.getsz(idx2[ev[i].pos]) != ev[i].l){
				puts("NO");
				return 0;
			}
		}
	}
	puts("YES");
}
