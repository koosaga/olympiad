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
const int N = 15000;

bool gph[N+5][3];

struct node{
	bool a00, a01, a10, a11;
};

node merge(node a, node b){
	node c;
	c.a00 = (a.a00 && b.a00) || (a.a01 && b.a10);
	c.a01 = (a.a00 && b.a01) || (a.a01 && b.a11);
	c.a10 = (a.a10 && b.a00) || (a.a11 && b.a10);
	c.a11 = (a.a11 && b.a11) || (a.a10 && b.a01);
	return c;
}

node getnode(int x){
	if(x % 2 == 0){
		return (node){1, gph[x/2][1], gph[x/2][1], 1};
	}
	else{
		return (node){gph[x/2][0], 0, 0, gph[x/2][2]};
	}
}

struct seg{
	node tree[66000];
	int lim;
	void init(int n){
		lim = (1 << 15);
		fill(tree, tree + 66000, (node){1, 0, 0, 1});
		for(int i=0; i<n; i++){
			tree[i+lim] = getnode(i);
		}
		for(int i=lim-1; i; i--){
			tree[i] = merge(tree[2*i], tree[2*i+1]);
		}
	}
	void update(int x){
		x += lim;
		tree[x] = getnode(x - lim);
		while(x > 1){
			x >>= 1;
			tree[x] = merge(tree[2*x], tree[2*x+1]);
 		}
	}
	node query(int s, int e){
		s += lim;
		e += lim;
		node ls, rs;
		ls = rs = (node){1, 0, 0, 1};
		while(s < e){
			if(s%2 == 1) ls = merge(ls, tree[s++]);
			if(e%2 == 0) rs = merge(tree[e--], rs);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ls = merge(ls, tree[s]);
		return merge(ls, rs);
	}
}seg;

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int r1, c1, r2, c2;
		scanf("%d %d %d %d",&c1,&r1,&c2,&r2);
		r1--;
		c1--;
		r2--;
		c2--;
		gph[min(r1, r2)][c1 + c2] = 1;
	}
	seg.init(2*N-1);
	char buf[5];
	while(1){
		scanf("%s",buf);
		if(*buf == 'E') break;
		int r1, c1, r2, c2;
		scanf("%d %d %d %d",&c1,&r1,&c2,&r2);
		r1--;
		c1--;
		r2--;
		c2--;
		if(*buf == 'T'){
			if(r1 > r2){
				swap(r1, r2);
				swap(c1, c2);
			}
			node t = seg.query(2*r1, 2*r2);
			bool ret = 0;
			if(c1 == 0 && c2 == 0){
				ret = t.a00;
			}
			if(c1 == 0 && c2 == 1){
				ret = t.a01;
			}
			if(c1 == 1 && c2 == 0){
				ret = t.a10;
			}
			if(c1 == 1 && c2 == 1){
				ret = t.a11;
			}
			puts(ret ? "Y" : "N");
		}
		else{
			gph[min(r1, r2)][c1 + c2] = (*buf == 'O');
			if(c1 != c2){
				seg.update(2*r1);
			}
			else{
				seg.update(2*min(r1, r2)+1);
			}
		}
	}
}