#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std; 
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 6005;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
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

struct edge{
	int s, e, x;
};

void solve(){
	vector<edge> v;
	int n, m;
	scanf("%d %d",&n,&m);
	vector<int> dist(n + 1);
	for(int i = 0; i < m; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		if(s > e) swap(s, e);
		if(s == 1) dist[e] = x;
		else v.push_back({s, e, x});
	}
	disj.init(2*n);
	printf("%d\n", n);
	for(auto &i : v){
		if(dist[i.s] + dist[i.e] == i.x){
			disj.uni(i.s, i.e + n);
			disj.uni(i.e, i.s + n);
		}
		else if(abs(dist[i.s] - dist[i.e]) == i.x){
			disj.uni(i.s, i.e);
			disj.uni(i.s + n, i.e + n);
		}
		else{
			puts("impossible");
			return;
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			if(dist[i] == dist[j]){
				disj.uni(i, j + n);
				disj.uni(j, i + n);
			}
		}
	}
	for(int i = 2; i <= n; i++){
		if(disj.find(i) == disj.find(i + n)){
			puts("impossible");
			return;
		}
		if(disj.find(i) != disj.find(2) && disj.find(i+n) != disj.find(2)){
			disj.uni(i, 2);
			disj.uni(i+n, 2+n);
		}
	}
	for(int i = 1; i <= n; i++){
		if(disj.find(i) == disj.find(2)) printf("%d ", dist[i]);
		else printf("%d ", -dist[i]);
	}
	puts("");
}

int main(){
	int t; scanf("%d",&t);
	while(t--) solve();
}
