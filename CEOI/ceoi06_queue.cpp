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
const int inf = 1e9;
 
map<int, int> nxt, prv, low;
 
int getprv(int x){
	if(prv.find(x) != prv.end()) return prv[x];
	return x - 1;
}
 
int getnxt(int x){
	if(nxt.find(x) != nxt.end()) return nxt[x];
	return x + 1;
}
 
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int a, b;
		scanf("%d %d",&a,&b);
		int pa = getprv(a);
		int na = getnxt(a);
		nxt[pa] = na;
		prv[na] = pa;
		int pb = getprv(b);
		nxt[pb] = a;
		prv[a] = pb;
		nxt[a] = b;
		prv[b] = a;
	}
	vector<pi> interval;
	vector<int> length;
	int p = 0;
	while(1){
		auto t = nxt.lower_bound(p);
		if(t == nxt.end()){
			interval.emplace_back(p, inf);
			break;
		}
		interval.emplace_back(p, t->first);
		p = t->second;
	}
	int cnt = 0;
	for(auto &i : interval){
		low[i.first] = cnt;
		cnt += i.second - i.first + 1;
		length.push_back(cnt);
	}
	int q;
	scanf("%d",&q);
	while(q--){
		char buf[5];
		int x;
		scanf("%s %d",buf,&x);
		if(*buf == 'L'){
			x++;
			int p = lower_bound(length.begin(), length.end(), x) - length.begin();
			if(p) x -= length[p-1];
			printf("%d\n",interval[p].first + x - 1);
		}
		else{
			int cnt = 0;
			auto p = --low.upper_bound(x);
			printf("%d\n", p->second + x - p->first);
		}
	}
}