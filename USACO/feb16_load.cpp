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
#include <assert.h>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int lim = 1000000;

int n;
pi a[100005];

struct bit{
	int tree[1000005];
	int sz;
	void init(){
		sz = 0;
		memset(tree, 0, sizeof(tree));
	}
	int size(){
		return sz;
	}
	void add(int x, int v){
		sz += v;
		while(x <= lim){
			tree[x] += v;
			x += x & -x;
		}
	}
	int kth(int p){
		int pos = 0;
		for(int i=19; i>=0; i--){
			if((pos | (1<<i)) <= lim && tree[pos|(1<<i)] < p){
				pos |= (1<<i);
				p -= tree[pos];
			}
		}
		return pos;
	}
}p1, p2;

bool cross(int x){
	if(p1.size() > 2 * x || p2.size() > 2 * x) return 0;
	if(p1.size() <= x || p2.size() <= x) return 1;
	int s1 = p1.kth(min(x, p1.size()-x)) + 1;
	int e1 = p1.kth(max(x, p1.size()-x) + 1) - 1;
	int s2 = p2.kth(min(x, p2.size()-x)) + 1;
	int e2 = p2.kth(max(x, p2.size()-x) + 1) - 1;
	return max(s1, s2) <= min(e1, e2);
}

int trial(int x){
	p1.init();
	p2.init();
	for(int i=0; i<n; i++){
		p2.add(a[i].second, 1);
	}
	if(cross(x)) return 1;
	for(int i=0; i<n; ){
		int e = i;
		while(e < n && a[i].first == a[e].first) e++;
		for(int j=i; j<e; j++){
			p1.add(a[j].second, 1);
			p2.add(a[j].second, -1);
		}
		if(cross(x)) return 1;
		i = e;
	}
	return 0;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
	}
	sort(a, a+n);
	int s = 0, e = n;
	while(s != e){
		int m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m+1;
	}
	printf("%d",s);
}