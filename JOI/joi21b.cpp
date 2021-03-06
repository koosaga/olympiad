#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 1000005;

int n, q;
lint a[MAXN], ret[MAXN];
vector<lint> query_stacks;
vector<lint> minval, maxval;

pi process(lint x){
	int s = 0, e = q;
	while(s != e){
		int m = (s + e + 1) / 2;
		if(maxval[m] - minval[m] <= x) s = m;
		else e = m - 1;
	}
	pi cur(maxval[e], -minval[e]);
	if(e < q){
		if(query_stacks[e + 1] - query_stacks[e] < 0){
			cur.second = x - cur.first;
		}
		else{
			cur.first = x - cur.second;
		}
	}
	return cur;
}

int main(){
	scanf("%d %d",&n,&q);
	for(int i = 1; i <= n; i++) scanf("%lld",&a[i]);
	query_stacks.push_back(0);
	minval.push_back(0);
	maxval.push_back(0);
	for(int i = 1; i <= q; i++){
		lint x; scanf("%lld",&x);
		x += query_stacks.back();
		query_stacks.push_back(x);
	}
	minval.resize(q + 1);
	maxval.resize(q + 1);
	for(int i = 1; i <= q; i++){
		minval[i] = min(minval[i - 1], query_stacks[i]);
		maxval[i] = max(maxval[i - 1], query_stacks[i]);
	}
	a[0] = -1e18;
	a[n + 1] = 1e18;
	for(int i = 1; i <= n + 1; i++){
		auto x = process(a[i] - a[i - 1]);
		ret[i - 1] += x.first;
		ret[i] += x.second;
	}
	for(int i = 1; i <= n; i++) printf("%lld\n", ret[i]); 
}
