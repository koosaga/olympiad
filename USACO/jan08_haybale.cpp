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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int q;
struct intv{
	int s, e, x;
}a[25005];

vector<int> v;
vector<intv> ls;
set<int> s;

bool trial(int x){
	ls.clear();
	for(int i=0; i<x; i++){
		ls.push_back(a[i]);
	}
	sort(ls.begin(), ls.end(), [&](const intv &a, const intv &b){
		return a.x > b.x;
	});
	s.clear();
	for(int i=0; i<v.size(); i++) s.insert(i);
	s.insert(1e9);
	for(int i=0; i<ls.size(); ){
		int e = i;
		int st = 0, ed = 1e9;
		while(e < ls.size() && ls[i].x == ls[e].x){
			st = max(st, ls[e].s);
			ed = min(ed, ls[e].e);
			e++;
		}
		if(*s.lower_bound(st) > ed) return 0;
		st = 1e9, ed = 0;
		for(int j=i; j<e; j++){
			st = min(st, ls[j].s);
			ed = max(ed, ls[j].e);
		}
		auto t = s.lower_bound(st);
		while(t != s.end() && *t <= ed){
			auto u = t;
			u++;
			s.erase(t);
			t = u;
		}
		i = e;
	}
	return 1;
}

int main(){
	scanf("%*d %d",&q);
	for(int i=0; i<q; i++){
		scanf("%d %d %d",&a[i].s,&a[i].e,&a[i].x);
		v.push_back(a[i].s);
		v.push_back(a[i].e+1);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for(int i=0; i<q; i++){
		a[i].s = lower_bound(v.begin(), v.end(), a[i].s) - v.begin();
		a[i].e = lower_bound(v.begin(), v.end(), a[i].e+1) - v.begin() - 1;
	}
	int s = 0, e = q;
	while(s != e){
		int m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	if(s == q) puts("0");
	else printf("%d",s+1);
}