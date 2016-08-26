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
lint ps[2000005], ds[2000005];
bool dap1[1000005], dap2[1000005];

void solve(bool *p){
	deque<pi> dq;
	for(int i=1; i<=n; i++){
		while(!dq.empty() && dq.back().first >= ps[i-1] - ds[i-1]){
			dq.pop_back();
		}
		dq.push_back(pi(ps[i-1] - ds[i-1], i));
	}
	for(int i=1; i<=n; i++){
		while(!dq.empty() && dq.back().first >= ps[i+n-1] - ds[i+n-1]){
			dq.pop_back();
		}
		dq.push_back(pi(ps[i+n-1] - ds[i+n-1], i+n));
		if(!dq.empty() && dq.front().first < ps[i-1] - ds[i-1]) p[i] = 0;
		else p[i] = 1;
		if(!dq.empty() && dq.front().second == i) dq.pop_front();
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&p[i], &d[i]);
	}
	for(int i=1; i<=n; i++){
		ps[i] = ps[i-1] + p[i];
		ds[i] = ds[i-1] + d[i];
	}
	for(int i=n+1; i<=2*n; i++){
		ps[i] = ps[n] + ps[i-n];
		ds[i] = ds[n] + ds[i-n];
	}
	solve(dap1);
	reverse(p+1, p+n+1);
	reverse(d+1, d+n+1);
	rotate(d+1, d+2, d+n+1);
	for(int i=1; i<=n; i++){
		ps[i] = ps[i-1] + p[i];
		ds[i] = ds[i-1] + d[i];
	}
	for(int i=n+1; i<=2*n; i++){
		ps[i] = ps[n] + ps[i-n];
		ds[i] = ds[n] + ds[i-n];
	}
	solve(dap2);
	for(int i=1; i<=n; i++){
		if(dap1[i] || dap2[n+1-i]) puts("TAK");
		else puts("NIE");
	}
}
