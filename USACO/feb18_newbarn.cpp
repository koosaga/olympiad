#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef pair<int, int> pi;
typedef long long lint;

pi fp[MAXN];
int comp[MAXN];
int dep[MAXN], par[17][MAXN];

int lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	int dx = dep[y] - dep[x];
	for(int i=0; i<17; i++){
		if((dx >> i) & 1) y = par[i][y];
	}
	for(int i=16; i>=0; i--){
		if(par[i][x] != par[i][y]){
			x = par[i][x];
			y = par[i][y];
		}
	}
	if(x != y) return par[0][x];
	return x;
}

int dist(int x, int y){
	return dep[x] + dep[y] - 2 * dep[lca(x, y)];
}

int main(){
	freopen("newbarn.in", "r", stdin);
	freopen("newbarn.out", "w", stdout);
	char buf[5];
	int n = 0, q;
	scanf("%d",&q);
	while(q--){
		int x;
		scanf("%s %d",buf,&x);
		if(*buf == 'B'){
			n++;
			if(x == -1){
				comp[n] = n;
				fp[n] = pi(n, n);
			}
			else{
				comp[n] = comp[x];
				par[0][n] = x;
				dep[n] = dep[x] + 1;
				for(int i=1; i<17; i++){
					par[i][n] = par[i-1][par[i-1][n]];
				}
				int p1 = fp[comp[n]].first;
				int p2 = fp[comp[n]].second;
				int cur = dist(p1, p2);
				int dnp1 = dist(n, p1);
				int dnp2 = dist(n, p2);
				if(cur < dnp1){
					cur = dnp1;
					fp[comp[n]] = pi(n, p1);
				}
				if(cur < dnp2){
					cur = dnp2;
					fp[comp[n]] = pi(n, p2);
				}
			}
		}
		else{
			int p1 = fp[comp[x]].first;
			int p2 = fp[comp[x]].second;
			printf("%d\n", max(dist(x, p1), dist(x, p2)));
		}
	}
}
