#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1005;
const int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
const int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};

int n, a[MAXN][MAXN], vis[MAXN][MAXN];

bool ok(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < n;
}

vector<pi> dfn;

void dfs(int x, int y){
	dfn.emplace_back(x, y);
	vis[x][y] = 1;
	for(int i=0; i<8; i++){
		if(ok(x + dx[i], y + dy[i]) && !vis[x + dx[i]][y + dy[i]] && a[x + dx[i]][y + dy[i]] == a[x][y]){
			dfs(x + dx[i], y + dy[i]);
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			scanf("%d",&a[i][j]);
		}
	}
	int r1 = 0, r2 = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(!vis[i][j]){
				dfn.clear();
				dfs(i, j);
				bool flag1 = 0, flag2 = 0;
				for(auto &k : dfn){
					for(int d=0; d<8; d++){
						if(ok(k.first + dx[d], k.second + dy[d])){
							if(a[k.first + dx[d]][k.second + dy[d]] > a[i][j]) flag1 = 1;
							if(a[k.first + dx[d]][k.second + dy[d]] < a[i][j]) flag2 = 1;
						}
					}
				}
				if(!flag1) r1++;
				if(!flag2) r2++;
			}
		}
	}
	printf("%d %d\n", r1, r2);
}

