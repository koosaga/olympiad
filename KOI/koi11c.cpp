#include <bits/stdc++.h>
typedef long long lint;
using namespace std;
typedef pair<int, int>pi;
const int MAXN = 300005;

int n, k;
vector<int> gph[MAXN];

pi dfs(int x, int p){
	vector<pi> v;
	for(auto &i : gph[x]){
		if(i == p) continue;
		v.push_back(dfs(i, x));
	}
	if(v.empty()) return pi(0, 1);
	sort(v.begin(), v.end(), [&](const pi &a, const pi &b){
		return a.second < b.second;
	});
	pi ret = v[0];
	for(int i=1; i<v.size(); i++){
		ret.first += v[i].first + 1;
	}
	ret.second++;
	if(ret.second > k){
		ret.first++;
		ret.second = 1;
	}
	if(v.size() >= 2 && v[0].second + v[1].second + 1 <= k){
		pi ret2(v[0].first + v[1].first, k);
		for(int i=2; i<v.size(); i++){
			ret2.first += v[i].first + 1;
		}
		ret = min(ret, ret2);
	}
	return ret;
}

int main(){
	scanf("%d %d",&n,&k);
	k++;
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	auto l = dfs(1, -1);
	cout << l.first + 1;
}
