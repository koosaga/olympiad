#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, a[100005], indeg[100005];
int ret[100005];
vector<int> gph[100005];

void dfs(int x, int v){
	ret[x] = v;
	for(auto &i : gph[x]){
		dfs(i, v+1);
	}
}

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		indeg[a[i]]++;
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(!indeg[i]) que.push(i);
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		indeg[a[x]]--;
		gph[a[x]].push_back(x);
		if(indeg[a[x]] == 0){
			que.push(a[x]);
		}
	}
	for(int i=1; i<=n; i++){
		if(indeg[i]){
			vector<int> cnd;
			cnd.push_back(i);
			for(int j=a[i]; j!=i; j=a[j]){
				cnd.push_back(j);
			}
			for(auto &i : cnd){
				dfs(i, cnd.size());
			}
			for(auto &i : cnd){
				indeg[i] = 0;
			}
		}
	}
	for(int i=1; i<=n; i++){
		printf("%d\n", ret[i]);
	}
}
