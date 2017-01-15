#include <bits/stdc++.h>
using namespace std;

int n, m;
char str[405][405];
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

bool vis[405][405], cyc;
int cnt;
bool instk[405][405];

void dfs(int x, int y, int d){
	if(x < 0 || y < 0 || x >= n || y >= m) return;
	if(vis[x][y]){
		if(instk[x][y]) cyc = 1;
		return;
	}
	vis[x][y] = 1;
	instk[x][y] = 1;
	cnt++;
	if(str[x][y] == 'N'){
		if(d == 1 || d == 2){
			for(int i=1; i<=2; i++){
				dfs(x + dx[i], y + dy[i], i);
			}
		}
		else{
			for(int i=0; i<=3; i+=3){
				dfs(x + dx[i], y + dy[i], i);
			}
		}
	}
	else{
		if(d == 0 || d == 1){
			for(int i=0; i<=1; i++){
				dfs(x + dx[i], y + dy[i], i);
			}
		}
		else{
			for(int i=2; i<=3; i++){
				dfs(x + dx[i], y + dy[i], i);
			}
		}
	}
	instk[x][y] = 0;
}

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++){
		cin >> str[i];
	}
	for(int i=0; i<n; i++){
		int ans[405];
		memset(ans, 0x3f, sizeof(ans));
		cyc = 0;
		cnt = 0;
		memset(vis, 0, sizeof(vis));
		for(int j=0; j<m; j++){
			dfs(i, j, 3);
			if(!cyc) ans[j] = min(ans[j], cnt);
		}
		cyc = 0;
		cnt = 0;
		memset(vis, 0, sizeof(vis));
		for(int j=m-1; j>=0; j--){
			dfs(i, j, 1);
			if(!cyc) ans[j] = min(ans[j], cnt);
		}
		for(int j=0; j<m; j++){
			if(ans[j] > 1e7) printf("-1");
			else printf("%d", ans[j] * 2);
			if(j != m-1) printf(" ");
			else puts("");
		}
	}
}

