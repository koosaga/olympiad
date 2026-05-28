#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
#define all(v) (v).begin(), (v).end()
#define sz(v) ((int)(v).size())
const int MAXN = 500005;
const int mod1 = 1e9 + 696969;
const int mod2 = 993244853;

int n;
char str[MAXN];
lint h1[MAXN], h2[MAXN], p1[MAXN], p2[MAXN];

lint Mod(lint x, int mod){
	x %= mod;
	if(x < 0) x += mod;
	return x;
}

int ptr[MAXN], occ[MAXN], vis[MAXN];
lint A[MAXN], B[MAXN];

int solve(int m){
	p1[0] = p2[0] = 1;
	for(int i = 1; i <= n; i++){
		h1[i] = (h1[i - 1] * 257 + str[i]) % mod1;
		h2[i] = (h2[i - 1] * 257 + str[i]) % mod2;
		p1[i] = (p1[i - 1] * 257) % mod1;
		p2[i] = (p2[i - 1] * 257) % mod2;
	}
	vector<lint> vect;
	for(int i = m; i <= n; i++){
		lint v1 = h1[i] - h1[i - m + 1] * p1[m - 1];
		lint v2 = h2[i] - h2[i - m + 1] * p2[m - 1];
		v1 = Mod(v1, mod1);
		v2 = Mod(v2, mod2);
		lint a1 = str[i - m + 1] * p1[m - 1] + v1;
		lint a2 = str[i - m + 1] * p2[m - 1] + v2;
		lint b1 = v1 * 257 + str[i - m + 1];
		lint b2 = v2 * 257 + str[i - m + 1];
		A[i] = Mod(a1, mod1) * mod2 + Mod(a2, mod2);
		B[i] = Mod(b1, mod1) * mod2 + Mod(b2, mod2);
		vect.push_back(A[i]);
	}
	sort(all(vect));
	vect.resize(unique(all(vect)) - vect.begin());
	memset(ptr, -1, sizeof(ptr));
	memset(occ, 0, sizeof(occ));
	memset(vis, 0, sizeof(vis));
	for(int i = m; i <= n; i++){
		if(!binary_search(all(vect), B[i])) continue;
		int cur = lower_bound(all(vect), A[i]) - vect.begin();
		int nxt = lower_bound(all(vect), B[i]) - vect.begin();
		ptr[cur] = nxt;
		occ[cur]++;
	}
	int ret = 0;
	for(int i = 0; i < sz(vect); i++){
		if(!vis[i]){
			int pos = i;
			int occsum = 0;
			while(pos != -1 && !vis[pos]){
				vis[pos] = 1;
				occsum += occ[pos];
				pos = ptr[pos];
			}
			if(pos != i) continue;
			ret = max(ret, occsum);
		}
	}
	return ret;
}

int main(){
	int q;
	scanf("%d %d",&n,&q);
	scanf("%s", str + 1);
	while(q--){
		int m; scanf("%d",&m);
		printf("%d\n", solve(m));
	}
}
