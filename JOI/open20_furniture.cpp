#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 1005;

int n, m, a[MAXN][MAXN];
int up[MAXN][MAXN], dn[MAXN][MAXN];
int L[MAXN], R[MAXN];

void dfs1(int x, int y){
	if(!dn[x][y]) return;
	dn[x][y] = 0;
	if(!dn[x + 1][y - 1]) dfs1(x, y - 1);
	if(!dn[x - 1][y + 1]) dfs1(x - 1, y);
}

void dfs2(int x, int y){
	if(!up[x][y]) return;
	up[x][y] = 0;
	if(!up[x - 1][y + 1]) dfs2(x, y + 1);
	if(!up[x + 1][y - 1]) dfs2(x + 1, y);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			scanf("%d",&a[i][j]);
			a[i][j] ^= 1;
		}
	}
	up[1][1] = dn[n][m] = 1;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(i + j == 2) continue;
			up[i][j] = ((up[i-1][j] | up[i][j-1]) & a[i][j]);
		}
	}
	for(int i=n; i; i--){
		for(int j=m; j; j--){
			if(i + j == n + m) continue;
			dn[i][j] = ((dn[i+1][j] | dn[i][j+1]) & a[i][j]);
		}
	}
	L[0] = R[0] = 1;
	for(int i=1; i<=n; i++){
		L[i] = L[i-1], R[i] = R[i-1];
		while(dn[i][L[i]] == 0) L[i]++;
		while(dn[i][R[i] + 1] == 1) R[i]++;
	}
	auto cL = [&](int x, int y){
		if(x == n) return L[x] <= y;
		else return L[x] <= y && y <= L[x + 1];
	};
	auto cR = [&](int x, int y){
		if(x == 1) return y <= R[x];
		else return R[x - 1] <= y && y <= R[x];
	};
	int q; scanf("%d",&q);
	while(q--){
		int x, y;
		scanf("%d %d",&x,&y);
		bool q1 = cL(x, y);
		bool q2 = cR(x, y);
		if(q1 && q2) puts("0");
		else{
			puts("1");
			a[x][y] = 0;
			dfs1(x, y);
			dfs2(x, y);
			if(q1){
				int start = y + 1;
				while(!(dn[x][start] && up[x - 1][start])) start++;
				L[x] = start;
				for(int i = x - 1; i >= 1; i--){
					int oL = L[i];
					L[i] = L[i + 1];
					while(up[i][L[i] - 1]) L[i]--;
					if(oL == L[i]) break;
				}
				for(int i = x + 1; i <= n; i++){
					int oL = L[i];
					L[i] = L[i - 1];
					while(!dn[i][L[i]]) L[i]++;
					if(oL == L[i]) break;
				}
			}
			if(q2){
				int start = y - 1;
				while(!(dn[x + 1][start] && up[x][start])) start--;
				R[x] = start;
				for(int i = x - 1; i >= 1; i--){
					int oR = R[i];
					R[i] = R[i + 1];
					while(!up[i][R[i]]) R[i]--;
					if(oR == R[i]) break;
				}
				for(int i = x + 1; i <= n; i++){
					int oR = R[i];
					R[i] = R[i - 1];
					while(dn[i][R[i] + 1]) R[i]++;
					if(oR == R[i]) break;
				}
			}
		}
	}
}
