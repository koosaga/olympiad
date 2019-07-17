#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 6005;

struct rect{
	int sx, ex, sy, ey, v;
};

struct event{
	int s, e, x, y;
};

int n;

pi solve(vector<rect> v){
	vector<int> vx, vy;
	for(auto &i : v){
		vy.push_back(i.sy);
		vy.push_back(i.ey + 1);
	}
	sort(vy.begin(), vy.end());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	vector<event> ev;
	for(auto &i : v){
		ev.push_back({i.sy, i.ey + 1, i.sx, +i.v});
		ev.push_back({i.sy, i.ey + 1, i.ex + 1, -i.v});
	}
	sort(ev.begin(), ev.end(), [&](const event &x, const event &y){
		return x.x < y.x;
	});
	int arr[MAXN] = {};
	pi dap(0, 0);
	for(int i=0; i+1<ev.size(); i++){
		int s = lower_bound(vy.begin(), vy.end(), ev[i].s) - vy.begin();
		int e = lower_bound(vy.begin(), vy.end(), ev[i].e) - vy.begin();
		for(int j=s; j<e; j++){
			arr[j] += ev[i].y;
		}
		for(int j=0; j<vy.size()-1; j++){
			if(arr[j] > 0){
				dap.first += 1ll * (vy[j + 1] - vy[j]) * (ev[i + 1].x - ev[i].x);
			}
			if(arr[j] < 0){
				dap.second += 1ll * (vy[j + 1] - vy[j]) * (ev[i + 1].x - ev[i].x);
			}
		}
	}
	return dap;
}

vector<rect> v[2];

void AddRect(int sx, int ex, int sy, int ey, char c, int p){
	auto D = [&](int p){
		if(p < 0) return (p - 1) / 2;
		return p / 2;
	};
	if(p < 0) p = 1;
	sx = D(sx); ex = D(ex); sy = D(sy); ey = D(ey);
	v[p].push_back({sx, ex, sy, ey, c == 'W' ? 1 : -1});
}

int main(){
	scanf("%*d %*d %d",&n);
	for(int i=0; i<n; i++){
		int x, y, r;
		char c[3];
		cin >> c >> x >> y >> r;
		int sx = x - y - r, ex = x - y + r;
		int sy = x + y - r, ey = x + y + r;
		AddRect(sx, ex, sy, ey, *c, (x + y - r) % 2);
		AddRect(sx + 1, ex - 1, sy + 1, ey - 1, *c, (x + y - r + 1) % 2);
	}
	auto p1 = solve(v[0]);
	auto p2 = solve(v[1]);
	printf("%lld %lld\n", p1.first + p2.first, p1.second + p2.second);
}
