#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 2505;
const int mod = 1e6;
int dy[4] = {0, 1, -1, 0}, dx[4] = {1, 0, 0, -1};
char str[6] = "ENSW";

int n, m, k;
pi a[MAXN], b[MAXN];
int cnt[64][64];
int dp[31][64][64];

int f(int s, int x, int y){
	if(s == k) return cnt[x][y];
	if(~dp[s][x][y]) return dp[s][x][y];
	int ret = 0;
	for(int i=0; i<4; i++){
		ret = max(ret, f(s+1, x + dx[i], y + dy[i]));
	}
	ret += cnt[x][y];
	return dp[s][x][y] = ret;
}

void trace(int s, int x, int y){
	if(s == k) return;
	for(int i=0; i<4; i++){
		if(f(s, x, y) == f(s+1, x + dx[i], y + dy[i]) + cnt[x][y]){
			putchar(str[i]);
			trace(s+1, x+dx[i], y+dy[i]);
			return;
		}
	}
}

int main(){
	memset(dp, -1, sizeof(dp));
	cin >> n >> m >> k;
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
	}
	for(int i=0; i<m; i++){
		cin >> b[i].first >> b[i].second;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			int dx = a[i].first - b[j].first;
			int dy = a[i].second - b[j].second;
			if(abs(dx) + abs(dy) <= k){
				cnt[-dx + 30][-dy + 30]++;
			}
		}
	}
	cout << f(0, 30, 30) << endl;
	trace(0, 30, 30);
}
