#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using real_t = long double;
using pi = pair<int, int>;
const int MAXN = 105;
const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

string FUCK;

bool hasEdge2(int sx, int sy, int ex, int ey){
	if(FUCK == "R"){
		return sx == ex || sy == ey;
	}
	else if(FUCK == "Q"){
		return sx == ex || sy == ey || (sx - sy) == (ex - ey) || (sx + sy) == (ex + ey);
	}
	else if(FUCK == "B"){
		return (sx - sy) == (ex - ey) || (sx + sy) == (ex + ey);
	}
	else if(FUCK == "K"){
		return abs(sx - ex) <= 1 && abs(sy - ey) <= 1;
	}
	else if(FUCK == "N"){
		for(int i=0; i<8; i++){
			if(sx + dx[i] == ex && sy + dy[i] == ey) return true;
		}
		return false;
	}
};

vector<pi> gph[15][15];

int n, m, k, x, y;
int dist[1<<10][15][15];

struct node{
	int x, y, dist;
	bool operator<(const node &n)const{
		return dist > n.dist;
	}
};

pi a[22];
int main(){
	cin >> n >> m >> x >> y >> FUCK >> k;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			for(int k=0; k<n; k++){
				for(int l=0; l<m; l++){
					if(hasEdge2(i, j, k, l)) gph[i][j].emplace_back(k, l);
				}
			}
		}
	}
	x--, y--;
	memset(dist, 0x3f, sizeof(dist));
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			dist[0][i][j] = 1;
		}
	}
	for(int i=0; i<k; i++){
		cin >> a[i].first >> a[i].second;
		a[i].first--;
		a[i].second--;
		dist[1<<i][a[i].first][a[i].second] = 0;
	}
	for(int i=0; i<(1<<k); i++){
		for(int j=i; j; j=(j-1)&i){
			for(int x1 = 0; x1 < n; x1++){
				for(int y1 = 0; y1 < m; y1++){
					dist[i][x1][y1] = min(dist[i][x1][y1], dist[j][x1][y1] + dist[i ^ j][x1][y1]);
				}
			}
		}
		priority_queue<node> pq;
		for(int j=0; j<n; j++){
			for(int k=0; k<m; k++){
				pq.push({j, k, dist[i][j][k]});
			}
		}
		while(!pq.empty()){
			auto x = pq.top();
			pq.pop();
			if(dist[i][x.x][x.y] != x.dist) continue;
			int x1 = x.x, y1 = x.y;
			for(auto &fuck : gph[x1][y1]){
				int p, q; tie(p, q) = fuck;
				if(dist[i][p][q] > x.dist + 1){
					dist[i][p][q] = x.dist + 1;
					pq.push({p, q, x.dist + 1});
				}
			}
		}
	}
	if(dist[(1<<k) - 1][x][y] > 1e7) dist[(1<<k)-1][x][y] = -1;  
	cout << dist[(1<<k)-1][x][y] << endl;
}
