#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

vector<int> gph[200005], rev[200005];
vector<int> v;

int n, m, indeg[200005];
bool vis[200005];
int dp[200005];

void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto &i : gph[x]){
		indeg[i]++;
		dfs(i);
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		rev[e].push_back(s);
	}
	dfs(1);
	queue<int> que;
	que.push(1);
	int idx = 0;
	while(!que.empty()){
		int x = que.front();
		que.pop();
		v.push_back(x);
		for(auto &i : gph[x]){
			indeg[i]--;
			if(!indeg[i]) que.push(i);
		}
	}
	dp[1] = -1;
	vector<int> ans;
	ans.push_back(v[0]);
	for(int i=1; i<v.size(); i++){
		int y = 0, n = 0;
		set<int> s;
		for(auto &j : rev[v[i]]){
			if(!vis[j]) continue;
			if(dp[j] == -1) y++;
			else{
				s.insert(dp[j]);
				n++;
			}
		}
		if(y >= 2) dp[v[i]] = -1;
		else if(y == 1){
			if(n == 0) dp[v[i]] = v[i];
			else dp[v[i]] = -1;
		}
		else{
			if(s.size() == 1){
				dp[v[i]] = *s.begin();
			}
			else dp[v[i]] = -1;
		}
		if(dp[v[i]] == -1) ans.push_back(v[i]);
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for(auto &i : ans){
		printf("%d ", i);
	}
}
