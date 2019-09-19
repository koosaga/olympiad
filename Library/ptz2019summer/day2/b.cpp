#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)((v).size()))
const int MAXN = 300005;
const int MAXT = 20000005;
const int mod = 998244353;
 
int n;
lint x, a[MAXN];
int trie[MAXT][2], sz[MAXT], piv;
 
int query(lint val, int pos, int dep){
	if(dep == -1) return sz[pos];
	int cbit = (val >> dep) & 1;
	int ret = 0;
	if((x >> dep) & 1){
		if(trie[pos][cbit ^ 1]){
			ret += query(val, trie[pos][cbit ^ 1], dep - 1);
		}
	}
	else{
		if(trie[pos][cbit ^ 1]){
			ret += sz[trie[pos][cbit ^ 1]];
		}
		if(trie[pos][cbit]) ret += query(val, trie[pos][cbit], dep - 1);
	}
	return ret;
}
 
void insert(lint x){
	sz[0]++;
	int pos = 0;
	for(int j=59; j>=0; j--){
		int val = (x >> j) & 1;
		if(!trie[pos][val]){
			trie[pos][val] = ++piv;
		}
		pos = trie[pos][val];
		sz[pos]++;
	}
}
 
lint solve(vector<lint> v){
	lint ret = 1 + sz(v);
	for(auto &i : v){
		ret += query(i, 0, 59);
		insert(i);
	}
	for(int i=0; i<=piv; i++){
		trie[i][0] = trie[i][1] = sz[i] = 0;
	}
	piv = 0;
	return ret % mod;
}
 
map<lint, vector<lint>> grp;
 
int main(){
	scanf("%d %lld",&n,&x);
	if(x == 0){
		lint ans = 1;
		for(int i=0; i<n; i++) ans = ans * 2 % mod;
		ans = (ans + mod - 1) % mod;
		cout << ans << endl;
		return 0;
	}
	int lstbit = 60;
	while((x >> lstbit) == 0) lstbit--;
	lstbit++;
	for(int i=0; i<n; i++){
		scanf("%lld",&a[i]);
		lint j = (a[i] >> lstbit);
		grp[j].push_back(a[i]);
	}
	lint ret = 1;
	for(auto &i : grp){
		ret *= solve(i.second);
		ret %= mod;
	}
	ret = (ret + mod - 1) % mod;
	cout << ret << endl;
}
