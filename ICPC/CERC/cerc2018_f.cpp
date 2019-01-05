#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1000005;

int n;
int chk[MAXN];

struct pnt{
	int x, y, idx;
	bool operator<(const pnt &p)const{
		return pi(x, y) < pi(p.x, p.y);
	};
}a[MAXN];

lint ccw(pnt a, pnt b, pnt c){
	int dx1 = b.x - a.x;
	int dy1 = b.y - a.y;
	int dx2 = c.x - a.x;
	int dy2 = c.y - a.y;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

void solve(vector<pnt> h, vector<pnt> g){
	if(h.size() == 3){
		if(!g.empty()){
			for(auto &i : h) chk[i.idx] = 1;
		}
		return;
	}
	int curidx = 1e9;
	int pos = -1;
	for(int i=0; i<h.size(); i++){
		if(curidx > h[i].idx){
			curidx = h[i].idx;
			pos = i;
		}
	}
	rotate(h.begin(), h.begin() + pos, h.end());
	int fth = 0;
	if(h.size() % 2 == 0){
		fth = h.size() / 2;
	}
	else{
		if(h[h.size() / 2].idx < h[h.size() / 2 + 1].idx){
			fth = h.size() / 2;
		}
		else fth = h.size() / 2 + 1;
	}
	vector<pnt> L, R, Lg, Rg;
	for(int i=0; i<=fth; i++) L.push_back(h[i]);
	for(int i=fth; i<=h.size(); i++) R.push_back(h[i % h.size()]);
	for(auto &i : g){
		if(ccw(h[0], h[fth], i) > 0) Rg.push_back(i);
		else if(ccw(h[0], h[fth], i) < 0) Lg.push_back(i);
		else assert(0);
	}
	solve(L, Lg);
	solve(R, Rg);
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].x,&a[i].y);
		a[i].idx = i;
	}
	swap(a[0], *min_element(a, a + n));
	sort(a + 1, a + n, [&](const pnt &p, const pnt &q){
		return ccw(a[0], p, q) > 0;
	});
	vector<pnt> g, h;
	for(int i=0; i<n; i++){
		while(h.size() >= 2 && ccw(h[h.size()-2], h.back(), a[i]) <= 0){
			g.push_back(h.back());
			h.pop_back();
		}
		h.push_back(a[i]);
	}
	if(h.size() == n){
		printf("%d %d %d\n", 3, n - 2, n);
		return 0;
	}
	for(auto &i : g) chk[i.idx] = 1;
	solve(h, g);
	printf("%d %d %d\n", 4, n - (int)h.size(), (int)count(chk, chk + n, 1));
}
