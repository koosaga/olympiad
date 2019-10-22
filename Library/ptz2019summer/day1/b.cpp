#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

int n, p[MAXN], q[MAXN];

int solve(int m){
	vector<int> v;
	for(int i=1; i<=n; i++){
		if(q[i] > m) continue;
		if(sz(v) == 0 || v.back() < p[i]) v.push_back(p[i]);
		else *lower_bound(v.begin(), v.end(), p[i]) = p[i];
	}
	return sz(v);
}


void dnc(int s, int e, int l, int r){
	if(s > e) return;
	if(l == r){
		for(int i=s; i<=e; i++) printf("%d ", l);
		return;
	}
	int m = (s+e)/2;
	auto ans = solve(m);
	dnc(s, m - 1, l, ans);
	printf("%d ", ans);
	dnc(m + 1, e, ans, r);
}

int main(){
	int t; scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1; i<=n; i++) scanf("%d",&p[i]);
		for(int i=1; i<=n; i++){
			int t; scanf("%d",&t);
			q[t] = i;
		}
		dnc(1, n, 1, solve(n));
		puts("");
	}
}
