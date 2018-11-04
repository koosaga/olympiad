#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

vector<pi> gph[40005];

int n;
double d, ret;

double dfs(int x, int p){
	vector<double> lis;
	for(auto &i : gph[x]){
		if(i.second != p){
			lis.push_back(dfs(i.second, x) + i.first);
		}
	}
	if(lis.size() == 0) return 0;
	if(lis.size() == 1){
		ret += max(lis[0] - d, 0.0);
		return min(lis[0], d);
	}
	sort(lis.begin(), lis.end());
	reverse(lis.begin(), lis.end());
	if(lis[0] + lis[1] <= d) return lis[0];
	if(lis[1] * 2 <= d){
		double p = d - lis[1];
		ret += max(lis[0] - p, 0.0);
		return min(lis[0], p);
	}
	for(auto &i : lis){
		if(i > 0.5 * d){
			ret += i - 0.5 * d;
		}
	}
	return d * 0.5;
}

int main(){
	int t;
	cin >> t;
	while(t--){
		for(int i=1; i<=n; i++) gph[i].clear();
		cin >> n >> d;
		for(int i=0; i<n-1; i++){
			int s, e, x;
			scanf("%d %d %d",&s,&e,&x);
			gph[s].push_back({x, e});
			gph[e].push_back({x, s});
		}
		ret = 0;
		dfs(1, 0);
		printf("%.1f\n", ret);
	}
}
