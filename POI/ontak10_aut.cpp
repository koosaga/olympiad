#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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

int n, m, q;
vector<int> gph[100005];
pi b[100005];
int din[100005], dout[100005], piv;

struct bit{
	int tree[100005];
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
	int query(int s, int e){
		return query(e) - query(s-1);
	}
}bit;

void dfs(int x){
	din[x] = ++piv;
	for(int ii=0; ii<gph[x].size(); ii++){
		int i = gph[x][ii];
		gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
		dfs(i);
	}
	dout[x] = piv; 
}

bool sub(int s, int e){return din[s] <= din[e] && dout[e] <= dout[s];}
bool cmp(int x, int y){return din[x] < din[y];}

int ret[500005];

struct sweep{
	int s, e, x, idx, buho;
	bool operator<(const sweep &s)const{
		return x < s.x;
	}
};

vector<sweep> swp;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s, &e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1);
	scanf("%d",&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		s = din[s], e = din[e];
		if(s > e) swap(s, e);
		b[i] = pi(s, e);
	}
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		if(din[s] > din[e]) swap(s, e);
		if(sub(s, e)){
			int p = *--upper_bound(gph[s].begin(), gph[s].end(), e, cmp);
			swp.push_back((sweep){din[e], dout[e], din[p] - 1, i, 1});
			swp.push_back((sweep){dout[p] + 1, n, din[e] - 1, i, -1});
			swp.push_back((sweep){dout[p] + 1, n, dout[e], i, 1});
		}
		else{
			swp.push_back((sweep){din[e], dout[e], din[s] - 1, i, -1});
			swp.push_back((sweep){din[e], dout[e], dout[s], i, 1});
		}
	}
	sort(b, b+m);
	sort(swp.begin(), swp.end());
	int p = 0;
	for(int i=0; i<swp.size(); i++){
		while(p < m && b[p].first <= swp[i].x){
			bit.add(b[p].second, 1);
			p++;
		}
		ret[swp[i].idx] += swp[i].buho * bit.query(swp[i].s, swp[i].e);
	}
	for(int i=0; i<q; i++) printf("%d\n", 1 + ret[i]);
}
