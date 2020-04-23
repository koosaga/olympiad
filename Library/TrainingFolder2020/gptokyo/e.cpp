#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int mod = 1e9 + 7;
const int MAXN = 200005;

bool solve(){
	lint n, s;
	vector<lint> a;
	scanf("%lld %lld",&n,&s);
	{
		int k; scanf("%d",&k);
		a.resize(k);
		for(auto &i : a) scanf("%lld",&i);
	}
	vector<lint> cnd = {s};
	while(n && sz(cnd)){
		if(n & 1){
			lint mxv = cnd.back();
			bitset<MAXN> bs1, bs2;
			for(auto &j : cnd) bs1[mxv - j] = 1;
			for(int j=0; j<sz(a); j++){
				bs2 ^= (bs1 << a[j]);
			}
			cnd.clear();
			for(int j=0; j<MAXN; j++){
				if(bs2[j]) cnd.push_back(mxv - j);
			}
			reverse(all(cnd));
		}
		n /= 2;
		vector<lint> ncnd;
		for(auto &j : cnd){
			if(j & 1) continue;
			if(sz(ncnd) && ncnd.back() == (j >> 1)) continue;
			ncnd.push_back(j >> 1);
		}
		cnd = ncnd;
	}
	return find(all(cnd), 0) != cnd.end();
}

int main(){
	int t; scanf("%d",&t);
	while(t--) puts(solve() ? "1" : "0");
}
