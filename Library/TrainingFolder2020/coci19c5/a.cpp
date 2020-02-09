#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 105;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n, m;
char str[MAXN][MAXN];

bool ok(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < m && str[x][y] == '*';
}

void dfs(int x, int y){
	str[x][y] = '.';
	for(int i=0; i<4; i++){
		if(ok(x + dx[i], y + dy[i])){
			dfs(x + dx[i], y + dy[i]);
		}
	}
}

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++) cin >> str[i];
	int cnt = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
		if(str[i][j] == '*'){
			dfs(i, j);
			cnt++;
		}
		}
	}
	cout << cnt << endl;
}
