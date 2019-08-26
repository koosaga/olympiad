#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define dec fuck
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

struct point{
	int x, y, idx;
	bool operator<(const point &p)const{
		return x < p.x;
	}
}a[4][MAXN], inp[MAXN];

struct window{
	point p[4];
};

int n;
bool vis[MAXN];

vector<point> inc, dec;
vector<window> windows;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&inp[i].x,&inp[i].y);
		inp[i].idx = i;
		a[0][i] = a[1][i] = a[2][i] = a[3][i] = inp[i];
	}
	sort(a[0], a[0] + n, [&](point &a, point &b){ return a.x < b.x; });
	sort(a[1], a[1] + n, [&](point &a, point &b){ return a.y < b.y; });
	sort(a[2], a[2] + n, [&](point &a, point &b){ return a.x > b.x; });
	sort(a[3], a[3] + n, [&](point &a, point &b){ return a.y > b.y; });
	int p[4] = {};
	// windowing process
	while(sz(inc) + sz(dec) + 4 * sz(windows) < n){
		set<int> s;
		for(int i=0; i<4; i++){
			while(vis[a[i][p[i]].idx]) p[i]++;
			s.insert(a[i][p[i]].idx);
		}
		if(sz(s) == 1){
			int v = *s.begin();
			inc.push_back(inp[v]);
			vis[v] = 1;
		}
		if(sz(s) == 2){
			int v0 = *s.begin(), v1 = *s.rbegin();
			if(inp[v0].x > inp[v1].x) swap(v0, v1);
			if(inp[v0].y < inp[v1].y){
				inc.push_back(inp[v0]);
				inc.push_back(inp[v1]);
			}
			else{
				dec.push_back(inp[v0]);
				dec.push_back(inp[v1]);
			}
			vis[v0] = vis[v1] = 1;
		}
		if(sz(s) == 3){
			int sx = 1e9, ex = -1e9, sy = 1e9, ey = -1e9;
			for(int i=0; i<4; i++){
				sx = min(sx, a[i][p[i]].x);
				ex = max(ex, a[i][p[i]].x);
				sy = min(sy, a[i][p[i]].y);
				ey = max(ey, a[i][p[i]].y);
			}
			for(int i=0; i<4; i++){
				for(int j=0; j<i; j++){
					if(a[i][p[i]].idx == a[j][p[j]].idx){
						pi pos(a[i][p[i]].x, a[i][p[i]].y);
						int sidx = a[i][p[i]].idx;
						if(pos == pi(sx, sy) || pos == pi(ex, ey)) inc.push_back(inp[sidx]);
						else dec.push_back(inp[sidx]);
						vis[sidx] = 1;
					}
				}
			}
		}
		if(sz(s) == 4){
			window w;
			for(int i=0; i<4; i++){
				w.p[i] = a[i][p[i]];
				vis[w.p[i].idx] = 1;
			}
			windows.push_back(w);
		}
	}
	// chaining process
	sort(inc.begin(), inc.end());
	sort(dec.begin(), dec.end());
	assert(sz(inc) + sz(dec) >= 2); // to reduce the amount of pain in the world
	if(sz(inc) == 0){
		inc.push_back(dec.back());
		dec.pop_back();
	}
	if(sz(dec) == 0){
		dec.push_back(inc.back());
		inc.pop_back();
	}
	vector<pi> chain;
	chain.emplace_back(0, 0);
	bool up = (sz(inc) - 1) % 2;
	if(up) chain.emplace_back(inc[0].x, 0);
	else chain.emplace_back(0, inc[0].y);
	for(int i=0; i+1<sz(inc); i++){
		if(up) chain.emplace_back(inc[i].x, inc[i + 1].y);
		else chain.emplace_back(inc[i + 1].x, inc[i].y);
		up ^= 1;
	}
	assert(up == 0);
	chain.emplace_back(1e9 + 100, chain.back().second);
	chain.emplace_back(1e9 + 100, dec.back().y);
	for(int i=sz(dec)-1; i>0; i--){
		if(up) chain.emplace_back(dec[i].x, dec[i - 1].y);
		else chain.emplace_back(dec[i - 1].x, dec[i].y);
		up ^= 1;
	}
	if(up) chain.emplace_back(dec[0].x, 1e9 + 100);
	else chain.emplace_back(-1, dec[0].y);
	if(sz(windows)){
		reverse(windows.begin(), windows.end());
		if(up){
			chain.emplace_back(windows[0].p[0].x, 1e9 + 100);
		}
		else{
			chain.emplace_back(-1, windows[0].p[1].y);
		}
		if(up){
			for(auto &i : chain) swap(i.first, i.second);
			for(auto &i : windows){
				swap(i.p[0], i.p[1]);
				swap(i.p[2], i.p[3]);
				for(int j=0; j<4; j++){
					swap(i.p[j].x, i.p[j].y);
				}
			}
			for(auto &i : chain) i.first *= -1;
			for(auto &i : windows){
				for(int j=0; j<4; j++){
					i.p[j].x *= -1;
				}
				swap(i.p[0], i.p[2]);
			}
		}
		chain.emplace_back(windows[0].p[2].x, windows[0].p[1].y);
		chain.emplace_back(windows[0].p[2].x, windows[0].p[3].y);
		chain.emplace_back(windows[0].p[0].x, windows[0].p[3].y);
		for(int i=1; i<sz(windows); i++){
			chain.emplace_back(chain.back().first, windows[i].p[1].y);
			if(chain.back().first < windows[i].p[1].x){
				chain.emplace_back(windows[i].p[2].x, windows[i].p[1].y);
				chain.emplace_back(windows[i].p[2].x, windows[i].p[3].y);
				chain.emplace_back(windows[i].p[0].x, windows[i].p[3].y);
			}
			else{
				chain.emplace_back(windows[i].p[0].x, windows[i].p[1].y);
				chain.emplace_back(windows[i].p[0].x, windows[i].p[3].y);
				chain.emplace_back(windows[i].p[2].x, windows[i].p[3].y);
			}
		}
		chain.emplace_back(chain.back().first, -1);
		if(up){
			for(int i=0; i<3; i++){
				for(auto &i : chain) swap(i.first, i.second);
				for(auto &i : windows){
					swap(i.p[0], i.p[1]);
					swap(i.p[2], i.p[3]);
					for(int j=0; j<4; j++){
						swap(i.p[j].x, i.p[j].y);
					}
				}
				for(auto &i : chain) i.first *= -1;
				for(auto &i : windows){
					for(int j=0; j<4; j++){
						i.p[j].x *= -1;
					}
					swap(i.p[0], i.p[2]);
				}
			}
		}
	}
	printf("%d\n", sz(chain) - 1);
	for(int i=1; i<sz(chain); i++) printf("%d %d\n", chain[i].first, chain[i].second);
}
