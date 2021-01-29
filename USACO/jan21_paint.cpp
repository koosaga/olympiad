#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1055;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
const int dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};

int n, m, q;

int cnt[4][MAXN][MAXN];
bool dnt[4][MAXN][MAXN];
bool vis[MAXN][MAXN];
char str[MAXN][MAXN];
int ans[MAXN], sx[MAXN], ex[MAXN], sy[MAXN], ey[MAXN];
int minx, maxx, miny, maxy;

void dfs(int x, int y){
	vis[x][y] = 0;
	minx = min(minx, x);
	maxx = max(maxx, x + 1);
	miny = min(miny, y);
	maxy = max(maxy, y + 1);
	for(int i=0; i<8; i++){
		if(vis[x + dx[i]][y + dy[i]]){
			dfs(x + dx[i], y + dy[i]);
		}
	}
}

int dp1[64][MAXN];
int dp2[64][MAXN];
int dp3[64][MAXN];
int dp4[64][MAXN];
int wtf[64][1<<16];

int main(){
	scanf("%d %d %d",&n,&m,&q);
	for(int i = 1; i <= n; i++) scanf("%s", str[i] + 1);
	for(int i = 0; i < q; i++){
		scanf("%d %d %d %d",&sx[i],&sy[i],&ex[i],&ey[i]);
		dp1[i>>4][sx[i]] |= (1<<(i&15));
		dp2[i>>4][ex[i]] |= (1<<(i&15));
		dp3[i>>4][sy[i]] |= (1<<(i&15));
		dp4[i>>4][ey[i]] |= (1<<(i&15));
	}
	for(int i = 0; i < 64; i++){
		for(int j = 1; j <= n; j++) dp1[i][j] |= dp1[i][j-1];
		for(int j = n; j >= 0; j--) dp2[i][j] |= dp2[i][j+1];
		for(int j = 1; j <= m; j++) dp3[i][j] |= dp3[i][j-1];
		for(int j = m; j >= 0; j--) dp4[i][j] |= dp4[i][j+1];
	}
	for(int i = 'A'; i <= 'Z'; i++){
		memset(dnt, 0, sizeof(dnt));
		for(int j = 1; j <= n; j++){
			for(int k = 1; k <= m; k++){
				if(str[j][k] != i){
					dnt[0][j][k] = 1;
					dnt[0][j][k+1] = 1;
					dnt[0][j+1][k] = 1;
					dnt[0][j+1][k+1] = 1;
					dnt[1][j][k] = 1;
					dnt[1][j][k+1] = 1;
					dnt[2][j][k] = 1;
					dnt[2][j+1][k] = 1;
					dnt[3][j][k] = 1;
					vis[j][k] = 1;
				}
			}
		}
		for(int i = 0; i < 4; i++){
			for(int j = 0; j <= n + 1; j++){
				for(int k = 0; k <= m + 1; k++){
					cnt[i][j][k] += dnt[i][j][k];
					dnt[i][j][k] = 0;
				}
			}
		}
		for(int j = 1; j <= n; j++){
			for(int k = 1; k <= m; k++){
				if(vis[j][k]){
					minx = 1e9, miny = 1e9, maxx = -1e9, maxy = -1e9;
					dfs(j, k);
					for(int i = 0; i < q / 16 + 1; i++){
						int mask = dp1[i][minx - 1] & dp2[i][maxx] & dp3[i][miny - 1] & dp4[i][maxy];
						wtf[i][mask]++;
					}
				}
			}
		}
	}
	for(int i = 0; i < 4; i++){
		for(int j = 1; j <= n+1; j++){
			for(int k = 1; k <= m+1; k++){
				cnt[i][j][k] += cnt[i][j-1][k] + cnt[i][j][k-1] - cnt[i][j-1][k-1];
			}
		}
	}
	auto query_helper = [&](int idx, int sx, int ex, int sy, int ey){
		return cnt[idx][ex][ey] - cnt[idx][sx-1][ey] - cnt[idx][ex][sy-1] + cnt[idx][sx-1][sy-1];
	};
	for(int i = 0; i < q; i++){
		int ar = sx[i];
		int br = ex[i];
		int ac = sy[i];
		int bc = ey[i];
		int V = query_helper(0, ar + 1, br, ac + 1, bc);
		int E = query_helper(1, ar, br, ac + 1, bc) + query_helper(2, ar + 1, br, ac, bc);
		int F = query_helper(3, ar, br, ac, bc);
		ans[i] += 26 + E - V - F;
	}
	for(int i = 0; i < 64; i++){
		for(int j = 1; j < (1<<16); j++){
			if(!wtf[i][j]) continue; 
			for(int k = 0; k < 16; k++){
				if((j >> k) & 1){
					ans[i*16+k] += wtf[i][j];
				}
			}
		}
	}
	for(int i = 0; i < q; i++) printf("%d\n", ans[i]);
}
