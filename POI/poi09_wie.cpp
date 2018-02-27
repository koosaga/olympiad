#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 205;

struct edg{
	int pos, cst, msk;
	bool operator<(const edg &e)const{
		return cst > e.cst;
	}
};

vector<edg> gph[MAXN];
int dist[MAXN][1<<13];
int n, p, swd[MAXN];
priority_queue<edg> pq;

int solve(){
	memset(dist, 0x3f, sizeof(dist));
	dist[1][swd[1]] = 0;
	pq.push({1, 0, swd[1]});
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dist[x.pos][x.msk] != x.cst) continue;
		for(auto &i : gph[x.pos]){
			if(i.msk & ~x.msk) continue;
			edg nxt = {i.pos, i.cst + x.cst, x.msk | swd[i.pos]};
			if(dist[nxt.pos][nxt.msk] > x.cst + i.cst){
				dist[nxt.pos][nxt.msk] = x.cst + i.cst;
				pq.push(nxt);
			}
		}
	}
	int w = *min_element(dist[n], dist[n] + 8192);
	if(w > 1e8) return -1;
	return w;
}

int main(){
	int m, k;
	scanf("%d %d %d %d",&n,&m,&p,&k);
	while(k--){
		int pos, cnt;
		scanf("%d %d",&pos,&cnt);
		while(cnt--){
			int x;
			scanf("%d",&x);
			swd[pos] |= (1 << (x-1));
		}
	}
	while(m--){
		int s, e, x, cnt, msk = 0;
		scanf("%d %d %d %d",&s,&e,&x,&cnt);
		while(cnt--){
			int x;
			scanf("%d",&x);
			msk |= (1 << (x-1));
		}
		gph[s].push_back({e, x, msk});
		gph[e].push_back({s, x, msk});
	}
	cout << solve() << endl;
}

