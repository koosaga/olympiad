#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

// Check camp17_railway_trip_alternative.cpp for application
struct treeDecomp{
	bool valid;
	vector<int> par;
	vector<vector<int>> bags;
};

// Tree decomposition, width 2
treeDecomp tree_decomposition(int n, vector<pi> edges){
	vector<set<int>> gph(n);
	for(auto &[u, v] : edges){
		gph[u].insert(v);
		gph[v].insert(u);
	}
	treeDecomp ret;
	ret.valid = false;
	ret.par.resize(n, -1);
	ret.bags.resize(n);
	queue<int> que;
	for(int i = 0; i < n; i++){
		if(sz(gph[i]) <= 2) que.push(i);
	}
	auto rem_edge = [&](int u, int v){
		gph[u].erase(gph[u].find(v));
		gph[v].erase(gph[v].find(u));
	};
	vector<pair<int, int>> pcand(n, pi(-1, -1));
	vector<int> ord(n, -1);
	int piv = 0;
	while(sz(que)){
		int x = que.front();
		que.pop();
		if(ord[x] != -1) continue;
		ret.bags[x].push_back(x);
		ord[x] = piv++;
		if(sz(gph[x]) == 1){
			int y = *gph[x].begin();
			rem_edge(x, y);
			ret.bags[x].push_back(y);
			if(sz(gph[y]) <= 2) que.push(y);
			pcand[x] = pi(y, y);
		}
		if(sz(gph[x]) == 2){
			int u = *gph[x].begin();
			int v = *gph[x].rbegin();
			rem_edge(x, u);
			rem_edge(x, v);
			gph[u].insert(v);
			gph[v].insert(u);
			ret.bags[x].push_back(u);
			ret.bags[x].push_back(v);
			if(sz(gph[u]) <= 2) que.push(u);
			if(sz(gph[v]) <= 2) que.push(v);
			pcand[x] = pi(u, v);
		}
	}
	if(piv != n) return ret;
	ret.valid = true;
	int root = -1;
	for(int i = 0; i < n; i++){
		if(pcand[i].first == -1){
			if(root != -1) ret.par[i] = root;
			else root = i;
			continue;
		}
		if(ord[pcand[i].first] < ord[pcand[i].second]) swap(pcand[i].first, pcand[i].second);
		ret.par[i] = pcand[i].second;
	}
	return ret;
}

