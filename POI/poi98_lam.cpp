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

int n; 
pi a[30005];

struct seg{
	int tree[130000], lim;
	void init(){
		memset(tree, 0, sizeof(tree));
		lim = (1<<16);
	}
	void add(int x, int v){
		x += lim;
		tree[x] = max(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 0;
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg;

int main(){
	int t;
	cin >> t;
	while(t--){
		int dp[30005];
		cin >> n;
		for(int i=0; i<n; i++){
			int x, y;
			scanf("%d %d",&x,&y);
			x++, y++;
			a[i] = pi(y-x, x+y);
		}
		seg.init();
		sort(a, a+n);
		for(int i=0; i<n; ){
			int e = i;
			while(e < n && a[e].first == a[i].first) e++;
			for(int j=i; j<e; j++){
				dp[j] = seg.query(0, a[j].second - 1) + 1;
			}
			for(int j=i; j<e; j++){
				seg.add(a[j].second, dp[j]);
			}
			i = e;
		}
		cout << *max_element(dp, dp+n) << endl;
	}
}

