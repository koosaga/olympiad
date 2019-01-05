#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

bool vis[202][202];
vector<pi> v0, v1;

void dfs0(int x, int y){
	if(max(x, y) > 200) return;
	if(vis[x][y]) return;
	vis[x][y] = 1;
	if(max(x, y) >= 25 && abs(x - y) >= 2){
		v0.emplace_back(x, y);
		return;
	}
	dfs0(x + 1, y);
	dfs0(x, y + 1);
}

void dfs1(int x, int y){
	if(max(x, y) > 200) return;
	if(vis[x][y]) return;
	vis[x][y] = 1;
	if(max(x, y) >= 15 && abs(x - y) >= 2){
		v1.emplace_back(x, y);
		return;
	}
	dfs1(x + 1, y);
	dfs1(x, y + 1);
}

void print(int x, int y, vector<pi> v){
	printf("%d:%d\n", x, y);
	for(auto &i : v) printf("%d:%d ", i.first, i.second);
	puts("");
}

int dp[4][4][202][202];
pi track[4][4][202][202];

int main(){
	dfs0(0, 0);
	memset(vis, 0, sizeof(vis));
	dfs1(0, 0);
	dp[0][0][0][0] = 1;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			for(int k=0; k<=200; k++){
				for(int l=0; l<=200; l++){
					for(auto &m : v0){
						if(m.first < m.second && j && k>=m.first && l>=m.second){
							if(dp[i][j-1][k-m.first][l-m.second]){
								dp[i][j][k][l] |= dp[i][j-1][k-m.first][l-m.second];
								track[i][j][k][l] = m;
							}
						}
						if(m.first > m.second && i && k>=m.first && l>=m.second){
							if(dp[i-1][j][k-m.first][l-m.second]){
								dp[i][j][k][l] |= dp[i-1][j][k-m.first][l-m.second];
								track[i][j][k][l] = m;
							}
						}
					}
				}
			}
		}
	}
	int tc; scanf("%d",&tc);
	while(tc--){
		int a, b; scanf("%d %d",&a,&b);
		bool ok = 0;
		{
			if(dp[3][0][a][b]){
				vector<pi> trace;
				for(int i=0; i<3; i++){
					trace.push_back(track[3-i][0][a][b]);
					a -= trace.back().first;
					b -= trace.back().second;
				}
				reverse(trace.begin(), trace.end());
				print(3, 0, trace);
				ok = 1;
			}
		}
		if(ok) continue;
		// try (3, 1)
		{
			for(auto &i : v0){
				if(i.first > i.second && a >= i.first && b >= i.second && dp[2][1][a-i.first][b-i.second]){
					vector<pi> trace;
					a -= i.first;
					b -= i.second;
					trace.push_back(i);
					int p1 = 2, p2 = 1;
					for(int i=0; i<3; i++){
						assert(dp[p1][p2][a][b]);
						trace.push_back(track[p1][p2][a][b]);
						a -= trace.back().first;
						b -= trace.back().second;
						if(trace.back().first < trace.back().second) p2--;
						else p1--;
					}
					reverse(trace.begin(), trace.end());
					print(3, 1, trace);
					ok = 1;
					break;
				}
			}
		}
		if(ok) continue;
		// try (3, 2)
		{
			for(auto &i : v1){
				if(i.first > i.second && a >= i.first && b >= i.second && dp[2][2][a-i.first][b-i.second]){
					vector<pi> trace;
					a -= i.first;
					b -= i.second;
					trace.push_back(i);
					int p1 = 2, p2 = 2;
					for(int i=0; i<4; i++){
						trace.push_back(track[p1][p2][a][b]);
						a -= trace.back().first;
						b -= trace.back().second;
						if(trace.back().first < trace.back().second) p2--;
						else p1--;
					}
					reverse(trace.begin(), trace.end());
					print(3, 2, trace);
					ok = 1;
					break;
				}
			}
		}
		if(ok) continue;
		// try (2, 3)
		{
			for(auto &i : v1){
				if(i.first < i.second && a >= i.first && b >= i.second && dp[2][2][a-i.first][b-i.second]){
					vector<pi> trace;
					a -= i.first;
					b -= i.second;
					trace.push_back(i);
					int p1 = 2, p2 = 2;
					for(int i=0; i<4; i++){
						trace.push_back(track[p1][p2][a][b]);
						a -= trace.back().first;
						b -= trace.back().second;
						if(trace.back().first < trace.back().second) p2--;
						else p1--;
					}
					reverse(trace.begin(), trace.end());
					print(2, 3, trace);
					ok = 1;
					break;
				}
			}
		}
		if(ok) continue;
		// try (1, 3)
		{
			for(auto &i : v0){
				if(i.first < i.second && a >= i.first && b >= i.second && dp[1][2][a-i.first][b-i.second]){
					vector<pi> trace;
					a -= i.first;
					b -= i.second;
					trace.push_back(i);
					int p1 = 1, p2 = 2;
					for(int i=0; i<3; i++){
						assert(dp[p1][p2][a][b]);
						trace.push_back(track[p1][p2][a][b]);
						a -= trace.back().first;
						b -= trace.back().second;
						if(trace.back().first < trace.back().second) p2--;
						else p1--;
					}
					reverse(trace.begin(), trace.end());
					print(1, 3, trace);
					ok = 1;
					break;
				}
			}
		}
		if(ok) continue;
		{
			if(dp[0][3][a][b]){
				vector<pi> trace;
				for(int i=0; i<3; i++){
					trace.push_back(track[0][3-i][a][b]);
					a -= trace.back().first;
					b -= trace.back().second;
				}
				reverse(trace.begin(), trace.end());
				print(0, 3, trace);
				ok = 1;
			}
		}
		if(ok) continue;
		puts("Impossible");
	}
}
