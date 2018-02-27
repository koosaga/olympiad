#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 782 * 64;
typedef unsigned long long fuck;

struct fuckstl{
	fuck E[782];
	void set(int x){
		E[x >> 6] |= (1ull << (x & 63));
	}
	void negate(){
		for(int i=0; i<782; i++) E[i] = ~E[i];
	}
	void get(vector<int> &v, int n){
		for(int i=0; i<782; i++){
			while(E[i]){
				int p = __builtin_ctzll(E[i]);
				E[i] ^= (1ull << p);
				v.push_back((i << 6) | p);
			}
		}
		while(v.size() && v.back() >= n) v.pop_back();
	}
}bs[5][75], gibon;

fuckstl operator|(const fuckstl &a, const fuckstl &b){
	fuckstl fucking_ret;
	for(int i=0; i<782; i++) fucking_ret.E[i] = a.E[i] | b.E[i];
	return fucking_ret;
}

int n, a[MAXN][5];
char buf[10];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		gibon.set(i);
		scanf("%s", buf);
		for(int j=0; j<5; j++){
			a[i][j] = buf[j] - 48;
			bs[j][a[i][j]].set(i);
		}
	}
	vector<pi> ans;
	for(int i=0; i<n; i++){
		fuckstl na = bs[0][a[i][0]] | bs[1][a[i][1]] | bs[2][a[i][2]] | bs[3][a[i][3]] | bs[4][a[i][4]];
		na.negate();
		vector<int> v;
		na.get(v, n);
		for(auto &j : v){
			if(j < i){
				ans.push_back(pi(j, i));
			}
			else break;
		}
		if(ans.size() >= 100000) break;
	}
	while(ans.size() > 100000) ans.pop_back();
	printf("%d\n", ans.size());
	for(auto &i : ans) printf("%d %d\n", i.first+1, i.second+1);
}
