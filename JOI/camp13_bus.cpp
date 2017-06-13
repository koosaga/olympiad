#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

struct edg{
	int nxt, cst;
	int idx, t, m;
};

struct node{
	int pos, cst, pidx;
	bool operator<(const node &n)const{
		return cst > n.cst;
	}
};

int up(int cur, int period, int mod){
	if(cur % period > mod) cur += period - cur % period;
	cur += mod - cur % period;
	return cur;
}

vector<edg> gph[1000005];
int n, m, k;
int vis[1000005][2];

priority_queue<node> pq;

int query(int s, int e){
	memset(vis, -1, sizeof(vis));
	pq.push({s, 0, 0});
	while(!pq.empty()){
		auto x = pq.top();
		if(x.pos == e) return x.cst;
		pq.pop();
		if(vis[x.pos][0] == -1){
			vis[x.pos][0] = x.pidx;
		}
		else{
			if(vis[x.pos][0] == x.pidx) continue;
			if(vis[x.pos][1] != -1) continue;
			vis[x.pos][1] = x.pidx;
		}
		for(auto &i : gph[x.pos]){
			if(i.idx != x.pidx){
				pq.push({i.nxt, up(x.cst + 1, i.t, i.m) + 1, i.idx});
			}
			else{
				pq.push({i.nxt, x.cst + 1, i.idx});
			}
		}
	}
	assert(0);
}


int get(int x, int y){
	return (x-1) * m + (y-1);
}

int main(){
	int sx, sy, ex, ey;
	scanf("%d %d %d %d %d %d %d",&n,&m,&sx,&sy,&ex,&ey,&k);
	int s = get(sx, sy);
	int e = get(ex, ey);
	for(int i=1; i<=k; i++){
		int x1, y1, x2, y2, t;
		scanf("%d %d %d %d %d",&x1,&y1,&x2,&y2,&t);
		int p = 2 * (x2 - x1 + y2 - y1);
		t = (p - t) % p;
		int px = x1, py = y1;
		for(int it=0; it<x2-x1; it++){
			gph[get(px, py)].push_back({
					get(px+1, py), 1, i, p, t});
			t = (t + 1) % p;
			px++;
		}
		for(int it=0; it<y2-y1; it++){
			gph[get(px, py)].push_back({
					get(px, py+1), 1, i, p, t});
			t = (t + 1) % p;
			py++;
		}
		for(int it=0; it<x2-x1; it++){
			gph[get(px, py)].push_back({
					get(px-1, py), 1, i, p, t});
			t = (t + 1) % p;
			px--;
		}
		for(int it=0; it<y2-y1; it++){
			gph[get(px, py)].push_back({
					get(px, py-1), 1, i, p, t});
			t = (t + 1) % p;
			py--;
		}
	}
	printf("%d\n", query(s, e));
}
