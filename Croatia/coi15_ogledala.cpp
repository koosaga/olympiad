#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

struct node{
	lint l, r;
	bool operator<(const node &nd)const{
		return pi(r - l, -l) < pi(nd.r - nd.l, -nd.l);
	}
};

struct query{
	lint pos;
	lint cnt; // 1-indexed
	int idx;
	bool operator<(const query &q)const{
		return pi(pos, cnt) < pi(q.pos, q.cnt);
	};
};

lint findCount(lint cur, lint d, lint value){
	lint xm1s = 0, xm0s = 1;
	for(int i = 0; i < d; i++){
		lint nxm1s = 0;
		lint nxm0s = 0;
		if((cur - 1) / 2 == cur / 2){
			nxm1s = xm1s;
			nxm0s = xm1s + 2 * xm0s;
		}
		else{
			nxm1s = 2 * xm1s + xm0s;
			nxm0s = xm0s;
		}
		cur /= 2;	
		xm1s = nxm1s;
		xm0s = nxm0s;
	}
	lint ans = 0;
	if(cur == value) ans += xm0s;
	if(cur - 1 == value) ans += xm1s;
	if(cur / 2 == value) ans += xm0s;
	if((cur - 1) / 2 == value) ans += xm0s + xm1s;
	if((cur - 2) / 2 == value) ans += xm1s;
	return ans;
}

lint findIndex(lint s, lint e, int d, lint findValue, lint toFind){
	if(d == 0){
		if(e - s + 1 == 2){
			if(findValue == 1) return s + 1;
			return s;
		}
		return (s + e) / 2;
	}
	lint m = (s + e) / 2;
	lint lsum = findCount(m - s, d - 1, findValue);
	if(toFind >= lsum) return findIndex(m + 1, e, d - 1, findValue, toFind - lsum);
	return findIndex(s, m - 1, d - 1, findValue, toFind);
}

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lint m; cin >> m;
	int n, q; cin >> n >> q;
	vector<lint> a(n);
	for(int i = 0; i < n; i++) cin >> a[i];
	vector<lint> b(q);
	int ptr = 0; lint cur = n;
	for(int i = 0; i < q; i++){
		cin >> b[i];
		if(b[i] <= n) cout << a[b[i] - 1] << "\n", ptr++;
	}
	vector<node> v;
	if(a[0] > 1) v.push_back({1, a[0] - 1});
	for(int i = 0; i < n - 1; i++){
		if(a[i] + 1 < a[i + 1]){
			v.push_back({a[i] + 1, a[i + 1] - 1});
		}
	}
	if(a[n - 1] < m) v.push_back({a[n - 1] + 1, m});
	map<lint, lint> mp;
	for(auto &x : v) mp[x.r - x.l + 1]++;
	set<query> grp;
	while(sz(mp)){
		auto z = *mp.rbegin();
		mp.erase(--mp.end());
		lint nxt = cur + z.second;
		while(ptr < q){
			if(b[ptr] <= nxt){
				int s = sz(grp);
				grp.insert({z.first, b[ptr] - cur, s});
				ptr++;
			}
			else break;
		}
		if(z.first >= 3) mp[(z.first - 1) / 2] += z.second;
		if(z.first >= 2) mp[z.first / 2] += z.second;
		cur = nxt;
	}
	map<lint, lint> acc;
	vector<lint> ans(sz(grp));
	for(int i = 0; i < sz(v); i++){
		lint cur = v[i].r - v[i].l + 1;
		map<lint, lint> mp;
		lint xm1s = 0, xm0s = 1;
		auto solve = [&](lint V, lint K, int depth){
			if(V == 0) return;
			auto it = grp.lower_bound({V, acc[V] + 1, -1});
			while(it != grp.end() && it->pos == V && it->cnt <= acc[V] + K){
				//cout << "ans[" << it->idx << "] = findIndex(" << v[i].l << "," << v[i].r << "," << depth << "," << (it->cnt - acc[V]) - 1 << ");\n";
				ans[it->idx] = findIndex(v[i].l, v[i].r, depth, V, (it->cnt - acc[V]) - 1);
				it = grp.erase(it);
			}
			acc[V] += K;
		};
		for(int j = 0; cur > 0; j++){
			if(cur == 2){
				solve(cur, xm0s, j);
				solve(cur - 1, xm1s + xm0s, j);
				break;
			}
			solve(cur - 1, xm1s, j);
			solve(cur, xm0s, j);
			lint nxm1s = 0;
			lint nxm0s = 0;
			if((cur - 1) / 2 == cur / 2){
				nxm1s = xm1s;
				nxm0s = xm1s + 2 * xm0s;
			}
			else{
				nxm1s = 2 * xm1s + xm0s;
				nxm0s = xm0s;
			}
			cur /= 2;	
			xm1s = nxm1s;
			xm0s = nxm0s;
		}
	}
	for(auto &x : ans) cout << x << "\n";
}
