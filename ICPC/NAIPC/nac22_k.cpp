#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 55;

int n, m;
bool term[MAXN];
int nxt[MAXN][52];
int dist[MAXN][MAXN][2][2];

struct node{
	int x, y, gd, ldone, dist;
	bool operator<(const node &nd)const{
		return dist > nd.dist;
	}
};

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int k;
	cin >> n >> k >> m;
	while(k--){
		int x; cin >> x;
		term[x] = 1;
	}
	auto idx = [&](char c){
		if(c <= 'Z' && c >= 'A') return c - 'A';
		return c - 'a' + 26;
	};
	for(int i = 0; i < m; i++){
		int u, v; string s; cin >> u >> s >> v;
		nxt[u][idx(s[0])] = v;
	}
	priority_queue<node> que;
	memset(dist, 0x3f, sizeof(dist));
	auto enq = [&](int x, int y, int g, int l, int d){
		if(dist[x][y][g][l] > d){
		//	cout << "attempt inque " << x << " " << y << " " << g << " " << l << " " << d << endl;
			dist[x][y][g][l] = d;
			que.push({x, y, g, l, d});
		}
	};
	enq(1, 1, 0, 0, 0);
	int ans = 1e9;
	while(sz(que)){
		auto nd = que.top();
		que.pop();
		int x = nd.x, y = nd.y, d = nd.dist;
		if(dist[x][y][nd.gd][nd.ldone] != d) continue;
	//	cout << x << " " << y << " " << nd.gd << " " << nd.ldone << " " << d << endl;
		if(nd.gd && term[x] && term[y]) ans = min(ans, d);
		for(int i = 0; i < 26; i++){
			if(nxt[x][i] && nxt[y][i]) enq(nxt[x][i], nxt[y][i], nd.gd, 0, d + 2);
		}
		if(nd.gd){
			for(int i = 26; i < 52; i++){
				if(!nd.ldone && nxt[x][i]) enq(nxt[x][i], y, nd.gd, nd.ldone, d + 1);
				if(nxt[y][i]) enq(x, nxt[y][i], nd.gd, nd.ldone, d + 1);
			}
		}
		if(nd.gd == 0 && !nd.ldone){	
			for(int i = 26; i < 52; i++){
				if(nxt[x][i] && nxt[y][i]) enq(nxt[x][i], nxt[y][i], nd.gd, 0, d + 2);
			}
			for(int i = 26; i < 52; i++){
				for(int j = 26; j < 52; j++){
					if(i != j && nxt[x][i] && nxt[y][j]){
						enq(nxt[x][i], nxt[y][j], 1, 0, d + 2);
					}
				}
				if(nxt[y][i]){
					// left is done to guarantee diffness
					enq(x, nxt[y][i], 1, 1, d + 1);
				}
			}
		}
	}
	if(ans > 1e8) ans = -1;
	cout << ans << "\n";
}
