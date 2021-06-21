#include "meetings.h"
#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
 using lint = long long;

mt19937 rng(0x14004);
int randint(int lb, int ub){ return uniform_int_distribution<int>(lb, ub)(rng); }
 
void bridge(int x, int y){ Bridge(min(x, y), max(x, y)); }
 map<lint, int> mp;
int query(lint x, lint y, lint z){
    if(x > y) swap(x, y);
    if(y > z) swap(y, z);
    if(x > y) swap(x, y);
    lint qq = (x << 40) | (y << 20) | z;
    if(mp.find(qq) != mp.end()) return mp[qq];
    return mp[qq] = Query(x, y, z);
}

void dfs(vector<int> v){
	if(v.size() == 1) return;
	if(v.size() == 2){
		bridge(v[0], v[1]);
		return;
	}
    shuffle(v.begin()+1, v.end(), rng);
    vector<pi> ords;
  vector<int> fuck = {v[0]};
    ords.emplace_back(v[1], v[1]);
	for(int i=2; i<v.size(); i++){
		int q = query(v[0], v[1], v[i]);
      if(q == v[0]) fuck.push_back(v[i]);
		else ords.emplace_back(q, v[i]);
	}
	sort(ords.begin(), ords.end(), [&](pi a, pi b){
		if(a.first != b.first) return query(v[0], a.first, b.first) == a.first;
		return a.second < b.second;
	});
  if(sz(ords)) bridge(v[0], ords[0].first);
	for(int i = 0; i < sz(ords); ){
		int e = i;
      vector<int> w;
		while(e < sz(ords) && ords[i].first == ords[e].first){
			w.push_back(ords[e++].second);
		}
		swap(w[0], *find(all(w), ords[i].first));
		dfs(w);
		if(e < sz(ords)) bridge(ords[i].first, ords[e].first);
		i = e;
	}
  dfs(fuck);
}
 
void Solve(int N) {
	vector<int> v(N);
	iota(v.begin(), v.end(), 0);
	dfs(v);
}

