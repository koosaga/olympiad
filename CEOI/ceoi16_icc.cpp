#include "icc.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;

vector<vector<int>> comp;

bool Q(vector<int> &a, vector<int> &b){
	if(a.empty() || b.empty()) return 0;
	vector<int> va, vb;
	for(auto &i : a){
		for(auto &j : comp[i]){
			va.push_back(j);
		}
	}
	for(auto &i : b){
		for(auto &j : comp[i]){
			vb.push_back(j);
		}
	}
	return query(va.size(), vb.size(), va.data(), vb.data());
}

bool Q2(vector<int> a, vector<int> b){
	if(a.empty() || b.empty()) return 0;
	return query(a.size(), b.size(), a.data(), b.data());
}

int solve(int s, int e, vector<int> &a, vector<int> &b, int d){
	if(d == 0){
		int m = (s+e)/2;
		for(int i=s; i<=m; i++) a.push_back(i);
		for(int i=m+1; i<=e; i++) b.push_back(i);
		return max(m-s+1, e-m);
	}
	int m = (s+e)/2;
	int r1 = solve(s, m, a, b, d-1);
	int r2 = solve(m+1, e, a, b, d-1);
	return max(r1, r2);
}

void make(int s, int e, vector<int> &a, vector<int> &b, int d){
	if(d == 0){
		int m = (s+e)/2;
		for(int i=s; i<=m; i++) a.push_back(i);
		for(int i=m+1; i<=e; i++) b.push_back(i);
		return;
	}
	int m =(s+e)/2;
	vector<int> la, lb;
	solve(s, m, la, lb, d-1);
	if(Q(la, lb)) return make(s, m, a, b, d-1);
	return make(m+1, e, a, b, d-1);
}

int f(int x){
	return x / 2; 
}

pi dnc1(vector<int> a, vector<int> b, int p){
	if(a.size() == 1 && b.size() == 1){
		return pi(a[0], b[0]);
	}
	vector<int> ha1, ha2;
	for(int i=0; i<f(a.size()); i++){
		ha1.push_back(a[i]);
	}
	for(int i=f(a.size()); i<a.size(); i++){
		ha2.push_back(a[i]);
	}
	if(ha2.empty() || Q(ha1, b)) return dnc1(b, ha1, 0);
	return dnc1(b, ha2, 0);
}

pi dnc2(vector<int> a, vector<int> b){
	if(a.size() == 1 && b.size() == 1){
		return pi(a[0], b[0]);
	}
	vector<int> ha1, ha2;
	for(int i=0; i<f(a.size()); i++){
		ha1.push_back(a[i]);
	}
	for(int i=f(a.size()); i<a.size(); i++){
		ha2.push_back(a[i]);
	}
	if(ha2.empty() || Q2(ha1, b)) return dnc2(b, ha1);
	return dnc2(b, ha2);
}

void run(int n) {
	for(int i=1; i<=n; i++){
		vector<int> v = {i};
		comp.push_back(v);
	}
	for(int i=n; i>=2; i--){
		vector<int> a, b;
		int p = 0;
		while(1){
			a.clear();
			b.clear();
			if(solve(0, i-1, a, b, p) == 1) break;
			if(Q(a, b)){
				a.clear();
				b.clear();
				make(0, i-1, a, b, p);
				break;
			}
			p++;
		}
		auto t = dnc1(a, b, 0);
		auto u = dnc2(comp[t.first], comp[t.second]);
		setRoad(u.first, u.second);
		for(auto &i : comp[t.second]){
			comp[t.first].push_back(i);
		}
		comp[t.second].clear();
		for(int j=t.second; j+1<i; j++){
			comp[j] = comp[j+1];
		}
	}
}
