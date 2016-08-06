#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int cnt[1000005], dep[1000005];
int n, q, k[1000005];
int dap[1000005];

bool cross(pi a, pi b, pi c){
	return 1ll * (a.second - b.second) * (c.first - b.first) >= 1ll * (b.second - c.second) * (b.first - a.first);
}

lint func(pi a, int x){
	return 1ll * a.first * x + a.second;
}

int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<q; i++) scanf("%d",&k[i]);
	cnt[0]++;
	for(int i=2; i<=n; i++){
		int x;
		scanf("%d",&x);
		dep[i] = dep[x] + 1;
		cnt[dep[i]]++;
	}
	int h = *max_element(dep, dep+n+1);
	for(int i=1; i<=h; i++){
		cnt[i] += cnt[i-1];
	}
	vector<pi> stk;
	for(int i=0; i<=h; i++){
		while(stk.size() >= 2 && cross(stk[stk.size()-2], stk.back(), {i, -cnt[i]})){
			stk.pop_back();
		}
		stk.push_back({i, -cnt[i]});
	}
	int p = 0;
	for(int i=1; i<=n; i++){
		while(p+1 < stk.size() && func(stk[p], i) < func(stk[p+1], i)) p++;
		dap[i] = 1 + (func(stk[p], i) + cnt[h] + i - 1) / i;
	}
	for(int i=0; i<q; i++) printf("%d ", dap[min(k[i], n)]);
}
