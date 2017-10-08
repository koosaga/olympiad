#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int adj[22][22];
int d1[18][1<<18], d2[18][1<<18];
int n, m;

int f1(int x, int b){
	if(b == (1<<x)) return adj[x][n-2];
	if(~d1[x][b]) return d1[x][b];
	int ret = 1e9;
	for(int i=0; i<n-2; i++){
		if(x != i && (b >> i) % 2 == 1){
			ret = min(ret, adj[x][i] + f1(i, b^(1<<x)));
		}
	}
	return d1[x][b] = ret;
}

int f2(int x, int b){
	if(b == (1<<x)) return adj[x][n-1];
	if(~d2[x][b]) return d2[x][b];
	int ret = 1e9;
	for(int i=0; i<n-2; i++){
		if(x != i && (b >> i) % 2 == 1){
			ret = min(ret, adj[x][i] + f2(i, b^(1<<x)));
		}
	}
	return d2[x][b] = ret;
}

int main(){
	int p = 0;
	while(~scanf("%d %d",&n,&m)){
		memset(adj, 0x3f, sizeof(adj));
		memset(d1, -1, sizeof(d1));
		memset(d2, -1, sizeof(d2));
		for(int i=0; i<m; i++){
			int s, e, x;
			scanf("%d %d %d",&s,&e,&x);
			if(s == 0) s = n-2;
			else if(s == n-2) s = 0;
			if(e == 0) e = n-2;
			else if(e == n-2) e = 0;
			adj[s][e] = min(adj[s][e], x);
			adj[e][s] = min(adj[e][s], x);
		}
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
				}
			}
		}
		int ret = 0;
		if(n == 3){
			ret = 2 * (adj[1][0] + adj[0][2]);
		}
		else{
			ret = 1e9;
			for(int i=0; i<(1<<(n-2)); i++){
				int bcnt = 0;
				for(int j=0; j<n-2; j++){
					if((i >> j) & 1) bcnt++;
				}
				if(bcnt == n / 2 - 1){
					int lb = i, rb = (1<<(n-2)) - 1 - i;
					int forw = 1e9, backw = 1e9;
					for(int j=0; j<n-2; j++){
						for(int k=0; k<n-2; k++){
							if((lb >> j) % 2 == 1 && (rb >> k) % 2 == 1){
								forw = min(forw, f1(j, lb) + f2(k, rb) + adj[j][k]);
								backw = min(backw, f2(j, lb) + f1(k, rb) + adj[j][k]);
							}
						}
					}
					ret = min(ret, forw + backw);
				}
			}
		}
		printf("Case %d: %d\n", ++p, ret);
	}
}