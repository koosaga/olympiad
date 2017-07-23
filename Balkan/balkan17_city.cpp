#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct node{
	int pos, frm, dist;
	bool operator<(const node &n)const{
		return pi(dist, -frm) < pi(n.dist, -n.frm);
	}
};

priority_queue<node> pq;
vector<int> gph[300005];
queue<int> que;

int n, a[300005], par[300005];
int vis[300005];
pi ans[300005][2];

int nxt[300005], up[300005];
lint k;

int main(){
	scanf("%d %lld",&n,&k);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		pq.push({i, i, a[i]});
	}
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	while(!pq.empty()){
		int pos, frm, dis;
		pos = pq.top().pos;
		frm = pq.top().frm;
		dis = pq.top().dist;
		pq.pop();
		if(ans[pos][0].second == frm || ans[pos][1].second == frm || vis[pos] >= 2) continue;
		ans[pos][vis[pos]++] = pi(dis, frm);
		for(auto &i : gph[pos]){
			pq.push({i, frm, dis - 1});
		}
	}
	int pos = 1;
	for(int i=1; i<=n; i++){
		if(ans[i][0].second != i) nxt[i] = ans[i][0].second;
		else nxt[i] = ans[i][1].second;
	}
	while(true){
		if(k & 1) pos = nxt[pos];
		k >>= 1;
		if(!k) break;
		for(int j=1; j<=n; j++){
			up[j] = nxt[nxt[j]];
		}
		memcpy(nxt, up, sizeof(nxt));
	}
	printf("%d\n", pos);
}

