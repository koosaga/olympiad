#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

int n, m;
set<int> s;
vector<int> gph[MAXN];
queue<int> que;

int bfs(int x){
	int ret = s.size();
	que.push(x);
	s.erase(x);
	while(!que.empty()){
		x = que.front();
		que.pop();
		for(int i=0; i+1<gph[x].size(); i++){
			int p = gph[x][i], q = gph[x][i+1];
			auto l = s.upper_bound(p);
			while(l != s.end() && *l < q){
				que.push(*l);
				l = s.erase(l);	
			}
		}
	}
	return ret - s.size();
}

int main(){
	scanf("%d %d",&n,&m);
	while(m--){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++){
		gph[i].push_back(0);
		gph[i].push_back(n+1);
		sort(gph[i].begin(), gph[i].end());
		s.insert(i);
	}
	vector<int> ans;
	for(int i=1; i<=n; i++){
		if(s.find(i) != s.end()) ans.push_back(bfs(i));
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for(auto &i : ans) printf("%d ", i);
}

