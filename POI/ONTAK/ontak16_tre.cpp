#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

int n, lev[5000005], ans[5000005];
int le[5000005], ri[5000005];
pi a[5000005];
pi stk[5000005];
int sz;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i].first);
		a[i].second = i;
	}
	sort(a, a+n);
	for(int i=0; i<n; i++){
		while(sz > 0 && stk[sz-1].second > a[i].second) sz--;
		if(sz == 0) le[a[i].first] = -1;
		else le[a[i].first] = stk[sz-1].first;
		stk[sz++] = a[i];
	}
	sz = 0;
	for(int i=n-1; i>=0; i--){
		while(sz > 0 && stk[sz-1].second > a[i].second) sz--;
		if(sz == 0) ri[a[i].first] = -1;
		else ri[a[i].first] = stk[sz-1].first;
		stk[sz++] = a[i];
	}
	sort(a, a+n, [&](const pi &a, const pi &b){
		return a.second < b.second;
	});
	for(int i=0; i<n; i++){
		int p = a[i].first;
		if(~le[p]) lev[p] = max(lev[p], lev[le[p]] + 1);
		if(~ri[p]) lev[p] = max(lev[p], lev[ri[p]] + 1);
		ans[lev[p]]++;
	}
	for(int i=0; ans[i]; i++) printf("%d ", ans[i]);
}
