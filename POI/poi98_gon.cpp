#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 3005;

int n, m, A, B, piv;
vector<int> gph[MAXN];
int d1[MAXN], d2[MAXN], ic[MAXN];
int dfn[MAXN], low[MAXN];

void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(i != p){
			if(!dfn[i]){
				dfs(i, x);
				low[x] = min(low[x], low[i]);
			}
			else{
				low[x] = min(low[x], dfn[i]);
			}
		}
	}
	for(auto &i : gph[x]){
		if(i == p || low[i] > dfn[x]) continue;
		ic[x] = ic[i] = 1;
	}
}

void bfs(int x, int *d){
	queue<int> que;
	que.push(x);
	d[x] = 0;
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(auto &i : gph[x]){
			if(d[i] > d[x] + 1){
				d[i] = d[x] + 1;
				que.push(i);
			}
		}
	}
}

int tdfs(int x, int p){
	int ret = d2[x];
	for(auto &i : gph[x]){
		if(i != p && d1[i] < d2[i]){
			ret = max(ret, tdfs(i, x));
		}
	}
	return ret;
}

int main(){
	scanf("%d %d %d %d",&n,&m,&A,&B);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++){
		sort(gph[i].begin(), gph[i].end());
		gph[i].resize(unique(gph[i].begin(), gph[i].end()) - gph[i].begin());
	}
	memset(d1, 0x3f, sizeof(d1));
	memset(d2, 0x3f, sizeof(d2));
	dfs(1, -1);
	bfs(A, d1);
	bfs(B, d2);
	for(int i=1; i<=n; i++){
		if(d1[i] < d2[i] && ic[i]){
			puts("NIE");
			return 0;
		}
	}
	cout << tdfs(A, -1) << endl;
}

