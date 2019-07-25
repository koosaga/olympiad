#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 24;
const int MAXT = 540000;

struct bit{
	lint tree[MAXT];
	void add(int x, lint v){
		while(x < MAXT){
			tree[x] = max(tree[x], v);
			x += x & -x;
		}
	}
	lint query(int x){
		lint ret = -1e18;
		while(x){
			ret = max(ret, tree[x]);
			x -= x & -x;
		}
		return ret;
	}
}bit;

int n, a[MAXN];

vector<pi> l, r;

void dfs(int s, int e, lint x, lint y, lint z, vector<pi> &v){
	if(s == e) v.push_back({y - x, z - y});
	else{
		dfs(s + 1, e, x + a[s], y, z, v);
		dfs(s + 1, e, x, y + a[s], z, v);
		dfs(s + 1, e, x, y, z + a[s], v);
	}
}

int main(){
	fill(bit.tree, bit.tree + MAXT, -1e18);
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i];
	dfs(0, n / 2, 0, 0, 0, l);
	dfs(n / 2, n, 0, 0, 0, r);
	for(auto &i : l){
		i.first *= -1;
		i.second *= -1;
	}
	sort(l.begin(), l.end());
	sort(r.begin(), r.end());
	vector<lint> vy;
	for(auto &i : l) vy.push_back(i.second);
	sort(vy.begin(), vy.end());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	lint ret = 1e18;
	int p = 0;
	for(auto &i : r){
		while(p < l.size() && l[p].first <= i.first){
			int pos = lower_bound(vy.begin(), vy.end(), l[p].second) - vy.begin();
			bit.add(pos + 1, l[p].first + l[p].second);
			p++;
		}
		int ypos = upper_bound(vy.begin(), vy.end(), i.second) - vy.begin();
		ret = min(ret, - bit.query(ypos) + i.first + i.second);
	}
	cout << ret << endl;
}
