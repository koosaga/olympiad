#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

struct qry{
	int pos, dis, idx;
};

int n, m, q;
vector<qry> query[5005];
vector<int> gph[5005];
bool chk[1000005];

int dis1[5005], dis2[5005];

void solve(int x){
	queue<int> que;
	que.push(x);
	memset(dis1, 0x3f, sizeof(dis1));
	memset(dis2, 0x3f, sizeof(dis2));
	dis1[x] = 0;
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(auto &i : gph[x]){
			if(dis1[i] > dis1[x] + 1){
				dis1[i] = dis1[x] + 1;
				que.push(i);
			}
			if(dis1[x] % 2 == dis1[i] % 2){
				dis2[x] = min(dis2[x], dis1[i] + 1);
				dis2[i] = min(dis2[i], dis1[x] + 1);
			}
		}
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i=1; i<=n; i++){
		if(dis2[i] < 1e9) pq.push(pi(dis2[i], i));
	}
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dis2[x.second] != x.first) continue;
		for(auto &i : gph[x.second]){
			if(dis2[i] > dis2[x.second] + 1){
				dis2[i] = dis2[x.second] + 1;
				pq.push(pi(dis2[i], i));
			}
		}
	}
	for(auto &i : query[x]){
		if(dis1[i.pos] % 2 == i.dis % 2){
			if(dis1[i.pos] <= i.dis) chk[i.idx] = 1;
		}
		else{
			if(dis2[i.pos] <= i.dis) chk[i.idx] = 1;
		}
	}
}

int main(){
	scanf("%d %d %d",&n,&m,&q);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=0; i<q; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		query[s].push_back((qry){e, x, i});
	}
	for(int i=1; i<=n; i++){
		if(!gph[i].empty() && !query[i].empty()){
			solve(i);
		}
	}
	for(int i=0; i<q; i++){
		puts(chk[i] ? "TAK" : "NIE");
	}
}
