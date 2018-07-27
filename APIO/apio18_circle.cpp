#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300005;
const int offs = 1e9 + 100;
using pi = pair<int, int>;

struct circ{
	int x, y, r, idx;
	bool operator<(const circ &c)const{
		return pi(x, y) < pi(c.x, c.y);
	}
}a[MAXN], orig_pos[MAXN];

int n, ans[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].r);
		a[i].x += offs;
		a[i].y += offs;
		a[i].idx = i + 1;
		orig_pos[i + 1] = a[i];
	}
	auto inter = [&](circ a, circ b){
		int dx = a.x - b.x;
		int dy = a.y - b.y;
		int dr = a.r + b.r;
		return 1ll * dx * dx + 1ll * dy * dy <= 1ll * dr * dr;
	};
	sort(a, a+n, [&](const circ &a, const circ &b){
		return pi(-a.r, a.idx) < pi(-b.r, b.idx);
	});
	for(int i=30; i; i--){
		int lb = (1 << (i - 1)), rb = (1 << i) - 1;
		vector<circ> v;
		for(int j=0; j<n; j++){
			if(!ans[a[j].idx] && a[j].r <= rb){
				v.push_back((circ){a[j].x >> i, a[j].y >> i, a[j].r, a[j].idx});
			}
		}
		sort(v.begin(), v.end());
		for(int j=0; j<n; j++){
			if(!ans[a[j].idx] && a[j].r <= rb && a[j].r >= lb){
				for(int k=-2; k<=2; k++){
					int px = (a[j].x >> i) + k;
					int py = (a[j].y >> i) - 2;
					auto itr = lower_bound(v.begin(), v.end(), (circ){px, py, -1, -1}) - v.begin();
					while(itr < v.size() && pi(v[itr].x, v[itr].y) <= pi(px, py + 4)){
						if(inter(orig_pos[v[itr].idx], a[j])){
							if(!ans[v[itr].idx]) ans[v[itr].idx] = a[j].idx;
						}
						itr++;
					}
				}
			}
		}
	}
	for(int i=1; i<=n; i++) printf("%d ", ans[i]);
}

