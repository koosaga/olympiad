#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
using lint = long long;

struct disj{
	int pa[5000005];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

set<int> s[55];
int chk[5000005];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
bool ok(int x, int y){
	return x >= 0 && x < 50 && y >= 0 && y < 100000;
}

int get(int x, int y){ return x * 100000 + y; }

void activate(int x, int y){
	chk[get(x, y)] = 1;
	for(int i=0; i<4; i++){
		if(ok(x + dx[i], y + dy[i])){
			int p = get(x + dx[i], y + dy[i]);
			if(chk[p]) disj.uni(get(x, y), p);
		}
	}
}
int main(){
	disj.init(5000000);
	for(int i=1; i<=50; i++){
		for(int j=1; j<=100000; j++) s[i-1].insert(j-1);
	}
	int q; scanf("%d",&q);
	while(q--){
		int t; scanf("%d",&t);
		int sx, sy; scanf("%d %d",&sx,&sy);
		int ex, ey; scanf("%d %d",&ex,&ey);
		sx--, sy--; ex--; ey--;
		if(t == 0){
			if(sx > ex) swap(sx, ex);
			if(sy > ey) swap(sy, ey);
			for(int i=sx; i<=ex; i++){
				auto l = s[i].lower_bound(sy);
				while(l != s[i].end() && *l <= ey){
					activate(i, *l);
					l = s[i].erase(l);
				}
			}
		}
		if(t == 1){
			int l = get(sx, sy);
			int r = get(ex, ey);
			if(chk[l] && chk[r] && disj.find(l) == disj.find(r)) puts("1");
			else puts("0");
		}
	}
}
