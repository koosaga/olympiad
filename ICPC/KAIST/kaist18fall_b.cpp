#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 300005;

vector<int> gph[MAXN], tpl;
vector<pi> ev[MAXN];
int deg[MAXN], l[MAXN], r[MAXN], rev[MAXN];

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%d %d",&l[i],&r[i]);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].emplace_back(e);
		deg[e]++;
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(!deg[i]) que.push(i);
	}
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		tpl.push_back(x);
		for(auto &i : gph[x]){
			deg[i]--;
			if(deg[i] == 0) que.push(i);
		}
	}
	if(*max_element(deg, deg + n + 1)){
		puts("-1");
		return 0;
	}
	for(auto &i : tpl){
		for(auto &j : gph[i]) l[j] = max(l[j], l[i] + 1);
	}
	reverse(tpl.begin(), tpl.end());
	for(auto &i : tpl){
		for(auto &j : gph[i]) r[i] = min(r[i], r[j] - 1);
	}
	for(int i=1; i<=n; i++){
		if(l[i] > r[i]){
			puts("-1");
			return 0;
		}
		ev[l[i]].emplace_back(r[i], i);
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	vector<int> v;
	for(int i=1; i<=n; i++){
		for(auto &j : ev[i]) pq.push(j);
		if(pq.empty() || pq.top().first < i){
		    puts("-1");
		    return 0;
		}
		v.push_back(pq.top().second);
		pq.pop();
	}
	for(auto &i : v) printf("%d\n", i);
}

