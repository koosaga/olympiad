#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct node{
	int adj[5][5];
	void init(){
		memset(adj, 0x3f, sizeof(adj));
	}
	void set(int s, int e, int x){
		adj[s][e] = min(adj[s][e], x);
	}
}tree[140000];

int k, n, m, q;

node merge(node l, node r){
	node x;
	x.init();
	for(int i=0; i<k; i++){
		for(int j=0; j<k; j++){
			for(int p=0; p<k; p++){
				x.adj[i][j] = min(x.adj[i][j], l.adj[i][p] + r.adj[p][j]);
			}
		}
	}
	return x;
}

void upd(int pos, int s, int e, int p, int ps, int pe, int px){
	if(s == e){
		tree[p].set(ps, pe, px);
		return;
	}
	int m = (s+e)/2;
	if(pos <= m) upd(pos, s, m, 2*p, ps, pe, px);
	else upd(pos, m+1, e, 2*p+1, ps, pe, px);
}

void init(int s, int e, int p){
	if(s == e) return;
	int m = (s+e)/2;
	init(s, m, 2*p);
	init(m+1, e, 2*p+1);
	tree[p] = merge(tree[2*p], tree[2*p+1]);
}

node query(int s, int e, int ps, int pe, int p){
	if(s <= ps && pe <= e) return tree[p];
	int pm = (ps+pe)/2;
	if(pm < s) return query(s, e, pm+1, pe, 2*p+1);
	if(e <= pm) return query(s, e, ps, pm, 2*p);
	return merge(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
}

int main(){
	scanf("%d %d %d %d",&k,&n,&m,&q);
	for(int i=0; i<140000; i++) tree[i].init();
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		upd(s / k, 0, (n-1)/k, 1, s%k, e%k, x); 
	}
	init(0, (n-1)/k, 1);
	while(q--){
		int s, e;
		scanf("%d %d",&s,&e);
		if(s/k >= e/k) puts("-1");
		else{
		auto l = query(s/k, e/k-1, 0, (n-1)/k, 1);
		if(l.adj[s%k][e%k] > 1e9) puts("-1");
		else printf("%d\n", l.adj[s%k][e%k]);
		}
	}
}
