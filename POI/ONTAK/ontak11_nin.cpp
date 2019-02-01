#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500050;
const int mod = 1e9 + 7;
typedef long long lint;
typedef pair<int, int> pi;

struct pnt{
	int idx, x, y;
	bool operator<(const pnt &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
};

lint ccw(pnt a, pnt b, pnt c){
	int dx1 = b.x - a.x;
	int dy1 = b.y - a.y;
	int dx2 = c.x - a.x;
	int dy2 = c.y - a.y;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

int main(){
	int tc;
	scanf("%d",&tc);
	for(int i=0; i<tc; i++){
		int n; scanf("%d",&n);
		vector<pnt> v(n);
		for(int i=0; i<n; i++){
			scanf("%d %d",&v[i].x,&v[i].y);
			v[i].idx = i;
		}
		swap(v[0], *min_element(v.begin(), v.end()));
		sort(v.begin() + 1, v.end(), [&](const pnt &a, const pnt &b){
			return ccw(v[0], a, b) > 0;
		});
		vector<pnt> h;
		for(auto &i : v){
			while(h.size() >= 2 && ccw(h[h.size()-2], h.back(), i) <= 0) h.pop_back();
			h.push_back(i);
		}
		int chk[4] = {};
		int cnt = 0;
		for(auto &i : h){
			cnt++;
			if(i.idx <= 3) chk[i.idx] = cnt;
		}
		if(!chk[0] || !chk[1] || !chk[2] || !chk[3]){
			puts("TAK");
			continue;
		}
		int s = chk[0], e = chk[1];
		if(s > e) swap(s, e);
		int ans = 0;
		if(s < chk[2] && chk[2] < e) ans ^= 1;
		if(s < chk[3] && chk[3] < e) ans ^= 1;
		puts(ans == 0 ? "TAK" : "NIE");
	}
}
