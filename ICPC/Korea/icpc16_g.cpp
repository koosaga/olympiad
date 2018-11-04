#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

char s[1005][1005];
bool vis[1005][1005];
int n, m;

int dfs(int x, int y){
	if(vis[x][y]) return 0;
	vis[x][y] = 1;
	if(x == n-1) return 1;
	for(int i=0; i<4; i++){
		if(x + dx[i] >= n || x + dx[i] < 0 || y + dy[i] >= m || y + dy[i] < 0 || 
				s[x+dx[i]][y+dy[i]] == '1') continue;
		if(dfs(x + dx[i], y + dy[i])){
			return 1;
		}
	}
	return 0;
}

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++) cin >> s[i];
	for(int i=0; i<m; i++){
		if(s[0][i] == '0' && dfs(0, i)){
			puts("YES");
			return 0;
		}
	}
	puts("NO");
}
