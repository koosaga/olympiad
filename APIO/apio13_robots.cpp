#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef vector<int> vi;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

int n, w, h;
char s[505][505];

bool vis[505][505][4];
bool stk[505][505][4];
pi nxt[505][505][4];

inline bool unpassable(int x, int y){
	if(x < 0 || x >= w || y < 0 || y >= h) return 1;
	if(s[x][y] == 'x') return 1;
	return 0;
}

pi getnxt(int x, int y, int d){
	if(vis[x][y][d]) return nxt[x][y][d];
	vis[x][y][d] = 1;
	if(stk[x][y][d]) return nxt[x][y][d] = pi(-1, -1);
	stk[x][y][d] = 1;
	int nx = x + dx[d], ny = y + dy[d];
	if(unpassable(nx, ny)){
		nxt[x][y][d] = pi(x, y);
	}
	else if(s[nx][ny] == 'C'){
		nxt[x][y][d] = getnxt(nx, ny, (d+1)%4);
	}
	else if(s[nx][ny] == 'A'){
		nxt[x][y][d] = getnxt(nx, ny, (d+3)%4);
	}
	else{
		nxt[x][y][d] = getnxt(nx, ny, d);
	}
	stk[x][y][d] = 0;
	return nxt[x][y][d];
}

vector<int> gph[250005];

int dp[9][9][250005];
bool tv[250005];
priority_queue<pi, vector<pi>, greater<pi> > pq;

void spread(int s, int e){
	queue<int> cur, nxt;
	memset(tv, 0, sizeof(tv));
	vector<pi> v;
	int minv = 1e9;
	for(int i=0; i<w*h; i++){
		if(dp[s][e][i] > 1e8) continue;
		minv = min(minv, dp[s][e][i]);
		v.push_back(pi(dp[s][e][i], i));
	}
	sort(v.begin(), v.end());
	int pnt = 0, cst = minv;
	while(!cur.empty() || pnt < v.size()){
		if(cur.empty()) cst = v[pnt].first;
		while(pnt < v.size() && v[pnt].first == cst){
			if(tv[v[pnt].second]){
				pnt++; continue;
			}
			tv[v[pnt].second] = 1;
			cur.push(v[pnt].second);
			pnt++;
		}
		while(!cur.empty()){
			int x = cur.front();
			cur.pop();
			dp[s][e][x] = cst;
			for(auto &j : gph[x]){
				if(!tv[j]){
					tv[j] = 1;
					nxt.push(j);
				}
			}
		}
		cur = nxt;
		while(!nxt.empty()) nxt.pop();
		cst++;
	}
}

int main(){
	cin >> n >> h >> w;
	for(int i=0; i<w; i++){
		cin >> s[i];
		for(int j=0; j<h; j++){
			if(s[i][j] <= '9' && s[i][j] >= '1'){
				s[i][j]--;
			}
		}
	}
	for(int i=0; i<w; i++){
		for(int j=0; j<h; j++){
			for(int k=0; k<4; k++){
				if(unpassable(i, j)){
					nxt[i][j][k] = pi(-1, -1);
					vis[i][j][k] = 1;
					continue;
				}
				getnxt(i, j, k);
			}
		}
	}
	for(int i=0; i<w; i++){
		for(int j=0; j<h; j++){
			for(int k=0; k<4; k++){
				if(nxt[i][j][k] == pi(-1, -1) || nxt[i][j][k] == pi(i, j)) continue;
				int p = nxt[i][j][k].first * h + nxt[i][j][k].second;
				gph[i*h+j].push_back(p);
			}
		}
	}
	memset(dp, 0x3f, sizeof(dp));
	for(int i=0; i<w; i++){
		for(int j=0; j<h; j++){
			if(s[i][j] - '0' < n && s[i][j] - '0' >= 0){
				dp[s[i][j] - '0'][s[i][j] - '0'][i*h+j] = 0;
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j+i<n; j++){
			for(int k=j; k<j+i; k++){
				for(int l=0; l<w*h; l++){
					dp[j][j+i][l] = min(dp[j][j+i][l], dp[j][k][l] + dp[k+1][j+i][l]);
				}
			}
			spread(j, j+i);
		}
	}
	int ret = 1e9;
	for(int i=0; i<w*h; i++){
		ret = min(ret, dp[0][n-1][i]);
	}
	if(ret > 1e8) ret = -1;
	cout << ret;
}
