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

int n, p[1000005], d[1000005];
lint ps[1000005], ds[1000005];
bitset<1000005> dap1, dap2;

void solve(bitset<1000005> &p){
	deque<pi> dq;
	lint q = ps[n] - ds[n];
	for(int i=1; i<=n; i++){
		while(!dq.empty() && dq.back().first >= ps[i-1] - ds[i-1]){
			dq.pop_back();
		}
		dq.push_back(pi(ps[i-1] - ds[i-1], i));
	}
	for(int i=1; i<=n; i++){
		while(!dq.empty() && dq.back().first >= q + ps[i-1] - ds[i-1]){
			dq.pop_back();
		}
		dq.push_back(pi(q + ps[i-1] - ds[i-1], i+n));
		if(!dq.empty() && dq.front().first < ps[i-1] - ds[i-1]) p[i] = 0;
		else p[i] = 1;
		if(!dq.empty() && dq.front().second == i) dq.pop_front();
	}
}
static char buf[1 << 19]; // size : any number geq than 1024
static int idx = 0;
static int bytes = 0;
static inline int _read() {
	if (!bytes || idx == bytes) {
		bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
		idx = 0;
	}
	return buf[idx++];
}
static inline int _readInt() {
	int x = 0, s = 1;
	int c = _read();
	while (c <= 32) c = _read();
	if (c == '-') s = -1, c = _read();
	while (c > 32) x = 10 * x + (c - '0'), c = _read();
	if (s < 0) x = -x;
	return x;
}

int main(){
	n = _readInt();
	for(int i=1; i<=n; i++){
		p[i] = _readInt();
		d[i] = _readInt();
	}
	for(int i=1; i<=n; i++){
		ps[i] = ps[i-1] + p[i];
		ds[i] = ds[i-1] + d[i];
	}
	solve(dap1);
	reverse(p+1, p+n+1);
	reverse(d+1, d+n+1);
	rotate(d+1, d+2, d+n+1);
	for(int i=1; i<=n; i++){
		ps[i] = ps[i-1] + p[i];
		ds[i] = ds[i-1] + d[i];
	}
	solve(dap2);
	for(int i=1; i<=n; i++){
		if(dap1[i] || dap2[n+1-i]) puts("TAK");
		else puts("NIE");
	}
}
