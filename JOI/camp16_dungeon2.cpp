#include "dungeon2.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;

int adj[205][205];
int piv;

vector<int> stk, edg;
vector<pi> tree[205], insp[205];
int parway[205], par[205];

void dfs(){
	piv++;
	int cur = piv;
	int p = NumberOfRoads();
	vector<int> v;
	for(int i=1; i<=p; i++){
		if(parway[cur] == i) continue;
		Move(i, 2);
		int t = Color();
		if(t == 3){
			Move(LastRoad(), 3);
		}
		if(t == 1){
			stk.push_back(cur);
			edg.push_back(i);
			int conn = piv + 1;
			tree[cur].push_back({conn, i});
			par[conn] = cur;
			parway[conn] = LastRoad();
			adj[cur][conn] = adj[conn][cur] = 1;
			dfs();
			stk.pop_back();
			edg.pop_back();
			Move(parway[conn], 3);
		}
		if(t == 2){
			insp[cur].push_back({i, 0});
			Move(LastRoad(), 2);
		}
	}
}

void dfs2(int x, int it){
	int p = (x / it) % 3;
	for(auto &i : tree[x]){
		Move(i.second, p + 1);
		dfs2(i.first, it);
		Move(parway[i.first], 1);
	}
	for(auto &i : insp[x]){
		Move(i.first, 1);
		int p = Color();
		i.second += it * (p - 1);
		Move(LastRoad(), p);
	}
}

int cnt[205];
void Inspect(int R)
{
	memset(adj, 0x3f, sizeof(adj));
	dfs();
	for(int i=1; i<=81; i*=3){
		dfs2(1, i);
	}
	for(int i=1; i<=piv; i++){
		for(auto &j : insp[i]){
			adj[i][j.second] = adj[j.second][i] = 1;
		}
	}
	for(int i=1; i<=piv; i++){
		for(int j=1; j<=piv; j++){
			for(int k=1; k<=piv; k++){
				adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
			}
		}
	}
	for(int i=1; i<=piv; i++){
		for(int j=1; j<i; j++){
			cnt[adj[i][j]]++;
		}
	}
	for(int i=1; i<=R; i++){
		Answer(i, cnt[i]);
	}
}
