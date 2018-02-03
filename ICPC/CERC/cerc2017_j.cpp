#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;

int n;
vector<int> gph[MAXN];
int sub[MAXN], cnt[MAXN];

void dfs(int x, int p){
	sub[x] = 1;
	for(auto &i : gph[x]){
		if(i == p) continue;
		dfs(i, x);
		sub[x] += sub[i];
	}
	if(x != 1)cnt[sub[x]]++;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	vector<int> v;
	for(int i=1; i<n; i++){
		if(n % i == 0){
			int ans = 0;
			for(int j=i; j<=n; j+=i){
				ans += cnt[j];
			}
			if(ans == n / i - 1) v.push_back(n / i - 1);
		}
	}
	vector<int> ans = v;
	reverse(ans.begin(), ans.end());
	for(auto &i : ans) printf("%d ", i);
}
