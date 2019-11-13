#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using vect = bitset<128>;
using pi = pair<int, vect>;
#define sz(v) ((int)(v).size())
const int MAXN = 250005;
const int mod = 998244353;
 
vector<pi> indep;
vect basis[128], source[128];
 
void Do(pi x){
	vect cur = x.second;
	vect src = 0;
	for(int j=0; j<128; j++){
		if(cur[j]){
			if(basis[j].any()){
				cur ^= basis[j];
				src ^= source[j];
			}
			else{
				src.set(sz(indep));
				basis[j] = cur;
				source[j] = src;
				indep.push_back(x);
				return; // insert success
			}
		}
	}
	pair<int, int> ret(2e9, -1);
	for(int j=0; j<sz(indep); j++){
		if(src[j]){
			ret = min(ret, make_pair(indep[j].first, j));
		}
	}
	if(x.first < ret.first) return;
	src[ret.second] = 0;
	indep[ret.second] = x;
	for(int j=0; j<128; j++){
		if(source[j][ret.second]){
			source[j] ^= src;
		}
	}
}
 
int q;
int main(){
	scanf("%*d %d",&q);
	for(int i=0; i<q; i++){
		int s, e, x;
		lint msk;
		scanf("%d %d %lld %d",&s,&e,&msk,&x);
		vect bs = msk;
		bs.set(s + 59); bs.set(e + 59);
		Do(pi(x, bs));
		lint ret = 0;
		for(auto &j : indep) ret += j.first;
		printf("%lld\n", ret);
	}
}
