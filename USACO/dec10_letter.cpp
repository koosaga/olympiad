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

int n, m;
char str1[50005], str2[50005];

char buf[100005];
int ord[100005], nord[100005], h, p = 1;

int sfx[100005], lcp[100005], rev[100005];
int match[50005];

struct rmq{
	int tree[270000], lim;
	void init(int n){
		memset(tree, 0x3f, sizeof(tree));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int x, int v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
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

set<int> topgear;

void get_sfx(){
	for(int i=0; i<n; i++){
		buf[i] = str1[i];
	}
	buf[n] = max('z', 'Z') + 1;
	for(int i=0; i<m; i++){
		buf[n+1+i] = str2[i];
	}
	int s = n + m + 1;
	ord[s] = -1;
	for(int i=0; i<s; i++){
		ord[i] = buf[i];
		sfx[i] = i;
	}
	auto cmp = [&](const int &a, const int &b){
		if(ord[a] != ord[b]) return ord[a] < ord[b];
		return ord[a+p] < ord[b+p];
	};
	while(1){
		sort(sfx, sfx + s, cmp);
		if(2*p >= s) break;
		nord[sfx[0]] = 0;
		for(int i=1; i<s; i++){
			nord[sfx[i]] = nord[sfx[i-1]];
			if(cmp(sfx[i-1], sfx[i])) nord[sfx[i]]++;
		}
		p *= 2;
		for(int i=0; i<s; i++){
			ord[i] = nord[i];
		}
	}
	for(int i=0; i<s; i++){
		rev[sfx[i]] = i;
	}
	int p = 0;
	for(int i=0; i<s; i++){
		if(rev[i]){
			int p = sfx[rev[i] - 1];
			while(buf[i+h] == buf[p+h]) h++;
			lcp[rev[i]] = h;
		}
		h = max(h-1, 0);
	}
	for(int i=n+1; i<s; i++){
		topgear.insert(rev[i]);
	}
	rmq1.init(s);
	for(int i=1; i<s; i++){
		rmq1.add(i, lcp[i]);
	}
}

int main(){
	cin >> m >> n;
	int p = 0, q = 0;
	while(p < m){
		scanf("%s", buf);
		for(int j=0; buf[j]; j++){
			str2[p++] = buf[j];
		}
	}
	while(q < n){
		scanf("%s", buf);
		for(int j=0; buf[j]; j++){
			str1[q++] = buf[j];
		}
	}
	get_sfx();
	for(int i=0; i<n; i++){
		auto it = topgear.lower_bound(rev[i]);
		if(it != topgear.end()){
			match[i] = max(match[i], rmq1.query(rev[i] + 1, *it));
		}
		if(it != topgear.begin()){
			it--;
			match[i] = max(match[i], rmq1.query(*it + 1, rev[i]));
		}
	}
	rmq2.init(n);
	rmq2.add(n, 0);
	for(int i=n-1; i>=0; i--){
		int dp = rmq2.query(i+1, i + match[i]) + 1;
		rmq2.add(i, dp);
	}
	cout << rmq2.query(0, 0);
}
