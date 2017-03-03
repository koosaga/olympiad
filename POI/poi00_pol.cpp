#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

vector<int> vx, vy;

pi a, b;
int n, sx[55], sy[55], ex[55], ey[55];
int arr[155][155];

struct node{
	int x, y, d, dis;
	bool operator<(const node &c)const{
		return dis > c.dis;
	}
};

int vis[155][155][2];
priority_queue<node> pq;

int bfs(pi a, pi b){
	if(arr[a.first][a.second] || arr[b.first][b.second]) return -1;
	pq.push({a.first, a.second, 0, 1});
	pq.push({a.first, a.second, 1, 1});
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(pi(x.x, x.y) == b){
			return x.dis;
		}
		if(vis[x.x][x.y][x.d]) continue;
		vis[x.x][x.y][x.d] = 1;
		if(x.x > 0 && !arr[x.x-1][x.y]){
			auto nxt = x;
			nxt.x--;
			if(nxt.d == 0) nxt.dis++;
			nxt.d = 1;
			pq.push(nxt);
		}
		if(x.x + 1 < vx.size() - 1&& !arr[x.x+1][x.y]){
			auto nxt = x;
			nxt.x++;
			if(nxt.d == 0) nxt.dis++;
			nxt.d = 1;
			pq.push(nxt);
		}
		if(x.y > 0 && !arr[x.x][x.y-1]){
			auto nxt = x;
			nxt.y--;
			if(nxt.d == 1) nxt.dis++;
			nxt.d = 0;
			pq.push(nxt);
		}
		if(x.y + 1 < vy.size() -1 && !arr[x.x][x.y+1]){
			auto nxt = x;
			nxt.y++;
			if(nxt.d == 1) nxt.dis++;
			nxt.d = 0;
			pq.push(nxt);
		}
	}
	return -1;
}

int main(){
	cin >> a.first >> a.second >> b.first >> b.second;
	vx.push_back(-5);
	vx.push_back(1e9 + 5);
	vy.push_back(-5);
	vy.push_back(1e9 + 5);
	vx.push_back(a.first);
	vx.push_back(a.first + 1);
	vx.push_back(b.first);
	vx.push_back(b.first + 1);
	vy.push_back(a.second);
	vy.push_back(a.second + 1);
	vy.push_back(b.second);
	vy.push_back(b.second + 1);
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> sx[i] >> sy[i] >> ex[i] >> ey[i];
		if(sx[i] > ex[i]) swap(sx[i], ex[i]);
		if(sy[i] > ey[i]) swap(sy[i], ey[i]);
		ex[i]++;
		ey[i]++;
		vx.push_back(sx[i]);
		vy.push_back(sy[i]);
		vx.push_back(ex[i]);
		vy.push_back(ey[i]);
	}
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	auto comp = [&](const vector<int> &v, int x){
		return lower_bound(v.begin(), v.end(), x) - v.begin();
	};
	a.first = comp(vx, a.first);
	a.second = comp(vy, a.second);
	b.first = comp(vx, b.first);
	b.second = comp(vy, b.second);
	for(int i=0; i<n; i++){
		sx[i] = comp(vx, sx[i]);
		sy[i] = comp(vy, sy[i]);
		ex[i] = comp(vx, ex[i]);
		ey[i] = comp(vy, ey[i]);
		arr[sx[i]][sy[i]]++;
		arr[ex[i]][sy[i]]--;
		arr[sx[i]][ey[i]]--;
		arr[ex[i]][ey[i]]++;
	}
	for(int i=1; i<vx.size(); i++){
		for(int j=1; j<vy.size(); j++){
			arr[i][j] += arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1];
		}
	}
	int x = bfs(a, b);
	if(x == -1) puts("BRAK");
	else cout << x;
}

