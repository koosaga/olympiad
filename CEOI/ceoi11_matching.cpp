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

int n, m, a[1000005], b[1000005];
int lp[1000005], rp[1000005], fail[1000005];

bool ins1(int x, int p){
	return a[x - lp[p]] <= a[x] && a[x] <= a[x - rp[p]];
}

bool ins2(int x, int p){
	return b[x - lp[p]] <= b[x] && b[x] <= b[x - rp[p]];
}

int nxtl[1000005], nxtr[1000005], r[1000005];

int fl(int x){
	if(x < 0) return x;
	return nxtl[x] = (nxtl[x] == x ? x : fl(nxtl[x]));
}

int fr(int x){
	if(x >= n) return x;
	return nxtr[x] = (nxtr[x] == x ? x : fr(nxtr[x]));
}

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++){
		int v;
		scanf("%d",&v);
		a[v-1] = i;
		r[i] = v-1;
		nxtl[i] = nxtr[i] = i;
	}
	for(int i=n-1; i>=0; i--){
		nxtl[a[i]] = fl(a[i] - 1);
		nxtr[a[i]] = fr(a[i] + 1);
		if(nxtr[a[i]] < n) rp[i] = i - r[nxtr[a[i]]];
		if(nxtl[a[i]] >= 0) lp[i] = i - r[nxtl[a[i]]];
	}
	int p = 0;
	for(int i=1; i<n; i++){
		while(p > 0 && !ins1(i, p)){
			p = fail[p];
		}
		if(ins1(i, p)) p++;
		fail[i+1] = p;
	}
	p = 0;
	vector<int> v;
	for(int i=0; i<m; i++){
		scanf("%d",&b[i]);
		while(p > 0 && !ins2(i, p)){
			p = fail[p];
		}
		if(ins2(i, p)) p++;
		if(p == n){
			v.push_back(i - n + 2);
			p = fail[p];
		}
	}
	printf("%d\n", v.size());
	for(auto &i : v) printf("%d ",i);
}
