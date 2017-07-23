#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;
const int MAXN = 100005;

int n;
pi a[MAXN];
vector<pi> v, w;
vector<pi> gph[32 * MAXN];
int par[32 * MAXN], chk[32 * MAXN], sz[32 * MAXN];

pi upy(pi x){
	return *--lower_bound(v.begin(), v.end(), x);
}

pi upx(pi x){
	x = *--lower_bound(w.begin(), w.end(), pi(x.second, x.first));
	return pi(x.second, x.first);
}

pi dfs(int x, int p){
	pi ret(0, chk[x]);
	for(auto &i : gph[x]){
		if(i.first == p) continue;
		auto v = dfs(i.first, x);
		ret.first += v.first + i.second * v.second;
		ret.second += v.second;
	}
	return ret;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%lld %lld",&a[i].first,&a[i].second);
		int x = a[i].first, y = a[i].second;
		v.push_back(a[i]);
		while(x && y){
			int lsb1 = x & -x;
			int lsb2 = y & -y;
			if(lsb1 <= lsb2) x -= lsb1;
			else y -= lsb2;
			v.push_back(pi(x, y));
		}
		v.push_back(pi(0, 0));
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	w = v;
	for(auto &i : w) swap(i.first, i.second);
	sort(w.begin(), w.end());
	for(int i=0; i<n; i++){
		auto l = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
		chk[l]++;
		sz[l]++;
	}
	for(int i=1; i<v.size(); i++){
		pi nxt;
		if(v[i].first == 0 || v[i].second == 0){
			if(v[i].first) nxt = upx(v[i]);
			else nxt = upy(v[i]);
		}
		else if((v[i].first & -v[i].first) < (v[i].second & -v[i].second)) nxt = upx(v[i]);
		else nxt = upy(v[i]);
		par[i] = lower_bound(v.begin(), v.end(), nxt) - v.begin();
		int cst = abs(nxt.first - v[i].first) + abs(nxt.second - v[i].second);
		gph[par[i]].push_back(pi(i, cst));
		gph[i].push_back(pi(par[i], cst));
	}
	for(int i=v.size()-1; i>=1; i--){
		sz[par[i]] += sz[i];
	}
	int pos = 0;
	while(1){
		int nxt = -1;
		for(auto &j : gph[pos]){
			if(j.first != par[pos] && sz[j.first] > n/2) nxt = j.first;
		}
		if(nxt == -1) break;
		pos = nxt;
	}
	cout << dfs(pos, -1).first;
}
