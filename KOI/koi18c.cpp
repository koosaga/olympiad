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
const int MAXN = 300005;
const int mod = 1e9 + 7;

struct tup{
	int x, y, z;
	bool operator<(const tup &t)const{
		return x < t.x;
	}
}a[MAXN];

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		x++;
		while(x < MAXN){
			tree[x] = max(tree[x], v);
			x += x & -x;
		}
	}
	void flush(int x){
		x++;
		while(x < MAXN){
			tree[x] = 0;
			x += x & -x;
		}
	}
	int query(int x){
		x++;
		int ret = 0;
		while(x){
			ret = max(ret, tree[x]);
			x -= x & -x;
		}
		return ret;
	}
}bit;

int dp[MAXN];

void solve(int s, int e){
	if(s == e){
		dp[s]++;
		return;
	}
	int m = (s+e)/2;
	solve(s, m);
	vector<tup> v, w;
	for(int i=s; i<=m; i++) v.push_back((tup){a[i].y, a[i].z, dp[i]});
	for(int i=m+1; i<=e; i++) w.push_back((tup){a[i].y, a[i].z, i});
	int ptr = 0;
	sort(v.begin(), v.end());
	sort(w.begin(), w.end());
	for(auto &i : w){
		while(ptr < v.size() && v[ptr].x < i.x){
			bit.add(v[ptr].y, v[ptr].z);
			ptr++;
		}
		dp[i.z] = max(dp[i.z], bit.query(i.y - 1));
	}
	for(int i=0; i<ptr; i++) bit.flush(v[i].y);
	solve(m + 1, e);
}

int main(){
	int m, n;
	scanf("%d %d",&m,&n);
	for(int i=0; i<n; i++) scanf("%d",&a[i].x);
	for(int i=0; i<n; i++) scanf("%d",&a[i].y);
	if(m == 3) for(int i=0; i<n; i++) scanf("%d",&a[i].z);
	sort(a, a+n);
	if(m == 2) for(int i=0; i<n; i++) a[i].z = i;
	vector<int> vy, vz;
	for(int i=0; i<n; i++){
		vy.push_back(a[i].y);
		vz.push_back(a[i].z);
	}
	sort(vy.begin(), vy.end());
	sort(vz.begin(), vz.end());
	for(int i=0; i<n; i++){
		int yv = lower_bound(vy.begin(), vy.end(), a[i].y) - vy.begin();
		int zv = lower_bound(vz.begin(), vz.end(), a[i].z) - vz.begin();
		a[i].y = yv;
		a[i].z = zv;
	}
	solve(0, n-1);
	cout << *max_element(dp, dp + n) << endl;
}
