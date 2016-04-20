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
typedef pair<int, int> pi;
typedef map<int,int>::iterator aauto;

int n, m;
vector<int> v;

struct intv{int s, e, x;}a[200005];

bool cmp(intv a, intv b){
	return a.e - a.s < b.e - b.s;
}

bool monotone(int a, int b, int c){
	return 1ll * (c - b) * (b - a) > 0;
}

void input(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].s, &a[i].e);
		a[i].x = i;
	}
	int bef;
	scanf("%d",&bef);
	v.push_back(bef);
	for(int i=1; i<m; i++){
		int t;
		scanf("%d",&t);
		if(v.size() && v.back() == t) continue;
		else if(v.size() >= 2 && monotone(v[v.size() - 2], v.back(), t)){
			v[v.size()-1] = t;
		}
		else v.push_back(t);
	}
}

lint ans[200005];
map<int, int> mp;
set<pi> s;

lint cumul;

void add(pi t){
	s.insert(pi(abs(t.second), t.first));
	mp.insert(pi(t.first, t.second));
	cumul += abs(t.second);
}

void del(aauto t){
	pi var = *t;
	mp.erase(t);
	s.erase(pi(abs(var.second), var.first));
	cumul -= abs(var.second);
}

int main(){
	input();
	sort(a, a+n, cmp);
	for(int i=1; i<v.size(); i++){
		add(pi(i, v[i] - v[i-1]));
	}
	int orig = v[0];
	for(int i=0; i<n; i++){
		while(s.size() > 1 && s.begin()->first <= a[i].e - a[i].s){
			pi t = *s.begin();
			aauto it = mp.find(t.second);
			if(it == mp.begin()){
				orig += it->second;
				del(it);
			}
			else if(it == --mp.end()) del(it);
			else{
				aauto bef = it, nxt = it;
				bef--, nxt++;
				pi rm1 = *bef, rm2 = *it, rm3 = *nxt;
				int tot = rm1.second + rm2.second + rm3.second;
				del(bef);
				del(it);
				del(nxt);
				add(pi(rm3.first, tot));
			}
		}
		lint ret = 0;
		if(mp.size() >= 2){
			if(mp.begin()->second > 0){
				ret += abs(a[i].s - orig);
			}
			else{
				ret += abs(a[i].e - orig);
			}
			ret += cumul - 1ll * (a[i].e - a[i].s) * mp.size();
		}
		else{
			vector<int> pos;
			pos.push_back(orig);
			if(mp.size()) pos.push_back(orig + mp.begin()->second);
			int p = a[i].s;
			for(int j=0; j<pos.size(); j++){
				if(p + a[i].e - a[i].s < pos[j]){
					ret += pos[j] - (p + a[i].e - a[i].s);
					p = pos[j] - a[i].e + a[i].s;
				}
				else if(p > pos[j]){
					ret += p - pos[j];
					p = pos[j];
				}
			}
		}
		ans[a[i].x] = ret;
	}
	for(int i=0; i<n; i++){
		printf("%lld\n",ans[i]);
	}
}