#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3005;

int n, m;
int adj[MAXN][MAXN];
int chk[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	fill(chk + 1, chk + n + 1, 1);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		if(s > e) swap(s, e);
		adj[e][s] = 1;
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<i; j++){
			if(!adj[i][j] && chk[i] && chk[j]){
				chk[i] = chk[j] = 0;
			}
		}
	}
	for(int i=1; i<=n; i++) if(chk[i]) printf("%d ", i);
}
