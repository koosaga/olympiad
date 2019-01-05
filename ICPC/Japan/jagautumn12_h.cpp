#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using real_t = long double;
using pi = pair<lint, lint>;
const int MAXN = 1005;

struct cht{
	vector<pi> v;
	void clear(){ v.clear(); }
	bool bad(pi a, pi b, pi c){
		real_t crs1 = 1.0L * (b.second - a.second) / (a.first - b.first);
		real_t crs2 = 1.0L * (c.second - b.second) / (b.first - c.first);
		return crs1 >= crs2;
	}
	vector<real_t> getgj(){
		vector<real_t> w;
		for(int i=0; i<v.size()-1; i++){
			pi a = v[i]; pi b = v[i+1];
			real_t crs1 = 1.0L * (b.second - a.second) / (a.first - b.first);
			w.push_back(crs1);
		}
		return w;
	}
	void add(lint x, lint y){
		while(v.size() >= 2 && bad(v[v.size()-2], v.back(), pi(x, y))) v.pop_back();
		v.emplace_back(x, y);
	}
	lint query(lint x){
		int s = 0, e = v.size() - 1;
		while(s != e){
			int m = (s + e) / 2;
			if(v[m].first * x + v[m].second > v[m+1].first * x + v[m+1].second) s = m + 1;
			else e = m;
		}
		return v[s].first * x + v[s].second;
	}
}cht1, cht2;


int n, m, s1, s2, t;
vector<pi> gph[MAXN];
lint dist[105][MAXN];

struct node{
	int cnt, pos; lint dist;
	bool operator<(const node &n)const{
		return dist > n.dist;
	}
};

void solve(){
	priority_queue<node> pq;
	scanf("%d %d %d %d %d",&n,&m,&s1,&s2,&t);
	if(n + m + s1 + s2 + t == 0){
		exit(0);
	}
	for(int i=0; i<m; i++){
		int a, b;
		cin >> a >> b;
		string w; cin >> w;
		int wei = -1;
		if(w != "x"){
			sscanf(w.c_str(), "%d",&wei);
		}
		gph[a].emplace_back(wei, b);
		gph[b].emplace_back(wei, a);
	}
	memset(dist, 0x3f, sizeof(dist));
	pq.push({0, t, 0});
	dist[0][t] = 0;
	while(!pq.empty()){
		auto x = pq.top(); pq.pop();
		if(dist[x.cnt][x.pos] != x.dist) continue;
		for(auto &i : gph[x.pos]){
			if(i.first == -1 && x.cnt == 104) continue;
			if(i.first == -1 && dist[x.cnt + 1][i.second] > x.dist){
				dist[x.cnt + 1][i.second] = x.dist;
				pq.push({x.cnt + 1, (int)i.second, x.dist});
			}
			if(i.first > -1 && dist[x.cnt][i.second] > x.dist + i.first){
				dist[x.cnt][i.second] = x.dist + i.first;
				pq.push({x.cnt, (int)i.second, x.dist + i.first});
			}
		}
	}
	lint ret = 1e18;
	cht1.clear();
	cht2.clear();
	for(int i=104; i>=0; i--){
		dist[i][s1] = min(dist[i][s1], (lint)1e18);
		dist[i][s2] = min(dist[i][s2], (lint)1e18);
		cht1.add(i, dist[i][s1]);
		cht2.add(i, dist[i][s2]);
	}
	vector<real_t> v1 = cht1.getgj();
	vector<real_t> v2 = cht2.getgj();
	vector<lint> cnd = {0, (lint)1e16};
	for(auto &i : v1){
		for(int j=-2; j<=2; j++) cnd.push_back((lint)floor(i + j));
	}
	for(auto &i : v2){
		for(int j=-2; j<=2; j++) cnd.push_back((lint)floor(i + j));
	}
	for(auto &i : cnd){
		i = max(i, 0ll);
		i = min(i, (lint)1e16);
	}
	sort(cnd.begin(), cnd.end());
	cnd.resize(unique(cnd.begin(), cnd.end()) - cnd.begin());
	auto fuck = [&](lint x){
		return abs(cht1.query(x) - cht2.query(x));
	};
	for(auto &i : cnd){
		ret = min(ret, fuck(i));
	}
	for(int i=1; i<cnd.size(); i++){
		lint s = cnd[i-1], e = cnd[i]; 
		while(s != e){
			lint m = (s + e)/ 2;
			if(fuck(m) < fuck(m + 1)) e = m;
			else s = m + 1;
		}
		ret = min(ret, fuck(s));
	}
	cout << ret << endl;
}

int main(){
	while(1){
		solve();
		for(int i=0; i<MAXN; i++) gph[i].clear();
	}
}

