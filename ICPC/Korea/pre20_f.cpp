#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int mod = 1e9 + 7;
const int MAXN = 500005;

int n;
pi a[MAXN], b;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%lld %lld",&a[i].first,&a[i].second);
	scanf("%lld %lld",&b.first,&b.second);
	int msk = 0;
	for(int i=0; i<n; i++){
		a[i].first -= b.first;
		a[i].second -= b.second;
		lint x = (a[i].first + a[i].second);
		lint y = (a[i].first - a[i].second);
		if(x <= 0 && y <= 0) msk |= 1;
		if(x <= 0 && y >= 0) msk |= 2;
		if(x >= 0 && y <= 0) msk |= 4;
		if(x >= 0 && y >= 0) msk |= 8;
	}
	puts(msk == 15 ? "NO" : "YES");
}
