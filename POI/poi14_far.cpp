#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, a[500005], sz[500005];
vector<int> gph[500005];

void dfs(int x, int p){
	sz[x] = 1;
	for(auto &i : gph[x]){
		if(i == p) continue;
		dfs(i, x);
		sz[x] += sz[i];
	}
}

int solve(int x, int p){
	int ret = a[x];
	vector<pi> v;
	for(auto &i : gph[x]){
		if(i == p) continue;
		v.push_back({solve(i, x) + 1, 2 * sz[i]});
	}
	sort(v.begin(), v.end(), [&](const pi &a, const pi &b){
		return a.first - a.second > b.first - b.second;
	});
	int subsz = 0;
	for(auto &i : v){
		ret = max(ret, subsz + i.first);
		subsz += i.second;
	}
	return ret;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	cout << max(2*n-2+a[1], solve(1, 0));
}