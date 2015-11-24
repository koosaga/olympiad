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

struct rmq{
	int tree[132000], lim;
	void init(int n, int *a){
		for(lim = 1; lim <= n; lim <<= 1);
		memset(tree,0x3f,sizeof(tree));
		for(int i=1; i<=n; i++){
			tree[i+lim] = a[i];
		}
		for(int i=lim; i; i--){
			tree[i] = min(tree[2*i], tree[2*i+1]);
		}
	}
	int q(int s, int e){
		s += lim;
		e += lim;
		int ret = 1e9;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}rmq1, rmq2;

int n, q, a[50005];
int main(){
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	rmq1.init(n, a);
	for(int i=1; i<=n; i++) a[i] = -a[i];
	rmq2.init(n, a);
	while(q--){
		int s, e;
		scanf("%d %d",&s,&e);
		printf("%d\n",-rmq2.q(s, e) - rmq1.q(s, e));
	}
}