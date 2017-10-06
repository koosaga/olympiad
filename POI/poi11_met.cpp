#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m, q;
vector<int> own[300005];
int crit[300005];
int l[300005], r[300005], a[300005];
int s[300005], e[300005];

struct bit{
	lint tree[300005];
	void init(){
		memset(tree, 0, sizeof(tree));
	}
	void add(int x, int v){
		while(x <= m){
			tree[x] += v;
			x += x & -x;
		}
	}
	lint query(int x){
		lint ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}seg;

int main(){
	cin >> n >> m;
	for(int i=1; i<=m; i++){
		int x;
		scanf("%d",&x);
		own[x].push_back(i);
	}
	for(int i=1; i<=n; i++){
		scanf("%d",&crit[i]);
	}
	cin >> q;
	for(int i=1; i<=q; i++){
		scanf("%d %d %d",&l[i],&r[i],&a[i]);
	}
	for(int i=1; i<=n; i++){
		s[i] = 1, e[i] = q + 1;
	}
	while(1){
		seg.init();
		vector<pi> v;
		for(int i=1; i<=n; i++){
			if(s[i] != e[i]){
				v.push_back(pi((s[i] + e[i]) / 2, i));
			}
		}
		if(v.empty()) break;
		sort(v.begin(), v.end());
		int p = 0;
		for(int i=1; i<=q; i++){
			if(l[i] <= r[i]){
				seg.add(l[i], a[i]);
				seg.add(r[i] + 1, -a[i]);
			}
			else{
				seg.add(l[i], a[i]);
				seg.add(1, a[i]);
				seg.add(r[i] + 1, -a[i]);
			}
			while(p < v.size() && v[p].first == i){
				lint tmp = 0;
				for(auto &k : own[v[p].second]){
					tmp += seg.query(k);
					tmp = min(tmp, (lint)1e18);
				}
				if(tmp < crit[v[p].second]){
					s[v[p].second] = v[p].first + 1;
				}
				else{
					e[v[p].second] = v[p].first;
				}
				p++;
			}
		}
	}
	for(int i=1; i<=n; i++){
		if(s[i] > q) puts("NIE");
		else printf("%d\n", s[i]);
	}
}

