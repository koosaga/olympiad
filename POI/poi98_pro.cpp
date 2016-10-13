#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, sx[7005], ex[7005], sy[7005], ey[7005];

bool cross(int x, int y){
	int dx = min(ex[x], ex[y]) - max(sx[x], sx[y]);
	int dy = min(ey[x], ey[y]) - max(sy[x], sy[y]);
	if(dx < 0 || dy < 0) return 0;
	if(dx == 0 && dy == 0) return 0;
	return 1;
}

bool vis[7005];

void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(int i=0; i<n; i++){
		if(cross(x, i)) dfs(i);
	}
}

int main(){
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		for(int i=0; i<n; i++){
			cin >> sx[i] >> sy[i] >> ex[i] >> ey[i];
		}
		memset(vis, 0, sizeof(vis));
		int cnt = 0;
		for(int i=0; i<n; i++){
			if(!vis[i]){
				dfs(i);
				cnt++;
			}
		}
		printf("%d\n", cnt);
	}
}
