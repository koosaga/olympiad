#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
using pi = pair<int, int>;

int n;
int byhuman[MAXN], goal[MAXN];
bool vis[MAXN][MAXN];
vector<pi> gph[MAXN];

bool dfs(int x, int y){
	if(goal[x] && goal[y]) return 1;
	if(vis[x][y]) return 0;
	vis[x][y] = 1;
	for(auto &i : gph[x]){
		for(auto &j : gph[y]){
			if(i.first == j.first && dfs(i.second, j.second)) return 1;
		}
	}
	return 0;
}

int main(){
	int q1, q2, m;
	scanf("%d %d %*d %d %d",&n,&m,&q1,&q2);
	while(q1--){
		int x; scanf("%d",&x);
		byhuman[x] = 1;
	}
	while(q2--){
		int x; scanf("%d",&x);
		goal[x] = 1;
	}
	while(m--){
		int s, e, x;
		scanf("%d %d %d",&s,&x,&e);
		gph[s].emplace_back(x, e);
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			if(byhuman[i] != byhuman[j] && dfs(i, j)){
				puts("YES");
				return 0;
			}
		}
	}
	puts("NO");
}
