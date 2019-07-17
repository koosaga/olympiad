#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 205;

vector<int> vx, vy;
int n, R[MAXN][MAXN], D[MAXN][MAXN];
pi x[MAXN], y[MAXN];

struct node{
	int x, y, v, dist;
	bool operator<(const node &n)const{
		return dist > n.dist;
	}
};

int dist[MAXN][MAXN][2];

int solve(int p, int q){
	priority_queue<node> pq;
	memset(dist, 0x3f, sizeof(dist));
	dist[p][q][0] = 0;
	pq.push({p, q, 0, 0});
	while(!pq.empty()){
		auto r = pq.top(); pq.pop();
		auto enq = [&](node n){
			if(dist[n.x][n.y][n.v] > n.dist){
				dist[n.x][n.y][n.v] = n.dist;
				pq.push(n);
			}
		};
		if(r.x + 1 < vx.size() && !D[r.x][r.y]){
			auto s = r;
			if(r.x == x[0].first && r.y <= x[0].second){
				s.v ^= 1;
			}
			s.dist += vx[r.x + 1] - vx[r.x];
			s.x++;
			enq(s);
		}
		if(r.x > 0 && !D[r.x - 1][r.y]){
			auto s = r;
			if(r.x - 1 == x[0].first && r.y <= x[0].second){
				s.v ^= 1;
			}
			s.dist += vx[r.x] - vx[r.x - 1];
			s.x--;
			enq(s);
		}
		if(r.y + 1 < vy.size() && !R[r.x][r.y]){
			auto s = r;
			s.dist += vy[r.y + 1] - vy[r.y];
			s.y++;
			enq(s);
		}
		if(r.y > 0 && !R[r.x][r.y - 1]){
			auto s = r;
			s.dist += vy[r.y] - vy[r.y - 1];
			s.y--;
			enq(s);
		}
	}
	return dist[p][q][1];
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> x[i].first >> x[i].second >> y[i].first >> y[i].second;
		vx.push_back(x[i].first);
		vx.push_back(y[i].first);
		vy.push_back(x[i].second);
		vy.push_back(y[i].second);
	}
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	for(int i=0; i<n; i++){
		x[i].first = lower_bound(vx.begin(), vx.end(), x[i].first) - vx.begin();
		y[i].first = lower_bound(vx.begin(), vx.end(), y[i].first) - vx.begin();
		x[i].second = lower_bound(vy.begin(), vy.end(), x[i].second) - vy.begin();
		y[i].second = lower_bound(vy.begin(), vy.end(), y[i].second) - vy.begin();
		int sx = x[i].first, ex = y[i].first;
		int sy = x[i].second, ey = y[i].second;
		for(int j=sx+1; j<ex; j++){
			for(int k=sy; k<ey; k++){
				R[j][k] = 1;
			}
		}
		for(int j=sx; j<ex; j++){
			for(int k=sy+1; k<ey; k++){
				D[j][k] = 1;
			}
		}	
	}
	int ret = 1e9;
	for(int i=0; i<vy.size(); i++) ret = min(ret, solve(x[0].first, i));
	cout << ret << endl;
}
