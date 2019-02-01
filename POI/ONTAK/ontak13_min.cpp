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
typedef pair<lint, lint> pi;

static char _buffer[1024];
static int _currentChar = 0;
static int _charsNumber = 0;

static inline int _read() {
	if (_charsNumber < 0) {
		exit(1);
	}
	if (!_charsNumber || _currentChar == _charsNumber) {
		_charsNumber = (int)fread(_buffer, sizeof(_buffer[0]), sizeof(_buffer), stdin);
		_currentChar = 0;
	}
	if (_charsNumber <= 0) {
		return -1;
	}
	return _buffer[_currentChar++];
}

static inline lint _readInt() {
	lint c, x, s;
	c = _read();
	while (c <= 32) c = _read();
	x = 0;
	s = 1;
	if (c == '-') {
		s = -1;
		c = _read();
	}
	while (c > 32) {
		x *= 10;
		x += c - '0';
		c = _read();
	}
	if (s < 0) x = -x;
	return x;
}

lint x[100005], r[100005], n;
vector<lint> vx, v;

struct intv{
	lint s, e, x;
}a[100005];

lint lv[100005], rv[100005];
int fuck[100005];

set<int> s;

struct seg{
	pi tree[270000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2 * lim + 2, pi(-3e18, -3e18));
	}
	void add(int x, pi v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(-3e18, -3e18);
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

void dfs(int x, lint val, lint *r){
	s.insert(x);
	seg.add(fuck[a[x].x], pi(-3e18, -3e18));
	r[a[x].x] = val;
	lint cent = (a[x].s + a[x].e) / 2;
	lint cnt = upper_bound(v.begin(), v.end(), cent) - v.begin();
	while(1){
		pi p = seg.query(0, cnt-1);
		if(p.first >= cent){
			dfs(p.second, val, r);
		}
		else break;
	}
}

void solve(){
	for(int i=0; i<n; i++){
		a[i] = {x[i] - r[i], x[i] + r[i], i};   
	}
	for(int i=0; i<n; i++) v.push_back(a[i].s);
	sort(v.begin(), v.end());
	sort(a, a+n, [&](const intv &a, const intv &b){
			return a.s < b.s;
			});
	for(int i=0; i<n; i++){
		fuck[a[i].x] = i;
	}
	sort(a, a+n, [&](const intv &a, const intv &b){
			return a.e < b.e;
			});
	seg.init(n);
	for(int i=0; i<n; i++){
		seg.add(fuck[a[i].x], pi(a[i].e, i));
	}
	for(int i=n-1; i>=0; i--){
		if(s.find(i) == s.end()){
			dfs(i, a[i].e, rv);
		}
	}
	s.clear();
	sort(a, a+n, [&](const intv &a, const intv &b){
			return a.s < b.s;
			});
	seg.init(n);
	for(int i=0; i<n; i++){
		seg.add(fuck[a[i].x], pi(a[i].e, i));
	}
	for(int i=0; i<n; i++){
		if(s.find(i) == s.end()){
			dfs(i, a[i].s, lv);
		}
	}
	for(int i=0; i<n; i++){
		printf("%d",upper_bound(vx.begin(), vx.end(), rv[i])
				- lower_bound(vx.begin(), vx.end(), lv[i]));
		if(i != n-1) printf(" ");
	}
	s.clear();
	puts("");
}

int main(){
	int t = _readInt();
	while(t--){
		n = _readInt();
		for(int i=0; i<n; i++){
			x[i] = _readInt();
			r[i] = _readInt();
			vx.push_back(x[i]);
		}
		sort(vx.begin(), vx.end());
		solve();
		v.clear();
		vx.clear();
	}
}
