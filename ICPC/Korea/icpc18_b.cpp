#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 505;
using pi = pair<int, int>;
#define sz(v) int((v).size())

int n, m;
int a[MAXN][MAXN], d[MAXN][MAXN], adj[MAXN][MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		for(int j=1; j<=n; j++){
			scanf("%d",&a[j][i]);
			if(a[j][i] == 0) a[j][i] = 1e9;
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int k=0; k<m; k++){
				if(a[i][k] < a[j][k]) d[i][j]++;
			}
		}
	}
	for(int i=1; i<=n; i++){
		adj[i][i] = 1e9;
		for(int j=1; j<=n; j++){
			if(d[i][j] > d[j][i]){
				adj[i][j] = d[i][j];
			}
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int k=1; k<=n; k++){
				adj[j][k] = max(adj[j][k], min(adj[j][i], adj[i][k]));
			}
		}
	}
	for(int i=1; i<=n; i++){
		bool ok = 1;
		for(int j=1; j<=n; j++){
			if(adj[i][j] < adj[j][i]) ok = 0;
		}
		if(ok) printf("%d ", i);
	}
}

