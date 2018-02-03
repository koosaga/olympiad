#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 200005;
const int mod = 1e9 + 7;

struct seg{
	int tree[530000], lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		memset(tree, 0x3f, sizeof(tree));
	}
	void add(int x, int v){
		x += lim;
		tree[x] = min(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 1e9;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg1, seg2;

namespace sfxarray{
	void solve(int n, int *str, int *sfx, int *rev, int *lcp){
		iota(sfx, sfx + n, 0);
		sort(sfx, sfx + n, [&](const int &a, const int &b){
			for(int i=0; ; i++){
				if(str[i + a] != str[i + b]) return str[i + a] < str[i + b];
			}
			return false;
		});
		for(int i=0; i<n; i++) rev[sfx[i]] = i;
		for(int i=0; i<n; i++){
			if(rev[i]){
				int h = 0;
				int j = sfx[rev[i] - 1];
				while(str[h + i] == str[h + j]) h++;
				lcp[rev[i]] = h;
			}
		}
	}
};

int str[MAXN], sfx[MAXN], rev[MAXN], lcp[18][MAXN];

char buf[MAXN];
int p;

lint solve(int x, int l, int ie){
	int s = 0, e = l+1;
	while(s != e){
		int m = (s+e)/2;
		int st = rev[x];
		int ed = rev[x]+1;
		for(int i=17; i>=0; i--){
			if(st >= (1<<i) && lcp[i][st] >= m) st -= (1<<i);
			if(ed + (1<<i) <= p && lcp[i][ed + (1<<i)-1] >= m) ed += (1<<i);
		}
		if(seg1.query(st, ed-1) < x || -seg2.query(st, ed-1) >= ie) s = m+1;
		else e = m;
	}
	return l+1-s;
}

int n;
int main(){
	freopen("standingout.in", "r", stdin);
	freopen("standingout.out", "w", stdout);
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%s",buf);
		for(int j=0; buf[j]; j++){
			str[p++] = buf[j];
		}
		str[p++] = i + 256;
	}
	seg1.init(p);
	seg2.init(p);
	sfxarray::solve(p, str, sfx, rev, lcp[0]);
	for(int i=0; i<p; i++) seg1.add(i, sfx[i]);
	for(int i=0; i<p; i++) seg2.add(i, -sfx[i]);
	for(int i=1; i<18; i++){
		for(int j=1; j<p; j++){
			lcp[i][j] = lcp[i-1][j];
			if(j > (1<<(i-1))) lcp[i][j] = min(lcp[i][j], lcp[i-1][j - (1<<(i-1))]);
		}
	}
	int cur = 0;
	for(int i=0; i<n; i++){
		int nxt = cur;
		while(str[nxt] < 256) nxt++;
		lint ans = 0;
		for(int j=cur; j<nxt; j++) ans += solve(j, nxt - j, nxt);
		printf("%lld\n", ans);
		cur = nxt + 1;
	}
}
