#include "park.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 1500;

static int Place[1400];

vector<int> gph[MAXN];
vector<int> ord;

int vis[MAXN], sz[MAXN];

void dfs(int x){
	vis[x] = 1;
	sz[x] = 1;
	ord.push_back(x);
	for(auto &y : gph[x]){
		if(!vis[y]){
			dfs(y);
			sz[x] += sz[y];
		}
	}
}

void go(int s, int e, int x, int n){
//	cout <<"go " <<  s << " " << e << " " << x << endl;

	set<int> banned;
	while(banned.count(s) == 0){
		// see if there exists edge in first place (called N+8M times)
		{
			for(int i = 0; i < n; i++) Place[i] = 0;
			for(int i = s; i <= e; i++){
				if(banned.count(i)) continue;
				Place[ord[i]] = 1;
			}
			Place[x] = 1;
			if(Ask(min(ord[s], x), max(ord[s], x), Place) == 0) return;
		}
		// find first position where you can have connection (called M times)
		int connPoint = -1;
		{
			int ns = s, ne = e;
			while(ns != ne){
				int m = (ns + ne) / 2;
				for(int i = 0; i < n; i++) Place[i] = 0;
				Place[ord[s]] = Place[x] = 1;
				for(int i = s; i <= m; i++){
					if(banned.count(i)) continue;
					Place[ord[i]] = 1;
				}
				if(Ask(min(ord[s], x), max(ord[s], x), Place) == 1) ne = m;
				else ns = m + 1;
			}
			connPoint = ns;
		}
		// add edge
		int y = ord[connPoint];
		gph[x].push_back(y);
//		cout << "found edge " << x << " " << y << endl;
		// ban 
		for(int i = connPoint; i <= connPoint + sz[y] - 1; i++){
			banned.insert(i);
		}
		int pos = connPoint + 1;
		while(pos <= connPoint + sz[y] - 1){
			go(pos, pos + sz[ord[pos]] - 1, x, n);
			pos += sz[ord[pos]];
		}
	}
}

void Detect(int T, int N) {
	vector<int> v = {};
	for(int i = 1; i < N; i++){
		auto init = [&](){
			memset(Place, 0, sizeof(Place));
			for(int i = 0; i < N; i++) Place[i] = 1;
		};
		int s = 0, e = sz(v);
		while(s != e){
			int m = (s + e) / 2;
			init();
			for(int i = m; i < sz(v); i++) Place[v[i]] = 0;
			if(Ask(0, i, Place) == 1) e = m;
			else s = m + 1;
		}
		v.insert(v.begin() + s, i);
	}
//	for(auto &i : v) cout << i << " ";
//	cout << "ok??" << endl;
	for(int i = 0; i < sz(v); i++){
		ord.clear();
		memset(sz, 0, sizeof(sz));
		memset(vis, 0, sizeof(vis));
		dfs(0);
		go(0, sz(ord) - 1, v[i], N);
		for(auto &j : gph[v[i]]) gph[j].push_back(v[i]);
	}
	for(int i = 0; i < N; i++){
		for(auto &j : gph[i]) if(i < j) Answer(i, j);
		gph[i].clear();
	}
}
