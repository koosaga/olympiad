#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
 
int n, m, x[200005], y[200005];
 
struct seg{
	struct node{
		bool adj[2][2];
	}tree[530000];  
	node merge(node a, node b){
		node r;
		for(int i=0; i<2; i++){
			for(int j=0; j<2; j++){
				r.adj[i][j] = 0;
				for(int k=0; k<2; k++){
					if(a.adj[i][k] && b.adj[k][j]) r.adj[i][j] = 1;
				}
			}
		}
		return r;
	}
	void set(int p, int v){
		tree[p].adj[0][0] = (x[v] <= x[v+1]);
		tree[p].adj[0][1] = (x[v] <= y[v+1]);
		tree[p].adj[1][0] = (y[v] <= x[v+1]);
		tree[p].adj[1][1] = (y[v] <= y[v+1]);
	}
	void init(int s, int e, int p){
		if(s == e){
			set(p, s);
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p);
		init(m+1, e, 2*p+1);
		tree[p] = merge(tree[2*p], tree[2*p+1]);
	}
	void update(int pos, int s, int e, int p){
		if(s == e){
			set(p, pos);
			return;
		}
		int m = (s+e)/2;
		if(pos <= m) update(pos, s, m, 2*p);
		else update(pos, m+1, e, 2*p+1);
		tree[p] = merge(tree[2*p], tree[2*p+1]);
	}
	bool query(){
		for(int i=0; i<2; i++){
			for(int j=0; j<2; j++){
				if(tree[1].adj[i][j]) return 1;
			}
		}
		return 0;
	}
}seg;
 
int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		scanf("%d %d",&x[i],&y[i]);
	}
	seg.init(1, n-1, 1);
	cin >> m;
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		swap(x[s], x[e]);
		swap(y[s], y[e]);
		if(s > e) swap(s, e);
		if(s > 1) seg.update(s-1, 1, n-1, 1);
		seg.update(s, 1, n-1, 1);
		seg.update(e-1, 1, n-1, 1);
		if(e < n) seg.update(e, 1, n-1, 1);
		puts(seg.query() ? "TAK" : "NIE");
	}
}