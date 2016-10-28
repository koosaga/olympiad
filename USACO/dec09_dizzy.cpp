#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

vector<int> gph[100005];
int deg[100005];
int topo[100005], piv;

int n, m, q;

int main(){
	cin >> n >> m >> q;
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		deg[e]++;
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(!deg[i]) que.push(i);
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		topo[x] = ++piv;
		for(auto &i : gph[x]){
			deg[i]--;
			if(deg[i] == 0){
				que.push(i);
			}
		}
	}
	while(q--){
		int s, e;
		scanf("%d %d",&s,&e);
		if(topo[s] > topo[e]) swap(s, e);
		printf("%d %d\n", s, e);
	}
}
