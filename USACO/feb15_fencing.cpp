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
  
lint ccw(pi a, pi b, pi c){
	lint dx1 = b.first - a.first;
	lint dy1 = b.second - a.second;
	lint dx2 = c.first - a.first;
	lint dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}
  
struct hull{
	vector<pi> h1, h2, pnt;
	void merge(vector<pi> &v){
		vector<pi> tmp = pnt;
		pnt.resize(pnt.size() + v.size());
		std::merge(tmp.begin(), tmp.end(), v.begin(), v.end(), pnt.begin());
		h1.clear();
		h2.clear();
		for(auto &i : pnt){
			while(h1.size() >= 2 && ccw(h1[h1.size()-2], h1.back(), i) <= 0){
				h1.pop_back();
			}
			while(h2.size() >= 2 && ccw(h2[h2.size()-2], h2.back(), i) >= 0){
				h2.pop_back();
			}
			h1.push_back(i);
			h2.push_back(i);
		}
	}
	pi query(int a, int b, lint c){
		if(pnt.empty()) return pi(5e18, -5e18);
		auto func = [&](pi i){
			return 1ll * a * i.first + 1ll * b * i.second - c;
		};
		int s = 0, e = h1.size()-1;
		while(s != e){
			int m = (s+e)/2;
			if(func(h1[m]) <= func(h1[m+1])){
				e = m;
			}
			else s = m+1;
		}
		lint cmin = func(h1[s]);
		s = 0, e = h2.size() - 1;
		while(s != e){
			int m = (s+e)/2;
			if(func(h2[m]) >= func(h2[m+1])){
				e = m;
			}
			else s = m+1;
		}
		lint cmax = func(h2[s]);
		return pi(cmin, cmax);
	}
	void clear(){
		h1.clear();
		h2.clear();
		pnt.clear();
	}
}h[19];
  
void upload(pi t){
	vector<pi> v;
	v.push_back(t);
	h[0].merge(v);
	for(int i=0; i<19; i++){
		if(h[i].pnt.size() > (1<<i)){
			h[i+1].merge(h[i].pnt);
			h[i].clear();
		}
		else break;
	}
}
  
bool query(int a, int b, lint c){
	if(b < 0) tie(a, b, c) = make_tuple(-a, -b, -c);
	lint cmin = 5e18, cmax = -5e18;
	for(int i=0; i<19; i++){
		auto t = h[i].query(a, b, c);
		cmin = min(cmin, t.first);
		cmax = max(cmax, t.second);
	}
	return cmax < 0 || cmin > 0;
}
  
int n, q;
  
int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<n; i++){
		pi t;
		scanf("%lld %lld",&t.first, &t.second);
		upload(t);
	}
	while(q--){
		int t;
		scanf("%d",&t);
		if(t == 1){
			pi u;
			scanf("%lld %lld",&u.first, &u.second);
			upload(u);
		}
		else{
			int a, b;
			lint c;
			scanf("%d %d %lld",&a,&b,&c);
			puts(query(a, b, c) ? "YES" : "NO");
		}
	}
}