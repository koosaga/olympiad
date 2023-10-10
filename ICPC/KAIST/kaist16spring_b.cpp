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
typedef pair<lint, int> pi;

int n, q, a[100005];

struct bit{
	int tree[100005];
	void add(int x, int v){
		while(x < n){
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
}bit;

int main(){
	cin >> n >> q;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		if(i > 1 && a[i-1] > a[i]) bit.add(i-1, 1);
	}
	while(q--){
		int p, l, r;
		scanf("%d %d %d",&p,&l,&r);
		if(p == 1){
			puts(bit.query(r-1) != bit.query(l-1) ? "HSS090" : "CS204");
		}
		else{
			set<int> s;
			s.insert(l);
			s.insert(l+1);
			s.insert(r);
			s.insert(r+1);
			for(auto &i : s){
				if(i > 1 && a[i-1] > a[i]){
					bit.add(i-1, -1);
				}
			}
			swap(a[l], a[r]);
			for(auto &i : s){
				if(i > 1 && a[i-1] > a[i]){
					bit.add(i-1, 1);
				}
			}
		}
	}
}