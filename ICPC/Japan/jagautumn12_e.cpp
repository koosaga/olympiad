#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> pi;

vector<pi> cont[26];

inline int map(char t){
	if(t <= 'z' && t >= 'a') return t - 'a';
	if(t <= 'Z' && t >= 'A') return t - 'A' + 26;
	return 10000;
}

int dp[51][51][51][51];
bool go[51][51][51][51];

int n, m;
char a[55][55];

int f(int sx, int sy, int ex, int ey){
//	fprintf(stderr,"%d %d %d %d\n",sx,sy,ex,ey);
	if(sx == ex && sy == ey) return 0;
	if(sx > ex || sy > ey) return -1e9;
	if(!go[ex][ey][sx][sy]) return -1e9;
	if(~dp[sx][sy][ex][ey]) return dp[sx][sy][ex][ey];
	int ret = 0;
	if(go[sx+1][sy][sx][sy]) ret = max(ret, f(sx+1, sy, ex, ey));
	if(go[sx][sy+1][sx][sy]) ret = max(ret, f(sx, sy+1, ex, ey));
	if(ex && go[ex][ey][ex-1][ey]) ret = max(ret, f(sx, sy, ex-1, ey));
	if(ey && go[ex][ey][ex][ey-1]) ret = max(ret, f(sx, sy, ex, ey-1));
	if(map(a[sx][sy]) + 26 == map(a[ex][ey])){
		int ret2 = 0;
		if(ex && go[sx+1][sy][sx][sy] && go[ex][ey][ex-1][ey]) ret2 = max(ret2, f(sx+1, sy, ex-1, ey));
		if(ex && go[sx][sy+1][sx][sy] && go[ex][ey][ex-1][ey]) ret2 = max(ret2, f(sx, sy+1, ex-1, ey));
		if(ey && go[sx+1][sy][sx][sy] && go[ex][ey][ex][ey-1]) ret2 = max(ret2, f(sx+1, sy, ex, ey-1));
		if(ey && go[sx][sy+1][sx][sy] && go[ex][ey][ex][ey-1]) ret2 = max(ret2, f(sx, sy+1, ex, ey-1));
		ret = max(ret, ret2+1);
	}
	if(0 <= map(a[sx][sy]) && map(a[sx][sy]) <= 25){
		for(auto &i : cont[map(a[sx][sy])]){
			if(go[i.first][i.second][sx][sy] && go[ex][ey][i.first][i.second]){
				if(ex == i.first && ey == i.second) continue;
				ret = max(ret, f(sx, sy, i.first, i.second) + f(i.first, i.second, ex, ey));
			}
		}
	}
	return dp[sx][sy][ex][ey] = ret;
}

void solve(){
	for(int i=0; i<n; i++){
		scanf("%s",a[i]);
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(map(a[i][j]) <= 51 && map(a[i][j]) >= 26){
				cont[map(a[i][j]) - 26].push_back(pi(i,j));
			}
			if(a[i][j] == '#') continue;
			go[i][j][i][j] = 1;
			for(int k=i; k>=0; k--){
				for(int l=j; l>=0; l--){
					if(a[k][l] != '#'){
						go[i][j][k][l] |= (go[i][j][k+1][l] | go[i][j][k][l+1]);
					}
				}
			}
		}
	}
	printf("%d\n",max(-1,f(0,0,n-1,m-1)));
}

int main(){
	while(1){
		memset(dp,-1,sizeof(dp));
		memset(go,0,sizeof(go));
		memset(a,0,sizeof(a));
		for(int i=0; i<26; i++) cont[i].clear();
		scanf("%d %d",&n,&m);
		if(n == 0 && m == 0) break;
		solve();
	}
}
