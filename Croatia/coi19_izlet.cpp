#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
using lint = long long;

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

int n;
vector<int> gph[MAXN];
int adj[MAXN][MAXN];
vector<int> pth;

void dfs(int x, int p, int r){
	pth.push_back(x);
	if(x != r && adj[x][r] == adj[x][]){
		int s = 0, e = pth.size() - 1;
		while(s != e){
			int m = (s+e)/2;
			if(adj[pth[m]][p] == adj[pth[m]][x]) s = m + 1;
			else e = m;
		}
		assert(s > 0);
		disj.uni(pth[s - 1], x); 
	}
	for(auto &i : gph[x]){
		if(i != p) dfs(i, x, r);
	}
	pth.pop_back();
}

int main(){
	scanf("%*d");
	scanf("%d",&n);
	disj.init(n);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			scanf("%d",&adj[i][j]);
			if(adj[i][j] == 1){
				if(disj.uni(i, j)){
					gph[i].push_back(j);
					gph[j].push_back(i);
				}
			}
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(adj[i][j] == 2){
				if(disj.uni(i, j)){
					gph[i].push_back(j);
					gph[j].push_back(i);
				}
			}
		}
	}
	disj.init(n);
	for(int i=1; i<=n; i++){
		dfs(i, 0, i);
	}
	for(int i=1; i<=n; i++){
		printf("%d ", disj.find(i));
	}
	puts("");
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			if(i < j) printf("%d %d\n", i, j);
		}
	}
}
