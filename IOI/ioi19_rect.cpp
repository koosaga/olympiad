#include "rect.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 2505;

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		for(int i=x; i<MAXN; i+=i&-i) tree[i] += v;
	}
	int query(int x){
		int ret = 0;
		for(int i=x; i; i-=i&-i) ret += tree[i];
		return ret;
	}
}bit;

struct strip{ int x, s, e, up; };

int cnt[MAXN];

void SORU(vector<strip> &v){
	memset(cnt, 0, sizeof(cnt));
	vector<strip> w(sz(v));
	for(auto &i : v) cnt[i.up]++;
	for(int i=1; i<MAXN; i++) cnt[i] += cnt[i-1];
	for(int i=v.size()-1; i>=0; i--){
		w[--cnt[v[i].up]] = v[i];
	}
	v = w;
}

void SORX(vector<strip> &v){
	memset(cnt, 0, sizeof(cnt));
	vector<strip> w(sz(v));
	for(auto &i : v) cnt[i.x]++;
	for(int i=1; i<MAXN; i++) cnt[i] += cnt[i-1];
	for(int i=v.size()-1; i>=0; i--){
		w[--cnt[v[i].x]] = v[i];
	}
	v = w;
}

void SORS(vector<strip> &v){
	memset(cnt, 0, sizeof(cnt));
	vector<strip> w(sz(v));
	for(auto &i : v) cnt[i.s]++;
	for(int i=1; i<MAXN; i++) cnt[i] += cnt[i-1];
	for(int i=v.size()-1; i>=0; i--){
		w[--cnt[v[i].s]] = v[i];
	}
	v = w;
}

void SORE(vector<strip> &v){
	memset(cnt, 0, sizeof(cnt));
	vector<strip> w(sz(v));
	for(auto &i : v) cnt[i.e]++;
	for(int i=1; i<MAXN; i++) cnt[i] += cnt[i-1];
	for(int i=v.size()-1; i>=0; i--){
		w[--cnt[v[i].e]] = v[i];
	}
	v = w;
}

void proc(vector<strip> &v){
	SORX(v); SORE(v); SORS(v);
	v.resize(unique(v.begin(), v.end(), [&](const strip &a, const strip &b){
		return make_tuple(a.s, a.e, a.x) == make_tuple(b.s, b.e, b.x);
	}) - v.begin());
	for(int i=1; i<v.size(); i++){
		if(pi(v[i-1].s, v[i-1].e) == pi(v[i].s, v[i].e) && v[i-1].x + 1 == v[i].x) v[i].up = v[i-1].up + 1;
	}
}

int L[MAXN], R[MAXN];

void getLR(vector<int> v){
	vector<int> stk;
	int m = sz(v);
	for(int j=0; j<m; j++){
		while(!stk.empty() && v[stk.back()] <= v[j]) stk.pop_back();
		if(stk.size()) L[j] = stk.back();
		stk.push_back(j);
	}
	stk.clear();
	for(int j=m-1; j>=0; j--){
		while(!stk.empty() && v[stk.back()] <= v[j]) stk.pop_back();
		if(stk.size()) R[j] = stk.back();
		stk.push_back(j);
	}
}

lint count_rectangles(vector<vector<int>> a){
	vector<strip> rdir, ldir;
	int n = sz(a);
	int m = sz(a[0]);
	vector<int> stk;
	for(int i=1; i<n-1; i++){
		memset(L, -1, sizeof(L));
		memset(R, -1, sizeof(R));
		vector<int> v(a[i].begin(), a[i].begin() + m);
		getLR(v);
		for(int j=0; j<m; j++){
			if(L[j] != -1 && R[j] != -1){
				rdir.push_back({i, L[j], R[j], 1});
			}
		}
	}
	for(int i=1; i<m-1; i++){
		memset(L, -1, sizeof(L));
		memset(R, -1, sizeof(R));
		vector<int> v;
		for(int j=0; j<n; j++){
			v.push_back(a[j][i]);
		}
		getLR(v);
		for(int j=0; j<n; j++){
			if(L[j] != -1 && R[j] != -1){
				ldir.push_back({i, L[j], R[j], 1});
			}
		}
	}
	proc(ldir);
	proc(rdir);
	SORU(ldir); SORX(ldir); SORE(ldir); 
	SORS(rdir); SORE(rdir); SORX(rdir);
	int p1 = 0, p2 = 0;
	lint ret = 0;
	vector<pi> punk1, punk2;
	for(int i=2; i<n; i++){
		for(int j=2; j<m; j++){
			while(p1 < sz(rdir) && pi(rdir[p1].x + 1, rdir[p1].e) == pi(i, j)){
				punk1.emplace_back(j - rdir[p1].s - 1, rdir[p1].up);
				p1++;
			}
			while(p2 < sz(ldir) && pi(ldir[p2].e, ldir[p2].x + 1) == pi(i, j)){
				punk2.emplace_back(ldir[p2].up, i - ldir[p2].s - 1);
				p2++;
			}
			reverse(punk1.begin(), punk1.end());
			int p3 = 0;
			for(auto &y : punk2){
				while(p3 < sz(punk1) && punk1[p3].first <= y.first) bit.add(punk1[p3++].second, +1);
				ret += p3 - bit.query(y.second - 1);
			}
			for(int i=0; i<p3; i++) bit.add(punk1[i].second, -1);
			punk1.clear();
			punk2.clear();
		}
	}
	return ret;
}
