#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

lint a, m, p, q, r, s;
pi tmp[50];

vector<int> get(int t){
	vector<int> sregy, ret;
	sregy.push_back(2e9);
	lint tr = r, ts = s;
	for(int i=t-1; i>=0; i--){
		tr = (tr + m - 1) / m;
		ts = ts / m;
		tmp[i] = pi(tr, ts);
	}
	lint cr = p, cs = q;
	for(int i=0; i<t; i++){
		lint mind = (max(tmp[i].first - cr, 0ll) + a - 1) / a;
		mind = min((max(tmp[i].second - cs, 0ll)) / a, mind);
		mind = max(mind, 0ll);
		if(mind != 0){
			ret.push_back(-mind);
		}
		cr += mind * a;
		cs += mind * a;
		cr *= m;
		cs *= m;
		if(!ret.empty() && ret.back() > 0){
			ret.back()++;
		}
		else ret.push_back(1);
	}
	lint mind = (max(r - cr, 0ll) + a - 1) / a;
	mind = max(mind, 0ll);
	if(mind != 0){
		ret.push_back(-mind);
	}
	cr += mind * a;
	cs += mind * a;
	if(r <= cr && cs <= s) return ret;
	return sregy;
}

bool compare(vector<int> &a, vector<int> &b){
	lint s1 = 0, s2 = 0;
	for(auto &i : a){
		s1 += abs(i);
	}
	for(auto &j : b){
		s2 += abs(j);
	}
	if(s1 < s2) return 1;
	if(s1 > s2) return 0;
	int p = 0;
	lint cs = 0;
	for(auto &i : a){
		lint js = 0;
		for(auto &j : b){
			if(max(cs, js) < min(cs + abs(i), js + abs(j))){
				if(i < 0 && j > 0) return 1;
				if(i > 0 && j < 0) return 0;
			}
			js += abs(j);
		}
		cs += abs(i);
	}
	return 1;
}

void solve(){
	if(m == 1){
		lint mind = (max(r - p, 0ll) + a - 1) / a;
		mind = min(mind, (s - q) / a);
		mind = max(mind, 0ll);
		p += mind * a;
		q += mind * a;
		if(r <= p && q <= s){
			if(mind == 0) printf("empty");
			else printf("%lldA",mind);
		}
		else{
			printf("impossible");
		}
		return;
	}
	lint tmp = m;
	vector<int> v = get(0);
	for(int i=1; tmp <= s; i++){
		vector<int> t = get(i);
		if(compare(t, v)) v = t; 
		tmp *= m;
	}
	if(v.empty()){
		printf("empty");
		return;
	}
	if(v[0] == 2e9){
		printf("impossible");
		return;
	}
	for(auto &i : v){
		if(i < 0) printf("%dA ", -i);
		else printf("%dM ", i);
	}
}

int main(){
	for(int i=1; ; i++){
		cin >> a >> m >> p >> q >> r >> s;
		if(!a && !m && !p && !q && !r && !s){
			break;
		}
		printf("Case %d: ", i);
		solve();
		puts("");
	}
}