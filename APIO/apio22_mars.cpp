#include "mars.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2000;

struct disjset{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

char str[50][50];

vector<pi> upRight(int n){
	vector<pi> v;
	for(int i = n - 1; i >= 0; i--) v.emplace_back(i, 0);
	for(int i = 1; i < n; i++) v.emplace_back(0, i);
	return v;
}

vector<int> bin2comp(string s, vector<pi> locs){
	assert(sz(s) % 2 == 0);
	assert(sz(s) == sz(locs) + 1);
	vector<int> ans;
	for(int i = 0; i < sz(locs); i++){
		if(str[locs[i].first][locs[i].second] == '0') ans.push_back(0);
		else ans.push_back(1);
	}
	ans.push_back(0);
	disjset newGrp;
	newGrp.init(sz(ans));
	for(int i = 0; i + 1 < sz(ans); i++){
		if(ans[i] && ans[i + 1]) newGrp.uni(i, i + 1);
	}
	vector<int> v;
	for(int i = 0; i < sz(s); i++){
		if(s[i] == '0') continue;
		if(i % 2 == 1){
			v.push_back(i / 2);
		}
		else{
			assert(sz(v));
			int l = v.back();
			int r = i / 2;
			v.pop_back();
			l *= 2;
			r *= 2;
			if(ans[l] == 0) l++;
			if(ans[r] == 0) r++;
			assert(ans[l] && ans[r]);
			newGrp.uni(l, r);
		}
	}
	assert(sz(v) == 0);
	ans.pop_back();
	for(int i = 0; i < sz(ans); i++){
		if(ans[i]) ans[i] = newGrp.find(i) + 1;
	}
	return ans;
}

string comp2bin(vector<int> v){
	assert(sz(v) % 2 == 1);
	v.push_back(0);
	{
		// compress
		vector<int> w;
		for(int i = 0; i < sz(v); i+=2){
			assert(v[i] == 0 || v[i+1] == 0 || v[i] == v[i + 1]);
			w.push_back(max(v[i], v[i + 1]));
		}
		v = w;
	}
	string s;
	for(int i = 0; i < sz(v); i++){
		if(v[i] == 0) s += "00";
		if(v[i]){
			bool prv = 0, nxt = 0;
			for(int j = 0; j < i; j++) if(v[j] == v[i]) prv = 1;
			for(int j = i + 1; j < sz(v); j++) if(v[j] == v[i]) nxt = 1;
			s.push_back(prv + '0');
			s.push_back(nxt + '0');
		}
	}
	return s;
}

std::string process(std::vector <std::vector<std::string>> a, int i, int j, int k, int n){
	int m = 2 * (n - k - 1);
	if(i == m && j == m){
		int g = 2 * k + 3;
		memset(str, 0, sizeof(str));
		auto get = [&](int x, int y){
			return x * g + y + 1;
		};
		disj.init(g * g + 1);
		int preComp = 0;
		string foo;
		if(k == 0){
			// first 2 bits.
			foo.push_back(a[2][0][0]);
			foo.push_back(a[0][2][0]);
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					str[i][j] = a[i][j][0];
				}
			}
		}
		else{
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					if(i + j == 4) continue;
					for(int x = 0; x < 2*k; x++){
						str[i + (2*k - x)][j] = a[i][j][x];
						str[i][j + x + 1] = a[i][j][2*k + x + 1];
					}
					str[i][j] = a[i][j][2*k];
				}
			}
			str[g - 1][2] = a[2][2][0];
			str[2][g - 1] = a[2][2][1];
			foo.push_back(str[g - 1][0]);
			foo.push_back(str[0][g - 1]);
			for(int i = 0; i < 11; i++){
				if(a[2][2][i + 2] == '1') preComp += (1 << i);
			}
			auto points = upRight(g - 2);
			for(auto &[x, y] : points){
				x += 2;
				y += 2;
			}
			auto seq = bin2comp(a[2][2].substr(13, 4 * k + 2), points);
			for(int i = 0; i < sz(seq); i++){
				for(int j = 0; j < i; j++){
					if(seq[i] && seq[j] && seq[i] == seq[j]){
						disj.uni(get(points[i].first, points[i].second), get(points[j].first, points[j].second));
					}
				}
			}
		}
		for(int i = 0; i < g; i++){
			for(int j = 0; j < g; j++){
				if(str[i][j] == '1' && str[i + 1][j] == '1'){
					disj.uni(get(i, j), get(i + 1, j));
				}
				if(str[i][j] == '1' && str[i][j + 1] == '1'){
					disj.uni(get(i, j), get(i, j + 1));
				}
			}
		}
		set<int> s;
		for(int i = 0; i < g; i++){
			for(int j = 0; j < g; j++){
				if(str[i][j] == '1'){
					int w = disj.find(get(i, j));
					s.insert(w);
				}
			}
		}
		auto seq = upRight(g);
		vector<int> vect;
		for(auto &[x, y] : seq){
			if(str[x][y] == '1'){
				int w = disj.find(get(x, y));
				if(s.count(w)) s.erase(w);
				vect.push_back(w);
			}
			else vect.push_back(0);
		}
		// 11 bits for internal components
		int cnt = sz(s) + preComp;
		if(k == n - 1){
			set<int> s;
			for(auto &j : vect) if(j) s.insert(j);
			cnt += sz(s);
			foo.clear();
			foo.resize(100, '0');
			for(int i = 0; i < 11; i++){
				foo[i] = cnt % 2 + '0';
				cnt /= 2;
			}
			return foo;
		}
		else{
			for(int i = 0; i < 11; i++){
				foo.push_back(cnt % 2 + '0');
				cnt /= 2;
			}
		}
		assert(sz(vect) + 1 == 2 * g);
		auto useq = comp2bin(vect);
		assert(sz(useq) == 2 * g);
		foo += useq;
		foo.resize(100, '0');
		return foo;
	}
	else{
		string foo;
		foo.push_back(a[2][0][0]);
		foo.push_back(a[1][0][0]);
		a[0][0].resize(4 * k + 1);
		foo += a[0][0];
		foo.push_back(a[0][1][4 * k]);
		foo.push_back(a[0][2][4 * k]);
		foo.resize(100, '0');
		return foo;
	}
}