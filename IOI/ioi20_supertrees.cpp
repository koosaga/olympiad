#include "supertrees.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
const int MAXN = 1505;
 
struct disj{
	int pa[MAXN];
	int sz[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
		fill(sz, sz + n + 1, 1);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	int getsz(int x){ return sz[find(x)]; }
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		sz[p] += sz[q];
		pa[q] = p; return 1;
	}
}disj, cx;
 
int n;
 
int construct(std::vector<std::vector<int>> a) {
	n = sz(a);
	disj.init(n);
	std::vector<std::vector<int>> answer(n);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(a[i][j] == 1) disj.uni(i, j);
			if(a[i][j] == 3) return 0;
		}
		answer[i].resize(n);
	}
	vector<int> v;
	for(int i=0; i<n; i++){
		if(disj.find(i) != i){
			answer[i][disj.find(i)] = 1;
			answer[disj.find(i)][i] = 1;
		}
		else v.push_back(i);
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(a[i][j] != a[disj.find(i)][disj.find(j)]) return 0;
		}
	}
	cx.init(n);
	for(auto &i : v){
		for(auto &j : v){
			if(a[i][j] == 2){
				cx.uni(i, j);
			}
		}
	}
	vector<int> v2[MAXN];
	for(auto &i : v){
		if(cx.getsz(i) > 1) v2[cx.find(i)].push_back(i);
	}
	for(int i=0; i<n; i++){
		if(sz(v2[i]) && sz(v2[i]) <= 2) return 0;
		for(auto &x : v2[i]){
			for(auto &y : v2[i]){
				if(x != y && a[x][y] != 2) return 0;
			}
		}
		if(sz(v2[i])){
			for(int j=0; j<sz(v2[i]); j++){
				int l = v2[i][j];
				int r = v2[i][(j+1)%sz(v2[i])];
				answer[l][r] = answer[r][l] = 1;
			}
		}
	}
	disj.init(n);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(answer[i][j]) disj.uni(i, j);
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(a[i][j] == 0 && disj.find(i) == disj.find(j)) return 0;
		}
	}
	build(answer);
	return 1;
}
