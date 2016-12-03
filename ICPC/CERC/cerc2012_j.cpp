#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m;
vector<int> gph[100005];
int deg[100005], snap[100005], a[100005];

int solve(int x){
	queue<int> que[2];
	for(int i=1; i<=n; i++){
		if(deg[i] == 0){
			que[a[i]].push(i);
		}
	}
	if(que[x].empty()) return 1e9;
	int cnt = 0;
	while(!que[x].empty()){
		int y = que[x].front();
		que[x].pop();
		for(auto &i : gph[y]){
			deg[i]--;
			if(deg[i] == 0){
				que[a[i]].push(i);
			}
		}
		if(que[x].empty()){
			x ^= 1;
			if(!que[x].empty()) cnt++;
		}
	}
	return cnt;
}

int main(){
	int t;
	cin >> t;
	while(t--){
		scanf("%d %d",&n,&m);
		for(int i=1; i<=n; i++){
			scanf("%d",&a[i]);
			a[i]--;
		}
		for(int i=0; i<m; i++){
			int s, e;
			scanf("%d %d",&s,&e);
			gph[s].push_back(e);
			snap[e]++;
		}
		for(int i=1; i<=n; i++) deg[i] = snap[i];
		int ret = solve(0);
		for(int i=1; i<=n; i++) deg[i] = snap[i];
		ret = min(ret, solve(1));
		printf("%d\n",ret);
		for(int i=0; i<=n; i++){
			snap[i] = 0;
			gph[i].clear();
		}
	}
}