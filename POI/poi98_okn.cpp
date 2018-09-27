#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 5050;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n;
pi s, e, a[MAXN];

struct sweep{ int xs, xe, dx; };

vector<sweep> sw[MAXN / 2];
bool chk[MAXN / 2][MAXN / 2];
int dv[MAXN];
bool ok(int x, int y){
	return x >= 0 && x < e.first - s.first && y >= 0 && y < e.second - s.second && chk[x][y];
}

void dfs(int x, int y){
	chk[x][y] = 0;
	for(int i=0; i<4; i++){
		if(ok(x + dx[i], y + dy[i])){
			dfs(x + dx[i], y + dy[i]);
		}
	}
}

void add_sweep(int pos, int l, int r, int x){
	if(pos >= e.second) return;
	if(pos < s.second) pos = s.second;
	pos -= s.second;
	l = max(l, s.first);
	r = min(r, e.first);
	l -= s.first; r -= s.first;
	if(l < r){
		sw[pos].push_back({l, r, x});
	}
}

int main(){
	cin >> s.first >> e.second >> e.first >> s.second >> n;
	vector<int> vx = {s.first, e.first};
	vector<int> vy = {s.second, e.second};
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
		vx.push_back(a[i].first);
		vy.push_back(a[i].second);
	}
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	for(int i=0; i<n; i++){
		a[i].first = lower_bound(vx.begin(), vx.end(), a[i].first) - vx.begin();
		a[i].second = lower_bound(vy.begin(), vy.end(), a[i].second) - vy.begin();
	}
	s.first = lower_bound(vx.begin(), vx.end(), s.first) - vx.begin();
	e.first = lower_bound(vx.begin(), vx.end(), e.first) - vx.begin();
	s.second = lower_bound(vy.begin(), vy.end(), s.second) - vy.begin();
	e.second = lower_bound(vy.begin(), vy.end(), e.second) - vy.begin();
	a[n] = a[0];
	for(int i=0; i<n; i++){
		if(a[i].first < a[i+1].first){
			add_sweep(a[i].second, a[i].first, a[i+1].first, -1);
		}
		if(a[i].first > a[i+1].first){
			add_sweep(a[i].second, a[i+1].first, a[i].first, 1);
		}
	}
	swap(s.first, s.second);
	swap(e.first, e.second);
	for(int i=0; i<e.first-s.first; i++){
		for(auto &j : sw[i]){
			for(int k=j.xs; k<j.xe; k++){
				dv[k] += j.dx;
			}
		}
		for(int j=0; j<e.second - s.second; j++){
			if(dv[j]) chk[i][j] = 1;
		//	printf("%d",chk[i][j]);
		}
		//puts("");
	}
	int cnt = 0;
	for(int i=0; i<e.first-s.first; i++){
		for(int j=0; j<e.second-s.second; j++){
			if(chk[i][j]){
				dfs(i, j);
				cnt++;
			}
		}
	}
	cout << cnt << endl;
}
