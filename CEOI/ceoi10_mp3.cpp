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

int n, m, e;
vector<int> cnd;
int b[100005], c[100005];
char t[3];

struct func{
	int ss, se, es, ee;
};

func merge(func l, func r){
	int gs = max(l.es, r.ss), ge = min(l.ee, r.se);
	if(gs > ge){
		if(l.ee < r.ss){
			return {0, 0, r.es, r.es};
			// 모두 
		}
		else if(r.se < l.es){
			return {0, 0, r.ee, r.ee};
		}
		// if(l.es )
	}
	int dx1 = l.es - l.ss, dx2 = r.es - r.ss;
	return {gs - dx1, ge - dx1, gs + dx2, ge + dx2};
}

struct seg{
	func tree[270000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 270000, (func){0, m, 0, m});
	}
	void add(int x, func v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = merge(tree[2*x], tree[2*x+1]);
		}
	}
}seg;

vector<pi> sweep;

int main(){
	cnd.push_back(2000000005);
	cin >> n >> m >> e;
	seg.init(n);
	for(int i=0; i<n; i++){
		scanf("%s %d",t, &c[i]);
		if(*t == '+') b[i] = 1;
		else b[i] = -1;
		if(i){
			cnd.push_back(c[i] - c[i-1] - 1);
			sweep.emplace_back(c[i] - c[i-1], i);
			if(b[i] == 1) seg.add(i, {0, m-1, 1, m});
			else seg.add(i, {1, m, 0, m-1});
		}
	}
	sort(cnd.begin(), cnd.end());
	cnd.resize(unique(cnd.begin(), cnd.end()) - cnd.begin());
	reverse(cnd.begin(), cnd.end());
	sort(sweep.begin(), sweep.end());
	reverse(sweep.begin(), sweep.end());
	int pnt = 0;
	for(auto &i : cnd){
		while(pnt < sweep.size() && sweep[pnt].first > i){
			seg.add(sweep[pnt++].second, {0, m, 0, m});
		}
		func t = seg.tree[1];
		if(t.es <= e && e <= t.ee){
			if(i > 2e9){
				puts("infinity");
				return 0;
			}
			int colp = t.ss + e - t.es;
			if(t.ee == e) colp = m;
			printf("%d %d\n",i, colp);
			return 0;
		}
	}
}