#include <bits/stdc++.h>
using namespace std;
const int MAXN = 250005;
using lint = long long;
using pi = pair<int, int>;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

int n;
int get(int x, int y){ return x * n + y; }

vector<int> gph[MAXN];
int dist[MAXN];
int idx[MAXN];
int adj[105][105];
int num[105];
int dp[1005][105];

void bfs(int x){
	memset(dist, 0x3f, sizeof(dist));
	dist[x] = 0;
	queue<int> que;
	que.push(x);
	while(!que.empty()){
		int x = que.front(); que.pop();
		for(auto &y : gph[x]){
			if(dist[y] > dist[x] + 1){
				dist[y] = dist[x] + 1;
				que.push(y);
			}
		}
	}
}

int main(){
	scanf("%d",&n);
	assert(1 <= n && n <= 500);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			int v; scanf("%d",&v);
			assert(0 <= v && v <= 15);
			if(i == 0 && j == 0){
				assert((v & 8) == 0);
				v |= 8;
			}
			if(i == n - 1 && j == n - 1){
				assert((v & 2) == 0);
				v |= 2;
			}
			assert(0 <= v && v <= 15);
			for(int k=0; k<4; k++){
				int nx = i + dx[k];
				int ny = j + dy[k];
				if(0 <= nx && nx < n && 0 <= ny && ny < n){
					if((v >> k) & 1) continue;
					else{
						gph[get(i, j)].push_back(get(nx, ny));
					}
				}
				else{
					assert((v >> k) & 1);
				}
			}
		}
	}
	for(int i=0; i<n*n; i++){
		sort(gph[i].begin(), gph[i].end());
	}
	for(int i=0; i<n*n; i++){
		for(auto &j : gph[i]){
			assert(binary_search(gph[j].begin(), gph[j].end(), i));
		}
	}
	int m; cin >> m;
	assert(1 <= m && m <= min(n * n, 100));
	for(int i=1; i<=m; i++){
		int x, y, c; 
		cin >> x >> y >> c;
		assert(1 <= x && x <= n);
		assert(1 <= y && y <= n);
		assert(1 <= c && c <= n * n);
		x--; y--;
		assert(!idx[get(x, y)]);
		num[i] = c;
		idx[get(x, y)] = i;
	}
	if(!idx[get(0, 0)]){
		idx[get(0, 0)] = m + 1;
	}
	if(!idx[get(n - 1, n - 1)]){
		idx[get(n - 1, n - 1)] = m + 2;
	}
	for(int j=0; j<n*n; j++){
		if(idx[j]){
			bfs(j);
			for(int k=0; k<n*n; k++){
				if(idx[k]){
					adj[idx[j]][idx[k]] = dist[k];
				}
			}
		}
	}
	int t; scanf("%d",&t);
	assert(1 <= t && t <= 1000);
	vector<int> v(t);
	for(auto &j : v){
		scanf("%d",&j);
		assert(1 <= j && j <= n * n);
		bool found = 0;
		for(int k=1; k<=m; k++){
			if(j == num[k]) found = 1;
		}
		assert(found);
	}
	for(int i=1; i<t; i++) assert(v[i-1] != v[i]);
	memset(dp, 0x3f, sizeof(dp));
	for(int k=1; k<=m; k++){
		if(num[k] == v[0]){
			dp[0][k] = adj[idx[get(0, 0)]][k];
		}
	}
	for(int i=1; i<t; i++){
		for(int j=1; j<=m; j++){
			if(num[j] != v[i]) continue;
			for(int k=1; k<=m; k++){
				dp[i][j] = min(dp[i][j], dp[i-1][k] + adj[k][j]);
			}
		}
	}
	int ret = 1e9;
	for(int k=1; k<=m; k++){
		if(num[k] == v.back()){
			ret = min(ret, dp[t - 1][k] + adj[idx[get(n - 1, n - 1)]][k]);
		}
	}
	assert(ret < 3e8);
	cout << ret + 2 << endl;
}
