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

const int MAXN = 400005;
struct sfxarray{
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
	void init(int n, int *str, int *sfx, int *rev, int *lcp){
		int p = 1;
		for(int i=0; i<n; i++){
			sfx[i] = i;
			ord[i] = str[i];
		}
		int pnt = 1;
		while(1){
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++){
				cnt[ord[min(i+p, n)]]++;
			}
			for(int i=1; i<=n; i++){
				cnt[i] += cnt[i-1];
			}
			for(int i=n-1; i>=0; i--){
				aux[--cnt[ord[min(i+p, n)]]] = i;
			}
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++){
				cnt[ord[i]]++;
			}
			for(int i=1; i<=n; i++){
				cnt[i] += cnt[i-1];
			}
			for(int i=n-1; i>=0; i--){
				sfx[--cnt[ord[aux[i]]]] = aux[i];
			}
			if(pnt == n) break;
			pnt = 1;
			nord[sfx[0]] = 1;
			for(int i=1; i<n; i++){
				if(ord[sfx[i-1]] != ord[sfx[i]] || ord[sfx[i-1] + p] != ord[sfx[i] + p]){
					pnt++;
				}
				nord[sfx[i]] = pnt;
			}
			memcpy(ord, nord, sizeof(int) * n);
			p *= 2;
		}
		for(int i=0; i<n; i++){
			rev[sfx[i]] = i;
		}
		int h = 0;
		for(int i=0; i<n; i++){
			if(rev[i]){
				int prv = sfx[rev[i] - 1];
				while(str[prv + h] == str[i + h]) h++;
				lcp[rev[i]] = h;
			}
			h = max(h-1, 0);
		}
	}
}sfxarray;

int n, a[400005];
int sfx[400005], rev[400005], lcp[400005];

struct disj{
	int pa[200005];
	void init(int n){
		for(int i=0; i<=n; i++){
			pa[i] = i;
		}
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

struct rmq{
	int tree[1050000], lim;
	void init(int n, int *a){
		for(lim = 1; lim <= n; lim <<= 1);
		memset(tree, 0x3f, sizeof(tree));
		for(int i=0; i<n; i++){
			tree[i + lim] = a[i];
		}
		for(int i=lim-1; i; i--){
			tree[i] = min(tree[2*i], tree[2*i+1]);
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
}rmq;

int solve(int x){
	vector<pi> v;
	int sz = 0;
	for(int i=0; i*x+x-1<n; i++){
		v.push_back(pi(rev[i*x], i));
		v.push_back(pi(rev[2*n-i*x-x+1], i));
		sz++;
	}
	disj.init(sz);
	int ret = sz;
	sort(v.begin(), v.end());
	for(int i=1; i<v.size(); i++){
		if(rmq.query(v[i-1].first + 1, v[i].first) >= x){
			if(disj.uni(v[i-1].second, v[i].second)) ret--;
		}
	}
	return ret;
}

int ret[200005];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
		a[2*n-i] = a[i];
	}
	a[n] = n+1;
	sfxarray.init(2*n+1, a, sfx, rev, lcp);
	rmq.init(2*n+1, lcp);
	for(int i=1; i<=n; i++){
		ret[i] = solve(i);
	}
	int maxv = *max_element(ret+1, ret+n+1);
	printf("%d %d\n", maxv, count(ret+1, ret+n+1, maxv));
	for(int i=1; i<=n; i++){
		if(ret[i] == maxv) printf("%d ", i);
	}
}

