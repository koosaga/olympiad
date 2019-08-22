#include "shoes.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		for(int i=x; i<MAXN; i+=i&-i) tree[i] += v;
	}
	int query(int x){
		int ret = 0;
		for(int i=x; i; i-=i&-i) ret += tree[i];
		return ret;
	}
}bit;


lint count_swaps(std::vector<int> s) {
	int n = sz(s) / 2;
	lint ret = 0;
	vector<pi> v;
	vector<pi> ord[MAXN];
	for(int i=0; i<sz(s); i++){
		ord[abs(s[i])].emplace_back(s[i], i);
	}
	for(int i=1; i<=n; i++){
		sort(ord[i].begin(), ord[i].end());
		for(int j=0; j<sz(ord[i])/2; j++){
			int l = ord[i][j].second;
			int r = ord[i][j + sz(ord[i])/2].second;
			if(l > r){
				swap(l, r);
				ret++;
			}
			v.emplace_back(l + 1, r + 1);
		}
	}
	for(int i=1; i<=2*n; i++) bit.add(i, 1);
	sort(v.begin(), v.end());
	for(auto &i : v){
		ret += bit.query(i.second - 1) - bit.query(i.first);
		bit.add(i.first, -1);
		bit.add(i.second, -1);
	}
	return ret;
}
