#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

int n, m;
set<int> gph[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].insert(e);
		gph[e].insert(s);
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(gph[i].size() == 2){
			que.push(i);
		}
	}
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		if(gph[x].size() != 2) continue;
		auto l = *gph[x].begin();
		auto r = *gph[x].rbegin();
		gph[l].erase(x);
		gph[r].erase(x);
		gph[l].insert(r);
		gph[r].insert(l);
		gph[x].clear();
		if(gph[l].size() == 2) que.push(l);
		if(gph[r].size() == 2) que.push(r);
	}
	int cnt = 0;
	for(int i=1; i<=n; i++){
		if(gph[i].size() > 2) cnt = 666;
		if(gph[i].size() == 1) cnt++;
	}
	puts(cnt == 2 ? "Yes" : "No");
}
