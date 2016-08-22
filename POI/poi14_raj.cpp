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

struct seg{
	int tree[1050000], lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int s, int e, int x){
		s += lim;
		e += lim;
		while(s < e){
			if(s%2 == 1){
				tree[s] = max(tree[s], x);
				s++;
			}
			if(e%2 == 0){
				tree[e] = max(tree[e], x);
				e--;
			}
			s >>= 1;
			e >>= 1;
		}
		if(s == e) tree[s] = max(tree[s], x);
		return;
	}
	int query(int x){
		x += lim;
		int ret = 0;
		while(x){
			ret = max(ret, tree[x]);
			x >>= 1;
		}
		return ret;
	}
}seg;

int n, m;
vector<int> gph[500005];
int indeg[500005], topo[500005], rtop[500005];
queue<int> que;
int s[1000005], e[1000005];
int l[500005], r[500005];

int ret[500005];
int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d %d",&s[i],&e[i]);
		gph[s[i]].push_back(e[i]);
		indeg[e[i]]++;
	}
	for(int i=1; i<=n; i++){
		if(!indeg[i]) que.push(i);
	}
	int cnt = 0;
	while(!que.empty()){
		int x = que.front();
		que.pop();
		topo[x] = ++cnt;
		rtop[topo[x]] = x;
		for(int i=0; i<gph[x].size(); i++){
			indeg[gph[x][i]]--;
			if(indeg[gph[x][i]] == 0){
				que.push(gph[x][i]);
			}
		}
	}
	for(int i=1; i<=n; i++){
		int pos = rtop[i];
		for(int j=0; j<gph[pos].size(); j++){
			int nxt = topo[gph[pos][j]];
			l[nxt] = max(l[nxt], l[i] + 1);
		}
	}
	for(int i=n; i; i--){
		int pos = rtop[i];
		for(int j=0; j<gph[pos].size(); j++){
			int nxt = topo[gph[pos][j]];
			r[i] = max(r[i], r[nxt] + 1);
		}
	}
	seg.init(n);	
	for(int i=0; i<m; i++){
		seg.add(topo[s[i]]+1, topo[e[i]]-1, l[topo[s[i]]] + r[topo[e[i]]] + 1);
	}
	for(int i=1; i<=n; i++){
		l[i] = max(l[i], l[i-1]);
		r[n+1-i] = max(r[n+1-i], r[n+2-i]);
	}
	for(int i=1; i<=n; i++){
		ret[i] = max(seg.query(topo[i]), max(l[topo[i]-1], r[topo[i]+1]));
	}
	int *p = min_element(ret + 1, ret + n + 1);
	printf("%d %d\n", (int)(p - ret), *p);
}

