#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const lint oo = 1e18;
  
struct obj{
	int x, y;
	lint cst;
	bool operator<(const obj &c)const{
		return cst == c.cst ? (pi(y,x) > pi(c.y,c.x)) : (cst < c.cst);
	}
};
  
int mark[2][150005], occu[150005];
int n, q;
  
pi arr[30005];
set<pi> s;
  
lint hyp(int x, int y){
	return 1ll * x * x + 1ll * y * y;
}
  
obj cost_calc(int s, int e){
	if(s == 1 && e == n){
		return {0, 1, oo};
	}
	if(s == 1){
		if(occu[e+1] == 2){
			return {0, 1, hyp(e+1-s, 0)};
		}
		return {mark[0][e+1], 1, hyp(e+1-s, 1)};
	}
	if(e == n){
		if(occu[s-1] == 2){
			return {0, n, hyp(e+1-s, 0)};
		}
		return {mark[0][s-1], n, hyp(e+1-s, 1)};
	}
	if(occu[s-1] == 2 && occu[e+1] == 2){
		return {0, (s+e)/2, hyp((s+e)/2-s+1, 0)};
	}
	if(occu[s-1] + occu[e+1] == 3){
		if((e - s + 1) % 2 == 1){
			return {0, (s+e)/2, hyp((s+e)/2-s+1, 0)};
		}
		if(occu[s-1] == 1){
			return {mark[0][s-1], (s+e)/2, hyp((s+e)/2-s+1, 1)};
		}
		return {mark[0][e+1], (s+e)/2+1, hyp(e-(s+e)/2, 1)};
	}
	if(occu[s-1] == 1 && occu[e+1] == 1){
		if(mark[0][s-1] == mark[0][e+1]){
			return {mark[0][s-1], (s+e)/2, hyp((s+e)/2-s+1, 1)};
		}
		if((e - s + 1) % 2 == 1){
			return {0, (s+e)/2, hyp((s+e)/2-s+1,0)};
		}
		return {mark[0][s-1], (s+e)/2, hyp((s+e)/2-s+1, 1)};
	}
	puts("dead end");
	assert(0);
	return {-1, -1, -1};
}
 
priority_queue<obj> ones;
set<pair<obj, pi> > pq;
map<pi, obj> mp;

void pq_insert(pi x){
	mp[x] = cost_calc(x.first, x.second);
	pq.insert(make_pair(mp[x], x));
	s.insert(x);
}
 
void pq_erase(set<pi> ::iterator it){
	pq.erase(make_pair(mp[*it], *it));
	mp.erase(mp.find(*it));
	s.erase(it);
}

void pq_norm(int x){
	auto t = s.lower_bound(pi(x, -1e9));
	auto u = s.lower_bound(pi(x, -1e9));
	if(u != s.begin()){
		pi intv = *--u;
		pq_erase(u);
		pq_insert(intv);
	}
	if(t != s.end()){
		pi intv = *t;
		pq_erase(t);
		pq_insert(intv);
	}
}
 
int main(){
	cin >> n >> q;
	char buf[5];
	pq_insert(pi(1, n));
	occu[0] = occu[n+1] = 1;
	for(int i=1; i<=q; i++){
		scanf("%s",buf);
		if(*buf == 'E'){
			obj ret = {-1, -1, -1};
			if(!pq.empty()) ret = (*--pq.end()).first;
			while(!ones.empty() && (occu[ones.top().y] != 1 || mark[ones.top().x][ones.top().y])) ones.pop();
			if(!ones.empty()) ret = max(ret, ones.top());
			arr[i] = pi(ret.x, ret.y);
			mark[arr[i].first][arr[i].second] = 1;
			printf("%d %d\n",arr[i].second, arr[i].first + 1);
			occu[arr[i].second]++;
			if(occu[arr[i].second] == 2){
				pq_norm(arr[i].second);
			}
			if(occu[arr[i].second] == 1){
				occu[arr[i].second]--;
				ones.push({mark[0][arr[i].second], arr[i].second, 1});
				auto t = --s.lower_bound(pi(arr[i].second, 1e9));
				pi intv = *t;
				pq_erase(t);
				occu[arr[i].second]++;
				if(intv.first < arr[i].second) pq_insert(pi(intv.first, arr[i].second-1));
				if(arr[i].second < intv.second) pq_insert(pi(arr[i].second+1, intv.second));
			}
		}
		else if(*buf == 'L'){
			int p;
			scanf("%d",&p);
			mark[arr[p].first][arr[p].second] = 0;
			occu[arr[p].second]--;
			if(occu[arr[p].second] == 1){
				pq_norm(arr[p].second);
				ones.push({mark[0][arr[p].second], arr[p].second, 1});
			}
			if(!occu[arr[p].second]){
				if(occu[arr[p].second-1] && occu[arr[p].second+1]){
					pq_insert(pi(arr[p].second, arr[p].second));
				}
				else if(!occu[arr[p].second-1] && !occu[arr[p].second+1]){
					auto lo = --s.lower_bound(pi(arr[p].second, 1e9));
					auto hi = lo;
					hi++;
					pq_insert(pi(lo->first, hi->second));
					pq_erase(lo);
					pq_erase(hi);
				}
				else if(!occu[arr[p].second-1]){
					auto lo = --s.lower_bound(pi(arr[p].second, 1e9));
					pq_insert(pi(lo->first, lo->second+1));
					pq_erase(lo);
				}
				else if(!occu[arr[p].second+1]){
					auto hi = s.lower_bound(pi(arr[p].second, 1e9));
					pq_insert(pi(hi->first-1, hi->second));
					pq_erase(hi);
				}
			}
		}
	}
}