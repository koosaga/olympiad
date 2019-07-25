#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

int n, m;
vector<int> gph[MAXN];
pi a[MAXN];

int ord[MAXN], vis[MAXN], piv;
vector<int> stk;

void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto &i : gph[x]){
		dfs(i);
	}
	ord[x] = ++piv;
}

bool hasCycle(){
	for(int i=1; i<=n; i++){
		if(!vis[i]) dfs(i);
	}
	for(int i=0; i<m; i++){
		if(ord[a[i].first] < ord[a[i].second]) return 1;
	}
	return 0;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		a[i] = pi(s, e);
	}
	if(hasCycle()){
		puts("2");
		vector<int> v[2];
		for(int i=0; i<m; i++){
			if(a[i].first < a[i].second) v[0].push_back(i + 1);
			else v[1].push_back(i + 1);
		}
		for(int i=0; i<2; i++){
			printf("%d", v[i].size());
			for(auto &j : v[i]) printf(" %d", j);
			puts("");
		}
		return 0;
	}
	printf("1\n%d ", m);
	for(int i=1; i<=m; i++) printf("%d ", i);
	puts("");
}
