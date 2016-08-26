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
const int inf = 1e9;
const int MAXN = 500005;

struct sfxarray{
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
	void init(int n, char *str, int *sfx, int *rev, int *lcp){
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
			for(int i=1; i<=n || i<=255; i++){
				cnt[i] += cnt[i-1];
			}
			for(int i=n-1; i>=0; i--){
				aux[--cnt[ord[min(i+p, n)]]] = i;
			}
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++){
				cnt[ord[i]]++;
			}
			for(int i=1; i<=n || i<=255; i++){
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

int n;
char str[500005];
int sfx[500005], rev[500005], lcp[500005];
int dist[500005];
int arr[500005];

set<int> s;

struct seg{
	struct node{
		int dis, l, r;
	}tree[1050000];
	int lim;
	node merge(node &a, node &b){
		node ret;
		ret.dis = max({a.dis, b.dis, b.l - a.r});
		if(a.l == -inf) tie(ret.l, ret.r) = pi(b.l, b.r);
		else if(b.l == -inf) tie(ret.l, ret.r) = pi(a.l, a.r);
		else tie(ret.l, ret.r) = pi(a.l, b.r);
		return ret;
	}
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 1050000, (node){0, -inf, inf});
	}
	void add(int x){
		tree[x + lim] = {0, x, x};
		x += lim;
		while(x > 1){
			x >>= 1;
			tree[x] = merge(tree[2*x], tree[2*x+1]);
		}
	}
}seg;

int main(){
	cin >> str;
	n = strlen(str);
	sfxarray.init(n, str, sfx, rev, lcp);
	dist[rev[0]] = 1e9;
	for(int i=rev[0]-1; i>=0; i--){
		dist[i] = min(dist[i+1], lcp[i+1]);
	}
	for(int i=rev[0]+1; i<n; i++){
		dist[i] = min(dist[i-1], lcp[i]);
	}
	for(int i=0; i<n; i++) arr[i] = i;
	sort(arr, arr+n, [&](const int &a, const int &b){
		return dist[a] < dist[b];
	});
	int p = n-1;
	seg.init(n);
	seg.add(n);
	int ret = n;
	for(int i=n; i; i--){
		while(p >= 0 && dist[arr[p]] >= i){
			seg.add(sfx[arr[p]]);
			p--;
		}
		if(seg.tree[1].dis <= i){
			ret = min(ret, i);
		}
	}
	printf("%d", ret);
}

