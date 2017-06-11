#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, k;
vector<int> gph[1000005];
int cnt[1000005];

int dfs(int x, int p){
	int mx = 0;
	for(auto &i : gph[x]){
		if(i == p) continue;
		int k = dfs(i, x);
		cnt[k]++;
		mx = max(mx, k);
	}
	if(mx > 0) cnt[mx]--;
	return mx + 1;
}

int dfs2(int x){
	queue<pi> que;
	que.push(pi(x, -1));
	int ret = -1;
	while(!que.empty()){
		int x = que.front().first;
		int p = que.front().second;
		que.pop();
		ret = x;
		for(auto &i : gph[x]){
			if(i != p) que.push(pi(i, x));
		}
	}
	return ret;
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	cnt[dfs(dfs2(1), -1)]++;
	int ans = 0;
	int tk = 2*k-1;
	for(int i=n; i; i--){
		while(tk > 0 && cnt[i]){
			ans += i;
			cnt[i]--;
			tk--;
		}
	}
	cout << ans;
}
