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

struct rmq{
	int tree[530000], lim;
	void init(int n){
		memset(tree, 0, sizeof(tree));
		for(lim = 1; lim <= n; lim <<= 1);
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
}rmq;

int n, a[200005];
int l[200005], r[200005];
vector<int> v;

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int ret = 0;
		v.clear();
		scanf("%d",&n);
		for(int i=0; i<n; i++){
			scanf("%d",&a[i]);
			v.push_back(a[i]);
		}
		l[0] = 1;
		for(int i=1; i<n; i++){
			if(a[i-1] < a[i]) l[i] = l[i-1] + 1;
			else l[i] = 1;
		}
		r[n-1] = 1;
		for(int i=n-2; i>=0; i--){
			if(a[i+1] > a[i]) r[i] = r[i+1] + 1;
			else r[i] = 1;
		}
		sort(v.begin(), v.end());
		for(int i=0; i<n; i++){
			a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
		}
		rmq.init(n);
		for(int i=0; i<n; i++){
			ret = max(ret, rmq.query(0, a[i] - 1) + r[i]);
			rmq.add(a[i], l[i]);
		}
		printf("%d\n",ret);
	}
}