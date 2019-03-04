#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int mod = 1e9 + 7;
typedef long long lint;

int n, k;
int term[MAXN];
int trie[MAXN][26], piv;
char buf[MAXN];
string s[MAXN];
lint fact[MAXN];

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

int main(){
	fact[0] = 1;
	for(int i=1; i<MAXN; i++) fact[i] = fact[i-1] * i % mod;
	scanf("%d %d",&n,&k);
	for(int i=0; i<n; i++){
		scanf("%s", buf);
		s[i] = buf;
	}
	sort(s, s+n);
	for(int i=0; i<n; i++){
		int p =0;
		for(int j=0; j<s[i].size(); j++){
			if(!trie[p][s[i][j] - 'a']){
				trie[p][s[i][j] - 'a']= ++piv;
			}
			p = trie[p][s[i][j] - 'a'];
		}
		term[p] = i + 1;
	}
	scanf("%s", buf);
	vector<int> v;
	int p = 0;
	for(int i=0; buf[i]; i++){
		p = trie[p][buf[i] - 'a'];
		if(term[p]){
			v.push_back(term[p]);
			p = 0;
		}
	}
	assert(p == 0);
	assert(v.size() == k);
	for(int i=1; i<=n; i++) bit.add(i, 1);
	lint ans = 0;
	for(int i=0; i<v.size(); i++){
		ans += 1ll * bit.query(v[i] - 1) * fact[n-i-1] % mod;
		bit.add(v[i], -1);
	}
	ans %= mod;
	ans *= ipow(fact[n-k], mod - 2);
	ans %= mod;
	cout << (ans + 1) % mod;
}

